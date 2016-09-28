# Chris Peabody cgpzbd@mst.edu
# Sokoban puzzle
# CS 5400, Artificial intelligence, F16
# Assignment 1 (NODE CLASS)

### --- VALID MOVE/PUSH --- ###

# Checks if this is not a wall, and isn't outside the grid
def validMove(y, x, layout):
	if x < 0 or y < 0:
		return False # Outside top or left
	if y >= len(layout) or x >= len(layout[0]):
		return False # Outside right or bottom
	if layout[y][x] == 'w':
		return False # Location is a wall
	return True # Passes all the tests

# Check if pushing a block in a direction is okay
def validPush(y, x, layout, direction):
	# This is always set to true if we aren't actually pushing anything
	if layout[y][x] != 'c':
		return True

	# Choose WHERE the crate would be pushed
	if direction == 'L':
		x -= 1
	if direction == 'R':
		x += 1
	if direction == 'U':
		y -= 1
	if direction == 'D':
		y += 1

	# If it's an open space, return true
	return validMove(y, x, layout) and layout[y][x] != 'c'

### --- NODE CLASS --- ###
class Node:
	def __init__(self, state, parent, action, pcost):
		self.STATE = state # Same format as puzzle.cfg file, without first line
		self.PARENT = parent # A node instance, or None for starting node
		self.ACTION = action # A character, one of {LRUD} or None for starting node
		self.PCOST = pcost # Total path cost to here, int

	# returns list of children nodes
	def CHILDREN(self):
		childList = []

		curX, curY = self.STATE[0].split(' ')
		curX, curY = int(curX), int(curY)
		curLayout = self.STATE
		del curLayout[0]

		# If left is open, or a pushable crate
		if validMove(curY, curX-1, curLayout) and validPush(curY, curX-1, curLayout, 'L'):
			# Generate the state for the child
			childState = []
			childState.append("{} {}".format(curX-1, curY))
			if curLayout[curY][curX-1] != 'c':
				# Not pushing? Just append as is
				for line in curLayout:
					childState.append(line)
			else:
				# Pushing? Move the crate
				newLayout = curLayout

				temp = list(newLayout[curY])
				temp[curX-1] = '.'
				temp[curX-2] = 'c'
				newLayout[curY] = ''.join(temp)

				for line in newLayout:
					childState.append(line)

			child = Node(childState, self, 'L', self.PCOST+1)
			childList.append(child)

		# If right is open, or a pushable crate
		if validMove(curY, curX+1, curLayout) and validPush(curY, curX+1, curLayout, 'R'):
			# Generate the state for the child
			childState = []
			childState.append("{} {}".format(curX+1, curY))
			if curLayout[curY][curX+1] != 'c':
				# Not pushing? Just append as is
				for line in curLayout:
					childState.append(line)
			else:
				# Pushing? Move the crate
				newLayout = curLayout
				temp = list(newLayout[curY])
				temp[curX+1] = '.'
				temp[curX+2] = 'c'
				newLayout[curY] = ''.join(temp)

				for line in newLayout:
					childState.append(line)

			child = Node(childState, self, 'R', self.PCOST+1)
			childList.append(child)

		# If up is open, or a pushable crate
		if validMove(curY-1, curX, curLayout) and validPush(curY-1, curX, curLayout, 'U'):
			# Generate the state for the child
			childState = []
			childState.append("{} {}".format(curX, curY-1))
			if curLayout[curY-1][curX] != 'c':
				# Not pushing? Just append as is
				for line in curLayout:
					childState.append(line)
			else:
				# Pushing? Move the crate
				newLayout = curLayout

				temp = list(newLayout[curY-1])
				temp[curX] = '.'
				newLayout[curY-1] = ''.join(temp)

				temp = list(newLayout[curY-2])
				temp[curX] = 'c'
				newLayout[curY-2] = ''.join(temp)

				for line in newLayout:
					childState.append(line)

			child = Node(childState, self, 'U', self.PCOST+1)
			childList.append(child)

		# If down is open, or a pushable crate
		if validMove(curY+1, curX, curLayout) and validPush(curY+1, curX, curLayout, 'D'):
			# Generate the state for the child
			childState = []
			childState.append("{} {}".format(curX, curY+1))
			if curLayout[curY+1][curX] != 'c':
				# Not pushing? Just append as is
				for line in curLayout:
					childState.append(line)
			else:
				# Pushing? Move the crate
				newLayout = curLayout
				
				temp = list(newLayout[curY+1])
				temp[curX] = '.'
				newLayout[curY+1] = ''.join(temp)

				temp = list(newLayout[curY+2])
				temp[curX] = 'c'
				newLayout[curY+2] = ''.join(temp)

				for line in newLayout:
					childState.append(line)

			child = Node(childState, self, 'D', self.PCOST+1)
			childList.append(child)

		return childList