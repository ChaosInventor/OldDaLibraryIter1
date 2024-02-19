#include <catch2/catch.hpp>

#include "../../../Debugging/Debugging.hpp"
#include "../Queue.hpp"
#include "QueueHelperFunctions.hpp"

using namespace Library::DataStructures::Queue;
using namespace Library::DataStructures::Array;
using namespace Debugging;

//Note: The tests here do not test more specific things such as allocation
//errors or if the buffer was copied successfully. These things are handled by
//the array functions that are used and the array functions are already tested
//in their own test cases, so there is no need to do the same testing twice.

TEST_CASE("Create of capacity", "[Queue][Creation]")
{

    Size l_capacity = GENERATE(range(0, 100));
    Queue<int> l_queue;
    
    SECTION("Defaults")
    {
        CreateQueueAtOfCapacityUsingAllocator(l_queue, l_capacity);
    }
    SECTION("Customs")
    {
        bool l_called = false;
        CreateQueueAtOfCapacityUsingAllocator(
            l_queue, l_capacity,
            malloc, &GeneralErrorCallback, &l_called
        );
        CHECK(l_called == false);
    }

    CHECK(l_queue.m_LastItem == 0);
    CHECK(l_queue.m_LastItem == l_queue.m_Buffer.m_Size);

    DestroyQueueUsingDeallocator(l_queue);

}

TEST_CASE("Create copy of queue", "[Queue][Creation]")
{

    Size l_capacity = GENERATE(take(10, random(10, 100)));
    
    Queue<int> l_queue = GenerateRandomQueueOfCapacityAndWithItem<int>(l_capacity, rand());
    //In case of allocation failure.
    REQUIRE(l_queue.m_Buffer.m_Capacity == l_capacity);
    //Counts the number of items in the random queue.
    Size l_numberOfItems = 0;
    for(
        Size i = l_queue.m_LastItem;
        i != l_queue.m_Buffer.m_Size;
        i = (i + 1) % l_capacity
    )
    {
        ++l_numberOfItems;
    }

    Queue<int> l_result;
    
    SECTION("Defaults")
    {
        CreateCopyAtOfQueueUsingAllocator(l_result, l_queue);
    }
    SECTION("Customs")
    {
        bool l_called = false;
        CreateCopyAtOfQueueUsingAllocator(
            l_result,
            l_queue,
            malloc, &GeneralErrorCallback, &l_called
        );
        CHECK(l_called == false);
    }

    //The random queue is also checked just to make sure that it was not mutated
    //in any way.
    CHECK(l_result.m_Buffer.m_Capacity == l_capacity);
    CHECK(l_queue.m_Buffer.m_Capacity == l_capacity);

    CHECK(QueueIntegrityIsGoodAndItHasNumberOfItems(l_result, l_numberOfItems));
    CHECK(QueueIntegrityIsGoodAndItHasNumberOfItems(l_queue, l_numberOfItems));

    DestroyQueueUsingDeallocator(l_queue);
    DestroyQueueUsingDeallocator(l_result);

}

TEST_CASE("Destroy queue", "[Queue][Destruction]")
{

    Size l_capacity = GENERATE(range(0, 100));
    Queue<int> l_queue;

    CreateQueueAtOfCapacityUsingAllocator(l_queue, l_capacity);

    DestroyQueueUsingDeallocator(l_queue);

    CHECK(l_queue.m_Buffer == Array<int>());
    CHECK(l_queue.m_LastItem == 0);

}
