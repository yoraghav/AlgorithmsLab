
//Submitted by Raghav Aggarwal (20EC10064)

#include <iostream>

using namespace std;

struct Node{
    int data;
    Node *left,*right;
    Node(int val){
        data = val;
        left = NULL;
        right = NULL;
    }
};

Node* insert(Node *root,int val){
    if(root == NULL){
        return new Node(val);
    }
    if(val < root ->data){
        root -> left = insert(root->left, val);
    }
    else{
        root->right = insert(root->right,val);
    }
    return root;
}

int height(Node* root){
    if(root == NULL){return 0;}
    return max(height(root->left),height(root->right))+1;
}

bool balanced(Node* root){
    if(root==NULL){return 1;}
    if(abs(height(root->left)-height(root->right))>1){return 0;}
    return 1;
}

Node* AVLbalancing(Node* root){
    if(balanced(root)){return root;}
    if(height(root->left)>height(root->right)){
        Node* exchangeright = root->left->right;
        Node* top = root;
        root = root->left;
        root->right = top;
        root->right->left = exchangeright;
        root->right = AVLbalancing(root->right);
        root->left = AVLbalancing(root->left);
        return root;
    }
    Node* exchangeleft = root->right->left;
    Node* top = root;
    root = root->right;
    root->left = top;
    root->left->right = exchangeleft;
    root->right = AVLbalancing(root->right);
    root->left = AVLbalancing(root->left);
    return root;
}

void printdescending(Node* root){
    if(root==NULL){return;}
    printdescending(root->left);
    cout<<root->data<<" ";
    printdescending(root->right);
}

void printascending(Node* root){
    if(root==NULL){return;}
    printascending(root->right);
    cout<<root->data<<" ";
    printascending(root->left);
}

void swap(int arr[],int i, int j){
    int y = arr[i];
    arr[i] = arr[j];
    arr[j] = y;
}

void minheapify(int arr[], int n, int i){
    
    int small = i,l = 2*i+1,r = 2*i+2;
    
    if (l<n && arr[l] < arr[small]){small = l;}
    if (r<n && arr[r] < arr[small]){small = r;}
    
    if (small != i){
        swap(arr[i], arr[small]);
        minheapify(arr, n, small);
    }
}

void mindeleteRoot(int arr[], int& n){
    swap(arr[0],arr[n-1]);
    n-=1;
    minheapify(arr, n, 0);
}

void mininsertheapify(int arr[], int n, int i){
    int parent = (i-1) / 2;
    if (arr[parent] > 0) {
        if(arr[i] < arr[parent]) {
            swap(arr[i], arr[parent]);
            mininsertheapify(arr, n, parent);
        }
    }
}

void mininsertNode(int arr[], int& n, int Key){
    n++;
    arr[n-1] = Key;
    mininsertheapify(arr, n, n-1);
}

void maxheapify(int arr[], int n, int i)
{
    int large = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
 
    if (l<n && arr[l] > arr[large])
        large = l;

    if (r<n && arr[r] > arr[large])
        large = r;

    if (large != i) {
        swap(arr[i], arr[large]);
        maxheapify(arr, n, large);
    }
}
void maxinsertheapify(int arr[], int n, int i){
    
    int parent = (i - 1) / 2;
    if (arr[parent] > 0) {
        if (arr[i] > arr[parent]) {
            swap(arr[i], arr[parent]);
            maxinsertheapify(arr, n, parent);
        }
    }
}
 

void maxinsertNode(int arr[], int& n, int Key){
    
    n = n + 1;
    arr[n - 1] = Key;
    maxinsertheapify(arr, n, n - 1);
    
}

void maxdeleteRoot(int arr[], int& n){
    
    int lastElement = arr[n - 1];
    arr[0] = lastElement;
    n = n - 1;
 
    maxheapify(arr, n, 0);
}
 


int main(){
    Node* root = NULL;
    
    cout<<"1. insert"<<endl<<"2. Find Max"<<endl<<"3. Find Min"<<endl<<"4. Find Median"<<endl<<"5. Print in non-decreasing order"<<endl<<"6. exit"<<endl;
    
    int max = INT_MIN,min=INT_MAX;
    int left=0,right=0;
    int leftarr[1000],rightarr[1000];
    int i=0;
    while(i!=6){
        cin>>i;
        if(i==1){
            int k;
            cout<<"Write element to be inserted: ";
            cin>>k;
            root = insert(root,k);
            root = AVLbalancing(root);
            printdescending(root);
            cout<<endl;
            if(k>max){max = k;}
            if(k<min){min = k;}
            
            if(left+right==0){
                leftarr[0] = k;
                left++;
            }
            else if(k>leftarr[0]){
                rightarr[right] = k;
                right++;
                mininsertheapify(rightarr, right, right-1);
                if(right>left){
                    int x = rightarr[0];
                    mindeleteRoot(rightarr, right);
                    maxinsertNode(leftarr,left,x);
                }
            }
            else{
                leftarr[left] = k;
                left++;
                maxinsertheapify(leftarr, left, left-1);
                if(left-right>1){
                    int x = leftarr[0];
                    maxdeleteRoot(leftarr, left);
                    mininsertNode(rightarr,right,x);
                }
            }
        }
        else if(i==2){
            cout<<max<<endl;
        }
        else if(i==3){
            cout<<min<<endl;
        }
        else if(i==4){
            cout<<leftarr[0]<<endl;
        }
        else if(i==5){
            printascending(root);
            cout<<endl;
        }
    }
}

//1 22 1 32 1 54 1 3 1 65 1 33 4
