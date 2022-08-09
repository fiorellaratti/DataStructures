//Driver: Anh Luu 50% contribution
//Navigator: Fiorella Andrea Ratti Tamayo 50% contribution
#ifndef CALCLIST_HPP
#define CALCLIST_HPP

#include<iostream>
#include <sstream>
#include <iomanip>
using namespace std;
#include "CalcListInterface.hpp"

struct Elem
{
    double total;
    string operation;
    double operand;
    double newTotal;
    int index;
};

//Node Interface
// typedef string Elem; //element type
struct DNode 
{
    public:
    Elem elem; //the node element value
    DNode* next; //next node in the list
    DNode* prev; //previous node in the list
    friend class DLinkedList; // allow DLinked List
};

class CalcList : public CalcListInterface 
{
    double finalTotal = 0;
    int counterOp = 0;
    public:
    // local type definitions
    DNode* header; // list sentinels
    DNode* trailer;
    CalcList();
    ~CalcList (); 
    void newOperation(FUNCTIONS,double);
    std::string toString(unsigned short) const;
    double total() const {
        return finalTotal; 
    };
    void add(DNode*,const Elem&);
    void addFront(const Elem&);
    void remove (DNode*);
    void removeFront (); 
    void removeLastOperation();
    
};

#endif