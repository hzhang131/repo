# geometry.py
# ---------------
# Licensing Information:  You are free to use or extend this projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to the University of Illinois at Urbana-Champaign
#
# Created by Jongdeog Lee (jlee700@illinois.edu) on 09/12/2018

"""
This file contains geometry functions that relate with Part1 in MP2.
"""

import math
import numpy as np
from const import *

def computeCoordinate(start, length, angle):
    """Compute the end cooridinate based on the given start position, length and angle.

        Args:
            start (tuple): base of the arm link. (x-coordinate, y-coordinate)
            length (int): length of the arm link
            angle (int): degree of the arm link from x-axis to couter-clockwise

        Return:
            End position (int,int):of the arm link, (x-coordinate, y-coordinate)
    """
    # TODO: implement this function. 
    y_diff = int(np.trunc(length * np.sin(angle * np.pi / 180)) * -1)
    x_diff = int(np.trunc(length * np.cos(angle * np.pi / 180)))
    pos = (start[0] + x_diff, start[1] + y_diff)
    return pos


def shortest_dis(start, end, obj_pt):
    """
    Solves for the shortest distance between a point and a line SEGMENT!!!!!!!
    Algorithm adapted from given JavaScript code from stackOverflow.
    https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
    """
    x_reach = obj_pt[0] - start[0]
    y_reach = obj_pt[1] - start[1]
    x_diff = end[0] - start[0]
    y_diff = end[1] - start[1]

    dot = x_reach * x_diff + y_reach * y_diff
    length_squared = x_diff**2 + y_diff**2

    param = -1

    if length_squared != 0:
        param = dot / length_squared
    
    xx = 0
    yy = 0

    if param < 0:
        xx = start[0]
        yy = start[1]
    elif param > 1:
        xx = end[0]
        yy = end[1]
    else:
        xx = start[0] + param * x_diff
        yy = start[1] + param * y_diff
    
    dx = obj_pt[0] - xx
    dy = obj_pt[1] - yy
    dist = np.sqrt(dx*dx+dy*dy)
    return dist

def doesArmTouchObjects(armPosDist, objects, isGoal=False):
    """Determine whether the given arm links touch any obstacle or goal

        Args:
            armPosDist (list): start and end position and padding distance of all arm links [(start, end, distance)]
            objects (list): x-, y- coordinate and radius of object (obstacles or goals) [(x, y, r)]
            isGoal (bool): True if the object is a goal and False if the object is an obstacle.
                           When the object is an obstacle, consider padding distance.
                           When the object is a goal, no need to consider padding distance.
        Return:
            True if touched. False if not.
    """
    for i in objects:
        for j in armPosDist:
            # find the minimum distance between armlink and objects.
            # algorithm from stackoverflow.
            obj_pt = (i[0], i[1])
            radius = i[2]
            start = j[0]
            end = j[1]
            padding = j[2]
            # dist = np.linalg.norm(np.cross(end-start, start - obj_pt))/np.linalg.norm(end-start)
            dist = shortest_dis(start, end, obj_pt)
            if not isGoal:
                if dist <= (radius + padding):
                    return True
            elif isGoal:
                if dist <= radius:
                    return True
    return False

def dist(pt1, pt2):
    return np.sqrt((pt1[0] - pt2[0]) * (pt1[0] - pt2[0]) + (pt1[1] - pt2[1]) * (pt1[1] - pt2[1]))

def doesArmTipTouchGoals(armEnd, goals):
    """Determine whether the given arm tip touch goals

        Args:
            armEnd (tuple): the arm tip position, (x-coordinate, y-coordinate)
            goals (list): x-, y- coordinate and radius of goals [(x, y, r)]. There can be more than one goal.
        Return:
            True if arm tick touches any goal. False if not.
    """
    for i in goals:
        pt = (i[0], i[1])
        radius = i[2]
        if dist(armEnd, pt) <= radius:
            return True
    return False


def isArmWithinWindow(armPos, window):
    """Determine whether the given arm stays in the window

        Args:
            armPos (list): start and end positions of all arm links [(start, end)]
            window (tuple): (width, height) of the window

        Return:
            True if all parts are in the window. False if not.
    """
    width = window[0]   
    height = window[1]
    for i in armPos:
        start = i[0]
        end = i[1]
        if end[0] > width or end[0] < 0 or start[0] > width or start[0] < 0:
            return False
        elif end[1] > height or end[1] < 0 or start[1] > height or start[1] < 0:
            return False
    return True


if __name__ == '__main__':
    computeCoordinateParameters = [((150, 190),100,20), ((150, 190),100,40), ((150, 190),100,60), ((150, 190),100,160)]
    resultComputeCoordinate = [(243, 156), (226, 126), (200, 104), (57, 156)]
    testRestuls = [computeCoordinate(start, length, angle) for start, length, angle in computeCoordinateParameters]
    assert testRestuls == resultComputeCoordinate

    testArmPosDists = [((100,100), (135, 110), 4), ((135, 110), (150, 150), 5)]
    testObstacles = [[(120, 100, 5)], [(110, 110, 20)], [(160, 160, 5)], [(130, 105, 10)]]
    resultDoesArmTouchObjects = [
        True, True, False, True, False, True, False, True,
        False, True, False, True, False, False, False, True
    ]

    testResults = []
    for testArmPosDist in testArmPosDists:
        for testObstacle in testObstacles:
            testResults.append(doesArmTouchObjects([testArmPosDist], testObstacle))
            # print(testArmPosDist)
            # print(testObstacle)
            # print(doesArmTouchObjects([testArmPosDist], testObstacle))

    print("\n")
    for testArmPosDist in testArmPosDists:
        for testObstacle in testObstacles:
            testResults.append(doesArmTouchObjects([testArmPosDist], testObstacle, isGoal=True))
            # print(testArmPosDist)
            # print(doesArmTouchObjects([testArmPosDist], testObstacle, isGoal=True))
    assert resultDoesArmTouchObjects == testResults

    testArmEnds = [(100, 100), (95, 95), (90, 90)]
    testGoal = [(100, 100, 10)]
    resultDoesArmTouchGoals = [True, True, False]

    testResults = [doesArmTipTouchGoals(testArmEnd, testGoal) for testArmEnd in testArmEnds]
    assert resultDoesArmTouchGoals == testResults

    testArmPoss = [((100,100), (135, 110)), ((135, 110), (150, 150))]
    testWindows = [(160, 130), (130, 170), (200, 200)]
    resultIsArmWithinWindow = [True, False, True, False, False, True]
    testResults = []
    for testArmPos in testArmPoss:
        for testWindow in testWindows:
            testResults.append(isArmWithinWindow([testArmPos], testWindow))
    assert resultIsArmWithinWindow == testResults

    print("Test passed\n")
