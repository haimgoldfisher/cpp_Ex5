#pragma

#include "doctest.h"
#include <stdexcept>
#include <iostream>
using namespace std;
#include "sources/MagicalContainer.hpp"
using namespace ariel;

// ******** HELPER FUNCTIONS *********

auto createContainer(const int nums[], size_t numsSize) // for easy creation of container
{
    MagicalContainer container;
    for (size_t i = 0; i < numsSize; i++) 
    {
        container.addElement(nums[i]);
    }
    return container;
}

int primeIteratorLength(MagicalContainer::PrimeIterator iterator) // it checks the length of the prime iterator
{
    int len = 0;
    for (auto it = iterator.begin(); it != iterator.end(); ++it) 
    {
        len++;
    }
    return len;
}
// *************************************

TEST_CASE("Container TEST:")
{
    CHECK_NOTHROW(MagicalContainer dumb);
    MagicalContainer container;
    CHECK_EQ(container.size(), 0);
    CHECK_NOTHROW(container.addElement(1)); // 1
    CHECK_EQ(container.size(), 1);
    for (int i = 2; i < 10; i++)
    {
        container.addElement(i); // 1 -> i=2 -> i=3 -> i=4 -> i=5 -> i=6 -> i=7 -> i=8 -> i=9
    }
    CHECK_EQ(container.size(), 9);
    CHECK_NOTHROW(container.removeElement(1)); // 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9
    CHECK_EQ(container.size(), 8);
    CHECK_NOTHROW(container.removeElement(1)); // should do NOTHING since 1 is not in the container!
    CHECK_EQ(container.size(), 8); // should stay the same
    container.addElement(2); // should do NOTHING since 1 is already in the container!
    CHECK_EQ(container.size(), 8); // should stay the same
}

TEST_CASE("AscendingIterator Empty TEST")
{
    MagicalContainer container;
    MagicalContainer::AscendingIterator ascIter(container);
    auto begin = ascIter.begin();
    auto end = ascIter.end();
    CHECK(begin == end); // since container is empty
    CHECK(ascIter == ascIter.begin());
    CHECK(ascIter == ascIter.end());
}

TEST_CASE("AscendingIterator Simple TEST:")
{
    int numbers[] = {8, -3, 1, 10};
    MagicalContainer container = createContainer(numbers, sizeof(numbers) / sizeof(numbers[0]));
    // Adding Order: 8 -> -3 -> 1 -> 10 , ASC Order: -3 -> 1 -> 8 -> 10
    MagicalContainer::AscendingIterator ascIter(container);
    auto myIT = ascIter.begin(); // should be -3
    auto lastIT = ascIter.end(); // should be nullptr
    CHECK(myIT < lastIT); // end() iterator is always bigger than begin()
    CHECK(*myIT == -3);
    CHECK_NOTHROW(++myIT); // -3 -> 1
    CHECK(*myIT == 1);
    ++myIT; // 1 -> 8
    CHECK(*myIT == 8);

    auto firstIT = ascIter.begin(); // should be -3
    CHECK(firstIT < myIT); // 8 > -3 in the iterator although 8 added before -3
    CHECK(myIT > firstIT); // 8 > -3 in the iterator although 8 added before -3
    CHECK_THROWS(++lastIT); // end() cannot be increased
    ++myIT; // 8 -> 10
    ++myIT; // 10 -> end
    CHECK(myIT == lastIT); 
}

TEST_CASE("SideCrossIterator Empty TEST")
{
    MagicalContainer container;
    MagicalContainer::SideCrossIterator crossIter(container);
    auto begin = crossIter.begin();
    auto end = crossIter.end();
    CHECK(begin == end); // since container is empty
    CHECK(crossIter == crossIter.begin());
    CHECK(crossIter == crossIter.end());
}

TEST_CASE("SideCrossIterator Simple TEST:")
{
    int numbers[] = {8, -3, 1, 10};
    MagicalContainer container = createContainer(numbers, sizeof(numbers) / sizeof(numbers[0]));
    // Adding Order: 8 -> -3 -> 1 -> 10 , Side Cross Order: -3 -> 10 -> 1 -> 8
    MagicalContainer::SideCrossIterator crossIter(container);
    auto myIT = crossIter.begin(); // should be -3
    auto lastIT = crossIter.end(); // should be nullptr
    CHECK(myIT < lastIT);
    CHECK(*myIT == -3);
    CHECK_NOTHROW(++myIT); // -3 -> 10
    CHECK(*myIT == 10);
    ++myIT; // 10 -> 1
    CHECK(*myIT == 1);
    ++myIT; // 1 -> 8
    CHECK(*myIT == 8); // 8
    CHECK_THROWS(++lastIT); // end() cannot be increased
}

TEST_CASE("PrimeIterator Empty TEST")
{
    MagicalContainer container;
    MagicalContainer::PrimeIterator primeIter(container);
    auto begin = primeIter.begin();
    auto end = primeIter.end();
    CHECK(begin == end); // since container is empty
    CHECK(primeIter == primeIter.begin());
    CHECK(primeIter == primeIter.end());
}

TEST_CASE("PrimeIterator Simple TEST:")
{
    int numbers[] = {8, 13, 3, 10, 7};
    MagicalContainer container = createContainer(numbers, sizeof(numbers) / sizeof(numbers[0]));
    // Adding Order: 8 -> 13 -> 3 -> 10 -> 7 , Prime Order: 3 -> 7 -> 13
    MagicalContainer::PrimeIterator primeIter(container);
    auto myIT = primeIter.begin(); // should be 3
    auto lastIT = primeIter.end(); // should be nullptr
    CHECK(myIT < lastIT);
    CHECK(*myIT == 3);
    CHECK_NOTHROW(++myIT); // 3 -> 7
    CHECK(*myIT == 7);
    CHECK_NOTHROW(++myIT); // 7 -> 13
    CHECK(*myIT == 13);
    CHECK_THROWS(++lastIT); // end() cannot be increased
}

TEST_CASE("AscendingIterator Comparing/Removing/Adding TEST:")
{
    int numbers[] = {11, 3, 14, -1, 0};
    MagicalContainer container = createContainer(numbers, sizeof(numbers) / sizeof(numbers[0]));
    // Adding Order: 11 -> 3 -> 14 -> -1 ->  0
    // ASC Order:    -1 -> 0 ->  3 -> 11 -> 14
    MagicalContainer::AscendingIterator ascIter(container);
    auto myIT = ascIter.begin(); // should be -1
    for (int i = 0; i < 2; i++)
    {
        ++myIT; // -1 -> 0 -> 3
    }
    CHECK(*myIT == 3);
    auto copyIT = myIT; // now copyIT should point to the same Node
    CHECK(myIT == copyIT); // they both point to same Node
    container.addElement(7); // so the ASC Order is: -1 -> 0 -> 3 -> 7 -> 11 -> 14
    ++copyIT; // 3 -> 7
    CHECK((*myIT == 3) + (*copyIT == 7) == 2); // both must be true according to iterator logic
    CHECK(myIT < copyIT); // IMPORTANT! since 7 is bigger than 3
    ++copyIT; // 7 -> 11
    ++myIT; // 3 -> 7
    ++myIT; // 7 -> 11
    container.addElement(16); // so the ASC Order is: -1 -> 0 -> 3 -> 7 -> 11 -> 14 -> 16
    ++myIT; // 11 -> 14
    ++myIT; // 14 -> 16
    container.removeElement(14); // so the ASC Order is: -1 -> 0 -> 3 -> 7 -> 11 -> 16
    ++copyIT;// 11 -> 16
    CHECK((myIT == copyIT) + (*myIT == *copyIT) == 2); // both must be true
}

TEST_CASE("SideCrossIterator Comparing/Removing/Adding TEST:")
{
    int numbers[] = {2, 1, 5, 3, 4};
    // Adding Order: 2 -> 1 -> 5 -> 3 -> 4 
    // ASC Order: 1 -> 2 -> 3 -> 4 -> 5
    // Cross Order: 1 -> 5 -> 2 -> 4 -> 3 (ACCORDING TO ASC ORDER!!!)
    MagicalContainer container = createContainer(numbers, sizeof(numbers) / sizeof(numbers[0]));
    MagicalContainer::SideCrossIterator crossIter(container);
    auto myIT = crossIter.begin(); // should be 1
    CHECK(*myIT == 1);
    ++myIT; // 1 -> 5
    auto secondIT = myIT; // should be 5
    ++myIT; // 5 -> 2
    CHECK((myIT > secondIT) + (*myIT < *secondIT) == 2); // since in side cross 5 < 2 but in value: 2 < 5
    container.removeElement(1); // New Cross Order: 2 -> 5 -> 3 -> 4
    CHECK(myIT < secondIT); // since now in cross order, 2 < 5
    container.addElement(0); // New Cross Order: 0 -> 5 -> 2 -> 4 -> 3
    CHECK(myIT > secondIT); // since now in cross order, 5 < 2
    ++secondIT; 
    // now they both at 2
    ++secondIT; // 2 -> 4
    CHECK(myIT < secondIT); // 4 > 2
    container.removeElement(5); // New Cross Order: 0 -> 4 -> 2 -> 3
    CHECK(myIT > secondIT);// 2 > 4
}

TEST_CASE("PrimeIterator Comparing/Removing/Adding TEST:")
{
    int numbers[] = {7, 11, 3};
    // Adding Order: 7 -> 11 -> 3 
    // Prime Order:  3 -> 7 -> 11
    MagicalContainer container = createContainer(numbers, sizeof(numbers) / sizeof(numbers[0]));
    MagicalContainer::PrimeIterator primeIter(container);
    auto myIT = primeIter.begin(); // should be 3
    CHECK(*myIT == 3);
    container.addElement(2); // New Prime Order: 2 -> 3 -> 7 -> 11
    auto secondIT = primeIter.begin(); // should be 2
    CHECK(myIT > secondIT); // since 3 > 2 in prime order
    ++secondIT; // 2 -> 3
    ++myIT; // 3 -> 7
    container.addElement(5); // New Prime Order: 2 -> 3 -> 5 -> 7 -> 11
    ++secondIT; // 3 -> 5
    CHECK(myIT > secondIT); // 7 > 5
}

TEST_CASE("PrimeIterator Size TEST:")
{
    int numbers[] = {2, 5, 7, 11, 13}; // all are prime numbers
    MagicalContainer container = createContainer(numbers, sizeof(numbers) / sizeof(numbers[0]));
    MagicalContainer::PrimeIterator primeIter(container);
    int iterLen = primeIteratorLength(primeIter);
    CHECK_EQ(container.size(), iterLen);
    container.addElement(8);
    iterLen = primeIteratorLength(primeIter);
    CHECK_NE(container.size(), iterLen); // size = 6, iter len is still 5

    int nonPrimeNumbers[] = {-5, -2, -1, 0, 1};
    MagicalContainer container2 = createContainer(nonPrimeNumbers, sizeof(nonPrimeNumbers) / sizeof(nonPrimeNumbers[0]));
    MagicalContainer::PrimeIterator primeIter2(container2);
    iterLen = primeIteratorLength(primeIter2);
    CHECK_EQ(iterLen, 0); // since all those numbers are not prime!!!
}