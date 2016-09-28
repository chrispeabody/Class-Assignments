# Chris Peabody cgpzbd@mst.edu
# Sokoban puzzle
# CS 5400, Artificial intelligence, F16
# Assignment 2 (ID-DFTS FUNCTION)

import queue
import node

def ID_DFTS(state, targets):
	# Make the frontier and put the starting state in
	frontier = queue.LifoQueue()
	
	startX, startY = state[0].split(' ')
	startX, startY = int(startX), int(startY)
	root = node.Node(state[1:], startX, startY, '')
	L = 0; # Max depth

	while True:
		frontier.put(root)
		while True:
			if frontier.empty():
				break # None represents a failure
			
			curNode = frontier.get()
			if curNode.isGoal():
				return (curNode.PATH, curNode)
			
			for child in curNode.CHILDREN(L, targets):
				frontier.put(child)
		L += 1
