#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <ctime>
#include <cassert>
using namespace std;

/*
 Journey to the Moon: 
    - The solution to this problem simply involves finding the size of each connected component in a graph and then doing calculations with the sizes.
    - Implementation: 
        1. Create a graph
        2. Run BFS to find sizes of each connected component
        3. Compute answer
 */

int main(){
    
    // Process Input
    int N, I;
    long long result = 0;
    cin >> N >> I;
    
    // Build graph
    vector<vector<int> > graph(N);
    for (int i = 0; i < I; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    // Find size of each connected component
    vector<bool> visited(N, false);
    vector<int> countries;
    int countrySize;
    
    for (int i=0; i<visited.size(); i++){
        if (visited[i] == false){
            countrySize = 1;
            
            // Breadth First Search
            queue<int> q;
            q.push(i);
            while (!q.empty()){
                int cur = q.front();
                q.pop();
                visited[cur] = true;
                for (auto v: graph[cur]){
                    if (visited[v] == false){
                        q.push(v);
                        countrySize++;
                        visited[v] = true;
                    }
                }
            }
            countries.push_back(countrySize);
        }
    }
    
    // compute result
    long long accumulated = countries[0];
    for (int i=1; i<countries.size(); i++){
        result += countries[i] * accumulated;
        accumulated += countries[i];
    }
    cout << result << endl;
    return 0;
}
