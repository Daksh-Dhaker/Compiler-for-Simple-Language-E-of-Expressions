/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    this->output_file = out_file;
    this->memory_size = mem_limit;
    for(int i=mem_limit-1;i>=0;i--){
        this->mem_loc.push_back(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    for(int i=0;i<code.size();i++){
        if(code[i][0]=="del"){
            int mem = targ.symtable->search(code[i][2]);
            if(mem !=-2){
                mem_loc.push_back(mem);
                targ.parse(code[i]);
                vector<string> ans = this->generate_targ_commands();
                this->write_to_file(ans);
            }else{
                targ.parse(code[i]);
                vector<string> ans;
                ans.push_back("DEL = mem[-2]");
                this->write_to_file(ans);
            }
        }else if(code[i][0] == "ret"){
            targ.parse(code[i]);
            vector<string> ans = this->generate_targ_commands();
            this->write_to_file(ans);
        }else{
            int idx = targ.symtable->search(code[i][0]);
            if(idx ==-2){
                int mem = mem_loc.back();
                mem_loc.pop_back();
                targ.parse(code[i]);
                targ.symtable->assign_address(code[i][0],mem);
                vector<string> ans = this->generate_targ_commands();
                this->write_to_file(ans);
            }else{
                targ.parse(code[i]);
                vector<string> ans = this->generate_targ_commands();
                this->write_to_file(ans);
            }
        }    
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    if(targ.expr_trees.back()->left->type == "DEL"){
        int mem = mem_loc.back();
        string s = "DEL = mem["+to_string(mem)+"]";
        vector<string> ans;
        ans.push_back(s);
        return ans;
    }else{
        ExprTreeNode* root = targ.expr_trees.back();
        ExprTreeNode* exp = root->right;
        vector<ExprTreeNode*> st1;
        vector<ExprTreeNode*> st2;
        st1.push_back(exp);
        ExprTreeNode* curr;
        while(!st1.empty()){
            curr = st1.back();
            st1.pop_back();
            st2.push_back(curr);

            if(curr->right !=NULL){
                st1.push_back(curr->right);
            }
            if(curr->left !=NULL){
                st1.push_back(curr->left);
            }
        }

        vector<string> ans;
        while(!st2.empty()){
            curr = st2.back();
            st2.pop_back();
            if(curr->type == "ADD"){
                ans.push_back("ADD");
            }else if(curr->type == "SUB"){
                ans.push_back("SUB");
            }else if(curr->type == "MUL"){
                ans.push_back("MUL");
            }else if(curr->type == "DIV"){
                ans.push_back("DIV");
            }else if(curr->type == "VAL"){
                string s = "PUSH "+to_string(curr->num);
                ans.push_back(s);
            }else{
                int mem = targ.symtable->search(curr->id);
                string s = "PUSH mem["+to_string(mem)+"]";
                ans.push_back(s);
            }
        }
        if(targ.expr_trees.back()->left->type == "RET"){
            ans.push_back("RET = POP");
        }else{
            int mem = targ.symtable->search(targ.expr_trees.back()->left->id);
            string s = "mem["+to_string(mem)+"] = POP";
            ans.push_back(s);
        }
        return ans;
    }
}

void EPPCompiler::write_to_file(vector<string> commands){
    fstream out_file;
    out_file.open(this->output_file,ios::app);
    if(out_file.is_open()){
        for(int i=0;i<commands.size();i++){
            out_file<<commands[i]<<endl;
        }
        out_file.close();
    } 
}

EPPCompiler::~EPPCompiler(){}