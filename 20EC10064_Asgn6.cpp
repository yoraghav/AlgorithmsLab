
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

void preorder(Node* root){
    if(root == NULL){
        return;
    }
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}

Node* search(Node*root, int val){
    if(root == NULL){return root;}
    if(root->data == val){
        return root;
    }
    if(val<root->data){return search(root->left,val);}
    return search(root->right,val);
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

Node* removenode(Node* root, int val){
    if(val<root->data){
        root->left = removenode(root->left, val);
    }
    else if(val>root->data){
        root->right = removenode(root->right, val);
    }
    else{
        if(root->left == NULL){
            Node* temp = root->right;
            free(root);
            return temp;
        }
        if(root->right == NULL){
            Node* temp = root->left;
            free(root);
            return temp;
        }
    }
    return root;
}

void exchangenode(Node* root){
    if(root==NULL){return;}
    if(root->left == NULL && root->right == NULL){
        removenode(root,root->data);
        return;
    }
    if(root->left==NULL){
        Node* exchange = root->right;
        while(exchange->left != NULL){exchange = exchange->left;}
        int a =exchange->data;
        removenode(root,a);
        root->data = a;
        
        return;
    }
    Node* exchange = root->left;
    while(exchange->right != NULL){exchange = exchange->right;}
    int a = exchange->data;
    removenode(root,a);
    root->data = a;
    return;
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

int unitree(Node* root,int arr[], int i){
    if (root==NULL){
        return i;
    }
    i = unitree(root->left, arr,i);
    arr[i] = root->data;
    i++;
    return unitree(root->right,arr,i);
}

Node* buldingtree(int* arr,int start,int end){
    if (start > end)
        return NULL;
 
    int mid = (start + end)/2;
    Node *root = new Node(arr[mid]);
 
    root->left  = buldingtree(arr, start, mid-1);
    root->right = buldingtree(arr, mid+1, end);
 
    return root;
}

Node* fastbalancing(Node* root){
    int arr[1000];
    int n = unitree(root, arr, 0);
    return buldingtree(arr, 0, n-1);
}





int main(){
    Node* root = NULL;
    
    cout<<"1. insert"<<endl<<"2. delete"<<endl<<"3. make tree balanced (AVL tree based method)."<<endl<<"4. make tree balanced faster"<<endl<<"5. exit";
    //Node* root = NULL;
    int i = 0;
    cin>>i;
    int k;
    cout<<"Write key to be inserted: ";
    cin>>k;
    root = insert(root,k);
    cout<<endl<<"Pre-order traversal: ";
    preorder(root);
    
    while(i!=5){
        cin>>i;
        if(i==1){
            int k;
            cout<<"Write key to be inserted: ";
            cin>>k;
            insert(root,k);
            cout<<endl<<"Pre-order traversal: ";
            preorder(root);
            
        }
        else if(i==2){
            int k;
            cout<<"Write key to be deleted: ";
            cin>>k;
            exchangenode(search(root,k));
            cout<<endl<<"Pre-order traversal: ";
            preorder(root);
        }
        else if(i==3){
            root = AVLbalancing(root);
            cout<<endl<<"Pre-order traversal of tree after balancing with AVL tree based method: ";
            preorder(root);
        }
        else if(i==4){
            root = fastbalancing(root);
            cout<<endl<<"Pre-order traversal of tree after balancing with faster method: ";
            preorder(root);
        }
    }
}
