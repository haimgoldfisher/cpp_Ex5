#include <iostream>
#include "sources/MagicalContainer.hpp"
using namespace ariel;
int main() {
    // Create a MagicalContainer and add some elements
    MagicalContainer container; // 17 -> 2 -> 25 -> 9 -> 3
    container.addElement(17);
    container.addElement(2);
    container.addElement(25);
    container.addElement(9);
    container.addElement(3);

    // Print container size
    std::cout << "Size of container: " << container.size() << std::endl; // should return 5

    container.containerPrinter();

    // Use AscendingIterator to display elements in ascending order
    std::cout << "Elements in ascending order:\n";
    MagicalContainer::AscendingIterator ascIter(container);
    for (auto it = ascIter.begin(); it != ascIter.end(); ++it) {
        std::cout << *it << ' ';   // 2 3 9 17 25
    }
    std::cout << std::endl;

    // Use DescendingIterator to display elements in descending order
    std::cout << "Elements in cross order:\n";
    MagicalContainer::SideCrossIterator crossIter(container);
    for (auto it = crossIter.begin(); it != crossIter.end(); ++it) {
        std::cout << *it << ' ';  // 2 25 3 17 9
    }
    std::cout << std::endl;

    // Use PrimeIterator to display prime numbers only
    std::cout << "Prime numbers:\n";
    MagicalContainer::PrimeIterator primeIter(container);
    for (auto it = primeIter.begin(); it != primeIter.end(); ++it) {
        std::cout << *it << ' ';  // 2 3 17 
    }
    std::cout << std::endl;

    // Remove an element from the container and display the size
    container.removeElement(9);
    std::cout << "Size of container after removing an element: " << container.size() << std::endl;


    std::cout << std::endl << "******** MY DEMO ********" << std::endl << std::endl;

    std::cout << "let's play with the container! first lets take a look at it:" << std::endl << std::endl;
    container.containerPrinter();
    std::cout << "the size of the container: " + std::to_string(container.size()) + " (should be 4)" << std::endl << std::endl;
    std::cout << "let's return 9 to the container and print it again:" << std::endl << std::endl;
    container.addElement(9);
    container.containerPrinter();
    std::cout << "the size of the container: " + std::to_string(container.size()) + " (should be 5)" << std::endl << std::endl;
    MagicalContainer::AscendingIterator asc;
    asc = ascIter.begin();
    std::cout << "the first element in asc iterator: " + std::to_string(*asc) + " (should be 2)" << std::endl;
    ++asc;
    std::cout << "the second element in asc iterator: " + std::to_string(*asc) + " (should be 3)" << std::endl;
    ++asc;
    std::cout << "the third element in asc iterator: " + std::to_string(*asc) + " (should be 9)" << std::endl << std::endl;

    MagicalContainer::SideCrossIterator cross;
    cross = crossIter.begin();
    std::cout << "the first element in side cross iterator: " + std::to_string(*cross) + " (should be 2)" << std::endl;
    ++cross;
    std::cout << "the second element in side cross iterator: " + std::to_string(*cross) + " (should be 25)" << std::endl;
    ++cross;
    std::cout << "the third element in side cross iterator: " + std::to_string(*cross) + " (should be 3)" << std::endl << std::endl;

    MagicalContainer::PrimeIterator prime;
    prime = primeIter.begin();
    std::cout << "the first element in prime iterator: " + std::to_string(*prime) + " (should be 2)" << std::endl;
    ++prime;
    std::cout << "the second element in prime iterator: " + std::to_string(*prime) + " (should be 3)" << std::endl;
    ++prime;
    std::cout << "the third element in prime iterator: " + std::to_string(*prime) + " (should be 17)" << std::endl << std::endl;

    std::cout << "let's remove 2, then lets add 18 & 19. now we can print it:" << std::endl << std::endl;
    container.removeElement(2).addElement(18).addElement(19);
    container.containerPrinter();
    std::cout << "the size of the container: " + std::to_string(container.size()) + " (should be 6)" << std::endl << std::endl;
    std::cout << "where our iterators now?:" << std::endl << std::endl;
    std::cout << "asc iterator: " + std::to_string(*asc) + " (should be 9)" << std::endl;
    std::cout << "side cross iterator: " + std::to_string(*cross) + " (should be 3)" << std::endl;
    std::cout << "prime iterator: " + std::to_string(*prime) + " (should be 17)" << std::endl << std::endl;
    std::cout << "let's move them one step forward and check them:" << std::endl << std::endl;
    ++asc; ++cross; ++prime;
    std::cout << "asc iterator: " + std::to_string(*asc) + " (should be 17)" << std::endl;
    std::cout << "side cross iterator: " + std::to_string(*cross) + " (should be 25)" << std::endl;
    std::cout << "prime iterator: " + std::to_string(*prime) + " (should be 19)" << std::endl << std::endl;

    std::cout << "let's add 29 now we can print it:" << std::endl << std::endl;
    container.addElement(29);
    container.containerPrinter();
    std::cout << "the size of the container: " + std::to_string(container.size()) + " (should be 7)" << std::endl << std::endl;
    std::cout << "where our iterators now?:" << std::endl << std::endl;
    std::cout << "asc iterator: " + std::to_string(*asc) + " (should be 17)" << std::endl;
    std::cout << "side cross iterator: " + std::to_string(*cross) + " (should be 25)" << std::endl;
    std::cout << "prime iterator: " + std::to_string(*prime) + " (should be 19)" << std::endl << std::endl;
    std::cout << "let's move them one step forward and check them:" << std::endl << std::endl;
    ++asc; ++cross; ++prime;
    std::cout << "asc iterator: " + std::to_string(*asc) + " (should be 18)" << std::endl;
    std::cout << "side cross iterator: " + std::to_string(*cross) + " (should be 17)" << std::endl;
    std::cout << "prime iterator: " + std::to_string(*prime) + " (should be 29)" << std::endl << std::endl;

    return 0;
}