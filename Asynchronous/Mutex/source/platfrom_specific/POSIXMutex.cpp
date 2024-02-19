#include "../../include/Mutex.hpp"

#include <errno.h>

#include "../../include/platfrom_specific/POSIXMutex.hpp"

namespace Library::Asynchronous
{

    Mutex* AllocateMutexUsingAllocator(
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {

        LogDebugLine("Allocating a mutex.");

        Mutex* l_returnValue = (Mutex*)p_allocate(sizeof(Mutex));
        if(l_returnValue == nullptr)
        {
            LogDebugLine("Allocation of mutex failed, bruh.");
            
            if(p_alloc_error != nullptr)
            {
                LogDebugLine("Alloc error is not null so calling it.");
                p_alloc_error(p_alloc_error_data);
            }
            LogDebugLine("Returning null from unsuccessful allocation.");
            
            return nullptr;
        }
        
        LogDebugLine("Successfully allocated a mutex at address "
        << (void*)l_returnValue);

        *l_returnValue = Mutex();

        return l_returnValue;

    }

    void CreateMutexAt(Mutex& outp_mutex)
    {

        LogDebugLine("Creating a new mutex.");

        pthread_mutexattr_t l_attributes;
        if(pthread_mutexattr_init(&l_attributes) != 0)
        {
            LogDebugLine("Could not initialize the mutex attributes, returing.");
            return;
        }

        pthread_mutexattr_setrobust(&l_attributes, PTHREAD_MUTEX_ROBUST);
        pthread_mutexattr_settype(&l_attributes, PTHREAD_MUTEX_ERRORCHECK);

        LogDebugLine("Created attributes.");

        pthread_mutex_t l_mutex;
        if(pthread_mutex_init(&l_mutex, &l_attributes) != 0)
        {
            LogDebugLine("Could not initialize a mutex, returning");

            pthread_mutexattr_destroy(&l_attributes);

            return;
        }
        LogDebugLine("Created mutex.");

        LogDebugLine("Getting rid of attributes");
        pthread_mutexattr_destroy(&l_attributes);

        outp_mutex.m_Mutex = l_mutex;
        outp_mutex.m_OwnerDeathCallback = nullptr;
        outp_mutex.m_OwnerDeathCallbackData = nullptr;

        LogDebugLine("Successfully created mutex, returning.");

    }

    bool LockMutex(Mutex& p_mutex)
    {

        LogDebugLine("Locking mutex at " << (void*)&p_mutex);

        int l_code = pthread_mutex_lock(&p_mutex.m_Mutex);
        if(l_code != 0)
        {
            if(l_code == EOWNERDEAD)
            {
                LogDebugLine("The previous owner of the mutex died!");
                if(p_mutex.m_OwnerDeathCallback != nullptr)
                {
                    LogDebugLine("Callback for owner death is not null so "
                    "calling it.");
                    p_mutex.m_OwnerDeathCallback(p_mutex.m_OwnerDeathCallbackData);
                }

                pthread_mutex_consistent(&p_mutex.m_Mutex);
                return true;
            }
            if(l_code == EDEADLK)
            {
                LogDebugLine("This thread already owns this mutex, returing true");
                return true;
            }

            LogDebugLine("Error with code " << l_code << " occurred, "
            "returning false.");
            return false;
        }

        LogDebugLine("Everything went well, returning true.");
        return true;

    }
    bool TryToLockMutex(Mutex& p_mutex)
    {

        LogDebugLine("Locking mutex at " << (void*)&p_mutex);

        int l_code = pthread_mutex_trylock(&p_mutex.m_Mutex);
        if(l_code != 0)
        {
            if(l_code == EOWNERDEAD)
            {
                LogDebugLine("The previous owner of the mutex died!");
                if(p_mutex.m_OwnerDeathCallback != nullptr)
                {
                    LogDebugLine("Callback for owner death is not null so "
                    "calling it.");
                    p_mutex.m_OwnerDeathCallback(p_mutex.m_OwnerDeathCallbackData);
                }

                //TODO: See if the mutex is now owned by this thread or not.
                pthread_mutex_consistent(&p_mutex.m_Mutex);
                return true;
            }

            LogDebugLine("Error with code " << l_code << " occurred, "
            "returning false.");
            return false;
        }

        LogDebugLine("Everything went well, returning true.");
        return true;

    }

    bool UnlockMutex(Mutex& p_mutex)
    {
        LogDebugLine("Unlocking mutex at " << (void*)&p_mutex);
        return pthread_mutex_unlock(&p_mutex.m_Mutex) == 0;
    }


    void SetMutexOwnerDeathCallback(
        Mutex& p_mutex,
        void (*p_callback) (void*), void* p_callback_data
    )
    {

        LogDebugLine("Setting owner death callback for mutex at "
        << (void*)&p_mutex);

        if(LockMutex(p_mutex) == false)
        {
            LogDebugLine("Could not lock the mutex, returning without setting "
            "the callbacks.");
            return;
        }
        
        p_mutex.m_OwnerDeathCallback = p_callback;
        p_mutex.m_OwnerDeathCallbackData = p_callback_data;
        
        UnlockMutex(p_mutex);

    }


    void DestroyMutex(Mutex& p_mutex)
    {
        
        LogDebugLine("Destroying mutex at " << (void*)&p_mutex);

        pthread_mutex_destroy(&p_mutex.m_Mutex);

        p_mutex = Mutex();

    }

    void DeallocateMutexUsingDeallocator(Mutex& p_mutex, void (&p_deallocate) (void*))
    {
        p_deallocate(&p_mutex);
    }


}
