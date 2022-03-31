
//Submitted by Raghav Aggarwal (20EC10064)

#include <iostream>

using namespace std;

struct Node{
    int key,a,b;
    Node(int val,int c,int d){
        key = val;
        a = c;
        b = d;
    }
};

void swap(Node* x,Node* y){
    int q,w,e;
    q = x->key;
    w = x->a;
    e = x->b;
    x->key = y->key;
    x->a = y->a;
    x->b = y->b;
    y->key = q;
    y->a = w;
    y->b = e;
}

void heapify(Node* arr[], int n, int i)
{
    int smallest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;
    
    if (l<n && arr[l]->key < arr[smallest]->key){
        smallest = l;
    }
 
    if (r<n && arr[r]->key < arr[smallest]->key){
        smallest = r;
    }
    
    if (smallest != i){
        swap(arr[i], arr[smallest]);
        heapify(arr, n, smallest);
    }
}

void deleteRoot(Node* arr[], int& n){
    swap(arr[0],arr[n-1]);
    n-=1;
    heapify(arr, n, 0);
}

void insertheapify(Node* arr[], int n, int i){
    int parent = (i-1) / 2;
    if (arr[parent]->key > 0) {
        if(arr[i]->key < arr[parent]->key) {
            swap(arr[i], arr[parent]);
            insertheapify(arr, n, parent);
        }
    }
}

void insertNode(Node* arr[], int& n, int Key,int x,int y){
    n++;
    arr[n-1]->key = Key;
    arr[n-1]->a = x;
    arr[n-1]->b = y;
    insertheapify(arr, n, n-1);
}


int main(){
    int n;
    cout<<"n = ";
    cin>>n;
    Node* heap1[n];
    Node* heap2[n];
    for(int i=1;i<n+1;i++){
        heap1[i-1] = new Node(i+1,i,1);
        heap2[i-1] = new Node(i*i*i + 1,i,1);
    }
    
    //we do not need to heapify in the first heaps because they are already sorted and are hence in a heap format
    
    //also we have built the heap function which automatically swaps the minimum value to index 0 hence we do need to iterate for minimum key
    
    int n1=n,n2=n;
    int k=1;
    int sol=0;
    
    while(k){

        if(n1==0||n2==0){
            k=0;
        }
        else if(heap1[0]->key<heap2[0]->key){
            int a = heap1[0]->a;
            int b = heap1[0]->b;
            deleteRoot(heap1, n1);
            if(b<n){
                insertNode(heap1, n1, a+((b+1)*(b+1)), a, b+1);
            }
        }
        else if(heap1[0]->key>heap2[0]->key){
            int a = heap2[0]->a;
            int b = heap2[0]->b;
            deleteRoot(heap2, n2);
            if(b<n){
                insertNode(heap2, n2, a*a*a+((b+1)*(b+1)*(b+1)*(b+1)), a, b+1);
            }
        }
        else if(heap1[0]->key==heap2[0]->key){
            cout<<heap1[0]->a<<" "<<heap1[0]->b<<" "<<heap2[0]->a<<" "<<heap2[0]->b<<endl;
            sol++;
            int a = heap2[0]->a;
            int b = heap2[0]->b;
            deleteRoot(heap2, n2);
            if(b<n){
                insertNode(heap2, n2, a*a*a+((b+1)*(b+1)*(b+1)*(b+1)), a, b+1);
            }
            a = heap1[0]->a;
            b = heap1[0]->b;
            deleteRoot(heap1, n1);
            if(b<n){
                insertNode(heap1, n1, a+((b+1)*(b+1)), a, b+1);
            }
        }
    }
    
    cout<<"Total number of solutions = "<<sol<<endl;
}
