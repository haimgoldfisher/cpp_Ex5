#include "MagicalContainer.hpp"

namespace ariel
{
    MagicalContainer::MagicalContainer() : firstNodeDEFAULT(nullptr), firstNodeASC(nullptr), firstNodeCROSS(nullptr), firstNodePRIME(nullptr), containerSize(0) {}

    MagicalContainer::~MagicalContainer()
    {
        if (this->size() > 0)
        {
            Node* curr = firstNodeDEFAULT;
            while (curr != nullptr)
            {
                Node* next = curr->nextNodeDEFAULT;
                delete curr;
                curr = next;
            }
        }
    }

    void MagicalContainer::reOrderCross() 
    {
        if (containerSize > 1)
        {
            Node** arr = new Node*[static_cast<size_t>(containerSize)];
            Node* curr = firstNodeASC;
            int index = 0; // Ascending Order: 2 -> 17 -> 25 
            while (index < containerSize) {
                arr[index] = curr;
                curr = curr->nextNodeASC;
                index+=2;
            }
            index == containerSize? index-- : index-=3;
            while (index > -1) {
                arr[index] = curr;
                curr = curr->nextNodeASC;
                index-=2;
            }
            // now the helper arr contains the Side Cross Order 
            this->firstNodeCROSS = arr[0];
            curr = firstNodeCROSS;
            for (int i = 1; i < containerSize; i++)
            {
                curr->nextNodeCROSS = arr[i];
                curr = arr[i];
                // std::cout << curr->value << std::endl;

            }
            curr->nextNodeCROSS = nullptr;
            delete[] arr;
            this->setIndex(firstNodeCROSS, &Node::nextNodeCROSS, &Node::indexCROSS);
        }
    }

    template<typename T, typename U>
    void MagicalContainer::addTo(Node* newNode, bool asc, Node* &first, T next, U index)
    {
        if (first == nullptr)
        {
            first = newNode;
        }
        else if (asc)
        {
            if (newNode->value < first->value)
            {
                newNode->*next = first;
                first = newNode;
            }
            else // adding order
            {
                Node* curr = first;
                while ((curr->*next) != nullptr && (curr->*next)->value < newNode->value)
                {
                    curr = curr->*next;
                }
                newNode->*next = curr->*next;
                curr->*next = newNode;
            }
        }
        else
        {
            Node* curr = first;
            while (curr->*next != nullptr)
            {
                curr = curr->*next;
            }
            curr->*next = newNode;
        }
        this->setIndex(first, next, index); // update the indexes in container
    }

    bool MagicalContainer::isInContainer(int val)
    {
        Node* curr = this->firstNodeDEFAULT;
        while (curr != nullptr) 
        {
            if (curr->value == val)
            {
                return true;
            }
            curr = curr->nextNodeDEFAULT;
        }
        return false;
    }

    template<typename T, typename U>
    void MagicalContainer::setIndex(Node* first, T Node::* next, U Node::* index)
    {
        int i = 0;
        Node* curr = first;
        while (curr != nullptr)
        {
            curr->*index = i; // update the index of curr node
            curr = curr->*next; // move to next node
            i++;
        }
    }

    void MagicalContainer::addElement(int val)
    {
        if (!isInContainer(val)) // every value is unique
        {
            this->containerSize++; // since we need to use the new size in side cross reorder function
            Node* newNode = new Node(val);
            addTo(newNode, false, firstNodeDEFAULT, &Node::nextNodeDEFAULT, &Node::indexDEFAULT); // adding value - without asc order
            addTo(newNode, true, firstNodeASC, &Node::nextNodeASC, &Node::indexASC); // adding value - with asc order
            addTo(newNode, false, firstNodeCROSS, &Node::nextNodeCROSS, &Node::indexCROSS);
            reOrderCross(); // update the new side cross order
            if (isPrime(val)) // so it belongs to the prime iterator
            {
                addTo(newNode, true, firstNodePRIME, &Node::nextNodePRIME, &Node::indexPRIME); // adding value - with asc order
            }
        }
        // else
        // {
        //     throw std::runtime_error("element is already in container!");
        // }
    }

    template<typename T, typename U>
    void MagicalContainer::removeFrom(int val, bool toDelete, Node* &first, T next, U index)
    {
        Node* curr = first;
        Node* prev = nullptr; 

        while (curr->value != val) // val must be one of them since we already know it
        {
            prev = curr;
            curr = curr->*next;
        }
        if (prev == nullptr) // first node to remove
        {
            first = curr->*next;
        }
        else // mid or last node
        {
            prev->*next = curr->*next;
        }
        this->setIndex(first, next, index); // update the indexes in container
        if (toDelete) // if its the last time so we must acctualy delete that node
        {
            delete curr; // free the node from heap
        }
    }

    void MagicalContainer::removeElement(int val)
    {
        if (isInContainer(val)) // can remove it
        {
            this->containerSize--;
            removeFrom(val, false, firstNodeASC, &Node::nextNodeASC, &Node::indexASC); // remove without delete the node from asc
            removeFrom(val, false, firstNodeCROSS, &Node::nextNodeCROSS, &Node::indexCROSS); // remove without delete the node from side cross
            reOrderCross(); // update the new side cross order
            if (isPrime(val)) // only when the value is prime
            {
                removeFrom(val, false, firstNodePRIME, &Node::nextNodePRIME, &Node::indexPRIME); // remove without delete the node from prime
            }
            removeFrom(val, true, firstNodeDEFAULT, &Node::nextNodeDEFAULT, &Node::indexDEFAULT); // + remove the node
        }
        else
        {
            throw std::runtime_error("element does not exist in container!");
        }
        
    }

    int MagicalContainer::size()
    {
        return this->containerSize;
    }

    void MagicalContainer::containerPrinter()
    {
        Node* curr = this->firstNodeDEFAULT; // move on adding order:
        std::cout << "Adding Order (FIFO): ";
        while (curr != nullptr) 
        {
            curr->nextNodeDEFAULT == nullptr? std::cout << curr->value << " " : std::cout << curr->value << " -> "; // cond for pretty printing
            curr = curr->nextNodeDEFAULT;
        }
        std::cout << std::endl;

        curr = this->firstNodeASC; // move on asc order:
        std::cout << "Ascending Order: ";
        while (curr != nullptr) 
        {
            curr->nextNodeASC == nullptr? std::cout << curr->value << " " : std::cout << curr->value << " -> "; // cond for pretty printing
            curr = curr->nextNodeASC;
        }
        std::cout << std::endl;

        curr = this->firstNodeCROSS; // move on side cross order:
        std::cout << "Side Cross Order: ";
        while (curr != nullptr) 
        {
            curr->nextNodeCROSS == nullptr? std::cout << curr->value << " " : std::cout << curr->value << " -> "; // cond for pretty printing
            curr = curr->nextNodeCROSS;
        }
        std::cout << std::endl;

        curr = this->firstNodePRIME; // move on prime order:
        std::cout << "Prime Order: ";
        while (curr != nullptr) 
        {
            curr->nextNodePRIME == nullptr? std::cout << curr->value << " " : std::cout << curr->value << " -> "; // cond for pretty printing
            curr = curr->nextNodePRIME;
        }
        std::cout << std::endl;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() 
    {
        if (this->getCurrNode() == nullptr)
        {
            throw std::runtime_error("the iterator is at the end!");
        }
        this->setCurrNode(this->getCurrNode()->nextNodeASC);
        return *this;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() 
    {
        if (this->getCurrNode() == nullptr)
        {
            throw std::runtime_error("the iterator is at the end!");
        }
        this->setCurrNode(this->getCurrNode()->nextNodeCROSS);
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() 
    {
        if (this->getCurrNode() == nullptr)
        {
            throw std::runtime_error("the iterator is at the end!");
        }
        this->setCurrNode(this->getCurrNode()->nextNodePRIME);
        return *this;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(MagicalContainer::AscendingIterator other)
    {
        if (this->getContainer() != other.getContainer())
        {
            throw std::runtime_error("different containers!");
        }
        this->setCurrNode(other.getCurrNode());
        return *this;
    }

        MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(MagicalContainer::SideCrossIterator other)
    {
        if (this->getContainer()  != other.getContainer())
        {
            throw std::runtime_error("different containers!");
        }
        this->setCurrNode(other.getCurrNode());
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(MagicalContainer::PrimeIterator other)
    {
        if (this->getContainer() != other.getContainer())
        {
            throw std::runtime_error("different containers!");
        }
        this->setCurrNode(other.getCurrNode());
        return *this;
    }

    bool isPrime(int num)
    {
        if (num <= 1) // 2 is the smallest prime number
        {
            return false;
        }
        for (int i = 2; i <= sqrt(num); i++) // run until sqrt(num) is enough
        {
            if (num % i == 0) // i divide the num
            {
                return false; // not prime
            }
        }
        return true; // prime
    }
}