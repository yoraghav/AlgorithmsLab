
//Submitted by Raghav Aggarwal (20EC10064)

#include <iostream>

using namespace std;

bool possible(string s,char m[],char sauce){
    if(s.empty()){return 1;}
    if(s.length()==1){if(s[0]==sauce){return 1;}return 0;}
    
    for(int i=0;i<25;i++){
        if(m[i]==sauce){
            
            char first = '1' + (i/5);
            char second = '1' + (i%5);
            
            string firstpart;
            for(int j=0;j<s.length()-1;j++){
                firstpart += s[j];
                string secondpart = &s[j+1];
                if(possible(firstpart, m, first) && possible(secondpart, m, second)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

int countways(string s,char m[],char sauce){
    
    if(s.empty()){return 0;}
    if(s.length()==1){if(s[0]==sauce){return 1;}return 0;}
    
    int count =0;
    for(int i=0;i<25;i++){
        if(m[i]==sauce){
            
            char first = char('1' + (i/5));
            char second = char('1' + (i%5));
            
            string firstpart = "";
            
            for(int j=0;j<s.length()-1;j++){
                firstpart += s[j];             
                string secondpart = &s[j+1];
                count += (countways(firstpart, m, first) * countways(secondpart, m, second));
                
            }
        }
    }
    return count;
}

int main(){
    cout<<"Enter M : "<<endl;
    char M[25];
    for(int i=0;i<25;i++){
        cin>>M[i];
    }
    cout<<"Enter string : ";
    string s;
    cin>>s;
    for(int i=1;i<6;i++){
        cout<<i<<" : "<<(possible(s,M,('0'+i))?"possible ":"not possible ")<<countways(s, M,       '0'+i)<<endl;
    }
    
}


//13435 42531 25312 31514 42425 31442
     
//25304
