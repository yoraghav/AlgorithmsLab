
//Submitted by Raghav Aggarwal (20EC10064)

#include <iostream>
#include <limits.h>

using namespace std;


int minDistance(int dist[], bool sptSet[], int V){     //Returns unprocessed node with minimum distance

    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++){
        if(sptSet[v] == false && dist[v] <= min){
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void printDistances(int dist[],int V,int src){
    for (int i = 0; i < V; i++){
        if(i==src){continue;}
        cout<<endl<<"Distance of vertex "<<i+1<<" from vertex "<<src+1<<" : "<<dist[i];
    }
}

void dijkstra(int V,int* graph[],int src,int vertex[]){
    
    int dist[V];
    
    bool sptSet[V];
    
    for (int i = 0; i < V; i++){
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = vertex[src];
    
    for (int count = 0; count < V - 1; count++){
        
        // Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in the first iteration.
        
        int u = minDistance(dist, sptSet, V);
        
        sptSet[u] = true;  //Marking the processed node
        
        for(int v = 0; v < V; v++){
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] + vertex[v] < dist[v]){
                dist[v] = dist[u] + graph[u][v] + vertex[v];        //updating to shortest distance
            }
        }
    }
    printDistances(dist,V,src);
}

int main(){
    
    int v;
    cout<<"Write the number of vertices in the undirected graph : ";
    cin>>v;
    cout<<"Write -1 to indicate the end of neighbors"<<endl;
    
    int* graph[v];
    for(int i=0;i<v;i++){
        graph[i] = new int [v];
    }
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            graph[i][j] = 0;        //initialising graph
        }
    }
    
    
    for(int i=0;i<v;i++){
        cout<<endl<<"Write neighbors of vertex "<<i+1<<" : ";
        int x;
        cin>>x;                             //initialising node connectivity
        while(x!=-1){
            graph[i][x-1] = -1;
            cin>>x;
        }
    }
    
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){                       //initialising edge weights
            if(graph[i][j] == -1){
                int w;
                cout<<endl<<"Weight of the edge {"<<i+1<<","<<j+1<<"}: ";
                cin>>w;
                graph[i][j] = w;
                graph[j][i] = w;
            }
        }
    }
    
    int vertex[v];
    for(int i=0;i<v;i++){                                   //initialising vertex weights
        cout<<endl<<"Weight of the vertex "<<i+1<<": ";
        cin>>vertex[i];
    }
    
    cout<<endl<<"Write source vertex: ";
    int src;
    cin>>src;
    src--;
    dijkstra(v,graph, src, vertex);

    return 0;
}


//5 2 5 -1 1 3 4 5 -1 2 4 5 -1 2 3 -1 1 2 3 -1 6 2 5 9 3 2 6 1 2 3 1 2 1
