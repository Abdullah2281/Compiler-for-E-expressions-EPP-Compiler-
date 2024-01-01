/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){

}

bool isDig(const std::string s) {
    if (!s.empty()) {
        char firstChar = s[0];
        if ((firstChar >= '0' && firstChar <= '9') || firstChar == '-') {
            return true;
        }
    }
    return false;
}

void postorder(ExprTreeNode* root, vector<string>& ans) {
    if(root == NULL) {
        return;
    }
    postorder(root->right, ans);
    postorder(root->left, ans);
    if(root->type == "VAR") {
        ans.push_back(root->id);
    }
    if(root->type == "VAL") {
        ans.push_back(std::to_string(root->num));
    }
    if(root->type=="ADD" || root->type=="SUB" || root->type=="MUL" || root->type=="DIV") {
        ans.push_back(root->type);
    }
}


EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    output_file = out_file;
    memory_size = mem_limit;
    for (int i = 0; i <= mem_limit; i++) {
        mem_loc.push_back(mem_limit-i);
    }
}


void EPPCompiler::compile(vector<vector<string>> code){
    std::ofstream outputFile(output_file);

    for(vector<string> v:code) {
        targ.parse(v);
        vector<string> temp = generate_targ_commands();
        write_to_file(temp);
    }
}


vector<string> EPPCompiler::generate_targ_commands() {
    vector<string> write;

        if(targ.expr_trees.back()->left->type == "DEL") {
            int index = mem_loc.size();
            for (int i = 0; i < mem_loc.size(); ++i) {
                if (targ.last_deleted > mem_loc[i]) {
                    index = i;
                    break;
                }
            }
            mem_loc.insert(mem_loc.begin() + index, targ.last_deleted);
            string temp = "DEL = mem[" + std::to_string(targ.last_deleted) + "]";
            write.push_back(temp);
            return write;
        }

        if(targ.expr_trees.back()->left->type == "RET") {
        vector<string> ans;
        postorder(targ.expr_trees.back()->right, ans);
        for(int i=0; i<ans.size(); i++) {
        if(isDig(ans[i])) {
            string temp = "PUSH " + ans[i];
            write.push_back(temp);
        }
        else if(ans[i] == "ADD") {
            write.push_back("ADD");
        }
        else if(ans[i] == "SUB") {
            write.push_back("SUB");
        }
        else if(ans[i] == "MUL") {
            write.push_back("MUL");
        }
        else if(ans[i] == "DIV") {
            write.push_back("DIV");
        }
        else {
            int address = targ.symtable->search(ans[i]);
            string temp = "PUSH mem[" + std::to_string(address) + "]";
            write.push_back(temp);
            }
        }
        write.push_back("RET = POP");
        return write;
        }
        
        //variable
        vector<string> ans;
        postorder(targ.expr_trees.back()->right, ans);
        // for(string i:ans){
        //     printf("%s ",i.c_str());
        // }
        // printf("\n");
        for(int i=0; i<ans.size(); i++) {
        if(isDig(ans[i])) {
            string temp = "PUSH " + ans[i];
            write.push_back(temp);
        }
        else if(ans[i] == "ADD") {
            write.push_back("ADD");
        }
        else if(ans[i] == "SUB") {
            write.push_back("SUB");
        }
        else if(ans[i] == "MUL") {
            write.push_back("MUL");
        }
        else if(ans[i] == "DIV") {
            write.push_back("DIV");
        }
        else {
            // printf("%s   search \n",ans[i].c_str());
            int address = targ.symtable->search(ans[i]);
            string temp = "PUSH mem[" + std::to_string(address) + "]";
            write.push_back(temp);
            }
        }
        int address = targ.symtable->search(targ.expr_trees.back()->left->id);
        if(address == -2) {
            targ.symtable->insert(targ.expr_trees.back()->left->id);
            mem_loc.pop_back();
            int idx = memory_size - mem_loc.size();
            targ.symtable->assign_address(targ.expr_trees.back()->left->id, idx);
            string temp = "mem[";
            temp += std::to_string(targ.symtable->search(targ.expr_trees.back()->left->id));
            temp += "] = POP";
            write.push_back(temp);
        }

        else if(address == -1) {
            mem_loc.pop_back();
            int idx = memory_size - mem_loc.size();
            targ.symtable->assign_address(targ.expr_trees.back()->left->id, idx);
            string temp = "mem[";
            temp += std::to_string(targ.symtable->search(targ.expr_trees.back()->left->id));
            temp += "] = POP";
            write.push_back(temp);
        }
        else {
            string temp = "mem[";
            temp += std::to_string(address);
            temp += "] = POP";
            write.push_back(temp);
        }
        return write;
}


void EPPCompiler::write_to_file(vector<string> commands) {
    ofstream outputFile;
    outputFile.open(output_file,ios::app);
    // Check if opened
    if (!outputFile.is_open()) {
        return;
    }
        for (const std::string& line : commands) {
                outputFile << line << std::endl;
            }
    outputFile.close();
    }


EPPCompiler::~EPPCompiler() {

}