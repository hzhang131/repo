import bisect
import numpy
import math
import time
"""
This is the main entry point for MP4. You should only modify code
within this file -- the unrevised staff files will be used for all other
files and classes when code is run, so be careful to not modify anything else.
"""

def baseline(train, test):
    '''
    TODO: implement the baseline algorithm. This function has time out limitation of 1 minute.
    input:  training data (list of sentences, with tags on the words)
            E.g. [[(word1, tag1), (word2, tag2)...], [(word1, tag1), (word2, tag2)...]...]
            test data (list of sentences, no tags on the words)
            E.g  [[word1,word2,...][word1,word2,...]]
    output: list of sentences, each sentence is a list of (word,tag) pairs.
            E.g. [[(word1, tag1), (word2, tag2)...], [(word1, tag1), (word2, tag2)...]...]
    '''
    current_time = time.time()
    predicts = []
    word_dict = {}
    word_tag_dict = {}
    tag_set = {}
    tag_rank = []
    for element in train:
        for word_tag in element:
           if word_tag[1] not in tag_set:
                tag_set[word_tag[1]] = 1
           elif word_tag[1] in tag_set:
                tag_set[word_tag[1]] += 1
           if word_tag not in word_tag_dict:
                word_tag_dict[word_tag] = 1
           elif word_tag in word_tag_dict:
                word_tag_dict[word_tag] += 1
    for key in word_tag_dict:
        if key[0] not in word_dict:
           word_dict[key[0]] = []
           word_dict[key[0]].append((key[1], word_tag_dict.get(key)))
        if key[0] in word_dict:
           word_dict[key[0]].append((key[1], word_tag_dict.get(key)))
    for keys in word_dict:
        word_dict.get(keys).sort(key=lambda x:x[1])
    for keys in tag_set:
        tag_rank.append((keys, tag_set.get(keys)))
    # ---------Testing phase----------
    tag_rank.sort(key=lambda x:x[1])
    for element in test:
        local_list = []
        for word in element:
            if word in word_dict:
                final_tag = word_dict.get(word)[len(word_dict.get(word))-1][0]
                local_list.append((word, final_tag))
            if word not in word_dict:
                final_tag = tag_rank[len(tag_rank)-1][0]
                local_list.append((word, final_tag))
        predicts.append(local_list)
    end_time = time.time()
    print("elapsed:", end_time - current_time)
    return predicts


def viterbi_p1(train, test):
    '''
    TODO: implement the simple Viterbi algorithm. This function has time out limitation for 3 mins.
    input:  training data (list of sentences, with tags on the words)
            E.g. [[(word1, tag1), (word2, tag2)], [(word3, tag3), (word4, tag4)]]
            test data (list of sentences, no tags on the words)
            E.g [[word1,word2...]]
    output: list of sentences with tags on the words
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
    
    for stc in train:
        for word_tag in stc:
            if word_tag[1] not in tag_prob:
                tag_prob[word_tag[1]] = 1
            else:
                tag_prob[word_tag[1]] += 1

    # Let me start from the start_p.
    for stc in train:
        if stc[0][1] not in start_p:
           start_p[stc[0][1]] = 1
        else:
           start_p[stc[0][1]] += 1

    for elem in tag_prob: 
        if elem in start_p:
            start_p[elem] = numpy.log((start_p[elem] + 0.0000001)/(number_of_stcs + len(tag_prob)))
        else:
            unk_start_p[elem] = numpy.log(0.0000001/(number_of_stcs + len(tag_prob)))

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
        final_prob = numpy.log((trans_p.get(pair) + 0.0000001) / (tag_prob.get(pair[0]) + 0.0000001 * len(tag_prob)))
        trans_p[pair] = final_prob
    
    for keys in number_of_transitions:
        final_prob = numpy.log(0.0000001 / (tag_prob.get(keys) + 0.0000001*len(tag_prob)))
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
        final_prob = numpy.log((emit_p.get(word_tag) + 0.0000001) / (tag_prob.get(word_tag[1]) + 0.0000001 * len(tag_prob)))
        emit_p[word_tag] = final_prob

    for keys in number_of_emissions:
        final_prob = numpy.log(0.0000001 / (tag_prob.get(keys) + 0.0000001*len(tag_prob)))
        unk_emit_p[keys] = final_prob

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

def viterbi_p2(train, test):
    '''
    TODO: implement the optimized Viterbi algorithm. This function has time out limitation for 3 mins.
    input:  training data (list of sentences, with tags on the words)
            E.g. [[(word1, tag1), (word2, tag2)], [(word3, tag3), (word4, tag4)]]
            test data (list of sentences, no tags on the words)
            E.g [[word1,word2...]]
    output: list of sentences with tags on the words
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
            number_of_hapax +=1
            if hapax.get(i)[1][1] not in tags_on_hapax:
                tags_on_hapax[hapax.get(i)[1][1]] = 1
            else:
                tags_on_hapax[hapax.get(i)[1][1]] += 1

    for tag in tags_on_hapax:
        tags_on_hapax[tag] = tags_on_hapax.get(tag) / number_of_hapax
        # print(tag, tags_on_hapax[tag])

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