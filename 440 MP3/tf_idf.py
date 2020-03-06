# tf_idf_bayes.py
# ---------------
# Licensing Information:  You are free to use or extend this projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to the University of Illinois at Urbana-Champaign
#
# Created by Justin Lizama (jlizama2@illinois.edu) on 09/28/2018
# Modified by Jaewook Yeom 02/02/2020

"""
This is the main entry point for the Extra Credit Part of this MP. You should only modify code
within this file for the Extra Credit Part -- the unrevised staff files will be used for all other
files and classes when code is run, so be careful to not modify anything else.
"""

import numpy as np
import math
from collections import Counter
import time



def compute_tf_idf(train_set, train_labels, dev_set):
    """
    train_set - List of list of words corresponding with each movie review
    example: suppose I had two reviews 'like this movie' and 'i fall asleep' in my training set
    Then train_set := [['like','this','movie'], ['i','fall','asleep']]

    train_labels - List of labels corresponding with train_set
    example: Suppose I had two reviews, first one was positive and second one was negative.
    Then train_labels := [1, 0]

    dev_set - List of list of words corresponding with each review that we are testing on
              It follows the same format as train_set

    Return: A list containing words with the highest tf-idf value from the dev_set documents
            Returned list should have same size as dev_set (one word from each dev_set document)
    """

    # TODO: Write your code here
    # Extra credit lalala.
    containing_doc = {}
    returned_list = []
    for stc in train_set:
        considered_list = []
        for word in stc:
                if word not in containing_doc and word not in considered_list:
                        containing_doc[word] = 1
                        considered_list.append(word)
                elif word in containing_doc and word not in considered_list:
                        containing_doc[word] += 1
                        considered_list.append(word)
    print(len(train_set))
    count = 0
    for stc in dev_set:
        # if count == 0:
        #         print(stc)
        shown_times = {}
        Prob_dict = []
        for word in stc:
                if word not in shown_times:
                        shown_times[word] = 1
                elif word in shown_times:
                        shown_times[word] += 1
        for word in stc:
                # if count == 0 and word in containing_doc:
                #         print(word, shown_times.get(word), containing_doc.get(word))
                if word in containing_doc:
                        prob = shown_times.get(word) / len(stc) * np.log(8000.0/(1 + containing_doc.get(word)))
                else:
                        prob = shown_times.get(word) / len(stc) * np.log(8000.0)
                Prob_dict.append((word, prob))

        candidate = Prob_dict[0]
        for entry in Prob_dict:
                if entry[1] > candidate[1]:
                        candidate = entry
        returned_list.append(candidate[0])
        count += 1
    # return list of words (should return a list, not numpy array or similar)
    print(returned_list)
    return returned_list