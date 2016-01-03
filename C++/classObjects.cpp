#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <sstream>
using namespace std;


class Student {

private:
    vector<int> _subjects;
    int _total;

public:
    
    void Input(){
        int score;
        string line;
        istringsteream sstr;
        
        while (getline(cin,line)){
            for (int i=0; i<5; i++){
                sstr >> score;
                _subjects.push_back(score);
            }
        }
    }
    
    int CalculateTotalScore(){
        int total = 0;
        for (auto s: _subjects){
            total += s;
        }
        return total;
    }
    
};

int main() {
    int n;
    cin>>n;
    Student s[n];
    for(int i=0;i<n;i++)
        s[i].Input();
    int count=0;
    int krish_score=s[0].CalculateTotalScore();
    for(int i=1;i<n;i++)
    {
        int total=s[i].CalculateTotalScore();
        if(total>krish_score)
            count++;
    }
    cout<<count;
    return 0;
}





/*
int main() {
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
    
    
    return 0;
}
*/

