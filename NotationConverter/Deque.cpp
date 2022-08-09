#include<iostream>
#include <sstream>
#include <iomanip>
#include "Deque.hpp"
using namespace std;


bool Deque::empty(){
    return (front == NULL);
}

int Deque::size(){
    return Size;
}

void Deque::addFront(string data)
{
    Node* newNode = Node::getnode(data);

    if (newNode == NULL)
        std::cout << "OverFlow\n";
    else
    {
        if (front == NULL)
            rear = front = newNode;
        else
        {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
        Size++;
    }
}
 
void Deque::addRear(string data)
{
    Node* newNode = Node::getnode(data);

    if (newNode == NULL)
        std::cout << "OverFlow\n";
    else
    {
        if (rear == NULL)
            front = rear = newNode;

        else
        {
            newNode->prev = rear;
            rear->next = newNode;
            rear = newNode;
        }
 
        Size++;
    }
}
 
void Deque::removeFront()
{
    if (empty())
        std::cout << "UnderFlow\n";

    else
    {
        Node* temp = front;
        front = front->next;

        if (front == NULL)
            rear = NULL;
        else
            front->prev = NULL;
        free(temp);
        Size--;
    }
}
 
void Deque::removeRear()
{

    if (empty())
        std::cout << "UnderFlow\n";
    else
    {
        Node* temp = rear;
        rear = rear->prev;

        if (rear == NULL)
            front = NULL;
        else
            rear->next = NULL;
        free(temp);
        Size--;
    }
}

string Deque::addFront()
{
    if (empty())
        return front->data;
    return front->data;
}
 
string Deque::addRear()
{
    if (empty())
        return rear->data;
    return rear->data;
}

void Deque::erase()
{
    rear = NULL;
    while (front != NULL)
    {
        Node* temp = front;
        front = front->next;
        free(temp);
    }
    Size = 0;
}
