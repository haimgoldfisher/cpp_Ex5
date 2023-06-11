#pragma once

#include <iostream>
#include <cassert>
#include <cmath>

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
        // Helper Functions:
        template<typename T, typename U> void removeFrom(int, bool, Node* &, T, U); // remove value from any order selected
        template<typename T, typename U> void addTo(Node*, bool, Node* &, T, U); // add the node to any order selected
        template<typename T, typename U> void setIndex(Node*, T Node::*, U Node::*); // set the index of any order selected
        bool isInContainer(int) const; // check if a value is already in container
        void reOrderCross(); // it updates the side cross order after remove/add operation on container  

    public:
        MagicalContainer(); // default ctor
        ~MagicalContainer(); // dtor
        MagicalContainer(const MagicalContainer&) = default;
        MagicalContainer& operator=(const MagicalContainer&) = default;
        MagicalContainer(MagicalContainer&&) = default;
        MagicalContainer& operator=(MagicalContainer&&) = delete;
        void addElement(int); // a method that adds a new node to the container
        void removeElement(int); // a method that removes a node from the container
        int size() const; // containerSize getter
        bool operator==(const MagicalContainer& other) const {return this == &other;} // checks if both containers have the same reffernce
        bool operator!=(const MagicalContainer& other) const {return this != &other;}
        void containerPrinter() const; // print all orders - for self check

        class Iterator // abstract class for iterators
        {
            private:
            MagicalContainer& container; // reffernce to container
            Node* currNode; // the node which the iterator points to

            public:
            Iterator(MagicalContainer& container_, Node* ptr_) : container(container_), currNode(ptr_){} // ctor
            virtual ~Iterator() = default;
            Iterator(const Iterator&) = default;
            Iterator& operator=(const Iterator&) = delete;
            Iterator(Iterator&&) = default;
            Iterator& operator=(Iterator&&) = delete;
            MagicalContainer& getContainer() const {return this->container;} // container reffernce getter
            Node* getCurrNode() const {return this->currNode;} // curr node getter
            void setCurrNode(Node* node) {this->currNode = node;} // curr node setter
            int getValue() const {return this->currNode->value;} // curr node value getter
            virtual int getIndex() const = 0; // curr node index getter
        };

        class AscendingIterator : public Iterator // Iterator: ASC Order
        {
        public:
            AscendingIterator(MagicalContainer& container_) : Iterator(container_, container_.firstNodeASC){} // default ctor
            AscendingIterator(MagicalContainer& container_, Node* ptr_) : Iterator(container_, ptr_){} // ctor for end,begin
            ~AscendingIterator() override = default;
            AscendingIterator(const AscendingIterator&) = default;
            AscendingIterator& operator=(const AscendingIterator&);
            AscendingIterator(AscendingIterator&&) = default;
            AscendingIterator& operator=(AscendingIterator&&) = delete;
            MagicalContainer::AscendingIterator begin() {return AscendingIterator(this->getContainer(), this->getContainer().firstNodeASC);}
            MagicalContainer::AscendingIterator end() {return AscendingIterator(this->getContainer(), nullptr);}
            AscendingIterator& operator++(); // it moves the iterator to next element in asc order
            int getIndex() const override {return this->getCurrNode() == nullptr? this->getContainer().containerSize : this->getCurrNode()->indexASC;}
        };

        class SideCrossIterator : public Iterator // Iterator: Side Cross (ASC) Order
        {
        public:
            SideCrossIterator(MagicalContainer& container_) : Iterator(container_, container_.firstNodeCROSS){} // default ctor
            SideCrossIterator(MagicalContainer& container_, Node* ptr_) : Iterator(container_, ptr_){} // ctor for end,begin
            ~SideCrossIterator() override = default;
            SideCrossIterator(const SideCrossIterator&) = default;
            SideCrossIterator& operator=(const SideCrossIterator&);
            SideCrossIterator(SideCrossIterator&&) = default;
            SideCrossIterator& operator=(SideCrossIterator&&) = delete;
            MagicalContainer::SideCrossIterator begin() {return SideCrossIterator(this->getContainer(), this->getContainer().firstNodeCROSS);}
            MagicalContainer::SideCrossIterator end() {return SideCrossIterator(this->getContainer(), nullptr);}
            SideCrossIterator& operator++();
            int getIndex() const override {return this->getCurrNode() == nullptr? this->getContainer().containerSize : this->getCurrNode()->indexCROSS;}
        };

        class PrimeIterator : public Iterator // Iterator: Prime ASC Order
        {
        public:
            PrimeIterator(MagicalContainer& container_) : Iterator(container_, container_.firstNodePRIME){} // default ctor
            PrimeIterator(MagicalContainer& container_, Node* ptr_) : Iterator(container_, ptr_){} // ctor for end,begin
            ~PrimeIterator() override = default;
            PrimeIterator(const PrimeIterator&) = default;
            PrimeIterator& operator=(const PrimeIterator&);
            PrimeIterator(PrimeIterator&&) = default;
            PrimeIterator& operator=(PrimeIterator&&) = delete;
            MagicalContainer::PrimeIterator begin() {return PrimeIterator(this->getContainer(), this->getContainer().firstNodePRIME);}
            MagicalContainer::PrimeIterator end() {return PrimeIterator(this->getContainer(), nullptr);}
            PrimeIterator& operator++();
            int getIndex() const override {return this->getCurrNode() == nullptr? this->getContainer().containerSize : this->getCurrNode()->indexPRIME;} // so end is always max()
        };

        // using template to compare between two unknown iterators:
        template <typename T> friend void checkIT(T iter)
        {
            static_assert(std::is_base_of<Iterator, T>::value, "Accpet only Iterator type!"); // checks if the arg is a child of Iterator
        }
        template <typename T, typename U> friend void checkError(T thisIT, U otherIT) // check errors for bool operations between ITERATORS
        {
            checkIT(thisIT); checkIT(otherIT); // accepts only Iterator object
            T *ptrIT = dynamic_cast<T*>(&otherIT); // try to cast U -> T: can happen only when T == U
            if (ptrIT == nullptr) // cannot cast U to T since there are not the same!
            {
                throw std::runtime_error("diff iterators comparing!");
            }
            if (thisIT.getContainer() != otherIT.getContainer()) // checks if their have the same container ref
            {
                throw std::runtime_error("iterators of diff containers comparing!");
            }
        }
        template <typename T, typename U> friend bool operator==(const T thisIT, const U otherIT) // == between two iterators
        {
            checkError(thisIT, otherIT);
            return thisIT.getIndex() == otherIT.getIndex();
        }
        template <typename T, typename U> friend bool operator!=(const T thisIT, const U otherIT) {return !(thisIT == otherIT);}  // != between two iterators
        template <typename T, typename U> friend bool operator<(const T thisIT, const U otherIT)  // < between two iterators
        {
            checkError(thisIT, otherIT);
            return thisIT.getIndex() < otherIT.getIndex();
        }
        template <typename T, typename U> friend bool operator>(const T thisIT, const U otherIT)  // > between two iterators
        {
            checkError(thisIT, otherIT);
            return thisIT.getIndex() > otherIT.getIndex();
        }
        template <typename T> friend int operator*(const T thisIT){checkIT(thisIT); return thisIT.getValue();} // * for iterator
    };

    bool isPrime(int);
}