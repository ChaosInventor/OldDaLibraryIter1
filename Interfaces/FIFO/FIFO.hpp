#ifndef FIFO__INTERFACES_FIFO_FIFO_HPP
#define FIFO__INTERFACES_FIFO_FIFO_HPP

#include "../../Meta/Meta.hpp"

namespace Library::Interfaces::FIFO
{

    template<typename T>
    struct FIFO
    {
        
        Size (*m_ExtractItemsFromThing) (
            T* p_items, const Size& p_items_size,
            void* p_thing
        );
        Size (*m_InstertItemsToThing) (
            const T* p_items, const Size& p_items_size,
            void* p_thing
        );

        Size (*m_GetCapacityOfThing) (void* p_thing);

        Size (*m_ResizeThingToCapacityUsingReallocator) (
            void* p_thing,
            const Size& p_capacity,
            Reallocator p_reallocate,
            Callback p_realloc_error, void* p_realloc_error_data
        );

        bool (*m_ThingIsFull) (void* p_thing);
        bool (*m_ThingIsEmpty) (void* p_thing);

    };
    

}

#endif FIFO__INTERFACES_FIFO_FIFO_HPP