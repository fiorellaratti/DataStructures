//Navigator: Anh Luu 50% contribution
//Driver: Fiorella Andrea Ratti Tamayo 50% contribution
#include<iostream>
#include <sstream>
#include <iomanip>
#include <algorithm> 
#include<iostream>
#include<string>

using namespace std;
#include "NotationConverter.hpp"
#include "Deque.hpp"

std::string NotationConverter::postfixToInfix(std::string inStr){
    
    Deque list;
    string new_str;
    for (int i = 0; i <= inStr.length(); i++){
        string s(1, inStr[i]);
        if (s == "[" || s == "]" || s == "^" || s == "\\" || s == "{" || s == "}" ){//checking for invalid characters
            throw "Invalid";// Throw in case of invalid character
        }

        else if ( s == "+" || s == "-" || s == "*" || s == "/"){ // check for operators
            string right = list.addFront(); // create a variable to get the fitst string
            list.removeFront(); // remove to get the second string
       
            string left = list.addFront(); // repeat process
            list.removeFront();
     
            new_str = "(" + left + " " + s + " " + right + ")"; // create the string 
            list.addFront(new_str); // add it to the deque
        }
        else if (s != " "){ 
            list.addFront(s); // add the strings to the deque
        }
    }
    
    return new_str; 
}

std::string NotationConverter::prefixToInfix(std::string inStr){
    Deque list;
    string new_str;
    for (int i = inStr.length(); i >= 0; i--){
        string s(1, inStr[i]);
        if (s == "[" || s == "]" || s == "^" || s == "\\" || s == "{" || s == "}" ){
            throw "Invalid";
        }
        else if ( s == "+" || s == "-" || s == "*" || s == "/"){
            string right = list.addFront();
            list.removeFront();
       
            string left = list.addFront();
            list.removeFront();
     
            new_str = "(" + right + " " + s + " " + left + ")";
            list.addFront(new_str);
        }
        else if (s != " "){ 
            list.addFront(s);
        }
    }
    
    return new_str;
}

std::string NotationConverter::infixToPostfix(std::string inStr){
    Deque list;
    string new_str = "";
    for (int i = 0; i <= inStr.length(); i++){
        string s(1, inStr[i]);

        if (s == "[" || s == "]" || s == "^" || s == "\\" || s == "{" || s == "}" ){ 
            throw "Invalid"; 
        }

        if ( s == "+" || s == "-" || s == "*" || s == "/" || s == "("){
            list.addFront(s);
        }
        else if (s == ")") { // when a closing parenthesis is found, we need to go bak until the opening parenthesis is found.
            while (list.addFront() != "("){
                new_str = new_str + list.addFront() + " ";
                list.removeFront();
            }
            list.removeFront();
       
        }
        else if (s != " "){
            new_str += s + " ";
        }
        
    }
    return new_str;
}

std::string NotationConverter::infixToPrefix(std::string inStr){
    Deque list;
    string new_str = "";

    for (int i = inStr.length(); i >= 0; i--){
        string s(1, inStr[i]);

        if (s == "[" || s == "]" || s == "^" || s == "\\" || s == "{" || s == "}" ){
                throw "Invalid";
            }

        else if ( s == "+" || s == "-" || s == "*" || s == "/" || s == ")"){
            list.addFront(s);
        }
        else if (s == "(") {
            while (list.addFront() != ")"){
                new_str = new_str + list.addFront() + " ";
                list.removeFront();
            }
            list.removeFront();
        }
        else if (s != " "){
            new_str = new_str + s + " ";
        }
    }
    reverse(new_str.begin(), new_str.end());
    return new_str;
}

std::string NotationConverter::prefixToPostfix(std::string inStr){
    for (int i = 0; i <= inStr.length(); i++){
        string s(1, inStr[i]);
            if (s == "[" || s == "]" || s == "^" || s == "\\" || s == "{" || s == "}" ){
            throw "Invalid";
            }
    }
    string new_str = infixToPostfix(prefixToInfix(inStr));
    return new_str;
}

std:: string NotationConverter::postfixToPrefix(std::string inStr){
    for (int i = 0; i <= inStr.length(); i++){
        string s(1, inStr[i]);
            if (s == "[" || s == "]" || s == "^" || s == "\\" || s == "{" || s == "}" ){
            throw "Invalid";
            }
    }
    string new_str = infixToPrefix(postfixToInfix(inStr));
    return new_str;
}