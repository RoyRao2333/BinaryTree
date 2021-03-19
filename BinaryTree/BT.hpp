//
//  BT.hpp
//  BinaryTree
//
//  Created by Roy Rao on 2020/7/27.
//  Copyright © 2020 RoyRao. All rights reserved.
//

#ifndef BT_hpp
#define BT_hpp

#include <iostream>
#include <queue>
using namespace std;

template<typename T> 
struct BTNode {
public:
    BTNode(): leftChild(nullptr), rightChild(nullptr) {}
    BTNode(T _data): data(_data), leftChild(nullptr), rightChild(nullptr) {}
public:
    T data;
    BTNode<T> *leftChild;
    BTNode<T> *rightChild;
};

template<typename T> 
class BinaryTree {
public:
    /// initialization
    BinaryTree(): root(nullptr) {}
    ~BinaryTree() { this->destroy(); }
    BinaryTree(BinaryTree<T> &node) { this->root = this->copy(node.getRoot()); }
    bool operator==(BinaryTree<T> &node) { return isEqual(this->getRoot(), node.getRoot()); }
    void destroy() { this->destroy(this->root); }
    /// traversal
    void preorderTraversal() { this->preorderTraversal(this->root); }
    void inorderTraversal() { this->preorderTraversal(this->root); }
    void postorderTraversal() { this->preorderTraversal(this->root); }
    void levelOrderTraversal() { this->levelOrderTraversal(this->root); }
    /// get node
    BTNode<T>* getRoot() const { return this->root; }
    BTNode<T>* getParent(BTNode<T> *curNode) { return (!this->root || this->root == curNode) ? nullptr : this->getParent(this->root, curNode); }
    BTNode<T>* getLeftChild(BTNode<T> *curNode);
    BTNode<T>* getRightChild(BTNode<T> *curNode);
    /// member function
    int getSize() { return this->getSize(this->root); }
    int getHeight() { return this->getHeight(this->root); }
    bool isEmpty() { return this->root == nullptr; }
private:
    void preorderTraversal(BTNode<T> *node);
    void inorderTraversal(BTNode<T> *node);
    void postorderTraversal(BTNode<T> *node);
    void levelOrderTraversal(BTNode<T> *node);
    BTNode<T>* getParent(BTNode<T> *node, BTNode<T> *curNode);
    BTNode<T>* copy(BTNode<T> *node);
    bool isEqual(BTNode<T> *aTree, BTNode<T> *bTree);
    void destroy(BTNode<T> *node);
    int getSize(BTNode<T> *node);
    int getHeight(BTNode<T> *node);
private:
    BTNode<T> *root;
};



/*  
    MARK: - DEPLOYMENT 
*/

// Iteration
template<typename T> 
void BinaryTree<T>::preorderTraversal(BTNode<T> *node) {
    if (!node) return {};
    stack<BTNode<T>*> stk;
    while (node || !stk.empty()) {
        while (node) {
            cout << node->data << "\t";
            stk.push(node);
            node = node->leftChild;
        }
        node = stk.top()->rightChild;
        stk.pop();
    }
}

template<typename T> 
void BinaryTree<T>::inorderTraversal(BTNode<T> *node) {
    if (!node) return {};
    stack<BTNode<T>*> stk;
    while (node || !stk.empty()) {
        while (node) {
            stk.push(node);
            node = node->leftChild;
        }
        cout << node->data << "\t";
        node = stk.top()->rightChild;
        stk.pop();
    }
}

template<typename T> 
void BinaryTree<T>::postorderTraversal(BTNode<T> *node) {
    if (!node) return {};
    stack<BTNode<T>*> stk;
    stk.push(node);
    while (!stk.empty()) {
        BTNode<T> *tempNode = stk.top();
        if (!tempNode) {
            stk.pop();
            cout << stk.top()->data << "\t";
            stk.pop();
            continue;
        }
        stk.push(nullptr);
        if (tempNode->rightChild) {
            stk.push(tempNode->rightChild);
        }
        if (tempNode->leftChild) {
            stk.push(tempNode->leftChild);
        }
    }
}

template<typename T> 
void BinaryTree<T>::levelOrderTraversal(BTNode<T> *node) {
    if (!node) return {};
    queue<BTNode<T>*> q;
    q.push(node);
    BTNode<T> *temp;
    while (!q.empty()) {
        temp = q.front();
        q.pop();
        cout << temp->data << "\t";
        if (temp->leftChild) {
            q.push(temp->leftChild);
        }
        if (temp->rightChild) {
            q.push(temp->rightChild);
        }
    }
}

// Recursion
/*
template<typename T> 
void BinaryTree<T>::preorderTraversal(BTNode<T> *node) {
    if (node) {
        cout << node->data << "\t";
        this->preorderTraversal(node->leftChild);
        this->preorderTraversal(node->rightChild);
    }
}

template<typename T> 
void BinaryTree<T>::inorderTraversal(BTNode<T> *node) {
    if (node) {
        this->inorderTraversal(node->leftChild);
        cout << node->data << "\t";
        this->inorderTraversal(node->rightChild);
    }
}

template<typename T> 
void BinaryTree<T>::postorderTraversal(BTNode<T> *node) {
    if (node) {
        this->postorderTraversal(node->leftChild);
        this->postorderTraversal(node->rightChild);
        cout << node->data << "\t";
    }
}
*/

template<typename T> 
BTNode<T>* BinaryTree<T>::getParent(BTNode<T> *node, BTNode<T> *curNode) {
    if (!node) {
        return nullptr;
    }
    if (node->leftChild == curNode || node->rightChild == curNode) {
        return node;
    }
    BTNode<T> *ptr = this->getParent(node->leftChild, curNode);
    if (ptr) {
        return ptr;
    } else {
        return this->getParent(node->rightChild, curNode);
    }
}

template<typename T> 
BTNode<T>* BinaryTree<T>::getLeftChild(BTNode<T> *curNode) {
    return (curNode != nullptr) ? curNode->leftChild : nullptr;
}

template<typename T> 
BTNode<T>* BinaryTree<T>::getRightChild(BTNode<T> *curNode) {
    return (curNode != nullptr) ? curNode->rightChild : nullptr;
}

template<typename T> 
int BinaryTree<T>::getSize(BTNode<T> *node) {
    if (!node) {
        return 0;
    }
    return 1 + this->getSize(node->leftChild) + this->getSize(node->rightChild);
}

template<typename T> 
int BinaryTree<T>::getHeight(BTNode<T> *node) {
    if (!node) {
        return 0;
    }
    int left = this->getHeight(node->leftChild);
    int right = this->getHeight(node->rightChild);
    return (left > right) ? left + 1 : right + 1;
}

template<typename T> 
void BinaryTree<T>::destroy(BTNode<T> *node) {
    if (node) {
        this->destroy(node->leftChild);
        this->destroy(node->rightChild);
        delete node;
        node = nullptr;
    }
}

template<typename T> 
BTNode<T>* BinaryTree<T>::copy(BTNode<T> *node) {
    if (!node) {
        return nullptr;
    }
    BTNode<T> *newTree = new BTNode<T>;
    newTree->data = node->data;
    newTree->leftChild = this->copy(node->leftChild);
    newTree->rightChild = this->copy(node->rightChild);
    return newTree;
}

template<typename T> 
bool BinaryTree<T>::isEqual(BTNode<T> *aTree, BTNode<T> *bTree) {
    if (!aTree && !bTree) {
        return true;
    }
    if (aTree && bTree) {
        if (aTree->data == bTree->data &&
            this->isEqual(aTree->leftChild, bTree->leftChild) &&
            this->isEqual(aTree->rightChild, bTree->rightChild)) {
            return true;
        }
    }
    return false;
}

#endif /* BT_hpp */
