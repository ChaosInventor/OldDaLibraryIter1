#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../Array.hpp"
#include "../../../Debugging/Debugging.hpp"

using namespace Library;
using namespace Library::DataStructures::Array;
using namespace Debugging;

TEST_CASE("Create empty array")
{

    Array<int> l_empty;

    SECTION("Constructor")
    {
        l_empty = Array<int>();
    }
    SECTION("Create with capacity, capacity 0")
    {
        SECTION("Defaults")
        {
            CreateArrayAtOfCapacity(l_empty, 0);
        }
        SECTION("Customs")
        {
            bool l_called = false;

            CreateArrayAtOfCapacityUsingAllocator(
                l_empty, 0,
                malloc, &GeneralErrorCallback, &l_called 
            );

            CHECK(l_called == false);
        }


        CHECK(l_empty.m_Capacity == 0);
        CHECK(l_empty.m_Size == 0);
    }
    SECTION("Create with capacity alloc error")
    {
        bool l_called = false;

        CreateArrayAtOfCapacityUsingAllocator(
            l_empty, 10,
            NullMalloc, &GeneralErrorCallback, &l_called
        );

        CHECK(l_called == true);
        CHECK(l_empty.m_Capacity == 0);
        CHECK(l_empty.m_Size == 0);
    }
    SECTION("Copy empty array")
    {
        Array<int> l_otherEmpty = {nullptr, 0, 0};
        SECTION("Defaults")
        {
            CreateCopyAtOfArray(l_empty, l_otherEmpty);
        }
        SECTION("Customs")
        {
            bool l_called = false;

            CreateCopyAtOfArrayUsingAllocator(
                l_empty, l_otherEmpty,
                malloc, &GeneralErrorCallback, &l_called
            );

            CHECK(l_called == false);
        }
 
 
        CHECK(l_empty.m_Capacity == 0);
        CHECK(l_empty.m_Size == 0);
    }
    SECTION("Create copy alloc error")
    {
        bool l_called = false;

        Array<int> l_other;
        l_other.m_Buffer = (int*)malloc(sizeof(int) * 5);
        l_other.m_Capacity = 5;
        l_other.m_Size = 5;

        for(Size i = 0; i < l_other.m_Size; ++i)
        {
            l_other[i] = (int)i;
        }

        CreateCopyAtOfArrayUsingAllocator(
            l_empty, l_other,
            NullMalloc, &GeneralErrorCallback, &l_called
        );

        CHECK(l_called == true);
        CHECK(l_empty.m_Capacity == 0);
        CHECK(l_empty.m_Size == 0);
    
        free(l_other.m_Buffer);
    }
    //Note: The case where sizeof(T) * capacity overflows is not tested.

    CHECK(l_empty.m_Buffer == nullptr);
    CHECK(l_empty.m_Size == 0);
    CHECK(l_empty.m_Capacity == 0);

}

TEST_CASE("Create array at of capacity")
{

    Size l_capacity = GENERATE(range(1, 1000));

    Array<unsigned int> l_array;

    SECTION("Defaults")
    {
        CreateArrayAtOfCapacity(l_array, l_capacity);
    }
    SECTION("Customs")
    {
        bool l_called = false;

        CreateArrayAtOfCapacityUsingAllocator(
            l_array, l_capacity,
            malloc, &GeneralErrorCallback, &l_called
        );

        CHECK(l_called == false);
    }

    CHECK(l_array.m_Buffer != nullptr);
    CHECK(l_array.m_Capacity == l_capacity);
    CHECK(l_array.m_Size == 0);

    //Test each memory location by reading and writing
    for(Size i = 0; i < l_capacity; ++i)
    {
        INFO("i = " << i);
        l_array.m_Buffer[i] = (unsigned int)i;
        unsigned int l_result = l_array.m_Buffer[i];

        CHECK(l_result == i);
    }

    free(l_array.m_Buffer);

}

TEST_CASE("Create copy at")
{

    Size l_size = GENERATE(Catch::Generators::range((Size)1, (Size)100));
    Size l_capacity = l_size * 2;

    Array<unsigned int> l_array;

    l_array.m_Buffer = (unsigned int*)malloc(sizeof(unsigned int) * l_capacity);
    if(l_array.m_Buffer == nullptr)
    {
        FAIL("Error cannot allocate test resources");
    }
    
    l_array.m_Size = l_size;
    l_array.m_Capacity = l_capacity;

    for(Size i = 0; i < l_size; ++i)
    {
        l_array.m_Buffer[i] = (unsigned int)i;
    }

    Array<unsigned int> l_result;

    SECTION("Defaults")
    {
        CreateCopyAtOfArray(l_result, l_array);
    }
    SECTION("Customs")
    {
        bool l_called = false;

        CreateCopyAtOfArrayUsingAllocator(
            l_result, l_array,
            malloc, &GeneralErrorCallback, &l_called
        );

        REQUIRE(l_called == false);
    }

    REQUIRE(l_result.m_Buffer != nullptr);
    REQUIRE(l_result.m_Capacity == l_size);
    REQUIRE(l_result.m_Size == l_size);

    for(Size i = 0; i < l_size; ++i)
    {
        CHECK(l_result.m_Buffer[i] == l_array.m_Buffer[i]);
    }

    //Checks all slots to make sure they work
    unsigned int n = 5;
    for(Size i = 0; i < l_size; ++i, n *= 5)
    {
        l_result.m_Buffer[i] = n;
        unsigned int l_readResult = l_result.m_Buffer[i];

        CHECK(l_readResult == n);
    }

    free(l_array.m_Buffer);
    free(l_result.m_Buffer);

}
