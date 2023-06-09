#include "MagicalContainer.hpp"

namespace ariel
{
    MagicalContainer::MagicalContainer() : firstNodeDEFAULT(nullptr), firstNodeASC(nullptr), firstNodeCROSS(nullptr), firstNodePRIME(nullptr), containerSize(0) {}

    MagicalContainer::~MagicalContainer() // run over the default order and delete each node
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
        } // no need to delete nullptr...
    }

    void MagicalContainer::reOrderCross() 
    {
        if (containerSize > 1) // trivial
        {
            Node** arr = new Node*[static_cast<size_t>(containerSize)];
            Node* curr = firstNodeASC;
            int index = 0; // Ascending Order: 2 -> 17 -> 25 
            while (index < containerSize) { // fill the small numbers 
                arr[index] = curr;
                curr = curr->nextNodeASC;
                index+=2; // jump by 2 indexes
            }
            index == containerSize? index-- : index-=3;
            while (index > -1) { // fill the big numbers
                arr[index] = curr;
                curr = curr->nextNodeASC;
                index-=2;// jump by 2 indexes
            }
            // now the helper arr contains the Side Cross Order 
            this->firstNodeCROSS = arr[0];
            curr = firstNodeCROSS;
            curr->indexCROSS = 0; // set the index of first to 0
            for (int i = 1; i < containerSize; i++) // now update the side cross order by the helper arr
            {
                curr->nextNodeCROSS = arr[i]; // make arr[i] curr next node
                curr = arr[i]; // update curr to arr[i]
                curr->indexCROSS = i; // update curr's index to i
            }
            curr->nextNodeCROSS = nullptr;
            delete[] arr;
        }
    }

    template<typename T>
    void MagicalContainer::addTo(Node* newNode, bool asc, Node* &first, T Node::* next)
    {
        if (first == nullptr) // trivial - empty container
        {
            first = newNode;
            return;
        }
        Node* curr = first; // ptr to first node in selected order
        if (asc) // adding by asc order
        {
            if (newNode->value < curr->value) // the new node is the smallest node case
            {
                newNode->*next = curr; // the first is the second
                first = newNode; // update newNode as the first node
            }
            else 
            {
                while ((curr->*next) != nullptr && (curr->*next)->value < newNode->value) // run untill find bigger value
                {
                    curr = curr->*next;
                }
                newNode->*next = curr->*next; // newNode points to next
                curr->*next = newNode; // curr points to newNode
            }
        }
        else // adding by adding order
        {
            while (curr->*next != nullptr) // run until last node
            {
                curr = curr->*next;
            }
            curr->*next = newNode; // newNode is the last
        }
    }

    bool MagicalContainer::isInContainer(int val) const
    {
        Node* curr = this->firstNodeDEFAULT; // because default has all nodes
        while (curr != nullptr) // search the value in the container until nullptr
        {
            if (curr->value == val)
            {
                return true; // found the value
            }
            curr = curr->nextNodeDEFAULT;
        }
        return false; // didnt find the value
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

    MagicalContainer& MagicalContainer::addElement(int val)
    {
        if (!isInContainer(val)) // every value is unique
        {
            this->containerSize++; // since we need to use the new size in side cross reorder function
            Node* newNode = new Node(val);
            addTo(newNode, false, firstNodeDEFAULT, &Node::nextNodeDEFAULT); // adding value - without asc order
            addTo(newNode, true, firstNodeASC, &Node::nextNodeASC); // adding value - with asc order
            setIndex(firstNodeASC, &Node::nextNodeASC, &Node::indexASC);
            addTo(newNode, false, firstNodeCROSS, &Node::nextNodeCROSS);
            reOrderCross(); // update the new side cross order
            if (isPrime(val)) // so it belongs to the prime iterator
            {
                addTo(newNode, true, firstNodePRIME, &Node::nextNodePRIME); // adding value - with asc order
            }
        }
        return *this;
        // else
        // {
        //     throw std::runtime_error("element is already in container!");
        // }
    }

    template<typename T>
    void MagicalContainer::removeFrom(int val, bool toDelete, Node* &first, T Node::* next)
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
        if (toDelete) // if its the last time so we must acctualy delete that node
        {
            delete curr; // free the node from heap
        }
    }

    MagicalContainer& MagicalContainer::removeElement(int val)
    {
        if (isInContainer(val)) // can remove it
        {
            this->containerSize--;
            removeFrom(val, false, firstNodeASC, &Node::nextNodeASC); // remove without delete the node from asc
            removeFrom(val, false, firstNodeCROSS, &Node::nextNodeCROSS); // remove without delete the node from side cross
            setIndex(firstNodeASC, &Node::nextNodeASC, &Node::indexASC);
            reOrderCross(); // update the new side cross order
            if (isPrime(val)) // only when the value is prime
            {
                removeFrom(val, false, firstNodePRIME, &Node::nextNodePRIME); // remove without delete the node from prime
            }
            removeFrom(val, true, firstNodeDEFAULT, &Node::nextNodeDEFAULT); // + remove the node
        }
        else
        {
            throw std::runtime_error("element does not exist in container!");
        }
        return *this;
    }

    int MagicalContainer::size() const
    {
        return this->containerSize;
    }

    void MagicalContainer::containerPrinter() const
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
        if (this->getCurrNode() == nullptr) // so end() cannot 'move'
        {
            throw std::runtime_error("the iterator is at the end!");
        }
        this->setCurrNode(this->getCurrNode()->nextNodeASC);
        return *this;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() 
    {
        if (this->getCurrNode() == nullptr) // so end() cannot 'move'
        {
            throw std::runtime_error("the iterator is at the end!");
        }
        this->setCurrNode(this->getCurrNode()->nextNodeCROSS);
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() 
    {
        if (this->getCurrNode() == nullptr) // so end() cannot 'move'
        {
            throw std::runtime_error("the iterator is at the end!");
        }
        this->setCurrNode(this->getCurrNode()->nextNodePRIME);
        return *this;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const MagicalContainer::AscendingIterator& other)
    {
        if (this->getContainer() != other.getContainer()) // cannot change container
        {
            throw std::runtime_error("different containers!");
        }
        this->setCurrNode(other.getCurrNode());
        return *this;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const MagicalContainer::SideCrossIterator& other)
    {
        if (this->getContainer() != other.getContainer()) // cannot change container
        {
            throw std::runtime_error("different containers!");
        }
        this->setCurrNode(other.getCurrNode());
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const MagicalContainer::PrimeIterator& other)
    {
        if (this->getContainer() != other.getContainer()) // cannot change container
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