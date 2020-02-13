# search.py
# ---------------
# Licensing Information:  You are free to use or extend this projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to the University of Illinois at Urbana-Champaign
#
# Created by Jongdeog Lee (jlee700@illinois.edu) on 09/12/2018

"""
This file contains search functions.
"""
# Search should return the path and the number of states explored.
# The path should be a list of tuples in the form (alpha, beta, gamma) that correspond
# to the positions of the path taken by your search algorithm.
# Number of states explored should be a number.
# maze is a Maze object based on the maze from the file specified by input filename
# searchMethod is the search method specified by --method flag (bfs,astar)
# You may need to slight change your previous search functions in MP1 since this is 3-d maze

from collections import deque
from heapq import heappop, heappush

def search(maze, searchMethod):
    return {
        "bfs": bfs,
    }.get(searchMethod, [])(maze)

def bfs(maze):
    # Write your code here
    """
    This function returns optimal path in a list, which contains start and objective.
    If no path found, return None. 
    """
    start = maze.getStart() 
    frontier = [] 
    path = [] 
    dim = maze.getDimensions()
    objs = maze.getObjectives()
    rows = dim[0]
    cols = dim[1]
    granularity = maze.granularity
    offsets = maze.granularity
    visited = {} # visited as a dictionary
    for i in range (-180, 180, granularity):
        for j in range (-180, 180, granularity):
            visited[(i,j)] = (-1000, -1000)
    frontier.append(start)
    visited[(i,j)] = (-2000, -2000)
    while frontier:
        pt = frontier.pop(0)
        if maze.isObjective(pt[0], pt[1]) == True:
            break
        else:
            list_of_neighbors = maze.getNeighbors(pt[0], pt[1])
            for i in list_of_neighbors:
                if visited.get(i) == (-1000, -1000): 
                    frontier.append(i)
                    visited[i] = pt   
    while pt != start:
        path.append(pt)
        pt = visited.get(pt)
    path.append(start)
    path.reverse()
    return path

