/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

Parser::Parser(){
    this->symtable = new SymbolTable();
}

void Parser::parse(vector<string> expression){
    vector<ExprTreeNode*> tree1;
    
    ExprTreeNode* root = new ExprTreeNode(":=",1);
    ExprTreeNode* symbol = new ExprTreeNode(expression[0],1);
    root->left = symbol;
    
    for(long unsigned int i=2;i<expression.size();i++){
        
        if(expression[i]!=")"){
            if(expression[i]=="("){
                ;
            }
            else if(expression[i]=="+" || expression[i]=="-" || expression[i]=="/" || expression[i]=="*"){
                ExprTreeNode* node = new ExprTreeNode(expression[i],1);
                tree1.push_back(node);
            }else{
                ExprTreeNode* node = new ExprTreeNode(expression[i],1);
                if(node->type == "VAL"){
                    node->num = stoi(expression[i]);
                    tree1.push_back(node);
                }else{
                    tree1.push_back(node);
                }
            }
        }else{
            ExprTreeNode* temp1 = tree1.back();
            tree1.pop_back();
            ExprTreeNode* temp2 = tree1.back();
            tree1.pop_back();
            ExprTreeNode* temp3 = tree1.back();
            tree1.pop_back();
            temp2->right = temp1;
            temp2->left = temp3;
            tree1.push_back(temp2);
            temp1 = NULL;
            temp2 = NULL;
            temp3 = NULL;
            delete temp1;
            delete temp2;
            delete temp3;   
        }
    }
    
    ExprTreeNode* exp = tree1.back();
    tree1.pop_back();
    root->right = exp;
    expr_trees.push_back(root);
    if(expression[0]=="del"){
        int idx = this->symtable->search(expression[2]);
        if(idx!=-2){
            this->symtable->remove(expression[2]);
        }
    }else if(expression[0]=="ret"){
        ;
    }else{
        int idx = this->symtable->search(expression[0]);
        if(idx ==-2){
            this->symtable->insert(expression[0]);
        }else{
            ;
        }
    }
        
    exp = NULL;
    delete exp;
    root = NULL;
    delete root;
    symbol = NULL;
    delete symbol;
    
}

Parser::~Parser(){
    delete symtable;
}