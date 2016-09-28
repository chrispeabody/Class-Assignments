# Chris Peabody
# CS 5401 FS 2015
# gpac.py
# Assignment 2a

import random
import sys

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
			seed = random.randint(1000000000,9999999999)
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
	if line.split(' ')[0] == 'bestfile:': # Still don't know what this one will be used for
		bestfile = line.split(' ')[1]

# Additional configuration
log = file(logfile, 'w')
bestlog = file(bestfile, 'w')
time = 2*height*width

grid = []

# Class definitions
class Pacman:
	def __init__(self):
		self.x = 0
		self.y = 0
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
		
def getPacAction(gamestate):
	validchoices = []
	choice = random.choice(['left','right','up','down','hold'])
	if choice == 'left' and validHere(gamestate[0].x-1, gamestate[0].y) == True:
		validchoices.append('left')
	if choice == 'right' and validHere(gamestate[0].x+1, gamestate[0].y) == True:
		validchoices.append('right')
	if choice == 'up' and validHere(gamestate[0].x, gamestate[0].y-1) == True:
		validchoices.append('up')
	if choice == 'down' and validHere(gamestate[0].x, gamestate[0].y+1) == True:
		validchoices.append('right')
	validchoice.append('hold')

	choice = random.choice(validchoices)

	return choice

def getGhostAction(gamestate, whichghost):
	validchoices = []
	if choice == 'left' and edgeHere(gamestate[1][whichghost].x-1, gamestate[1][whichghost].y) == False:
		validchoices.append('left')
	if choice == 'right' and edgeHere(gamestate[1][whichghost].x+1, gamestate[1][whichghost].y) == False:
		validchoices.append('right')
	if choice == 'up' and edgeHere(gamestate[1][whichghost].x, gamestate[1][whichghost].y-1) == False:
		validchoices.append('up')
	if choice == 'down' and edgeHere(gamestate[1][whichghost].x, gamestate[1][whichghost].y+1) == False:
		validchoices.append('right')

	choice = random.choice(validchoices)

	return choice

# Checks if the location is in bounds
def edgeHere(x, y):
	iswall = False
	if x == -1 or y == -1 or x == width or y == height:
		iswall = True
	return iswall

# Validity checking for mrsP
def validHere(x, y, gamestate):
	isValid = True
	if edgeHere(x, y) == True:
		isValid = False
	for ghost in gamestate[1]:
		if ghost.x == x and ghost.y == y:
			isValid = False

	return isValid

def runGame():
	global pill
	global ghost
	global pacman
	global time
	global curgamelog

	# Clear the game log
	curgamelog = []
	curgamelog.append(width)
	curgamelog.append(height)


	## Initialization of all Objects ##
	# MrsP and the ghosts
	mrsP = Pacman()
	g1 = Ghost(width-2, height-2)
	g2 = Ghost(width-2, height-2)
	g3 = Ghost(width-2, height-2)
	ghosts = [g1, g2, g3]

	# Make pill list and populate it
	pills = []
	for x in range(width):
		for y in range(height):

			if x != 1 or y != 1:
				# Not on mrsp start

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
		gamestate = [mrsP, ghosts, pills]
		#printBoard(gamestate) # For test reasons

		# Put things in log file
		curgamelog.append("m "+str(mrsP.x)+' '+str(mrsP.y))
		for w in range(len(ghosts)):
			curgamelog.append(str(w+1)+' '+str(ghosts[w].x)+' '+str(ghosts[w].y))

		if printedpills == False:
			for pill in pills:
				curgamelog.append('p '+str(pill.x)+' '+str(pill.y))
			printedpills = True

		curgamelog.append('t '+str(curTime)+' '+str(score))

		# Decide on moves
		pacmove = getPacAction(gamestate)
		ghostmove = []
		for num in range(3):
			ghostmove.append(getGhostAction(gamestate, num))
		
		# Execute moves
		mrsP.move(pacmove)
		for num in range(3):
			ghosts[num].move(ghostmove[num])

		# Manage time
		curTime -= 1

		# Collect Pills
		foundone = False
		for pill in pills:
			if pill.x == mrsP.x and pill.y == mrsP.y:
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
			if ghosty.x == mrsP.x and ghosty.y == mrsP.y:
				alive = False

		if alive == False:
			score = int(100*collected/totPills)
			break

		# Update Score
		score = int(100*collected/totPills)

	# Log the final state
	curgamelog.append("m "+str(mrsP.x)+' '+str(mrsP.y))
	for w in range(len(ghosts)):
		curgamelog.append(str(w+1)+' '+str(ghosts[w].x)+' '+str(ghosts[w].y))

	if printedpills == False:
		for pill in pills:
			curgamelog.append('p '+str(pill.x)+' '+str(pill.y))
		printedpills = True

	curgamelog.append('t '+str(curTime)+' '+str(score))



	return score

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

bestgamelog = []
curgamelog = []
highestScoreOfAll = 0
for run in range(numRuns):
	log.write('Run ')
	log.write(str(run+1))
	log.write('\n')

	highestRunScore = 0
	bestInRunLog = []
	for evalu in range(numEvals):
		fitness = runGame()

		if fitness > highestRunScore:
			highestRunScore = fitness
			log.write(str(evalu+1))
			log.write('	')
			log.write(str(fitness))
			log.write("\n")
			bestInRunLog = curgamelog

		print(run),
		print("-"),
		print(evalu)

	if highestRunScore > highestScoreOfAll:
		highestScoreOfAll = highestRunScore
		bestgamelog = bestInRunLog

	log.write('\n')

for line in bestgamelog:
	bestlog.write(str(line))
	bestlog.write('\n')