/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){}

ExprTreeNode::ExprTreeNode(string t,int v){
    int j=0;
    int i;
    if(t[0]=='-'){
        j++;
    }
    if(t[0]=='+'){
        j++;
    }
    for(i=j;i<t.size();i++){
        if(t[i]-'0' <0 || t[i]-'0' >9){
            break;
        }
    }
    this->left = NULL;
    this->right = NULL;
    if(t == "+"){
        this->type = "ADD";
    }else if(t=="-"){
        this->type = "SUB";
    }else if(t=="*"){
        this->type = "MUL";
    }else if(t=="/"){
        this->type = "DIV";
    }else if(t=="del"){
        this->type = "DEL";
    }else if(t == "ret"){
        this->type = "RET";
    }else{
        if(i == t.size()){
            this->type = "VAL";
            this->num = v;
        }else{
            this->type = "VAR";
            this->id = t;
            this->num = v;
        }
    }
}

ExprTreeNode::~ExprTreeNode(){
    delete left;
    delete right;
}