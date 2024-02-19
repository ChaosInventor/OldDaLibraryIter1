#include <pthread.h>

#include "../../include/Thread.hpp"

namespace Library::Asynchronous
{

    struct Thread
    {
        pthread_t m_ThreadID;
        bool m_Finished;
        void* m_ReturnValue;
        Size m_References;
    };


    bool operator==(const Thread& p_left, const Thread& p_right)
    {
        return pthread_equal(p_left.m_ThreadID, p_right.m_ThreadID) == 0;
    }
    bool operator!=(const Thread& p_left, const Thread& p_right)
    {
        return pthread_equal(p_left.m_ThreadID, p_right.m_ThreadID) != 0;
    }


    Thread* AllocateThreadUsingAllocator(
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*),
        void* p_alloc_error_data
    )
    {

        LogDebugLine("Allocating thread.");

        Thread* l_returnValue = (Thread*)p_allocate(sizeof(Thread));
        if(l_returnValue == nullptr)
        {
            LogDebugLine("Allocation failed.");
            if(p_alloc_error != nullptr)
            {
                LogDebugLine("Alloc error is not null so calling it.");
                p_alloc_error(p_alloc_error_data);
            }
            LogDebugLine("Returing null because of unsuccessful allocation.");
            return nullptr;
        }
        LogDebugLine("Successfully allocated thread at " << (void*)l_returnValue);

        //TODO: Add to the global reference list or smt.

        return l_returnValue;

    }


    Thread* StartRoutineOnThreadWithStackUsingAllocator(
        void* (&p_routine) (void*),
        void* p_data,
        const Stack& m_Stack,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {

        LogDebugLine("Starting a routine on another thread with stack " << m_Stack);

        LogDebugLine("Setting up thread attributes.");
        pthread_attr_t l_attribute;
        if(pthread_attr_init(&l_attribute) != 0)
        {
            LogDebugLine("Attribute initialization failed, returning null.");
            return nullptr;
        }

        if(pthread_attr_setdetachstate(&l_attribute, PTHREAD_CREATE_JOINABLE) != 0)
        {
            LogDebugLine("Could not set thread detach state, returing null.");
            pthread_attr_destroy(&l_attribute);
            return nullptr;
        }

        LogDebugLine("Creating thread.");
        pthread_t l_thread;
        //TODO: Change routine
        if(pthread_create(&l_thread, &l_attribute, p_routine, p_data) != 0)
        {
            LogDebugLine("Could not create thread, returing null.");
            pthread_attr_destroy(&l_attribute);
            return nullptr;
        }

        pthread_attr_destroy(&l_attribute);
        LogDebugLine("Successfully created thread.");

        //TODO: Think of way to block thread until all allocation can be finished.

        LogDebugLine("Allocating thread handle.");
        Thread* l_returnValue = AllocateThreadUsingAllocator(
            p_allocate, p_alloc_error, p_alloc_error_data
        );
        if(l_returnValue == nullptr)
        {
            LogDebugLine("Allocation of thread handle failed, returing null.");
            return nullptr;
        }

        l_returnValue->m_Finished = false;
        l_returnValue->m_ReturnValue = nullptr;
        l_returnValue->m_ThreadID = l_thread;

        return l_returnValue;

    }

    
    Thread* GetThisThreadUsingAllocator(
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*),
        void* p_alloc_erro_data
    );


    bool WaitForThreadToFinish(const Thread& p_thread);
    bool ThreadIsFinished(const Thread& p_thread)
    {

        return p_thread.m_Finished;

    }

    void* GetThreadRoutineReturnValue(const Thread& p_thread)
    {

        LogDebugLine("Getting the return value of thread " << p_thread);

        if(p_thread.m_Finished)
        {
            LogDebugLine("The thread has finished, returning what is in m_ReturnValue.");
            return &p_thread.m_ReturnValue;
        }
        else
        {
            LogDebugLine("The thread has not finished. returning null");
            return nullptr;
        }

    }


    void DestroyThreadUsingDeallocator(Thread& p_thread, void (&p_deallocate) (void*));


    void ExitFromThisThread(void* p_return_value);

    void YieldFromThisThread()
    {
        pthread_yield();
    }


}
