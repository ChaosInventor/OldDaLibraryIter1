#ifndef INDEXABLE__INTERFACES_INDEXABLE_INDEXABLE_HPP
#define INDEXABLE__INTERFACES_INDEXABLE_INDEXABLE_HPP

#include "../../Meta/Meta.hpp"

//TODO: Better namespace
namespace Library::Interfaces
{
    
    //Number of items are know.
    //Exact location of items and how they are structured is unknow.
    //Any item can be acessed at anytime and anywhere.
    //Items may be added and removed. 2 types arise from this variation, fixed and dynamic.
    template<typename T> //TODO: Is a template a good idea?
    struct Indexable
    {

        void (*m_IDK) (const Size& p_index, T*& outp_location_item, Size& outp_items_before, Size& p_items_after, Indexable& p_indexable);

        Size (*m_GetSizeOfIndexable) (Indexable& p_indexable);

        void* m_State;


        //TODO: Will this even give a performance advantage with the new get item?
        void (*m_SwapIndexWithIndexNoErrorCheckInThing) (
            const Size& p_index1, const Size& p_index2,
            void* p_thing
        );


        void (*m_AddNumberOfItemsToThingBeforeIndexNoErrorCheckUsingReallocator) (
            const Size& p_number_of_items,
            void* p_thing,
            const Size& p_index,
            Reallocator p_reallocate,
            Callback p_realloc_error, void* p_realloc_error_data
        );
        void (*m_RemoveNumberOfItemsFromThingStartingAtIndexNoErrorCheckUsingReallocator) (
            const Size& p_number_of_items,
            void* p_thing,
            const Size& p_index,
            Reallocator p_reallocate,
            Callback p_realloc_error, void* p_realloc_error_data
        );

        //TODO: Will this give a performance advantage with the new get item function?
        void (*m_CreateIteratorAtUsingAllocator) (
            Iterator<T>& outp_iterator,
            Allocator p_allocate,
            Callback p_alloc_error, void* p_alloc_error_data
        );
        void (*m_DestryIteratorUsingDeallocator) (
            Iterator<T>& p_iterator,
            Deallocator p_deallocate
        );

        void* m_Thing;

        //TODO: Operators

    };


    template<typename T>
    Size FindIndexOfFirstOccurrenceOfItemsInIndexable(
        const T* const p_items, const Size& p_items_size,
        const Indexable<T>& p_indexable
    );
    template<typename T>
    Size FindIndexOfLastOccurrenceOfItemsInIndexable(
        const T* const p_items, const Size& p_items_size,
        const Indexable<T>& p_indexable
    );

    template<typename T>
    Size FindNumberOfOccurrenceOfItemsInIndexable(
        const T* const p_items, const Size& p_items_size,
        const Indexable<T>& p_indexable
    );

    template<typename T>
    bool IndexableContainsItems(
        const Indexable<T>& p_indexable,
        const T* const p_items, const Size& p_items_size
    );

    template<typename T>
    bool IndexableStartsWithItems(
        const Indexable<T>& p_indexable,
        const T* const p_items, const Size& p_items_size
    );
    template<typename T>
    bool IndexableEndsWithItems(
        const Indexable<T>& p_indexable,
        const T* const p_items, const Size& p_items_size
    );


    template<typename T>
    void ReverseIndexable(Indexable<T>& p_indexable);

    template<typename T>
    void AppendNumberOfItemsToStartOfIndexableUsingReallocator(
        const Size& p_number_of_items,
        const Indexable<T>& p_indexable,
        Reallocator p_reallocate,
        Callback p_realloc_error, void* p_realloc_error_data
    );
    template<typename T>
    void AppendNumberOfItemsToEndOfIndexableUsingReallocator(
        const Size& p_number_of_items,
        const Indexable<T>& p_indexable,
        Reallocator p_reallocate,
        Callback p_realloc_error, void* p_realloc_error_data
    );

    template<typename T>
    void RemoveNumberOfItemsFromStartOfIndexableUsingReallocator(
        const Size& p_number_of_items,
        const Indexable<T>& p_indexable,
        Reallocator p_reallocate,
        Callback p_realloc_error, void* p_realloc_error_data
    );
    template<typename T>
    void RemoveNumberOfItemsFromEndOfIndexableUsingReallocator(
        const Size& p_number_of_items,
        const Indexable<T>& p_indexable,
        Reallocator p_reallocate,
        Callback p_realloc_error, void* p_realloc_error_data
    );

    //TODO: Each item remove

}

#endif