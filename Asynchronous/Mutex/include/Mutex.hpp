#ifndef MUTEX__ASYNCHRONOUS_MUTEX_MUTEX_HPP

#include "../../../LibraryMeta/LibraryMeta.hpp"
#include "../../../Debugging/Logging/Log.hpp"

namespace Library::Asynchronous
{

    /**
     * @brief An opaque structure that is used for handels to a mutex.
     * 
     * @details Pointers and references to this structure are used as handles to
     * mutexes. Mutexes are strucutres that are used for mutual exclusion
     * between different threads in the proccess.
     * 
     */
    struct Mutex;

    //TODO: Some sort of mutex warpper struct that takes in a T and any access
    //to it requires that the mutex inside is locked, maybe put into a rules
    //module


    Mutex* AllocateMutexUsingAllocator(
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    );
    inline Mutex* AllocateMutex()
    {
        LogDebugLine("Using defaults for AllocateMutexUsingAllocator.");
        return AllocateMutexUsingAllocator(
            Library::LibraryMeta::g_DEFAULT_ALLOCATOR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR_DATA
        );
    }

    /**
     * @brief Allocates a mutex using p_allocate.
     * 
     * @details The allocated mutex can then be used for synchronization. The
     * number of bytes allocated is implementation defined.
     * 
     * @param p_allocate The allocator to use.
     * @param p_alloc_error A callback to be called if allocation fails.
     * @param p_alloc_error_data Data for the callback.
     * @return A pointer to a section of memory that stores a mutex if no errors
     * occurred. Null if some sort of error occurred.
     *  
     * This function can fail and return null in some cases:
     * - Allocation failure, in this case the function first calls p_alloc_error
     * with p_alloc_error_data and returns null.
     * - Internal error while creating the mutex, in this case the function
     * returns null, and any internal resources are cleaned up. The allocator is
     * never called. p_alloc_error is never called. 
     * 
     */
    void CreateMutexAt(Mutex& outp_mutex);

    /**
     * @brief Locks p_mutex.
     * 
     * @details
     * 
     * @param p_mutex 
     * @return true 
     * @return false 
     */
    bool LockMutex(Mutex& p_mutex);
    bool TryToLockMutex(Mutex& p_mutex);

    bool UnlockMutex(Mutex& p_mutex);


    void SetMutexOwnerDeathCallback(
        Mutex& p_mutex,
        void (*p_callback) (void*), void* p_callback_data
    );


    void DestroyMutex(Mutex& p_mutex);

    void DeallocateMutexUsingDeallocator(Mutex& p_mutex, void (&p_deallocate) (void*));
    inline void DeallocateMutex(Mutex& p_mutex)
    {
        LogDebugLine("Using defaults for DeallocateMutexUsingDeallocator.");
        DeallocateMutexUsingDeallocator(
            p_mutex,
            Library::LibraryMeta::g_DEFAULT_DEALLOCATOR
        );
    }

}

#endif // !MUTEX__ASYNCHRONOUS_MUTEX_MUTEX_HPP
