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
This is the main entry point for Part 2 of this MP. You should only modify code
within this file for Part 2 -- the unrevised staff files will be used for all other
files and classes when code is run, so be careful to not modify anything else.
"""


import numpy as numpy
import math
from collections import Counter

def naiveBayesMixture(train_set, train_labels, dev_set, bigram_lambda,unigram_smoothing_parameter, bigram_smoothing_parameter, pos_prior):
    """
    train_set - List of list of words corresponding with each movie review
    example: suppose I had two reviews 'like this movie' and 'i fall asleep' in my training set
    Then train_set := [['like','this','movie'], ['i','fall','asleep']]

    train_labels - List of labels corresponding with train_set
    example: Suppose I had two reviews, first one was positive and second one was negative.
    Then train_labels := [1, 0]

    dev_set - List of list of words corresponding with each review that we are testing on
              It follows the same format as train_set

    bigram_lambda - float between 0 and 1

    unigram_smoothing_parameter - Laplace smoothing parameter for unigram model (between 0 and 1)

    bigram_smoothing_parameter - Laplace smoothing parameter for bigram model (between 0 and 1)

    pos_prior - positive prior probability (between 0 and 1)
    """

    # TODO: Write your code here
    Prob_pos_uni_dict = {}
    Prob_pos_bi_dict = {}
    Prob_neg_uni_dict = {}
    Prob_neg_bi_dict = {}
    pos_size_uni = 0
    pos_size_bi = 0
    neg_size_uni = 0
    neg_size_bi = 0
    prob_pos_final = 0.0
    prob_neg_final = 0.0
    dev_labels = []

    for i in range(0, len(train_labels)):
        # flag = 0 if negative, flag = 1 if positive 
        flag = train_labels[i]
        for word in train_set[i]:
            if flag == 0:
                neg_size_uni += 1
                if word not in Prob_neg_uni_dict:
                    Prob_neg_uni_dict[word] = 1
                if word in Prob_neg_uni_dict:
                    Prob_neg_uni_dict[word] = Prob_neg_uni_dict.get(word) + 1
            if flag == 1:
                pos_size_uni += 1
                if word not in Prob_pos_uni_dict:
                    Prob_pos_uni_dict[word] = 1
                if word in Prob_pos_uni_dict:
                    Prob_pos_uni_dict[word] = Prob_pos_uni_dict.get(word) + 1

    for i in range(0, len(train_labels)):
        flag = train_labels[i]
        for j in range(0, len(train_set[i])-1):
            if flag == 0:
                neg_size_bi += 1
                if (train_set[i][j], train_set[i][j+1]) not in Prob_neg_bi_dict:
                    Prob_neg_bi_dict[(train_set[i][j], train_set[i][j+1])] = 1
                else: 
                    Prob_neg_bi_dict[(train_set[i][j], train_set[i][j+1])] = Prob_neg_bi_dict.get((train_set[i][j], train_set[i][j+1])) + 1
            if flag == 1:
                pos_size_bi += 1
                if (train_set[i][j], train_set[i][j+1]) not in Prob_pos_bi_dict:
                    Prob_pos_bi_dict[(train_set[i][j], train_set[i][j+1])] = 1
                else: 
                    Prob_pos_bi_dict[(train_set[i][j], train_set[i][j+1])] = Prob_pos_bi_dict.get((train_set[i][j], train_set[i][j+1])) + 1
    
    for stc in dev_set:
        prob_pos = 0.0
        prob_neg = 0.0
        for word in stc:
            if word in Prob_pos_uni_dict:
                prob_pos += numpy.log((Prob_pos_uni_dict.get(word) + unigram_smoothing_parameter) / (pos_size_uni + unigram_smoothing_parameter * len(Prob_pos_uni_dict)))
            
            else:
                prob_pos += numpy.log(unigram_smoothing_parameter / (pos_size_uni + unigram_smoothing_parameter * len(Prob_pos_uni_dict)))
            
            if word in Prob_neg_uni_dict:
                prob_neg += numpy.log((Prob_neg_uni_dict.get(word) + unigram_smoothing_parameter) / (neg_size_uni + unigram_smoothing_parameter * len(Prob_neg_uni_dict)))
            
            else: 
                prob_neg += numpy.log(unigram_smoothing_parameter / (neg_size_uni + unigram_smoothing_parameter * len(Prob_neg_uni_dict)))
        prob_pos += numpy.log(pos_prior)
        prob_pos += numpy.log(1-bigram_lambda)
        prob_neg += numpy.log(1 - pos_prior)
        prob_neg += numpy.log(1-bigram_lambda)
        prob_pos = numpy.exp(prob_pos)
        prob_neg = numpy.exp(prob_neg)
        prob_pos_final += prob_pos
        prob_neg_final += prob_neg
        prob_pos = 0.0
        prob_neg = 0.0

        for i in range(0, len(stc)-1):
            if (stc[i], stc[i+1]) in Prob_pos_bi_dict:
                prob_pos += numpy.log((Prob_pos_bi_dict.get((stc[i], stc[i+1])) + bigram_smoothing_parameter) / (pos_size_bi + bigram_smoothing_parameter * len(Prob_pos_bi_dict)))
            else:  
                prob_pos += numpy.log(bigram_smoothing_parameter / (pos_size_bi + bigram_smoothing_parameter * len(Prob_pos_bi_dict)))
            if (stc[i], stc[i+1]) in Prob_neg_bi_dict:
                prob_neg += numpy.log((Prob_neg_bi_dict.get((stc[i], stc[i+1])) + bigram_smoothing_parameter) / (neg_size_bi + bigram_smoothing_parameter * len(Prob_neg_bi_dict)))
            else:
                prob_neg += numpy.log(bigram_smoothing_parameter / (neg_size_bi + bigram_smoothing_parameter * len(Prob_neg_bi_dict)))
        prob_pos += numpy.log(pos_prior)
        prob_pos += numpy.log(bigram_lambda)
        prob_neg += numpy.log(1-pos_prior)
        prob_neg += numpy.log(bigram_lambda)
        prob_pos = numpy.exp(prob_pos)
        prob_neg = numpy.exp(prob_neg)
        prob_pos_final += prob_pos 
        prob_neg_final += prob_neg
        if prob_pos_final >= prob_neg_final:
            dev_labels.append(1)
        if prob_pos_final < prob_neg_final:
            dev_labels.append(0)
    # return predicted labels of development set (make sure it's a list, not a numpy array or similar)
    return dev_labels