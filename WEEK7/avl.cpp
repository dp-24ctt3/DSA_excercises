#include <iostream>
#include <vector>
using namespace std;

struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};

NODE* createNode(int data) {
    NODE* newNode = new NODE;
    newNode->key = data;
    newNode->p_left = newNode->p_right = nullptr;
    newNode->height = 0;
    return newNode;
}

// Insert & Remove and their supporting functions
int height(NODE* pRoot) {
    if (pRoot) return 1 + max(height(pRoot->p_left), height(pRoot->p_right));
    return -1;
}

int diffHeight(NODE* p) {
    if (p) return height(p->p_left) - height(p->p_right);
    return 0;
}

NODE* rotateLeft(NODE* x) {
    NODE* y = x->p_right;

    x->p_right = y->p_left;
    y->p_left = x;
    x->height = height(x);
    y->height = height(y);

    return y;
}

NODE* rotateRight(NODE* x) {
    NODE* y = x->p_left;

    x->p_left = y->p_right;
    y->p_right = x;
    x->height = height(x);
    y->height = height(y);

    return y;
}

void Insert(NODE* &pRoot, int x) {
    if (!pRoot) {
        NODE* newNode = createNode(x);
        pRoot = newNode;
        return;
    }
    if (pRoot->key < x) Insert(pRoot->p_right, x);
    else if (pRoot->key > x) Insert(pRoot->p_left, x);
    else return;
    
    pRoot->height = height(pRoot);

    // rebalancing

    int diff_height = diffHeight(pRoot);

    // left-left
    if (diff_height > 1 && pRoot->p_left->key > x) {
        pRoot = rotateRight(pRoot);
    }
    // right-right
    if (diff_height < -1 && pRoot->p_right->key < x) {
        pRoot = rotateLeft(pRoot);
    }
    // left-right
    if (diff_height > 1 && pRoot->p_left->key < x) {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        pRoot = rotateRight(pRoot);
    }
    // right-left
    if (diff_height < -1 && pRoot->p_right->key > x) {
        pRoot->p_right = rotateRight(pRoot->p_right);
        pRoot = rotateLeft(pRoot);
    }
}

void Remove(NODE* &pRoot, int x) {
    if (!pRoot) return;
    if (pRoot->key > x) Remove(pRoot->p_left, x);
    else if (pRoot->key < x) Remove(pRoot->p_right, x);
    else {
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

    if (!pRoot) return;
    pRoot->height = height(pRoot);

    // rebalancing

    int diff_height = diffHeight(pRoot);

    // left-left
    if (diff_height > 1 && diffHeight(pRoot->p_left) >= 0) {
        pRoot = rotateRight(pRoot);
    }
    // right-right
    if (diff_height < -1 && diffHeight(pRoot->p_right) <= 0) {
        pRoot = rotateLeft(pRoot);
    }
    // left-right
    if (diff_height > 1 && diffHeight(pRoot->p_left) < 0) {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        pRoot = rotateRight(pRoot);
    }
    // right-left
    if (diff_height < -1 && diffHeight(pRoot->p_right) > 0) {
        pRoot->p_right = rotateRight(pRoot->p_right);
        pRoot = rotateLeft(pRoot);
    }

}

// isAVL and its suppoting function
bool isBST(NODE* pRoot) {
    if (pRoot) {
        if (pRoot->p_left && pRoot->p_left->key > pRoot->key) return false;
        if (pRoot->p_right && pRoot->p_right->key < pRoot->key) return false;
        return isBST(pRoot->p_left) && isBST(pRoot->p_right);
    }
    return true;
}

bool isAVL(NODE* pRoot) {
    if (pRoot) {
        if (!isBST(pRoot)) return false;
        int dif = diffHeight(pRoot);
        if (dif < -1 || dif > 1) return false;
        return (isAVL(pRoot->p_left) && isAVL(pRoot->p_right));
    }
    return true;
}