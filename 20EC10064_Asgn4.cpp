
//Submitted by Raghav Aggarwal (20EC10064)

#include <iostream>

using namespace std;

void algo1(int n,int l[],int d[]){
    int min = 0;
    while(1){
        int t[n];
        int flag=0;
        for (int i=0; i<n; i++){
            t[i] = d[i]+min-l[i];
            if(t[i]<0){
                flag=1;
                break;
            }
        }
        int time=0;
        if(flag==0){
            int sch[n];
            for(int i=0; i<n; i++){
                int minx = INT_MAX;
                int k = 0;
                for(int j=0; j<n; j++){
                    if(t[j]>-1&&t[j]<minx){
                        k = j;
                        minx = t[j];
                    }
                }
                if(time>t[k]){
                    flag=1;
                    break;
                }
                time += l[k];
                t[k] = -1;
                sch[i] = k;
            }
            if(flag == 0){
                cout<<endl<<"By algorithm 1 : "<<endl<<"schedule : ";
                for (int i=0; i<n; i++) {
                    cout<<sch[i]+1<<" ";
                }
                cout<<endl;
                return;
            }
        }
        min++;
    }
}

void heapify(int sch[], int n, int i, int d[])
{
    int largest = i;
    int l = 2*i+1, r =2*i+2;
    
    if (l<n && d[sch[l]]>d[sch[largest]])
        largest = l;
  
    if (r<n && d[sch[r]]>d[sch[largest]])
        largest = r;
  
    if (largest != i) {
        swap(sch[i],sch[largest]);
        heapify(sch, n, largest,d);
    }
}

void algo2(int d[],int l[], int n){
    int sch[n];
    for (int i=0; i<n; i++) {
        sch[i] = i;
    }
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(sch, n, i, d);
    
    for (int i = n - 1; i >= 0; i--) {
        swap(sch[0], sch[i]);
        heapify(sch, i, 0,d);
    }
    int min = 0,t=0;
    for (int i =0; i<n; i++) {
        if(t + l[sch[i]] - d[sch[i]]>min){
            min = t + l[sch[i]] - d[sch[i]];
        }
        t+=l[sch[i]];
    }
    cout<<endl<<"By algorithm 2 : "<<endl<<"schedule : ";
    for (int i=0; i<n; i++) {
        cout<<sch[i]+1<<" ";
    }
    cout<<endl;
}


int main(){
    int n;
    cout<<"n = ";
    cin>>n;
    int l[n],d[n];
    cout<<"lengths : ";
    for(int i=0;i<n;i++){
        cin>>l[i];
    }
    cout<<"deadlines : ";
    for(int i=0;i<n;i++){
        cin>>d[i];
    }
    algo1(n, l, d);
    algo2(d, l, n);
}


//10 1 2 4 2 2 3 1 1 1 1 4 9 1 7 3 10 6 2 8 5
