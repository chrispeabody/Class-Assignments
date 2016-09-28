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
	if line.split(' ')[0] == 'Psolfile:':
		Psolfile = line.split(' ')[1]
	if line.split(' ')[0] == 'Gsolfile:':
		Gsolfile = line.split(' ')[1]
	if line.split(' ')[0] == 'bestfile:':
		bestfile = line.split(' ')[1]
	if line.split(' ')[0] == 'depthmax:':
		depthmax = int(line.split(' ')[1])

	if line.split(' ')[0] == 'Pmu:':
		PMu = int(line.split(' ')[1])
	if line.split(' ')[0] == 'Plambda:':
		PLambda = int(line.split(' ')[1])
	if line.split(' ')[0] == 'Precombpercent:':
		Precombpercent = float(line.split(' ')[1])
	if line.split(' ')[0] == 'Poverselectprop:':
		Poverselectprop = float(line.split(' ')[1])
	if line.split(' ')[0] == 'Pparentselection:':
		if line.split(' ')[1] == 'overselection':
			Pparentselection = 'overselection'
		else:
			Pparentselection = 'proportional'
	if line.split(' ')[0] == 'Psurvivalselection:':
		if line.split(' ')[1] == 'ktournament':
			Psurvivalselection = 'ktournament'
		else:
			Psurvivalselection = 'truncation'
	if line.split(' ')[0] == 'Pkvalue:':
		Pkvalue = int(line.split(' ')[1])
	if line.split(' ')[0] == 'Pparsepressure:':
		Pparsepressure = int(line.split(' ')[1])

	if line.split(' ')[0] == 'Gmu:':
		GMu = int(line.split(' ')[1])
	if line.split(' ')[0] == 'Glambda:':
		GLambda = int(line.split(' ')[1])
	if line.split(' ')[0] == 'Grecombpercent:':
		Grecombpercent = float(line.split(' ')[1])
	if line.split(' ')[0] == 'Goverselectprop:':
		Goverselectprop = float(line.split(' ')[1])
	if line.split(' ')[0] == 'Gparentselection:':
		if line.split(' ')[1] == 'overselection':
			Gparentselection = 'overselection'
		else:
			Gparentselection = 'proportional'
	if line.split(' ')[0] == 'Gsurvivalselection:':
		if line.split(' ')[1] == 'ktournament':
			Gsurvivalselection = 'ktournament'
		else:
			Gsurvivalselection = 'truncation'
	if line.split(' ')[0] == 'Gkvalue:':
		Gkvalue = int(line.split(' ')[1])
	if line.split(' ')[0] == 'Gparsepressure:':
		Gparsepressure = int(line.split(' ')[1])

# Additional configuration
log = file(logfile, 'w')
bestlog = file(bestfile, 'w')
time = 2*height*width

Psol = file(Psolfile, 'w')
Gsol = file(Gsolfile, 'w')

# Class definitions
class Node:
	def __init__(self, op, typ):
		self.operation = op
		self.value = random.uniform(0,2)
		self.leftchild = None
		self.rightchild = None
		self.type = typ # Used 100% purely for catching potential errors

	def evaluate(self, gamestate, gnum):
		# Function nodes
		if self.operation == 'add':
			if self.leftchild is None or self.rightchild is None:
				print("NODE HAS NO CHILD WHERE CHILD IS REQUIRED, ABORTING (add)")
			return (self.leftchild.evaluate(gamestate, gnum)+self.rightchild.evaluate(gamestate, gnum))
		elif self.operation == 'sub':
			if self.leftchild is None or self.rightchild is None:
				print("NODE HAS NO CHILD WHERE CHILD IS REQUIRED, ABORTING (sub)")
			return (self.leftchild.evaluate(gamestate, gnum)-self.rightchild.evaluate(gamestate, gnum))
		elif self.operation == 'multi':
			if self.leftchild is None or self.rightchild is None:
				print("NODE HAS NO CHILD WHERE CHILD IS REQUIRED, ABORTING (multi)")
			return (self.leftchild.evaluate(gamestate, gnum)*self.rightchild.evaluate(gamestate, gnum))
		elif self.operation == 'div':
			if self.leftchild is None or self.rightchild is None:
				print("NODE HAS NO CHILD WHERE CHILD IS REQUIRED, ABORTING (div)")
			# Can't divide my zero
			denom = self.rightchild.evaluate(gamestate, gnum)
			if denom == 0:
				denom = 1 # Just make the denom 1
			return (self.leftchild.evaluate(gamestate, gnum)/denom)
		elif self.operation == 'rand':
			if self.leftchild is None or self.rightchild is None:
				print("NODE HAS NO CHILD WHERE CHILD IS REQUIRED, ABORTING (rand)")
			return random.uniform(self.leftchild.evaluate(gamestate, gnum), self.rightchild.evaluate(gamestate, gnum))
		
		## Terminal nodes ##
		elif self.operation == 'const':
			if self.value is None:
				print("VALUE OF CONST NODE IS NONE, ABORTING")
				sys.exit(0)
			return float(self.value)
		# These two are pacman only
		elif self.operation == 'distGhost':
			if self.type != 'pac':
				print("GHOST NODE ATTEMPTING TO USE PAC PRIMITIVE, ABORTING (distGhost)")
				sys.exit(0)
			dist = width+height # A distance greater than possible
			for ghost in gamestate[1]:
				tempDist = abs(ghost.x - gamestate[0].x) + abs(ghost.y - gamestate[0].y)
				if tempDist < dist:
					dist = tempDist
			return dist
		elif self.operation == 'distPill':
			if self.type != 'pac':
				print("GHOST NODE ATTEMPTING TO USE PAC PRIMITIVE, ABORTING (distPill)")
				sys.exit(0)
			dist = width+height # A distance greater than possible
			for pill in gamestate[2]:
				tempDist = abs(pill.x - gamestate[0].x) + abs(pill.y - gamestate[0].y)
				if tempDist < dist:
					dist = tempDist
			return dist
		# These two are ghost only
		elif self.operation == 'distOtherGhost':
			if self.type != 'ghost':
				print("PAC NODE ATTEMPTING TO USE GHOST PRIMITIVE, ABORTING (distOtherGhost)")
				sys.exit(0)
			dist = width+height
			for g in range(len(gamestate[1])):
				if g != gnum:
					tempDist = abs(gamestate[1][gnum].x - gamestate[1][g].x) + abs(gamestate[1][gnum].y - gamestate[1][g].y)
					if tempDist < dist:
						dist = tempDist
			return dist
		elif self.operation == 'distPac':
			if self.type != 'ghost':
				print("PAC NODE ATTEMPTING TO USE GHOST PRIMITIVE, ABORTING (distPac)")
				sys.exit(0)
			dist = abs(gamestate[1][gnum].x - gamestate[0].x) + abs(gamestate[1][gnum].y - gamestate[0].y)
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
		elif self.operation == 'distOtherGhost':
			return "distOtherGhost"
		elif self.operation == 'distPac':
			return "distPac"

	def depth(self):
		if self.leftchild is None and self.rightchild is None:
			return 0
		else:
			dep = max(self.leftchild.depth()+1, self.rightchild.depth()+1)

		return dep

	# This will FILL all children underneath until depthmax
	# This does NOT initialize the root
	def Pfill(self, curdepth):
		if curdepth < depthmax-1:
			op = random.choice(['add','sub','multi','div','rand'])
			left = Node(op, 'pac')
			op = random.choice(['add','sub','multi','div','rand'])
			right = Node(op, 'pac')

			self.leftchild = left
			self.rightchild = right

			self.leftchild.Pfill(curdepth+1)
			self.rightchild.Pfill(curdepth+1)
		if curdepth == depthmax-1:
			op = random.choice(['const','distGhost','distPill'])
			left = Node(op, 'pac')
			if op == 'const':
				left.value = random.uniform(0,2)

			op = random.choice(['const','distGhost','distPill'])
			right = Node(op, 'pac')
			if op == 'const':
				right.value = random.uniform(0,2)

			self.leftchild = left
			self.rightchild = right

	# This will have a CHANCE to create children and call this method again
	# This initializes the root
	def Pchancefill(self, curdepth):
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

			self.leftchild = Node('const', 'pac')
			self.rightchild = Node('const', 'pac') # These op values get changed in the next layer

			self.leftchild.Pchancefill(curdepth+1)
			self.rightchild.Pchancefill(curdepth+1)

	# This will FILL all children underneath until depthmax
	# This does NOT initialize the root
	def Gfill(self, curdepth):
		if curdepth < depthmax-1:
			op = random.choice(['add','sub','multi','div','rand'])
			left = Node(op, 'ghost')
			op = random.choice(['add','sub','multi','div','rand'])
			right = Node(op, 'ghost')

			self.leftchild = left
			self.rightchild = right

			self.leftchild.Gfill(curdepth+1)
			self.rightchild.Gfill(curdepth+1)
		if curdepth == depthmax-1:
			op = random.choice(['const','distOtherGhost','distPac'])
			left = Node(op, 'ghost')
			if op == 'const':
				left.value = random.uniform(0,2)

			op = random.choice(['const','distOtherGhost','distPac'])
			right = Node(op, 'ghost')
			if op == 'const':
				right.value = random.uniform(0,2)

			self.leftchild = left
			self.rightchild = right

	# This will have a CHANCE to create children and call this method again
	# This initializes the root
	def Gchancefill(self, curdepth):
		ran = random.random()
		if ran < (1-(float(curdepth)/float(depthmax))):
			leaf = False
		else:
			leaf = True

		op = random.choice(['const','distOtherGhost','distPac'])
		self.operation = op
		if op == 'const':
			self.value = random.uniform(0,2)

		if curdepth != depthmax-1 and leaf == False:
			op = random.choice(['add','sub','multi','div','rand'])
			self.operation = op

			self.leftchild = Node('const', 'ghost')
			self.rightchild = Node('const', 'ghost') # These op values get changed in the next layer

			self.leftchild.Gchancefill(curdepth+1)
			self.rightchild.Gchancefill(curdepth+1)
		
class Pacman:
	def __init__(self):
		self.x = 0
		self.y = 0
		self.fitness = None
		self.fitnessdump = 0
		self.timesEvaluated = 0
		self.root = Node('const', 'pac')
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

			self.root.Pfill(0)
		# 50% chance of chance fill
		else:
			self.root.Pchancefill(0)

	def getPacAction(self, gamestate):
		choicedict = {}

		leftstate = gamestate
		leftstate[0].x = leftstate[0].x-1
		if validHere(self.x-1, self.y, leftstate):
			leftnum = self.root.evaluate(leftstate, 10)
			# Use 10 as the parameter to throw an error if pacman tries to use a ghost primitive
			choicedict['left'] = leftnum
		leftstate[0].x = leftstate[0].x+1

		rightstate = gamestate
		rightstate[0].x = rightstate[0].x+1
		if validHere(self.x+1, self.y, rightstate):
			rightnum = self.root.evaluate(rightstate, 10)
			choicedict['right'] = rightnum
		rightstate[0].x = rightstate[0].x-1

		upstate = gamestate
		upstate[0].y = upstate[0].y-1
		if validHere(self.x, self.y-1, upstate):
			upnum = self.root.evaluate(upstate, 10)
			choicedict['up'] = upnum
		upstate[0].y = upstate[0].y+1

		downstate = gamestate
		downstate[0].y = downstate[0].y+1
		if validHere(self.x, self.y+1, downstate):
			downnum = self.root.evaluate(downstate, 10)
			choicedict['down'] = downnum
		downstate[0].y = downstate[0].y-1

		holdnum = self.root.evaluate(gamestate, 10)
		choicedict['hold'] = holdnum

		choose = max(choicedict, key=choicedict.get)

		return choose

	def addFitness(self, score):
		self.fitnessdump += score
		self.timesEvaluated += 1
		self.fitness = float(self.fitnessdump)/float(self.timesEvaluated)

class Ghost:
	def __init__(self):
		self.x = width-1
		self.y = height-1
		self.fitness = 0
		self.fitnessdump = 0
		self.timesEvaluated = 0
		self.root = Node('const', 'ghost')

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

	def initializeTree(self):
		# We have to initialize the root node.
		chance = random.random()

		# 50% chance of full fill
		if chance < 0.5:
			# This kind of fill requires us to initialize the root
			op = random.choice(['add','sub','multi','div','rand'])
			self.root.operation = op

			self.root.Gfill(0)
		# 50% chance of chance fill
		else:
			self.root.Gchancefill(0)

	def getGhostAction(self, gamestate, ghostnum):
		choicedict = {}

		leftstate = gamestate
		leftstate[1][ghostnum].x = leftstate[1][ghostnum].x-1
		if not edgeHere(leftstate[1][ghostnum].x, leftstate[1][ghostnum].y):
			leftnum = self.root.evaluate(leftstate, ghostnum)
			choicedict['left'] = leftnum
		leftstate[1][ghostnum].x = leftstate[1][ghostnum].x+1

		rightstate = gamestate
		rightstate[1][ghostnum].x = rightstate[1][ghostnum].x+1
		if not edgeHere(rightstate[1][ghostnum].x, rightstate[1][ghostnum].y):
			rightnum = self.root.evaluate(rightstate, ghostnum)
			choicedict['right'] = rightnum
		rightstate[1][ghostnum].x = rightstate[1][ghostnum].x-1

		upstate = gamestate
		upstate[1][ghostnum].y = upstate[1][ghostnum].y-1
		if not edgeHere(upstate[1][ghostnum].x, upstate[1][ghostnum].y):
			upnum = self.root.evaluate(upstate, ghostnum)
			choicedict['up'] = upnum
		upstate[1][ghostnum].y = upstate[1][ghostnum].y+1

		downstate = gamestate
		downstate[1][ghostnum].y = downstate[1][ghostnum].y+1
		if not edgeHere(downstate[1][ghostnum].x, downstate[1][ghostnum].y):
			downnum = self.root.evaluate(downstate, ghostnum)
			choicedict['down'] = downnum
		downstate[1][ghostnum].y = downstate[1][ghostnum].y-1

		choose = max(choicedict, key=choicedict.get)

		return choose

	def addFitness(self, score):
		self.fitnessdump += score
		self.timesEvaluated += 1
		self.fitness = float(self.fitnessdump)/float(self.timesEvaluated)

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

class Pill:	
	def __init__(self, xplace, yplace):
		self.x = xplace
		self.y = yplace

def duelFitness(pacControl, ghostControl):
		global pill
		global ghost
		global time

		# Clear the game log
		# Game log will be of last evaluation if more than one eval happened
		pacControl.runlog = []
		pacControl.runlog.append(width)
		pacControl.runlog.append(height)


		## Initialization of all Objects ##
		# self and the ghosts
		pacControl.x = 0
		pacControl.y = 0

		g1 = copy.deepcopy(ghostControl)
		g1.x = width-1
		g1.y = height-1

		g2 = copy.deepcopy(ghostControl)
		g2.x = width-1
		g2.y = height-1

		g3 = copy.deepcopy(ghostControl)
		g3.x = width-1
		g3.y = height-1

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
			gamestate = [pacControl, ghosts, pills]
			#printBoard(gamestate) # For test reasons

			# Put things in log file
			pacControl.runlog.append("m "+str(pacControl.x)+' '+str(pacControl.y))
			for w in range(len(ghosts)):
				pacControl.runlog.append(str(w+1)+' '+str(ghosts[w].x)+' '+str(ghosts[w].y))

			if printedpills == False:
				for pill in pills:
					pacControl.runlog.append('p '+str(pill.x)+' '+str(pill.y))
				printedpills = True

			pacControl.runlog.append('t '+str(curTime)+' '+str(score))

			# Decide on moves
			pacmove = pacControl.getPacAction(gamestate)
			ghostmove = []
			for num in range(3):
				ghostmove.append(ghostControl.getGhostAction(gamestate, num))
			
			# Execute moves
			pacControl.move(pacmove)
			for num in range(3):
				ghosts[num].move(ghostmove[num])

			# Manage time
			curTime -= 1

			# Collect Pills
			foundone = False
			for pill in pills:
				if pill.x == pacControl.x and pill.y == pacControl.y:
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
				if ghosty.x == pacControl.x and ghosty.y == pacControl.y:
					alive = False

			if alive == False:
				score = int(100*collected/totPills)
				break

			# Update Score
			score = int(100*collected/totPills)

		# Log the final state
		pacControl.runlog.append("m "+str(pacControl.x)+' '+str(pacControl.y))
		for w in range(len(ghosts)):
			pacControl.runlog.append(str(w+1)+' '+str(ghosts[w].x)+' '+str(ghosts[w].y))

		if printedpills == False:
			for pill in pills:
				pacControl.runlog.append('p '+str(pill.x)+' '+str(pill.y))
			printedpills = True

		pacControl.runlog.append('t '+str(curTime)+' '+str(score))

		Poversize = max(0, pacControl.root.depth() - depthmax)
		Goversize = max(0, ghostControl.root.depth() - depthmax)

		adjustedGhostScore = (200-score) - Gparsepressure*Goversize
		adjustedPacScore = score - Pparsepressure*Poversize

		pacControl.addFitness(adjustedPacScore)
		ghostControl.addFitness(adjustedGhostScore)
		print(Poversize, Goversize, score, adjustedPacScore, adjustedGhostScore)
		print("fitnessval", pacControl.fitness, ghostControl.fitness)

		return score

def mutate(individual, typ):
	newind = copy.deepcopy(individual)

	# deep copy causes old fitness information to be saved. Kill it.
	newind.fitness = 0
	newind.timesEvaluated = 0
	newind.fitnessdump = 0

	nodelist = collectNodes(newind.root)

	choice = random.choice(nodelist)

	# We chose a random node in the tree.

	# Will 'chancefill' the tree with a random max depth between 0 and depthmax
	if typ == 'pac':
		choice.Pchancefill(random.randint(0,depthmax-1))
	elif typ == 'ghost':
		choice.Gchancefill(random.randint(0,depthmax-1))
	else:
		print("INVALID TYPE FOR MUTATE SPECIFIED, ABORTING")
		sys.exit(0)

	return newind

def recombine(indiv1, indiv2):
	new1 = copy.deepcopy(indiv1)
	new2 = copy.deepcopy(indiv2)

	# deep copy causes old fitness information to be saved. Kill it.
	new1.fitness = 0
	new1.timesEvaluated = 0
	new1.fitnessdump = 0
	new2.fitness = 0
	new2.timesEvaluated = 0
	new2.fitnessdump = 0

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
def selectAndOperate(pacPop, ghostPop):
	Pnextgen = []

	while len(Pnextgen) < PLambda:
		print('pacs-gen', len(Pnextgen))
		# First we need to decide on recombination or mutation

		if random.random() < (Precombpercent/100):
			type = 'mutation'
		else:
			type = 'recombination'

		parent1 = None
		parent2 = None

		if Pparentselection == 'proportional':
			while parent2 is None:
				rand = random.choice(pacPop)
				if random.random() < (float(rand.fitness)/200):
					if parent1 == None:
						parent1 = rand
					else:
						parent2 = rand

		elif Pparentselection == 'overselection':
			orderedpop = sorted(pacPop, key= lambda indiv: indiv.fitness, reverse=True)
			topgroup = orderedpop[0:int(len(orderedpop)*(Poverselectprop/100))]
			bottomgroup = orderedpop[int(len(orderedpop)*(Poverselectprop/100)):len(orderedpop)]
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
			print("INVALID PARENT SELECTION TYPE SPECIFIED, ABORTING (P)")
			sys.exit(0)

		if type == 'mutation':
			child = mutate(parent1, 'pac')
			Pnextgen.append(child)
		elif type == 'recombination':
			childlist = recombine(parent1, parent2)
			Pnextgen.append(childlist[0])
			Pnextgen.append(childlist[1])

	Pnextgen = Pnextgen[:PLambda] #Just in case recombination was the last operator

	# Now for ghosts
	Gnextgen = []

	while len(Gnextgen) < GLambda:
		print('ghosts-gen', len(Gnextgen))
		# First we need to decide on recombination or mutation

		if random.random() < (Grecombpercent/100):
			type = 'mutation'
		else:
			type = 'recombination'

		parent1 = None
		parent2 = None

		if Gparentselection == 'proportional':
			while parent2 is None:
				rand = random.choice(ghostPop)
				if random.random() < (float(rand.fitness)/200):
					if parent1 == None:
						parent1 = rand
					else:
						parent2 = rand

		elif Gparentselection == 'overselection':
			orderedpop = sorted(ghostPop, key= lambda indiv: indiv.fitness, reverse=True)
			topgroup = orderedpop[0:int(len(orderedpop)*(Goverselectprop/100))]
			bottomgroup = orderedpop[int(len(orderedpop)*(Goverselectprop/100)):len(orderedpop)]
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
			print("INVALID PARENT SELECTION TYPE SPECIFIED, ABORTING (G)")
			sys.exit(0)

		if type == 'mutation':
			child = mutate(parent1, 'ghost')
			Gnextgen.append(child)
		elif type == 'recombination':
			childlist = recombine(parent1, parent2)
			Gnextgen.append(childlist[0])
			Gnextgen.append(childlist[1])

	Gnextgen = Gnextgen[:GLambda] #Just in case recombination was the last operator

	scoredPops = evaluateGroups(Pnextgen, Gnextgen)
	Pnextgen = scoredPops[0]
	Gnextgen = scoredPops[1]

	return ((pacPop + Pnextgen), (ghostPop + Gnextgen))

def survival(pacPop, ghostPop):
	Psurvivors = []

	if Psurvivalselection == 'ktournament':
		temppop = pacPop
		while len(Psurvivors) < PMu:
			tournpool = []
			for x in range(Pkvalue):
				rand = random.choice(temppop)
				tournpool.append(rand)

			tournpool = sorted(tournpool, key = lambda indiv: indiv.fitness, reverse=True)
			winner = tournpool[0]
			Psurvivors.append(winner)
			temppop.remove(winner)

	elif Psurvivalselection == 'truncation':
		while len(Psurvivors) < PMu:
			sortpop = sorted(pacPop, key=lambda indiv: indiv.fitness, reverse = True)
			Psurvivors = sortpop[:PMu]
	else:
		print("INVALID SURVIVAL SELECTION SPECIFIED, ABORTING (P)")
		sys.exit(0)

	Gsurvivors = []

	if Gsurvivalselection == 'ktournament':
		temppop = ghostPop
		while len(Gsurvivors) < GMu:
			tournpool = []
			for x in range(Gkvalue):
				rand = random.choice(temppop)
				tournpool.append(rand)

			tournpool = sorted(tournpool, key = lambda indiv: indiv.fitness, reverse=True)
			winner = tournpool[0]
			Gsurvivors.append(winner)
			temppop.remove(winner)

	elif Gsurvivalselection == 'truncation':
		while len(Gsurvivors) < GMu:
			sortpop = sorted(ghostPop, key=lambda indiv: indiv.fitness, reverse = True)
			Gsurvivors = sortpop[:GMu]
	else:
		print("INVALID SURVIVAL SELECTION SPECIFIED, ABORTING (G)")
		sys.exit(0)


	return (Psurvivors, Gsurvivors)

def avgFitness(population):
	totfitness = 0
	for indiv in population:
		totfitness += indiv.fitness

	avgfit = float(totfitness)/float(len(population))

	return avgfit

def bestFitness(population):
	best = max(population, key= lambda indiv: indiv.fitness)

	return best.fitness

def doWeStop(curevals):
	if curevals >= numEvals:
		return True
	else:
		return False

def evaluateGroups(pacs, ghosts):
	# pacs is the population of Pacman()
	# ghosts is the population of Ghost()

	paccount = len(pacs)
	ghostcount = len(ghosts)
	evalcount = max(paccount, ghostcount)

	tempPacs = pacs
	tempGhosts = ghosts

	finalPacs = []
	finalGhosts = []

	for x in range(evalcount):
		if len(tempPacs) == 0:
			tempPacs = finalPacs
		if len(tempGhosts) == 0:
			tempGhosts = finalGhosts

		pacchoice = random.choice(tempPacs)
		ghostchoice = random.choice(tempGhosts)

		duelFitness(pacchoice, ghostchoice)

		tempPacs.remove(pacchoice)
		finalPacs.append(pacchoice)
		tempGhosts.remove(ghostchoice)
		finalGhosts.append(ghostchoice)
		print("eval-complete",x)

	return (finalPacs, finalGhosts)



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

# List of best individual from any run
bestPacIndividuals = []
bestGhostIndividuals = []

print("before program")
for run in range(numRuns):
	log.write('Run ')
	log.write(str(run+1))
	log.write('\n')

	# Initialize population
	pacPopulation = [] # List of Mrs. Pacmen
	ghostPopulation = []
	for x in range(PMu):
		newpac = Pacman()
		newpac.initializeTree()
		pacPopulation.append(newpac)
		print('pacinit', x)

	for y in range(GMu):
		newghost = Ghost()
		newghost.initializeTree()
		ghostPopulation.append(newghost)
		print('ghostinit', y)

	# score them
	scoredPops = evaluateGroups(pacPopulation, ghostPopulation)
	pacPopulation = scoredPops[0]
	ghostPopulation = scoredPops[1]

	print("After init/eval pops")

	# Initialize loop control variables
	curevals = max(PMu, GMu) # This many evaluations already occured on initialization

	while doWeStop(curevals) == False:
		newPops = selectAndOperate(pacPopulation, ghostPopulation)
		pacPopulation = newPops[0]
		ghostPopulation = newPops[1]

		curevals += max(PLambda, GLambda)

		newPops = survival(pacPopulation, ghostPopulation)
		pacPopulation = newPops[0]
		ghostPopulation = newPops[1]

		log.write(str(curevals))
		log.write('	')
		log.write(str(avgFitness(pacPopulation)))
		log.write('	')
		log.write(str(bestFitness(pacPopulation)))
		log.write("\n")

		# For debugging
		print(run),
		print("-"),
		print(curevals)

	# Keep an eye on this, 'lambda' is a tricky piece of code, not to be confused with PLambda
	bestPacInPop = sorted(pacPopulation, key=lambda indiv: indiv.fitness, reverse=True)[0]
	bestGhostInPop = sorted(ghostPopulation, key=lambda indiv: indiv.fitness, reverse=True)[0]

	bestPacIndividuals.append(bestPacInPop)
	bestGhostIndividuals.append(bestGhostInPop)

	log.write('\n')

# This will write the run file for the best in the final run
for line in bestPacIndividuals[len(bestPacIndividuals)-1].runlog:
	bestlog.write(str(line))
	bestlog.write('\n')

# Give a solution for each run representing the best in the last generation
for pac in range(len(bestPacIndividuals)):
	Psol.write('Formula for best Pacman tree found in run ')
	Psol.write(str(pac+1))
	Psol.write(':\n')
	Psol.write(bestPacIndividuals[pac].root.getFormula())
	Psol.write('\n\n')

for gos in range(len(bestGhostIndividuals)):
	Gsol.write('Formula for best Ghost tree found in run ')
	Gsol.write(str(pac+1))
	Gsol.write(':\n')
	Gsol.write(bestGhostIndividuals[gos].root.getFormula())
	Gsol.write('\n\n')

# TODO NEXT:
# 				FOR GHOSTS THIS TIME
#		Initialization:								<- Done
#				Ramped Half and Half 				<- Done
#		Parent Selection:				
#				Fitness Proportionoal Selection 
#				Over-Selection			
#		Recombination/PLambdatation:			
#				Sub-Tree Crossover		
#				Sub-Tree PLambdatation 		
#		Survival Selection:				
#				truncation 				
#				k-Tournament without replacement	
#		Bloat control:								<- Done
#				parsimony pressure 					<- Done	
#		Termination:								<- Done
#				Number of evals 					<- Done						


