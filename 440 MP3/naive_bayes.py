# naive_bayes.py
# ---------------
# Licensing Information:  You are free to use or extend this projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to the University of Illinois at Urbana-Champaign
#
# Created by Justin Lizama (jlizama2@illinois.edu) on 09/28/2018
# Modified by Jaewook Yeom 02/02/2020

"""
This is the main entry point for Part 1 of MP3. You should only modify code
within this file for Part 1 -- the unrevised staff files will be used for all other
files and classes when code is run, so be careful to not modify anything else.
"""

import numpy as numpy
import math
from collections import Counter
from collections import OrderedDict

def naiveBayes(train_set, train_labels, dev_set, smoothing_parameter, pos_prior):
    """
    train_set - List of list of words corresponding with each movie review
    example: suppose I had two reviews 'like this movie' and 'i fall asleep' in my training set
    Then train_set := [['like','this','movie'], ['i','fall','asleep']]

    train_labels - List of labels corresponding with train_set
    example: Suppose I had two reviews, first one was positive and second one was negative.
    Then train_labels := [1, 0]

    dev_set - List of list of words corresponding with each review that we are testing on
              It follows the same format as train_set

    smoothing_parameter - The smoothing parameter you provided with --laplace (1.0 by default)

    pos_prior - positive prior probability (between 0 and 1)
    """
    # TODO: Write your code here
    Prob_negatives = 0
    Prob_positives = 0
    Prob_pos_dict = {}
    Prob_neg_dict = {}
    pos_size = 0
    neg_size = 0
    dev_labels = []

    # calculate the number of times each word appeared in both dictionaries.
    for i in range(0, len(train_labels)):
        # flag = 0 if negative, flag = 1 if positive 
        flag = train_labels[i]
        for word in train_set[i]:
            if flag == 0:
                neg_size += 1
                if word not in Prob_neg_dict:
                    Prob_neg_dict[word] = 1
                if word in Prob_neg_dict:
                    Prob_neg_dict[word] = Prob_neg_dict.get(word) + 1
            if flag == 1:
                pos_size += 1
                if word not in Prob_pos_dict:
                    Prob_pos_dict[word] = 1
                if word in Prob_pos_dict:
                    Prob_pos_dict[word] = Prob_pos_dict.get(word) + 1

    # grab the development set into a similar dictionary and calculate likelihood using Laplace Smoothing.
    
    for stc in dev_set:
        prob_pos = 0.0
        prob_neg = 0.0
        for word in stc:
            if word in Prob_pos_dict:
                prob_pos += numpy.log((Prob_pos_dict.get(word) + smoothing_parameter) / (pos_size + smoothing_parameter * len(Prob_pos_dict)))
            
            else:
                prob_pos += numpy.log(smoothing_parameter / (pos_size + smoothing_parameter * len(Prob_pos_dict)))
            
            if word in Prob_neg_dict:
                prob_neg += numpy.log((Prob_neg_dict.get(word) + smoothing_parameter) / (neg_size + smoothing_parameter * len(Prob_neg_dict)))
            
            else: 
                prob_neg += numpy.log(smoothing_parameter / (neg_size + smoothing_parameter * len(Prob_neg_dict)))
        prob_pos += numpy.log(pos_prior)
        prob_neg += numpy.log(1 - pos_prior)
        if prob_pos >= prob_neg:
            dev_labels.append(1)
        elif prob_pos < prob_neg:
            dev_labels.append(0)
    print(dev_labels)
    # return predicted labels of development set (make sure it's a list, not a numpy array or similar)
    return dev_labels