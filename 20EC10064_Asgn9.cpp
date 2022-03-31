
//Submitted by Raghav Aggarwal (20EC10064)

#include <iostream>

using namespace std;

struct node{                //for nodes of adjecency list
    int vertex;
    struct node* next;
    node(int val){
        vertex = val;
        next = NULL;
    }
};

bool scheduler(node* graph[], int vertex, int* schedule, int slot,bool initial){
    
    if(initial){                                    //for sample scheduling to check
        if(schedule[vertex] == -1){
            schedule[vertex] = slot;
            node* Node = graph[vertex];
            while(Node != NULL){
                if(!scheduler(graph,Node->vertex, schedule, (slot+1)%2,0)){
                    return 0;
                }
                Node = Node->next;
            }
        }
        return 1;
    }
    if(schedule[vertex] == -1){
        schedule[vertex] = slot;
        node* Node = graph[vertex];
        while(Node != NULL){
            if(!scheduler(graph,Node->vertex, schedule, (slot+1)%2,0)){
                return 0;
            }
            Node = Node->next;
        }
    }
    else if(schedule[vertex]!=slot){
        return 0;
    }
    return 1;
}


bool exists_schedule(node* graph[], int n){     //for checking scheduling possible or not
    int schedule[n];
    for(int i=0;i<n;i++){
        schedule[i] = -1;
    }
    for(int i=0;i<n;i++){
        if(!scheduler(graph, i, schedule, 0, 1)){
            return 0;
        }
    }
    return 1;
}

void read_graph(int n,int e, node* graph[]){        //for taking inputs for graph construction
    cout<<"Reading edges..."<<endl;
    for(int i=0;i<n;i++){
        cout<<i<<" : ";
        bool first = true;
        node* Node;
        while(1){
            int x;
            cin>>x;
            if(x==-1){
                break;
            }
            if(first){
                first = false;
                graph[i] = new node(x);
                Node = graph[i];
            }
            else{
                Node->next = new node(x);
                Node = Node->next;
            }
        }
    }
}

void trivialnodes(node* graph[], int vertex, bool visited[], int disc[], int low[], int& time, int parent,bool isTrivial[]){
    
    int children = 0;
    visited[vertex] = true;
    
    low[vertex] = ++time;
    disc[vertex] = low[vertex];

    node* Node = graph[vertex];
    while(Node!=NULL){
        int v = Node->vertex;
        if(!visited[v]) {
            children++;
            trivialnodes(graph, v, visited, disc, low, time, vertex, isTrivial);
            low[vertex] = min(low[vertex], low[v]);
            if (parent != -1 && low[v] >= disc[vertex])
                isTrivial[vertex] = true;
        }

        else if (v != parent){
            low[vertex] = min(low[vertex], disc[v]);
        }
        Node = Node->next;
    }

    if(parent==-1 && children>1){
        isTrivial[vertex] = true;
    }
}
 

void find_trivial(node* graph[], int n){
    int disc[n],low[n];
    bool visited[n],isTrivial[n];
    int time = 0, par = -1;
    for(int i=0;i<n;i++){
        disc[i] = 0;
        visited[i] = false;
        isTrivial[i] = false;
    }
    
    for(int i = 0; i < 1; i++){
        if(!visited[i]){
            trivialnodes(graph, i, visited, disc, low,time, par, isTrivial);
        }
    }
    cout<<"The trivial vertices of the graph are: "<<endl;
    for(int i = 0; i < n; i++){
        if(isTrivial[i] == false){
            cout << i << " ";
        }
    }
    cout<<endl;
}

int main(){
    int n,e;
    cout<<"n = ";
    cin>>n;
    cout<<"e = ";
    cin>>e;
    
    node* graph[n];
    for(int i=0;i<n;i++){
        graph[i] = NULL;
    }
    read_graph(n,e,graph);
    
    if(exists_schedule(graph, n)){
        cout<<endl<<"There exists one or multiple conflict-free schedules."<<endl<<endl;
    }
    else{
        cout<<endl<<"There exists no conflict-free schedule."<<endl<<endl;
    }
    find_trivial(graph,n);
    return 0;
    
}

//8 9 2 3 5 -1 3 -1 0 6 -1 0 1 7 -1 5 -1 0 4 6 7 -1 2 5 -1 3 5 -1
//9 10 6 -1 2 8 -1 1 5 6 7 -1 4 -1 3 5 -1 2 4 7 -1 0 2 8 -1 2 5 -1 1 6 -1
