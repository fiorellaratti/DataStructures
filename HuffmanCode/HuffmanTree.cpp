#include "HuffmanTree.hpp"
#include <vector>
#include <string>
#include <stack>
void rec(HuffmanNode* node, std::map <char, std::string> &newMap,std::string inputStr);



HuffmanTree::HuffmanTree() {
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> priorityQueue;   
    std::string seriaStr;
    std::map <char, std::string> newMap;
}

std::string HuffmanTree::compress(const std::string inputStr){

    std::string outputStr = "";
    std::map <char, int> freqMap ;
    
//Generate a list of the frequency in which characters appear in the string using a map
    for(auto it : inputStr){
        freqMap[it]++;
    }

//Inserting the characters and their frequencies into a priority queue (sorted first by the lowest frequency and then lexicographically)	
    
    for (std::map<char,int>::iterator it=freqMap.begin(); it!=freqMap.end(); ++it){
            HuffmanNode* node = new HuffmanNode(it->first, it->second);
            priorityQueue.insert(node);
            
    }

    //Until there is one element left in the priority queue
    while (priorityQueue.size()>1){

        //Remove two characters/frequencies pairs from the priority queue
        HuffmanNode* pair1=priorityQueue.min();
        //std::cout<<pair1<<std::endl;
        //std::cout<<pair1->getCharacter()<<std::endl;
        priorityQueue.removeMin();


        HuffmanNode* pair2=priorityQueue.min();
        priorityQueue.removeMin();
        
        //Turn them into leaf nodes on a binary tree

        //std::cout<<pair2->getCharacter()<<std::endl;
        //Create an intermediate node to be their parent using the sum of the frequencies for those children
        HuffmanNode* parentChild = new HuffmanNode('\0', pair1->getFrequency()+pair2->getFrequency(), nullptr, pair1, pair2);
        pair1->parent = parentChild;
        pair2->parent = parentChild;

        //Put that intermediate node back in the priority queue
        priorityQueue.insert(parentChild);

    }	
    //std::cout<<"funciona"<<std::endl;

    rec(priorityQueue.min(), newMap, outputStr);

    // //std::cout<<"funciona 2"<<std::endl;
    // for (std::map<char, std::string>::iterator it=newMap.begin(); it!=newMap.end(); ++it){
    //     //  std::cout<<it->first<<"        ";
    //     //  std::cout<<it->second<<std::endl;

    // }
    std::string finalStr = "";
    for(auto it : inputStr){
        //std::cout<<it<<std::endl;
        finalStr += newMap[it];
    }

    HuffmanNode* root= priorityQueue.min();
    recursiveSerialize(root);

    //std::cout<<finalStr<<std::endl;
    //With this encoding, replace the characters in the string with their new variable-length prefix codes
    return finalStr;
}

void rec(HuffmanNode* node, std::map <char, std::string> &newMap,std::string outputStr){
    //std::cout<<node->getCharacter()<<std::endl; 
    //Using the new tree, encode the characters in the string using a map with their prefix code 
    // by traversing the tree to find where the character’s leaf is.
    if (node->isLeaf()){
        newMap[node->getCharacter()] = outputStr;
        return;
    }
    //When traversal goes left, add a 0 to the code, 
    if (node->left!=NULL){
        rec(node->left, newMap, outputStr+"0");
    }
    //when it goes right, add a 1 to the code
    if (node->right!=NULL){
        rec(node->right, newMap, outputStr+"1");
    }        


}


std::string HuffmanTree::serializeTree() const{
    //To serialize the tree I made a recursive function so this one will only return the final string
    return seriaStr;
}

void HuffmanTree::recursiveSerialize(HuffmanNode* node){

    //if it the node is a leaf (external node) then you add a L plus the character to the serialize tree string
    if (node->isLeaf()){
        seriaStr =  seriaStr + "L"+ node->getCharacter();
    }
    //the recursive function will travel through the tree until it finds the leaf
    if (node->left != nullptr){
        recursiveSerialize(node->left);
    }
    if (node->right != nullptr){
        recursiveSerialize(node->right);
    }

    //if it is a branch (internal node) then you add a B to the serialize tree string
    if (node->isBranch()){
        seriaStr = seriaStr + "B";
    }
}


std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree){
    // I created the output string and the stack that will help me decompress
    std::string outputStr = "";
    std::stack<HuffmanNode*> stacky;
    // I did a loop to iterate over the tree
    int tamano = 0;
    while (tamano < serializedTree.length()){
        //When the tree encounters "L", I increased the iterator so it would go to the char next to L
        if (serializedTree[tamano] == 'L') {
            tamano++;
            //I added the new node to the stack
            HuffmanNode* tempNode = new HuffmanNode(serializedTree[tamano], 0);            
            stacky.push(tempNode);

        } 
        // When the tree encounters "B", I created 2 new nodes from the top of the stack which willbuild the tree
        else if (serializedTree[tamano] == 'B') {
            HuffmanNode* pair1 = stacky.top();
            stacky.pop();
            HuffmanNode* pair2 = stacky.top();
            stacky.pop();
            //I created the parent for both of the nodes using the second one as the left and the first one as the right node
            HuffmanNode* parent = new HuffmanNode('\0', 0, nullptr, pair2, pair1);
            pair1->parent = parent;
            pair2->parent = parent;
            //pushing the new parent node to the stack
            stacky.push(parent);
        }
        //increasing the iterator for the loop
        tamano++;
    }
    //making the root from the top of the stack
    HuffmanNode* root = stacky.top();
    //using a temporal value that will be changed
    HuffmanNode* temp = root;

    //another loop to iterate over the input code
    int it = 0;
    while (it < inputCode.length()) {
        //when the char is a 0 the temporary node will move to the left
        if (inputCode[it] == '0') {
            temp = temp->left;
        } 
        //when the char is a 1 the temporary node will move to the right
        else if (inputCode[it] == '1'){
            temp = temp->right;
        }
        // when is a leaf, the output string will start to get filled with the characters
        if (temp->isLeaf()) {
            outputStr += temp->getCharacter();
            temp = root;
        }
        it++;
    }
    
    return outputStr;

}



// int main(){
//     HuffmanTree letras;
//     std::string a = letras.compress("if a machine is expected to be infallible it cannot also be intelligent");
//     return 0;
// }