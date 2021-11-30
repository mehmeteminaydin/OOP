#include <iostream>

#include "LinkedList.h"

int main() {
    LinkedList<int> llist;
    //llist.insertAtTheEnd(10);
    //llist.insertAtTheFront(8);
    //llist.insertAtTheFront(7);
    //llist.insertAtTheFront(6);
    llist.insertAtTheFront(2);
    llist.insertAtTheFront(2);
    llist.insertAtTheFront(2);
    llist.insertAtTheFront(2);
    llist.insertAtTheFront(2);
    llist.print();
    llist.removeNode(2);

    //llist.insertAtTheEnd(15);
    //llist.insertAfterNode(1, llist.getNode(4));
    //llist.insertAtTheFront(3);
    //llist.removeNode(2);
    //llist.print();
    std::cout << "after changed the nodes"  << std::endl;
    //llist.removeNode(llist.getNodeAtIndex(0));
    llist.print();
    //std::cout << "after removed the nodes"  << std::endl;
    //llist.print();

    return 0;
}
