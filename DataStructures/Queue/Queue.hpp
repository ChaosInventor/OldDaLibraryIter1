#ifndef QUEUE__DATA_STRUCTURES_QUEUE_QUEUE_HPP
#define QUEUE__DATA_STRUCTURES_QUEUE_QUEUE_HPP

#include "../../Debugging/Logging/Log.hpp"
#include "../Array/Array.hpp"

namespace Library::DataStructures::Queue
{

    template<typename T>
    struct Queue
    {

        /**
         * @brief The buffer of the queue that is used to store items.
         *
         */
        Array::Array<T> m_Buffer;
        /**
         * @brief The index of the last item that can be read from the queue.
         *
         */
        Size m_LastItem;


        /**
         * @brief Constructs an empty queue.
         *
         * @details See @ref QueueTypes for info on the different queue types.
         *
         */
        Queue():
        m_Buffer(),
        m_LastItem(0)
        {
            LogDebugLine("Constructed empty queue at " << (void*)this);
        }
        /**
         * @brief Copies all of the fields from p_other to this.
         *
         */
        Queue(const Queue<T>& p_other):
        m_Buffer(p_other.m_Buffer),
        m_LastItem(p_other.m_LastItem)
        {
            LogDebugLine("Constructed queue at " << (void*)this << " by copying from " << p_other);
        }
        /**
         * @brief Copies all of the fields from p_other to this. And then
         * creates an empty queue at p_other.
         *
         * @details See @ref QueueTypes for info on the different queue types.
         *
         */
        Queue(Queue<T>&& p_other):
        m_Buffer((Array::Array<T>&&)p_other.m_Buffer),
        m_LastItem(p_other.m_LastItem)
        {
            p_other.m_LastItem = 0;
            LogDebugLine("Constructed queue at " << (void*)this << " by "
            "moving from queue at " << (void*)&p_other);
        }

        /**
         * @brief Shallow copies p_array to m_Buffer.
         * **NO allocation takes place.**m_LastItem is set to 0.
         *
         */
        Queue(const Array::Array<T>& p_array):
        m_Buffer(p_array),
        m_LastItem(0)
        {
            LogDebugLine("Constructed queue from array " << p_array);
        }


        /**
         * @brief Same as copy constructor. Returns *this.
         *
         */
        Queue<T>& operator=(const Queue<T>& p_other)
        {

            LogDebugLine("Copying from queue " << p_other << " to queue"
            << *this);

            m_Buffer = p_other.m_Buffer;
            m_LastItem = p_other.m_LastItem;

            return *this;

        }
        /**
         * @brief Same as move operator. Returns *this.
         *
         */
        Queue<T>& operator=(Queue<T>&& p_other)
        {

            LogDebugLine("Moving from queue " << p_other << " to queue"
            << *this);

            m_Buffer = p_other.m_Buffer;
            m_LastItem = p_other.m_LastItem;

            p_other.m_Buffer = Array::Array<T>();
            p_other.m_LastItem = 0;

            return *this;

        }

    };


    #ifdef DEBUG
    template<typename T>
    const Debugging::Log& operator<<(const Debugging::Log& p_log, const Queue<T>& p_queue)
    {

        p_log << (void*)&p_queue << " { m_Buffer = ";
        p_log << p_queue.m_Buffer;
        p_log << ", m_LastItem  = " << p_queue.m_LastItem;
        p_log << " }";

        return p_log;

    }
    #endif //DEBUG


    /**
     * @brief Creates a queue of p_capacity capacity using p_allocate as an
     * allocator
     *
     * @details This function in reality is just a wrapper for
     * @ref Array::CreateArrayAtOfCapacityUsingAllocator, that function is called
     * to create outp_buffer.m_Buffer. outp_buffer.m_LastItem is then set to 0.
     *
     * Make sure to read @ref Array::CreateArrayAtOfCapacityUsingAllocator for
     * all of the details on how the queue's buffer is created.
     *
     */
    template<typename T>
    inline void CreateQueueAtOfCapacityUsingAllocator(
        Queue<T>& outp_buffer,
        const Size& p_capacity,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {
        LogDebugLine("The created array will be used as part of a queue.");
        Array::CreateArrayAtOfCapacity(
            outp_buffer.m_Buffer,
            p_capacity,
            p_allocate, p_alloc_error, p_alloc_error_data
        );
        outp_buffer.m_LastItem = 0;
    }
    template<typename T>
    inline void CreateQueueAtOfCapacityUsingAllocator(
        Queue<T>& outp_buffer,
        const Size& p_capacity
    )
    {
        LogDebugLine("The created array will be used as part of a queue.");
        Array::CreateArrayAtOfCapacity(
            outp_buffer.m_Buffer,
            p_capacity
        );
        outp_buffer.m_LastItem = 0;
    }

    /**
     * @brief Does a complete copy from p_queue to outp_buffer
     *
     * @details Allocates a new buffer that is the same capacity as p_queue's,
     * then copies all of the items from p_queue to the new buffer. outp_buffer
     * is then set set up to be identical to p_queue except that a different
     * buffer is used.
     *
     * The function used for copying the buffer is
     * @ref Array::CreateCopyAtOfArrayUsingAllocator, make sure to check it's
     * documentation.
     *
     * In case of an allocation error or if p_queue is null, an empty queue is
     * made at outp_buffer.
     *
     * @time O(n), n being the capacity of p_queue.
     *
     */
    template<typename T>
    void CreateCopyAtOfQueueUsingAllocator(
        Queue<T>& outp_buffer,
        const Queue<T>& p_queue,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {

        LogDebugLine("Copying queue from " << p_queue << " to " << outp_buffer);
        
        //The copy array function only copies everything up to the size of the
        //array, but this function requires that the entire capacity is copied,
        //so to solve this we make a copy the queue's buffer as in copying the
        //pointer and pretend as if the entire capacity is used by setting
        //m_Size to m_Capacity.
        Array::Array<T> l_copy = p_queue.m_Buffer;
        l_copy.m_Size = l_copy.m_Capacity;

        Array::CreateCopyAtOfArray(
            outp_buffer.m_Buffer,
            l_copy,
            p_allocate, p_alloc_error, p_alloc_error_data
        );

        //If no allocation error occurred.
        if(outp_buffer.m_Buffer != nullptr)
        {
            LogDebugLine("Setting the item tail.");
            outp_buffer.m_LastItem = p_queue.m_LastItem;

            //Now we need to set the head to the correct number.
            outp_buffer.m_Buffer.m_Size = p_queue.m_Buffer.m_Size;
        }
        else
        {
            LogDebugLine("Allocation error detected, setting tail to 0.");
            outp_buffer.m_LastItem = 0;

            //No need to modify the head here since it is already 0 in this
            //case.
        }
        
    }
    template<typename T>
    inline void CreateCopyAtOfQueueUsingAllocator(
        Queue<T>& outp_buffer,
        const Queue<T>& p_queue
    )
    {
        LogDebugLine("Using defaults for CreateCopyAtOfQueueUsingAllocator");
        CreateCopyAtOfQueueUsingAllocator(
            outp_buffer,
            p_queue,
            Library::LibraryMeta::g_DEFAULT_ALLOCATOR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR_DATA
        );
        LogDebugLine("Returing from defaults function");
    }


    /**
     * @brief Checks if p_queue is empty.
     * 
     * @details For more details on the types of queues, and which queues are
     * considered to be empty, see @ref QueueTypes
     * 
     * @return True if p_queue is empty.
     * @return False if p_queue is not empty.
     * 
     */
    template<typename T>
    inline bool QueueIsEmpty(const Queue<T>& p_queue)
    {
        return p_queue.m_Buffer.m_Size == p_queue.m_LastItem;
    }
    template<typename T>
    /**
     * @brief Checks if p_queue is full.
     * 
     * @details For more details on the types of queues, and which queues are
     * considered to be full, see @ref QueueTypes
     * 
     * @return True if p_queue is full.
     * @return False if p_queue is not full.
     * 
     */
    inline bool QueueIsFull(const Queue<T>& p_queue)
    {
        return p_queue.m_Buffer.m_Size == p_queue.m_Buffer.m_Capacity;
    }

    /**
     * @brief Finds the number of items that can be read from p_queue.
     * //TODO:
     */
    template<typename T>
    Size FindNumberOfItemsInQueue(const Queue<T>& p_queue)
    {

        //TODO: Possibly make this branchless.

        //If there no items before the item tail the distance between it and the
        //item head gives the number of items.
        if(p_queue.m_Buffer.m_Size < p_queue.m_LastItem)
        {
            return p_queue.m_Buffer.m_Size - p_queue.m_LastItem;
        }
        else
        {
            //Here the item head is the number of items after the begining of
            //the buffer, while the item tail minus the buffer capacity is the
            //number of items between the item head and the end of the buffer.
            //
            //To get the total number of items you just add them up.
            return p_queue.m_Buffer.m_Size + (p_queue.m_Buffer.m_Capacity - p_queue.m_LastItem);
        }

    }


    //TODO: Document the requirements for T
    /**
     * @brief Increases the item capacity of p_queue.
     *
     * @details Increases p_queue.m_Buffer.m_Capacity by p_amount. This is done
     * by reallocating p_queue's buffer so that it's of size
     * p_queue.m_Buffer.m_Capacity + p_amount.
     *
     * This function does not handle the reallocation of the buffer, the
     * @ref IncreaseArrayCapacityByAmountUsingReallocator function is used
     * instead. Make sure to check it's documentation for details on how the
     * capacity is changed and how that can fail.
     *
     * No items are lost when the capacity is increased successfully.
     *
     * This function also covers an edge case where the next empty item is
     * behind the next available item. See the source of this function for
     * details on this edge case.
     *
     * @time O(n) or O(1), n being the number of items after the end of the
     * queue buffer. O(n) only applies when the item head is behind the item
     * tail in terms of indexes, in that case the function needs to move all of
     * the items backward in order to fill in the empty slots left behind by the
     * increased capacity.
     * 
     * @param p_queue The queue which will have it's capcity increased.
     * @param p_amount By how much should the queue's capacity be increased.
     * @param p_reallocate The reallocator to use to get more memory for
     * p_queue's buffer
     * @param p_realloc_error A callback to call when reallocation fails.
     * @param p_realloc_error_data Data that will be passed to the realloc error
     * callback.
     * 
     */
    template<typename T>
    void IncreasesQueueCapicityByAmountUsingReallocator(
        Queue<T>& p_queue,
        const Size& p_amount,
        void* (&p_reallocate) (void*, Size),
        void (*p_realloc_error) (void*), void* p_realloc_error_data
    )
    {

        LogDebugLine("Increasing the capacity of queue " << p_queue
        << " by " << p_amount);

        Size l_oldCapacity = p_queue.m_Buffer.m_Capacity;

        IncreaseArrayCapacityByAmountUsingReallocator(
            p_queue.m_Buffer,
            p_amount,
            p_reallocate, p_realloc_error, p_realloc_error_data
        );

        //TODO: Explain this edge case.
        if(p_queue.m_Buffer.m_Size < p_queue.m_LastItem)
        {
            LogDebugLine("There are empty slots before the item head due to"
            " the increased capacity, moving items backward.");
            for(
                Size i = l_oldCapacity, n = 0;
                n != p_queue.m_Buffer.m_Size;
                i = (i + 1) % p_queue.m_Buffer.m_Capacity, ++n
            )
            {
                if(n == p_queue.m_Buffer.m_Size)
                {
                    LogDebugLine("No more items need moving, adjusting item head.");
                    p_queue.m_Buffer.m_Size = i;
                    break;
                }

                LogDebugLine("Moving item backward");
                p_queue.m_Buffer[i] = p_queue.m_Buffer[n];
            }

            LogDebugLine("Finished moving items.");
        }

    }
    template<typename T>
    inline void IncreasesQueueCapicityByAmountUsingReallocator(
        Queue<T>& p_queue,
        const Size& p_amount
    )
    {
        LogDebugLine("Using defaults for IncreasesQueueCapicityByAmountUsingReallocator");
        IncreasesQueueCapicityByAmountUsingReallocator(
            p_queue, p_amount,
            Library::LibraryMeta::g_DEFAULT_REALLOCATOR,
            Library::LibraryMeta::g_DEFAULT_REALLOC_ERROR,
            Library::LibraryMeta::g_DEFAULT_REALLOC_ERROR_DATA
        );
        LogDebugLine("Returning from defaults function");
    }

    /**
     * @brief Decreases the item capacity of p_queue.
     *
     * @details Decreases the capacity of p_queue.m_Buffer by p_amount. This
     * is done by reallocating the memory of the buffer so that it is of size
     * p_queue.m_Buffer.m_Capacity - p_amount.
     *
     * This function does not handle the reallocation of the buffer, the
     * @ref DecreaseArrayCapacityByAmountUsingReallocator function is used for
     * this. Make sure to read it's documentation for details on how
     * reallocation is done and how it could fail.
     *
     * Items are lost after a successful reallocation.
     *
     * @param p_queue The queue who's capacity will be decreased.
     * @param p_amount By how much the capacity of p_queue should be decreased.
     * @param p_reallocate The reallocator to use to decrase the capacity of
     * p_queue.
     * @param p_realloc_error A callback to call when reallocation fails.
     * @param p_realloc_error_data Data that will be passed to the realloc error
     * callback.
     */
    template<typename T>
    void DecreaseQueueCapacityByAmountUsingReallocator(
        Queue<T>& p_queue,
        const Size p_amount,
        void* (&p_reallocate) (void*, Size),
        void (*p_realloc_error) (void*), void* p_realloc_error_data
    )
    {

        LogDebugLine("Decreasing the capacity of queue " << p_queue
        << " by " << p_amount);

        DecreaseArrayCapacityByAmountUsingReallocator(
            p_queue.m_Buffer,
            p_amount,
            p_reallocate, p_realloc_error, p_realloc_error_data
        );

        //TODO: Explain edge case.
        if(p_queue.m_LastItem >= p_queue.m_Buffer.m_Capacity)
        {
            LogDebugLine("Adjusting the item tail.");
            p_queue.m_LastItem = 0;
            if(p_queue.m_Buffer.m_Size >= p_queue.m_Buffer.m_Capacity)
            {
                LogDebugLine("Adjusting the item head");
                p_queue.m_Buffer.m_Size = 0;
            }
        }

    }
    template<typename T>
    inline void DecreaseQueueCapacityByAmountUsingReallocator(
        Queue<T>& p_queue,
        const Size p_amount
    )
    {
        LogDebugLine("Using defaults for DecreaseQueueCapacityByAmountUsingReallocator.");
        DecreaseQueueCapacityByAmountUsingReallocator(
            p_queue, p_amount,
            Library::LibraryMeta::g_DEFAULT_REALLOCATOR,
            Library::LibraryMeta::g_DEFAULT_REALLOC_ERROR,
            Library::LibraryMeta::g_DEFAULT_REALLOC_ERROR_DATA
        );
        LogDebugLine("Returing from defaults functions.");
    }

    template<typename T>
    void AddItemToQueue(const T& p_item, Queue<T>& p_queue)
    {

        LogDebugLine("Adding item " << p_item << " to queue " << p_queue);

        //A null queue is also a full queue.
        if(QueueIsFull(p_queue))
        {
            LogDebugLine("The queue is full, returning");
            return;
        }

        //TODO: Extract in different function that only does this.
        LogDebugLine("Adding the item.");
        p_queue.m_Buffer[p_queue.m_Buffer.m_Size] = p_item;
        LogDebugLine("Advancing item head.");
        p_queue.m_Buffer.m_Size = (p_queue.m_Buffer.m_Size + 1) % p_queue.m_Buffer.m_Capacity;

        //This would mean that the queue has become full.
        if(p_queue.m_Buffer.m_Size == p_queue.m_LastItem)
        {
            LogDebugLine("Queue became full, setting head appropriately.");
            p_queue.m_Buffer.m_Size = p_queue.m_Buffer.m_Capacity;
        }

    }

    template<typename T>
    void RemoveItemFromQueuePutItAt(Queue<T>& p_queue, T& outp_item)
    {

        LogDebugLine("Removing item from queue " << p_queue << " and "
        "putting it in address " << (void*)&outp_item);

        //A null queue is also an empty queue.
        if(QueueIsEmpty(p_queue))
        {
            LogDebugLine("The queue is empty, returning.");
            return;
        }

        //TODO: Extract in different function that only does this.
        LogDebugLine("Copying item at tail over to location.");
        outp_item = p_queue.m_Buffer[p_queue.m_LastItem];

        //If the queue was full, then it's not any more.
        if(QueueIsFull(p_queue))
        {
            LogDebugLine("The queue is no longer full, setting head appropriately");
            p_queue.m_Buffer.m_Size = p_queue.m_LastItem;
        }

        LogDebugLine("Advancing the tail.");
        p_queue.m_LastItem = (p_queue.m_LastItem + 1) % p_queue.m_Buffer.m_Capacity;

    }

    template<typename T>
    void PutQueueItemAt(const Queue<T>& p_queue, T& outp_item)
    {

        if(QueueIsEmpty(p_queue))
        {
            return;
        }

        outp_item = p_queue.m_Buffer[p_queue.m_LastItem];

    }


    /**
     * @brief Destroys and frees all of the resources used by p_queue.
     *
     * @details p_queue.m_Buffer is destroyed using
     * @ref Array::DestroyArrayUsingDeallocator. After that is complete an
     * empty queue is created at p_queue.
     *
     * Make sure to read @ref Array::DestroyArrayUsingDeallocator for how
     * p_queue.m_Buffer is handled.
     *
     */
    template<typename T>
    inline void DestroyQueueUsingDeallocator(Queue<T>& p_queue, void (&p_deallocate) (void*))
    {
        LogDebugLine("Destroying queue " << p_queue);
        Array::DestoryArray(p_queue.m_Buffer, p_deallocate);
        p_queue = Queue<T>();
    }
    template<typename T>
    inline void DestroyQueueUsingDeallocator(Queue<T>& p_queue)
    {
        LogDebugLine("Destroying queue " << p_queue);
        Array::DestoryArray(p_queue.m_Buffer);
        p_queue = Queue<T>();
    }

}

#endif //QUEUE__DATA_STRUCTURES_QUEUE_QUEUE_HPP