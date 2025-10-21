#include <iostream>
#include "linkedlist.h"

void DemoLinkedList(){
    CLinkedList<int> l1;
    int x = 5;
    l1.Insert(x, 3);
    x = 9;
    l1.Insert(x, 14);
    std::cout << x;
    std::cout << l1;
    CLinkedList<float> l2;
    float f = 3.14;
    l2.Insert(f, 10.5);
    std::cout << l2;
    l2.Insert(f, 21.0);
    std::cout << l2;

    CLinkedList<int> l3 = l1;
    std::cout << l3;

    CLinkedList<int> l4 = std::move(l1);
    std::cout << l4;


}