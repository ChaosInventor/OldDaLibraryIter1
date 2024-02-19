#ifndef THREAD__ASYNCHRONOUS_THREAD_THREAD_HPP
#define THREAD__ASYNCHRONOUS_THREAD_THREAD_HPP

#include "../../../LibraryMeta/LibraryMeta.hpp"
#include "../../../Debugging/Logging/Log.hpp"

namespace Library::Asynchronous
{

    #ifdef DEBUG
    struct Stack;
    const Debugging::Log& operator<<(const Debugging::Log& p_log, const Stack& p_stack);
    #endif // DEBUG



    struct Thread;

    /**
     * @brief A structure that holds data about a memory segment that can be
     * used as a stack for a thread.
     * 
     * @details //TODO: Document
     * 
     * Currently this feature is not fully documented.
     * 
     * However here are some basics to using it:
     * - If you want a stack to be automaticaly created for you pass a
     * default stack. A default stack can be constructed by the default
     * constructor, as such: Stack(). The default stack's address and size are
     * platfrom specific and implementation defined.
     * - If you want a stack to be automaticaly created for but with a custom
     * size then set the stack's address to null and the stack's size to the
     * size you want. If this size is lower than the minimum then the stack's
     * size will be the minimum. The minimum stack size is implementation
     * defined and platfrom specific.
     * 
     */
    struct Stack
    {

        /**
         * @brief The address of the stack.
         * 
         */
        void* m_Address;
        /**
         * @brief The size of the stack in bytes.
         * 
         */
        Size m_Size;

        /**
         * @brief Constructs a default stack, use this kind of stack if you do
         * not want to set up a custom one.
         * 
         * @details Sets m_Address to null and m_Size to 0.
         * 
         */
        Stack():
        m_Address(nullptr),
        m_Size(0)
        {
            LogDebugLine("Constructed default stack at " << (void*)this);
        }
        /**
         * @brief Copies each filed from p_other to this.
         * 
         */
        Stack(const Stack& p_other):
        m_Address(p_other.m_Address),
        m_Size(p_other.m_Size)
        {
            LogDebugLine("Constructed stack by copying from " << p_other <<
            " and to " << (void*)this);
        }
        /**
         * @brief Copies each field from p_other to this and then creates a
         * default stack at p_other.
         * 
         */
        Stack(Stack&& p_other):
        m_Address(p_other.m_Address),
        m_Size(p_other.m_Size)
        {
            LogDebugLine("Constructed stack by moving from " << p_other <<
            " and to " << (void*)this);

            p_other.m_Address = nullptr;
            p_other.m_Size = 0;
        }

        /**
         * @brief Sets m_Address to p_address and m_Size to p_size. 
         * 
         */
        Stack(void* p_address, const Size& p_size):
        m_Address(p_address),
        m_Size(p_size)
        {
            LogDebugLine("Constructed stack from address " << p_address <<
            " and size " << p_size);
        }

        /**
         * @brief Same as copy constructor.
         * 
         * @return *this
         * 
         */
        Stack& operator=(const Stack& p_other)
        {

            LogDebugLine("Copying stack from " << p_other << " to " << *this);

            m_Address = p_other.m_Address;
            m_Size = p_other.m_Size;

            return *this;

        }
        /**
         * @brief Same as move constructor.
         * 
         * @return *this.
         * 
         */
        Stack& operator=(Stack&& p_other)
        {

            LogDebugLine("Moving stack from " << p_other << " to " << *this);

            m_Address = p_other.m_Address;
            m_Size = p_other.m_Size;

            p_other.m_Address = nullptr;
            p_other.m_Size = 0;

            return *this;

        }

    };
    

    bool operator==(const Thread& p_left, const Thread& p_right);
    bool operator!=(const Thread& p_left, const Thread& p_right);


    Thread* StartRoutineOnThreadWithStackUsingAllocator(
        void* (&p_routine) (void*),
        void* p_data,
        const Stack& p_stack,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    );
    inline Thread* StartRoutineOnThreadWithStack(
        void* (&p_routine) (void*),
        void* p_data,
        const Stack& p_stack
    )
    {
        LogDebugLine("Using defaults for StartRoutineOnThreadWithStackUsingAllocator.");
        return StartRoutineOnThreadWithStackUsingAllocator(
            p_routine, p_data,
            p_stack,
            Library::LibraryMeta::g_DEFAULT_ALLOCATOR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR_DATA
        );
    }

    Thread* CopyThreadUsingAllocator(
        const Thread& p_thread,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data    
    );
    inline Thread* CopyThread(const Thread& p_thread)
    {
        LogDebugLine("Using defaults for CopyThreadUsingAllocator.");
        return CopyThreadUsingAllocator(
            p_thread,
            Library::LibraryMeta::g_DEFAULT_ALLOCATOR,     
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR_DATA            
        );
    }
   

    Thread* GetThisThreadUsingAllocator(
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*),
        void* p_alloc_erro_data
    );
    inline Thread* GetThisThread()
    {
        LogDebugLine("Using defaults for GetThisThreadUsingAllocator.");
        return GetThisThreadUsingAllocator(
            Library::LibraryMeta::g_DEFAULT_ALLOCATOR,           
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR,                
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR_DATA                    
        );
    }


    bool WaitForThreadToFinish(const Thread& p_thread);
    /**
     * @brief Checks if p_thread has finished execution.
     * 
     * @details A thread is consider to be finished with exectution once its
     * routine has returned or if the thread has made a call to
     * @ref ExitFromThisThread.
     * 
     * @param p_thread The thread to check for.
     * @return True if the thread has successfully finished execution. False
     * in case of an error or if the thread has not finished executing yet.
     * 
     * Also see:
     * @ref GetThreadRoutineReturnValue, @ref WaitForThreadToFinish.
     * 
     */
    bool ThreadIsFinished(const Thread& p_thread);

    void* GetThreadRoutineReturnValue(const Thread& p_thread);


    void DestroyThreadUsingDeallocator(Thread& p_thread, void (&p_deallocate) (void*));
    inline void DestroyThread(Thread& p_thread)
    {
        LogDebugLine("Using defaults for DestroyThreadUsingDeallocator.");
        DestroyThreadUsingDeallocator(
            p_thread, Library::LibraryMeta::g_DEFAULT_DEALLOCATOR
        );
    }


    void ExitFromThisThread(void* p_return_value);

    void YieldFromThisThread();

}


#endif // !THREAD__ASYNCHRONOUS_THREAD_THREAD_HPP