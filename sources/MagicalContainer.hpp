#pragma once

#include <iostream>
#include <cassert>

namespace ariel
{   
    class MagicalContainer
    {
    private:
        struct Node // the container will be a linked list with 3 orders so the iterator will work in O(1)
        {
            int value; // the int the node holds
            int indexDEFAULT; // index for adding order
            int indexASC; // index for asc order
            int indexCROSS; // index for side cross order
            int indexPRIME; // index for prime order
            Node* nextNodeDEFAULT; // pointer to next node in adding order
            Node* nextNodeASC; // pointer to next node in asc order
            Node* nextNodeCROSS; // pointer to next node in side cross order
            Node* nextNodePRIME; // pointer to next node in prime order
            Node(int val) : value(val), nextNodeDEFAULT(nullptr), nextNodeASC(nullptr), nextNodeCROSS(nullptr), nextNodePRIME(nullptr),
            indexDEFAULT(-1), indexASC(-1), indexCROSS(-1), indexPRIME(-1) {}; // ctor for a new node, given it's int value
        };

        int containerSize; // the size of the container
        Node* firstNodeDEFAULT; // first node in adding order
        Node* firstNodeASC; // first node in asc order
        Node* firstNodeCROSS; // first node in side cross order
        Node* firstNodePRIME; // first node in prime order

    public:
        MagicalContainer(); // default ctor
        ~MagicalContainer(); // dtor
        MagicalContainer(const MagicalContainer&) = default;
        MagicalContainer& operator=(const MagicalContainer&) = default;
        MagicalContainer(MagicalContainer&&) = default;
        MagicalContainer& operator=(MagicalContainer&&) = delete;
        bool isInContainer(int); // check if a value is already in container
        void reOrderCross(); // it updates the side cross order after remove/add operation on container  
        void addElement(int); // a method that adds a new node to the container
        void addToDefault(Node*); // adding order (FIFO)
        void addToASC(Node*); // order by value
        void addToCross(Node*); // adding order (FIFO) with cross order 
        void addToPrime(Node*); // order by value (only prime values)
        template<typename T, typename U>
        void setIndex(Node*, T Node::*, U Node::*); // set the index of any order selected
        void removeElement(int); // a method that removes a node from the container
        void removeFromDefault(int); 
        void removeFromASC(int);
        void removeFromCross(int);
        void removeFromPrime(int);
        int size(); // containerSize getter
        bool operator==(MagicalContainer& other) {return this->firstNodeDEFAULT == other.firstNodeDEFAULT;} // checks if both container are the same 
        bool operator!=(MagicalContainer& other) {return !(*this == other);} // checks if both container are not the same 

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
            AscendingIterator& operator++(); // it moves the iterator to next element in asc order
            int operator*() {return this->currNode->value;}
            int getIndex() {return this->currNode == nullptr? this->container.containerSize : this->currNode->indexASC;}
            MagicalContainer& getContainer() {return this->container;} // container reffernce getter
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
            int operator*() {return this->currNode->value;}
            int getIndex() {return this->currNode == nullptr? this->container.containerSize : this->currNode->indexCROSS;}
            MagicalContainer& getContainer() {return this->container;}
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
            int operator*() {return this->currNode->value;}
            int getIndex() {return this->currNode == nullptr? this->container.containerSize : this->currNode->indexPRIME;} // so end is always max()
            MagicalContainer& getContainer() {return this->container;}
        };

        // using template to compare between two unknown iterators:
        template <typename T1, typename T2>
        friend bool operator==(T1 thisIT, T2 otherIT)
        {
            T1 *ptrIT = dynamic_cast<T1*>(&otherIT); // try to cast T2 -> T1: can happen only when T1 == T2
            if (ptrIT == nullptr) // cannot cast T2 to T1 since there are not the same!
            {
                throw std::runtime_error("diff iterators comparing!");
            }
            if (thisIT.getContainer() != otherIT.getContainer()) // checks if their have the same container ref
            {
                throw std::runtime_error("iterators of diff containers comparing!");
            }
            return thisIT.getIndex() == otherIT.getIndex();
        }

        template <typename T1, typename T2>
        friend bool operator!=(T1 thisIT, T2 otherIT)
        {
            return !(thisIT == otherIT);
        }

        template <typename T1, typename T2>
        friend bool operator<(T1 thisIT, T2 otherIT)
        {
            T1 *ptrIT = dynamic_cast<T1*>(&otherIT); // try to cast T2 -> T1: can happen only when T1 == T2
            if (ptrIT == nullptr) // cannot cast T2 to T1 since there are not the same!
            {
                throw std::runtime_error("diff iterators comparing!");
            }
            if (thisIT.getContainer() != otherIT.getContainer()) // checks if their have the same container ref
            {
                throw std::runtime_error("iterators of diff containers comparing!");
            }
            return thisIT.getIndex() < otherIT.getIndex();
        }

        template <typename T1, typename T2>
        friend bool operator>(T1 thisIT, T2 otherIT)
        {
            T1 *ptrIT = dynamic_cast<T1*>(&otherIT); // try to cast T2 -> T1: can happen only when T1 == T2
            if (ptrIT == nullptr) // cannot cast T2 to T1 since there are not the same!
            {
                throw std::runtime_error("diff iterators comparing!");
            }
            if (thisIT.getContainer() != otherIT.getContainer()) // checks if their have the same container ref
            {
                throw std::runtime_error("iterators of diff containers comparing!");
            }
            return thisIT.getIndex() > otherIT.getIndex();
        }
    };

    bool isPrime(int);
}