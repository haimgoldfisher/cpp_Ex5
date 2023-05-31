#include "MagicalContainer.hpp"

namespace ariel
{
    MagicalContainer::MagicalContainer() : firstNodeDEFAULT(nullptr), firstNodeASC(nullptr), firstNodeCROSS(nullptr), firstNodePRIME(nullptr), containerSize(0) {}

    MagicalContainer::~MagicalContainer() 
    {
        if (this->containerSize > 0) // so there are nodes to delete
        {
            Node* curr = this->firstNodeDEFAULT;
            while (curr != nullptr)
            {
                Node* temp = curr->nextNodeDEFAULT;
                delete curr; // free the curr Node
                curr = temp; // move to next
            }
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
    void MagicalContainer::addToCross(Node* newNode) // implement later
    {
        if (firstNodeCROSS == nullptr)
        {
            firstNodeCROSS = newNode;
        }
        else
        {
            Node* curr = firstNodeCROSS;
            while (curr->nextNodeCROSS != nullptr)
            {
                curr = curr->nextNodeCROSS;
            }
            curr->nextNodeCROSS = newNode;
        }
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
            Node* newNode = new Node(val);
            addToDefault(newNode); 
            addToASC(newNode);
            addToCross(newNode);
            addToPrime(newNode);
            this->containerSize++;
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
            removeFromASC(val);
            removeFromCross(val);
            removeFromPrime(val);
            removeFromDefault(val); // + the actual delete of the node
            this->containerSize--;
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