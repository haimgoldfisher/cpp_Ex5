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
        }
    }

    void MagicalContainer::addToDefault(Node* newNode)
    {
        if (firstNodeDEFAULT == nullptr)
        {
            firstNodeDEFAULT = newNode;
        }
        else
        {
            Node* curr = firstNodeDEFAULT;
            while (curr->nextNodeDEFAULT != nullptr)
            {
                curr = curr->nextNodeDEFAULT;
            }
            curr->nextNodeDEFAULT = newNode;
        }
        this->setIndexDefault();
    }


    void MagicalContainer::addToASC(Node* newNode)
    {
        if (firstNodeASC == nullptr || newNode->value < firstNodeASC->value)
        {
            newNode->nextNodeASC = firstNodeASC;
            firstNodeASC = newNode;
        }
        else
        {
            Node* curr = firstNodeASC;
            while (curr->nextNodeASC != nullptr && curr->nextNodeASC->value < newNode->value)
            {
                curr = curr->nextNodeASC;
            }
            newNode->nextNodeASC = curr->nextNodeASC;
            curr->nextNodeASC = newNode;
        }
        this->setIndexASC();
    }

    void MagicalContainer::addToCross(Node* newNode)
    {
        if (firstNodeCROSS == nullptr)
        {
            firstNodeCROSS = newNode;
        }
        else
        {
            Node* curr = firstNodeCROSS;
            firstNodeCROSS = newNode;
            newNode->nextNodeCROSS = curr;
            
        }
        this->reOrderCross();
        this->setIndexCross();
    }

    void MagicalContainer::addToPrime(Node* newNode)
    {
        if (isPrime(newNode->value))
        {
            if (firstNodePRIME == nullptr || newNode->value < firstNodePRIME->value)
            {
                newNode->nextNodePRIME = firstNodePRIME;
                firstNodePRIME = newNode;
            }
            else
            {
                Node* curr = firstNodePRIME;
                while (curr->nextNodePRIME != nullptr && curr->nextNodePRIME->value < newNode->value)
                {
                    curr = curr->nextNodePRIME;
                }
                newNode->nextNodePRIME = curr->nextNodePRIME;
                curr->nextNodePRIME = newNode;
            }
            this->setIndexPrime();
        }
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

    void MagicalContainer::setIndexDefault()
    {
        int i = 0;
        Node* curr = this->firstNodeDEFAULT;
        while (curr != nullptr)
        {
            curr->indexDEFAULT = i;
            curr = curr->nextNodeDEFAULT;
            i++;
        }
    }

    void MagicalContainer::setIndexASC()
    {
        int i = 0;
        Node* curr = this->firstNodeASC;
        while (curr != nullptr)
        {
            curr->indexASC = i;
            curr = curr->nextNodeASC;
            i++;
        }
    }

    void MagicalContainer::setIndexCross()
    {
        int i = 0;
        Node* curr = this->firstNodeCROSS;
        while (curr != nullptr)
        {
            curr->indexCROSS = i;
            curr = curr->nextNodeCROSS;
            i++;
        }
    }

    void MagicalContainer::setIndexPrime()
    {
        int i = 0;
        Node* curr = this->firstNodePRIME;
        while (curr != nullptr)
        {
            curr->indexPRIME = i;
            curr = curr->nextNodePRIME;
            i++;
        }
    }

    void MagicalContainer::addElement(int val)
    {
        if (!isInContainer(val)) // every value is unique
        {
            this->containerSize++;
            Node* newNode = new Node(val);
            addToDefault(newNode); 
            addToASC(newNode);
            addToCross(newNode);
            addToPrime(newNode);
        }
    }

    void MagicalContainer::removeFromDefault(int val)
    {
        Node* curr = firstNodeDEFAULT;
        Node* prev = nullptr;

        while (curr != nullptr && curr->value != val)
        {
            prev = curr;
            curr = curr->nextNodeDEFAULT;
        }
        if (prev == nullptr)
        {
            firstNodeDEFAULT = curr->nextNodeDEFAULT;
        }
        else
        {
            prev->nextNodeDEFAULT = curr->nextNodeDEFAULT;
        }
        this->setIndexDefault();
        delete curr; // this is the last time so it can delete the node
    }

    void MagicalContainer::removeFromASC(int val)
    {
        Node* curr = firstNodeASC;
        Node* prev = nullptr;

        while (curr != nullptr && curr->value != val)
        {
            prev = curr;
            curr = curr->nextNodeASC;
        }
        if (prev == nullptr)
        {
            firstNodeASC = curr->nextNodeASC;
        }
        else
        {
            prev->nextNodeASC = curr->nextNodeASC;
        }
        this->setIndexASC();
    }

    void MagicalContainer::removeFromCross(int val)
    {
        Node* curr = firstNodeCROSS;
        Node* prev = nullptr;

        while (curr != nullptr && curr->value != val)
        {
            prev = curr;
            curr = curr->nextNodeCROSS;
        }
        if (prev == nullptr)
        {
            firstNodeCROSS = curr->nextNodeCROSS;
        }
        else
        {
            prev->nextNodeCROSS = curr->nextNodeCROSS;
        }
        reOrderCross();
        this->setIndexCross();
    }

    void MagicalContainer::removeFromPrime(int val)
    {
        if (isPrime(val))
        {
            Node* curr = firstNodePRIME;
            Node* prev = nullptr;

            while (curr != nullptr && curr->value != val)
            {
                prev = curr;
                curr = curr->nextNodePRIME;
            }
            if (prev == nullptr)
            {
                firstNodePRIME = curr->nextNodePRIME;
            }
            else
            {
                prev->nextNodePRIME = curr->nextNodePRIME;
            }
            this->setIndexPrime();
        }
    }

    void MagicalContainer::removeElement(int val)
    {
        if (isInContainer(val))
        {
            this->containerSize--;
            removeFromASC(val);
            removeFromCross(val);
            removeFromPrime(val);
            removeFromDefault(val); // + the actual delete of the node
        }
        else
        {
            throw std::runtime_error("elements does not exist in container!");
        }
        
    }

    int MagicalContainer::size()
    {
        return this->containerSize;
    }

    void MagicalContainer::containerPrinter()
    {
        Node* curr = this->firstNodeDEFAULT;
        std::cout << "Adding Order (FIFO): ";
        while (curr != nullptr) 
        {
            curr->nextNodeDEFAULT == nullptr? std::cout << curr->value << " " : std::cout << curr->value << " -> ";
            curr = curr->nextNodeDEFAULT;
        }
        std::cout << std::endl;

        curr = this->firstNodeASC;
        std::cout << "Ascending Order: ";
        while (curr != nullptr) 
        {
            curr->nextNodeASC == nullptr? std::cout << curr->value << " " : std::cout << curr->value << " -> ";
            curr = curr->nextNodeASC;
        }
        std::cout << std::endl;

        curr = this->firstNodeCROSS;
        std::cout << "Side Cross Order: ";
        while (curr != nullptr) 
        {
            curr->nextNodeCROSS == nullptr? std::cout << curr->value << " " : std::cout << curr->value << " -> ";
            curr = curr->nextNodeCROSS;
        }
        std::cout << std::endl;

        curr = this->firstNodePRIME;
        std::cout << "Prime Order: ";
        while (curr != nullptr) 
        {
            curr->nextNodePRIME == nullptr? std::cout << curr->value << " " : std::cout << curr->value << " -> ";
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
        setCurrNode(nextNode());
        return *this;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() 
    {
        if (this->getCurrNode() == nullptr)
        {
            throw std::runtime_error("the iterator is at the end!");
        }
        setCurrNode(nextNode());
        return *this;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++() 
    {
        if (this->getCurrNode() == nullptr)
        {
            throw std::runtime_error("the iterator is at the end!");
        }
        setCurrNode(nextNode());
        return *this;
    }

    bool isPrime(int num)
    {
        if (num <= 1)
        {
            return false;
        }
        for (int i = 2; i * i <= num; ++i)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    }
}