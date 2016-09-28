# Chris Peabody cgpzbd@mst.edu
# Sokoban puzzle
# CS 5400, Artificial intelligence, F16
# Assignment 2 (MAIN FILE)

import sys
import astargs
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

	# Collect information about map
	width, height = instance[0].split(' ')
	mapsize = (int(width), int(height))

	targetloc = []
	crateloc = []
	wallloc = []
	rawmap = instance[2:]
	for y in range(len(rawmap)):
		for x in range(len(rawmap[y])):
			if rawmap[y][x] == 't':
				targetloc.append((x,y))
			if rawmap[y][x] == 'c':
				crateloc.append((x,y))
			if rawmap[y][x] == 'w':
				wallloc.append((x,y))

	pX, pY = instance[1].split(' ')
	playerloc = (int(pX), int(pY))

	# pact it neatly into a state
	startState = {'player': playerloc,
				'crates': crateloc,
				'targets': targetloc,
				'walls': wallloc,
				'size':mapsize}

	#mapInfo = {'targets': targetloc,
	#			'walls': wallloc,
	#			'size':mapsize}

	### --- SOLVE PUZZLE --- ###

	# Start the timer! (save the time)
	startTime = datetime.now()

	# Solve it!
	sol = astargs.AStarGS(startState)

	# Stop the timer!
	endTime = datetime.now()

	# Record it!
	with open(instFile.replace('.cfg', '_sol.txt').replace('inst','sol'), 'w') as s:
		#if sol == None:
		#	s.write("There was no solution.")
		#else:
			s.write('{}\n'.format((endTime - startTime).microseconds))
			s.write(str(len(sol.PATH)))
			s.write('\n')
			s.write(sol.PATH)
			s.write('\n')
			s.write('{} {}\n'.format(width, height))
			s.write('{} {}\n'.format(sol.STATE['player'][0], sol.STATE['player'][1]))
			for y in range(int(height)):
				for x in range(int(width)):
					if (x, y) in sol.STATE['crates']:
						s.write('c')
					elif (x, y) in sol.STATE['walls']:
						s.write('w')
					else:
						s.write('.')
				s.write('\n')
