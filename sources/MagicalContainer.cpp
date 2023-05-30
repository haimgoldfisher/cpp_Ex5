#include "MagicalContainer.hpp"

namespace ariel
{
    MagicalContainer::MagicalContainer() : firstNodeASC(nullptr), firstNodeCROSS(nullptr), firstNodePRIME(nullptr), containerSize(0) {}

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
        if (firstNodeASC == nullptr)
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
    }

    void MagicalContainer::addToASC(Node* newNode)
    {
        if (firstNodeASC == nullptr || newNode->value <= firstNodeASC->value)
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
    }

    void MagicalContainer::addToPrime(Node* newNode)
    {
        if (isPrime(newNode->value))
        {
            if (firstNodePRIME == nullptr || newNode->value <= firstNodePRIME->value)
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
        }
    }

    void MagicalContainer::addElement(int val)
    {
        Node* newNode = new Node(val);
        addToDefault(newNode); 
        addToASC(newNode);
        addToCross(newNode);
        addToPrime(newNode);
        this->containerSize++;
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

        if (curr == nullptr)
        {
            return; // Value not found
        }

        if (prev == nullptr)
        {
            firstNodeDEFAULT = curr->nextNodeDEFAULT;
        }
        else
        {
            prev->nextNodeDEFAULT = curr->nextNodeDEFAULT;
        }
        this->containerSize--;
        delete curr;
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

        if (curr == nullptr)
        {
            return; // Value not found
        }

        if (prev == nullptr)
        {
            firstNodeASC = curr->nextNodeASC;
        }
        else
        {
            prev->nextNodeASC = curr->nextNodeASC;
        }

        delete curr;
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

        if (curr == nullptr)
        {
            return; // Value not found
        }

        if (prev == nullptr)
        {
            firstNodeCROSS = curr->nextNodeCROSS;
        }
        else
        {
            prev->nextNodeCROSS = curr->nextNodeCROSS;
        }

        delete curr;
    }

    void MagicalContainer::removeFromPrime(int val)
    {
        if (!isPrime(val))
        {
            return; // Value is not prime
        }

        Node* curr = firstNodePRIME;
        Node* prev = nullptr;

        while (curr != nullptr && curr->value != val)
        {
            prev = curr;
            curr = curr->nextNodePRIME;
        }

        if (curr == nullptr)
        {
            return; // Value not found
        }

        if (prev == nullptr)
        {
            firstNodePRIME = curr->nextNodePRIME;
        }
        else
        {
            prev->nextNodePRIME = curr->nextNodePRIME;
        }

        delete curr;
    }

    void MagicalContainer::removeElement(int val)
    {
        removeFromDefault(val);
        removeFromASC(val);
        removeFromCross(val);
        removeFromPrime(val);
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
