#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;


struct node{
    int distance = -1;
    bool visited = false;
};


// function declarations
vector<vector<int> > buildGraph(int, int);
void bfsCompute(int, vector<node>*, vector<vector<int> >*);


int main() {
    
    // process test cases
    int t,n,m,s;
    cin >> t;
    
    
    for (int i = 0; i<t; i++){
        cin >> n; // number nodes
        cin >> m; // number edges
        
        // build graph
        vector<vector<int> > graph = buildGraph(n,m);
        vector<node> *nodes = new vector<node>(n);
        vector<vector<int> > *g;
        
        cin >> s; // start node
        g = &graph;
        
        bfsCompute(s,nodes,g);
    }
    
    
    return 0;
}


vector<vector<int> > buildGraph(int n, int m){ //ok!
    int x, y;
    vector<vector<int> > graph = vector<vector<int> >(n);
    for (int i = 0; i<m; i++){
        cin >> x;
        cin >> y;
        graph[x-1].push_back(y-1);
        graph[y-1].push_back(x-1);
    }
    return graph;
}


void bfsCompute(int s, vector<node>* nodes, vector<vector<int> >* g){
    int current = s-1;
    queue<int> Q;
    (*nodes)[current].visited = true;
    (*nodes)[current].distance = 0;
    
    // run BFS procedure
    Q.push(current);
    while (!Q.empty()){
        current = Q.front();
        Q.pop();
        
        // push unvisited neighbors
        for (auto neighbor: (*g)[current]){
            if ((*nodes)[neighbor].visited == false){
                Q.push(neighbor);
                (*nodes)[neighbor].visited = true;
                (*nodes)[neighbor].distance = (*nodes)[current].distance + 6;
            }
        }
    }
    
    // print solution
    for (int j=0; j<(*nodes).size(); j++){
        if (j!=s-1){
            cout << (*nodes)[j].distance << " ";
        }
    }
    printf("\n");
    
    return;
    
    
}