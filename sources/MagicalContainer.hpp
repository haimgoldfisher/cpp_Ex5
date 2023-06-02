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
        bool operator==(MagicalContainer& other) {return this->firstNodeDEFAULT == other.firstNodeDEFAULT;}
        bool operator!=(MagicalContainer& other) {return !(*this == other);}

        void containerPrinter(); // for self check

        class AscendingIterator
        {
        private:
            MagicalContainer& container; // reffernce to container
            Node* currNode; // the node which the iterator points to
        public:
            AscendingIterator(MagicalContainer& container_) : container(container_), currNode(this->container.firstNodeASC){} // default ctor
            AscendingIterator(MagicalContainer& container_, Node* ptr_) : container(container_), currNode(ptr_){} // ctor for end,begin
            ~AscendingIterator() = default;
            AscendingIterator(const AscendingIterator&) = default;
            AscendingIterator& operator=(const AscendingIterator&);
            AscendingIterator(AscendingIterator&&) = default;
            AscendingIterator& operator=(AscendingIterator&&) = delete;
            MagicalContainer::AscendingIterator begin() {return AscendingIterator(this->container, this->container.firstNodeASC);}
            MagicalContainer::AscendingIterator end() {return AscendingIterator(this->container, nullptr);}
            AscendingIterator& operator++();
            bool operator==(AscendingIterator other){return this->getIndex() == other.getIndex();}
            bool operator!=(AscendingIterator other) {return !(*this == other);}
            bool operator>(AscendingIterator other) {return this->getIndex() > other.getIndex();}
            bool operator<(AscendingIterator other) {return this->getIndex() < other.getIndex();}
            int operator*() {return this->currNode->value;}
            int getIndex() {return this->currNode == nullptr? this->container.containerSize : this->currNode->indexASC;}
        };

        class SideCrossIterator
        {
        private:
            MagicalContainer& container; // reffernce to container
            Node* currNode; // the node which the iterator points to
        public:
            SideCrossIterator(MagicalContainer& container_) : container(container_), currNode(this->container.firstNodeCROSS){} // default ctor
            SideCrossIterator(MagicalContainer& container_, Node* ptr_) : container(container_), currNode(ptr_){} // ctor for end,begin
            ~SideCrossIterator() = default;
            SideCrossIterator(const SideCrossIterator&) = default;
            SideCrossIterator& operator=(const SideCrossIterator&);
            SideCrossIterator(SideCrossIterator&&) = default;
            SideCrossIterator& operator=(SideCrossIterator&&) = delete;
            MagicalContainer::SideCrossIterator begin() {return SideCrossIterator(this->container, this->container.firstNodeCROSS);}
            MagicalContainer::SideCrossIterator end() {return SideCrossIterator(this->container, nullptr);}
            SideCrossIterator& operator++();
            bool operator==(SideCrossIterator other){return this->getIndex() == other.getIndex();}
            bool operator!=(SideCrossIterator other) {return !(*this == other);}
            bool operator>(SideCrossIterator other) {return this->getIndex() > other.getIndex();}
            bool operator<(SideCrossIterator other) {return this->getIndex() < other.getIndex();}
            int operator*() {return this->currNode->value;}
            int getIndex() {return this->currNode == nullptr? this->container.containerSize : this->currNode->indexCROSS;}
        };

        class PrimeIterator
        {
        private:
            MagicalContainer& container; // reffernce to container
            Node* currNode; // the node which the iterator points to
        public:
            PrimeIterator(MagicalContainer& container_) : container(container_), currNode(this->container.firstNodePRIME){} // default ctor
            PrimeIterator(MagicalContainer& container_, Node* ptr_) : container(container_), currNode(ptr_){} // ctor for end,begin
            ~PrimeIterator() = default;
            PrimeIterator(const PrimeIterator&) = default;
            PrimeIterator& operator=(const PrimeIterator&);
            PrimeIterator(PrimeIterator&&) = default;
            PrimeIterator& operator=(PrimeIterator&&) = delete;
            MagicalContainer::PrimeIterator begin() {return PrimeIterator(this->container, this->container.firstNodePRIME);}
            MagicalContainer::PrimeIterator end() {return PrimeIterator(this->container, nullptr);}
            PrimeIterator& operator++();
            bool operator==(PrimeIterator other){return this->getIndex() == other.getIndex();}
            bool operator!=(PrimeIterator other) {return !(*this == other);}
            bool operator>(PrimeIterator other) {return this->getIndex() > other.getIndex();}
            bool operator<(PrimeIterator other) {return this->getIndex() < other.getIndex();}
            int operator*() {return this->currNode->value;}
            int getIndex() {return this->currNode == nullptr? this->container.containerSize : this->currNode->indexPRIME;}
        };
    };

    bool isPrime(int);
}