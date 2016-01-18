#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
using namespace std;

// Problem specific definitions
#define MAX_DIM 15
#define MAX_STEPS 305
#define MAX_POS 105
#define MOD 1000000007
#define ll long long
typedef vector<vector<long long> > pathVector;
typedef vector<pathVector> P;

// Primary Functions
void build_Dimensions(P*, vector<int>, vector<int>, int, int);
void test_build_Dimensions(P*, vector<int>, vector<int>, int, int);
void compute(P*, vector<int>, vector<int>, int, int, long long[][301]);

// Helper Functions
void fillCombinations(long long [][301], int);
void test_fillCombinations(long long[][301]);
long long modularPow(long long, int, int);
long long nCk_mod(int, int, int);
long long modular_pow(long long, long long, int);


int main() {

    int T,N,M; // T = no. test cases, N = no. dimensions, M = no. steps
    cin >> T;
	
	// precompute binomial coefficients (mod p)
	long long chooseTable[301][301];
	fillCombinations(chooseTable, 300);
    
    for (int k=0;k<T;k++){
        
        // Step 1:  process input
        cin >> N >> M;
        vector<int> position(N);
        vector<int> boundary(N);
		for (int i=0; i<N; i++){ cin >> position[i];}
        for (int i=0; i<N; i++){ cin >> boundary[i];}
        
        // Step 2a : Initialize mutli-dimensional vectors containing path information
        P pathData(N);                                               // vector containing info on all paths
        for (int i=0;i<N; i++){                                      // 1st index - dimension
            pathVector p(MAX_POS, vector<long long>(MAX_STEPS,0));   // 2nd index - position in dimension i
            pathData[i] = p;                                         // 3rd index - steps remaining from position
        }
        P* allPaths = &pathData;
        
        // Step 2b: build 1 dimensional tables for each dimension
        build_Dimensions(allPaths, boundary, position, N, M);
        
        // Step 3: Combine tables and compute answer
        compute(allPaths, boundary, position, N, M, chooseTable);
    }
	return 0;
}



/*
* build_Dimensions()  - ok!
    - For each dimension (i= 1,...,n), we build a table.
    - Each table entry cur[s][m] represents number of total possible moves given s (start pos.) and m (no. moves)
    - allPaths contains a vector of pointers, each which points to an individual table
 
*/

void build_Dimensions(P* allPaths, vector<int> boundary, vector<int> position, int N, int M){
	
	for (int i=0;i<N;i++){
        pathVector* cur = &(*allPaths)[i]; // vector accessing dimension i
		for (int s=1; s<=boundary[i]; s++){(*cur)[s][0] = 1;} // see (1)
        
        // populate table
        for (int m=1; m<=M; m++){
            for (int s=0; s<=boundary[i]; s++){
				(*cur)[s][m] += (s-1 > 0 ) ? (*cur)[s-1][m-1] % MOD : 0; //step -1 (left)
                (*cur)[s][m] += (s+1 <= boundary[i]) ? (*cur)[s+1][m-1] % MOD : 0; // step +1 (right)
				
                // mod conversion
                (*cur)[s][m] %=  MOD;
            }
        }
    }
}

void compute(P* allPaths, vector<int> boundary, vector<int> position, int N, int M, long long chooseTable[][301]){
    
    long long ans = 0;
	pathVector total(N,vector<long long>(M+1,0));
    
    // initialize convolution vector for 1st dimension
    for (int m=0; m<=M; m++){
        total[0][m] = (*allPaths)[0][position[0]][m];
    }
    
    // convolution process
    for (int i=1;i<N;i++){
        total[i][0] = 1;
        for (int m=1; m<=M; m++){
			total[i][m] = 0;
			for (int j=0; j<=m; j++){
				long long prev = total[i-1][m-j];
				long long cur = (*allPaths)[i][position[i]][j] % MOD;
				long long combinations = chooseTable[m][j];
				total[i][m] += ((prev * cur) % MOD * chooseTable[m][j]) % MOD;
				total[i][m] %= MOD;
			}
		}
    }
	
    // compute answer
    cout << total[N-1][M] << endl;
}


/****************
 Helper Functions
 ****************/

// compute binomial coeffcients
void fillCombinations(long long chooseTable[][301], int M){
	chooseTable[1][0] = 1; // initialization
	chooseTable[1][1] = 1;
	for (int n=2;n<=M;n++){
		chooseTable[n][0] = 1;
		chooseTable[n][n] = 1;
	}
	for (int n=2; n<=M; n++){ // recursive compute
		for (int k=1; k<=n; k++){
			chooseTable[n][k] = (chooseTable[n-1][k-1] % MOD) + (chooseTable[n-1][k] % MOD);
			chooseTable[n][k] %= MOD;
		}
	}
	return;
}

// not sure why this works -- dissect later
long long modular_pow(long long base, long long exponent, int modulus){
	long long result = 1;
	while (exponent > 0){
		if (exponent % 2 == 1){result = (result * base) % modulus;}
		exponent = exponent >> 1;
		base = (base * base) % modulus;
	}
	return result;
}

// n choose k mod p
long long nCk_mod(int n, int k, int p){
	long long numerator = 1;
	long long denominator = 1;
	
	for (int i=0;i<k;i++){ numerator = (numerator*(n-i))%p; }
	for (int i=1;i<=k;i++){ denominator = (denominator*i)%p; }
	long long c = modular_pow(denominator, p-2, p);
	
	return (numerator * c)%p;
}


/*
 Tests
 */

void test_build_Dimensions(P* allPaths, vector<int> boundary, vector<int> position, int N, int M){
    printf("Testing build_Dimensions.... \n");
    
    printf("Testing dimension 0.... \n");
	
    assert( (*allPaths)[0][1][1] == 1);
    assert( (*allPaths)[0][1][2] == 1);
    assert( (*allPaths)[0][1][3] == 1);
    
    printf("Testing dimension 1.... \n");
    assert( (*allPaths)[1][1][1] == 1);
    assert( (*allPaths)[1][2][1] == 2);
    assert( (*allPaths)[1][1][2] == 2);
    assert( (*allPaths)[1][2][3] == 4);
	
	/*
		cout << "printing d1 table" << endl;
		cout << (*allPaths)[0][position[0]][0] << endl;
		cout << (*allPaths)[0][position[0]][1] << endl;
		cout << (*allPaths)[0][position[0]][2] << endl;
		cout << (*allPaths)[0][position[0]][3] << endl;
		
		cout << "printing d2 table" << endl;
		cout << (*allPaths)[1][position[1]][0] << endl;
		cout << (*allPaths)[1][position[1]][1] << endl;
		cout << (*allPaths)[1][position[1]][2] << endl;
		cout << (*allPaths)[1][position[1]][3] << endl;
	*/
	
    cout<<"All tests passed"<<endl;
}
void test_fillCombinations(long long chooseTable[][301]){
	printf(" Testing chooseTable... \n");
	assert( chooseTable[295][5] == nCk_mod(295,5,MOD) );
	assert( chooseTable[300][175] == nCk_mod(300,175,MOD) );
	assert( chooseTable[173][79] == nCk_mod(173,79,MOD) );
	cout<<"All tests passed"<<endl;
}

/*
 Concepts to learn:
 1. modular power function
 2. array passing (why does 2nd element need to have size)
 
 Notes:
 (1) - We initialize 1 move for m=0 steps in order to correctly compute m>0.
 */

