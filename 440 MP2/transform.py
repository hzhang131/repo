
# transform.py
# ---------------
# Licensing Information:  You are free to use or extend this projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to the University of Illinois at Urbana-Champaign
# 
# Created by Jongdeog Lee (jlee700@illinois.edu) on 09/12/2018

"""
This file contains the transform function that converts the robot arm map
to the maze.
"""
import copy
from arm import Arm
from maze import Maze
from search import *
from geometry import *
from const import *
from util import *

def transformToMaze(arm, goals, obstacles, window, granularity):
    """This function transforms the given 2D map to the maze in MP1.
    
        Args:
            arm (Arm): arm instance
            goals (list): [(x, y, r)] of goals
            obstacles (list): [(x, y, r)] of obstacles
            window (tuple): (width, height) of the window
            granularity (int): unit of increasing/decreasing degree for angles

        Return:
            Maze: the maze instance generated based on input arguments.

    """
    # Determine the number of rows and cols.
    alphas_range = arm.getArmLimit()[0]
    min_alpha = alphas_range[0]
    max_alpha = alphas_range[1]
    rows = int((max_alpha - min_alpha) / (granularity)) + 1
    # print("Number of rows: ", rows)
    beta_range = arm.getArmLimit()[1]
    min_beta = beta_range[0]
    max_beta = beta_range[1]
    cols = int((max_beta - min_beta) / (granularity)) + 1
    # print("Number of cols: ", cols)
    # Fill in the starting point.
    Init_pos = arm.getArmAngle()
    Init_alpha = Init_pos[0]
    Init_beta = Init_pos[1]
    # Determine the goal points and walls.
    goals_in_maze = []
    walls = []
    offsets = []
    offsets.append(min_alpha)
    offsets.append(min_beta)
    start = angleToIdx(Init_pos, offsets, granularity)
    # j -- β, column,  i -- α, row.
   
    for i in range(min_alpha, max_alpha+granularity, granularity):
        for j in range(min_beta, max_beta+granularity, granularity):
            arm.setArmAngle((i, j))
            coordinate = angleToIdx((i, j), offsets, granularity)
            if coordinate == start:
                continue
            if doesArmTipTouchGoals(arm.getEnd(), goals) and not doesArmTouchObjects(arm.getArmPosDist(), obstacles):
                goals_in_maze.append(coordinate)
                if coordinate == (35, 75):
                    print("Fuck1.")
                continue
            if doesArmTouchObjects(arm.getArmPosDist(), obstacles):
                walls.append(coordinate)
                if coordinate == (35, 75):
                    print("Fuck2.")
                continue
            if doesArmTouchObjects(arm.getArmPosDist(), goals, True) and not doesArmTipTouchGoals(arm.getEnd(), goals):
                walls.append(coordinate)
                if coordinate == (35, 75):
                    print("Fuck3.")
                continue
            if not isArmWithinWindow(arm.getArmPos(), window):
                walls.append(coordinate)
                if coordinate == (35, 75):
                    print("Fuck4.")
                continue
            
    input_map = []
    # Generating input_map from two lists.
    for i in range(0, rows):
        input_map.append([])
        for j in range(0, cols):
            input_map[i].append(SPACE_CHAR) 
    
    #put start pt onto map.
    input_map[start[0]][start[1]] = START_CHAR

    for i in range(0, rows):
        for j in range(0, cols):
            if (i, j) in walls:
                input_map[i][j] = WALL_CHAR
            elif (i, j) in goals_in_maze:
                input_map[i][j] = OBJECTIVE_CHAR

    generated_maze = Maze(input_map, offsets, granularity)
    generated_maze.saveToFile("mine.txt")
    return generated_maze
     
    