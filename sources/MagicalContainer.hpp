#pragma once

#include <iostream>
#include <iterator>

namespace ariel
{
    class MagicalContainer
    {
    private:
        struct Node // the container will be a linked list with 3 orders so the iterator will work in O(1)
        {
            int value;
            int indexDEFAULT;
            int indexASC;
            int indexCROSS;
            int indexPRIME;
            Node* nextNodeDEFAULT;
            Node* nextNodeASC;
            Node* nextNodeCROSS;
            Node* nextNodePRIME;
            Node(int val) : value(val), nextNodeDEFAULT(nullptr), nextNodeASC(nullptr), nextNodeCROSS(nullptr), nextNodePRIME(nullptr),
            indexDEFAULT(-1), indexASC(-1), indexCROSS(-1), indexPRIME(-1) {};
        };

        int containerSize;
        Node* firstNodeDEFAULT;
        Node* firstNodeASC;
        Node* firstNodeCROSS;
        Node* firstNodePRIME;

    public:
        MagicalContainer();
        ~MagicalContainer();
        MagicalContainer(const MagicalContainer&) = default;
        MagicalContainer& operator=(const MagicalContainer&) = delete;
        MagicalContainer(MagicalContainer&&) = default;
        MagicalContainer& operator=(MagicalContainer&&) = delete;
        bool isInContainer(int); // check if a value is already in container
        void reOrderCross();
        void addElement(int);
        void addToDefault(Node*); // adding order (FIFO)
        void addToASC(Node*); // order by value
        void addToCross(Node*); // adding order (FIFO) with cross order 
        void addToPrime(Node*); // order by value (only prime values)
        void setIndexDefault();
        void setIndexASC();
        void setIndexCross();
        void setIndexPrime();
        void removeElement(int);
        void removeFromDefault(int); 
        void removeFromASC(int);
        void removeFromCross(int);
        void removeFromPrime(int);
        int size();

        void containerPrinter(); // for self check
        
        class DefaultIterator // abstarct class for iterator, based on adding sort (FIFO)
        {
        private:
            MagicalContainer& container; // reffernce to container
            Node* currNode; // the node which the iterator points to
        public:
            DefaultIterator(MagicalContainer& container_) : container(container_){this->currNode = this->container.firstNodeDEFAULT;} // default ctor
            DefaultIterator(MagicalContainer& container_, Node* ptr_) : container(container_), currNode(ptr_){} // ctor for end,begin
            virtual ~DefaultIterator() = default; // dtor
            DefaultIterator(const DefaultIterator&) = default; // copy ctor
            DefaultIterator& operator=(const DefaultIterator&) = delete; // copy assignment operator
            DefaultIterator(DefaultIterator&&) = default; // move ctor
            DefaultIterator& operator=(DefaultIterator&&) = delete; // move assignment operator
            virtual Node* firstNode() = 0; // first node getter (virtual)
            virtual Node* nextNode() = 0; // next node getter (virtual)
            int getValue() {return this->getCurrNode()->value;} // value getter
            Node* getCurrNode(){return this->currNode;} // curr node getter
            void setCurrNode(Node* node_){this->currNode = node_;} // curr node setter
            MagicalContainer& getContainer() {return this->container;} // container getter
        };

        class AscendingIterator : DefaultIterator
        {
        public:
            AscendingIterator(MagicalContainer& container_) : DefaultIterator(container_){this->setCurrNode(this->getContainer().firstNodeASC);}
            AscendingIterator(MagicalContainer& container_, Node* ptr_) : DefaultIterator(container_, ptr_){}
            ~AscendingIterator() override = default;
            AscendingIterator(const AscendingIterator&) = default;
            AscendingIterator& operator=(const AscendingIterator&) = delete;
            AscendingIterator(AscendingIterator&&) = default;
            AscendingIterator& operator=(AscendingIterator&&) = delete;
            Node* firstNode() override {return this->getContainer().firstNodeASC;}
            Node* nextNode() override {return this->getCurrNode()->nextNodeASC;}
            MagicalContainer::AscendingIterator begin() {return AscendingIterator(this->getContainer(), this->firstNode());}
            MagicalContainer::AscendingIterator end() {return AscendingIterator(this->getContainer(), nullptr);}
            AscendingIterator& operator++();
            bool operator==(AscendingIterator other){return this->getIndex() == other.getIndex();}
            bool operator!=(AscendingIterator other) {return !(*this == other);}
            bool operator>(AscendingIterator other) {return this->getIndex() > other.getIndex();}
            bool operator<(AscendingIterator other) {return this->getIndex() < other.getIndex();}
            int operator*() {return this->getValue();}
            int getIndex() {return this->getCurrNode() == nullptr? this->getContainer().size() : this->getCurrNode()->indexASC;}
        };

        class SideCrossIterator : DefaultIterator
        {
        public:
            SideCrossIterator(MagicalContainer& container_) : DefaultIterator(container_){this->setCurrNode(this->getContainer().firstNodeCROSS);}
            SideCrossIterator(MagicalContainer& container_, Node* ptr_) : DefaultIterator(container_, ptr_){}
            ~SideCrossIterator() override = default;
            SideCrossIterator(const SideCrossIterator&) = default;
            SideCrossIterator& operator=(const SideCrossIterator&) = delete;
            SideCrossIterator(SideCrossIterator&&) = default;
            SideCrossIterator& operator=(SideCrossIterator&&) = delete;
            Node* firstNode() override {return this->getContainer().firstNodeCROSS;}
            Node* nextNode() override {return this->getCurrNode()->nextNodeCROSS;}
            MagicalContainer::SideCrossIterator begin() {return SideCrossIterator(this->getContainer(), this->firstNode());}
            MagicalContainer::SideCrossIterator end() {return SideCrossIterator(this->getContainer(), nullptr);}
            SideCrossIterator& operator++();
            bool operator==(SideCrossIterator other){return this->getIndex() == other.getIndex();}
            bool operator!=(SideCrossIterator other) {return !(*this == other);}
            bool operator>(SideCrossIterator other) {return this->getIndex() > other.getIndex();}
            bool operator<(SideCrossIterator other) {return this->getIndex() < other.getIndex();}
            int operator*() {return this->getValue();}
            int getIndex() {return this->getCurrNode() == nullptr? this->getContainer().size() : this->getCurrNode()->indexCROSS;}
        };

        class PrimeIterator : DefaultIterator
        {
        public:
            PrimeIterator(MagicalContainer& container_) : DefaultIterator(container_){this->setCurrNode(this->getContainer().firstNodePRIME);}
            PrimeIterator(MagicalContainer& container_, Node* ptr_) : DefaultIterator(container_, ptr_){}
            ~PrimeIterator() override = default;
            PrimeIterator(const PrimeIterator&) = default;
            PrimeIterator& operator=(const PrimeIterator&) = delete;
            PrimeIterator(PrimeIterator&&) = default;
            PrimeIterator& operator=(PrimeIterator&&) = delete;
            Node* firstNode() override {return this->getContainer().firstNodePRIME;}
            Node* nextNode() override {return this->getCurrNode()->nextNodePRIME;}
            MagicalContainer::PrimeIterator begin() {return PrimeIterator(this->getContainer(), this->firstNode());}
            MagicalContainer::PrimeIterator end() {return PrimeIterator(this->getContainer(), nullptr);}
            PrimeIterator& operator++();
            bool operator==(PrimeIterator other) {return this->getIndex() == other.getIndex();}
            bool operator!=(PrimeIterator other) {return !(*this == other);}
            bool operator>(PrimeIterator other) {return this->getIndex() > other.getIndex();}
            bool operator<(PrimeIterator other) {return this->getIndex() < other.getIndex();}
            int operator*() {return this->getValue();}
            int getIndex() {return this->getCurrNode() == nullptr? this->getContainer().size() : this->getCurrNode()->indexPRIME;}
        };
    };

    bool isPrime(int);
}