#include <catch2/catch.hpp>

#include "../../../Debugging/Debugging.hpp"
#include "../Queue.hpp"
#include "QueueHelperFunctions.hpp"

using namespace Library::DataStructures::Queue;
using namespace Catch::Generators;
using namespace Debugging;

TEST_CASE("Write item to null queue", "[Queue][Mutable][Writing]")
{

    Queue<int> l_queue;

    int l_rand = GENERATE(take(100, random(INT32_MIN, INT32_MAX)));
    AddItemToQueue(l_rand, l_queue);

    CHECK(l_queue.m_Buffer.m_Capacity == 0);
    CHECK(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, 0));

}
TEST_CASE("Write item to full queue", "[Queue][Mutable][Writing]")
{

    Size l_capacity = GENERATE(range(1, 100));

    Queue<int> l_queue;
    CreateQueueAtOfCapacityUsingAllocator(l_queue, l_capacity);
    //Indicates an allocation error.
    REQUIRE(l_queue.m_Buffer != nullptr);

    //Fakes a full queue.
    l_queue.m_LastItem = 0;
    l_queue.m_Buffer.m_Size = l_queue.m_Buffer.m_Capacity;

    int l_rand = GENERATE(take(100, random(INT32_MIN, INT32_MAX)));
    //There should be no effect of calling this function.
    AddItemToQueue(l_rand, l_queue);

    CHECK(l_queue.m_Buffer.m_Capacity == l_capacity);
    //The queue is faked as being full so it has the maximum number of items
    //that being it's capacity.
    CHECK(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, l_capacity));

}

TEST_CASE("Read item from null queue", "[Queue][Mutable][Reading]")
{

    Queue<int> l_queue;

    //Should not be mutated.
    int l_result;
    int l_oldDataInResult = l_result;
    RemoveItemFromQueuePutItAt(l_queue, l_result);
    CHECK(l_result == l_oldDataInResult);

    CHECK(l_queue.m_Buffer.m_Capacity == 0);
    CHECK(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, 0));
    
}
TEST_CASE("Read item from full queue", "[Queue][Mutable][Reading]")
{

    Size l_capacity = GENERATE(range(1, 100));

    Queue<int> l_queue;
    CreateQueueAtOfCapacityUsingAllocator(l_queue, l_capacity);
    REQUIRE(l_queue.m_Buffer != nullptr);

    //Should not be mutated.
    int l_result;
    int l_oldDataInResult = l_result;
    RemoveItemFromQueuePutItAt(l_queue, l_result);
    CHECK(l_result == l_oldDataInResult);

    CHECK(l_queue.m_Buffer.m_Capacity == l_capacity);
    CHECK(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, 0));
    
}

TEST_CASE("Reading and writing items", "[Queue][Mutable][Reading][Writing]")
{

    Size l_capacity = GENERATE(take(10, range(1, 10)));

    Queue<int> l_queue;
    CreateQueueAtOfCapacityUsingAllocator(l_queue, l_capacity);
    REQUIRE(l_queue.m_Buffer != nullptr);

    int l_rand = GENERATE(take(5, random(INT32_MIN, INT32_MAX)));
    Size l_numberOfWrites = GENERATE(take(5, random(0, 10)));
    Size l_numberOfReads = GENERATE(take(5, random(0, 10)));

    CAPTURE(l_rand, l_numberOfReads, l_numberOfWrites, l_capacity);

    for(Size i = 0; i < l_numberOfWrites; ++i)
    {
        AddItemToQueue(l_rand, l_queue);
    }

    Size l_oldNumberOfItems;
    //Makes sure that the writes did not screw something up.
    REQUIRE(l_queue.m_Buffer.m_Capacity == l_capacity);
    if(l_numberOfWrites < l_capacity)
    {
        REQUIRE(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, l_numberOfWrites));
        l_oldNumberOfItems = l_numberOfWrites;
    }
    else
    {
        REQUIRE(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, l_capacity));
        l_oldNumberOfItems = l_capacity;
    }


    int l_readResult = l_rand;
    for(Size i = 0; i < l_numberOfReads; ++i)
    {
        RemoveItemFromQueuePutItAt(l_queue, l_readResult);
        CHECK(l_readResult == l_rand);
    }

    REQUIRE(l_queue.m_Buffer.m_Capacity == l_capacity);

    if(l_numberOfReads >= l_oldNumberOfItems)
    {
        REQUIRE(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, 0));
        l_oldNumberOfItems = 0;
    }
    else
    {
        REQUIRE(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, l_oldNumberOfItems - l_numberOfReads));
        l_oldNumberOfItems -= l_numberOfReads;
    }

    CAPTURE(l_oldNumberOfItems, l_numberOfReads, l_numberOfWrites, l_capacity);

    //More reading and writing to cover as many cases as possible.
    l_numberOfWrites = GENERATE(take(5, random(0, 10)));
    l_numberOfReads = GENERATE(take(5, random(0, 10)));    
    bool l_readOrWriteFirst = GENERATE(true, false);

    //If true write first.
    if(l_readOrWriteFirst == true)
    {
        for(Size i = 0; i < l_numberOfWrites; ++i)
        {
            AddItemToQueue(l_rand, l_queue);
        }

        //Makes sure that the writes did not screw something up.
        REQUIRE(l_queue.m_Buffer.m_Capacity == l_capacity);
        if(l_numberOfWrites + l_oldNumberOfItems < l_capacity)
        {
            REQUIRE(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, l_numberOfWrites + l_oldNumberOfItems));
            l_oldNumberOfItems += l_numberOfWrites;
        }
        else
        {
            REQUIRE(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, l_capacity));
            l_oldNumberOfItems = l_capacity;
        }
    }
    //Otherwise read first.
    else
    {
        int l_readResult = l_rand;
        for(Size i = 0; i < l_numberOfReads; ++i)
        {
            RemoveItemFromQueuePutItAt(l_queue, l_readResult);
            CHECK(l_readResult == l_rand);
        }

        REQUIRE(l_queue.m_Buffer.m_Capacity == l_capacity);
        if(l_numberOfReads > l_oldNumberOfItems)
        {
            REQUIRE(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, 0));
            l_oldNumberOfItems = 0;
        }
        else
        {
            REQUIRE(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, l_oldNumberOfItems - l_numberOfReads));
            l_oldNumberOfItems -= l_numberOfReads;
        }
    }

    CAPTURE(l_rand, l_numberOfReads, l_numberOfWrites, l_capacity);

    //Now the opposite of above.
    if(l_readOrWriteFirst == false)
    {
        int l_readResult = l_rand;
        for(Size i = 0; i < l_numberOfReads; ++i)
        {
            RemoveItemFromQueuePutItAt(l_queue, l_readResult);
            CHECK(l_readResult == l_rand);
        }

        REQUIRE(l_queue.m_Buffer.m_Capacity == l_capacity);
        if(l_numberOfReads > l_oldNumberOfItems)
        {
            REQUIRE(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, 0));
        }
        else
        {
            REQUIRE(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, l_oldNumberOfItems - l_numberOfReads));
        }
    }
    else
    {
        for(Size i = 0; i < l_numberOfWrites; ++i)
        {
            AddItemToQueue(l_rand, l_queue);
        }

        //Makes sure that the writes did not screw something up.
        REQUIRE(l_queue.m_Buffer.m_Capacity == l_capacity);
        if(l_numberOfWrites + l_oldNumberOfItems < l_capacity)
        {
            REQUIRE(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, l_numberOfWrites + l_oldNumberOfItems));
            l_oldNumberOfItems += l_numberOfWrites;
        }
        else
        {
            REQUIRE(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, l_capacity));
            l_oldNumberOfItems = l_capacity;
        }
    }

    DestroyQueueUsingDeallocator(l_queue);

}

TEST_CASE("Increase queue capacity", "[Queue][Mutable][Capacity]")
{

    Size l_capacity = GENERATE(take(20, random(0, 100)));

    Queue<int> l_queue = GenerateRandomQueueOfCapacityAndWithItem(l_capacity, rand());
    Size l_amount = GENERATE(take(10, random(0, 100)));

    Size l_oldNumberOfItems = FindNumberOfItemsInQueue<int>(l_queue);

    SECTION("Defaults")
    {
        IncreasesQueueCapicityByAmountUsingReallocator(l_queue, l_amount);
    }
    SECTION("Customs")
    {
        bool l_called = false;
        IncreasesQueueCapicityByAmountUsingReallocator(
            l_queue,
            l_amount,
            realloc, &GeneralErrorCallback, &l_called
        );
        CHECK(l_called == false);
    }

    if(l_capacity + l_amount == 0)
    {
        CHECK(l_queue.m_Buffer == nullptr);
        CHECK(l_queue.m_Buffer.m_Capacity == 0);
        CHECK(l_queue.m_Buffer.m_Size == 0);
        CHECK(l_queue.m_LastItem == 0);

        return;
    }

    REQUIRE(l_queue.m_Buffer != nullptr);
    REQUIRE(l_queue.m_Buffer.m_Capacity == l_capacity + l_amount);

    CHECK(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, l_oldNumberOfItems));

    DestroyQueueUsingDeallocator(l_queue);

}

TEST_CASE("Decrease queue capacity", "[Queue][Mutable][Capacity]")
{

    Size l_capacity = GENERATE(take(20, random(0, 100)));

    Queue<int> l_queue = GenerateRandomQueueOfCapacityAndWithItem(l_capacity, rand());
    Size l_amount = GENERATE(take(10, random(0, 100)));

    Size l_oldNumberOfItems = FindNumberOfItemsInQueue<int>(l_queue);

    int* l_oldBuffer = l_queue.m_Buffer;
    Size l_oldSize = l_queue.m_Buffer.m_Size;
    Size l_oldLastItem = l_queue.m_LastItem;

    SECTION("Defaults")
    {
        DecreaseQueueCapacityByAmountUsingReallocator(l_queue, l_amount);
    }
    SECTION("Customs")
    {
        bool l_called = false;
        DecreaseQueueCapacityByAmountUsingReallocator(
            l_queue,
            l_amount,
            realloc, &GeneralErrorCallback, &l_called
        );
        CHECK(l_called == false);
    }

    //If the buffer's capacity was decreased to 0 the buffer should be empty.
    if(l_capacity == l_amount)
    {
        CHECK(l_queue.m_Buffer == nullptr);
        CHECK(l_queue.m_Buffer.m_Capacity == 0);
        CHECK(l_queue.m_Buffer.m_Size == 0);

        return;
    }
    //If the buffer's capacity overflowed, nothing should have been mutated
    else if(l_capacity < l_amount)
    {
        CHECK(l_queue.m_Buffer == l_oldBuffer);
        CHECK(l_queue.m_Buffer.m_Size == l_oldSize);
        CHECK(l_queue.m_Buffer.m_Capacity == l_capacity);

        return;
    }

    Size l_newNumberOfItems = l_oldNumberOfItems;
    if(l_oldSize > l_queue.m_Buffer.m_Capacity)
    {
        l_newNumberOfItems -= l_amount - l_oldLastItem + 1;
    }
    CHECK(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, l_oldNumberOfItems));

    DestroyQueueUsingDeallocator(l_queue);

}
