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
using namespace std;

template<typename T> struct BTNode {
public:
    BTNode(): leftChild(nullptr), rightChild(nullptr) {}
    BTNode(T _data): data(_data), leftChild(nullptr), rightChild(nullptr) {}
public:
    T data;
    BTNode<T> *leftChild;
    BTNode<T> *rightChild;
};

template<typename T> class BinaryTree {
public:
    /// initialization
    BinaryTree(): root(nullptr) {}
    ~BinaryTree() { this->destroy(); }
    BinaryTree(BinaryTree<T> &tree) { this->root = this->copy(tree.getRoot()); }
    bool operator==(BinaryTree<T> &tree) { return isEqual(this->getRoot(), tree.getRoot()); }
    void destroy() { this->destroy(this->root); }
    /// traversal
    void preorderTraversal() { this->preorderTraversal(this->root); }
    void inorderTraversal() { this->preorderTraversal(this->root); }
    void postorderTraversal() { this->preorderTraversal(this->root); }
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
    void preorderTraversal(BTNode<T> *tree);
    void inorderTraversal(BTNode<T> *tree);
    void postorderTraversal(BTNode<T> *tree);
    BTNode<T>* getParent(BTNode<T> *tree, BTNode<T> *curNode);
    BTNode<T>* copy(BTNode<T> *tree);
    bool isEqual(BTNode<T> *aTree, BTNode<T> *bTree);
    void destroy(BTNode<T> *tree);
    int getSize(BTNode<T> *tree);
    int getHeight(BTNode<T> *tree);
private:
    BTNode<T> *root;
};



//  MARK: - DEPLOYMENT
template<typename T> void BinaryTree<T>::preorderTraversal(BTNode<T> *tree) {
    if (tree) {
        cout << tree->data << "\t";
        this->preorderTraversal(tree->leftChild);
        this->preorderTraversal(tree->rightChild);
    }
}

template<typename T> void BinaryTree<T>::inorderTraversal(BTNode<T> *tree) {
    if (tree) {
        this->inorderTraversal(tree->leftChild);
        cout << tree->data << "\t";
        this->inorderTraversal(tree->rightChild);
    }
}

template<typename T> void BinaryTree<T>::postorderTraversal(BTNode<T> *tree) {
    if (tree) {
        this->postorderTraversal(tree->leftChild);
        this->postorderTraversal(tree->rightChild);
        cout << tree->data << "\t";
    }
}

template<typename T> BTNode<T>* BinaryTree<T>::getParent(BTNode<T> *tree, BTNode<T> *curNode) {
    if (!tree) {
        return nullptr;
    }
    if (tree->leftChild == curNode || tree->rightChild == curNode) {
        return tree;
    }
    BTNode<T> *ptr = this->getParent(tree->leftChild, curNode);
    if (ptr) {
        return ptr;
    } else {
        return this->getParent(tree->rightChild, curNode);
    }
}

template<typename T> BTNode<T>* BinaryTree<T>::getLeftChild(BTNode<T> *curNode) {
    return (curNode != nullptr) ? curNode->leftChild : nullptr;
}

template<typename T> BTNode<T>* BinaryTree<T>::getRightChild(BTNode<T> *curNode) {
    return (curNode != nullptr) ? curNode->rightChild : nullptr;
}

template<typename T> int BinaryTree<T>::getSize(BTNode<T> *tree) {
    if (!tree) {
        return 0;
    }
    return 1 + this->getSize(tree->leftChild) + this->getSize(tree->rightChild);
}

template<typename T> int BinaryTree<T>::getHeight(BTNode<T> *tree) {
    if (!tree) {
        return 0;
    }
    int left = this->getHeight(tree->leftChild);
    int right = this->getHeight(tree->rightChild);
    return (left > right) ? left + 1 : right + 1;
}

template<typename T> void BinaryTree<T>::destroy(BTNode<T> *tree) {
    if (tree) {
        this->destroy(tree->leftChild);
        this->destroy(tree->rightChild);
        delete tree;
        tree = nullptr;
    }
}

template<typename T> BTNode<T>* BinaryTree<T>::copy(BTNode<T> *tree) {
    if (!tree) {
        return nullptr;
    }
    BTNode<T> *newTree = new BTNode<T>;
    newTree->data = tree->data;
    newTree->leftChild = this->copy(tree->leftChild);
    newTree->rightChild = this->copy(tree->rightChild);
    return newTree;
}

template<typename T> bool BinaryTree<T>::isEqual(BTNode<T> *aTree, BTNode<T> *bTree) {
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
