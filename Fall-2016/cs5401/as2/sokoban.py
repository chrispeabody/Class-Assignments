# Chris Peabody cgpzbd@mst.edu
# Sokoban puzzle
# CS 5400, Artificial intelligence, F16
# Assignment 2 (MAIN FILE)

import sys
import id_dfts
import copy
from datetime import datetime

if __name__ == '__main__':
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
	firstNodeState = instance[1:]

	# Collect target locations for later use
	targetlocations = []
	rawmap = instance[2:]
	for y in range(len(rawmap)):
		for x in range(len(rawmap[y])):
			if rawmap[y][x] == 't':
				targetlocations.append((x,y))

	### --- SOLVE PUZZLE --- ###

	# Start the timer! (save the time)
	startTime = datetime.now()

	# Solve it!
	sol = id_dfts.ID_DFTS(firstNodeState, targetlocations)

	# Stop the timer!
	endTime = datetime.now()

	# Record it!
	with open(instFile.replace('.cfg', '_sol.txt').replace('inst','sol'), 'w') as s:
		if sol == None:
			s.write("There was no solution.")
		else:
			s.write('{}\n'.format((endTime - startTime).microseconds))
			s.write(str(len(sol[1].PATH)))
			s.write('\n')
			s.write(sol[0])
			s.write('\n')
			s.write('{} {}\n'.format(width, height))
			s.write('{} {}\n'.format(sol[1].PLAYERX, sol[1].PLAYERY))
			for line in sol[1].LAYOUT:
				s.write(line)
				s.write('\n')

	# TODO
	# DO ALL THE STUFF TO MAKE IS-DFTS INSTEAD OF BFTS