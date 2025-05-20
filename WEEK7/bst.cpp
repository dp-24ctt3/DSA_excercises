#include <iostream>
#include <vector>
using namespace std;

struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
};

NODE* Search(NODE* pRoot, int x) {
    if (pRoot) {
        if (pRoot->key == x) return pRoot;
        if (pRoot->key > x) return Search(pRoot->p_left, x);
        return Search(pRoot->p_right, x);
    }
    return nullptr;
}

void Insert(NODE* &pRoot, int x) {
    if (!pRoot) {
        NODE* newNode = new NODE;
        newNode->key = x;
        newNode->p_left = newNode->p_right = nullptr;
        pRoot = newNode;
        return;
    }
    if (pRoot->key > x) Insert(pRoot->p_left, x);
    else if (pRoot->key < x) Insert(pRoot->p_right, x);
    return;
}

void Remove(NODE* &pRoot, int x) {
    if (!pRoot) return;
    if (pRoot->key > x) Remove(pRoot->p_left, x);
    else if (pRoot->key < x) Remove(pRoot->p_right, x);
    else {
        // node has 0 or 1 child
        if (!pRoot->p_left || !pRoot->p_right) {
            NODE* tmp;
            if (pRoot->p_left) tmp = pRoot->p_left;
            else tmp = pRoot->p_right;
            
            // node has 1 child
            if (tmp) {
                *pRoot = *tmp;
            }
            // node has 0 child
            else {
                tmp = pRoot;
                pRoot = nullptr;
            }

            delete tmp;
            return;
        }
        // node has 2 children
        NODE* replace = pRoot->p_left;
        while (replace->p_right) replace = replace->p_right;
        pRoot->key = replace->key;
        Remove(pRoot->p_left, replace->key);
    }
}

NODE* createTree(int a[], int n) {
    NODE* pRoot = nullptr;
    for (int i = 0; i < n; i++) Insert(pRoot, a[i]);
    return pRoot;
} 

void removeTree(NODE* &pRoot) {
    if (pRoot) {
        removeTree(pRoot->p_left);
        removeTree(pRoot->p_right);
        pRoot->p_left = pRoot->p_right = nullptr;
        delete pRoot;
    }
}

int Height(NODE* pRoot) {
    if (pRoot) {
        return 1 + max(Height(pRoot->p_left), Height(pRoot->p_right));
    }
    return -1;
}

int countLess(NODE* pRoot, int x) {
    NODE* node = pRoot;
    while (node && node->key >= x) node = node->p_left;
    if (node) return 1 + countLess(node->p_left, x) + countLess(node->p_right, x);
    return 0;
}

int countGreater(NODE* pRoot, int x) {
    NODE* node = pRoot;
    while (node && node->key <= x) node = node->p_right;
    if (node) return 1 + countGreater(node->p_left, x) + countGreater(node->p_right, x);
    return 0;
}

bool isBST(NODE* pRoot) {
    if (pRoot) {
        if (pRoot->p_left && pRoot->p_left->key > pRoot->key) return false;
        if (pRoot->p_right && pRoot->p_right->key < pRoot->key) return false;
        return isBST(pRoot->p_left) && isBST(pRoot->p_right);
    }
    return true;
}

bool isFullBST(NODE* pRoot) {
    if (pRoot) {
        if (!isBST(pRoot)) return false;
        if (!((pRoot->p_left && pRoot->p_right) || (!pRoot->p_left && !pRoot->p_right))) return false;
        return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
    }
    return true;
}