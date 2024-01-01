/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICITLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

int height1(SymNode* root) {
    if (root == NULL) {
        return -1;
    }
    return root->height;
}

int getBalance(SymNode* root) {
    if (root == NULL) {
        return 0;
    }
    return height1(root->left) - height1(root->right);
}

SymNode* minValueNode(SymNode* node) {
    SymNode* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

void rotateWithLeftChild(SymNode* &k2) {
    SymNode *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = 1 + max(height1(k2->left), height1(k2->right));
    k1->height = 1 + max(height1(k1->left), k2->height);
    k2 = k1;
}

void rotateWithRightChild(SymNode* &k1) {
    SymNode* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = 1 + max(height1(k1->left), height1(k1->right));
    k2->height = 1 + max(height1(k2->right), k1->height);
    k1 = k2;
}

void doubleWithRightChild(SymNode* &k3) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}

void doubleWithLeftChild(SymNode* &k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

static const int ALLOWED_IMBALANCE = 1;

void balance(SymNode* &t) {
    if (t == NULL)
        return;

    if (height1(t->left) - height1(t->right) > ALLOWED_IMBALANCE) {
        if (height1(t->left->left) >= height1(t->left->right)) {
            rotateWithLeftChild(t);
        }
        else {
            doubleWithLeftChild(t);
        }
    }
    else if (height1(t->right) - height1(t->left) > ALLOWED_IMBALANCE) {
        if (height1(t->right->right) >= height1(t->right->left)) {
            rotateWithRightChild(t);
        }
        else {
            doubleWithRightChild(t);
        }
    }

    t->height = 1 + max(height1(t->left), height1(t->right));
}

void insertUtil(string x, SymNode* &t) {
    if (t == nullptr) {
        t = new SymNode(x);
    }
    else if (x < t->key) {
        insertUtil(x, t->left);
    }
    else if (t->key < x) {
        insertUtil(x, t->right);
    }

    balance(t);
}

void removeUtil(string x, SymNode* &t) {
    if (t == NULL)
        return; // Item not found; do nothing
    if (x < t->key) {
        removeUtil(x, t->left);
    }
    else if (t->key < x) {
        removeUtil(x, t->right);
    }
    else if (t->left != nullptr && t->right != nullptr) // Two children
    {
        t->key = minValueNode(t->right)->key;
        t->address = minValueNode(t->right)->address;
        removeUtil(t->key, t->right);
    }
    else {
        SymNode* oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }

    balance(t);
}

SymbolTable::SymbolTable() {
    root = nullptr;
    size = 0;
}

bool found(SymNode* root, string k) {
    if (root == NULL) {
        return false;
    }
    if (root->key == k) {
        return true;
    } else if (root->key > k) {
        return found(root->left, k);
    }
    return found(root->right, k);
}

void updateHeight(SymNode* root) {
    if (root != nullptr) {
        root->height = 1 + max(height1(root->left), height1(root->right));
    }
}

void SymbolTable::insert(string k) {
    insertUtil(k, root);
    size++;
}

void SymbolTable::remove(string k) {
    if (root == NULL) {
        return;
    }
    removeUtil(k, root);
    size--;
}

int searchHelper(SymNode* root, string k) {
    if (root->key == k) {
        return root->address;
    } else if (root->key > k) {
        return searchHelper(root->left, k);
    }
    return searchHelper(root->right, k);
}

int SymbolTable::search(string k) {
    if (!found(root, k)) {
        return -2;
    } else {
        int ans = searchHelper(root, k);
        return ans;
    }
}

SymNode* assignHelper(SymNode* root, string k) {
    if (k == root->key) {
        return root;
    } else if (root->key > k) {
        return assignHelper(root->left, k);
    }
    return assignHelper(root->right, k);
}

void SymbolTable::assign_address(string k, int idx) {
    SymNode* temp = assignHelper(root, k);
    temp->address = idx;
}

int SymbolTable::get_size() {
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

void baldevDestroyer(SymNode* root) {
    if (root == NULL) {
        return;
    }
    baldevDestroyer(root->left);
    baldevDestroyer(root->right);
    delete root;
}

SymbolTable::~SymbolTable() {
    baldevDestroyer(root);
    size = 0;
    root = nullptr;
}
