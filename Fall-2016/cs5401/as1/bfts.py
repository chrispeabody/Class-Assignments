# Chris Peabody cgpzbd@mst.edu
# Sokoban puzzle
# CS 5400, Artificial intelligence, F16
# Assignment 1 (BFTS FUNCTION)

import queue
import node

def isGoal(state):
	# Go through each line in state
	# If no 't' targets found, it's a goal
	for line in state:
		if 't' in line:
			return False
	return True

def BFTS(state):
	# Make the frontier and put the starting state in
	frontier = queue.Queue()
	root = node.Node(state, None, None, 0)
	frontier.put(root)

	while True:
		if frontier.empty():
			return None # None represents a failure
		
		curNode = frontier.get()
		if isGoal(curNode.STATE):
			# Collect and return path
			sequence = []
			curTracing = curNode

			while curTracing.PARENT != None:
				sequence.append(curTracing.ACTION)
				curTracing = curTracing.PARENT

			sequence.reverse()

			return (sequence, curNode)
		
		for child in curNode.CHILDREN():
			frontier.put(child)