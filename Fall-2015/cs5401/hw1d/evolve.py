# Chris Peabody
# cpgzbd@mst.edu
# COMP SCI 5401 FS2015 Assignment 1c

import random
import sys
import math

### --- COFIGURATION --- ###

# Connect with the config file, and put in list form
cfgfile = 'none'
if len(sys.argv) > 1:
	cfgfile = sys.argv[1]
else:
	cfgfile = 'configs/default.cfg'
cfg = file(cfgfile, 'r')
config = list(cfg)

# Removing extra \r and \n from the file lines
for i in range(len(config)):
	config[i] = config[i].replace('\r\n','')

# Configure program based on file
cnfFilename = config[0]
logfile = config[1]
solutionfile = config[2]
if config[3] == 'random':
	random.seed()
	# The purpose of this is to be able to print out the seed.
	# It is much harder to print out the seed when it's based on time.
	ranseed = random.randint(1000000000,9999999999)
	random.seed(str(ranseed))
else:
	random.seed(config[3])
	ranseed = config[3]
numruns = int(config[4])
if config[5].split(' ')[0] == 'tournament':
	pselect = 'tournament'
	pTournSize = int(config[5].split(' ')[1])
else:
	pselect = 'proportional'
	pTournSize = -1

if config[6].split(' ')[0] == 'tournament':
	sselect = 'tournament'
	sTournSize = int(config[6].split(' ')[1])
else:
	sselect = 'truncation'
	sTournSize = -1

if config[7].split(' ')[0] == 'True':
	evalterm = True
else:
	evalterm = False
numevals = int(config[7].split(' ')[1])

if config[8].split(' ')[0] == 'True':
	shellconverge = True
else:
	shellconverge = False
shellconvergen = int(config[8].split(' ')[1])

if config[9].split(' ')[0] == 'True':
	rrestart = True
else:
	rrestart = False
eliteR = int(config[9].split(' ')[1])

popsize = int(config[10])
offspringsize = int(config[11])

if config[12] == 'No seed':
	seededinit = False
	seedfile = ''
else:
	seededinit = True
	seedfile = config[12]

if config[13] == 'comma':
	survivalstrat = 'comma'
else:
	survivalstrat = 'plus'

frontsfile = config[14]
fronts = file(frontsfile, 'w')

# Connect log and solution files
log = file(logfile,'w')
log.write('Result Log\n')
log.write('Cnf file: ')
log.write(cnfFilename)
log.write('\nGenerator Seed: ')
log.write(str(ranseed))
log.write('\nConfig file contents: \n\n')
for line in config:
	log.write(line)
	log.write('\n')
log.write("\n")
sol = file(solutionfile,'w')

### --- Constraint Testing --- ###
if survivalstrat == 'comma' and offspringsize <= popsize:
	# Doesn't make sense for lambda < mu in comma strategy
	log.write('\n\nLAMBDA < MU IN COMMA STRATEGY, ABORTING')
	sys.exit(0)

if numruns <= 0:
	log.write('\n\nINVALID INPUT FOR RUNS, ABORTING')
	sys.exit(0)

if numevals <= 0:
	log.write('\n\nINVALID INPUT FOR EVALS, ABORTING')
	sys.exit(0)

if shellconvergen <= 0:
	log.write('\n\nINVALID INPUT FOR SHELL CONVERGENCE MAX, ABORTING')
	sys.exit(0)

if eliteR < 0 or eliteR > popsize:
	log.write('\n\nINVALID INPUT FOR R IN R RESTART, ABORTING')
	sys.exit(0)

### --- CLAUSE COLLECTION --- ###

# Connect with cnf data and put in list form
cnf = list(file(cnfFilename,'r'))

# Remove extra \r and \n characters again
for i in range(len(cnf)):
	cnf[i] = cnf[i].replace('\r\n','')

foundclauses = False # Used for transition into clause collection
clauses = [] # Used for clause storage, a list of lists
# Each entry in clauses is a clause made up of a list, where each
# entry on that list is it's variable parts

# Sift through cnf and collect clauses
for line in cnf:
	if foundclauses == False:
		if line[0] == 'p':
			nbvar = int(line.split(' ')[2])
			nbclauses = int(line.split(' ')[3])
			foundclauses = True
	else:
		clauses.append((line.replace(' 0','')).split(' '))

# Set the inital mutation rate based on the number of variables
mutrate = 1/nbvar

### --- SATISFIED FITNESS FUNCTION --- ###
def fitness_sat(variables):
	numtrue = 0
	for cls in clauses:
		# cls is a list, each entry is a number with a possible '-' in front
		clauseConfirmed = False # A flag that will be set to true if the clause has a true value
		for var in cls:
			neg = False # A flag that is true if the variable is negated
			if var[0] == '-':
				neg = True;
			varnum = int(var.replace('-','')) # Which variable this is
			# If the variable is true and not negated, or if the variable is false and negated
			if variables[varnum-1] == True and neg == False:
				clauseConfirmed = True
			if variables[varnum-1] == False  and neg == True:
				clauseConfirmed = True
		if clauseConfirmed == True:
			numtrue += 1
	return numtrue

### --- AVERAGE SATISFIED FITNESS --- ###
def avgfitness_sat(population):
	i = 0
	for specimen in population:
		i += fitness_sat(specimen)

	avg = i/len(population)
	return avg

### --- LEAST-SET FITNESS FUNCTION--- ###
def fitness_unset(variables):
	numunset = 0
	for var in variables:
		if var == '':
			numunset += 1

	return numunset

### --- AVERAGE LEAST-SET FITNESS --- ###
def avgfitness_unset(population):
	i = 0
	for specimen in population:
		i += fitness_unset(specimen)

	avg = i/len(population)
	return avg
	
### --- RETURN THE DOMINANCE LAYERS --- ###

def putInDomLayers(population):
	domLayers = [[[], []]] # Clear layers
	# Fill the first layer with the whole population

	# This makes sure no identical individuals make it in. One is all we need.
	newpop = []
	for item in population:
		if newpop.count(item) == 0:
			newpop.append(item)

	population = newpop

	for x in range(len(population)):
		domLayers[0][0].append(population[x])
		domLayers[0][1].append((fitness_sat(population[x]), fitness_unset(population[x])))

	for w in range(len(domLayers)):
		noCheck = [] # List of specimen (index) not to check
		moveDown = [] # List of specimen to move down
		moveDownTuples = [] # Fitness tuples to move down
		for i in range(len(domLayers[w][0])):
			# Make sure it's not on the noCheck list
			if noCheck.count(i) == 0: 
				for x in range(len(domLayers[w][0])):
					# Make sure it's not comparing to self or to a noCheck
					if i != x and noCheck.count(x) == 0:
						if domLayers[w][1][i][0] >= domLayers[w][1][x][0] and domLayers[w][1][i][1] >= domLayers[w][1][x][1]:
							if domLayers[w][1][i][0] != domLayers[w][1][x][0] or domLayers[w][1][i][1] != domLayers[w][1][x][1]:
								# i dominates x, mark x as dominated and as a noCheck
								noCheck.append(x)
								moveDown.append(domLayers[w][0][x])
								moveDownTuples.append(domLayers[w][1][x])
						elif domLayers[w][1][i][0] <= domLayers[w][1][x][0] and domLayers[w][1][i][1] <= domLayers[w][1][x][1]:
								# x dominates i, mark i as dominated and as a noCheck
								noCheck.append(i)
								moveDown.append(domLayers[w][0][i])
								moveDownTuples.append(domLayers[w][1][i])
								break
			# If we need a new layer and there is none
			if len(moveDown) > 0 and len(domLayers) <= w+1:
				domLayers.append([[],[]])

		# Move things to the next layer down and remove them from this layer
		for n in range(len(moveDown)):
			domLayers[w+1][0].append(moveDown[n])
			domLayers[w+1][1].append(moveDownTuples[n])
			domLayers[w][0].remove(moveDown[n])
			domLayers[w][1].remove(moveDownTuples[n])

	return domLayers


### --- FIND WHICH SHELL SPECIMEN IS IN --- ###
def whichShell(specimen):
	found = False
	place = 1

	for x in range(len(dominationLayers)):
		if dominationLayers[x][0].count(specimen) > 0:
			found = True
			break
		else:
			place += 1

	if found:
		return place
	else:
		return -1

### --- POPULATE THE POPULATION BASED ON SIZE --- ###
def populate(size):
	pop = [] # A blank list of specimen

	if seededinit == True:
		seedsf = file(seedfile, 'r')
		seeds = list(seedsf)

		#strip file of unnecessary symbols, construct members, add members to population
		for i in range(len(seeds)):
			seeds[i] = seeds[i].replace('\r\n','')

			member = []
			for x in seed[i].split(' '):
				if x[0] == '-':
					member.append(False)
				elif x == '?':
					member.append('')
				else:
					member.append(True)

			member = member[:nbvar] # Chop member down to size if too many variables

			pop.append(member)

	# Fill out remaining unseeded population members
	while len(pop) < size:
		varset = [] # Set of variables to complete a clause
		for var in range(nbvar):
			varset.append(random.choice([True, False, '']))

		pop.append(varset)

	pop = pop[:size] # Truncate in case seed had more members than the initial population should

	return pop

### --- PARENT SELECTION AND RECOMBINATION --- ###
def selAndRecom(population):
	offspring = []

	for i in range(offspringsize):
		parent1 = []
		parent2 = []

		if pselect == 'proportional':
			while parent2 == []:
				test = random.choice(population) # Choose a random specimen
				if random.random() > (float(whichShell(test))/math.fsum(range(len(dominationLayers)+2))): #If a number 0-1 is above fitness/total possible
					# select it
					if parent1 == []:
						parent1 = test
					else:
						parent2 = test
		elif pselect == 'random':
			while parent2 == []:
				randomchoice = random.choice(population)

				if parent1 == []:
					parent1 = randomchoice
				else:
					parent2 = randomchoice
		else: # k Tournament
			while parent2 == []:
				random.shuffle(population) # mix up the population list
				tourny = population[0:pTournSize-1] # take out a portion equal to k (or pTournSize)

				best = min(tourny, key=whichShell)

				if parent1 == []:
					parent1 = best
				else:
					parent2 = best

		# parents are selected, time to recombine
		child = []

		for num in range(nbvar):
			curparent = random.choice([parent1, parent2]) # RECOMBINE
			child.append(curparent[num])

		# MUTATE HERE
		for loci in range(nbvar):
			if random.random() < mutrate:
				if child[loci] == 0:
					child[loci] = random.choice([1,''])
				elif child[loci] == 1:
					child[loci] = random.choice([0,''])
				else:
					child[loci] = random.choice([1,0])

		offspring.append(child)

	if survivalstrat == 'plus':
		return population + offspring
	else: # Comma
		return offspring


### --- ELIMINATE --- ###
def eliminate(population):
	survivors = []

	global dominationLayers
	dominationLayers = putInDomLayers(population)

	if sselect == 'truncation':
		while len(survivors) < popsize:
			population = sorted(population, key=whichShell)
			survivors = population[:popsize]

	elif sselect == 'proportional':
		while len(survivors) < popsize:
			test = random.choice(population) # Choose a random specimen
			if random.random() > (float(whichShell(test))/math.fsum(range(len(dominationLayers)+2))): #If a number 0-1 is above fitness/total possible
				survivors.append(test)

	elif sselect == 'random':
		while len(survivors) < popsize:
			randomchoice = random.choice(population)
			survivors.append(randomchoice)

	else: # k Tournament
		while len(survivors) < popsize:
			random.shuffle(population) # mix up the population list
			tourny = population[:sTournSize-1] # take out a portion equal to k (or pTournSize)

			best = min(tourny, key=whichShell)

			population.remove(best)
			survivors.append(best)

	return survivors

### --- CONVERGED? --- ###
def converged(shellchange):
	converged = False

	if shellconverge and shellchange >= shellconvergen:
		converged = True

	return converged

### --- END OF EVALS? --- ###
def evalsreached(cureval):
	exit = False

	if evalterm and cureval >= numevals:
		exit = True

	return exit

### --- ELISTIST RESET --- ###
def elitistreset(population):
	pop = sorted(population, key=whichShell)
	pop = pop[:eliteR] # Clear except for R best individuals

	# Add new random individuals to population
	while len(pop) < popsize:
		varset = [] # Set of variables to complete a clause
		for var in range(nbvar):
			rando = random.choice([True, False,''])
			varset.append(rando)

		pop.append(varset)

	return pop

print("BEGINNING!")

##########################################
### --- --- The Actual Program --- --- ###
##########################################

paretofront = []
dominationLayers = []

for run in range(numruns):

	log.write("Run ")
	log.write(str(run + 1))
	log.write("\n")

	population = populate(popsize)

	### --- EACH EVALUATION! --- ###
	# loop control variables
	cureval = popsize # current number of evals
	
	curavgSAT = avgfitness_sat(population) #current average
	curavgUNSET = avgfitness_unset(population)
	
	curbestSAT = max(population, key=fitness_sat) # current best variable set
	curbestSATF = fitness_sat(curbestSAT) # current best fitness

	curbestUNSET = max(population, key=fitness_unset)
	curbestUNSETF = fitness_unset(curbestUNSET)

	dominationLayers = putInDomLayers(population)

	firstShell = sorted(dominationLayers[0][0])
	oldFirstShell = firstShell

	shellchange = 0 # Used to keep track of convergence crittirion

	# Update log file
	log.write(str(cureval))
	log.write("	")
	log.write(str(curavgSAT))
	log.write("	")
	log.write(str(curbestSATF))
	log.write("	")
	log.write(str(curavgUNSET))
	log.write("	")
	log.write(str(curbestUNSETF))
	log.write("\n")

	while evalsreached(cureval) == False:
		print(run),
		print(" - "),
		print(cureval)
		
		# Choose parents, make children, lump them all together
		population = selAndRecom(population)
		# KILL THE WEAK ONES until you've reach the desired pop size
		population = eliminate(population)
		dominationLayers = putInDomLayers(population)

		# Update the loop control variables
		cureval += offspringsize
		
		curavgSAT = avgfitness_sat(population)
		curavgUNSET = avgfitness_unset(population)

		curbestUNSET = max(population, key=fitness_unset)
		curbestUNSETF = fitness_unset(curbestUNSET)

		curbestSAT = max(population, key=fitness_sat)
		curbestSATF = fitness_sat(curbestSAT)

		oldFirstShell = firstShell
		firstShell = sorted(dominationLayers[0][0])
		if oldFirstShell == firstShell:
			shellchange += 1
		else:
			shellchange = 0

		# Update log file
		log.write(str(cureval))
		log.write("	")
		log.write(str(curavgSAT))
		log.write("	")
		log.write(str(curbestSATF))
		log.write("	")
		log.write(str(curavgUNSET))
		log.write("	")
		log.write(str(curbestUNSETF))
		log.write("\n")

		if converged(shellchange):
			if rrestart == False:
				break
			else:
				#R-Elitist Restart
				population = elitistreset(population)
				shellchange = 0
				cureval += popsize - eliteR #increase eval count based on amount of new individuals

	log.write("\n")

	# Store objective values of pareto curve
	fronts.write("Run ")
	fronts.write(str(run))
	for spec in firstShell:
		fronts.write('\n')
		fronts.write(str(fitness_sat(spec)))
		fronts.write(' ')
		fronts.write(str(fitness_unset(spec)))
	fronts.write("\n")

	# Is the curve better?
	P1 = 0
	P2 = 0

	print("Lengths: "),
	print(len(firstShell)),
	print(len(paretofront)),
	print(len(dominationLayers))

	for specimen in firstShell:
		for other in paretofront:
			spec_sat = fitness_sat(specimen)
			other_sat = fitness_sat(other)
			spec_unset = fitness_unset(specimen)
			other_unset = fitness_unset(other)
			if spec_sat >= other_sat and spec_unset >= other_unset:
				if spec_sat != other_sat or spec_unset  != other_unset:
					# specimen dominates one in best best
					P1 += 1
					break
	for other in paretofront:
		for specimen in firstShell:
			spec_sat = fitness_sat(specimen)
			other_sat = fitness_sat(other)
			spec_unset = fitness_unset(specimen)
			other_unset = fitness_unset(other)
			if other_sat >= spec_sat and other_unset >= spec_unset:
				if spec_sat != other_sat or spec_unset  != other_unset:
					# specimen dominates one in best best
					P2 += 1
					break

	# More dominators in this shell than in the current best
	print("P1: "),
	print(P1)
	print("P2: "),
	print(P2)
	if P1 > P2 or run == 0:
		paretofront = firstShell
		print("Swapped.")

sol.write("c ")
sol.write(cnfFilename)
sol.write("\nc Number of solutions in Pareto Front: ")
sol.write(str(len(paretofront)))

count = 0
for specimen in paretofront:
	count += 1

	sol.write("\nc Fitness of ")
	sol.write(str(count))
	sol.write(": ")
	sol.write(str(fitness_sat(specimen)))

	sol.write("\nc Robustness of ")
	sol.write(str(count))
	sol.write(": ")
	sol.write(str(fitness_unset(specimen)))

	sol.write("\nv")
	for i in range(len(specimen)):
		if specimen[i] == True:
			sol.write(' ')
			sol.write(str(i+1))
		elif specimen[i] == False:
			sol.write(' -')
			sol.write(str(i+1))
		
