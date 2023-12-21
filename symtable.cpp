/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

int height(SymNode* root){
    if(root == NULL){
        return -1;
    }else{
        return root->height;
    }
}

int balance_factor(SymNode* root){
    if(root == NULL){
        return 0;
    }else{
        return height(root->left)-height(root->right);
    }
}

SymNode* successor(SymNode* temp){
    SymNode* curr_node = temp;
    while(curr_node->left !=NULL){
        curr_node = curr_node->left;
    }
    return curr_node;
}

SymNode* insert_helper(SymNode* &root,string k){
    if(root == NULL){
        return new SymNode(k);
    }

    if(k < root->key){
        SymNode* n = insert_helper(root->left,k);
        n->par = root;
        root->left = n;
    }else if(k > root->key){
        SymNode* n = insert_helper(root->right,k);
        n->par = root;
        root->right = n;
    }else{
        return root;
    }
    
    root->height = 1+max(height(root->left),height(root->right));
    
    int bal_fact = balance_factor(root);

    if(bal_fact < -1 && k > root->right->key){
        //cout<<"LL"<<endl;
        return root->LeftLeftRotation();
    }
    if(bal_fact > 1 && k < root->left->key){
        //cout<<"RR"<<endl;
        return root->RightRightRotation();
    }
    if(bal_fact > 1 && k > root->left->key){
        //cout<<"RL"<<endl;
        return root->RightLeftRotation();
    }
    if(bal_fact < -1 && k < root->right->key){
        //cout<<"LR"<<endl;
        return root->LeftRightRotation();
    }

    return root;
}

SymNode* delete_helper(SymNode* &root,string k){
    if(root == NULL){
        return root;
    }
    if(k < root->key){
        SymNode* n = delete_helper(root->left,k);
        if(n !=NULL){
        n->par = root;
        }
        root->left = n;
    }else if(k > root->key){
        SymNode* n = delete_helper(root->right,k);
        if(n!=NULL){
        n->par = root;
        }
        root->right = n;
    }else{
        if(root->left == NULL || root->right == NULL){
            SymNode* child;
            if(root->left !=NULL){
                child = root->left;
            }else{
                child = root->right;
            }
            if(child == NULL){
                child = root;
                root = NULL;
            }else{
                *root = *child;
                free(child);
            }
            
        }else{
            SymNode* temp = successor(root->right);
            root->key = temp->key;
            root->address = temp->address;
            
            SymNode* ans = delete_helper(root->right,temp->key);
            
            root->right = ans;
            if(ans!=NULL){
            ans->par = root;
            }
            
        }
    }
    if(root == NULL){
        return root;
    }
    
    root->height = max(height(root->left),height(root->right))+1;
    //cout<<root->key<<" "<<root->height<<endl;
    int bal_fact = balance_factor(root);

    if(bal_fact > 1 && balance_factor(root->left) >=0){
        //cout<<"RR"<<endl;
        return root->RightRightRotation();
    }
    if(bal_fact > 1 && balance_factor(root->left)<0){
        //cout<<"RL"<<endl;
        return root->RightLeftRotation();
    }
    if(bal_fact <-1 && balance_factor(root->right) <=0){
        //cout<<"LL"<<endl;
        return root->LeftLeftRotation();
    }
    if(bal_fact <-1 && balance_factor(root->right) >0){
        //cout<<"LR"<<endl;
        return root->LeftRightRotation();
    }

    return root;
}

SymbolTable::SymbolTable(){
    this->size =0;
    this->root = NULL;
}

void SymbolTable::insert(string k){
    this->root = insert_helper(this->root,k);
    this->size++;
    return;
}

void SymbolTable::remove(string k){
    this->root = delete_helper(this->root,k);
    this->size--;
    return;
}

int SymbolTable::search(string k){
    SymNode* temp = root;
    while(temp!=NULL && temp->key!=k){
        if(temp->key >= k){
            temp = temp->left;
        }else{
            temp = temp->right;
        }
    }
    if(temp == NULL){
        return -2;
    }
    return temp->address;
}

void SymbolTable::assign_address(string k,int idx){
    SymNode* temp = root;
    while(temp!=NULL && temp->key!=k){
        if(temp->key >= k){
            temp = temp->left;
        }else{
            temp = temp->right;
        }
    }
    if(temp!=NULL){
        temp->address = idx;
    }
    return;
}

int SymbolTable::get_size(){
    return this->size;
}

SymNode* SymbolTable::get_root(){
    return this->root;
}

SymbolTable::~SymbolTable(){
    delete root;
}