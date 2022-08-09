#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H
#include "NotationConverterInterface.hpp"
#include "Deque.hpp"
#include<iostream>
using namespace std;

//Class for the notation converter
//It is a friend of the Deque class
class NotationConverter:public NotationConverterInterface{
public:
string postfixToInfix(string inStr);
string postfixToPrefix(string inStr);

string infixToPostfix(string inStr);
string infixToPrefix(string inStr);

string prefixToInfix(string inStr);
string prefixToPostfix(string inStr);
};

#endif