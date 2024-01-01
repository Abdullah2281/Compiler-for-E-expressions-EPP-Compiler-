/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){
    key = "";
    height = -1;
    address = -1;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode::SymNode(string k){
    key = k;
    height = 0;
    address = -1;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode* SymNode::LeftLeftRotation(){
    return NULL;
}

SymNode* SymNode::RightRightRotation(){
    return NULL;
}

SymNode* SymNode::LeftRightRotation(){
    return NULL;
}

SymNode* SymNode::RightLeftRotation(){
    return NULL;
}

SymNode::~SymNode(){
    // key = "kuch bhi";
    // if (left != NULL) {
    //     delete left;
    //     left = NULL;
    // }
    
    // if (right != NULL) {
    //     delete right;
    //     right = NULL;
    // }
}