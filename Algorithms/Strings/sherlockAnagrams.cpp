#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;


// Given string S, returns vector of substrings for S indexed by length 
vector<vector<string> >* get_Substrings(string S){
    int N = S.length();
    vector<vector<string> >* p = new vector<vector<string> >;
    
    // enumerate all substrings 
    for (int k=1; k<=N; k++){ // k = length of substring
        vector<string> bucket;
        for (int i=0; i<=N-k; i++){
            string substring = S.substr(i,k);
            bucket.push_back(substring);
        }
        p->push_back(bucket);
    }
    return p;
}


/* 
Counts total unordered anagram pairings 
*/ 
int countAnagram(vector<vector<string> >* p){
    int noClasses = p->size();
    vector<map<string, int> > v;
    
    map<string,int> substrCounts;
    for (int k=0; k<noClasses; k++){ //  iterate through all substring lengths 
        int n = (*p)[k].size();
        
        // compares every substring of length k with one another 
        // record total number of anagram pairs 
        int count = 0;
        for (int i=0; i<n-1; i++){
            string w1 = (*p)[k][i];
            sort(w1.begin(), w1.end());
            
            for (int j=i+1; j<n; j++){
                string w2 = (*p)[k][j];
                sort(w2.begin(), w2.end());
                
                if (w1.compare(w2) == 0){ 
                    string anagramPair = (*p)[k][i] + (*p)[k][j];
                    if (substrCounts.count(anagramPair) == 0){count++;} 
                }
            }
        }
    }
    return count;
}
            

int main() {
    int T; 
    cin >> T;
    cin.ignore();
    string S;
    for (int i=0; i<T; i++){
        getline(cin,S);
        vector<vector<string> >* p = get_Substrings(S); // enumerate all substrings
        cout<< countAnagram(p) << endl; 
    }
    return 0;
}

