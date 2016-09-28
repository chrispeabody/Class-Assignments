# Chris Peabody cgpzbd@mst.edu
# Sokoban puzzle
# CS 5400, Artificial intelligence, F16
# Assignment 2 (A*GS FUNCTION)

import queue
import node

def AStarGS(state):
	# Make the frontier and put the starting state in
	frontier = queue.PriorityQueue()
	root = node.Node(state, '')
	frontier.put(root)

	# Technically is the explored
	# AND frontier sets of states
	explored = []

	while True:
		if frontier.empty():
			break # None represents a failure
		
		curNode = frontier.get()
		if curNode.isGoal():
			return curNode

		for child in curNode.CHILDREN():
			if child.STATE not in explored:
				frontier.put(child)
				explored.append(child.STATE)