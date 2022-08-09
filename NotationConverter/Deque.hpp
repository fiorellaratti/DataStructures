#ifndef DEQUE_H
#define DEQUE_H

#include<iostream>
#include <sstream>
#include <iomanip>
#include "NotationConverterInterface.hpp"
using namespace std;


struct Node
{
    string data;
    Node *prev, *next;
    static Node* getnode(string data)
    {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = data;
        newNode->prev = newNode->next = NULL;
        return newNode;
    }
};
 
class Deque 
{
    Node* front;
    Node* rear;
    int Size;
 
public:
    Deque()
    {
        front = rear = NULL;
        Size = 0;
    }

    void addFront(string data);
    void addRear(string data);
    void removeFront();
    void removeRear();
    string addFront();
    string addRear();
    int size();
    bool empty();
    void erase();
};
 
#endif