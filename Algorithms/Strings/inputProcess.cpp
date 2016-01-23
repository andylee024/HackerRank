
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <sstream>
using namespace std;


// Set of notes explaining how to process input

// Sample Input (get each indvidiual element)
// 30 10 40
// 30 20 40
// 40 20 30

int item;
string line;

while (getline(cin,line)){
    cout << line << endl;
    cout << "hello" << endl;
    
    istringstream sstr(line);
    while(!sstr.eof()){
        sstr >> item;
        cout << item << endl;
    }
    cout << endl;
    }

