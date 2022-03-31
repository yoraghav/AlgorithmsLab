/* Raghav Aggarwal
20EC10064
Assignment 1*/

#include <iostream>
#include <vector>

using namespace std;

int method1(int apples,int sizes[],int prices[], int n,int n1){
    int max=0;
    int ans[apples];
    for(int i=n1;i<n;i++){
        if(apples>=sizes[i]){
            int a = method1(apples-sizes[i],sizes,prices,n,n1);
            if(a+sizes[i]*prices[i]>max){
                max = a+sizes[i]*prices[i];
            }
        }
    }
    return max;
}

int method2(int apples,int sizes[],int prices[],int n){
    int maxearn[apples+1];
    int pattern[apples+1];
    for(int i=0;i<apples+1;i++){
        maxearn[i]=0;
        pattern[i]=-1;
        for(int j=0; j<n; j++) {
            if(i>=sizes[j]){
                if(maxearn[i-sizes[j]]+sizes[j]*prices[j]>maxearn[i]){
                    maxearn[i] = maxearn[i-sizes[j]]+sizes[j]*prices[j];
                    pattern[i] = j;
                }
            }
        }
    }
    int k = apples,finalp[n];
    for (int i=0; i<n; i++) {
        finalp[i]=0;
    }
    while(pattern[k]!=-1){
        finalp[pattern[k]]++;
        k-=sizes[pattern[k]];
    }
    cout<<"pattern to sell :";
    for (int i=0; i<n; i++) {
        cout<<finalp[i]*sizes[i]<<" ";
    }
    
    return maxearn[apples];
}



//1000 5 7 11 13 17 19 32 31 34 33 35

int main(){
    int apples,n;
    cout<<"Write the number of apples that Ramu has:";
    cin>>apples;
    cout<<endl<<"Write the number of buyers:";
    cin>>n;
    int sizes[n],prices[n];
    cout<<endl<<"Write family sizes:";
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        sizes[i]=x;
    }
    cout<<endl<<"Write prices:";
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        prices[i]=x;
    }
    

    cout<<endl;
    int m2 = method2(apples, sizes, prices, n);
    cout<<endl<<"Method2 (Dynamic Programming) max earnings :"<<m2;
    
    cout<<endl<<"Method1 (Recursive) max earnings :"<<method1(apples, sizes, prices, n,0)<<endl;
    return 0;
}
