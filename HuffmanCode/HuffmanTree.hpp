#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <string>
#include <map>
#include "HeapQueue.hpp"
#include "HuffmanBase.hpp"


class HuffmanTree: virtual public HuffmanTreeBase  {
    public: 
        HuffmanTree();
        std::string compress(const std::string inputStr);
        std::string serializeTree() const;
        std::string decompress(const std::string inputCode, const std::string serializedTree); 
        void recursiveSerialize(HuffmanNode* node);

    private: 
        HuffmanNode* root;
        HeapQueue<HuffmanNode*, HuffmanNode::Compare> priorityQueue;
        std::string seriaStr="";
        std::map <char, std::string> newMap;
};

#endif