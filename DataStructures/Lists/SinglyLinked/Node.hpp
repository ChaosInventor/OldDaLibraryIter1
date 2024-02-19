#ifndef SINGLY_LINKED_NODE__DATA_STRUCTURES_LISTS_SINGLY_LINKED_NODE_HPP
#define SINGLY_LINKED_NODE__DATA_STRUCTURES_LISTS_SINGLY_LINKED_NODE_HPP

#include "../../../Meta/Meta.hpp"
#include "../../../Debugging/Logging/Log.hpp"

namespace Library::DataStructures::Lists::SinglyLinked
{

    #ifdef DEBUG
    template<typename T>
    struct Node;
    template<typename T>
    const Debugging::Log& operator<<(const Debugging::Log& p_log, const Node<T>& p_node);
    #endif //DEBUG



    template<typename T>
    struct Node
    {

        Node<T>* m_NextNode;
        T m_Item;

        Node():
        m_NextNode(nullptr),
        m_Item()
        {
            LogDebugLine("Constructed default singly linked list node at "
            << (void*)this);
        }
        Node(const T& p_item):
        m_NextNode(nullptr),
        m_Item(p_item)
        {
            LogDebugLine("Constructed singly linked list node at "
            << (void*)this << " by copying item from address " << (void*)&p_item);
        }
        Node(Node<T>* const p_next):
        m_NextNode(p_next),
        m_Item()
        {
            LogDebugLine("Constructed singly linked list node at "
            << (void*)this << " with next node at " << (void*)p_next
            << " and a default item.");
        }
        Node(Node<T>* const p_next, const T& p_item):
        m_NextNode(p_next),
        m_Item(p_item)
        {
            LogDebugLine("Constructed singly linked list node at "
            << (void*)this << " with next node at " << (void*)p_next
            << " by copying item from address " << (void*)&p_item);
        }

        Node(const Node<T>& p_other):
        m_NextNode(p_other.m_NextNode),
        m_Item(p_other.m_Item)
        {
            LogDebugLine("Copy constructed singly linked list node from address "
            << (void*)&p_other << " to address " << (void*)this);
        }
        Node(Node<T>&& p_other):
        m_NextNode(p_other.m_NextNode),
        m_Item(p_other.m_Item)
        {

            LogDebugLine("Move constructed singly linked list node from address "
            << (void*)&p_other << " to address " << (void*)this);
        
            p_other.m_NextNode = nullptr;
            p_other.m_Item = T();        

        }
        

        Node<T>& operator=(const Node<T>& p_other)
        {

            LogDebugLine("Copying singly linked list node from " << p_other
            << " to " << *this);

            m_NextNode = p_other.m_NextNode;
            m_Item = p_other.m_Item;

            return *this;
        
        }
        Node<T>& operator=(Node<T>&& p_other)
        {

            LogDebugLine("Moving singly linked list node from " << p_other
            << " to " << *this);

            m_NextNode = p_other.m_NextNode;
            m_Item = p_other.m_Item;

            p_other.m_NextNode = nullptr;
            p_other.m_Item = T();

            return *this;
        
        }

        operator T&()
        {
            return m_Item;
        }
        operator Node<T>*&()
        {
            return m_NextNode;
        }

        operator const T&() const
        {
            return m_Item;
        }
        operator const Node<T>* const&() const
        {
            return m_NextNode;
        }

        bool operator==(const Node<T>& p_other) const
        {
            LogDebugLine("Comparing singly linked list node " << *this
            << " and " << p_other);
            return m_NextNode == p_other.m_NextNode && m_Item == p_other.m_Item;
        }
        bool operator!=(const Node<T>& p_other) const
        {
            LogDebugLine("Returing opposite of comparison.");
            return !(*this == p_other);
        }

    };


    template<typename T>
    Size CreateNodeChainOfSizeFirstNodePointerAtLastNodePointerAtUsingAllocator(
        const Size& p_size,
        Node<T>*& outp_first_node,
        Node<T>*& outp_last_node,
        Allocator p_allocate, Callback p_alloc_error, void* p_alloc_error_data
    )
    {
        
        LogDebugLine("Creating singly linked node chain of size " << p_size
        << ", writing the first node pointer at " << (void*)&outp_first_node
        << " and writing the last node pointer at " << (void*)&outp_last_node);

        if(p_size == 0)
        {
            LogDebugLine("The given size is 0, setting both node pointers to "
            "null and returning 0.");
            outp_first_node = nullptr;
            outp_last_node = nullptr;
            return 0;
        }

        LogDebugLine("Allocating node 0");
        //This inital allocation bootstraps the entire loop.
        Node<T>* l_temp = (Node<T>*)p_allocate(sizeof(Node<T>));
        outp_first_node = l_temp;
        outp_last_node = l_temp;
        
        if(l_temp == nullptr)
        {
            LogDebugLine("Allocation failure!");
            if(p_alloc_error != nullptr)
            {
                LogDebugLine("p_alloc_error is not null so calling it.");
                p_alloc_error(p_alloc_error_data);
            }
            LogDebugLine("Returing 0 after failed allocation.");
            return 0;
        }
        LogDebugLine("Successfully allocated node 0 at address" << (void*)l_temp);

        for(Size l_allocatedNodes = 1; l_allocatedNodes < p_size; ++l_allocatedNodes)
        {        
            //outp_last_node here points to the last allocated node, while
            //l_temp is the newly allocated node.
            outp_last_node->m_NextNode = l_temp;
            outp_last_node = l_temp;

            LogDebugLine("Allocating node " << l_allocatedNodes);

            l_temp = (Node<T>*)p_allocate(sizeof(Node<T>));
            if(l_temp == nullptr)
            {
                LogDebugLine("Allocation failure!");
                if(p_alloc_error != nullptr)
                {
                    LogDebugLine("p_alloc_error is not null so calling it.");
                    p_alloc_error(p_alloc_error_data);
                }
                LogDebugLine("Returing the numbere of allocated nodes after "
                "failed allocation.");
                return l_allocatedNodes;
            }
            
            LogDebugLine("Successfully allocated node " << l_allocatedNodes
            << " at address " << (void*)l_temp);

        }

        //This is in order to setup the very last node.
        outp_last_node->m_NextNode = l_temp;
        outp_last_node = l_temp;

        LogDebugLine("Successfully allocated all nodes, returning the size.");
        return p_size;

    }


    template<typename T>
    const Node<T>* FindNodeNumberOfLinksAfterNode(
        const Size& p_number_of_links,
        const Node<T>& p_node
    )
    {

        LogDebugLine("Finding singly linked list node " << p_number_of_links
        << " links after node " << p_node);

        const Node<T>* l_returnValue = &p_node;
        for(size_t i = 0; i < p_number_of_links; ++i)
        {
            LogDebugLine("Link " << i);
            l_returnValue = l_returnValue->m_NextNode;
        }

        LogDebugLine("Found the node at address " << l_returnValue);
        return l_returnValue;

    }
    template<typename T>
    Node<T>* FindNodeNumberOfLinksAfterNode(
        const Size& p_number_of_links,
        Node<T>& p_node
    )
    {
        return (Node<T>*)FindNodeNumberOfLinksAfterNode(p_number_of_links, (const Node<T>&)p_node);
    }


    template<typename T>
    void InsertNodeAfterNode(Node<T>& p_new_node, Node<T>& p_node)
    {

        LogDebugLine("Insterting singly linked node " << p_new_node
        << " after node " << p_node);

        p_new_node.m_NextNode = p_node.m_NextNode;
        p_node.m_NextNode = &p_new_node;

    }    
    
    template<typename T>
    Node<T>* AddItemAfterNodeUsingAllocator(
        const T& p_item, Node<T>& p_node,
        Allocator p_allocate, Callback p_alloc_error, void* p_alloc_error_data
    )
    {

        LogDebugLine("Insterting item at " << (void*)&p_item
        << " after singly linked node " << p_node);

        Node<T>* l_newNode = (Node<T>*)p_allocate(sizeof(Node<T>));
        if(l_newNode == nullptr)
        {
            LogDebugLine("Allocation failure!");
            if(p_alloc_error != nullptr)
            {
                LogDebugLine("p_alloc_error is not null so calling it.");
                p_alloc_error(p_alloc_error_data);
            }
            LogDebugLine("Returning from unsuccessful allocation.");
            return l_newNode;
        }
        
        LogDebugLine("Successfully allocated a new singly linked node at "
        << (void*)l_newNode);

        LogDebugLine("Copying item to the new node.");
        l_newNode->m_Item = p_item;
    
        InsertNodeAfterNode(*l_newNode, p_node);

        return l_newNode;

    }

    template<typename T>
    Node<T>* ExtractNodeAfterNode(Node<T>& p_node)
    {

        LogDebugLine("Extracting singly linked node after node " << p_node);
    
        Node<T>* l_returnValue = p_node.m_NextNode;
        p_node.m_NextNode = l_returnValue->m_NextNode;
        
        return l_returnValue;

    }
    
    template<typename T>
    void RemoveNodeAfterNodeUsingDeallocator(
        Node<T>& p_node,
        Deallocator p_deallocate
    )
    {
        p_deallocate(ExtractNodeAfterNode(p_node));
    }


    template<typename T>
    void DestroyNodeChainWithFirstNodeAtAndLastNodeAtUsingDeallocator(
        Node<T>& p_first_node, Node<T>& p_last_node,
        Deallocator p_deallocate
    )
    {

        LogDebugLine("Destroying singly linked node chain with first node "
        << p_first_node << " and last node " << p_last_node);

        Node<T>* l_curNode = &p_first_node;
        Node<T>* l_nextNode = p_first_node.m_NextNode;
        while(l_curNode != &p_last_node)
        {
            LogDebugLine("Deallocating node at " << (void*)l_curNode);
            p_deallocate(l_curNode);
            l_curNode = l_nextNode;
            l_nextNode = l_nextNode->m_NextNode;
        }

        LogDebugLine("Deallocating node at " << (void*)l_curNode);
        p_deallocate(l_curNode);

        LogDebugLine("Deallocated entire node chain, returning");

    }



    template<typename T>
    inline Size CreateNodeChainOfSizeFirstNodePointerAtLastNodePointerAt(
        const Size& p_size,
        Node<T>*& outp_first_node,
        Node<T>*& outp_last_node
    )
    {
        LogDebugLine("Using defaults for CreateNodeChainOfSizeFirstNodePointerAtLastNodePointerAtUsingAllocator.");
        return CreateNodeChainOfSizeFirstNodePointerAtLastNodePointerAtUsingAllocator(
            p_size,
            outp_first_node, outp_last_node,
            g_DEFAULT_ALLOCATOR,
            g_DEFAULT_REALLOC_ERROR, g_DEFAULT_REALLOC_ERROR_DATA
        );
    }


    template<typename T>
    inline Node<T>* AddItemAfterNode(const T& p_item, Node<T>& p_node)
    {
        LogDebugLine("Using defaults for AddItemAfterNodeUsingAllocator");
        return AddItemAfterNodeUsingAllocator(
            p_item, p_node,
            g_DEFAULT_ALLOCATOR,
            g_DEFAULT_REALLOC_ERROR, g_DEFAULT_REALLOC_ERROR_DATA
        );
    }

    template<typename T>
    inline void RemoveNodeAfterNode(Node<T>& p_node)
    {
        LogDebugLine("Using defaults for RemoveNodeAfterNodeUsingDeallocator");
        RemoveNodeAfterNodeUsingDeallocator(p_node, g_DEFAULT_DEALLOCATOR);
    }


    template<typename T>
    inline void DestroyNodeChainWithFirstNodeAtAndLastNodeAt(
        Node<T>& p_first_node, Node<T>& p_last_node
    )
    {
        LogDebugLine("Using defaults for DestroyNodeChainWithFirstNodeAtAndLastNodeAtUsingDeallocator");
        DestroyNodeChainWithFirstNodeAtAndLastNodeAtUsingDeallocator(
            p_first_node, p_last_node, g_DEFAULT_DEALLOCATOR
        );
    }



    #ifdef DEBUG
    template<typename T>
    const Debugging::Log& operator<<(const Debugging::Log& p_log, const Node<T>& p_node)
    {

        p_log << (void*)&p_node;
        p_log << " { ";
        p_log << " m_NextNode = " << p_node.m_NextNode;
        p_log << ", m_Item = " << p_node.m_Item;
        p_log << " }";

        return p_log;
    
    }
    #endif //DEBUG

}

#endif //SINGLY_LINKED_NODE__DATA_STRUCTURES_LISTS_SINGLY_LINKED_NODE_HPP