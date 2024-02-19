#include <catch2/catch.hpp>

#include "../Array.hpp"

using namespace Library;
using namespace Library::DataStructures::Array;

TEST_CASE("Find and contains tests", "[Array][Immutable]")
{

    Array<int> l_array1;
    Array<int> l_array2;

    Array<int> l_sequence1;
    Array<int> l_sequence2;

    Array<int> l_nullArray;
    Array<int> l_emptyArray;

    CreateArrayAtOfCapacity(l_array1, 15);
    CreateArrayAtOfCapacity(l_array2, 20);

    CreateArrayAtOfCapacity(l_sequence1, 3);
    CreateArrayAtOfCapacity(l_sequence2, 3);

    CreateArrayAtOfCapacity(l_emptyArray, 5);

    //These checks are here to make sure that allocation went well.
    REQUIRE(l_array1.m_Capacity == 15);
    REQUIRE(l_array1.m_Buffer != nullptr);

    REQUIRE(l_array2.m_Capacity == 20);
    REQUIRE(l_array2.m_Buffer != nullptr);

    REQUIRE(l_sequence1.m_Capacity == 3);
    REQUIRE(l_sequence1.m_Buffer != nullptr);

    REQUIRE(l_sequence2.m_Capacity == 3);
    REQUIRE(l_sequence2.m_Buffer != nullptr);

    REQUIRE(l_emptyArray.m_Capacity == 5);
    REQUIRE(l_emptyArray.m_Buffer != nullptr);


    //Zero initialize all of the arrays
    for(Size i = 0; i < 15; ++i)
    {
        l_array1[i] = 0;
        l_array2[i] = 0;
    }
    for(Size i = 15; i < 20; ++i)
    {
        l_array2[i] = 0;
    }

    for(Size i = 0; i < 3; ++i)
    {
        //+1 offset since i starts at 0 but the sequences start at 1
        l_sequence1[i] = i + 1;
        l_sequence2[i] = i + 4;
    }

    l_sequence1.m_Size = 3;
    l_sequence2.m_Size = 3;

    //The entire arrays are used
    l_array1.m_Size = l_array1.m_Capacity;
    l_array2.m_Size = l_array2.m_Capacity;

    //Give the arrays a sequence of 3 numbers near the start.
    l_array1[2] = 1;
    l_array1[3] = 2;
    l_array1[4] = 3;

    l_array2[3] = 4;
    l_array2[4] = 5;
    l_array2[5] = 6;

    //And near the end.
    l_array1[8] = 1;
    l_array1[9] = 2;
    l_array1[10] = 3;

    l_array2[9] = 4;
    l_array2[10] = 5;
    l_array2[11] = 6;

    //Sprinkle in some 3s and 6s
    l_array1[6] = 3;
    l_array1[12] = 3;

    l_array2[7] = 6;
    l_array2[13] = 6;

    //The first array has a 1, the second doesn't and the empty one nither.
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray<int>(1, l_array1) == 2);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray<int>(1, l_array2) == l_array2.m_Size);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray<int>(1, l_nullArray) == l_nullArray.m_Size);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray<int>(1, l_emptyArray) == l_emptyArray.m_Size);

    CHECK(FindIndexOfLastOccurrenceOfArrayInArray<int>(1, l_array1) == 8);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray<int>(1, l_array2) == l_array2.m_Size);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray<int>(1, l_nullArray) == l_nullArray.m_Size);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray<int>(1, l_emptyArray) == l_emptyArray.m_Size);


    //The second array has a 4, the first doesn't and the empty one nither.
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray<int>(4, l_array1) == l_array1.m_Size);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray<int>(4, l_array2) == 3);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray<int>(4, l_nullArray) == l_nullArray.m_Size);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray<int>(4, l_emptyArray) == l_emptyArray.m_Size);

    CHECK(FindIndexOfLastOccurrenceOfArrayInArray<int>(4, l_array1) == l_array1.m_Size);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray<int>(4, l_array2) == 9);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray<int>(4, l_nullArray) == l_nullArray.m_Size);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray<int>(4, l_emptyArray) == l_emptyArray.m_Size);


    CHECK(FindNumberOfInstanceOfArrayInArray<int>(3, l_array1) == 4);
    CHECK(FindNumberOfInstanceOfArrayInArray<int>(3, l_array2) == 0);
    CHECK(FindNumberOfInstanceOfArrayInArray<int>(3, l_nullArray) == 0);
    CHECK(FindNumberOfInstanceOfArrayInArray<int>(3, l_emptyArray) == 0);

    CHECK(FindNumberOfInstanceOfArrayInArray<int>(6, l_array1) == 0);
    CHECK(FindNumberOfInstanceOfArrayInArray<int>(6, l_array2) == 4);
    CHECK(FindNumberOfInstanceOfArrayInArray<int>(6, l_nullArray) == 0);
    CHECK(FindNumberOfInstanceOfArrayInArray<int>(6, l_emptyArray) == 0);


    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_sequence1, l_array1) == 2);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_sequence1, l_array2) == l_array2.m_Size);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_sequence1, l_nullArray) == l_nullArray.m_Size);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_sequence1, l_emptyArray) == l_emptyArray.m_Size);

    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_sequence2, l_array1) == l_array1.m_Size);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_sequence2, l_array2) == 3);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_sequence2, l_nullArray) == l_nullArray.m_Size);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_sequence2, l_emptyArray) == l_emptyArray.m_Size);

    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_nullArray, l_array1) == l_array1.m_Size);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_emptyArray, l_array2) == l_array2.m_Size);

    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_nullArray, l_nullArray) == l_nullArray.m_Size);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_emptyArray, l_emptyArray) == l_emptyArray.m_Size);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_nullArray, l_emptyArray) == l_nullArray.m_Size);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_emptyArray, l_nullArray) == l_emptyArray.m_Size);

    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_array1, l_array1) == 0);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_array2, l_array2) == 0);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_array2, l_array1) == l_array1.m_Size);
    CHECK(FindIndexOfFirstOccurrenceOfArrayInArray(l_array1, l_array2) == l_array2.m_Size);


    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_sequence1, l_array1) == 8);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_sequence1, l_array2) == l_array2.m_Size);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_sequence1, l_nullArray) == l_nullArray.m_Size);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_sequence1, l_emptyArray) == l_emptyArray.m_Size);

    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_sequence2, l_array1) == l_array1.m_Size);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_sequence2, l_array2) == 9);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_sequence2, l_nullArray) == l_nullArray.m_Size);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_sequence2, l_emptyArray) == l_emptyArray.m_Size);

    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_nullArray, l_array1) == l_array1.m_Size);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_emptyArray, l_array2) == l_array2.m_Size);

    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_nullArray, l_nullArray) == l_nullArray.m_Size);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_emptyArray, l_emptyArray) == l_emptyArray.m_Size);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_nullArray, l_emptyArray) == l_nullArray.m_Size);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_emptyArray, l_nullArray) == l_emptyArray.m_Size);

    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_array1, l_array1) == 0);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_array2, l_array2) == 0);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_array2, l_array1) == l_array1.m_Size);
    CHECK(FindIndexOfLastOccurrenceOfArrayInArray(l_array1, l_array2) == l_array2.m_Size);


    CHECK(FindNumberOfInstanceOfArrayInArray(l_sequence1, l_array1) == 2);
    CHECK(FindNumberOfInstanceOfArrayInArray(l_sequence1, l_array2) == 0);
    CHECK(FindNumberOfInstanceOfArrayInArray(l_sequence1, l_nullArray) == 0);
    CHECK(FindNumberOfInstanceOfArrayInArray(l_sequence1, l_emptyArray) == 0);

    CHECK(FindNumberOfInstanceOfArrayInArray(l_sequence2, l_array1) == 0);
    CHECK(FindNumberOfInstanceOfArrayInArray(l_sequence2, l_array2) == 2);
    CHECK(FindNumberOfInstanceOfArrayInArray(l_sequence2, l_nullArray) == 0);
    CHECK(FindNumberOfInstanceOfArrayInArray(l_sequence2, l_emptyArray) == 0);

    CHECK(FindNumberOfInstanceOfArrayInArray(l_nullArray, l_array1) == 0);
    CHECK(FindNumberOfInstanceOfArrayInArray(l_emptyArray, l_array2) == 0);

    CHECK(FindNumberOfInstanceOfArrayInArray(l_nullArray, l_nullArray) == 0);
    CHECK(FindNumberOfInstanceOfArrayInArray(l_emptyArray, l_emptyArray) == 0);
    CHECK(FindNumberOfInstanceOfArrayInArray(l_nullArray, l_emptyArray) == 0);
    CHECK(FindNumberOfInstanceOfArrayInArray(l_emptyArray, l_nullArray) == 0);

    CHECK(FindNumberOfInstanceOfArrayInArray(l_array1, l_array1) == 1);
    CHECK(FindNumberOfInstanceOfArrayInArray(l_array2, l_array2) == 1);
    CHECK(FindNumberOfInstanceOfArrayInArray(l_array2, l_array1) == 0);
    CHECK(FindNumberOfInstanceOfArrayInArray(l_array1, l_array2) == 0);


    CHECK(ArrayIsEmpty(l_array1) == false);
    CHECK(ArrayIsEmpty(l_array2) == false);
    CHECK(ArrayIsEmpty(l_sequence1) == false);
    CHECK(ArrayIsEmpty(l_sequence2) == false);
    CHECK(ArrayIsEmpty(l_emptyArray) == true);
    CHECK(ArrayIsEmpty(l_nullArray) == true);


    CHECK(ArrayContainsArray<int>(l_array1, 1) == true);
    CHECK(ArrayContainsArray<int>(l_array2, 1) == false);
    CHECK(ArrayContainsArray<int>(l_nullArray, 1) == false);
    CHECK(ArrayContainsArray<int>(l_emptyArray, 1) == false);

    CHECK(ArrayContainsArray<int>(l_array1, 4) == false);
    CHECK(ArrayContainsArray<int>(l_array2, 4) == true);
    CHECK(ArrayContainsArray<int>(l_nullArray, 4) == false);
    CHECK(ArrayContainsArray<int>(l_emptyArray, 4) == false);


    CHECK(ArrayContainsArray(l_array1, l_sequence1) == true);
    CHECK(ArrayContainsArray(l_array2, l_sequence1) == false);
    CHECK(ArrayContainsArray(l_nullArray, l_sequence1) == false);
    CHECK(ArrayContainsArray(l_emptyArray, l_sequence1) == false);

    CHECK(ArrayContainsArray(l_array1, l_sequence2) == false);
    CHECK(ArrayContainsArray(l_array2, l_sequence2) == true);
    CHECK(ArrayContainsArray(l_nullArray, l_sequence2) == false);
    CHECK(ArrayContainsArray(l_emptyArray, l_sequence2) == false);

    CHECK(ArrayContainsArray(l_nullArray, l_array1) == false);
    CHECK(ArrayContainsArray(l_emptyArray, l_array2) == false);

    CHECK(ArrayContainsArray(l_nullArray, l_nullArray) == false);
    CHECK(ArrayContainsArray(l_emptyArray, l_emptyArray) == false);
    CHECK(ArrayContainsArray(l_nullArray, l_emptyArray) == false);
    CHECK(ArrayContainsArray(l_emptyArray, l_nullArray) == false);

    CHECK(ArrayContainsArray(l_array1, l_array1) == true);
    CHECK(ArrayContainsArray(l_array2, l_array2) == true);
    CHECK(ArrayContainsArray(l_array1, l_array2) == false);
    CHECK(ArrayContainsArray(l_array2, l_array1) == false);


    CHECK(ArrayStartsWithArray<int>(l_array1, 0) == true);
    CHECK(ArrayStartsWithArray<int>(l_array2, 0) == true);
    CHECK(ArrayStartsWithArray<int>(l_emptyArray, 0) == false);
    CHECK(ArrayStartsWithArray<int>(l_nullArray, 0) == false);

    CHECK(ArrayStartsWithArray<int>(l_array1, 1) == false);
    CHECK(ArrayStartsWithArray<int>(l_array2, 1) == false);
    CHECK(ArrayStartsWithArray<int>(l_emptyArray, 1) == false);
    CHECK(ArrayStartsWithArray<int>(l_nullArray, 1) == false);


    CHECK(ArrayEndsWithArray<int>(l_array1, 0) == true);
    CHECK(ArrayEndsWithArray<int>(l_array2, 0) == true);
    CHECK(ArrayEndsWithArray<int>(l_emptyArray, 0) == false);
    CHECK(ArrayEndsWithArray<int>(l_nullArray, 0) == false);

    CHECK(ArrayEndsWithArray<int>(l_array1, 1) == false);
    CHECK(ArrayEndsWithArray<int>(l_array2, 1) == false);
    CHECK(ArrayEndsWithArray<int>(l_emptyArray, 1) == false);
    CHECK(ArrayEndsWithArray<int>(l_nullArray, 1) == false);

    //An example of a stack arrays
    int l_zeroZero[] = {0, 0};
    Array<int> l_zeroZeroSequence(l_zeroZero, 2);

    int l_oneOne[] = {1, 1};
    Array<int> l_oneOneSequence(l_oneOne, 2);

    CHECK(ArrayStartsWithArray(l_array1, l_zeroZeroSequence) == true);
    CHECK(ArrayStartsWithArray(l_array2, l_zeroZeroSequence) == true);
    CHECK(ArrayStartsWithArray(l_emptyArray, l_zeroZeroSequence) == false);
    CHECK(ArrayStartsWithArray(l_nullArray, l_zeroZeroSequence) == false);

    CHECK(ArrayStartsWithArray(l_array1, l_oneOneSequence) == false);
    CHECK(ArrayStartsWithArray(l_array2, l_oneOneSequence) == false);
    CHECK(ArrayStartsWithArray(l_emptyArray, l_oneOneSequence) == false);
    CHECK(ArrayStartsWithArray(l_nullArray, l_oneOneSequence) == false);

    CHECK(ArrayStartsWithArray(l_emptyArray, l_array1) == false);
    CHECK(ArrayStartsWithArray(l_nullArray, l_array2) == false);

    CHECK(ArrayStartsWithArray(l_emptyArray, l_nullArray) == false);
    CHECK(ArrayStartsWithArray(l_nullArray, l_emptyArray) == false);
    CHECK(ArrayStartsWithArray(l_emptyArray, l_emptyArray) == false);
    CHECK(ArrayStartsWithArray(l_nullArray, l_nullArray) == false);

    CHECK(ArrayStartsWithArray(l_array1, l_array1) == true);
    CHECK(ArrayStartsWithArray(l_array1, l_array2) == false);
    CHECK(ArrayStartsWithArray(l_array2, l_array2) == true);
    CHECK(ArrayStartsWithArray(l_array2, l_array1) == false);


    CHECK(ArrayEndsWithArray(l_array1, l_zeroZeroSequence) == true);
    CHECK(ArrayEndsWithArray(l_array2, l_zeroZeroSequence) == true);
    CHECK(ArrayEndsWithArray(l_emptyArray, l_zeroZeroSequence) == false);
    CHECK(ArrayEndsWithArray(l_nullArray, l_zeroZeroSequence) == false);

    CHECK(ArrayEndsWithArray(l_array1, l_oneOneSequence) == false);
    CHECK(ArrayEndsWithArray(l_array2, l_oneOneSequence) == false);
    CHECK(ArrayEndsWithArray(l_emptyArray, l_oneOneSequence) == false);
    CHECK(ArrayEndsWithArray(l_nullArray, l_oneOneSequence) == false);

    CHECK(ArrayEndsWithArray(l_emptyArray, l_array1) == false);
    CHECK(ArrayEndsWithArray(l_nullArray, l_array2) == false);

    CHECK(ArrayEndsWithArray(l_emptyArray, l_nullArray) == false);
    CHECK(ArrayEndsWithArray(l_nullArray, l_emptyArray) == false);
    CHECK(ArrayEndsWithArray(l_emptyArray, l_emptyArray) == false);
    CHECK(ArrayEndsWithArray(l_nullArray, l_nullArray) == false);

    CHECK(ArrayEndsWithArray(l_array1, l_array1) == true);
    CHECK(ArrayEndsWithArray(l_array1, l_array2) == false);
    CHECK(ArrayEndsWithArray(l_array2, l_array2) == true);
    CHECK(ArrayEndsWithArray(l_array2, l_array1) == false);


    DestoryArray(l_array1);
    DestoryArray(l_array2);
    DestoryArray(l_sequence1);
    DestoryArray(l_sequence2);
    DestoryArray(l_emptyArray);

}
