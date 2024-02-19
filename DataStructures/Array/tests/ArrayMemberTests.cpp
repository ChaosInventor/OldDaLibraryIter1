#include <catch2/catch.hpp>

#include "../Array.hpp"

using namespace Library;
using namespace Library::DataStructures::Array;

TEST_CASE("Member initialization")
{

    Array<int> l_array1((int*)0xB0B, 11);
    Array<int> l_array2((int*)0xD00D00, 11, 88);

    CHECK(l_array1.m_Buffer == (int*)0xB0B);
    CHECK(l_array1.m_Size == 11);
    CHECK(l_array1.m_Capacity == 11);

    CHECK(l_array2.m_Buffer == (int*)0xD00D00);
    CHECK(l_array2.m_Size == 11);
    CHECK(l_array2.m_Capacity == 88);

}

TEST_CASE("Single item construction")
{

    int l_interger = 5;
    Array<int> l_array = l_interger;

    CHECK(l_array.m_Buffer == &l_interger);
    CHECK(l_array.m_Size == 1);
    CHECK(l_array.m_Capacity == 1);

}

TEST_CASE("Moving and copying")
{

    Array<int> l_from((int*)0xB0B, 11);
    Array<int> l_to;

    SECTION("Copy operator")
    {
        Array<int>& l_returnValue = l_to = l_from;
        CHECK(&l_returnValue == &l_to);
    }
    SECTION("Copy constructor")
    {
        l_to = Array<int>(l_from);
    }
    SECTION("Move operator")
    {
        Array<int>& l_returnValue = l_to = (Array<int>&&)l_from;

        CHECK(&l_returnValue == &l_to);
        
        CHECK(l_from.m_Buffer == nullptr);
        CHECK(l_from.m_Capacity == 0);
        CHECK(l_from.m_Size == 0);
    }
    SECTION("Move constructor")
    {
        l_to = Array<int>((Array<int>&&)l_from);

        CHECK(l_from.m_Buffer == nullptr);
        CHECK(l_from.m_Capacity == 0);
        CHECK(l_from.m_Size == 0);
    }

    CHECK(l_to.m_Buffer == (int*)0xB0B);
    CHECK(l_to.m_Size == 11);
    CHECK(l_to.m_Capacity == 11);

}

TEST_CASE("Implicit conversion")
{

    Array<int> l_array((int*)0xB0B, 11);

    int* l_pointer = l_array;
    Size l_size = l_array;

    CHECK(l_pointer == (int*)0xB0B);
    CHECK(l_size == 11);

}

TEST_CASE("Index operator")
{

    Size l_size = GENERATE(Catch::Generators::range(1, 100));

    Array<Size> l_array;

    l_array.m_Buffer = (Size*)malloc(sizeof(Size) * l_size);
    if(l_array.m_Buffer == nullptr)
    {
        FAIL("Could not allocate test resources");
    }

    l_array.m_Size = l_size;
    l_array.m_Capacity = l_size;

    for(Size i = 0; i < l_size; ++i)
    {
        INFO(i);
        l_array[i] = i;
        CHECK(l_array[i] == i);
    }

    free(l_array.m_Buffer);

}

TEST_CASE("Comparison operators")
{

    Size l_size = GENERATE(Catch::Generators::range(2, 100));

    Array<int> l_array;
    Array<int> l_sameArray;
    Array<int> l_diffrentArray;
    Array<int> l_diffrentArray2;
    Array<int> l_emptyArray;
    Array<int> l_emptyArray2;

    CreateArrayAtOfCapacity(l_array, l_size);
    CreateArrayAtOfCapacity(l_diffrentArray2, l_size * 2);
    
    l_array.m_Size = l_size;
    l_diffrentArray2.m_Size = l_size * 2;

    for(Size i = 0; i < l_size; ++i)
    {
        l_array[i] = i;
        l_diffrentArray2[i] = i;
    }
    for(Size i = l_size; i < l_size * 2; ++i)
    {
        l_diffrentArray2[i] = i;
    }

    CreateCopyAtOfArray(l_sameArray, l_array);
    CreateCopyAtOfArray(l_diffrentArray, l_array);

    for(Size i = 0; i < l_size; ++i)
    {
        l_diffrentArray[i] *= 2;
    }

    INFO(l_size);
    CHECK((l_array == l_sameArray));
    CHECK((l_array == l_diffrentArray) == false);    
    CHECK_FALSE((l_array == l_diffrentArray2));
    CHECK_FALSE((l_array == l_emptyArray));
    CHECK((l_emptyArray == l_emptyArray2));

    CHECK_FALSE((l_array != l_sameArray));
    CHECK((l_array != l_diffrentArray) == true);    
    CHECK((l_array != l_diffrentArray2));
    CHECK((l_array != l_emptyArray));
    CHECK_FALSE((l_emptyArray != l_emptyArray2));

    free(l_array.m_Buffer);
    free(l_sameArray.m_Buffer);
    free(l_diffrentArray.m_Buffer);
    free(l_diffrentArray2.m_Buffer);

}
