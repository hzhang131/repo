from collections import defaultdict
import math
import numpy
import time
import re
def extra(train,test):
    '''
    TODO: implement improved viterbi algorithm for extra credit.
    input:  training data (list of sentences, with tags on the words)
            E.g. [[(word1, tag1), (word2, tag2)...], [(word1, tag1), (word2, tag2)...]...]
            test data (list of sentences, no tags on the words)
            E.g  [[word1,word2,...][word1,word2,...]]
    output: list of sentences, each sentence is a list of (word,tag) pairs.
            E.g. [[(word1, tag1), (word2, tag2)...], [(word1, tag1), (word2, tag2)...]...]
    '''
    current_time = time.time()
    predicts = []
    # prepare start_p, emit_p and trans_p from the train set.
    
    tag_prob = {}
    start_p = {}
    number_of_stcs = len(train)
    number_of_transitions = {}
    types_of_transitions = {}
    number_of_emissions = {}
    types_of_emissions = {}
    unk_trans_p = {}
    trans_p = {}
    unk_start_p = {}
    unk_emit_p = {}
    emit_p = {}
    emit_prob = {}
    hapax = {}
    tags_on_hapax = {}
    

    for stc in train:
        for word_tag in stc:
            if word_tag[1] not in tag_prob:
                tag_prob[word_tag[1]] = 1
            else:
                tag_prob[word_tag[1]] += 1
            if word_tag[0] not in hapax:
                hapax[word_tag[0]] = (True, word_tag)
            else:
                hapax[word_tag[0]] = (False, word_tag)
    
    number_of_hapax = 0
    for i in hapax:
        if hapax.get(i)[0] == True:
            number_of_hapax += 1
            if hapax.get(i)[1][1] not in tags_on_hapax:
                tags_on_hapax[hapax.get(i)[1][1]] = 1
            else:
                tags_on_hapax[hapax.get(i)[1][1]] += 1

    for tag in tags_on_hapax:
        tags_on_hapax[tag] = tags_on_hapax.get(tag) / number_of_hapax

    # start from the start_p.
    for stc in train:
        if stc[0][1] not in start_p:
           start_p[stc[0][1]] = 1
        else:
           start_p[stc[0][1]] += 1

    for elem in tag_prob: 
        if elem in start_p:
            start_p[elem] = numpy.log((start_p[elem] + 0.00001)/(number_of_stcs + 0.00001 * len(tag_prob)))
        else:
            unk_start_p[elem] = numpy.log(0.00001/(number_of_stcs + 0.00001 * len(tag_prob)))

    for stc in train:
        for i in range(0, len(stc)-1):
            pair = (stc[i][1], stc[i+1][1])
            if pair not in trans_p:
                trans_p[pair] = 1
                if pair[0] not in number_of_transitions:
                    number_of_transitions[pair[0]] = 1
                    types_of_transitions[pair[0]] = 1
                else:
                    number_of_transitions[pair[0]] += 1
                    types_of_transitions[pair[0]] += 1
            else:
                trans_p[pair] += 1
                number_of_transitions[pair[0]] += 1

    for pair in trans_p:    
        final_prob = numpy.log((trans_p.get(pair) + 0.00001) / (tag_prob.get(pair[0]) + 0.00001 * len(tag_prob)))
        trans_p[pair] = final_prob
    
    for keys in number_of_transitions:
        final_prob = numpy.log(0.00001 / (tag_prob.get(keys) + 0.00001*len(tag_prob)))
        unk_trans_p[keys] = final_prob

    for stc in train:
        for word_tag in stc:
            if word_tag not in emit_p:
                emit_p[word_tag] = 1
                if word_tag[1] not in number_of_emissions:
                    number_of_emissions[word_tag[1]] = 1
                    types_of_emissions[word_tag[1]] = 1
                else:
                    number_of_emissions[word_tag[1]] += 1
                    types_of_emissions[word_tag[1]] += 1
            else:
                emit_p[word_tag] += 1
                number_of_emissions[word_tag[1]] += 1
    
    for word_tag in emit_p:
        if word_tag[1] in tags_on_hapax:
            final_prob = numpy.log((emit_p.get(word_tag) + 0.00001 * tags_on_hapax.get(word_tag[1])) / (tag_prob.get(word_tag[1]) + 0.00001 * tags_on_hapax.get(word_tag[1]) * len(tag_prob)))
        else:
            final_prob = numpy.log((emit_p.get(word_tag) + 0.00001 * 1 / number_of_hapax) / (tag_prob.get(word_tag[1]) + 0.00001 * len(tag_prob)))
        emit_p[word_tag] = final_prob
    
    for keys in number_of_emissions:
        if keys in tags_on_hapax:
            final_prob = numpy.log(0.00001 * tags_on_hapax.get(keys) / (tag_prob.get(keys) + 0.00001 * tags_on_hapax.get(keys) * len(tag_prob)))
        else:
            final_prob = numpy.log((0.00001 * 1 / number_of_hapax) / (tag_prob.get(keys) + 0.00001 * len(tag_prob)))
        unk_emit_p[keys] = final_prob

    print(emit_p)
# Now we adapt the three possibilities to the testset.
# Need to apply smoothing.
    for stc in test:
        local_list = []
        DP_list = []
        count = 0
        for i in range(0, len(stc)):
            word_dict = {}
            if i == 0:
                for keys in tag_prob:
                   if keys in start_p:
                       word_dict[(stc[i], keys)] = [start_p.get(keys), 'None']
                   else:
                       word_dict[(stc[i], keys)] = [unk_start_p.get(keys), 'None']
                   if (stc[i], keys) in emit_p:
                       word_dict.get((stc[i], keys))[0] += emit_p.get((stc[i], keys))
                   else:
                       word_dict[(stc[i], keys)][0] += unk_emit_p.get(keys)
                DP_list.append(word_dict)
            else:
                for current_tag in tag_prob:
                    temp_list = []
                    for entries in DP_list[i-1]:
                        if (entries[1], current_tag) in trans_p:
                           trans = trans_p.get((entries[1], current_tag))
                           current_prob = DP_list[i-1].get(entries)[0] + trans
                           if (stc[i], current_tag) in emit_p:
                              current_prob += emit_p.get((stc[i], current_tag))
                           else:
                              current_prob += unk_emit_p.get(current_tag)
                           temp_list.append((entries[1], current_prob))
                        else:
                           trans = unk_trans_p.get(entries[1])
                           current_prob = DP_list[i-1].get(entries)[0] + trans
                           if (stc[i], current_tag) in emit_p:
                              current_prob += emit_p.get((stc[i], current_tag))
                           else:
                              current_prob += unk_emit_p.get(current_tag)
                           temp_list.append((entries[1], current_prob))
                    temp_list.sort(key=lambda x:x[1])
                    word_dict[stc[i], current_tag] = [temp_list[len(temp_list)-1][1], temp_list[len(temp_list)-1][0]]
                DP_list.append(word_dict)
        
        largest_prob = float("-inf")
        largest_key = ('None', 'None')
        for keys in DP_list[len(DP_list)-1]:
            if DP_list[len(DP_list)-1].get(keys)[0] > largest_prob:
                largest_prob = DP_list[len(DP_list)-1].get(keys)[0]
                largest_key = keys

        last_state = largest_key
        for i in range(len(DP_list)-1, -1, -1):
            local_list.append(last_state)
            if i >= 1:
                last_state = (stc[i-1], DP_list[i].get(last_state)[1])
        local_list.reverse()
        predicts.append(local_list)
    
    end_time = time.time()
    print("elapsed:", end_time - current_time)
    return predicts