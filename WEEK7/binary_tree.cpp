#include <iostream>
#include <vector>
using namespace std;

struct NODE{
    int key;
    NODE* p_left;
    NODE* p_right;
};

NODE* createNode(int data) {
    NODE* newNode = new NODE;
    newNode->key = data;
    newNode->p_left = newNode->p_right = nullptr;
    return newNode;
}

vector<int> NLR(NODE* pRoot) {
    vector<int> value = {};
    if (pRoot) {
        value.push_back(pRoot->key);    
        for (int i : NLR(pRoot->p_left)) value.push_back(i);
        for (int i : NLR(pRoot->p_right)) value.push_back(i);
    }
    return value;
}

vector<int> LNR(NODE* pRoot) {
    vector<int> value = {};
    if (pRoot) {
        for (int i : LNR(pRoot->p_left)) value.push_back(i);
        value.push_back(pRoot->key); 
        for (int i : LNR(pRoot->p_right)) value.push_back(i);
    }
    return value;
}

vector<int> LRN(NODE* pRoot) {
    vector<int> value = {};
    if (pRoot) {
        for (int i : LRN(pRoot->p_left)) value.push_back(i);
        for (int i : LRN(pRoot->p_right)) value.push_back(i);
        value.push_back(pRoot->key); 
    }
    return value;
}

vector<vector<int>> LevelOrder(NODE* pRoot) {
    vector<vector<int>> level = {};
    if (pRoot) {
        vector<int> value = {pRoot->key};
        level.push_back(value);
        vector<vector<int>> left = LevelOrder(pRoot->p_left);
        vector<vector<int>> right = LevelOrder(pRoot->p_right);
        int len = max(left.size(), right.size());

        for (int i = 0; i < len; i++) {
            vector<int> sublevel = {};
            if (i < left.size()) for (int k : left[i]) sublevel.push_back(k);
            if (i < right.size()) for (int k : right[i]) sublevel.push_back(k);
            level.push_back(sublevel);
        }
    }
    return level;
}

int countNode(NODE* pRoot) {
    if (pRoot) return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
    return 0;
}

int sumNode(NODE* pRoot) {
    if (pRoot) return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
    return 0;
}

int heightNode(NODE* pRoot, int value) {
    if (pRoot) {
        if (pRoot->key == value) {
            int l = -1, r = -1;
            if (pRoot->p_left) l = heightNode(pRoot->p_left, pRoot->p_left->key);
            if (pRoot->p_right) r = heightNode(pRoot->p_right, pRoot->p_right->key);
            return 1 + max(l, r);
        }
        return max(heightNode(pRoot->p_left, value), heightNode(pRoot->p_right, value));
    }
    return -1;
}

int Level(NODE* pRoot, NODE* p) {
    if (pRoot && p) {
        if (pRoot == p) return 0;
        int l = Level(pRoot->p_left, p);
        if (l > -1) return l + 1;
        l = Level(pRoot->p_right, p);
        if (l > -1) return l + 1;
    }
    return -1;
}

int countLeaf(NODE* pRoot) {
    if (pRoot) {
        if (!pRoot->p_left && !pRoot->p_right)
            return 1;
        return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
    }
    return 0;
}