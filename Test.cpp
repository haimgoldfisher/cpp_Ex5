#pragma

#include "doctest.h"
#include <stdexcept>
#include <iostream>
using namespace std;
#include "sources/MagicalContainer.hpp"
using namespace ariel;

// ******** HELPER FUNCTION *********

auto createContainer(const int nums[], size_t numsSize) // for easy creation of container
{
    MagicalContainer container;
    for (size_t i = 0; i < numsSize; i++) 
    {
        container.addElement(nums[i]);
    }
    return container;
} 
// *************************************

TEST_CASE("Container TEST:")
{
    CHECK_NOTHROW(MagicalContainer dumb);
    MagicalContainer container;
    CHECK_EQ(container.size(), 0);
    CHECK_NOTHROW(container.addElement(1));
    CHECK_EQ(container.size(), 1);
    for (int i = 2; i < 10; i++)
    {
        container.addElement(i);
    }
    CHECK_EQ(container.size(), 9);
    CHECK_NOTHROW(container.removeElement(1));
    CHECK_EQ(container.size(), 8);
}

TEST_CASE("AscendingIterator Simple TEST:")
{
    int numbers[] = {8, -3, 1, 10};
    MagicalContainer container = createContainer(numbers, sizeof(numbers) / sizeof(numbers[0]));
    // Adding Order: 8 -> -3 -> 1 -> 10 , ASC Order: -3 -> 1 -> 8 -> 10
    CHECK_NOTHROW(MagicalContainer::AscendingIterator dumbIter(MagicalContainer dumb));   
    MagicalContainer::AscendingIterator ascIter(container);
    auto myIT = ascIter.begin(); // should be -3
    auto lastIT = ascIter.end(); // should be nullptr
    CHECK(myIT != lastIT);
    CHECK(*myIT == -3);
    CHECK_NOTHROW(myIT++); // -3 -> 1
    CHECK(*myIT == 1);
    CHECK_NOTHROW(++myIT); // 1 -> 8
    CHECK(*myIT == 8);

    auto firstIT = ascIter.begin(); // should be -3
    CHECK(firstIT < myIT); // 8 > -3 in the iterator although 8 added before -3
    CHECK(myIT > firstIT); // 8 > -3 in the iterator although 8 added before -3
    // CHECK_THROWS(firstIT < lastIT); // cannot compare to null
    // CHECK_THROWS(firstIT > lastIT); // cannot compare to null
    // CHECK_THROWS(lastIT++); // end() cannot be increased
    // CHECK_THROWS(++lastIT); // end() cannot be increased
    myIT++; // 8 -> 10
    ++myIT; // 10 -> end
    CHECK(myIT == lastIT);

    // DOES END BIGGER THAN ALL?
    // WHAT TO DO WHEN END++?
    
}

TEST_CASE("SideCrossIterator Simple TEST:")
{
    int numbers[] = {8, -3, 1, 10};
    MagicalContainer container = createContainer(numbers, sizeof(numbers) / sizeof(numbers[0]));
    // Adding Order: 8 -> -3 -> 1 -> 10 , Side Cross Order: -3 -> 10 -> 1 -> 8
    MagicalContainer::SideCrossIterator crossIter(container);
    auto myIT = crossIter.begin(); // should be -3
    auto lastIT = crossIter.end(); // should be nullptr
    CHECK(*myIT == -3);
    CHECK_NOTHROW(myIT++); // -3 -> 10
    CHECK(*myIT == 10);
    CHECK_NOTHROW(++myIT); // 10 -> 1
    CHECK(*myIT == 1);
    myIT++; // 1 -> 8
    CHECK(*myIT == 8); // 8
    

    // DOES END BIGGER THAN ALL?
    // WHAT TO DO WHEN END++?
    
}

TEST_CASE("PrimeIterator Simple TEST:")
{
    int numbers[] = {8, 13, 3, 10, 7};
    MagicalContainer container = createContainer(numbers, sizeof(numbers) / sizeof(numbers[0]));
    // Adding Order: 8 -> 13 -> 3 -> 10 -> 7 , Prime Order: 3 -> 7 -> 13

    // CHECK(isPrime(13));
    // CHECK_FALSE(isPrime(8));

    MagicalContainer::PrimeIterator primeIter(container);
    auto myIT = primeIter.begin(); // should be 3
    auto lastIT = primeIter.end(); // should be nullptr
    CHECK(*myIT == 3);
    CHECK_NOTHROW(myIT++); // 3 -> 7
    CHECK(*myIT == 7);
    CHECK_NOTHROW(++myIT); // 7 -> 13
    CHECK(*myIT == 13);

    // DOES END BIGGER THAN ALL?
    // WHAT TO DO WHEN END++?
    
}

TEST_CASE("AscendingIterator Comparing/Removing/Adding TEST:")
{
    int numbers[] = {11, 3, 14, -1, 0, 3};
    MagicalContainer container = createContainer(numbers, sizeof(numbers) / sizeof(numbers[0]));
    // Adding Order: 11 -> 3 -> 14 -> -1 ->  0 -> 3
    // ASC Order:    -1 -> 0 -> 3  ->  3 -> 11 -> 14
    MagicalContainer::AscendingIterator ascIter(container);
    auto myIT = ascIter.begin(); // should be 3
    for (int i = 0; i < 2; i++)
    {
        myIT++; // -1 -> 0 -> 3
    }
    CHECK(*myIT == 3);
    auto copyIT = myIT; // now copyIT should point to the same Node
    CHECK(*myIT == *copyIT); // they both have 3 value
    CHECK(myIT == copyIT); // since they both on same position
    copyIT++; // 3 -> 3
    CHECK(*myIT == *copyIT); // they both have 3 value
    CHECK(myIT < copyIT); // since myIT is at first 3 & copyIT at second 3  
    myIT++; // now they are again at same position 
    CHECK(myIT == copyIT); // since they both on same position
    myIT++; // 3 -> 11
    container.addElement(7); // so the ASC Order is: -1 -> 0 -> 3 -> 3 -> 7 -> 11 -> 14
    copyIT++; // 3 -> 7
    CHECK((*myIT == 11) + (*copyIT == 7) == 2); // both must be true according to iterator logic
    CHECK(myIT > copyIT); // IMPORTANT! since 11 bigger than 7
    container.addElement(16); // so the ASC Order is: -1 -> 0 -> 3 -> 3 -> 7 -> 11 -> 14 -> 16
    container.removeElement(14); // so the ASC Order is: -1 -> 0 -> 3 -> 3 -> 7 -> 11 -> 16
    CHECK_NOTHROW(myIT++); // 11 -> 16
    container.removeElement(11); // so the ASC Order is: -1 -> 0 -> 3 -> 3 -> 7 -> 16
    CHECK_NOTHROW(++copyIT); // 7 -> 16 
    CHECK((*myIT == *copyIT) + (myIT == copyIT) == 2); // both must be true since they both point to same Node now

    // DOES END BIGGER THAN ALL?
    // WHAT TO DO WHEN END++?
    
}

TEST_CASE("SideCrossIterator Comparing/Removing/Adding TEST:")
{}

TEST_CASE("PrimeIterator Comparing/Removing/Adding TEST:")
{}

TEST_CASE("Iterator Illegal Operations TEST:")
{
    int numbers[] = {8, 5, 4};
    // Adding: 8 -> 5 -> 4
    // ASC:    4 -> 5 -> 8
    // Cross:  4 -> 8 -> 5
    // Prime:  5
    MagicalContainer container = createContainer(numbers, sizeof(numbers) / sizeof(numbers[0]));
    MagicalContainer::AscendingIterator ascIter(container); // 4 -> 5 -> 8
    MagicalContainer::SideCrossIterator crossIter(container); // 4 -> 8 -> 5
    MagicalContainer::PrimeIterator primeIter(container); // 5

    auto ascIT = ascIter.begin(); // 4
    auto crosIT = crossIter.begin(); // 4
    auto primeIT = primeIter.begin(); // 5

    // CHECK_THROWS(ascIT == crosIT); 
    // CHECK_THROWS(ascIT == primeIT); 
    // CHECK_THROWS(crosIT == primeIT);

    // CHECK_THROWS(ascIT != crosIT); 
    // CHECK_THROWS(ascIT != primeIT); 
    // CHECK_THROWS(crosIT != primeIT);

    // CHECK_THROWS(ascIT < crosIT); 
    // CHECK_THROWS(ascIT < primeIT); 
    // CHECK_THROWS(crosIT < primeIT);

    // CHECK_THROWS(ascIT > crosIT); 
    // CHECK_THROWS(ascIT > primeIT); 
    // CHECK_THROWS(crosIT > primeIT);

    MagicalContainer container2 = createContainer(numbers, sizeof(numbers) / sizeof(numbers[0]));
    MagicalContainer::AscendingIterator ascIter2(container); // 4 -> 5 -> 8
    MagicalContainer::SideCrossIterator crossIter2(container); // 4 -> 8 -> 5
    MagicalContainer::PrimeIterator primeIter2(container); // 5

    auto ascIT2 = ascIter2.begin(); // 4
    auto crosIT2 = crossIter2.begin(); // 4
    auto primeIT2 = primeIter2.begin(); // 5

    CHECK_THROWS(ascIT == ascIT2); 
    CHECK_THROWS(primeIT == primeIT2); 
    CHECK_THROWS(crosIT == crosIT2);

    CHECK_THROWS(ascIT != ascIT2); 
    CHECK_THROWS(primeIT != primeIT2); 
    CHECK_THROWS(crosIT != crosIT2);
    
    CHECK_THROWS(ascIT > ascIT2); 
    CHECK_THROWS(primeIT > primeIT2); 
    CHECK_THROWS(crosIT > crosIT2);

    CHECK_THROWS(ascIT < ascIT2); 
    CHECK_THROWS(primeIT < primeIT2); 
    CHECK_THROWS(crosIT < crosIT2);
}