#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>
#include <iostream>
#include <sstream>

using namespace std;

bool check_balanced(char c1, char c2){
    if ( (c1 == '(') && (c2 == ')') ){ return true;}
    if ( (c1 == '[') && (c2 == ']') ){ return true;}
    if ( (c1 == '{') && (c2 == '}') ){ return true;}
    return false;
}

int main() {
    
    string line;
    int T;
    bool balanced;
    
    getline(cin,line);
    istringstream iss(line);
    iss >> T;
    
    // process test cases
    for (int i=0;i<T;i++){
        getline(cin,line);
        balanced = true;
        stack<char> S;
        
        for (auto c: line){
            if (!balanced){break;}
            if ( (c == '(') || (c == '{') || (c == '[') ){S.push(c);}
            
            else{
                // edge case: empty stack
                if (S.empty()){balanced = false; break;}
                
                // check mismatched parantheses
                balanced = check_balanced(S.top(), c);
                S.pop();
            }
        }
        balanced ? printf("YES \n") : printf("NO \n") ;
    }
    return 0;
}



