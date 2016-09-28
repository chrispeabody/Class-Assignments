# Chris Peabody
# cgpzbd@mst.edu
# COMP SCI 5401 FS2015 Assignment 1c
# The STATALYZER! This program is a small tool to go along side the
# Sat solver. It can read in a front file, and output another file that
# can be analyzed in EXCEL. It can also give the diversity measures of both solutions

#############################################
### --- --- STATALYZE ME CAPTAIN! --- --- ###
#############################################

import sys

# Connect to the file or abort
if len(sys.argv) > 2:
	file1 = file(sys.argv[1], 'r')
	file2 = file(sys.argv[2], 'r')
	print("Connected to log files:"),
	print(sys.argv[1])
	print(sys.argv[2])
else:
	print("No log files specified! Aborting.")
	sys.exit(0)

# Connect to output file
sendto = 'sheets/SHEET' + (sys.argv[1].replace('fronts/','')).replace('.txt','') + 'AND' + sys.argv[2].replace('fronts/','')
send = file(sendto, 'w')

send.write("From log files: ")
send.write(sys.argv[1])
send.write(", ")
send.write(sys.argv[2])
send.write('\n')

# Create a list and cleanse it of it's extra stuff
one = list(file1)
for i in range(len(one)):
	one[i] = one[i].replace('\n','')

two = list(file2)
for i in range(len(two)):
	two[i] = two[i].replace('\n','')

# Set up 'individual' class
class individual:
	def __init__(self, sat_score, unset_score):
		self.objectives = {'sat': sat_score, 'unset': unset_score}

# define  diversity measure
def measure(front, objectives, mins, maxs):
    """
    Calculates the normalized hyper-volume between each point on a Pareto front and its neighbors
    Returns the percentage of the total normalized volume NOT taken up by these volumes
        A higher return value corresponds to a better distributed Pareto front
    front: non-empty list of class objects with an objectives dictionary member variable
    objectives: list of objective names (needs to match what's in the individual's objectives dictionary)
    mins: dictionary with objective names as keys and the minimum possible value for that objective as values
    maxs: dictionary with objective names as keys and the maximum possible value for that objective as values
    """
    # This will store the hyper-volume between neighboring individuals on the front; initialize all volumes to 1
    volumes = {individual: 1.0 for individual in front}
    # There is one more volume of interest than there is points on the front, so associate it with the max value
    volumes['max'] = 1.0
    for objective in objectives:
        # Sort the front by this objective's values
        sorted_front = sorted(front, key=lambda x: x.objectives[objective])
        # Calculate the volume between the first solution and minimum
        volumes[sorted_front[0]] *= float(sorted_front[0].objectives[objective]-mins[objective])/(maxs[objective]-mins[objective])
        # Calculate the volume between adjacent solutions on the front
        for i in range(1, len(sorted_front)):
            volumes[sorted_front[i]] *= float(sorted_front[i].objectives[objective]-sorted_front[i-1].objectives[objective])/(maxs[objective]-mins[objective])
        # Calculate the volume between the maximum and the last solution
        volumes['max'] *= float(maxs[objective]-sorted_front[-1].objectives[objective])/(maxs[objective]-mins[objective])
    # The normalized volume of the entire objective space is 1.0, subtract the volumes we calculated to turn this into maximization
    return 1.0 - sum(volumes.values())

## Set up basic structures
# To be filled with fronts
runs1 = []
runs2 = []

currun = 0
for line in one:
	if line.split(' ')[0] == 'Run':
		currun = line.split(' ')[1]
		runs1.append([])
	else:
		curindividual = individual(line.split(' ')[0], line.split(' ')[1])
		runs1[int(currun)].append(curindividual)

currun = 0
for line in two:
	if line.split(' ')[0] == 'Run':
		currun = line.split(' ')[1]
		runs2.append([])
	else:
		curindividual = individual(line.split(' ')[0], line.split(' ')[1])
		runs2[int(currun)].append(curindividual)

oneBeatsTwo = []
index = 0
# For each run in experiment 1
for front1 in runs1:
	# Compare to each run in experiment 2
	oneBeatsTwo.append(0)

	for front2 in runs2:
		count1 = 0
		count2 = 0

		for indiv1 in front1:
			for indiv2 in front2:
				if indiv1.objectives['sat'] >= indiv2.objectives['sat'] and indiv1.objectives['unset'] >= indiv2.objectives['unset']:
					if indiv1.objectives['sat'] != indiv2.objectives['sat'] or indiv1.objectives['unset'] != indiv2.objectives['unset']:
						count1 += 1
						break

		for indiv2 in front2:
			for indiv1 in front1:
				if indiv2.objectives['sat'] >= indiv1.objectives['sat'] and indiv2.objectives['unset'] >= indiv1.objectives['unset']:
					if indiv2.objectives['sat'] != indiv1.objectives['sat'] or indiv2.objectives['unset'] != indiv1.objectives['unset']:
						count2 += 1
						break

		# front1 beats front2
		if count1 > count2:
			oneBeatsTwo[index] += 1

	index += 1

twoBeatsOne = []
index = 0 
# For each run in experiment 1
for front2 in runs2:
	# Compare to each run in experiment 2
	twoBeatsOne.append(0)
	
	for front1 in runs1:
		count1 = 0
		count2 = 0

		for indiv1 in front1:
			for indiv2 in front2:
				if indiv1.objectives['sat'] >= indiv2.objectives['sat'] and indiv1.objectives['unset'] >= indiv2.objectives['unset']:
					if indiv1.objectives['sat'] != indiv2.objectives['sat'] or indiv1.objectives['unset'] != indiv2.objectives['unset']:
						count1 += 1
						break

		for indiv2 in front2:
			for indiv1 in front1:
				if indiv2.objectives['sat'] >= indiv1.objectives['sat'] and indiv2.objectives['unset'] >= indiv1.objectives['unset']:
					if indiv2.objectives['sat'] != indiv1.objectives['sat'] or indiv2.objectives['unset'] != indiv1.objectives['unset']:
						count2 += 1
						break

		# front1 beats front2
		if count2 > count1:
			twoBeatsOne[index] += 1

	index += 1

# Percentages1[0] says how many of experiment2's runs that experiment1 - run 0 beat
percentages1 = []
percentages2 = []

for x in range(len(oneBeatsTwo)):
	percentages1.append(100*(float(oneBeatsTwo[x])/float(30)))
for y in range(len(twoBeatsOne)):
	percentages2.append(100*(float(twoBeatsOne[y])/float(30)))

send.write("Exp. 1	Exp. 2")
for w in range(30):
	send.write('\n')
	send.write(str(percentages1[w]))
	send.write('	')
	send.write(str(percentages2[w]))

### --- Diversity portion --- ###

string1 = raw_input("Solution file 1: ")
string2 = raw_input("Solution file 2: ")
solution1 = file(string1, 'r')
solution2 = file(string2, 'r')

# Create a list and cleanse it of it's extra stuff
sol1 = list(solution1)
for i in range(len(sol1)):
	sol1[i] = sol1[i].replace('\n','')

sol2 = list(solution2)
for i in range(len(sol2)):
	sol2[i] = sol2[i].replace('\n','')

# Create front from solution file
front1 = []
curindi = 0 # Placeholder
for line in sol1:
	if line.split(' ')[1] == 'Fitness':
		curindi = individual(int(line.split(' ')[4]), 0)
	if line.split(' ')[1] == 'Robustness':
		curindi.objectives['unset'] = int(line.split(' ')[4])
		front1.append(curindi)

front2 = []
curindi = 0 # Placeholder
for line in sol2:
	if line.split(' ')[1] == 'Fitness':
		curindi = individual(int(line.split(' ')[4]), 0)
	if line.split(' ')[1] == 'Robustness':
		curindi.objectives['unset'] = int(line.split(' ')[4])
		front2.append(curindi)

mes1 = measure(front1, ['sat','unset'], {'sat': 0, 'unset': 0}, {'sat': 2130, 'unset': 500})
mes2 = measure(front2, ['sat','unset'], {'sat': 0, 'unset': 0}, {'sat': 2130, 'unset': 500})

send.write("\n\nDiversity")
send.write("\nExp. 1	")
send.write(str(mes1))
send.write("\nExp. 2	")
send.write(str(mes2))


