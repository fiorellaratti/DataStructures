//Driver: Anh Luu 50% contribution
//Navigator: Fiorella Andrea Ratti Tamayo 50% contribution
#include<iostream>
#include <sstream>
#include <iomanip>
using namespace std;
#include "CalcList.hpp"

CalcList::CalcList() // constructor
{ 
      header = new DNode; // create sentinels
      trailer = new DNode;
      header->next = trailer; // have them point to each othe
      trailer->prev = header;
      header->prev = NULL;
      trailer->next=NULL;
};

CalcList::~CalcList () // destructor
{ 
  while ( header->next != trailer) removeFront (); // remove all but sentinels
  delete header; // remove the sentinels
  delete trailer;
}

void CalcList::add(DNode* v, const Elem& e) 
{
        DNode* u = new DNode;
        u->elem = e; //create new node
        u->next = v; // link u in between v
        u->prev = v->prev; //...and v->prev 
        v->prev->next = u;
        v->prev = u;
};

void CalcList::addFront(const Elem& e) 
{
        add(header->next, e);
}

void CalcList::newOperation(const FUNCTIONS func, const double operand) 
{
    DNode* u = new DNode; //creating a new node and store all the elements in it
    switch(func) {
        case ADDITION:
            u->elem.total=finalTotal;
            u->elem.operation="+";
            u->elem.operand=operand;
            u->elem.newTotal= u->elem.total + operand;
            break;
        case SUBTRACTION:
            u->elem.total=finalTotal;
            u->elem.operation="-";
            u->elem.operand=operand;
            u->elem.newTotal= u->elem.total - operand;
            break;
        case MULTIPLICATION:
            u->elem.total=finalTotal;
            u->elem.operation="*";
            u->elem.operand=operand;
            u->elem.newTotal= u->elem.total*operand;
            break;
        case DIVISION:
            if (operand==0) {
              throw 1;
            }
            u->elem.total=finalTotal;
            u->elem.operation="/";
            u->elem.operand=operand;
            u->elem.newTotal= u->elem.total/operand;
            break;
            
    }
    
    finalTotal = u->elem.newTotal;
    counterOp++; //increment counterOp
    u->elem.index=counterOp;
    addFront(u->elem);
}

void CalcList::remove(DNode* v) // remove node v
{
    DNode* u = v->prev; // predecessor
    DNode* w = v->next; // successor
    u->next = w;// unlink v from list
    w->prev = u;
    finalTotal = v->elem.total;
    delete v;
    counterOp--; //decrement counterOp
}

//remove from front
void CalcList::removeFront () 
{
    remove (header->next);
}

void CalcList::removeLastOperation() 
{
    if (header->next == trailer) {
        throw 1;
    } 
    removeFront();
}

std::string CalcList::toString(unsigned short precision) const { //toString function
    if (header->next == trailer) 
        return "";
    DNode* u = header->next;
    std::string out;
    std::stringstream stream;
    stream <<std::fixed<< std::setprecision(precision);
    while (u != trailer)
    {
        Elem elem = u->elem;
        stream <<elem.index <<": "<< elem.total <<elem.operation <<elem.operand << "=" << elem.newTotal << "\n";
        u = u->next;
     
    }
    out = stream.str();
    return out;
}