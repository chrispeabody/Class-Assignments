# Chris Peabody
# CS 5401 FS 2015
# gpac.py
# Assignment 2b

import random
import sys
import copy

sys.setrecursionlimit(10000)

# Connect to configuration #
if len(sys.argv) > 1:
	cfgfile = sys.argv[1]
else:
	cfgfile = 'configs/default.cfg'
cfg = file(cfgfile, 'r')
config = list(cfg)

for i in range(len(config)):
	config[i] = config[i].replace('\r\n','')

# Configure based on file #
for line in config:
	if line.split(' ')[0] == 'height:':
		height = int(line.split(' ')[1])
	if line.split(' ')[0] == 'width:':
		width = int(line.split(' ')[1])
	if line.split(' ')[0] == 'pilldensity:':
		pilldensity = float(line.split(' ')[1])
	if line.split(' ')[0] == 'seed:':
		if line.split(' ')[1] == 'random':
			random.seed()
			seed = random.randint(1000000000,9999999999) # This line is so that I can record the seed. It's still seeded by time because of the previous line.
			random.seed(str(seed))
		else:
			random.seed(line.split(' ')[1])
			seed = line.split(' ')[1]
	if line.split(' ')[0] == 'runs:':
		numRuns = int(line.split(' ')[1])
	if line.split(' ')[0] == 'evals:':
		numEvals = int(line.split(' ')[1])
	if line.split(' ')[0] == 'logfile:':
		logfile = line.split(' ')[1]
	if line.split(' ')[0] == 'solfile:':
		solfile = line.split(' ')[1]
	if line.split(' ')[0] == 'bestfile:':
		bestfile = line.split(' ')[1]
	if line.split(' ')[0] == 'depthmax:':
		depthmax = int(line.split(' ')[1])
	if line.split(' ')[0] == 'lambda:':
		Lambda = int(line.split(' ')[1])
	if line.split(' ')[0] == 'mu:':
		Mu = int(line.split(' ')[1])
	if line.split(' ')[0] == 'noimprovementcount:':
		if int(line.split(' ')[1]) == -1:
			sametermination = False
			noimprovementcount = -1
		else:
			sametermination = True
			noimprovementcount = int(line.split(' ')[1])
	if line.split(' ')[0] == 'recombpercent:':
		recombpercent = float(line.split(' ')[1])
	if line.split(' ')[0] == 'overselectprop:':
		overselectprop = float(line.split(' ')[1])
	if line.split(' ')[0] == 'parentselection:':
		if line.split(' ')[1] == 'overselection':
			parentselection = 'overselection'
		else:
			parentselection = 'proportional'
	if line.split(' ')[0] == 'survivalselection:':
		if line.split(' ')[1] == 'ktournament':
			survivalselection = 'ktournament'
		else:
			survivalselection = 'truncation'
	if line.split(' ')[0] == 'kvalue:':
		kvalue = int(line.split(' ')[1])
	if line.split(' ')[0] == 'parsepressure:':
		parsepressure = int(line.split(' ')[1])

print(str(sametermination))

# Additional configuration
log = file(logfile, 'w')
bestlog = file(bestfile, 'w')
time = 2*height*width

sol = file(solfile, 'w')

# Class definitions
class Node:
	def __init__(self, op):
		self.operation = op
		self.value = random.uniform(0,2)
		self.leftchild = None
		self.rightchild = None
		self.value = None

	def evaluate(self, gamestate):
		# Function nodes
		if self.operation == 'add':
			if self.leftchild is None or self.rightchild is None:
				print("NODE HAS NO CHILD WHERE CHILD IS REQUIRED, ABORTING (add)")
			return (self.leftchild.evaluate(gamestate)+self.rightchild.evaluate(gamestate))
		elif self.operation == 'sub':
			if self.leftchild is None or self.rightchild is None:
				print("NODE HAS NO CHILD WHERE CHILD IS REQUIRED, ABORTING (sub)")
			return (self.leftchild.evaluate(gamestate)-self.rightchild.evaluate(gamestate))
		elif self.operation == 'multi':
			if self.leftchild is None or self.rightchild is None:
				print("NODE HAS NO CHILD WHERE CHILD IS REQUIRED, ABORTING (multi)")
			return (self.leftchild.evaluate(gamestate)*self.rightchild.evaluate(gamestate))
		elif self.operation == 'div':
			if self.leftchild is None or self.rightchild is None:
				print("NODE HAS NO CHILD WHERE CHILD IS REQUIRED, ABORTING (div)")
			# Can't divide my zero
			denom = self.rightchild.evaluate(gamestate)
			if denom == 0:
				denom = 1 # Just make the denom 1
			return (self.leftchild.evaluate(gamestate)/denom)
		elif self.operation == 'rand':
			if self.leftchild is None or self.rightchild is None:
				print("NODE HAS NO CHILD WHERE CHILD IS REQUIRED, ABORTING (rand)")
			return random.uniform(self.leftchild.evaluate(gamestate), self.rightchild.evaluate(gamestate))
		
		# Terminal nodes
		elif self.operation == 'const':
			if self.value is None:
				print("VALUE OF CONST NODE IS NONE, ABORTING")
				sys.exit(0)
			return float(self.value)
		elif self.operation == 'distGhost':
			dist = width+height # A distance greater than possible
			for ghost in gamestate[1]:
				tempDist = abs(ghost.x - gamestate[0].x) + abs(ghost.y - gamestate[0].y)
				if tempDist < dist:
					dist = tempDist
			return dist
		elif self.operation == 'distPill':
			dist = width+height # A distance greater than possible
			for pill in gamestate[2]:
				tempDist = abs(pill.x - gamestate[0].x) + abs(pill.y - gamestate[0].y)
				if tempDist < dist:
					dist = tempDist
			return dist
		else:
			print("ERROR, INVALID EVALUATION OPERATION, ABORTING")
			sys.exit(0)

	def getFormula(self):
		if self.operation == 'add':
			return '('+self.leftchild.getFormula()+' + '+self.rightchild.getFormula()+')'
		elif self.operation == 'sub':
			return '('+self.leftchild.getFormula()+' - '+self.rightchild.getFormula()+')'
		elif self.operation == 'multi':
			return '('+self.leftchild.getFormula()+' * '+self.rightchild.getFormula()+')'
		elif self.operation == 'div':
			return '('+self.leftchild.getFormula()+' / '+self.rightchild.getFormula()+')'
		elif self.operation == 'rand':
			return 'rand('+self.leftchild.getFormula()+', '+self.rightchild.getFormula()+')'
		elif self.operation == 'const':
			return str(self.value)
		elif self.operation == 'distGhost':
			return "distGhost"
		elif self.operation == 'distPill':
			return "distPill"

	def depth(self):
		if self.leftchild is None and self.rightchild is None:
			return 0
		else:
			dep = max(self.leftchild.depth()+1, self.rightchild.depth()+1)

		return dep

	# This will FILL all children underneath until depthmax
	# This does NOT initialize the root
	def fill(self, curdepth):
		if curdepth < depthmax-1:
			op = random.choice(['add','sub','multi','div','rand'])
			left = Node(op)
			op = random.choice(['add','sub','multi','div','rand'])
			right = Node(op)

			self.leftchild = left
			self.rightchild = right

			self.leftchild.fill(curdepth+1)
			self.rightchild.fill(curdepth+1)
		if curdepth == depthmax-1:
			op = random.choice(['const','distGhost','distPill'])
			left = Node(op)
			if op == 'const':
				left.value = random.uniform(0,2)

			op = random.choice(['const','distGhost','distPill'])
			right = Node(op)
			if op == 'const':
				right.value = random.uniform(0,2)

			self.leftchild = left
			self.rightchild = right

	# This will have a CHANCE to create children and call this method again
	# This initializes the root
	def chancefill(self, curdepth):
		ran = random.random()
		if ran < (1-(float(curdepth)/float(depthmax))):
			leaf = False
		else:
			leaf = True

		op = random.choice(['const','distGhost','distPill'])
		self.operation = op
		if op == 'const':
			self.value = random.uniform(0,2)

		if curdepth != depthmax-1 and leaf == False:
			op = random.choice(['add','sub','multi','div','rand'])
			self.operation = op

			self.leftchild = Node('const')
			self.rightchild = Node('const') # These op values get changed in the next layer

			self.leftchild.chancefill(curdepth+1)
			self.rightchild.chancefill(curdepth+1)
		

class Pacman:
	def __init__(self):
		self.x = 0
		self.y = 0
		self.fitness = None
		self.root = Node('const')
		self.runlog = []
	def move(self, way):
		if way == 'left':
			self.x -= 1
		elif way == 'right':
			self.x += 1
		elif way == 'up':
			self.y -= 1
		elif way == 'down':
			self.y += 1
		# Everything else will count as staying #

	def initializeTree(self):
		# We have to initialize the root node.
		chance = random.random()

		# 50% chance of full fill
		if chance < 0.5:
			# This kind of fill requires us to initialize the root
			op = random.choice(['add','sub','multi','div','rand'])
			self.root.operation = op

			self.root.fill(0)
		# 50% chance of chance fill
		else:
			self.root.chancefill(0)

	# Rewrite this to use .evaluate of root
	def getPacAction(self, gamestate):
		choicedict = {}

		leftstate = gamestate
		leftstate[0].x = leftstate[0].x-1
		if validHere(self.x-1, self.y, leftstate):
			leftnum = self.root.evaluate(leftstate)
			choicedict['left'] = leftnum

		rightstate = gamestate
		rightstate[0].x = rightstate[0].x+1
		if validHere(self.x+1, self.y, rightstate):
			rightnum = self.root.evaluate(rightstate)
			choicedict['right'] = rightnum

		upstate = gamestate
		upstate[0].y = upstate[0].y-1
		if validHere(self.x, self.y-1, upstate):
			upnum = self.root.evaluate(upstate)
			choicedict['up'] = upnum

		downstate = gamestate
		downstate[0].y = downstate[0].y+1
		if validHere(self.x, self.y+1, downstate):
			downnum = self.root.evaluate(downstate)
			choicedict['down'] = downnum

		holdnum = self.root.evaluate(gamestate)
		choicedict['hold'] = holdnum

		choose = max(choicedict, key=choicedict.get)

		return choose

	def updateFitness(self):
		global pill
		global ghost
		global time

		# Clear the game log
		self.runlog.append(width)
		self.runlog.append(height)


		## Initialization of all Objects ##
		# self and the ghosts
		self.x = 0
		self.y = 0

		g1 = Ghost(width-1, height-1)
		g2 = Ghost(width-1, height-1)
		g3 = Ghost(width-1, height-1)
		ghosts = [g1, g2, g3]

		# Make pill list and populate it
		pills = []
		for x in range(width):
			for y in range(height):

				if x != 0 or y != 0:
					# Not on self start

					if x == width-2 and y == height-2:
						# Special case, last chance to generate one. Do it if no pills, otherwise normal chance
						if len(pills) == 0:
							newPill = Pill(x, y)
							pills.append(newPill)
						else:
							if random.random() < (pilldensity/100):
								newPill = Pill(x, y)
								pills.append(newPill)
					else:
						# Normal case, generate chance = pill density
						if random.random() < (pilldensity/100):
								newPill = Pill(x, y)
								pills.append(newPill)

		#####################
		## THE ACTUAL GAME ##
		#####################
		totPills = len(pills)
		curTime = time

		collected = 0
		alive = True
		printedpills = False
		score = 0
		while(curTime > 0 and len(pills) > 0):
			# Set and display game state
			gamestate = [self, ghosts, pills]
			#printBoard(gamestate) # For test reasons

			# Put things in log file
			self.runlog.append("m "+str(self.x)+' '+str(self.y))
			for w in range(len(ghosts)):
				self.runlog.append(str(w+1)+' '+str(ghosts[w].x)+' '+str(ghosts[w].y))

			if printedpills == False:
				for pill in pills:
					self.runlog.append('p '+str(pill.x)+' '+str(pill.y))
				printedpills = True

			self.runlog.append('t '+str(curTime)+' '+str(score))

			# Decide on moves
			pacmove = self.getPacAction(gamestate)
			ghostmove = []
			for num in range(3):
				ghostmove.append(getGhostAction(gamestate, num))
			
			# Execute moves
			self.move(pacmove)
			for num in range(3):
				ghosts[num].move(ghostmove[num])

			# Manage time
			curTime -= 1

			# Collect Pills
			foundone = False
			for pill in pills:
				if pill.x == self.x and pill.y == self.y:
					foundone = True
					theone = pill

			if foundone == True:
				pills.remove(theone)
				collected += 1

			if len(pills) == 0:
				score = int(100*collected/totPills)
				score += int(100*curTime/time)
				break

			# See if ghosts caught her
			for ghosty in ghosts:
				if ghosty.x == self.x and ghosty.y == self.y:
					alive = False

			if alive == False:
				score = int(100*collected/totPills)
				break

			# Update Score
			score = int(100*collected/totPills)

		# Log the final state
		self.runlog.append("m "+str(self.x)+' '+str(self.y))
		for w in range(len(ghosts)):
			self.runlog.append(str(w+1)+' '+str(ghosts[w].x)+' '+str(ghosts[w].y))

		if printedpills == False:
			for pill in pills:
				self.runlog.append('p '+str(pill.x)+' '+str(pill.y))
			printedpills = True

		self.runlog.append('t '+str(curTime)+' '+str(score))

		oversize = max(0, self.root.depth() - depthmax)
		self.fitness = score - parsepressure*oversize

		return score

class Ghost:
	def __init__(self, xplace, yplace):
		self.x = width-1
		self.y = height-1
	def move(self, way):
		if way == 'left':
			self.x -= 1
		elif way == 'right':
			self.x += 1
		elif way == 'up':
			self.y -= 1
		elif way == 'down':
			self.y += 1
		else:
			print("INVALID MOVE DIRECTION IN GHOST, ABORTING: ")
			print(way)
			sys.exit(0)

class Pill:	
	def __init__(self, xplace, yplace):
		self.x = xplace
		self.y = yplace

# Just for visual testing purposes #
def printBoard(gamestate):
	for y in range(height):
		for x in range(width):
			occupied = False
			if gamestate[0].x == x and gamestate[0].y == y:
				print('M'),
				occupied = True
			for ghosty in gamestate[1]:
				if ghosty.x == x and ghosty.y == y:
					print('G'),
					occupied = True
			for pill in gamestate[2]:
				if pill.x == x and pill.y == y:
					print('p'),
					occupied = True
			if occupied == False:
				print('-'),
			print('	'),
		print('\n')

def getGhostAction(gamestate, whichghost):
	validchoices = []
	if edgeHere(gamestate[1][whichghost].x-1, gamestate[1][whichghost].y) == False:
		validchoices.append('left')
	if edgeHere(gamestate[1][whichghost].x+1, gamestate[1][whichghost].y) == False:
		validchoices.append('right')
	if edgeHere(gamestate[1][whichghost].x, gamestate[1][whichghost].y-1) == False:
		validchoices.append('up')
	if edgeHere(gamestate[1][whichghost].x, gamestate[1][whichghost].y+1) == False:
		validchoices.append('down')

	choice = random.choice(validchoices)

	return choice

# Checks if the location is in bounds
def edgeHere(x, y):
	iswall = False
	if x <= -1 or y <= -1 or x >= width or y >= height:
		iswall = True
	return iswall

# Validity checking for self
def validHere(x, y, gamestate):
	isValid = True
	if x <= -1 or y <= -1 or x >= width or y >= height:
		isValid = False
	for ghost in gamestate[1]:
		if ghost.x == x and ghost.y == y:
			isValid = False

	return isValid

def doWeStop(curevals, samecount):
	if curevals >= numEvals:
		return True
	elif samecount >= noimprovementcount and sametermination==True:
		return True
	else:
		return False

def mutate(individual):
	newind = copy.deepcopy(individual)
	nodelist = collectNodes(newind.root)

	choice = random.choice(nodelist)

	# We chose a random node in the tree.

	# Will 'chancefill' the tree with a random max depth between 0 and depthmax
	choice.chancefill(random.randint(0,depthmax-1))

	return newind

def recombine(indiv1, indiv2):
	new1 = copy.deepcopy(indiv1)
	new2 = copy.deepcopy(indiv2)

	nodelist1 = collectNodes(new1.root)
	firstnode = random.choice(nodelist1)

	nodelist2 = collectNodes(new2.root)
	secondnode = random.choice(nodelist2)

	parent1 = findParent(new1.root, firstnode)
	parent2 = findParent(new2.root, secondnode)

	if parent1 is not None:
		if parent1.leftchild == firstnode:
			parent1.leftchild = secondnode
		else:
			parent1.rightchild = secondnode
	else:
		new1.root = secondnode
		
	if parent2 is not None:
		if parent2.leftchild == secondnode:
			parent2.leftchild = firstnode
		else:
			parent2.rightchild = firstnode
	else:
		new2.root = firstnode

	return [new1, new2]

def findParent(curnode, targetnode):
	if curnode == targetnode:
		return None
	elif curnode.leftchild is None or curnode.rightchild is None:
		return "Nothere"
	elif curnode.leftchild == targetnode or curnode.rightchild == targetnode:
		return curnode
	else:
		left = findParent(curnode.leftchild, targetnode)
		right = findParent(curnode.rightchild, targetnode)

		if left != "Nothere":
			return left
		else:
			return right

def collectNodes(root):
	if root.leftchild is None or root.rightchild is None:
		# Leaf
		list = [root]
		return list
	else:
		list = [root]
		list1 = collectNodes(root.leftchild)
		list2 = collectNodes(root.rightchild)
		for node in list1:
			list.append(node)
		for node in list2:
			list.append(node)
		return list

def selectAndOperate(population):
	nextgen = []

	while len(nextgen) < Mu:
		print(len(nextgen))
		# First we need to decide on recombination or mutation

		if random.random() < (recombpercent/100):
			type = 'mutation'
		else:
			type = 'recombination'

		parent1 = None
		parent2 = None

		if parentselection == 'proportional':
			while parent2 is None:
				rand = random.choice(population)
				if random.random() < (float(rand.fitness)/200):
					if parent1 == None:
						parent1 = rand
					else:
						parent2 = rand

		elif parentselection == 'overselection':
			orderedpop = sorted(population, key= lambda indiv: indiv.fitness, reverse=True)
			topgroup = orderedpop[0:int(len(orderedpop)*(overselectprop/100))]
			bottomgroup = orderedpop[int(len(orderedpop)*(overselectprop/100)):len(orderedpop)]
			while parent2 is None:
				if random.random() < 0.8:
					choice = random.choice(topgroup)
				else:
					choice = random.choice(bottomgroup)

				if parent1 == None:
					parent1 = choice
				else:
					parent2 = choice
		else:
			print("INVALID PARENT SELECTION TYPE SPECIFIED, ABORTING")
			sys.exit(0)

		if type == 'mutation':
			child = mutate(parent1)
			child.updateFitness()
			nextgen.append(child)
		elif type == 'recombination':
			childlist = recombine(parent1, parent2)
			childlist[0].updateFitness()
			childlist[1].updateFitness()
			nextgen.append(childlist[0])
			nextgen.append(childlist[1])

	nextgen = nextgen[:Mu] #Just in case recombination was the last operator

	return population + nextgen

def survival(population):
	survivors = []

	if survivalselection == 'ktournament':
		temppop = population
		while len(survivors) < Lambda:
			tournpool = []
			for x in range(kvalue):
				rand = random.choice(temppop)
				tournpool.append(rand)

			tournpool = sorted(tournpool, key = lambda indiv: indiv.fitness, reverse=True)
			winner = tournpool[0]
			survivors.append(winner)
			temppop.remove(winner)

	elif survivalselection == 'truncation':
		while len(survivors) < Lambda:
			sortpop = sorted(population, key=lambda indiv: indiv.fitness, reverse = True)
			survivors = sortpop[:Lambda]
	else:
		print("INVALID SURVIVAL SELECTION SPECIFIED, ABORTING")
		sys.exit(0)

	return survivors

def avgFitness(population):
	totfitness = 0
	for indiv in population:
		totfitness += indiv.fitness

	avgfit = float(totfitness)/float(len(population))

	return avgfit

def bestFitness(population):
	best = max(population, key= lambda indiv: indiv.fitness)

	return best.fitness


#################
## The Program ##
#################

# Log Header #
log.write("Width: ")
log.write(str(width))
log.write("\nHeight: ")
log.write(str(height))
log.write("\nPill Density: ")
log.write(str(pilldensity))
log.write("\nSeed: ")
log.write(str(seed))
log.write('\n\n')

# Create a dummy
bestIndividual = Pacman()
bestIndividual.fitness = 0

print("before program")
print(parentselection)
for run in range(numRuns):
	log.write('Run ')
	log.write(str(run+1))
	log.write('\n')

	# Initialize population
	population = [] # List of Mrs. Pacmen
	for x in range(Lambda):
		newpac = Pacman()
		newpac.initializeTree()
		newpac.updateFitness()
		population.append(newpac)
		print(x)
	# Now population is full of lambda pacmen, each with it's own tree and recorded fitness
	print("After initializing pop")

	# Initialize loop control variables
	oldBestInPop = sorted(population, key=lambda indiv: indiv.fitness, reverse=True)[0]
	bestInPopulation = oldBestInPop
	bestInCurrentRun = bestInPopulation
	nochangecount = 0
	curevals = Lambda # This many evaluations already occured on initialization

	# WHILE TERMINATION UNMET - CHANGE TO THIS BEFORE WE'RE DONE
	while doWeStop(curevals, nochangecount) == False:
		population = selectAndOperate(population)
		curevals += Mu
		population = survival(population)

		# Keep an eye on this, lambda is a tricky piece of code
		bestInPopulation = sorted(population, key=lambda indiv: indiv.fitness, reverse=True)[0]
		if bestInPopulation == oldBestInPop:
			nochangecount += 1
		else:
			nochangecount = 0
		oldBestInPop = bestInPopulation

		# this was an error that made it into the final cut
		if bestInPopulation > bestInCurrentRun:
			bestInCurrentRun = bestInPopulation

		log.write(str(curevals))
		log.write('	')
		log.write(str(avgFitness(population)))
		log.write('	')
		log.write(str(bestFitness(population)))
		log.write("\n")

		print(run),
		print("-"),
		print(curevals)

	if bestInCurrentRun.fitness > bestIndividual.fitness:
		bestIndividual = bestInCurrentRun

	log.write('\n')

for line in bestIndividual.runlog:
	bestlog.write(str(line))
	bestlog.write('\n')

sol.write('Formula for best tree found in all runs:\n')
sol.write(bestIndividual.root.getFormula())

# TODO NEXT:
# 				
#				Create EA cycle <-- Working on it
#		Initialization:					<----------------- DONE
#				Ramped Half and Half 	<----------------- DONE
#		Parent Selection:				<----------------- DONE
#				Fitness Proportionoal Selection <----------------- DONE
#				Over-Selection			<----------------- DONE
#		Recombination/Mutation:			<----------------- DONE
#				Sub-Tree Crossover		<----------------- DONE
#				Sub-Tree Mutation 		<----------------- DONE
#		Survival Selection:				<----------------- DONE
#				truncation 				<----------------- DONE
#				k-Tournament without replacement	<----------------- DONE
#		Bloat control:								<----------------- DONE
#				parsimony pressure 					<----------------- DONE
#		Termination:								<----------------- DONE
#				Number of evals 							<----------------- DONE
#				No change in best fitness for n generations <----------------- DONE