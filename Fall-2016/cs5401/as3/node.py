# Chris Peabody cgpzbd@mst.edu
# Sokoban puzzle
# CS 5400, Artificial intelligence, F16
# Assignment 2 (NODE CLASS)

import copy

# A dictionary to define how each direction affects a position
dirs = {'D': (0,1), 'R': (1,0), 'U': (0,-1), 'L': (-1,0)}

### --- NODE CLASS --- ###
class Node:
	def __init__(self, state, path):
		self.STATE = state # A dictionary with 'player', 'targets' 'crates', 'walls', 'size'
		self.PATH = path # A string of characters, of {LRUD} or '' for starting node
		self.H = self.heuristic()
		
	def __lt__(self, other):
		if self.H < other.H:
			return True
		return False

	# Give a heuristic rating of a node
	def heuristic(self):
		# My choice in heuristic is to minimize the distance from each
		# crate which are not on targets to the closest uncovered target

		# first remove any crates which are on targets
		# and any targets which are covered. They contribute
		# 0 to the value of the heuristic
		purgelist = []
		for crate in self.STATE['crates']:
			if crate in self.STATE['targets']:
				purgelist.append(crate)

		viablecrates = copy.deepcopy(self.STATE['crates'])
		viabletargets = copy.deepcopy(self.STATE['targets'])

		for loc in purgelist:
			viablecrates.remove(loc)
			viabletargets.remove(loc)

		# What is left is uncovered targets and not-covering-crates
		# For each crate, find the nearest target, add that dist to score
		# (Manhattan distance)
		score = 0
		for crate in viablecrates:
			minDist = self.STATE['size'][0] + self.STATE['size'][1] # arbitrarily large
			for target in viabletargets:
				tempdist = abs(crate[0]-target[0])+abs(crate[1]-target[1])
				if tempdist < minDist:
					minDist = tempdist
			score += minDist

		# We will also add the distance from the player to the nearest crate 
		# Which isn't on a target already
		# This will cause the player to drift toward crates
		if len(viablecrates) > 0:
			dist = self.STATE['size'][0] + self.STATE['size'][1] # Give an arbitrarily large start
		else:
			dist = 1
		for crate in viablecrates:
			tempdist = abs(crate[0]-self.STATE['player'][0])+abs(crate[1]-self.STATE['player'][1])
			if tempdist < dist:
				dist = tempdist
		score += dist -1

		# This will be admissible because it will never give a
		# number higher than what is required to finish the puzzle
		# The score will be 0 if all targets are covered.

		return score


	def isGoal(self):
		# Go through each target in state
		# If coordinates not in crates list, it's not a goal
		for target in self.STATE['targets']:
			if target not in self.STATE['crates']:
				return False
		# Otherwise all targets are covered
		return True

	# Checks if this is not a wall, and isn't outside the grid
	def validMove(self, direction):
		newX = self.STATE['player'][0] + dirs[direction][0]
		newY = self.STATE['player'][1] + dirs[direction][1]

		if newX < 0 or newY < 0:
			return False # Outside top or left
		if newX >= self.STATE['size'][0] or newY >= self.STATE['size'][1]:
			return False # Outside right or bottom
		if (newX, newY) in self.STATE['walls']:
			return False # Location is a wall

		# if the place is a crate, make sure behind it is clear
		if (newX, newY) in self.STATE['crates']:
			pushX = newX + dirs[direction][0]
			pushY = newY + dirs[direction][1]

			if pushX < 0 or pushY < 0:
				return False # Outside top or left
			if pushX >= self.STATE['size'][0] or pushY >= self.STATE['size'][1]:
				return False # Outside right or bottom
			if (pushX, pushY) in self.STATE['walls'] or (pushX, pushY) in self.STATE['crates']:
				return False # Location is a wall or another crate

		return True # Passes all the tests

	# returns list of children nodes
	def CHILDREN(self):
		childList = []

		# Loop through the four directions
		for direction in dirs:
			if self.validMove(direction):
				newloc = (self.STATE['player'][0]+dirs[direction][0], self.STATE['player'][1]+dirs[direction][1])

				newstate = copy.deepcopy(self.STATE)
				newstate['player'] = newloc

				if newloc in self.STATE['crates']:
					newstate['crates'].remove(newloc)
					newcrateloc = (newloc[0]+dirs[direction][0], newloc[1]+dirs[direction][1])
					newstate['crates'].append(newcrateloc)

				child = Node(newstate, ''.join([self.PATH, direction]))
				childList.append(child)

		return childList