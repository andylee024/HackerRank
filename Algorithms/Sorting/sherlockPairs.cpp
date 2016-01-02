#include <iostream>
#include <algorithm>
using namespace std;


// choose function
long long nChoosek( long long n, long long k ){
    if (k > n) return 0;
    if (k * 2 > n) k = n-k;
    if (k == 0) return 1;

    long long result = n;
    for( long long i = 2; i <= k; ++i ) {
        result *= (n-i+1);
        result /= i;
    }
    return result;
}

int main(){
    int t; // no. test cases
    long long n, a, ans; // no. elements in array
    long long intArray[1000001];
    cin >> t;
    
    // process input
    for (int k=0; k<t; k++){
        cin >> n;

        for (long long i = 0; i<1000001; i++) // reinitialize array to 0 to refresh
            intArray[i] = 0;
        
        for (long long i=0;i<n;i++){
            cin >> a;
            intArray[a]++;
        }
        
        ans = 0;
        for (long long i=0; i<1000001; i++){ // count pairs
            ans += nChoosek(intArray[i],2);
        }
        
        cout << ans*2 << endl;
    }
    return 0;
}


