#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan {preorder, inorder, postorder};

template<class T>
class BST {
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp=inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;
    void BSTCopyHelper(BSTNode<T>* &obj1, const BSTNode<T>* obj2)const;
    void DestructorHelper(BSTNode<T>* &node);
    BSTNode<T> * successorHelper(BSTNode<T> * &node,TraversalPlan tp)const;
    BSTNode<T> * deleteNode(BSTNode<T> * &root, T data)const;
    bool containsHelper(BSTNode<T> * root, BSTNode<T> * node)const;
    void insertHelper(BSTNode<T> * &root,T data);
    BSTNode<T>* searchHelper(BSTNode<T> * root, const T &data)const;
    BSTNode<T>* getMin(BSTNode<T> * &node) const;
    BSTNode<T>* getParent(BSTNode<T> * node, T value)const;
private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif //BST_H

template<class T>
BST<T>::BST() {
    /* TODO */
    root = NULL;
}
// I will define helper function for copy constructor
template <class T>
void BST<T>::BSTCopyHelper(BSTNode<T>* &obj1, const BSTNode<T>* obj2)const
{
    if(obj2 == NULL){
        obj1 = NULL;
    }
    else{
        obj1 = new BSTNode<T>;
        obj1->data = obj2->data;
        BSTCopyHelper(obj1->left, obj2->left); 
        BSTCopyHelper(obj1->right, obj2->right); 
    }
}


template<class T>
BST<T>::BST(const BST<T> &obj) {
    /* TODO */
    if(obj.root == NULL){
        root = NULL;
    }
    else{
        BSTCopyHelper(root,obj.root);
    }
}
// I will define helper function for destructor
template <class T>
void BST<T>::DestructorHelper(BSTNode<T> *&node)
{
    if(node == NULL){
        return;
    }
    else
    {
        DestructorHelper(node->left);
        DestructorHelper(node->right);
        delete node;
        node = NULL;
    }
}
template<class T>
BST<T>::~BST() {
    /* TODO */
    DestructorHelper(this->root);
}

template<class T>
BSTNode<T> *BST<T>::getRoot() const {
    /* TODO */
    if(this->root == NULL){
        return NULL;
    }
    return this->root;
}

template<class T>
bool BST<T>::isEmpty() const {
    /* TODO */
    if(root == NULL) return true;
    else{
        return false;
    }
}
// helper for contains
template<class T>
bool BST<T>::containsHelper(BSTNode<T> * root, BSTNode<T> * node)const{
    /* TODO */
    if (root == NULL){
        return false;
    }
    else{
        if ((node->data == root->data) && (root->right == node->right) && (root->left == node->left)){
            return true;
        }
        else if(node->data < root->data){
            return containsHelper(root->left, node);
        }
        else if (node->data > root->data){
            return containsHelper(root->right, node);
        }
    }
}

template<class T>
bool BST<T>::contains(BSTNode<T> *node) const {
    /* TODO */
    return containsHelper(this->root, node);
}

// helper for insert
template<class T>
void BST<T>::insertHelper(BSTNode<T> * &root,T data){
    /* TODO */
    if (root == NULL) {
        root = new BSTNode<T>;
        root->data = data;
    }
    else if(root->data > data) {
        insertHelper(root->left, data);
    }else if (root->data < data) {
        insertHelper(root->right, data);
    } // else a duplicate
}

template<class T>
void BST<T>::insert(const T &data) {
    /* TODO */
    insertHelper(root, data);
}

// helper function for remove
template<class T>
BSTNode<T> * BST<T>::deleteNode(BSTNode<T> * &root, T data)const
{
    // base case
    if (root == NULL)
        return root;
    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left==NULL && root->right==NULL){
            delete root;
            root = NULL;
            return root;
        }
        else if (root->left == NULL) {
            BSTNode<T>* temp = root->right;
            delete root;
            root = NULL;
            return temp;
        }
        else if (root->right == NULL) {
            BSTNode<T>* temp = root->left;
            delete root;
            root = NULL;
            return temp;
        }
        BSTNode<T>* temp = getMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
template<class T>
void BST<T>::remove(const T &data) {
    /* TODO */
    deleteNode(root,data);
}

template<class T>
void BST<T>::removeAllNodes() {
    /* TODO */
    DestructorHelper(this->root);
}
// helper for search
template<class T>
BSTNode<T>* BST<T>::searchHelper(BSTNode<T> * root, const T &data) const{
    /* TODO */
    if (root == NULL){
        return NULL;
    }
    else{
        if ((data == root->data)){
            return root;
        }
        else if(data < root->data){
            return searchHelper(root->left, data);
        }
        else if (data > root->data){
            return searchHelper(root->right, data);
        }
    }
}


template<class T>
BSTNode<T> *BST<T>::search(const T &data) const {
    /* TODO */
    return searchHelper(root, data);
}

// I will define helper function in order to get minimum value of given root
template<class T>
BSTNode<T> *BST<T>::getMin(BSTNode<T> *&node) const
{
    if(node){
        BSTNode<T> * current = node;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }
    else
        return NULL;
    
}
// helper function to find parent of a given node
template<class T>
BSTNode<T>* BST<T>::getParent(BSTNode<T>* node, T value)const
{
    
    if (node == NULL)
       return NULL;
    if(node->data == value){
        return NULL;
    }
    if(node->left == NULL && node->right == NULL)
       return NULL;

    if( (node->left != NULL && node->left->data == value)
        || (node->right != NULL && node->right->data == value))
       return node;

    if(node->data > value)
       return getParent(node->left,value);

    if(node->data < value)
       return getParent(node->right,value);
    
}


// helper function for getSuccessor
template<class T>
BSTNode<T> * BST<T>::successorHelper(BSTNode<T> * &node,TraversalPlan tp)const
{
    if (tp == inorder) {
        if(node && root){
            if (node->right != NULL){
                return getMin(node->right);
            }
            if(root == NULL)
                return NULL;
            if(node == NULL)
                return NULL;
            BSTNode<T>* successor = NULL;
            BSTNode<T>* current = root;
            while (current != NULL)
            {
                if (node->data < current->data)
                {
                    successor = current;
                    current = current->left;
                }
                else if (node->data > current->data)
                    current = current->right;
                else
                    break;
            }
            if(successor){
                return successor;
            }
            else{
                return NULL;
            }
        }
        else
            return NULL;
    }
    else if (tp == preorder) {
    /* TODO */
        if (!root){
            return NULL;
        }
        if (!node){
            return NULL;
        }
        if (node->left){
            return node->left;
        }
        if (node->right){
            return node->right;
        }
        BSTNode<T> * parent_node = getParent(root, node->data);
        BSTNode<T> * temporary_parent = parent_node;

        if(parent_node != 0){
            if ((node == parent_node->left)){
            while (parent_node)
            {
                if (parent_node->right && parent_node->right != temporary_parent)
                    return parent_node ->right;
                temporary_parent = parent_node;
                parent_node = getParent(root, parent_node->data);
            }
            return parent_node;
            }
            else
            {
                BSTNode<T> * cur = node;
                while (parent_node)
                {
                    if (cur == parent_node->left && parent_node->right)
                        return parent_node->right;
                    cur = parent_node;
                    parent_node = getParent(root, parent_node->data);
                }
            }
        }
        
        return NULL;
    }
    else if (tp == postorder) {
    /* TODO */
        BSTNode<T> * temp;
        if (!root){
            return NULL;
        }
        if (!node){
            return NULL;
        }
        BSTNode<T>* parent_node = getParent(root,node->data);
        if (!parent_node){
            return NULL;
        }
        if(!parent_node->right){
            return parent_node;
        }
        if(node->data == parent_node->right->data){
            return parent_node;
        }
        else{
            temp = getMin(parent_node->right);
            while(temp->right){
                temp = getMin(temp->right);
            }
            return temp;
        }
    }
}

template<class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const {
    return successorHelper(node,tp);
}

template<class T>
void BST<T>::print(TraversalPlan tp) const {

    if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, inorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == preorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        // the tree is not empty.
        // recursively output the tree.
        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        // the tree is not empty.
        // recursively output the tree.
        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs) {
    /* TODO */
    if(this != &rhs){
        this->removeAllNodes();
        if(rhs.root == NULL){
            root = NULL;
        }
        else{
            BSTCopyHelper(root,rhs.root);
        }
    }
    return *this;
}

template<class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder) {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } else if (tp == preorder) {
        std::cout << "\t" << node->data;
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
    } else if (tp == postorder) {
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->data;
    }
}
