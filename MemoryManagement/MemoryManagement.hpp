#include "../Memory/Memory.hpp"

namespace Library
{

    //TODO: Should memory management functions have special naming rules?

    //m_Location is ignored, m_Size and m_Permissions are used. All of them
    //may be mutated.
    using MemoryAllocator = void (*)(
        Memory& outp_memory,
        void*& p_state,
        Callback p_alloc_error, void* p_alloc_error_data
    );
    using MemoryAllocatorRef = void (&)(
        Memory& outp_memory,
        void*& p_state,
        Callback p_alloc_error, void* p_alloc_error_data
    );

    //TODO: Better name for this.
    using MemoryRepermissionator = void (*)(
        Memory& p_memory,
        const Byte& p_new_permissions,
        void*& p_state,
        Callback p_repermission_error, void* p_repermission_error_data
    );

    using MemoryReallocatorFront = void(*)(
        Memory& p_memory,
        const Size& p_new_size,
        void*& p_state,
        Callback p_realloc_error, void* p_realloc_error_data
    );
    using MemoryReallocatorFrontRef = void(&)(
        Memory& p_memory,
        const Size& p_new_size,
        void*& p_state,
        Callback p_realloc_error, void* p_realloc_error_data
    );

    using MemoryReallocatorBack = void(*)(
        Memory& p_memory,
        const Size& p_new_size,
        void*& p_state,
        Callback p_realloc_error, void* p_realloc_error_data
    );
    using MemoryReallocatorBackRef = void(&)(
        Memory& p_memory,
        const Size& p_new_size,
        void*& p_state,
        Callback p_realloc_error, void* p_realloc_error_data
    );

    using MemoryDeallocator = void (*)(Memory& p_memory, void*& p_state);
    using MemoryDeallocatorRef = void (&)(Memory& p_memory, void*& p_state);

    struct MemoryManagement
    {

        MemoryAllocator m_Allocate;

        MemoryRepermissionator m_Repermissionate;

        MemoryReallocatorFront m_ReallocateFront;
        MemoryReallocatorBack m_ReallocateBack;

        MemoryDeallocator m_Deallocate;

        void* m_State;

    };    

}
