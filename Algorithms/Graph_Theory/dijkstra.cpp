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


/*
 * Setup
 */

//typdef and struct declarations
typedef struct vertex{
    int id;
    int distance;
    int predecessor;
    bool visited;
} vertex;

struct vertexCompare{
    bool operator()(const vertex& v1, const vertex& v2){
        return v1.distance > v2.distance;
    }
};

typedef priority_queue<vertex, vector<vertex>, vertexCompare> PQ;

typedef struct edge{
    int incident;
    int weight;
} edge;


//function declarations
vector<vector<edge> >* buildGraph(int, int);
void dijkstra(int, int, int, vector<vector<edge> >* );
void computeAnswer(vector<vertex>, int);




/******
 Main
 ******/
int main() {
    int T,n,m,s;
    cin >> T; // no. test cases
    
    for (int i=0; i<T; i++){
        // process input
        cin >> n; // no. vertices
        cin >> m; // no. edges
        vector<vector<edge> >* g = buildGraph(n, m); // adjacency list implementation
        cin >> s; // starting node
        
        // compute answer
        dijkstra(n,m,s, g);
        
        // clean up
        delete g;
    }
    return 0;
}




/* 
 Helper Functions
 */

/********************
 Dijkstra's algorithm:
 
 - C++ priority queue does not support key_update, which is needed for optimal implementation of dijkstra's algorithm. Our work-around is to simply add updated vertex distances into the Q without removing the original. 
 ********************/

void dijkstra(int n, int m, int s, vector<vector<edge> >* g){
    
    // initialization
    vector<vertex> vertices = vector<vertex>(n); // vector to track final distances
    PQ Q;
    
    for (int i=0; i<n; i++){
        vertex v;
        if (i==s-1){v.distance = 0; v.predecessor = s-1;}
        else {v.distance = INT_MAX;}
        
        v.id = i;
        v.predecessor = -1;
        v.visited = false;
        vertices[i] = v;
        Q.push(v);
    }
    
    
    while (!Q.empty()){
        
        if (vertices[Q.top().id].visited){ // pop off vertex if already visited
            Q.pop();
            continue;
        }
        
        if (Q.top().distance == INT_MAX){ // no more remaining vertices to consider
            break;
        }
        
        // set current index
        int current_id = Q.top().id;
        int current_distance = vertices[current_id].distance;
        vertices[current_id].visited = true;
        Q.pop();
        
        // Update step
        for (edge e: (*g)[current_id]){
            if (vertices[e.incident].visited == true){ // ignore irrelevant edge
                continue;
            }
            
            int alt_distance = current_distance + e.weight;
            int existing_distance = vertices[e.incident].distance;
            if (alt_distance < existing_distance){
                
                // update new distance and path
                vertices[e.incident].distance = alt_distance;
                vertices[e.incident].predecessor = current_id;
                
                // add updated vertex to priority queue
                vertex new_v = vertices[e.incident];
                Q.push(new_v);
            }
        }
    }
    computeAnswer(vertices, s);
    }



/*
 Function to build graph
    - read in edges from std input
    - uses adjacency list as implementation
*/
 
vector<vector<edge> >* buildGraph(int n, int m){
    int x,y,w;
    vector<vector<edge> >* graph = new vector<vector<edge> >(n);
    for (int i=0;i<m;i++){
        cin >> x; cin >> y; cin >> w;
        edge e1, e2;
        e1.incident = y-1;
        e2.incident = x-1;
        e1.weight = w;
        e2.weight = w;
        (*graph)[x-1].push_back(e1);
        (*graph)[y-1].push_back(e2);
    }
    return graph;
}

// function to format and computer answer
void computeAnswer(vector<vertex> vertices, int s){
    for (int k=0; k<vertices.size();k++){
        if (k != s-1){
            if (vertices[k].distance == INT_MAX){ // format distances
                vertices[k].distance = -1;
            }
            cout << vertices[k].distance << " "; // print
        }
    }
    printf("\n");
}

