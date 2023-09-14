 #include <stdio.h>
#include <stdbool.h>

#define V 5 // Number of vertices in the graph

int graph[V][V] = {
   {0, 2, 0, 6, 0},
   {2, 0, 3, 8, 5},
   {0, 3, 0, 0, 7},
   {6, 8, 0, 0, 9},
   {0, 5, 7, 9, 0}
};

int parent[V];
int key[V];
bool mstSet[V];

void primMST() {
    // Initialize key values and MST set
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }
    
    key[0] = 0; // Start with the first vertex
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = minKey();
        mstSet[u] = true;
        
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the MST
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}

int minKey() {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

int main() {
    primMST();
    return 0;
}
