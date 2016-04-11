import sys
import pandas as pd
import numpy as np
import re
from sklearn.naive_bayes import BernoulliNB


# Helper functions
def getFeature(s):
    match = re.search('(\d+):(.+)',s)
    return match.group(2)

def getLabel(s):
    if s == "+1": return 1
    else: return -1

def returnLabel(s):
    if s == 1: return "+1"
    else: return "-1"

# Input processing
def process_input():
    
    counter = -1
    X_tr,Y_tr,X_te = [], [], []
    uids_te = []
    
    for line in sys.stdin:
        
        if counter == -1: # get n,m - ok
            n = int(line.split()[0])
            m = int(line.split()[1])
            counter += 1
            
        elif counter < n:
            line = line.split()
            x = [ line[0] ]
            feature = map(getFeature,line[2:])
            
            X_tr.append(feature)
            Y_tr.append(line[1])
            counter += 1
            
        elif counter == n:
            q = int(line)
            counter += 1
        
        else:
            line = line.split()
            uids_te.append(line[0]) 
            features = map(getFeature,line[1:])
            X_te.append(features)

    return X_tr, Y_tr, X_te, uids_te
        
        
def main():
    # process input
    X_tr, Y_tr, X_te, uids_te = process_input()
    X_tr = np.asarray(X_tr, dtype=np.float)
    Y_tr = np.asarray(Y_tr, dtype=np.int)
    X_te = np.asarray(X_te,dtype=np.float)

    # train Naive Bayes model
    clf = BernoulliNB()
    clf.fit(X_tr,Y_tr)
    predictions = clf.predict(X_te)

    # output results
    predictions = map(returnLabel, predictions.tolist())
    output = zip(uids_te, predictions)
    
    for (uid, ans) in output:
        print "%s %s" % (uid, ans)


    return


main()