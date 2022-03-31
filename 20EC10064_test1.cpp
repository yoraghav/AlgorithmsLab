
//Submitted by Raghav Aggarwal (20EC10064)

#include <iostream>

using namespace std;

int main(){
    
    // Taking input from the user
    
    cout<<"Write the number of objects: ";
    int n;
    cin>>n;
    cout<<"Write the start and end angles of 5 objects :"<<endl;
    int start[n],end[n],startcopy[n],endcopy[n];
    for(int i=0;i<n;i++){
        cout<<"Start : ";
        cin>>start[i];
        startcopy[i] = start[i]; // creating copy of start angle array for sorting later
        cout<<"End : ";
        cin>>end[i];
        endcopy[i] = end[i]; // creating copy of end angle array for sorting later
        cout<<endl;
    }
    
    //now we sort the objects on the basis of start angles and end angles separetely and instead of shuffling the actual values store them as indices in new arrays
    
    int startsort[n],endsort[n];
    int x = 361;
    
    for(int i=0;i<n;i++){        //sorting on the basis of start entry.
        int mini=0;
        x = 361;
        for(int j=0;j<n;j++){
            if(startcopy[j]>0&&startcopy[j]<x){
                x = startcopy[j];
                mini = j;
            }
        }
        startcopy[mini] = -1;
        startsort[i] = mini;
    }
    
    for(int i=0;i<n;i++){
        int mini=0;
        x = 361;
        for(int j=0;j<n;j++){       //sorting on the basis of end entry.
            
            if(endcopy[j]>0&&endcopy[j]<x){
                x = endcopy[j];
                mini = j;
            }
        }
        endcopy[mini] = -1;
        endsort[i] = mini;
    }
    
    // Now to simplify we are going to remove the objects which completely overlap one or more than one objects since the count of these objects can be taken by the objects they compeletly overlap. We will do this by creating a validity array which will store if the object has to be taken for further calculations or not.
    
    //But there are cases in which the end point is smaller than the starting point i.e. the points which have 0 degrees in their domain [lets call them "overturn cases" ]. For handling them we consider these objects once by subtracting 360 from the starting point and then by adding 360 to the End point of these cases.
    
    int valid[n];
    for(int i=0;i<n;i++){
        valid[i] = 1;
    }
    
    for(int i=0;i<n;i++){
        if(start[i]>end[i]){
            end[i]+=360;     // By adding 360 to end point
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i!=j&&start[i]<=start[j]&&end[i]>=end[j]&&valid[j]==1){
                valid[i] = 0;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(end[i]>=360){
            end[i]-=360;    // By subtracting 360 from the starting point
            start[i] -= 360;
        }
    }
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i!=j&&start[i]<=start[j]&&end[i]>=end[j]&&valid[j]==1){
                valid[i] = 0;
            }
        }
    }
    
    for(int i=0;i<n;i++){
        if(start[i]<0){
            start[i] += 360;   //Normalising back to initial entries
        }
    }
    
    //Now we select the valid objects based on the first starting angle and then calculate the other objects which can be account using greedy algorithm. Again for this we will store them in an array which will have a +1 for the indices of objects selected.
    
    int selectedstart[n];
    for(int i=0;i<n;i++){
        selectedstart[i] = -1;
    }
    
    int endpt =0,startpt = -1;
    for(int i=0;i<n;i++){
        while(i<n&&!valid[startsort[i]]){
            i++;
        }
        if(start[startsort[i]]>endpt){
            if(start[startsort[i]]>=end[startsort[i]] && end[startsort[i]]>startpt){
                continue;
            }
            else{
                selectedstart[startsort[i]] = 1;
                endpt = end[startsort[i]];
                if(startpt == -1){
                    startpt = start[startsort[i]];
                }
            }
            
        }
    }
    
    //But in the above selection the first startpoint valid entry was considered which might not always be the case since the object's angle intervals lie in a circular fashion. Hence we now take the entry with the lowest endpoint and if it is a case of overturning( startpoint > ending point ), we will perform the object selection process once again taking the valid lowest endpoint entry as the first case.
    
    int i=0;
    while(!valid[endsort[i]]){i++;}    //going to the first valid endpoint entry.
    int j=0;
    while(!valid[endsort[j]]){j++;}    //going to the first valid startpoint entry.
    
    int selectedend[n];
    for(int i=0;i<n;i++){
        selectedend[i] = -1;
    }
    
    if(end[endsort[i]]<start[endsort[i]]&&end[endsort[i]]>start[startsort[j]]){     //comparing
        selectedend[endsort[i]] = 1;
        int endpt = start[endsort[i]] ,startpt = end[endsort[i]];
        for(int i=0;i<n;i++){
            while(i<n&&!valid[startsort[i]]){
                i++;
            }
            if(start[startsort[i]]>endpt){
                if(end[startsort[i]]>=startpt){
                    continue;
                }
                else{
                    selectedend[startsort[i]] = 1;
                    endpt = end[startsort[i]];
                    if(startpt == -1){
                        startpt = start[startsort[i]];
                    }
                }
                
            }
        }
    }
    
    
    int c1=0,c2=0;
    for(int i=0;i<n;i++){        //calculating the count of objects obtained from both the cases.
        if(selectedstart[i]>0){
            c1++;
        }
        if(selectedend[i]>0){
            c2++;
        }
    }
    
    cout<<"Objects selected : "<<endl;
    if(c1>c2){
        for(int i=0;i<n;i++){
            if(selectedstart[i]>0){
                cout<<"Start : "<<start[i]<<"   End : "<<end[i]<<endl;
            }
        }
    }
    else{
        for(int i=0;i<n;i++){
            if(selectedend[i]>0){
                cout<<"Start : "<<start[i]<<"   End : "<<" "<<end[i]<<endl;
            }
        }
    }
    
}

//5 350 30 40 50 20 80 70 100 90 110

