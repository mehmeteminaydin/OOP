#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse=false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    
private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};

template<class T>
LinkedList<T>::LinkedList() {
    /* TODO */
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    /* TODO */
    Node<T>* curr = NULL;
    Node<T>* curr2 = NULL;
    Node<T>* tmp = NULL;
    if(obj.head == NULL){
        head = NULL;
    }
    else{
        head = new Node<T>(obj.head->data);
        curr = head;
        curr2 = obj.head->next;
        
        while(curr2 != obj.head){
            curr->next = new Node<T>(curr2->data);
            tmp = curr;
            curr = curr->next;
            //curr->data = curr2->data;
            curr->prev = tmp;
            curr2 = curr2->next;
        }
        // link the last node to first node
        curr->next = head;
        head->prev = curr;
    }
    // assign size
    size = obj.size;
}

template<class T>
LinkedList<T>::~LinkedList() {
    /* TODO */
    if(getSize()>1){
        Node<T>* tmp = NULL;
        Node<T>* curr = head->next;
        while (curr != head){
            tmp = curr;
            curr = curr->next;
            delete tmp;
            tmp = NULL;
        }
        delete head;
        head = NULL;
    }
    else if(getSize()==1){
        delete head;
        head = NULL;
    }
    size = 0;
}

template<class T>
int LinkedList<T>::getSize() const {
    /* TODO */
    return this->size;
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    /* TODO */
    if(getSize() == 0){
        return true;
    }
    else{
        return false;
    }
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    /* TODO */
    //if list is empty return false directly
    if(!head){
        return false;
    }
    Node<T> * curr = head;
    while(curr != head->prev){
        if(curr == node){
            return true;
        }
        curr = curr->next;
    }
    //check the last node
    if(curr == node){
        return true;
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    /* TODO */
    if(!head){
        return NULL;
    }
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    /* TODO */
    if(!head){
        return NULL;
    }
    if(getSize() == 1){
        return head;
    }
    return head->prev;
}

// operator== can be overloaded. Check it before submitting.


template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    /* TODO */
    if(!head){
        return NULL;
    }
    Node<T> * curr = head;
    while(curr != head->prev){
        if(curr->data == data){
            return curr;
        }
        curr = curr->next;
    }
    //check the last node
    if(curr->data == data){
        return curr;
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const {
    /* TODO */
    Node<T>* curr = head;
    if((index >= 0) && (index <= size-1)){
        //return the intended node
        for(int i = 0; i < index; i++){
            curr = curr->next;
        }
        return curr;
    }
    // otherwise it is out of linkedlist;
    return NULL;
}

template<class T>
void LinkedList<T>::insertAtTheFront(const T &data) {
    /* TODO */
    Node<T>* firstNode;
    firstNode = new Node <T> (data);
    if(getSize()>= 1){
        firstNode->next = head;
        firstNode->prev = head->prev;
        head->prev = firstNode;
        firstNode->prev->next = firstNode;
    }
    // if list is empty
    else{
        firstNode->next = firstNode;
        firstNode->prev = firstNode;
    }
    // assign the head pointer to new added node
    head = firstNode;
    size++;
}

template<class T>
void LinkedList<T>::insertAtTheEnd(const T &data) {
    /* TODO */
    Node<T>* lastNode = new Node<T>(data);
    if(getSize()==0){
        lastNode->next = lastNode;
        lastNode->prev = lastNode;
        head = lastNode;
    }
    else if(getSize()==1){
        head->next = lastNode;
        head->prev = lastNode;
        lastNode->prev = head;
        lastNode->next = head;
        //head remains same
    }
    else{
        Node<T>* oldLastNode;
        oldLastNode = head->prev;
        lastNode->prev = oldLastNode;
        lastNode->next = head;
        oldLastNode->next = lastNode;
        head->prev = lastNode;
        // head remains same
    }
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node) {
    /* TODO */
    if(getSize() > 1){
        Node<T>* curr = head->next;
        bool checker = false;
        while(curr != head){
            if((curr == node) && (curr->next == node->next) && (curr->prev == node->prev)){
                Node<T>* nextNode = curr->next;
                Node<T>* newNode = new Node<T>(data);
                newNode->next = nextNode;
                newNode->prev = curr;
                curr->next = newNode;
                nextNode->prev = newNode;
                checker = true;
                size++;
                break;
            }
            curr = curr->next;
        }
        //Lastly, check for the head node
        if((curr == node) && (curr->next == node->next) && (curr->prev == node->prev) && !checker){
            Node<T>* nextNode = curr->next;
            Node<T>* newNode = new Node<T>(data);
            newNode->next = nextNode;
            newNode->prev = curr;
            curr->next = newNode;
            nextNode->prev = newNode;
            size++;
        }
    }
    else if(getSize() == 1){
        Node<T>* curr = head;
        if((curr == node) && (curr->next == node->next) && (curr->prev == node->prev)){
            Node<T>* newNode = new Node<T>(data);
            newNode->next = curr;
            newNode->prev = curr;
            curr->next = newNode;
            curr->prev = newNode;
            size++;
        }
    }
    
}

template<class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k) {
    /* TODO */
    int firstSize = size;
    if(k >= 2){
        int i = 0;
        Node<T>* curr = head->next;
        while(curr != head){
            i++;
            if(i == (k-1)){
                Node<T>* newNode = new Node<T>(data);
                newNode->next = curr;
                newNode->prev = curr->prev;
                curr->prev->next = newNode;
                curr->prev = newNode;
                size++;
                i = 0;
            }
            curr = curr->next;
        }
        if(firstSize%(k-1) == 0){
            Node<T>* newNode = new Node<T>(data);
            newNode->next = curr;
            newNode->prev = curr->prev;
            curr->prev->next = newNode;
            curr->prev = newNode;
            size++;
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    /* TODO */
    if(getSize()==1){
        if((head == node) && (head->next == node->next) && (head->prev == node->prev)){
            delete head;
            head = NULL;
            size--;
        }
    }
    else if(getSize() == 2){
        if((head == node) && (head->next == node->next) && (head->prev == node->prev)){
            Node<T>* newHead = head->next;
            delete head;
            head = newHead;
            head->next = head;
            head->prev = head;
            size--;
        }
        else if((head->next == node) && (head->next->next == node->next) && (head->next->prev == node->prev)){
            delete head->next;
            head->next = head;
            head->prev = head;
            size--;
        }
    }
    else if (getSize() > 2){
        bool checker = false;
        Node<T>* tmp = NULL;
        Node<T>* curr = head->next;
        while (curr != head){
            if((curr == node) && (curr->next == node->next) && (curr->prev == node->prev)){
                tmp = curr;
                curr = curr->next;
                tmp->prev->next = curr;
                curr->prev = tmp->prev;
                delete tmp;
                tmp = NULL;
                checker = true;
                size--;
                break;
            }
            else{
                curr = curr->next;
            }
        }
        if((head == node) && (head->next == node->next) && (head->prev == node->prev) && !checker){
            Node<T>* newHead = head->next;
            head->prev->next = head->next;
            head->next->prev = head->prev;
            delete head;
            head = newHead;
            size--;
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    /* TODO */
    if(getSize()==1){
        if(head->data == data){
            delete head;
            head = NULL;
            size--;
        }
    }
    else if(getSize() == 2){
        if(head->data == data){
            Node<T>* newHead = head->next;
            delete head;
            head = newHead;
            head->next = head;
            head->prev = head;
            size--;
        }
        else if(head->next->data == data){
            delete head->next;
            head->next = head;
            head->prev = head;
            size--;
        }
    }
    else if (getSize() > 2){
        Node<T>* tmp = NULL;
        Node<T>* curr = head->next;
        while (curr != head){
            if((curr->data == data)){
                tmp = curr;
                curr = curr->next;
                tmp->prev->next = curr;
                curr->prev = tmp->prev;
                delete tmp;
                tmp = NULL;
                size--;
                
            }
            else{
                curr = curr->next;
            }
        }
        if((head->data == data)){
            Node<T>* newHead = head->next;
            head->prev->next = head->next;
            head->next->prev = head->prev;
            delete head;
            head = newHead;
            size--;
        }
    }
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    /* TODO */
    if(getSize()>1){
        Node<T>* tmp = NULL;
        Node<T>* curr = head->next;
        while (curr != head){
            tmp = curr;
            curr = curr->next;
            delete tmp;
            tmp = NULL;
        }
        delete head;
        head = NULL;
    }
    else if(getSize()==1){
        delete head;
        head = NULL;
    }
    size = 0;
}

template<class T>
void LinkedList<T>::removeEveryKthNode(int k) {
    /* TODO */
    int firstSize = size;
    if(k >= 2){
        int i = 1;
        bool checker;
        Node<T>* curr = head->next;
        while(curr != head){
            checker = false;
            i++;
            if(i == (k)){
                Node<T>* deleted = curr;
                Node<T>* nextNode = curr->next;
                Node<T>*prevNode = curr->prev;
                prevNode->next = nextNode;
                nextNode->prev = prevNode;
                curr = nextNode;
                delete deleted;
                deleted = NULL;
                size--;
                i = 0;
                checker = true;
            }
            if(!checker){
                curr = curr->next;
            }
        }
        
    }
}

template<class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2) {
    /* TODO */
    bool t = true;
    Node<T>* tmp1;
    Node<T>* tmp2;
    tmp1 = NULL;
    tmp2 = NULL;
    Node<T>* curr = head->next;
    while(curr != head){
        if((curr == node1) && (curr->next == node1->next) && (curr->prev == node1->prev)){
            tmp1 = node1;
        }
        if((curr == node2) && (curr->next == node2->next) && (curr->prev == node2->prev)){
            tmp2 = node2;
        }
        curr = curr->next;
    }
    if((head == node1) && (head->next == node1->next) && (head->prev == node1->prev)){
        tmp1 = head;
    }
    if((head == node2) && (head->next == node2->next) && (head->prev == node2->prev)){
        tmp2 = head;
    }
    if(tmp1 == NULL || tmp2 == NULL){
        t = false;
    }
    // head olmayan ve ardışık olmayan nodeları kontrol et
    if(t && ((tmp1 != head) && (tmp2 != head)) && ((tmp1->next != tmp2)&& tmp2->next!=tmp1)){
        Node<T>* tmp1Prev = tmp1->prev;
        Node<T>* tmp2Prev = tmp2->prev;
        Node<T>* tmp1Next = tmp1->next;
        Node<T>* tmp2Next = tmp2->next;
        tmp1Prev->next = tmp2;
        tmp2Prev->next = tmp1;
        tmp1Next->prev = tmp2;
        tmp2Next->prev = tmp1;
        tmp1->next = tmp2Next;
        tmp1->prev = tmp2Prev;
        tmp2->next = tmp1Next;
        tmp2->prev = tmp1Prev;
    }
    // head olmayan ve ardışık olanları kontrol et
    else if(t && ((tmp1 != head) && (tmp2 != head)) && ((tmp1->next == tmp2)|| (tmp2->next==tmp1))){
        if((tmp1->next == tmp2)){
            Node<T>* tmp1Prev = tmp1->prev;
            Node<T>* tmp2Prev = tmp2->prev;
            Node<T>* tmp1Next = tmp1->next;
            Node<T>* tmp2Next = tmp2->next;
            tmp1Prev->next = tmp2;
            tmp2Prev->next = tmp2Next;
            tmp1Next->prev = tmp1Prev;
            tmp2Next->prev = tmp1;
            tmp1->next = tmp2Next;
            tmp1->prev = tmp2;
            tmp2->next = tmp1;
        }
        else if((tmp2->next==tmp1)){
            Node<T>* tmp1Prev = tmp1->prev;
            Node<T>* tmp2Prev = tmp2->prev;
            Node<T>* tmp1Next = tmp1->next;
            Node<T>* tmp2Next = tmp2->next;
            tmp2Prev->next = tmp1;
            tmp1Prev->next = tmp1Next;
            tmp2Next->prev = tmp2Prev;
            tmp1Next->prev = tmp2;
            tmp2->next = tmp1Next;
            tmp2->prev = tmp1;
            tmp1->next = tmp2;
        }
    }
    //head olan ve ardısık olmayan
    else if(t && ((tmp1 == head) || (tmp2 == head)) && ((tmp1->next != tmp2)&& tmp2->next!=tmp1)){
        if(tmp1 == head){
            Node<T>* tmp1Prev = tmp1->prev;
            Node<T>* tmp2Prev = tmp2->prev;
            Node<T>* tmp1Next = tmp1->next;
            Node<T>* tmp2Next = tmp2->next;
            tmp1Prev->next = tmp2;
            tmp2Prev->next = tmp1;
            tmp1Next->prev = tmp2;
            tmp2Next->prev = tmp1;
            tmp1->next = tmp2Next;
            tmp1->prev = tmp2Prev;
            tmp2->next = tmp1Next;
            tmp2->prev = tmp1Prev;
            head = tmp2;
        }
        else if(tmp2 == head){
            Node<T>* tmp1Prev = tmp1->prev;
            Node<T>* tmp2Prev = tmp2->prev;
            Node<T>* tmp1Next = tmp1->next;
            Node<T>* tmp2Next = tmp2->next;
            tmp1Prev->next = tmp2;
            tmp2Prev->next = tmp1;
            tmp1Next->prev = tmp2;
            tmp2Next->prev = tmp1;
            tmp1->next = tmp2Next;
            tmp1->prev = tmp2Prev;
            tmp2->next = tmp1Next;
            tmp2->prev = tmp1Prev;
            head = tmp1;
        }
    }
    //head olan ve ardısık olan
    else if(t && ((tmp1 == head) || (tmp2 == head)) && ((tmp1->next == tmp2)|| (tmp2->next==tmp1))){
        if((tmp1->next == tmp2)){
            Node<T>* tmp1Prev = tmp1->prev;
            Node<T>* tmp2Prev = tmp2->prev;
            Node<T>* tmp1Next = tmp1->next;
            Node<T>* tmp2Next = tmp2->next;
            tmp1Prev->next = tmp2;
            tmp2Prev->next = tmp2Next;
            tmp1Next->prev = tmp1Prev;
            tmp2Next->prev = tmp1;
            tmp1->next = tmp2Next;
            tmp1->prev = tmp2;
            tmp2->next = tmp1;
        }
        else if((tmp2->next==tmp1)){
            Node<T>* tmp1Prev = tmp1->prev;
            Node<T>* tmp2Prev = tmp2->prev;
            Node<T>* tmp1Next = tmp1->next;
            Node<T>* tmp2Next = tmp2->next;
            tmp2Prev->next = tmp1;
            tmp1Prev->next = tmp1Next;
            tmp2Next->prev = tmp2Prev;
            tmp1Next->prev = tmp2;
            tmp2->next = tmp1Next;
            tmp2->prev = tmp1;
            tmp1->next = tmp2;
        }
        if(tmp1 == head){
            head = tmp2;
        }
        else if(tmp2 == head){
            head = tmp1;
        }
    }
    
}

template<class T>
void LinkedList<T>::shuffle(int seed) {
    /* TODO */
    for(int i =0; i<getSize(); i++){
        swap(this->getNodeAtIndex(i), this->getNodeAtIndex(((i*i)+seed)%getSize()));
    }
}

template<class T>
void LinkedList<T>::print(bool reverse) const {
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse) {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do {
            std::cout << *node << std::endl;
            node = node->prev;
        }
        while (node != this->getLastNode());
    } else {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do {
            std::cout << *node << std::endl;
            node = node->next;
        }
        while (node != this->getFirstNode());
    }
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    /* TODO */
    if(rhs.head != head){
        removeAllNodes();
        Node<T>* curr = NULL;
        Node<T>* curr2 = NULL;
        Node<T>* tmp = NULL;
        if(rhs.head == NULL){
            head = NULL;
        }
        else{
            head = new Node<T>(rhs.head->data);
            curr = head;
            curr2 = rhs.head->next;
            
            while(curr2 != rhs.head){
                curr->next = new Node<T>(curr2->data);
                tmp = curr;
                curr = curr->next;
                //curr->data = curr2->data;
                curr->prev = tmp;
                curr2 = curr2->next;
            }
            // link the last node to first node
            curr->next = head;
            head->prev = curr;
        }
        // assign size
        size = rhs.size;
    }
}

#endif //LINKEDLIST_H
