/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

int height_1(SymNode* root){
    if(root == NULL){
        return -1;
    }else{
        return root->height;
    }
}

SymNode::SymNode(){}

SymNode::SymNode(string k){
    this->key = k;
    this->height =0;
    this->par = NULL;
    this->left = NULL;
    this->right = NULL;
}

SymNode* SymNode::LeftLeftRotation(){
    
    SymNode* a = this->right;
    if(this->par !=NULL){
        if(this->par->left == this){
            this->par->left = a;
        }else{
            this->par->right =a;
        }
    }
    a->par = this->par;
    if(a->left !=NULL){
        a->left->par = this; 
    }
    this->right = a->left;
    a->left = this;
    this->par = a;
    this->height = 1+max(height_1(this->left),height_1(this->right)) ;
    a->height = 1+max(height_1(a->left),height_1(a->right));
    return a;
}

SymNode* SymNode::RightRightRotation(){
    SymNode* a = this->left;
    if(this->par !=NULL){
        if(this->par->left == this){
            this->par->left =a;
        }else{
            this->par->right = a;
        }
    };
    a->par = this->par;
    if(a->right !=NULL){
        a->right->par = this;
    }
    this->left = a->right;
    a->right = this;
    this->par = a;
    this->height = 1+max(height_1(this->left),height_1(this->right)) ;
    a->height = 1+max(height_1(a->left),height_1(a->right));
    return a;
}

SymNode* SymNode::RightLeftRotation(){
    SymNode* a = this->left;
    SymNode* d = a->right;
    if(this->par!=NULL){
        if(this->par->left == this){
            this->par->left = d;
        }else{
            this->par->right -d;
        }
    }
    d->par = this->par;
    if(d->right !=NULL){
        d->right->par = this;
    }
    this->left = d->right;
    if(d->left !=NULL){
        d->left->par =a;
    }
    a->right = d->left;
    d->left =a;
    a->par =d;
    d->right = this;
    this->par =d;
    this->height = 1+max(height_1(this->left),height_1(this->right));
    
    a->height = 1+max(height_1(a->left),height_1(a->right));
    d->height = 1+max(height_1(d->left),height_1(d->right));
    return d;
}

SymNode* SymNode::LeftRightRotation(){
    SymNode* a = this->right;
    SymNode* d = a->left;
    if(this->par!=NULL){
        if(this->par->left == this){
            this->par->left =d;
        }else{
            this->par->right = d;
        }
    }
    d->par = this->par;
    if(d->right != NULL){
        d->right->par =a;
    }
    a->left = d->right;
    if(d->left !=NULL){
        d->left->par =this;
    }
    this->right = d->left;
    this->par = d;
    d->left = this;
    a->par = d;
    d->right = a;
    this->height = 1+max(height_1(this->left),height_1(this->right));
    
    a->height = 1+max(height_1(a->left),height_1(a->right));
    d->height = 1+max(height_1(d->left),height_1(d->right));
    return d;
}

SymNode::~SymNode(){
    delete par;
    delete left;
    delete right;// Ask if I have to first set it to NULL.
}