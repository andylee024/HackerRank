#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <climits>
#include <assert.h>

#include <vector>
#include <queue>
#include <map>

using namespace std;

// typdef declarations
typedef struct edge{
    int incident;
    int weight;

} edge;

struct edgeCompare{
    bool operator()(const edge& e1, const edge& e2){
        return e1.weight > e2.weight;
    }
};

typedef vector<priority_queue<edge, vector<edge>, edgeCompare> > vPQ;

// function declarations
void buildMST(int,int, vPQ*);
void test_vPQ(vPQ*);


int main() {
    
    // process input
    int n,m,s;
    cin >> n; // no. nodes
    cin >> m; // no. edges
    int x,y,w; // edge(x,y) with weight w
    
    // create priority queues for each vertex v
    // each individual  PQ contains edges incident to v, ordered by lowest edge weight
    // all PQs held inside a vector named "edges", indexed by vertex number (1 to n)
    vPQ edges(n);
    for (int i=0;i<m;i++){
        cin >> x; cin >> y; cin >> w;
        edge e1, e2;
        e1.incident = y-1;
        e2.incident = x-1;
        e1.weight = w;
        e2.weight = w;
        edges[x-1].push(e1);
        edges[y-1].push(e2);
    }

    vPQ* e = &edges;
    cin >> s; // starting node
   
    // build MST and output solution
    buildMST(n,s,e);

    return 0;
    
    
}

void test_vPQ(vPQ* e){ // ok tests passed
    printf("Testing vertex priority queue.... \n");
    assert( ((*e)[0].top().weight == 3 && (*e)[0].top().incident == 1) ) ;
    (*e)[1].pop();
    assert( ((*e)[1].top().weight == 3 && (*e)[1].top().incident == 0) );// error here
    assert( ((*e)[2].top().weight == 4 && (*e)[2].top().incident == 0) );
    assert( ((*e)[3].top().weight == 6 && (*e)[3].top().incident == 1) );
    assert( ((*e)[4].top().weight == 2 && (*e)[4].top().incident == 1) );
    cout<<"All tests passed"<<endl;
}

void buildMST(int n, int s, vPQ* e){
    
    // initialize vertex sets
    int MSTweight = 0;
    map<int, bool> tree; //vertices in MST = true (set S), vertices not yet in MST = false (set U)
    vector<int> S;
    
    // initialize tree
    tree[s-1] = true;
    S.push_back(s-1);
    for (int i=0; i<n; i++){
        if (i!=s-1){
            tree[i] = false;
        }
    }

    // Prim's algorithm for building a MST
    while(S.size() < n){
        edge lightEdge;
        lightEdge.weight = INT_MAX;
        lightEdge.incident = -1;
        edge neighbor = lightEdge;
        
        for (auto s: S){
            edge neighbor;
            neighbor.weight = INT_MAX;
            
            // only need to consider edges (s,u) where s in S and u in U
            // edges (s1,s2) where s1 in S and s2 in S are irrelevant
            while(!(*e)[s].empty()){
                if (tree[(*e)[s].top().incident] == true){
                    (*e)[s].pop();
                    continue;
                }
                else{
                    neighbor = (*e)[s].top();
                    break;
                }
            }
            
            // update lightEdge if a valid edge with less weight is found
            if (neighbor.weight < lightEdge.weight){
                lightEdge = neighbor;
            }
        }
        
        // append lightEdge
        tree[lightEdge.incident] = true;
        S.push_back(lightEdge.incident);
        MSTweight += lightEdge.weight;
    }
    
    // output MST
    cout << MSTweight << endl;
}

