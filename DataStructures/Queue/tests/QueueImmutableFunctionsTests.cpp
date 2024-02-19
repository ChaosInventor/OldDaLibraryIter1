#include <catch2/catch.hpp>

#include "../Queue.hpp"
#include "QueueHelperFunctions.hpp"

using namespace Library::DataStructures::Queue;
using namespace Catch::Generators;

TEST_CASE("Is queue empty or full", "[Queue][Immutable]")
{

    Size l_capacity = GENERATE(take(10, random(1, 100)));

    Queue<int> l_nullQueue;
    Queue<int> l_fullQueue;
    Queue<int> l_emptyQueue;
    Queue<int> l_availableQueue;

    CreateQueueAtOfCapacityUsingAllocator(l_fullQueue, l_capacity);
    CreateQueueAtOfCapacityUsingAllocator(l_emptyQueue, l_capacity);
    CreateQueueAtOfCapacityUsingAllocator(l_availableQueue, l_capacity * 2);

    REQUIRE(l_fullQueue.m_Buffer != nullptr);
    REQUIRE(l_emptyQueue.m_Buffer != nullptr);
    REQUIRE(l_availableQueue.m_Buffer != nullptr);

    for(Size i = 0; i < l_capacity; ++i)
    {
        AddItemToQueue(rand(), l_fullQueue);
        AddItemToQueue(rand(), l_availableQueue);
    }

    CHECK(QueueIsFull(l_nullQueue));
    CHECK(QueueIsEmpty(l_nullQueue));

    CHECK(QueueIsFull(l_fullQueue));
    CHECK_FALSE(QueueIsEmpty(l_fullQueue));

    CHECK_FALSE(QueueIsFull(l_emptyQueue));
    CHECK(QueueIsEmpty(l_emptyQueue));

    CHECK_FALSE(QueueIsFull(l_availableQueue));
    CHECK_FALSE(QueueIsEmpty(l_availableQueue));

}
