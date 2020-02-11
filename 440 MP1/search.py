import queue
import bisect
import copy
import math
import time
# search.py
# ---------------
# Licensing Information:  You are free to use or extend this projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to the University of Illinois at Urbana-Champaign
#
# Created by Michael Abir (abir2@illinois.edu) on 08/28/2018

"""
This is the main entry point for MP1. You should only modify code
within this file -- the unrevised staff files will be used for all other
files and classes when code is run, so be careful to not modify anything else.
"""
# Search should return the path.
# The path should be a list of tuples in the form (row, col) that correspond
# to the positions of the path taken by your search algorithm.
# maze is a Maze object based on the maze from the file specified by input filename
# searchMethod is the search method specified by --method flag (bfs,dfs,astar,astar_multi,extra)

class state:
    def __init__(self, position, cnr_list = None):
        self.cnr_list = cnr_list
        self.position = position
    def getlist(self):
        return self.cnr_list
    def getpos(self):
        return self.position
    def __eq__(self, other):
        if (self.position == other.position) and (self.cnr_list == other.cnr_list):
            return True
        else:
            return False
    def __ne__(self, other):
        return (self.position is not other.position) or (self.cnr_list is not other.cnr_list)
    def __hash__(self):
        hash_value = hash(self.position)
        hash_value = hash(tuple(self.cnr_list))
        return hash_value
    def __lt__(self, other):
        return other
    
        
class disjointSet:
    def __init__(self):
        self.dictionary = {}
        self.size = 0
    def addelements(self, objs):
        self.size = len(objs)
        for i in objs:
            self.dictionary[i] = (-1, -1)
        return
    # find -- find the root of the path by a given point.
    def find(self, pt):
        if self.dictionary.get(pt)[0] < 0:
            return pt
        else:
            root = self.find(self.dictionary.get(pt))
            self.dictionary[pt] = root
            return root
        return (-1, -1)
    def setunion(self, pt_a, pt_b):
        if self.find(pt_a) == self.find(pt_b):
            return
        size1 = self.dictionary.get(self.find(pt_a))
        size2 = self.dictionary.get(self.find(pt_b))
        new_size = (size1[0] + size2[0], size1[1] + size2[1])
        # if a is larger (ie more negative), then we let pt_b join the larger set.
        if self.dictionary.get(self.find(pt_a))[0] < self.dictionary.get(self.find(pt_b))[0]:
            self.dictionary[self.find(pt_a)] = new_size
            self.dictionary[self.find(pt_b)] = self.find(pt_a)
            # print("More negative!!!")
        else:
            self.dictionary[self.find(pt_a)] = self.find(pt_b)
            self.dictionary[self.find(pt_b)] = new_size
            # print("More positive!!!")
        return
    
    def size(self, elem):
        idx = self.find(elem)
        current_size = self.dictionary.get(idx)[0] * -1
        return current_size
    
    def length(self, elem):
        return self.size

def search(maze, searchMethod):
    return {
        "bfs": bfs,
        "astar": astar,
        "astar_corner": astar_corner,
        "astar_multi": astar_multi,
        "extra": extra,
    }.get(searchMethod)(maze)

# provided API functions:
# getStart() -- Returns a tuple of the starting position. 
# getObjective() -- Returns a list of tuples that correspond to the dot positions. 
# isValidMove(row, col) -- Returns the boolean True if the (row, col) position is valid. 
#                          returns False otherwise.
# getNeighbors(row, col) -- Given a position, returns the list of tuples that correspond to valid
# neighbor positions. Will return at most 4 neighbors, but may return less. 


def bfs(maze):
    """
    Runs BFS for part 1 of the assignment.

    @param maze: The maze to execute the search on.

    @return path: a list of tuples containing the coordinates of each state in the computed path
    """
    # TODO: Write your code here.
    start = maze.getStart() 
    frontier = [] 
    path = [] 
    dim = maze.getDimensions()
    objs = maze.getObjectives()
    rows = dim[0]
    cols = dim[1]
    visited = {} # visited as a dictionary
    for i in range (0, rows):
        for j in range (0, cols):
            visited[(i,j)] = (-1, -1)
    frontier.append(start)
    visited[(i,j)] = (-2, -2)
    while frontier:
        pt = frontier.pop(0)
        if maze.isObjective(pt[0], pt[1]) == True:
            break
        else:
            list_of_neighbors = maze.getNeighbors(pt[0], pt[1])
            for i in list_of_neighbors:
                if visited.get(i) == (-1, -1): 
                    frontier.append(i)
                    visited[i] = pt   
    while pt != start:
        path.append(pt)
        pt = visited.get(pt)
    path.append(start)
    path.reverse()
    return path

def astar(maze):
    """
    Runs A star for part 1 of the assignment.

    @param maze: The maze to execute the search on.

    @return path: a list of tuples containing the coordinates of each state in the computed path
    """
    # TODO: Write your code here
    start = maze.getStart()
    # p_queue = Queue.PriorityQueue()
    p_queue = []
    dim = maze.getDimensions()
    rows = dim[0]
    cols = dim[1]
    # backtrace.
    visited = {} 
    lookup_table = {}
    for i in range (0, rows):
        for j in range (0, cols):
            visited[(i,j)] = (-1, -1)
            # heuristic, cost, prev
            lookup_table[(i, j)] = (-1, -1, (-1, -1))
    end = maze.getObjectives()[0]
    path = []
    # add startpoint to the queue.
    start_heuristic = 0 + abs(start[0] - end[0]) + abs(start[1] - end[1])
    # format: heuristic, current point so we can better sort. 
    p_queue.append((start_heuristic, start))
    lookup_table[start] = (start_heuristic, 0, (-2, -2))
    while p_queue:
        pair = p_queue.pop(0)
        visited[pair[1]] = lookup_table.get(pair[1])[2]
        if pair[1] == end:
            break
        else:
            list_of_neighbors = maze.getNeighbors(pair[1][0], pair[1][1])
            for i in list_of_neighbors:
                # if i is part of path, skip i.
                if visited.get(i) != (-1, -1):
                    cost = lookup_table.get(pair[1])[1] + 1
                    heuristic = cost + abs(i[0] - end[0]) + abs(i[1] - end[1])
                    old_heuristic = lookup_table[i][0]
                    if cost < lookup_table.get(i)[1]:
                        lookup_table[i] = (heuristic, cost, pair[1])
                        #remove node from explored set and move it to frontier.
                        visited[i] = (-1,-1)
                        bisect.insort(p_queue, (heuristic, i))
                    else:
                        continue
                # if i is in the queue, we may check whether the new path is better.
                if (lookup_table.get(i)[0], i) in p_queue:
                     cost = lookup_table.get(pair[1])[1] + 1
                     heuristic = cost + abs(i[0] - end[0]) + abs(i[1] - end[1])
                     old_heuristic = lookup_table[i][0]
                     if cost < lookup_table.get(i)[1]:
                         lookup_table[i] = (heuristic, cost, pair[1])
                         # remove item by value and insert it again to the p_queue. 
                         p_queue.remove((old_heuristic, i))
                         bisect.insort(p_queue, (heuristic, i))
                # if the point is not in the open_list, then we can add it to the open_list and the look_up table.
                else:
                    cost = lookup_table.get(pair[1])[1] + 1
                    heuristic = cost + abs(i[0] - end[0]) + abs(i[1] - end[1])
                    lookup_table[i] = (heuristic, cost, pair[1])
                    bisect.insort(p_queue, (heuristic, i))
            # We are done!!!
    pt = end
    while pt != start:
        path.append(pt)
        pt = visited.get(pt)
    path.append(start)
    path.reverse()
    return path


def astar_corner(maze):
    """
    Runs A star for part 2 of the assignment in the case where there are four corner objectives.
        
    @param maze: The maze to execute the search on.
        
    @return path: a list of tuples containing the coordinates of each state in the computed path
        """
    return astar_multi(maze)
    

def astar_set(maze, startpoint, endpoint):
    start = startpoint
    # p_queue = Queue.PriorityQueue()
    p_queue = []
    dim = maze.getDimensions()
    rows = dim[0]
    cols = dim[1]
    # backtrace.
    visited = {} 
    lookup_table = {}
    for i in range (0, rows):
        for j in range (0, cols):
            visited[(i,j)] = (-1, -1)
            # heuristic, cost, prev
            lookup_table[(i, j)] = (-1, -1, (-1, -1))
    end = endpoint
    path = []
    # add startpoint to the queue.
    start_heuristic = 0 + abs(start[0] - end[0]) + abs(start[1] - end[1])
    # format: heuristic, current point so we can better sort. 
    p_queue.append((start_heuristic, start))
    lookup_table[start] = (start_heuristic, 0, (-2, -2))
    while p_queue:
        pair = p_queue.pop(0)
        visited[pair[1]] = lookup_table.get(pair[1])[2]
        if pair[1] == end:
            break
        else:
            list_of_neighbors = maze.getNeighbors(pair[1][0], pair[1][1])
            for i in list_of_neighbors:
                # if i is part of path, skip i.
                if visited.get(i) != (-1, -1):
                    cost = lookup_table.get(pair[1])[1] + 1
                    heuristic = cost + abs(i[0] - end[0]) + abs(i[1] - end[1])
                    old_heuristic = lookup_table[i][0]
                    if heuristic < lookup_table.get(i)[0]:
                        lookup_table[i] = (heuristic, cost, pair[1])
                        #remove node from explored set and move it to frontier.
                        visited[i] = (-1,-1)
                        bisect.insort(p_queue, (heuristic, i))
                    else:
                        continue
                # if i is in the queue, we may check whether the new path is better.
                if (lookup_table.get(i)[0], i) in p_queue:
                     cost = lookup_table.get(pair[1])[1] + 1
                     heuristic = cost + abs(i[0] - end[0]) + abs(i[1] - end[1])
                     old_heuristic = lookup_table[i][0]
                     if heuristic < lookup_table.get(i)[0]:
                         lookup_table[i] = (heuristic, cost, pair[1])
                         # remove item by value and insert it again to the p_queue. 
                         p_queue.remove((old_heuristic, i))
                         bisect.insort(p_queue, (heuristic, i))
                # if the point is not in the open_list, then we can add it to the open_list and the look_up table.
                else:
                    cost = lookup_table.get(pair[1])[1] + 1
                    heuristic = cost + abs(i[0] - end[0]) + abs(i[1] - end[1])
                    lookup_table[i] = (heuristic, cost, pair[1])
                    bisect.insort(p_queue, (heuristic, i))
            # We are done!!!
    pt = end
    while pt != start:
        path.append(pt)
        pt = visited.get(pt)
    path.append(start)
    path.reverse()
    return path

def edge_set(maze, objects, someset, dictionary):
    """
    only for part 3 tree construction.
    """
    # TODO: Write your code here
    #objs = maze.getObjectives()
    objs = objects
    objs_cached = copy.copy(objs)
    edge_set = someset
    # shortest_path_by_edge = dictionary
    length = len(objs)
    for i in range(0, length):
        for j in range(i+1, length):
            path = astar_set(maze, objs[i], objs[j])
            bisect.insort(edge_set, (len(path) - 1, (objs[i], objs[j])))
            # shortest_path_by_edge[(objs[i], objs[j])] = path
    return 

def minimum_spanning_tree(maze, objs, dictionary, edgeset_cached):
    dset = disjointSet()
    dset.addelements(objs)
    shortest_path_by_edge = {}
    if not edgeset_cached:
        edge_set(maze, objs, edgeset_cached, shortest_path_by_edge)
        edgeset = copy.copy(edgeset_cached)
    else: 
        edgeset = copy.copy(edgeset_cached)
    edges = 0
    MST = 0
    # MST initialization.
    dim = maze.getDimensions()
    while edges < (len(objs) - 1):
        removed_edge = edgeset.pop(0)
        start_pt = removed_edge[1][0]
        end_pt = removed_edge[1][1]
        if start_pt not in objs or end_pt not in objs:
            continue
        if dset.find(start_pt) != dset.find(end_pt):
            dset.setunion(dset.find(start_pt), dset.find(end_pt))
            edges = edges + 1
            MST += removed_edge[0]
    return MST

def multi_dot_heuristic_query(maze, pt, objs, edge_set, min_tree):
    # it's fine to keep it, speed-wise. But it is not really necessary...
    shortest_path_by_edge = {}

    if tuple(objs) in min_tree:
        MST = min_tree.get(tuple(objs))
        
    else:
        MST = minimum_spanning_tree(maze, objs, shortest_path_by_edge, edge_set)
        min_tree[tuple(objs)] = MST

    final_heuristic = 0
    # find the closest objective from the queried coordinates. 
    if not objs:
        return 0
    pivot = objs[0]
    manhattan_dis = abs(pivot[0] - pt[0]) + abs(pivot[1] - pt[1])
    for i in objs:
        if manhattan_dis > (abs(i[0] - pt[0]) + abs(i[1] - pt[1])):
            manhattan_dis = (abs(i[0] - pt[0]) + abs(i[1] - pt[1]))
            pivot = i
    
    final_heuristic += manhattan_dis + MST 
    return final_heuristic 


def astar_multi(maze):
    """
    Runs A star for part 3 of the assignment in the case where there are
    multiple objectives.

    @param maze: The maze to execute the search on.

    @return path: a list of tuples containing the coordinates of each state in the computed path
    """
    heuristic_lookup = {} 
    objs = maze.getObjectives()
    corner_list = maze.getObjectives()
    start = maze.getStart()
    path = []
    dim = maze.getDimensions()
    visited = {}
    lookup_table = {}
    p_queue = []
    edgeset = []
    mintree = {}
    start_heuristic = 0 + multi_dot_heuristic_query(maze, start, objs, edgeset, mintree) 
    heuristic_lookup[(start, tuple(objs))] = start_heuristic
    start_state = state(start, corner_list)
    lookup_table[state(start, corner_list)] = (start_heuristic, 0, state((-2, -2)))
    p_queue.append((start_heuristic, state(start, corner_list)))
    while p_queue:
        pair = p_queue.pop(0)
        visited[pair[1]] = lookup_table.get(pair[1])[2]
        if not pair[1].getlist():
            current_state = pair[1]
            while current_state != start_state:
                path.append(current_state.getpos())
                current_state = visited.get(current_state)
            path.append(start)
            path.reverse()
            return path
        else: 
            list_of_neighbors = maze.getNeighbors(pair[1].getpos()[0], pair[1].getpos()[1])
            for coordinates in list_of_neighbors:
                current_state = state(coordinates)
                if coordinates in pair[1].getlist():
                    new_list = copy.copy(pair[1].getlist())
                    new_list.remove(coordinates)
                    current_state = state(coordinates, new_list)
                else:
                    current_state = state(coordinates, pair[1].getlist())   
                if current_state in visited:
                    continue
                if current_state in lookup_table:
                    if (lookup_table.get(current_state)[0], current_state) in p_queue:
                        cost = lookup_table.get(pair[1])[1] + 1
                        queried_heuristic = 0
                        if (current_state.getpos(), tuple(current_state.getlist())) in heuristic_lookup:
                            queried_heuristic = heuristic_lookup.get((current_state.getpos(), tuple(current_state.getlist())))
                        else:
                            queried_heuristic = multi_dot_heuristic_query(maze, current_state.getpos(), current_state.getlist(), edgeset, mintree)
                            heuristic_lookup[(current_state.getpos(), tuple(current_state.getlist()))] = queried_heuristic
                        heuristic = queried_heuristic + cost
                        old_heuristic = lookup_table.get(current_state)[0]
                        if heuristic < lookup_table.get(current_state)[0]:
                            lookup_table[current_state] = (heuristic, cost, pair[1])
                            p_queue.remove((old_heuristic, current_state))
                            bisect.insort(p_queue, (heuristic, current_state))
                else:
                    cost = lookup_table.get(pair[1])[1] + 1
                    queried_heuristic = 0
                    if (current_state.getpos(), tuple(current_state.getlist())) in heuristic_lookup:
                        queried_heuristic = heuristic_lookup.get((current_state.getpos(), tuple(current_state.getlist())))
                    else:
                        queried_heuristic = multi_dot_heuristic_query(maze, current_state.getpos(), current_state.getlist(), edgeset, mintree) 
                        heuristic_lookup[(current_state.getpos(), tuple(current_state.getlist()))] = queried_heuristic
                    heuristic = queried_heuristic + cost
                    lookup_table[current_state] = (heuristic, cost, pair[1])
                    bisect.insort(p_queue, (heuristic, current_state))
    return []      
    


def extra(maze):
    """
    Runs extra credit suggestion.

    @param maze: The maze to execute the search on.

    @return path: a list of tuples containing the coordinates of each state in the computed path
    """
    # TODO: Write your code here
    heuristic_lookup = {} 
    objs = maze.getObjectives()
    corner_list = maze.getObjectives()
    start = maze.getStart()
    path = []
    dim = maze.getDimensions()
    visited = {}
    lookup_table = {}
    p_queue = []
    edgeset = []
    mintree = {}
    start_heuristic = 0 + multi_dot_heuristic_query(maze, start, objs, edgeset, mintree) * 2
    heuristic_lookup[(start, tuple(objs))] = start_heuristic
    start_state = state(start, corner_list)
    lookup_table[state(start, corner_list)] = (start_heuristic, 0, state((-2, -2)))
    p_queue.append((start_heuristic, state(start, corner_list)))
    while p_queue:
        pair = p_queue.pop(0)
        visited[pair[1]] = lookup_table.get(pair[1])[2]
        if not pair[1].getlist():
            current_state = pair[1]
            while current_state != start_state:
                path.append(current_state.getpos())
                current_state = visited.get(current_state)
            path.append(start)
            path.reverse()
            return path
        else: 
            list_of_neighbors = maze.getNeighbors(pair[1].getpos()[0], pair[1].getpos()[1])
            for coordinates in list_of_neighbors:
                current_state = state(coordinates)
                if coordinates in pair[1].getlist():
                    new_list = copy.copy(pair[1].getlist())
                    new_list.remove(coordinates)
                    current_state = state(coordinates, new_list)
                else:
                    current_state = state(coordinates, pair[1].getlist())   
                if current_state in visited:
                    continue
                if current_state in lookup_table:
                    if (lookup_table.get(current_state)[0], current_state) in p_queue:
                        cost = lookup_table.get(pair[1])[1] + 1
                        queried_heuristic = 0
                        if (current_state.getpos(), tuple(current_state.getlist())) in heuristic_lookup:
                            queried_heuristic = heuristic_lookup.get((current_state.getpos(), tuple(current_state.getlist())))
                        else:
                            queried_heuristic = multi_dot_heuristic_query(maze, current_state.getpos(), current_state.getlist(), edgeset, mintree) * 2
                            heuristic_lookup[(current_state.getpos(), tuple(current_state.getlist()))] = queried_heuristic
                        heuristic = queried_heuristic + cost
                        old_heuristic = lookup_table.get(current_state)[0]
                        if heuristic < lookup_table.get(current_state)[0]:
                            lookup_table[current_state] = (heuristic, cost, pair[1])
                            p_queue.remove((old_heuristic, current_state))
                            bisect.insort(p_queue, (heuristic, current_state))
                else:
                    cost = lookup_table.get(pair[1])[1] + 1
                    queried_heuristic = 0
                    if (current_state.getpos(), tuple(current_state.getlist())) in heuristic_lookup:
                        queried_heuristic = heuristic_lookup.get((current_state.getpos(), tuple(current_state.getlist()))) 
                    else:
                        queried_heuristic = multi_dot_heuristic_query(maze, current_state.getpos(), current_state.getlist(), edgeset, mintree) * 2
                        heuristic_lookup[(current_state.getpos(), tuple(current_state.getlist()))] = queried_heuristic
                    heuristic = queried_heuristic + cost
                    lookup_table[current_state] = (heuristic, cost, pair[1])
                    bisect.insort(p_queue, (heuristic, current_state))

    return []
