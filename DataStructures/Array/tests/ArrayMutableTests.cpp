#include <catch2/catch.hpp>

#include <stdint.h>
#include "../Array.hpp"
#include "../../../Debugging/Debugging.hpp"

using namespace Library;
using namespace Library::DataStructures::Array;
using namespace Debugging;
using namespace Catch::Generators;

TEST_CASE("Change array capacity", "[Array][Mutable][Capacity]")
{

    Size l_capacity = GENERATE(Catch::Generators::range(20, 100));

    Array<int> l_array;
    Array<int> l_nullArray;

    CreateArrayAtOfCapacity(l_array, l_capacity);

    REQUIRE(l_array.m_Buffer != nullptr);
    REQUIRE(l_array.m_Capacity == l_capacity);

    l_array.m_Size = l_array.m_Capacity / 2;

    SECTION("Zero new capacity")
    {
        SECTION("Defaults")
        {
            ResizeArrayToCapacity(l_array, 0);
        }
        SECTION("Customs")
        {
            bool l_called = false;

            ResizeArrayToCapacityUsingReallocator(l_array, 0, realloc, &GeneralErrorCallback, &l_called);

            CHECK(l_called == false);
        }

        CHECK(l_array.m_Buffer == nullptr);
        CHECK(l_array.m_Capacity == 0);
        CHECK(l_array.m_Size == 0);
    }

    SECTION("Same capacity")
    {
        int* l_oldBuffer = l_array.m_Buffer;
        Size l_oldSize = l_array.m_Size;
        Size l_oldCapacity = l_array.m_Capacity;

        SECTION("Defaults")
        {
            ResizeArrayToCapacity(l_array, l_capacity);
        }
        SECTION("Customs")
        {
            bool l_called = false;

            ResizeArrayToCapacityUsingReallocator(
                l_array,
                l_capacity,
                realloc, &GeneralErrorCallback, &l_called
            );

            CHECK(l_called == false);
        }

        CHECK(l_array.m_Buffer == l_oldBuffer);
        CHECK(l_array.m_Size == l_oldSize);
        CHECK(l_array.m_Capacity == l_oldCapacity);

    }

    SECTION("Bigger than m_Size")
    {
        Size l_oldSize = l_array.m_Size;

        SECTION("Defaults")
        {
            ResizeArrayToCapacity(l_array, l_capacity * 2);
            ResizeArrayToCapacity(l_nullArray, l_capacity * 2);
        }
        SECTION("Customs")
        {
            bool l_called = false;
            bool l_called2 = false;

            ResizeArrayToCapacityUsingReallocator(
                l_array,
                l_capacity * 2,
                realloc, &GeneralErrorCallback, &l_called
            );
            ResizeArrayToCapacityUsingReallocator(
                l_nullArray,
                l_capacity * 2,
                realloc, &GeneralErrorCallback, &l_called2
            );

            CHECK(l_called == false);
            CHECK(l_called2 == false);
        }

        REQUIRE(l_array.m_Buffer != nullptr);
        CHECK(l_array.m_Capacity == l_capacity * 2);
        CHECK(l_array.m_Size == l_oldSize);

        REQUIRE(l_nullArray.m_Buffer != nullptr);
        CHECK(l_nullArray.m_Capacity == l_capacity * 2);
        CHECK(l_nullArray.m_Size == 0);

        //Makes sure that all slots are ok.
        for(Size i = 0; i < l_capacity * 2; ++i)
        {
            l_array[i] = (int)i;
            CHECK(l_array[i] == (int)i);

            l_nullArray[i] = (int)i;
            CHECK(l_nullArray[i] == (int)i);
        }
    }

    SECTION("Less than m_Size")
    {
     
        SECTION("Defaults")
        {
            ResizeArrayToCapacity(l_array, l_capacity / 4);
            ResizeArrayToCapacity(l_nullArray, l_capacity / 4);
        }
        SECTION("Customs")
        {
            bool l_called = false;
            bool l_called2 = false;

            ResizeArrayToCapacityUsingReallocator(
                l_array,
                l_capacity / 4,
                realloc, &GeneralErrorCallback, &l_called
            );
            ResizeArrayToCapacityUsingReallocator(
                l_nullArray,
                l_capacity / 4,
                realloc, &GeneralErrorCallback, &l_called2
            );

            CHECK(l_called == false);
            CHECK(l_called2 == false);
        }

        REQUIRE(l_array.m_Buffer != nullptr);
        CHECK(l_array.m_Capacity == l_capacity / 4);
        CHECK(l_array.m_Size == l_capacity / 4);

        REQUIRE(l_nullArray.m_Buffer != nullptr);
        CHECK(l_nullArray.m_Capacity == l_capacity / 4);
        CHECK(l_nullArray.m_Size == 0);

        //Makes sure that all slots are ok.
        for(Size i = 0; i < l_capacity / 4; ++i)
        {
            l_array[i] = (int)i;
            CHECK(l_array[i] == (int)i);

            l_nullArray[i] = (int)i;
            CHECK(l_nullArray[i] == (int)i);
        }
    }

    SECTION("Realloc error")
    {
        bool l_called = false;

        ResizeArrayToCapacityUsingReallocator(
            l_array, l_capacity * 3,
            NullRealloc, &GeneralErrorCallback, &l_called
        );

        CHECK(l_called == true);
    }

    DestoryArray(l_array);
    DestoryArray(l_nullArray);

}

TEST_CASE("Increase array capacity", "[Array][Mutable][Capacity]")
{

    Size l_capacity = GENERATE(Catch::Generators::range(20, 100));

    Array<int> l_array;
    Array<int> l_nullArray;

    CreateArrayAtOfCapacity(l_array, l_capacity);

    SECTION("Normal execution")
    {
        Size l_by = GENERATE(Catch::Generators::range(1, 10));
        Size l_oldSize = l_array.m_Size;

        SECTION("Defaults")
        {
            IncreaseArrayCapacityByAmount(l_array, l_by);
            IncreaseArrayCapacityByAmount(l_nullArray, l_by);
        }
        SECTION("Customs")
        {
            bool l_called = false;
            bool l_called2 = false;

            IncreaseArrayCapacityByAmountUsingReallocator(
                l_array, l_by,
                realloc, &GeneralErrorCallback, &l_called
            );
            IncreaseArrayCapacityByAmountUsingReallocator(
                l_nullArray, l_by,
                realloc, &GeneralErrorCallback, &l_called2
            );

            CHECK(l_called == false);
            CHECK(l_called2 == false);
        }

        REQUIRE(l_array.m_Buffer != nullptr);
        CHECK(l_array.m_Size == l_oldSize);
        CHECK(l_array.m_Capacity == l_capacity + l_by);

        REQUIRE(l_nullArray.m_Buffer != nullptr);
        CHECK(l_nullArray.m_Size == 0);
        CHECK(l_nullArray.m_Capacity == l_by);

        //Checks all of the slots to make sure that enough memory was allocated.
        //This part failing could case deallocation errors.
        for(Size i = 0; i < l_by; ++i)
        {
            l_array[i] = (int)i;
            CHECK(l_array[i] == (int)i);

            l_nullArray[i] = (int)i;
            CHECK(l_nullArray[i] == (int)i);
        }
        for(Size i = l_by; i < l_by + l_capacity; ++i)
        {
            l_array[i] = (int)i;
            CHECK(l_array[i] == (int)i);
        }

    }
    SECTION("By 0")
    {
        Array<int> l_oldArray = l_array;
        Array<int> l_oldNullArray = l_nullArray;

        SECTION("Defaults")
        {
            IncreaseArrayCapacityByAmount(l_array, 0);
            IncreaseArrayCapacityByAmount(l_nullArray, 0);
        }
        SECTION("Customs")
        {
            bool l_called = false;
            bool l_called2 = false;

            //Null realloc to make sure that no calls are made.
            IncreaseArrayCapacityByAmountUsingReallocator(
                l_array, 0,
                NullRealloc, &GeneralErrorCallback, &l_called
            );
            IncreaseArrayCapacityByAmountUsingReallocator(
                l_nullArray, 0,
                NullRealloc, &GeneralErrorCallback, &l_called2
            );

            CHECK(l_called == false);
            CHECK(l_called2 == false);
        }

        REQUIRE(l_array.m_Buffer == l_oldArray.m_Buffer);
        CHECK(l_array.m_Size == l_oldArray.m_Size);
        CHECK(l_array.m_Capacity == l_oldArray.m_Capacity);
        
        REQUIRE(l_nullArray.m_Buffer == l_oldNullArray.m_Buffer);
        CHECK(l_nullArray.m_Size == l_oldNullArray.m_Size);
        CHECK(l_nullArray.m_Capacity == l_oldNullArray.m_Capacity);
    
        for(Size i = 0; i < l_array.m_Capacity; ++i)
        {
            l_array[i] = (int)i;
            CHECK(l_array[i] == (int)i);
        }

    }
    SECTION("Overflow")
    {
        Array<int> l_oldArray = l_array;

        //SIZE_MAX is used here to gurante an overflow.
        SECTION("Defaults")
        {
            IncreaseArrayCapacityByAmount(l_array, SIZE_MAX);
        }
        SECTION("Customs")
        {
            bool l_called = false;

            //Null realloc to make sure that no calls are made.
            IncreaseArrayCapacityByAmountUsingReallocator(
                l_array, SIZE_MAX,
                NullRealloc, &GeneralErrorCallback, &l_called
            );

            CHECK(l_called == false);
        }

        REQUIRE(l_array.m_Buffer == l_oldArray.m_Buffer);
        CHECK(l_array.m_Size == l_oldArray.m_Size);
        CHECK(l_array.m_Capacity == l_oldArray.m_Capacity);
        
        for(Size i = 0; i < l_array.m_Capacity; ++i)
        {
            l_array[i] = (int)i;
            CHECK(l_array[i] == (int)i);
        }

    }
    SECTION("Realloc error")
    {
        Size l_oldSize = l_array.m_Size;
        Size l_oldCapacity = l_array.m_Capacity;
        
        bool l_called = false;
        bool l_called2 = false;

        Size l_by = GENERATE(Catch::Generators::range(1, 10));

        IncreaseArrayCapacityByAmountUsingReallocator(
            l_array, l_by,
            NullRealloc, &GeneralErrorCallback, &l_called 
        );
        IncreaseArrayCapacityByAmountUsingReallocator(
            l_nullArray, l_by,
            NullRealloc, &GeneralErrorCallback, &l_called2 
        );

        CHECK(l_called == true);
        CHECK(l_called2 == true);

        REQUIRE(l_array.m_Buffer != nullptr);
        REQUIRE(l_array.m_Capacity == l_oldCapacity);
        REQUIRE(l_array.m_Size == l_oldSize);

        for(Size i = 0; i < l_array.m_Capacity; ++i)
        {
            l_array[i] = (int)i;
            CHECK(l_array[i] == (int)i);
        }

    }

    DestoryArray(l_array);
    DestoryArray(l_nullArray);

}

TEST_CASE("Decrease array capacity", "[Array][Mutable][Capacity]")
{

    Size l_capacity = GENERATE(Catch::Generators::range(20, 100));

    Array<int> l_array;
    Array<int> l_nullArray;

    CreateArrayAtOfCapacity(l_array, l_capacity);

    SECTION("Normal execution")
    {
        Size l_by = GENERATE(Catch::Generators::range(1, 10));
        Size l_oldSize = l_array.m_Size;

        SECTION("Defaults")
        {
            DecreaseArrayCapacityByAmount(l_array, l_by);
        }
        SECTION("Customs")
        {
            bool l_called = false;
            DecreaseArrayCapacityByAmountUsingReallocator(
                l_array, l_by,
                realloc, &GeneralErrorCallback, &l_called
            );

            CHECK(l_called == false);
        }

        REQUIRE(l_array.m_Buffer != nullptr);
        if(l_oldSize > l_capacity - l_by)
        {
            CHECK(l_array.m_Size == l_array.m_Capacity);
        }
        else
        {
            CHECK(l_array.m_Size == l_oldSize);
        }
        CHECK(l_array.m_Capacity == l_capacity - l_by);

        //Checks all of the slots to make sure that enough memory was allocated.
        //This part failing could case deallocation errors.
        for(Size i = 0; i < l_capacity - l_by; ++i)
        {
            l_array[i] = (int)i;
            CHECK(l_array[i] == (int)i);
        }

    }
    SECTION("By 0")
    {
        Array<int> l_oldArray = l_array;
        Array<int> l_oldNullArray = l_nullArray;

        SECTION("Defaults")
        {
            DecreaseArrayCapacityByAmount(l_array, 0);
            DecreaseArrayCapacityByAmount(l_nullArray, 0);
        }
        SECTION("Customs")
        {
            bool l_called = false;
            bool l_called2 = false;

            //Null realloc to make sure that no calls are made.
            DecreaseArrayCapacityByAmountUsingReallocator(
                l_array, 0,
                NullRealloc, &GeneralErrorCallback, &l_called
            );
            DecreaseArrayCapacityByAmountUsingReallocator(
                l_nullArray, 0,
                NullRealloc, &GeneralErrorCallback, &l_called2
            );

            CHECK(l_called == false);
            CHECK(l_called2 == false);
        }

        REQUIRE(l_array.m_Buffer == l_oldArray.m_Buffer);
        CHECK(l_array.m_Size == l_oldArray.m_Size);
        CHECK(l_array.m_Capacity == l_oldArray.m_Capacity);
        
        REQUIRE(l_nullArray.m_Buffer == l_oldNullArray.m_Buffer);
        CHECK(l_nullArray.m_Size == l_oldNullArray.m_Size);
        CHECK(l_nullArray.m_Capacity == l_oldNullArray.m_Capacity);
    
        for(Size i = 0; i < l_array.m_Capacity; ++i)
        {
            l_array[i] = (int)i;
            CHECK(l_array[i] == (int)i);
        }

    }
    SECTION("Get to 0")
    {
        SECTION("Defaults")
        {
            DecreaseArrayCapacityByAmount(l_array, l_capacity);
        }
        SECTION("Customs")
        {
            bool l_called = false;

            //Null realloc to make sure that no calls are made.
            DecreaseArrayCapacityByAmountUsingReallocator(
                l_array, l_capacity,
                realloc, &GeneralErrorCallback, &l_called
            );

            CHECK(l_called == false);
        }

        CHECK(l_array.m_Buffer == nullptr);
        CHECK(l_array.m_Capacity == 0);
        CHECK(l_array.m_Size == 0);

    }
    SECTION("Overflow")
    {
        Array<int> l_oldArray = l_array;
        Array<int> l_oldNullArray = l_nullArray;

        //SIZE_MAX is used here to gurante an overflow.
        SECTION("Defaults")
        {
            DecreaseArrayCapacityByAmount(l_array, SIZE_MAX);
            DecreaseArrayCapacityByAmount(l_nullArray, SIZE_MAX);
        }
        SECTION("Customs")
        {
            bool l_called = false;
            bool l_called2 = false;

            //Null realloc to make sure that no calls are made.
            DecreaseArrayCapacityByAmountUsingReallocator(
                l_array, SIZE_MAX,
                NullRealloc, &GeneralErrorCallback, &l_called
            );
            DecreaseArrayCapacityByAmountUsingReallocator(
                l_nullArray, SIZE_MAX,
                NullRealloc, &GeneralErrorCallback, &l_called2
            );

            CHECK(l_called == false);
            CHECK(l_called2 == false);
        }

        REQUIRE(l_array.m_Buffer == l_oldArray.m_Buffer);
        CHECK(l_array.m_Size == l_oldArray.m_Size);
        CHECK(l_array.m_Capacity == l_oldArray.m_Capacity);
        
        CHECK(l_nullArray.m_Buffer == l_oldNullArray.m_Buffer);
        CHECK(l_nullArray.m_Capacity == l_oldNullArray.m_Capacity);
        CHECK(l_nullArray.m_Size == l_oldNullArray.m_Size);

        for(Size i = 0; i < l_array.m_Capacity; ++i)
        {
            l_array[i] = (int)i;
            CHECK(l_array[i] == (int)i);
        }

    }
    SECTION("Realloc error")
    {
        Size l_oldSize = l_array.m_Size;
        Size l_oldCapacity = l_array.m_Capacity;
        
        bool l_called = false;

        Size l_by = GENERATE(Catch::Generators::range(1, 10));

        DecreaseArrayCapacityByAmountUsingReallocator(
            l_array, l_by,
            NullRealloc, &GeneralErrorCallback, &l_called 
        );

        CHECK(l_called == true);
        
        REQUIRE(l_array.m_Buffer != nullptr);
        REQUIRE(l_array.m_Capacity == l_oldCapacity);
        REQUIRE(l_array.m_Size == l_oldSize);

        for(Size i = 0; i < l_array.m_Capacity; ++i)
        {
            l_array[i] = (int)i;
            CHECK(l_array[i] == (int)i);
        }

    }

    DestoryArray(l_array);
    DestoryArray(l_nullArray);

}

TEST_CASE("Reverse array", "[Array][Mutable]")
{

    SECTION("Non emtpy array")
    {
        Size l_capacity = GENERATE(Catch::Generators::range(1, 100));

        Array<int> l_array;
        CreateArrayAtOfCapacity(l_array, l_capacity);
    
        for(Size i = 0; i < l_capacity; ++i)
        {
            l_array[i] = (int)i;
        }
        l_array.m_Size = l_capacity;

        Array<int> l_oldArray = l_array;

        ReverseArray(l_array);

        REQUIRE(l_array.m_Buffer == l_oldArray.m_Buffer);
        REQUIRE(l_array.m_Size == l_oldArray.m_Size);
        REQUIRE(l_array.m_Capacity == l_oldArray.m_Capacity);

        for(Size i = 0, n = l_array.m_Size; n-- > 0; ++i)
        {
            CHECK(l_array[n] == (int)i);
        }

        DestoryArray(l_array);
    }
    SECTION("Empty array")
    {
        Array<int> l_array;

        ReverseArray(l_array);

        CHECK(l_array.m_Buffer == nullptr);
        CHECK(l_array.m_Capacity == 0);
        CHECK(l_array.m_Size == 0);
    }

}

TEST_CASE("Add array to array simple", "[Array][Mutable][Size]")
{

    Array<int> l_array;
    CreateArrayAtOfCapacity(l_array, 50);
    
    REQUIRE(l_array.m_Buffer != nullptr);
    REQUIRE(l_array.m_Capacity == 50);

    l_array.m_Size = 10;
    for(Size i = 0; i < l_array.m_Size; ++i)
    {
        l_array[i] = (int)i;
    }


    SECTION("Non empty addition array")
    {
        Size l_capacity = GENERATE(Catch::Generators::range(1, 40));

        Array<int> l_additionArray;
        CreateArrayAtOfCapacity(l_additionArray, l_capacity);

        REQUIRE(l_additionArray.m_Buffer != nullptr);
        REQUIRE(l_additionArray.m_Capacity == l_capacity);
        
        for(Size i = 0; i < l_additionArray.m_Capacity; ++i)
        {
            l_additionArray[i] = (int)i;
        }
        l_additionArray.m_Size = l_additionArray.m_Capacity;

        Size l_index = GENERATE(Catch::Generators::range(0, 9));
        AddArrayToArrayAfterIndexNoErrorCheckAssumingEnoughCapacity(
            l_additionArray,
            l_array,
            l_index
        );

        REQUIRE(l_array.m_Buffer != nullptr);
        REQUIRE(l_array.m_Capacity == 50);
        REQUIRE(l_array.m_Size == 10 + l_capacity);

        //Check the part BEFORE the addition.
        Size i = 0;
        for(; i < l_index + 1; ++i)
        {
            CHECK(l_array[i] == (int)i);
        }
        //Check the addition it's self.
        for(Size n = 0; n < l_additionArray.m_Size; ++i, ++n)
        {
            CHECK(l_array[i] == l_additionArray[n]);
        }
        //Check after the addition.
        for(Size n = l_index + 1; i < l_array.m_Size; ++i, ++n)
        {
            CHECK(l_array[i] == (int)n);
        }
        //Check if the remanding slots work.
        for(; i < l_array.m_Capacity; ++i)
        {
            l_array[i] = (int)i;
            CHECK(l_array[i] == (int)i);
        }

        DestoryArray(l_additionArray);
    }

    SECTION("Empty addition array")
    {
        Array<int> l_additionArray;

        Array<int> l_oldArray = l_array;

        Size l_index = GENERATE(Catch::Generators::range(0, 49));
        AddArrayToArrayAfterIndexNoErrorCheckAssumingEnoughCapacity(
            l_additionArray,
            l_array,
            l_index
        );

        CHECK(l_oldArray.m_Buffer == l_array.m_Buffer);
        CHECK(l_oldArray.m_Capacity == l_array.m_Capacity);
        CHECK(l_oldArray.m_Size == l_array.m_Size);
    }


    DestoryArray(l_array);

}

TEST_CASE("Add array to array abstract", "[Array][Mutable][Size][Capacity]")
{

    //Note since this function technically wraps the simple version, the
    //functionality of the simple one is not tested in this test case.

    Array<int> l_array;
    CreateArrayAtOfCapacity(l_array, 50);

    REQUIRE(l_array.m_Buffer != nullptr);
    REQUIRE(l_array.m_Capacity == 50);

    for(Size i = 0; i < 10; ++i)
    {
        l_array[i] = (int)i;
    }
    l_array.m_Size = 10;

    Array<int> l_additionArray;

    SECTION("Index error")
    {
        CreateArrayAtOfCapacity(l_additionArray, 10);
        REQUIRE(l_additionArray.m_Buffer != nullptr);
        REQUIRE(l_additionArray.m_Capacity == 10);

        for(Size i = 0; i < l_additionArray.m_Capacity; ++i)
        {
            l_additionArray[i] = (int)i;
        }
        l_additionArray.m_Size = l_additionArray.m_Capacity;

        bool l_called = false;
        bool l_calledRealloc = false;

        Size l_index = GENERATE_COPY(Catch::Generators::range(l_array.m_Size, l_array.m_Size * 2));
        
        SECTION("Defaults")
        {
            AddArrayToArrayAfterIndex(
                l_additionArray,
                l_array,
                l_index, &GeneralErrorCallback, &l_called
            );
        }
        SECTION("Customs")
        {
            AddArrayToArrayAfterIndexUsingReallocator(
                l_additionArray,
                l_array,
                l_index, &GeneralErrorCallback, &l_called,
                NullRealloc, &GeneralErrorCallback, &l_calledRealloc
            );
        }

        INFO("l_index = " << l_index);
        CHECK(l_called == true);
        CHECK(l_calledRealloc == false);
    }

    SECTION("Not enough capacity")
    {
        Size l_capacity = GENERATE_COPY(Catch::Generators::range(
            l_array.m_Capacity - l_array.m_Size + 1,
            l_array.m_Capacity * 2
            )
        );
        CreateArrayAtOfCapacity(l_additionArray, l_capacity);
        REQUIRE(l_additionArray.m_Buffer != nullptr);
        REQUIRE(l_additionArray.m_Capacity == l_capacity);

        for(Size i = 0; i < l_additionArray.m_Capacity; ++i)
        {
            l_additionArray[i] = (int)i;
        }
        l_additionArray.m_Size = l_additionArray.m_Capacity;

        SECTION("Overflow")
        {
            SECTION("Doubling l_additionArray.m_Size overflow")
            {
                int* l_oldBuffer = l_array.m_Buffer;

                //No one said you can't lie about the size for testing purposes
                l_additionArray.m_Size = SIZE_MAX / 2 + 1;
                //This is so that the second try also overflows.
                l_array.m_Capacity = SIZE_MAX - l_additionArray.m_Size + 1;

                SECTION("Defaults")
                {
                    AddArrayToArrayAfterIndex(
                        l_additionArray,
                        l_array,
                        0, nullptr, nullptr
                    );
                }
                SECTION("Customs")
                {
                    bool l_called = false;

                    AddArrayToArrayAfterIndexUsingReallocator(
                        l_additionArray,
                        l_array,
                        0, nullptr, nullptr,
                        NullRealloc, &GeneralErrorCallback, &l_called
                    );

                    CHECK(l_called == false);
                }

                //Checks to make sure l_array was not mutated in anyway
                REQUIRE(l_array.m_Buffer == l_oldBuffer);
                REQUIRE(l_array.m_Capacity == SIZE_MAX - l_additionArray.m_Size + 1);
                REQUIRE(l_array.m_Size == 10);

                for(Size i = 0; i < 10; ++i)
                {
                    CHECK(l_array[i] == (int)i);
                }
            }
            SECTION("Doubled size + l_array.m_Capacity overflow")
            {
                int* l_oldBuffer = l_array.m_Buffer;

                //This is so that it doesn't overflow while being doubled.
                l_additionArray.m_Size = SIZE_MAX / 2 - 1;
                //A gurante for an overflow.
                l_array.m_Capacity = SIZE_MAX / 2;
            
                SECTION("Defaults")
                {
                    AddArrayToArrayAfterIndex(
                        l_additionArray,
                        l_array,
                        0, nullptr, nullptr
                    );
                }
                SECTION("Customs")
                {
                    bool l_called = false;
                    
                    AddArrayToArrayAfterIndexUsingReallocator(
                        l_additionArray,
                        l_array,
                        0, nullptr, nullptr,
                        NullRealloc, &GeneralErrorCallback, &l_called
                    );

                    CHECK(l_called == false);
                }

                //Checks to make sure l_array was not mutated in anyway
                REQUIRE(l_array.m_Buffer == l_oldBuffer);
                REQUIRE(l_array.m_Capacity == SIZE_MAX / 2);
                REQUIRE(l_array.m_Size == 10);

                for(Size i = 0; i < 10; ++i)
                {
                    CHECK(l_array[i] == (int)i);
                }
            }
            SECTION("sizeof(T) * new capacity overflow")
            {
                int* l_oldBuffer = l_array.m_Buffer;

                Size l_maxNumberOfInts = SIZE_MAX / sizeof(int) + 1;

                //Divide the max number evenly so that new capacity is bigger
                l_array.m_Capacity = l_maxNumberOfInts / 2;
                l_additionArray.m_Size = l_maxNumberOfInts / 2;

                SECTION("Defaults")
                {
                    AddArrayToArrayAfterIndex(
                        l_additionArray,
                        l_array,
                        0, nullptr, nullptr
                    );
                }
                SECTION("Customs")
                {
                    bool l_called = false;
                    
                    AddArrayToArrayAfterIndexUsingReallocator(
                        l_additionArray,
                        l_array,
                        0, nullptr, nullptr,
                        NullRealloc, &GeneralErrorCallback, &l_called
                    );

                    CHECK(l_called == false);
                }

                //Checks to make sure l_array was not mutated in anyway
                REQUIRE(l_array.m_Buffer == l_oldBuffer);
                REQUIRE(l_array.m_Capacity == l_maxNumberOfInts / 2);
                REQUIRE(l_array.m_Size == 10);

                for(Size i = 0; i < 10; ++i)
                {
                    CHECK(l_array[i] == (int)i);
                }
            }
        }

        SECTION("Realloc error")
        {
            Size l_index = GENERATE_COPY(Catch::Generators::range((Size)0, l_array.m_Size - 1));
            bool l_called = false;
            bool l_calledIndex = false;

            AddArrayToArrayAfterIndexUsingReallocator(
                l_additionArray,
                l_array,
                l_index, &GeneralErrorCallback, &l_calledIndex,
                NullRealloc, &GeneralErrorCallback, &l_called
            );

            INFO("l_index = " << l_index);
            CHECK(l_called == true);
            CHECK(l_calledIndex == false);
        }

    }

    DestoryArray(l_array);
    DestoryArray(l_additionArray);

}

TEST_CASE("Remove items simple", "[Array][Mutable][Size]")
{

    Size l_capacity = GENERATE(Catch::Generators::range(10, 30));
    
    Array<int> l_array;
    CreateArrayAtOfCapacity(l_array, l_capacity);

    REQUIRE(l_array.m_Buffer != nullptr);
    REQUIRE(l_array.m_Capacity == l_capacity);

    for(Size i = 0; i < l_capacity; ++i)
    {
        l_array[i] = (int)i;
    }
    l_array.m_Size = l_capacity;

    Size l_index = GENERATE_COPY(Catch::Generators::range<Size>(0, l_capacity - 1));
    Size l_numberOf = GENERATE_COPY(Catch::Generators::range<Size>(0, (l_capacity - l_index) - 1));

    RemoveNumberOfItemsStartingFromAndIncludingIndexNoErrorCheckFromArray(
        l_numberOf,
        l_index,
        l_array
    );

    REQUIRE(l_array.m_Buffer != nullptr);
    REQUIRE(l_array.m_Capacity == l_capacity);
    REQUIRE(l_array.m_Size == l_capacity - (l_numberOf + 1));

    Size i;
    for(i = 0; i < l_index; ++i)
    {
        CHECK(l_array[i] == (int)i);
    }
    for(Size n = i + l_numberOf + 1; i < l_array.m_Size; ++i, ++n)
    {
        CHECK(l_array[i] == (int)n);
    }

    DestoryArray(l_array);

}

TEST_CASE("Remove items abstract", "[Array][Mutable][Size]")
{

    //Note this test does not test all the actual removal of items, since
    //that is the responsibility of the simple version which is called by this
    //function internally anyway. 

    Array<int> l_array;
    CreateArrayAtOfCapacity(
        l_array,
        50
    );

    for(Size i = 0; i < 10; ++i)
    {
        l_array[i] = (int)i;
    }
    l_array.m_Size = 10;

    SECTION("Index error")
    {
        SECTION("p_index > p_array.m_Size")
        {
            Size l_index = GENERATE_COPY(Catch::Generators::range(l_array.m_Size, l_array.m_Size * 2));

            bool l_called = false;

            RemoveNumberOfItemsStartingFromAndIncludingIndexFromArray(
                0,
                l_index,
                &GeneralErrorCallback, &l_called,
                l_array
            );

            CHECK(l_called == true);
        }
        SECTION("p_index + p_numberOf > p_array.m_Size")
        {
            Size l_index = l_array.m_Size - 1;
            Size l_numberOf = GENERATE_COPY(Catch::Generators::range((Size)1, l_array.m_Capacity));

            bool l_called = false;

            RemoveNumberOfItemsStartingFromAndIncludingIndexFromArray(
                l_numberOf,
                l_index,
                &GeneralErrorCallback, &l_called,
                l_array
            );

            CHECK(l_called == true);
        }
    }

    SECTION("End index overflow")
    {
        bool l_called = false;

        RemoveNumberOfItemsStartingFromAndIncludingIndexFromArray(
            SIZE_MAX,
            1,
            &GeneralErrorCallback, &l_called,
            l_array
        );

        CHECK(l_called == false);
    }

    DestoryArray(l_array);

}

TEST_CASE("Remove each instance of item", "[Array][Mutable][Size]")
{

    //To high a value and this takes forever to run.
    Size l_arrayCapacity = GENERATE(range(0, 20));
    
    Array<int> l_array;
    Array<int> l_items;

    CreateArrayAtOfCapacity(l_array, l_arrayCapacity);
    REQUIRE(l_array.m_Capacity == l_arrayCapacity);

    Size l_arraySize;
    if(l_arrayCapacity > 0)
    {
        l_arraySize = GENERATE_COPY(range((Size)0, l_arrayCapacity));
    }
    else
    {
        l_arraySize = 0;
    }

    Size l_itemsCapacity; 
    if(l_arraySize > 0)
    {
        l_itemsCapacity = GENERATE_COPY(range((Size)0, l_arraySize));
    }
    else
    {
        l_itemsCapacity = 0;
    }

    CreateArrayAtOfCapacity(l_items, l_itemsCapacity);
    REQUIRE(l_items.m_Capacity == l_itemsCapacity);


    for(Size i = 0; i < l_arraySize; ++i)
    {
        l_array[i] = rand();
    }
    l_array.m_Size = l_arraySize;

    for(Size i = 0, n = 0; i < l_itemsCapacity; ++i)
    {
        int l_chance = rand();
        if(l_chance < 0)
        {
            l_chance = -l_chance;
        }
        l_chance %= 128;
        if(l_chance > 64)
        {
            Size l_randIndex = rand();
            l_randIndex %= l_arraySize;

            int l_toAdd = l_array[l_randIndex];
            //If this item is already contained inside the array skip it.
            if(ArrayContainsArray<int>(l_items, l_toAdd))
            {
                continue;
            }
            l_items[n] = l_toAdd;

            ++n;
            ++l_items.m_Size;
        }
    }

    int* l_oldBuffer = l_array.m_Buffer;
    
    Size l_numberOfMatchingItems = 0;
    for(Size i = 0; i < l_items.m_Size; ++i)
    {
        l_numberOfMatchingItems += FindNumberOfInstanceOfArrayInArray<int>(
            l_items[i],
            l_array
        );
    }

    RemoveEachInstanceOfArrayOfItemsFromArray(l_items, l_array);

    REQUIRE(l_array.m_Buffer == l_oldBuffer);
    REQUIRE(l_array.m_Capacity == l_arrayCapacity);

    CHECK(l_array.m_Size == l_arraySize - l_numberOfMatchingItems);

    for(Size i = 0; i < l_items.m_Size; ++i)
    {
        CHECK(!ArrayContainsArray<int>(l_array, l_items[i]));
    }


    DestoryArray(l_array);
    DestoryArray(l_items);

}
