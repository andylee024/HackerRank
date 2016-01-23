#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map> 
using namespace std;


int main() {
    int T;
    cin >> T;
    cin.ignore();
    string line1, line2;
    bool flag;
    
    for (int i=0; i<T; i++){
       
        flag = false;
        map<char, int> H;
        
        getline(cin, line1);
        getline(cin, line2);

        for (char c : line1){H[c] = 1;}
        for (char c : line2){
            if (H.count(c)>0){
                flag = true;
                break;
            }
        }
        
        if (flag){cout << "YES" << endl;}
        else{cout << "NO" << endl;}

    }
    

    return 0;
}

