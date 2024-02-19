#ifndef LIST__DATA_STRUCTURES_LISTS_SINGLY_LINKED_LINEAR_UNCOUNTED_LIST_HPP
#define LIST__DATA_STRUCTURES_LISTS_SINGLY_LINKED_LINEAR_UNCOUNTED_LIST_HPP

#include "../../Node.hpp"
#include "../../../../../Meta/Meta.hpp"

namespace Library::DataStructures::Lists::SinglyLinked::Linear::Uncounted
{

    #ifdef DEBUG
    template<typename T>
    struct List;
    template<typename T>
    const Debugging::Log& operator<<(const Debugging::Log& p_log, const List<T>& p_list);
    #endif //DEBUG

    template<typename T>
    struct List
    {

        Node<T>* m_FirstNode;
        Node<T>* m_LastNode;
    
        List():
        m_FirstNode(nullptr),
        m_LastNode(nullptr)
        {
            LogDebugLine("Constructed default singly linked uncounted linear "
            "list at " << (void*)this);
        }
        List(const List<T>& p_other):
        m_FirstNode(p_other.m_FirstNode),
        m_LastNode(p_other.m_LastNode)
        {
            LogDebugLine("Constructed singly linked uncounted linear list at "
            << (void*)this << " by copying from list " << p_other);
        }
        List(List<T>&& p_other):
        m_FirstNode(p_other.m_FirstNode),
        m_LastNode(p_other.m_LastNode)
        {

            p_other.m_FirstNode = nullptr;
            p_other.m_LastNode = nullptr;

            LogDebugLine("Constructed singly linked uncounted linear list at "
            << (void*)this << " by moving from list " << p_other);
        
        }

        List(Node<T>* p_first_node, Node<T>* p_last_node):
        m_FirstNode(p_first_node),
        m_LastNode(p_last_node)
        {
            LogDebugLine("Constructed singly linked uncounted linear list at "
            << (void*)this << " with first node at " << (void*)p_first_node
            << " and last node at " << (void*)p_last_node);
        }

        List& operator=(const List<T>& p_other)
        {

            LogDebugLine("Copying from singly linked uncounted linear list "
            << p_other << " to list " << *this);

            m_FirstNode = p_other.m_FirstNode;
            m_LastNode = p_other.m_LastNode;

            return *this;

        }
        List& operator=(List<T>&& p_other)
        {

            LogDebugLine("Moving from singly linked uncounted linear list "
            << p_other << " to list " << *this);

            m_FirstNode = p_other.m_FirstNode;
            m_LastNode = p_other.m_LastNode;

            p_other.m_FirstNode = nullptr;
            p_other.m_LastNode = nullptr;

            return *this;

        }

        bool operator==(const List<T>& p_other)
        {
            LogDebugLine("Checking if singly linked uncounted linear list "
            << *this << " is the same as " << p_other);
            return m_FirstNode == p_other.m_FirstNode && m_LastNode == p_other.m_LastNode;
        }
        bool operator!=(const List<T>& p_other)
        {
            LogDebugLine("Returning the opposite of the comparison.");
            return !(*this == p_other);
        }

        Node<T>* operator[](const Size& p_index)
        {
            return FindNodeAtIndexNoErrorCheckFromList(p_index, *this);
        }

    };
    

    template<typename T>
    void CreateListAtOfSizeUsingAllocator(
        List<T>& outp_list,
        const Size& p_size,
        Allocator p_allocate, Callback p_alloc_error, void* p_alloc_error_data
    )
    {
        LogDebugLine("Creating singly linked uncounted list at " << outp_list
        << " of size " << p_size);
        CreateNodeChainOfSizeFirstNodePointerAtLastNodePointerAtUsingAllocator(
            p_size,
            outp_list.m_FirstNode, outp_list.m_LastNode,
            p_allocate, p_alloc_error, p_alloc_error_data
        );

        if(outp_list.m_LastNode != nullptr)
        {
            outp_list.m_LastNode->m_NextNode = nullptr;
        }

    }
    template<typename T>
    void CreateCopyAtOfListUsingAllocator(
        List<T>& outp_list,
        const List<T>& p_list,
        Allocator p_allocate, Callback p_alloc_error, void* p_alloc_error_data
    )
    {

        LogDebugLine("Creating a copy of singly linked linear uncounted list "
        << p_list << " at " << outp_list);

        //TODO: This should be a function is Node.hpp, not here

        if(ListIsNull(p_list))
        {
            LogDebugLine("The other list is null so creating a null list and returning.");

            outp_list.m_FirstNode = nullptr;
            outp_list.m_LastNode = nullptr;
            
            return;
        }

        LogDebugLine("Allocating the first node.");
        Node<T>* l_newNode = (Node<T>*)p_allocate(sizeof(Node<T>));
        if(l_newNode == nullptr)
        {
            LogDebugLine("Failed to allocate first node, creating a null list");

            outp_list.m_FirstNode = nullptr;
            outp_list.m_LastNode = nullptr;

            if(p_alloc_error != nullptr)
            {
                LogDebugLine("Alloc error is not null so calling it.");
                p_alloc_error(p_alloc_error_data);
            }
            LogDebugLine("Returing from unsuccessful allocation.");
            return;
        }
        LogDebugLine("Successfully allocated the first node at " << (void*)l_newNode);

        LogDebugLine("Setting up the output list with 1 node...");
        outp_list.m_FirstNode = l_newNode;
        outp_list.m_LastNode = l_newNode;

        outp_list.m_FirstNode->m_Item = p_list.m_FirstNode->m_Item;
        
        outp_list.m_LastNode->m_NextNode = nullptr;

        Node<T>* l_curNode = p_list.m_FirstNode->m_NextNode;
        while(l_curNode != nullptr)
        {
            LogDebugLine("Allocating node.");
            l_newNode = (Node<T>*)p_allocate(sizeof(Node<T>));
            if(l_newNode == nullptr)
            {
                LogDebugLine("Failed to allocate node.");
                if(p_alloc_error != nullptr)
                {
                    LogDebugLine("Alloc error is not null so calling it.");
                    p_alloc_error(p_alloc_error_data);
                }
                LogDebugLine("Returing from unsuccessful allocation.");
                return;
            }
            LogDebugLine("Successfully allocated a node at " << (void*)l_newNode);

            l_newNode->m_Item = l_curNode->m_Item;

            InsertNodeAfterNode(*l_newNode, *outp_list.m_LastNode);
            outp_list.m_LastNode = l_newNode;
            
            l_curNode = l_curNode->m_NextNode;

        }

        LogDebugLine("Successfully copied the entire list.");

    }


    template<typename T>
    Node<T>* FindNodeAtIndexNoErrorCheckFromList(
        const Size& p_index,
        const List<T>& p_list
    )
    {
        LogDebugLine("Finding the singly linked list node at index " << p_index
        << " from uncounted linear list " << p_list);
        return FindNodeNumberOfLinksAfterNode<T>(p_index, *p_list.m_FirstNode);
    }
    template<typename T>
    Size FindNumberOfNodesInList(const List<T>& p_list)
    {

        Size l_numberOfNodes = 0;
        Node<T>* l_curNode = p_list.m_FirstNode;
        while(l_curNode != nullptr)
        {
            ++l_numberOfNodes;
            l_curNode = l_curNode->m_NextNode;
        }

        return l_numberOfNodes;

    }

    template<typename T>
    inline bool ListIsNull(const List<T>& p_list)
    {
        return p_list.m_FirstNode == nullptr;
    }


    //TODO: This should operator on multiple nodes instead of just 1
    template<typename T>
    void InsertNodeToStartOfList(Node<T>& p_node, List<T>& p_list)
    {

        LogDebugLine("Inserting singly linked list node " << p_node << " at the "
        "start of uncounted linear list " << p_list);

        p_node.m_NextNode = p_list.m_FirstNode;
        p_list.m_FirstNode = &p_node;

        if(p_list.m_LastNode == nullptr)
        {
            LogDebugLine("List doesn't have a last node so setting it to the "
            "new node.");
            p_list.m_LastNode = &p_node;
        }

    }
    template<typename T>
    void InsertNodeToEndOfList(Node<T>& p_node, List<T>& p_list)
    {

        LogDebugLine("Inserting singly linked list node " << p_node << " at the "
        "end of uncounted linear list " << p_list);

        if(ListIsNull(p_list))
        {
            LogDebugLine("The list doesn't have any nodes so making the new "
            "node the only node.");
            p_list.m_FirstNode = &p_node;
            p_list.m_LastNode = &p_node;
            p_node.m_NextNode = nullptr;
        }
        else
        {
            InsertNodeAfterNode(p_node, *p_list.m_LastNode);

            p_list.m_LastNode = &p_node;
        }
        
    }
    template<typename T>
    void InsertNodeAfterIndexNoErrorCheckOfList(
        Node<T>& p_node,
        const Size& p_index,
        List<T>& p_list
    )
    {

        LogDebugLine("Inserting singly linked list node " << p_node
        << " after index " << p_index << " to uncounted linear list "
        << p_list);

        Node<T>* l_nodeAtIndex = FindNodeNumberOfLinksAfterNode(p_index, *p_list.m_FirstNode);
        InsertNodeAfterNode(p_node, *l_nodeAtIndex);

        //Edge case of the last index being used for this function.
        if(l_nodeAtIndex == p_list.m_LastNode)
        {
            LogDebugLine("The last index was being used, so the last node must "
            "be updated.");
            p_list.m_LastNode = &p_node;
        }

    }

    //TODO: Again multiple items instead of just 1
    template<typename T>
    void AddItemToStartOfListUsingAllocator(
        const T& p_item,
        List<T>& p_list,
        Allocator p_allocate, Callback p_alloc_error, void* p_alloc_error_data
    )
    {

        LogDebugLine("Adding item at " << (void*)&p_item << " to start of "
        "singly linked uncounted linear list" << p_list);

        LogDebugLine("Allocating a node...");
     
        Node<T>* l_newNode = (Node<T>*)p_allocate(sizeof(Node<T>));
        if(l_newNode == nullptr)
        {
            LogDebugLine("Allocation failed!");
            if(p_alloc_error != nullptr)
            {
                LogDebugLine("Alloc error is not null so calling it.");
                p_alloc_error(p_alloc_error_data);
            }
            LogDebugLine("Returning from unsuccessful allocation.");
            return;
        }
     
        LogDebugLine("Successfully allocated a new node at " << (void*)l_newNode);

        LogDebugLine("Copying item to new node.");
        l_newNode->m_Item = p_item;
        InsertNodeToStartOfList(*l_newNode, p_list);

    }
    template<typename T>
    void AddItemToEndOfListUsingAllocator(
        const T& p_item,
        List<T>& p_list,
        Allocator p_allocate, Callback p_alloc_error, void* p_alloc_error_data
    )
    {

        LogDebugLine("Adding item at " << (void*)&p_item << " to end of "
        "singly linked uncounted linear list" << p_list);

        LogDebugLine("Allocating a node...");
     
        Node<T>* l_newNode = (Node<T>*)p_allocate(sizeof(Node<T>));
        if(l_newNode == nullptr)
        {
            LogDebugLine("Allocation failed!");
            if(p_alloc_error != nullptr)
            {
                LogDebugLine("Alloc error is not null so calling it.");
                p_alloc_error(p_alloc_error_data);
            }
            LogDebugLine("Returning from unsuccessful allocation.");
            return;
        }
     
        LogDebugLine("Successfully allocated a new node at " << (void*)l_newNode);

        LogDebugLine("Copying item to new node.");
        l_newNode->m_Item = p_item;
        InsertNodeToEndOfList(*l_newNode, p_list);

    }
    template<typename T>
    void AddItemAfterIndexNoErrorCheckOfListUsingAllocator(
        const T& p_item,
        const Size& p_index,
        List<T>& p_list,
        Allocator p_allocate, Callback p_alloc_error, void* p_alloc_error_data
    )
    {

        LogDebugLine("Adding item at " << (void*)&p_item << " after index "
        << p_index << " in singly linked uncounted linear list" << p_list);

        LogDebugLine("Allocating a node...");
     
        Node<T>* l_newNode = (Node<T>*)p_allocate(sizeof(Node<T>));
        if(l_newNode == nullptr)
        {
            LogDebugLine("Allocation failed!");
            if(p_alloc_error != nullptr)
            {
                LogDebugLine("Alloc error is not null so calling it.");
                p_alloc_error(p_alloc_error_data);
            }
            LogDebugLine("Returning from unsuccessful allocation.");
            return;
        }
     
        LogDebugLine("Successfully allocated a new node at " << (void*)l_newNode);

        LogDebugLine("Copying item to new node.");
        l_newNode->m_Item = p_item;
        InsertNodeAfterIndexNoErrorCheckOfList(*l_newNode, p_index, p_list);

    }

    //TODO: Change to work with extracting multiple nodes.
    template<typename T>
    Node<T>* ExtractNodeFromStartOfList(List<T>& p_list)
    {

        LogDebugLine("Extracting the first singly linked list node from "
        "uncounted linear list " << p_list);

        Node<T>* l_returnValue = p_list.m_FirstNode;
        if(l_returnValue != nullptr)
        {
            p_list.m_FirstNode = p_list.m_FirstNode->m_NextNode;
            if(p_list.m_FirstNode == nullptr)
            {
                LogDebugLine("Extracted the last node, creating null list.");
                p_list.m_LastNode = p_list.m_FirstNode;
            }
        }

        LogDebugLine("Returning " << (void*)l_returnValue);
        return l_returnValue;

    }
    template<typename T>
    Node<T>* ExtractNodeFromEndOfList(List<T>& p_list)
    {

        LogDebugLine("Extracting the last singly linked list node from "
        "uncounted linear list " << p_list);

        Node<T>* l_beforeLastNode = p_list.m_FirstNode;
        if(l_beforeLastNode == nullptr)
        {
            LogDebugLine("List doesn't have any nodes, returing null.");
            return nullptr;
        }
        if(l_beforeLastNode->m_NextNode == nullptr)
        {
            LogDebugLine("The list only has one node, returning it and making a null list.");
            p_list.m_FirstNode = nullptr;
            p_list.m_LastNode = nullptr;
            return l_beforeLastNode;
        }

        LogDebugLine("Finding the node before the last node.");
        while(l_beforeLastNode->m_NextNode != p_list.m_LastNode)
        {
            l_beforeLastNode = l_beforeLastNode->m_NextNode;
        }
        LogDebugLine("Found it, it is at " << (void*)l_beforeLastNode);

        Node<T>* l_returnValue = ExtractNodeAfterNode(*l_beforeLastNode);
        p_list.m_LastNode = l_beforeLastNode;
        
        LogDebugLine("Returning " << (void*)l_returnValue);
        return l_returnValue;

    }
    template<typename T>
    Node<T>* ExtractNodeFromIndexNoErrorCheckOfList(
        const Size& p_index,    
        List<T>& p_list
    )
    {

        LogDebugLine("Extracting the node at index " << p_index << " in singly "
        "linked uncounted linear list " << p_list);

        if(ListIsNull(p_list))
        {
            LogDebugLine("List doesn't have any nodes, returning null.");
            return nullptr;
        }
        if(p_index == 0)
        {
            return ExtractNodeFromStartOfList(p_list);
        }

        Node<T>* l_nodeBeforeIndex = FindNodeNumberOfLinksAfterNode(
            p_index - 1, //Can't overflow, only overflows when p_index is 0,
                         //p_index will never be 0 because of the above if.
            *p_list.m_FirstNode
        );

        Node<T>* l_returnValue = ExtractNodeAfterNode(*l_nodeBeforeIndex);
        if(l_returnValue == p_list.m_LastNode)
        {
            LogDebugLine("Last index is being removed so updating the last "
            "node pointer.");
            p_list.m_LastNode = l_nodeBeforeIndex;
        }

        LogDebugLine("Returning " << (void*)l_returnValue);
        return l_returnValue;

    }

    //TODO: Change to work with removing multiple nodes.
    template<typename T>
    void RemoveNodeFromStartOfListUsingDeallocator(
        List<T>& p_list,
        Deallocator p_deallocate
    )
    {
        LogDebugLine("Removing the first singly linked list node of the "
        "uncounted linear list " << p_list);
        p_deallocate(ExtractNodeFromStartOfList(p_list));
    }
    template<typename T>
    void RemoveNodeFromEndOfListUsingDeallocator(
        List<T>& p_list,
        Deallocator p_deallocate
    )
    {
        LogDebugLine("Removing the last singly linked list node of the "
        "uncounted linear list " << p_list);     
        p_deallocate(ExtractNodeFromEndOfList(p_list));
    }
    template<typename T>
    void RemoveNodeFromIndexNoErrorCheckOfListUsingDeallocator(
        const Size& p_index,
        List<T>& p_list,
        Deallocator p_deallocate
    )
    {
        LogDebugLine("Removing the singly linked list node at index "
        << p_index << " from the uncounted linear list " << p_list);
        p_deallocate(ExtractNodeFromIndexNoErrorCheckOfList(p_index, p_list));
    }


    template<typename T>
    void DestroyListUsingDeallocator(
        List<T>& p_list,
        Deallocator p_deallocate
    )
    {
        LogDebugLine("Destroying singly linked uncounted linear list " << p_list);
        
        if(ListIsNull(p_list))
        {
            LogDebugLine("The list doesn't have any nodes, returning.");
            return;
        }
        
        DestroyNodeChainWithFirstNodeAtAndLastNodeAtUsingDeallocator(
            *p_list.m_FirstNode, *p_list.m_LastNode,
            p_deallocate
        );
        
        LogDebugLine("Creating null list.");
        p_list.m_FirstNode = nullptr;
        p_list.m_LastNode = nullptr;
    
    }



    template<typename T>
    inline void CreateListAtOfSize(
        List<T>& outp_list,
        const Size& p_size
    )
    {
        LogDebugLine("Using defaults for CreateListAtOfSizeUsingAllocator.");
        CreateListAtOfSizeUsingAllocator(
            outp_list,
            p_size,
            g_DEFAULT_ALLOCATOR, g_DEFAULT_ALLOC_ERROR, g_DEFAULT_ALLOC_ERROR_DATA
        );
    }
    template<typename T>
    inline void CreateCopyAtOfList(List<T>& outp_list, const List<T>& p_list)
    {
        LogDebugLine("Using defaults for CreateCopyAtOfListUsingAllocator");
        CreateCopyAtOfListUsingAllocator(
            outp_list,
            p_list,
            g_DEFAULT_ALLOCATOR, g_DEFAULT_ALLOC_ERROR, g_DEFAULT_ALLOC_ERROR_DATA
        );
    }


    template<typename T>
    inline void AddItemToStartOfList(
        const T& p_item,
        List<T>& p_list
    )
    {
        LogDebugLine("Using defaults for AddItemToStartOfListUsingAllocator.");
        AddItemToStartOfListUsingAllocator(
            p_item,
            p_list,
            g_DEFAULT_ALLOCATOR, g_DEFAULT_ALLOC_ERROR, g_DEFAULT_ALLOC_ERROR_DATA
        );
    }
    template<typename T>
    inline void AddItemToEndOfList(
        const T& p_item,
        List<T>& p_list
    )
    {
        LogDebugLine("Using defaults for AddItemToEndOfListUsingAllocator.");
        AddItemToEndOfListUsingAllocator(
            p_item,
            p_list,
            g_DEFAULT_ALLOCATOR, g_DEFAULT_ALLOC_ERROR, g_DEFAULT_ALLOC_ERROR_DATA
        );
    }
    template<typename T>
    inline void AddItemAfterIndexNoErrorCheckOfList(
        const T& p_item,
        const Size& p_index,
        List<T>& p_list
    )
    {
        LogDebugLine("Using defaults for AddItemAfterIndexNoErrorCheckOfListUsingAllocator.");
        AddItemAfterIndexNoErrorCheckOfListUsingAllocator(
            p_item, p_index,
            p_list,
            g_DEFAULT_ALLOCATOR, g_DEFAULT_ALLOC_ERROR, g_DEFAULT_ALLOC_ERROR_DATA
        );
    }

    template<typename T>
    inline void RemoveNodeFromStartOfList(
        List<T>& p_list
    )
    {
        LogDebugLine("Using defaults for RemoveNodeAtStartOfListUsingDeallocator.");
        RemoveNodeFromStartOfListUsingDeallocator(
            p_list, g_DEFAULT_DEALLOCATOR
        );
    }
    template<typename T>
    inline void RemoveNodeFromEndOfList(
        List<T>& p_list
    )
    {
        LogDebugLine("Using defaults for RemoveNodeAtEndOfListUsingDeallocator.");
        RemoveNodeFromEndOfListUsingDeallocator(
            p_list, g_DEFAULT_DEALLOCATOR
        );
    }
    template<typename T>
    inline void RemoveNodeFromIndexNoErrorCheckOfList(
        const Size& p_index,
        List<T>& p_list
    )
    {
        LogDebugLine("Using defaults for RemoveNodeFromIndexNoErrorCheckOfListUsingDeallocator.");
        RemoveNodeFromIndexNoErrorCheckOfListUsingDeallocator(
            p_index, p_list, g_DEFAULT_DEALLOCATOR
        );
    }


    template<typename T>
    inline void DestroyList(List<T>& p_list)
    {
        LogDebugLine("Using defaults for DestroyListUsingDeallocator.");
        DestroyListUsingDeallocator(p_list, g_DEFAULT_DEALLOCATOR);
    }



    #ifdef DEBUG
    template<typename T>
    const Debugging::Log& operator<<(const Debugging::Log& p_log, const List<T>& p_list)
    {

        p_log << (void*)&p_list;
        p_log << " { ";
        p_log << "m_FirstNode = " << (void*)p_list.m_FirstNode << ", ";
        p_log << "m_LastNode = " << (void*)p_list.m_LastNode;
        p_log << " }";

        return p_log;

    }
    #endif //DEBUG

}

#endif //LIST__DATA_STRUCTURES_LISTS_SINGLY_LINKED_LINEAR_UNCOUNTED_LIST_HPP