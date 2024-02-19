#include <pthread.h>

#include "../../../../Debugging/Logging/Log.hpp"

namespace Library::Asynchronous
{

    struct Mutex
    {

        pthread_mutex_t m_Mutex;

        void (*m_OwnerDeathCallback) (void*);
        void* m_OwnerDeathCallbackData;
    
        Mutex():
        m_Mutex(),
        m_OwnerDeathCallback(nullptr),
        m_OwnerDeathCallbackData(nullptr)
        {
            LogDebugLine("Constructed empty mutex at " << (void*)this);
        }

    };

}
