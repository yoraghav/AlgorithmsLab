
//Submitted by Raghav Aggarwal (20EC10064)

#include <iostream>

using namespace std;

int dist1(int arr[],int n){
    int ans=0;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]>2*arr[j]){ans++;}
        }
    }
    return ans;
}

int dist2(int arr[],int l,int r){
    //handling base cases
    if(r-l+1<2){return 0;}
    if(r==l+1){
        if(arr[l]>2*arr[r]){
            int x = arr[l];
            arr[l] = arr[r];
            arr[r] = x;
            return 1;
        }
        if(arr[l]>arr[r]){
            int x = arr[l];
            arr[l] = arr[r];
            arr[r] = x;
        }
        return 0;
    }
    
    //dividing
    int m = (r+l)/2;
    int b = dist2(arr, m+1, r);
    int a = dist2(arr, l, m);
    int j=m+1;
    int ans=0;
    
    //conquering
    for(int i=l;i<m+1;i++){
        while(j<r+1&&arr[i]>2*arr[j]){
            j++;
        }
        ans += j-m-1;
    }
    int arr2[r-l+1];
    int i=l;
    j=m+1;
    
    //merging
    for(int k=0;k<r-l+1;k++){
        if(i==m+1){
            while(k!=r-l+1){arr2[k++]=arr[j++];}
        }
        else if(j==r+1){
            while(k!=r-l+1){arr2[k++]=arr[i++];}
        }
        else if(arr[i]>arr[j]){
            arr2[k]=arr[j++];
        }
        else{
            arr2[k]=arr[i++];
        }
    }
    for(int k=0;k<r-l+1;k++){
        arr[l+k]=arr2[k];
    }
    
    return (ans+a+b);
}

int main(){
    int n;
    cout<<"n = ";
    cin>>n;
    int arr[n];
    cout<<"Ranking : ";
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout<<"Distance by Method1 : "<<dist1(arr,n)<<"\nDistance by Method2 : "<<dist2(arr,0,n-1)<<endl;
}


//10 4 9 1 7 3 10 6 2 8 5
