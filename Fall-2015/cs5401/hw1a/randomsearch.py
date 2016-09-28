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
if config[1] == 'random':
	random.seed()
else:
	random.seed(config[1])
numruns = int(config[2])
numevals = int(config[3])
logfile = str(config[4])
solutionfile = str(config[5])

# Connect log and solution files
log = file(logfile,'w')
log.write('Result Log\n')
sol = file(solutionfile,'w')

### --- FITNESS FUNCTION --- ###
def fitness(clauses, variables):
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

bestever = 0 # Meant to keep track of the best solution over all runs AKA solution
besteversol = []
bestreachedat = 0
for run in range(numruns):
	bestyet = 0
	bestsol = []

	log.write("Run ")
	log.write(str(run + 1))
	log.write("\n")
	for evalu in range(numevals):
		# Randomize values for variables
		varvals = [] #Index 0 holds the boolean value for variable 1, etc
		for i in range(nbvar):
			varvals.append(random.choice([True, False]))
		howfit = fitness(clauses, varvals)
		# Update log file and best eval if this eval is better
		if howfit > bestyet:
			bestyet = howfit
			bestsol = varvals
			log.write(str(evalu+1))
			log.write('	')
			log.write(str(howfit))
			log.write('\n')

	# Update solution if max in this run is max overall
	if bestyet > bestever:
		bestever = bestyet
		besteversol = bestsol
		bestreachedat = run + 1
# Write the solution to the file
sol.write("c Solution for: ")
sol.write(str(cfgfile))
sol.write("\nc MAXSAT fitness value: ")
sol.write(str(bestever))
sol.write("\nc On run ")
sol.write(str(bestreachedat))
sol.write("\nv")
for i in range(len(besteversol)):
	if besteversol[i] == True:
		sol.write(' ')
		sol.write(str(i+1))
	else:
		sol.write(' -')
		sol.write(str(i+1))
	