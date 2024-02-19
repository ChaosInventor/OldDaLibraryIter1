#ifndef LIST__DATA_STRUCTURES_LISTS_SINGLY_LINKED_LINEAR_COUNTED_LIST_HPP
#define LIST__DATA_STRUCTURES_LISTS_SINGLY_LINKED_LINEAR_COUNTED_LIST_HPP

#include "../../Node.hpp"
#include "../Uncounted/List.hpp"
#include "../../../../../Meta/Meta.hpp"

namespace Library::DataStructures::Lists::SinglyLinked::Linear::Counted
{

    template<typename T>
    struct List
    {
        Node<T>* m_FirstNode;
        Node<T>* m_LastNode;
        Size m_Size;
    };
    

    template<typename T>
    void CreateListAtOfSizeUsingAllocator(
        List<T>& outp_list,
        const Size& p_size,
        Allocator p_allocate, Callback p_alloc_error, void* p_alloc_error_data
    )
    {
        outp_list.m_Size =
            CreateNodeChainOfSizeFirstNodePointerAtLastNodePointerAt<T>(
                p_size
                outp_list.m_FirstNode, outp_list.m_LastNode,
            );
    }
    template<typename T>
    void CreateCopyAtOfListUsingAllocator(
        List<T>& outp_list,
        const List<T>& p_list,
        Allocator p_allocate, Callback p_alloc_error, void* p_alloc_error_data
    )
    {
        //TODO: Use the new function in Node.hpp here.
    }


    //TODO: Should this have a index check or nha?
    template<typename T>
    Node<T>* FindNodeAtIndexNoErrorCheckFromList(
        const Size& p_index,
        const List<T>& p_list
    )
    {
        return FindNodeNumberOfLinksAfterNode<T>(p_index, *p_list.m_FirstNode);
    }

    template<typename T>
    inline bool ListIsNull(const List<T>& p_list)
    {
        return p_list.m_FirstNode == nullptr;
    }


    template<typename T>
    void DestroyListUsingDeallocator(List<T>& p_list, Deallocator p_deallocate)
    {
        DestroyNodeChainWithFirstNodeAtAndLastNodeAtUsingDeallocator<T>(
            p_list.m_FirstNode, p_list.m_LastNode,
            p_deallocate
        );

        p_list = List<T>();
    }
    


    template<typename T>
    inline void CreateListAtOfSize(
        List<T>& outp_list,
        const Size& p_size
    )
    {
        CreateListAtOfSizeUsingAllocator(
            outp_list,
            p_size,
            g_DEFAULT_ALLOCATOR, g_DEFAULT_ALLOC_ERROR, g_DEFAULT_ALLOC_ERROR_DATA
        );
    }
    template<typename T>
    inline void CreateCopyAtOfList(
        List<T>& outp_list,
        const List<T>& p_list
    )
    {
        CreateCopyAtOfListUsingAllocator(
            outp_list,
            p_list,
            g_DEFAULT_ALLOCATOR, g_DEFAULT_ALLOC_ERROR, g_DEFAULT_ALLOC_ERROR_DATA
        );
    }


    template<typename T>
    void DestroyList(List<T>& p_list)
    {
        DestroyListUsingDeallocator(p_list, g_DEFAULT_DEALLOCATOR);
    }

}

#endif //LIST__DATA_STRUCTURES_LISTS_SINGLY_LINKED_LINEAR_COUNTED_LIST_HPP