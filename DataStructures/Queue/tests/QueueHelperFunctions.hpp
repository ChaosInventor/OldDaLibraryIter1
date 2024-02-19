/**
 * @file QueueHelperFunctions.hpp
 * 
 * @brief Contains some helper functions for testing queues.
 *  
 */
#ifndef QUEUE_HELPER_FUNCTIONS_HPP
#define QUEUE_HELPER_FUNCTIONS_HPP

#include "../Queue.hpp"

using namespace Library::DataStructures::Queue;

/**
 * @brief Checks if p_queue is correct and that it has p_expected_number_of_items
 * items.
 * 
 * @details All errors that are found are reported using @ref LogLineToSTDError.
 *  
 * @param p_queue The queue to test.
 * @param p_expected_number_of_items The number of items you expect the queue to
 * have. 
 * @return True if the queue is correct and has p_expected_number_of_items items,
 * false otherwise.
 * 
 */
template<typename T>
bool QueueIntegrityIsGoodAndItHasNumberOfItems(const Queue<T>& p_queue, const Size& p_expected_number_of_items)
{

    LogDebugLine("Checking if the queue " << p_queue << " is malformed in "
    "anyway. Also checking if it has " << p_expected_number_of_items << " item queued up.");

    bool l_returnValue = true;

    //Null queue
    if(p_queue.m_Buffer == nullptr)
    {
        if(p_queue.m_LastItem != 0)
        {
            LogDebugLine("The queue has a null buffer but the item tail is"
            " not 0. It is " << p_queue.m_LastItem);
            l_returnValue = false;
        }
        if(p_queue.m_Buffer.m_Capacity != 0)
        {
            LogDebugLine("The queue has a null buffer but the capacity is "
            "not 0. It is " << p_queue.m_Buffer.m_Capacity);
            l_returnValue = false;
        }
        if(p_queue.m_Buffer.m_Size != 0)
        {
            LogDebugLine("The queue has a null buffer but the item head is"
            " not 0. It is " << p_queue.m_Buffer.m_Size);
            l_returnValue = false;
        }
        if(p_expected_number_of_items != 0)
        {
            LogDebugLine("The queue has a null buffer but the expected "
            "number of items is not 0. It is " << p_expected_number_of_items);
        }
        
        return l_returnValue;
    }
    //Empty queue
    if(p_queue.m_Buffer.m_Size == p_queue.m_LastItem)
    {
        if(p_queue.m_Buffer.m_Capacity == 0)
        {
            LogDebugLine("The empty queue has a capacity of 0.");
            l_returnValue = false;
        }
        if(p_queue.m_LastItem >= p_queue.m_Buffer.m_Capacity)
        {
            LogDebugLine("The item tail( " << p_queue.m_LastItem << ") is "
            "greater than or equaled to the queue's capacity( "
            << p_queue.m_Buffer.m_Capacity << " ).");
            l_returnValue = false;
        }
        if(p_queue.m_Buffer.m_Size >= p_queue.m_Buffer.m_Capacity)
        {
            LogDebugLine("An empty queue has it's item head( "
            << p_queue.m_Buffer.m_Size << " ) greater than or equaled to the "
            "queue's capacity( " << p_queue.m_Buffer.m_Capacity << " ).");
            l_returnValue = false;
        }
        if(p_expected_number_of_items != 0)
        {
            LogDebugLine("The queue is empty but the expected number of "
            "items is not 0. It is " << p_expected_number_of_items);
            l_returnValue = false;
        }
        
        return l_returnValue;
    }
    //Full queue
    if(p_queue.m_Buffer.m_Size == p_queue.m_Buffer.m_Capacity)
    {
        if(p_queue.m_Buffer.m_Capacity == 0)
        {
            LogDebugLine("The full queue has a capacity of 0.");
            l_returnValue = false;
        }
        if(p_queue.m_LastItem >= p_queue.m_Buffer.m_Capacity)
        {
            LogDebugLine("The item tail( " << p_queue.m_LastItem
            << " ) is greater than or equaled to the queue's capacity( "
            << p_queue.m_Buffer.m_Capacity << ").");
            l_returnValue = false;
        }
        if(p_queue.m_Buffer.m_Capacity != p_expected_number_of_items)
        {
            LogDebugLine("The expected number of items( "
            << p_expected_number_of_items << " ) is not the queue's capacity( "
            << p_queue.m_Buffer.m_Capacity << " ).");
            l_returnValue = false;
        }

        return l_returnValue;
    }

    //Available queue
    if(p_queue.m_Buffer.m_Capacity == 0)
    {
        LogDebugLine("The available queue has a capacity of 0.");
        l_returnValue = false;
    }
    if(p_queue.m_Buffer.m_Size >= p_queue.m_Buffer.m_Capacity)
    {
        LogDebugLine("The item head( " << p_queue.m_Buffer.m_Size
        << " ) of the queue is greater than or equaled to the queue's capacity ( "
        << p_queue.m_Buffer.m_Capacity << " ).");
        l_returnValue = false;
    }
    if(p_queue.m_LastItem >= p_queue.m_Buffer.m_Capacity)
    {
        LogDebugLine("The item tail( " << p_queue.m_LastItem
        << " ) of the queue is greater than or equaled to the queue's capacity ( "
        << p_queue.m_Buffer.m_Capacity << " ).");
        l_returnValue = false;
    }

    //Discovers the number of items in the queue.
    Size l_numberOfItems = 0;
    for(
        Size i = p_queue.m_LastItem;
        i != p_queue.m_Buffer.m_Size;
        i = (i + 1) % p_queue.m_Buffer.m_Capacity,
        ++l_numberOfItems
    );
    if(l_numberOfItems != p_expected_number_of_items)
    {
        LogDebugLine("The counted number of items " << " ( "
        << l_numberOfItems << " ) is not the expted number of items ( "
        << p_expected_number_of_items << " ).");
        l_returnValue = false;
    }

    return l_returnValue;

}

/**
 * @brief Generates a random queue of p_capacity.
 * 
 * @details The queue has p_item written to it 0 to p_capacity * 2 times. After 
 * the queue is read 0 to p_capacity * 2 times. The result of the read is
 * ignored.
 * 
 * The default allocator and friends are used for allocation and callback.
 * 
 * @tparam T Must be a valid type that can be copied and moved as well as having
 * a default constructor so that an instance of it can be made by this function. 
 * @param p_capacity The capacity that the random queue should have.
 * @param p_item The item to use.
 * @return The random queue.
 * 
 */
template<typename T>
Queue<T> GenerateRandomQueueOfCapacityAndWithItem(const Size& p_capacity, const T& p_item)
{

    LogDebugLine("Generating random queue...");

    Queue<T> l_returnValue;
    CreateQueueAtOfCapacityUsingAllocator(l_returnValue, p_capacity);
    //In case of alloc error or if p_capacity was 0, in either case the function
    //needs to return.
    if(l_returnValue.m_Buffer.m_Capacity == 0)
    {
        return l_returnValue;
    }
    
    Size l_numberOfReads = rand() % p_capacity * 2;
    Size l_numberOfWrites = rand() % p_capacity * 2;

    T l_temp;
    for(; l_numberOfWrites > 0; --l_numberOfWrites)
    {
        AddItemToQueue(p_item, l_returnValue);
    }
    for(; l_numberOfReads > 0; --l_numberOfReads)
    {
        RemoveItemFromQueuePutItAt(l_returnValue, l_temp);
    }

    LogDebugLine("Successfully generated random queue " << l_returnValue);
    return l_returnValue;

}

#endif //QUEUE_HELPER_FUNCTIONS_HPP