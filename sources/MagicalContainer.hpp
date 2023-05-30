#pragma once

#include <iostream>

typedef enum {DEFAULT = 0, ASCENDING = 1, SIDE_CROSS = 2, PRIME = 3 } ITERATOR_TYPE;

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
        bool isInContainer(int); // check if a value is already in container
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
        
        class DefaultIterator
        {
        private:
            MagicalContainer& container;
            Node* currNode;
        public:
            DefaultIterator(MagicalContainer& container_, Node* ptr_ = nullptr) : container(container_), currNode(ptr_){}
            ~DefaultIterator() = default;
            virtual Node* firstNode() {return this->getContainer().firstNodeDEFAULT;}
            virtual Node* nextNode() {return this->getCurrNode()->nextNodeDEFAULT;}
            virtual ITERATOR_TYPE getType() {return DEFAULT;}
            MagicalContainer::DefaultIterator begin() {return DefaultIterator(this->getContainer(), this->firstNode());}
            MagicalContainer::DefaultIterator end() {return DefaultIterator(this->getContainer(), nullptr);}
            DefaultIterator operator++(int) 
            {
                if (this->getCurrNode() == nullptr)
                {
                    throw std::runtime_error("the iterator is at the end!");
                }
                DefaultIterator tmp = *this;
                setCurrNode(nextNode());
                return tmp;
		    }
            DefaultIterator& operator++() 
            {
                if (this->getCurrNode() == nullptr)
                {
                    throw std::runtime_error("the iterator is at the end!");
                }
                setCurrNode(nextNode());
                return *this;
		    }
            bool operator==(DefaultIterator& other)
            {
                if (this->getType() != other.getType()) // check if the refer to same container?
                {
                    throw std::runtime_error("");
                }
                return this->getIndex() == other.getIndex();
            }
            bool operator!=(DefaultIterator other) {return !(*this == other);}
            bool operator>(DefaultIterator other) {return this->getIndex() > other.getIndex();}
            bool operator<(DefaultIterator other) {return this->getIndex() < other.getIndex();}
            int operator*() {return this->getValue();}
            int getValue() {return this->getCurrNode()->value;}
            Node* getCurrNode(){return this->currNode;}
            void setCurrNode(Node* node_){this->currNode = node_;}
            MagicalContainer& getContainer() {return this->container;}
            int getIndex() {return this->getCurrNode() == nullptr? this->getContainer().size() : this->getCurrNode()->indexDEFAULT;}
        };

        class AscendingIterator : DefaultIterator
        {
        public:
            AscendingIterator(MagicalContainer& container_, Node* ptr_ = nullptr) : DefaultIterator(container_, ptr_){}
            ~AscendingIterator() = default;
            Node* firstNode() {return this->getContainer().firstNodeASC;}
            Node* nextNode() {return this->getCurrNode()->nextNodeASC;}
            ITERATOR_TYPE getType() {return ASCENDING;}
            MagicalContainer::AscendingIterator begin() {return AscendingIterator(this->getContainer(), this->firstNode());}
            MagicalContainer::AscendingIterator end() {return AscendingIterator(this->getContainer(), nullptr);}
            AscendingIterator operator++(int) 
            {
                if (this->getCurrNode() == nullptr)
                {
                    throw std::runtime_error("the iterator is at the end!");
                }
                AscendingIterator tmp = *this;
                setCurrNode(nextNode());
                return tmp;
		    }
            AscendingIterator& operator++() 
            {
                if (this->getCurrNode() == nullptr)
                {
                    throw std::runtime_error("the iterator is at the end!");
                }
                setCurrNode(nextNode());
                return *this;
		    }
            bool operator==(AscendingIterator& other)
            {
                if (this->getType() != other.getType()) // check if the refer to same container?
                {
                    throw std::runtime_error("");
                }
                return this->getIndex() == other.getIndex();
            }
            bool operator!=(AscendingIterator other) {return !(*this == other);}
            bool operator>(AscendingIterator other) {return this->getIndex() > other.getIndex();}
            bool operator<(AscendingIterator other) {return this->getIndex() < other.getIndex();}
            int operator*() {return this->getValue();}
            int getIndex() {return this->getCurrNode() == nullptr? this->getContainer().size() : this->getCurrNode()->indexASC;}
        };

        class SideCrossIterator : DefaultIterator
        {
        public:
            SideCrossIterator(MagicalContainer& container_, Node* ptr_ = nullptr) : DefaultIterator(container_, ptr_){}
            ~SideCrossIterator() = default;
            Node* firstNode() {return this->getContainer().firstNodeCROSS;}
            Node* nextNode() {return this->getCurrNode()->nextNodeCROSS;}
            ITERATOR_TYPE getType() {return SIDE_CROSS;}
            MagicalContainer::SideCrossIterator begin() {return SideCrossIterator(this->getContainer(), this->firstNode());}
            MagicalContainer::SideCrossIterator end() {return SideCrossIterator(this->getContainer(), nullptr);}
            SideCrossIterator operator++(int) 
            {
                if (this->getCurrNode() == nullptr)
                {
                    throw std::runtime_error("the iterator is at the end!");
                }
                SideCrossIterator tmp = *this;
                setCurrNode(nextNode());
                return tmp;
		    }
            SideCrossIterator& operator++() 
            {
                if (this->getCurrNode() == nullptr)
                {
                    throw std::runtime_error("the iterator is at the end!");
                }
                setCurrNode(nextNode());
                return *this;
		    }
            bool operator==(SideCrossIterator& other)
            {
                if (this->getType() != other.getType()) // check if the refer to same container?
                {
                    throw std::runtime_error("");
                }
                return this->getIndex() == other.getIndex();
            }
            bool operator!=(SideCrossIterator other) {return !(*this == other);}
            bool operator>(SideCrossIterator other) {return this->getIndex() > other.getIndex();}
            bool operator<(SideCrossIterator other) {return this->getIndex() < other.getIndex();}
            int operator*() {return this->getValue();}
            int getIndex() {return this->getCurrNode() == nullptr? this->getContainer().size() : this->getCurrNode()->indexCROSS;}
        };

        class PrimeIterator : DefaultIterator
        {
        public:
            PrimeIterator(MagicalContainer& container_, Node* ptr_ = nullptr) : DefaultIterator(container_, ptr_){}
            ~PrimeIterator() = default;
            Node* firstNode() override {return this->getContainer().firstNodePRIME;}
            Node* nextNode() override {return this->getCurrNode()->nextNodePRIME;}
            ITERATOR_TYPE getType() override {return PRIME;}
            MagicalContainer::PrimeIterator begin() {return PrimeIterator(this->getContainer(), this->firstNode());}
            MagicalContainer::PrimeIterator end() {return PrimeIterator(this->getContainer(), nullptr);}
            PrimeIterator operator++(int) 
            {
                if (this->getCurrNode() == nullptr)
                {
                    throw std::runtime_error("the iterator is at the end!");
                }
                PrimeIterator tmp = *this;
                setCurrNode(nextNode());
                return tmp;
		    }
            PrimeIterator& operator++() 
            {
                if (this->getCurrNode() == nullptr)
                {
                    throw std::runtime_error("the iterator is at the end!");
                }
                setCurrNode(nextNode());
                return *this;
		    }
            bool operator==(PrimeIterator& other)
            {
                if (this->getType() != other.getType()) // check if the refer to same container?
                {
                    throw std::runtime_error("");
                }
                return this->getIndex() == other.getIndex();
            }
            bool operator!=(PrimeIterator other) {return !(*this == other);}
            bool operator>(PrimeIterator other) {return this->getIndex() > other.getIndex();}
            bool operator<(PrimeIterator other) {return this->getIndex() < other.getIndex();}
            int operator*() {return this->getValue();}
            int getIndex() {return this->getCurrNode() == nullptr? this->getContainer().size() : this->getCurrNode()->indexPRIME;}
        };
    };

    bool isPrime(int);
}

