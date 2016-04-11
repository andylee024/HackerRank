Maximum Profit

#include <iostream>
using namespace std;
#define SIZE 10000000000 
#define MAX(a, b) ( ((a) > (b)) ? (a) : (b)) 
typedef unsigned long long int ulli;

ulli* splitCoin(ulli n){
    int size = 3;
    ulli* a = new ulli[size];
    a[0] = n/2;
    a[1] = n/3;
    a[2] = n/4;
    return a;
}

void populate_table(ulli* T){
    T[0] = 0;
    for (ulli i=1; i<SIZE; i++){
        
        // get max value of coin if we split
        ulli s = 0;
        ulli *a = splitCoin(i);
        for (int i =0; i<3; i++){          
            ulli n1 = a[i];
            ulli n2 = T[a[i]];
            s += MAX(n1,n2);
        }
        
        T[i] = MAX(i, s);
        
        delete a;
    }
}


int main() {
    int noCases;
    cin >> noCases;
    
    ulli *T = new ulli[SIZE];
    populate_table(T);
    
    
    for (int i=0; i<noCases; i++){
        ulli n;
        cin >> n;
        ulli ans = (T[n] - n)>0 ? T[n]-n : 0;
        cout << ans << endl;
        
    }
    delete[] T;
    
return 0;
}

