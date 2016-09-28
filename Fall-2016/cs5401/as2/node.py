# Chris Peabody cgpzbd@mst.edu
# Sokoban puzzle
# CS 5400, Artificial intelligence, F16
# Assignment 2 (NODE CLASS)

import copy

# 0 - Down
# 1 - Right
# 2 - Up
# 3 - Left
dirs = [(0,1), (1,0), (0,-1), (-1,0)]
letter = ['D', 'R', 'U', 'L']

### --- NODE CLASS --- ###
class Node:
	def __init__(self, layout, x, y, path):
		self.PLAYERX, self.PLAYERY = x, y # Location of warehouse manager
		self.LAYOUT = layout # Same format as puzzle.cfg file, without first line
		self.PATH = path # A string of characters, of {LRUD} or '' for starting node

	def isGoal(self):
		# Go through each line in state
		# If no 't' targets found, it's a goal
		for line in self.LAYOUT:
			if 't' in line:
				return False
		return True

	# Checks if this is not a wall, and isn't outside the grid
	def validMove(self, direction):
		newX = self.PLAYERX + dirs[direction][0]
		newY = self.PLAYERY + dirs[direction][1]

		if newX < 0 or newY < 0:
			return False # Outside top or left
		if newY >= len(self.LAYOUT) or newX >= len(self.LAYOUT[0]):
			return False # Outside right or bottom
		if self.LAYOUT[newY][newX] == 'w':
			return False # Location is a wall

		# if the place is a crate, make sure behind it is clear
		if self.LAYOUT[newY][newX] == 'c':
			pushX = newX + dirs[direction][0]
			pushY = newY + dirs[direction][1]

			if pushX < 0 or pushY < 0:
				return False # Outside top or left
			if pushY >= len(self.LAYOUT) or pushX >= len(self.LAYOUT[0]):
				return False # Outside right or bottom
			if self.LAYOUT[pushY][pushX] == 'w' or self.LAYOUT[pushY][pushX] == 'c':
				return False # Location is a wall or another crate

		return True # Passes all the tests

	# returns list of children nodes
	def CHILDREN(self, L, targets):
		if len(self.PATH) >= L:
			return []

		childList = []

		# Loop through the four directions
		for direction in range(4):
			if self.validMove(direction):
				newLayout = copy.copy(self.LAYOUT)
				if self.LAYOUT[self.PLAYERY+dirs[direction][1]][self.PLAYERX+dirs[direction][0]] == 'c':
					if (self.PLAYERX+dirs[direction][0], self.PLAYERY+dirs[direction][1]) in targets:
						# Put a 't' there if necessary
						newLine = list(newLayout[self.PLAYERY+dirs[direction][1]])
						newLine[self.PLAYERX+dirs[direction][0]] = 't'
						newLayout[self.PLAYERY+dirs[direction][1]] = ''.join(newLine)
					else:
						# Put a '.' there if necessary
						newLine = list(newLayout[self.PLAYERY+dirs[direction][1]])
						newLine[self.PLAYERX+dirs[direction][0]] = '.'
						newLayout[self.PLAYERY+dirs[direction][1]] = ''.join(newLine)

					# Place the crate in the new location
					newLine = list(newLayout[self.PLAYERY+2*dirs[direction][1]])
					newLine[self.PLAYERX+2*dirs[direction][0]] = 'c'
					newLayout[self.PLAYERY+2*dirs[direction][1]] = ''.join(newLine)

				child = Node(newLayout, self.PLAYERX+dirs[direction][0],
							self.PLAYERY+dirs[direction][1], ''.join([self.PATH, letter[direction]]))
				childList.append(child)

		return childList