# Chris Peabody
# cpgzbd@mst.edu
# COMP SCI 5401 FS2015 Assignment 1a

import random
import sys

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
	ranseed = random.randint(1000000000,9999999999)
	random.seed(str(ranseed))
else:
	random.seed(config[3])
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
	avgterm = True
else:
	avgterm = False
avgn = int(config[8].split(' ')[1])

if config[9].split(' ')[0] == 'True':
	bestterm = True
else:
	bestterm = False

bestn = int(config[9].split(' ')[1])
popsize = int(config[10])
offspringsize = int(config[11])

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

### --- FITNESS FUNCTION --- ###
def fitness(variables):
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

### --- AVERAGE FITNESS --- ###
def avgfitness(population):
	i = 0
	for specimen in population:
		i += fitness(specimen)

	avg = i/len(population)
	return avg

### --- POPULATE THE POPULATION BASED ON SIZE --- ###
def populate(size):
	pop = [] # A blank list of specimen

	for baby in range(size):
		varset = [] # Set of variables to complete a clause
		for var in range(nbvar):
			rando = random.choice([True, False])
			varset.append(rando)
		pop.append(varset)

	return pop

### --- PARENT SELECTIOIN AND RECOMBINATION --- ###
def selAndRecom(population):
	offspring = []

	for i in range(offspringsize):
		parent1 = []
		parent2 = []

		if pselect == 'proportional':
			while parent2 == []:
				test = random.choice(population) # Choose a random specimen
				if random.random() < (float(fitness(test))/float(nbclauses)): #If a number 0-1 is above fitness/total possible
					# select it
					if parent1 == []:
						parent1 = test
					else:
						parent2 = test
		else:
			while parent2 == []:
				random.shuffle(population) # mix up the population list
				tourny = population[0:pTournSize-1] # take out a portion equal to k (or pTournSize)

				best = max(tourny, key=fitness)

				if parent1 == []:
					parent1 = best
				else:
					parent2 = best

		# parents are selected, time to recombine
		child = []

		for num in range(nbvar):
			curparent = random.choice([parent1, parent2])
			child.append(curparent[num])

		offspring.append(child)

	return population + offspring

### --- ELIMINATE --- ###
def eliminate(population):
	survivors = []

	while len(survivors) < popsize:
		if sselect == 'truncation':
			population = sorted(population, key=fitness, reverse = True)
			survivors = population[:popsize]

		else: # k tournament
			random.shuffle(population) # mix up the population list
			tourny = population[:sTournSize-1] # take out a portion equal to k (or pTournSize)

			best = max(tourny, key=fitness)

			population.remove(best)
			survivors.append(best)

	return survivors

### --- TERMINATE --- ###
def terminate(cureval, sameavgcount, samebestcount):
	exit = False

	if evalterm and cureval >= numevals:
		exit = True

	if avgterm and sameavgcount >= avgn:
		exit = True

	if bestterm and samebestcount >= bestn:
		exit = True

	return exit



bestyet = []
bestyetF = 0
bestavg = 0

### --- EACH RUN! --- ###
for run in range(numruns):

	log.write("Run ")
	log.write(str(run + 1))
	log.write("\n")

	population = populate(popsize)

	### --- EACH EVALUATION! --- ###
	# loop control variables
	cureval = popsize # current number of evals
	
	curavg = avgfitness(population) #current average
	prevavg = curavg # average of previous eval
	sameavgcount = 0 #counts how many times the avg has stayed the same
	
	curbest = max(population, key=fitness) # current best variable set
	curbestF = fitness(curbest) # current best fitness
	prevbest = [] # previous best variable set
	prevbestF = 0
	samebestcount = 0 # counts how many times the best has stayed the same

	while terminate(cureval, sameavgcount, samebestcount) == False:
		print(run),
		print(" - "),
		print(cureval)
		# Choose parents, make children, lump them all together
		population = selAndRecom(population)
		# KILL THE WEAK ONES until you've reach the desired pop size
		population = eliminate(population)

		# Update the loop control variables
		cureval += offspringsize
		
		prevavg = curavg
		curavg = avgfitness(population)
		if prevavg == curavg:
			sameavgcount += 1
		else:
			sameavgcount = 0

		prevbest = curbest
		prevbestF = fitness(prevbest)
		curbest = max(population, key=fitness)
		curbestF = fitness(curbest)
		if prevbestF == curbestF:
			samebestcount += 1
		else:
			samebestcount = 0

		# Update log file
		log.write(str(cureval))
		log.write("	")
		log.write(str(curavg))
		log.write("	")
		log.write(str(curbestF))
		log.write("\n")

	log.write("\n")

	# Best for this run is better than best yet
	if curbestF > bestyetF:
		bestyet = curbest # Make this run's best the best yet
		bestyetF = curbestF
	# Average for this run is better than best average so far
	if curavg > bestavg:
		bestavg = curavg

sol.write("c ")
sol.write(cnfFilename)
sol.write("\nc Best-best fitness achieved: ")
sol.write(str(bestyetF))
sol.write("\nc Best-average fitness achieved: ")
sol.write(str(bestavg))
sol.write("\nv")
for i in range(len(bestyet)):
	if bestyet[i] == True:
		sol.write(' ')
	else:
		sol.write(' -')
	sol.write(str(i+1))
