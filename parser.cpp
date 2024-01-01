/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

Parser::Parser(){
    symtable = new SymbolTable();
    last_deleted = -1;
}

bool isDigit(const std::string s) {
    if (!s.empty()) {
        char firstChar = s[0];
        if ((firstChar >= '0' && firstChar <= '9') || firstChar == '-') {
            return true;
        }
    }
    return false;
}

ExprTreeNode* parseHelper(vector<string>& expressions, int& idx) {
    if (idx >= expressions.size()) {
        return nullptr;
    }

    string str = expressions[idx];
    idx++;

    ExprTreeNode* node = new ExprTreeNode();

    if (str == "(") {
        node->left = parseHelper(expressions, idx); // Parse left subtree
        if (idx < expressions.size()) {
            if(expressions[idx]=="+") {
            node->type = "ADD";
            idx++;
            node->right = parseHelper(expressions, idx);
            }
            if(expressions[idx]=="-") {
            node->type = "SUB";
            idx++;
            node->right = parseHelper(expressions, idx);
            }
            if(expressions[idx]=="*") {
            node->type = "MUL";
            idx++;
            node->right = parseHelper(expressions, idx);
            }
            if(expressions[idx]=="/") {
            node->type = "DIV";
            idx++;
            node->right = parseHelper(expressions, idx);
            }
        } 
        idx++; // Skip the closing ")"
    } 
    else if (isDigit(str)) {
        node->type = "VAL";
        node->num = stoi(str);
    }
    else {
        node->type = "VAR";
        node->id = str;
    }
    return node;
}

void Parser::parse(vector<string> expression) {
    ExprTreeNode* root = new ExprTreeNode();
    root->type = "EQUAL";
    root->id = expression[1];
    if(expression[0] == "ret") {
        root->left = new ExprTreeNode();
        root->left->type = "RET";
        root->left->id = "ret";
        expression.erase(expression.begin());
        expression.erase(expression.begin());
        int idx = 0;
        root->right = parseHelper(expression, idx);
        expr_trees.push_back(root);
    }
    else if(expression[0] == "del") {
        root->left = new ExprTreeNode();
        root->left->type = "DEL";
        root->left->id = "del";
        root->right = new ExprTreeNode();
        root->right->type = "VAR";
        root->right->id = expression[2];
        last_deleted = symtable->search(root->right->id);
        symtable->remove(root->right->id);
        expr_trees.push_back(root);
    }
    else {
        root->left = new ExprTreeNode();
        root->left->type = "VAR";
        root->left->id = expression[0];
        symtable->insert(root->left->id);
        expression.erase(expression.begin());
        expression.erase(expression.begin());
        int idx = 0;
        root->right = parseHelper(expression, idx);
        expr_trees.push_back(root);
    }

}

Parser::~Parser() {
    if (symtable != NULL) {
        delete symtable;
    }
    for (ExprTreeNode* root : expr_trees) {
        delete root;
    }
    expr_trees.clear();
}