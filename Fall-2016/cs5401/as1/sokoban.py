# Chris Peabody cgpzbd@mst.edu
# Sokoban puzzle
# CS 5400, Artificial intelligence, F16
# Assignment 1 (MAIN FILE)

import sys
import bfts
from datetime import datetime

### --- CONFIGURATION --- ###

# Make sure a file was specified
if len(sys.argv) > 1:
	instFile = sys.argv[1]
else:
	instFile = input("Please type the puzzle instance file name: ")

# Open the puzzle instance file, and create a list based on it's lines
connected = False
while not connected:
	try:
		with open(instFile) as f:
			instance = list(f)
			connected = True
	except Exception as e: 
		print("{}. Try again.".format(e))
		instFile = input("Please type the puzzle instance file name: ")

# Trim lines of their extra bits
for line in range(len(instance)):
	instance[line] = instance[line].replace('\n','')

# Set the height and width based on puzzle file
width, height = instance[0].split(' ')

## ADD A SECTION TO MAKE SURE SIZE, NUM CRATES, ETC IS CORRECT ##

# Create the first start state node
firstNodeState = instance
del firstNodeState[0]

# Collect target locations for later use
# So you can restore them when crates move

### --- SOLVE PUZZLE --- ###

# Start the timer! (save the time)
startTime = datetime.now()

# Solve it!
sol = bfts.BFTS(firstNodeState)

# Stop the timer!
endTime = datetime.now()

# Record it!
with open(instFile.replace('.cfg', '_sol.txt').replace('inst','sol'), 'w') as s:
	s.write('{}\n'.format((endTime - startTime).microseconds))
	s.write(str(sol[1].PCOST))
	s.write('\n')
	s.write(''.join(sol[0]))
	s.write('\n')
	s.write('{} {}\n'.format(width, height))
	for line in sol[1].STATE:
		s.write(line)
		s.write('\n')

print("Microsec: ???")
print(sol[1].PCOST)
print(''.join(sol[0]))
for line in sol[1].STATE:
	print(line)
