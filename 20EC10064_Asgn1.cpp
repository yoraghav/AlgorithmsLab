/* Raghav Aggarwal
20EC10064
Assignment 1*/

#include <iostream>
#include <vector>

using namespace std;
/*
class stack{
    int* arr;
    int top;
    
    public:
    stack(int n){
        arr = new int[n];
        top = -1;
        
    }
    
    void push(int x){
        if(top == n-1){
            return;
        }
        top++;
        arr[top] = x;
    }
    void pop(int x){
        if(top == -1){return;}
        top--;
    }
    int Top(){
        if(top == -1){return -1;}
        return arr[top];
    }
    bool empty(){
        return top==-1;
    }
};
*/
int algo0(int *arr, int n){
    int a,b,c;
    for (a=1; a<n-1; a++) {
       for (b=a+1; b<n; b++) {
          for (c=b+1; c<=n; c++) {
             int i,j,k;
             for (int l=0; l<n; l++) {
                if (arr[l]==a){i=l;}
                else if(arr[l]==b){j=l;}
                else if(arr[l]==c){k=l;}
             }
             if((i < k) && (k < j)){return 0;}
          }
       }
    }
    return 1;
}

int algo1(int *arr,int n){
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            for (int k=j+1; k<n; k++) {
                if(arr[j]>arr[k]&&arr[j]>arr[i]&&arr[k]>arr[i]){return 0;}
            }
        }
    }
    return 1;
}

int algo2(int *arr, int n )
{
    for (int i=0; i<n; i++) {
        int x=0;
        for (int j=i+1; j<n; j++) {
            if(arr[j]>arr[i]){
                if(arr[j]<x){
                    return 0;
                }
                x = arr[j];
            }
        }
    }
   return 1;
}

int algo3(int *arr, int n){
    vector<int> vec;
    int a=1;
    for(int i=0;i<n;i++){
        while (a <= arr[i]) {
            vec.push_back(a);
            a++;
        }
        if (vec.size() == 0) return 0;
        if (vec[vec[(vec.size()-1)]] != arr[i]) return 0;
        vec.pop_back();
    }
    return 1;
}

int main ( int argc, char *argv[] )
{
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout<<endl;
    cout<<"Method 0: "<<(algo0(arr,n) ? "Musical" : "Unmusical")<<endl;
    cout<<"Method 1: "<<(algo1(arr,n) ? "Musical" : "Unmusical")<<endl;
    cout<<"Method 2: "<<(algo2(arr,n) ? "Musical" : "Unmusical")<<endl;
    cout<<"Method 3: "<<(algo3(arr,n) ? "Musical" : "Unmusical")<<endl;
}
