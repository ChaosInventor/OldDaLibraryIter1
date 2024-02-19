/**
 * @file DoublyLinkedListNode.hpp 
 * @brief Contains the namespace Lists::DoublyLinked. The only dependence is
 * LibraryMeta.
 * 
 */

#ifndef DOUBLY_LINKED_LIST_NODE__DATA_STRUCTURES_LISTS_DOUBLY_LINKED_DOUBLY_LINKED_LIST_NODE_HPP
#define DOUBLY_LINKED_LIST_NODE__DATA_STRUCTURES_LISTS_DOUBLY_LINKED_DOUBLY_LINKED_LIST_NODE_HPP

#include "../../../LibraryMeta/LibraryMeta.hpp"

/**
 * @brief Contains the doubly linked version of lists.
 * 
 * @details This specific namespace defines the doubly linked node and some
 * functions that can be used with it.
 * 
 */
namespace Library::DataStructures::Lists::DoublyLinked
{

    /**
     * @brief A structure that can be used to create doubly linked lists.
     * Contains 2 pointers to the same structure and a item of type T.
     * 
     * @tparam T This type must support the following operations:
     * - Being copyable;
     * - Being movable;
     * - Default construction;
     * - Comparison to it's self using the == operator.
     * 
     */
    template<typename T>
    struct Node
    {

        /**
         * @brief The previous node in the chain. May be null.
         * 
         */
        Node<T>* m_PreviousNode;
        /**
         * @brief The next node in the chain. May be null.
         * 
         */
        Node<T>* m_NextNode;
        /**
         * @brief The item this node carries.
         * 
         */
        T m_Item;

        /**
         * @brief Sets m_PreviousNode and m_NextNode to null, m_Item is set to
         * it's default value.
         * 
         */
        Node():
        m_PreviousNode(nullptr),
        m_NextNode(nullptr),
        m_Item()
        {
            LogDebugLine("Constructed default node at " << *this);
        }
        /**
         * @brief Copies all of the fields from p_other to this.
         * 
         */
        Node(const Node<T>& p_other):
        m_PreviousNode(p_other.m_PreviousNode),
        m_NextNode(p_other.m_NextNode),
        m_Item(p_other.m_Item)
        {
            LogDebugLine("Constructed copy of node from " << p_other <<
            " to " << *this);
        }
        /**
         * @brief Copies all of the fields from p_other to this.
         * p_other.m_PreviousNode and p_other.m_NextNode are set to null and
         * p_other.m_Item is set to T().
         * 
         */
        Node(Node<T>&& p_other):
        m_PreviousNode(p_other.m_PreviousNode),
        m_NextNode(p_other.m_NextNode),
        m_Item(p_other.m_Item)
        {
            LogDebugLine("Moved data from node " << p_other << " to " <<
            *this << ". Now doing clean up.");
            p_other.m_PreviousNode = nullptr;
            p_other.m_NextNode = nullptr;
            p_other.m_Item = T();
        }
        
        /**
         * @brief m_PreviousNode and m_NextNode are set to their paramater
         * equivalents and m_Item is set to it's default value.
         * 
         */
        Node(Node<T>* const p_previous_node, Node<T>* const p_next_node):
        m_PreviousNode(p_previous_node),
        m_NextNode(p_next_node),
        m_Item()
        {
            LogDebugLine("Constructed node at " << *this <<
            " from previous node " << p_previous_node << " and next node "
            << p_next_node);
        }
        /**
         * @brief Sets m_PreviousNode and m_NextNode to null, m_Item is set to
         * p_item.
         * 
         */
        Node(const T& p_item):
        m_PreviousNode(nullptr),
        m_NextNode(nullptr),
        m_Item(p_item)
        {
            LogDebugLine("Constructed node at " << *this << " from item "
            << p_item);
        }
        /**
         * @brief All of the fields are set to their paramater equivalents.
         * 
         */
        Node(Node<T>* const p_previous_node, Node<T>* const p_next_node, const T& p_item):
        m_PreviousNode(p_previous_node),
        m_NextNode(p_next_node),
        m_Item(p_item)
        {
            LogDebugLine("Constructed node at " << *this <<
            " from previous node " << p_previous_node << ", next node "
            << p_next_node << " and item " << p_item);
        }

        /**
         * @brief Same as copy constructor.
         * 
         * @return *this.
         * 
         */
        Node<T>& operator=(const Node<T>& p_other)
        {

            LogDebugLine("Copying from node " << p_other << " to node " << *this);

            m_PreviousNode = p_other.m_PreviousNode;
            m_NextNode = p_other.m_NextNode;
            m_Item = p_other.m_Item;

            return *this;

        }
        /**
         * @brief Same as move constructor.
         * 
         * @return *this.
         * 
         */
        Node<T>& operator=(Node<T>&& p_other)
        {
        
            LogDebugLine("Moving from node " << p_other << " to node " << *this);

            m_PreviousNode = p_other.m_PreviousNode;
            m_NextNode = p_other.m_NextNode;
            m_Item = p_other.m_Item;

            p_other.m_PreviousNode = nullptr;
            p_other.m_NextNode = nullptr;
            p_other.m_Item = T();

            return *this;
        
        }

        /**
         * @brief Returns m_Item.
         *  
         */
        operator T&()
        {
            return m_Item;
        }
        /**
         * @brief Returns m_Item.
         *  
         */
        operator const T&() const
        {
            return m_Item;
        }

        /**
         * @brief Returns true if this node is identical to p_other
         * 
         * @details Identical here referse to the fact that all of their fields
         * are the same(previous node, next node and item).
         *  
         */
        bool operator==(const Node<T>& p_other) const
        {
            LogDebugLine("Comapring node " << *this << " and node " << p_other);
            return 
                m_PreviousNode == p_other.m_PreviousNode
                &&
                m_NextNode == p_other.m_NextNode
                &&
                m_Item == p_other.m_Item
            ;
        }
        /**
         * @brief Returns the opposite of the
         * @ref operator==(const Node<T>& p_other) operator.
         * 
         */
        bool operator!=(const Node<T>& p_other) const
        {
            LogDebugLine("Returning the reverse of the comparison");
            return !(*this == p_other);
        }

    };


    #ifdef IO__IO_IO_HPP
    template<typename T>
    const Library::IO::OutputStream& operator<<(const Library::IO::OutputStream& p_stream, const Node<T>& p_node)
    {
        
        p_stream << (void*)&p_node;
        p_stream << "{ m_PreviousNode = ";
        p_stream << (void*)p_node.m_PreviousNode;
        p_stream << ", m_NextNode = ";
        p_stream << (void*)p_node.m_NextNode;
        p_stream << ", m_Item = [ ";
        p_stream << p_node.m_Item;
        p_stream << " ] }";
        
        return p_stream;
        
    }
    #endif


    /**
     * @brief Calls p_allocate and allocates sizeof(Node<T>) bytes. What ever
     * p_allocate returns is returned back.
     * 
     */
    template<typename T>
    inline Node<T>* AllocateNodeUsingAllocatorNoErrorCheck(void* (&p_allocate) (Size))
    {
        LogDebugLine("Allocating node using allocator.");
        Node<T>* l_returnValue = (Node<T>*)p_allocate(sizeof(Node<T>));
        LogDebugLine("Allocated node is at " << (void*)l_returnValue);
        return l_returnValue;
    }
    template<typename T>
    inline Node<T>* AllocateNodeUsingAllocatorNoErrorCheck()
    {
        LogDebugLine("Using defaults for AllocateNodeUsingAllocatorNoErrorCheck.");
        return AllocateNodeUsingAllocatorNoErrorCheck<T>(Library::LibraryMeta::g_DEFAULT_ALLOCATOR);
    }

    /**
     * @brief Returns the number of pointer jumps that are needed to reach p_end
     * by starting from p_start->m_NextNode and continuing to follow the next
     * node pointers.
     * 
     * @details This function counts the number of time m_NextNode needs to be
     * dereference in order to reach p_end from p_start.
     * 
     * The function can be used to count the number of nodes in a given part of
     * a chain.
     * 
     * @section DoLiLiNo_DisCalc_Examples Examples
     * If the node chain ends in a null pointer then this function can be used
     * to count the distance to the end from any given node. Simply pass nullptr
     * as p_end.
     * @code{.cpp}
     * Size l_result = CountDistanceFromNodeToNode(l_someNode, nullptr);
     * @endcode
     * 
     * If the node chain is cyclic then p_start and p_end can be the same.
     * The function does NOT compare p_start and p_end and as such it would make
     * a full circle around the node chain.
     * @code{.cpp}
     * //This would return the number of nodes in the entire cycle.
     * Size l_result = CountDistanceFromNodeToNode(l_someNodeInCycle. l_someNodeInCycle);
     * @endcode
     * 
     * @time O(n), n being the number of jumps that the function has to do in
     * order to reach p_end from p_start.
     * 
     * @param p_start The node to start going up the chain from.
     * @param p_end The node to reach by going up the chain.
     * 
     * @return The number of times a pointer was dereferenced, including the
     * inital p_start. The minimum return value is 1.
     *  
     * @warning **This function is low level.**
     * This function **ASSUMES** the following:
     * -# p_start and p_end are a part of the same node chain
     * -# p_end can be reached by dereferencing each next node starting from
     * p_start.
     * 
     * If any of these assumptions are false then the behaviour of the function
     * is undefined.
     * 
     */
    template<typename T>
    Size CountDistanceFromNodeToNode(
        const Node<T>& p_start,
        const Node<T>* const p_end
    )
    {

        LogDebugLine("Counting the distance going forward from node at "
        << p_start << " to node at " << p_end); //Note: p_end may be null.

        Size l_returnValue = 1;
        Node<T>* l_curNode = p_start.m_NextNode;

        LogDebugLine("Starting at node at " << (void*)l_curNode);
        while(l_curNode != p_end)
        {
            l_curNode = l_curNode->m_NextNode;
            ++l_returnValue;
        }
        LogDebugLine("Ended at node at " << (void*)l_curNode);

        LogDebugLine("Counted distance is " << l_returnValue);
        return l_returnValue;

    }
    /**
     * @brief Same as @ref CountDistanceFromNodeToNode except that
     * m_PreviousNode is dereferenced instead of m_NextNode.
     * 
     * @warning **This function is low level.** This function makes the same
     * assumptions as @ref CountDistanceFromNodeToNode make sure to read them!
     * 
     */
    template<typename T>
    Size CountDistanceFromNodeToNodeBackwards(
        const Node<T>& p_start,
        const Node<T>* const p_end
    )
    {

        LogDebugLine("Couting the distance going backward from node at "
        << p_start << " to node at " << p_end); //Note: p_end may be null.

        Size l_returnValue = 1;
        Node<T>* l_curNode = p_start.m_PreviousNode;

        LogDebugLine("Starting at node at " << (void*)l_curNode);
        while(l_curNode != p_end)
        {
            l_curNode = l_curNode->m_PreviousNode;
            ++l_returnValue;
        }
        LogDebugLine("Ended at node at " << (void*)l_curNode);

        LogDebugLine("Counted distance is " << l_returnValue);
        return l_returnValue;
    }

    /**
     * @brief Loops starting from p_start->m_NextNode and checks if the current
     * node has p_item as it's m_Item. If that is true then the node is returned
     * otherwise the function continues onto the current node's m_NextNode.
     * 
     * @details Note: The function does NOT check if p_start and p_end have
     * p_item as such they most likely won't be returned.
     * 
     * @time O(n), n being however many times the loop needs to run until a node
     * with p_item is found.
     * 
     * @tparam T This type must have the == operator. The operator must return
     * bool and be able to compare 2 objects of type T. The operator is expected
     * to return true if the objects are the same, false otherwise.
     * 
     * @param p_item The item to find.
     * @param p_start Where the search should begin.
     * @param p_end Where the search should end.
     * 
     * @warning **This function is low level.**
     * This function **ASSUMES** the following:
     * -# p_start and p_end are a part of the same node chain
     * -# p_end can be reached by dereferencing each next node starting from
     * p_start.
     * 
     * If any of these assumptions are false then the behaviour of the function
     * is undefined.
     * 
     * @return The first node with p_item. If p_item cannot be found inside any
     * node, nullptr is returned.
     *  
     */
    template<typename T>
    Node<T>* FindFirstNodeWithItemBetweenNodeAndNode(
        const T& p_item,
        const Node<T>& p_start,
        const Node<T>* const p_end
    )
    {

        LogDebugLine("Searching for item at " << (void*)&p_item
        << " between node starting at " << (void*)&p_start << " and ending at "
        "node at " << (void*)p_end << " going forwards.");

        //BUG: What if p_start has the item and the list is not cyclical?
        Node<T>* l_curNode = p_start.m_NextNode;
        while(l_curNode != p_end)
        {
            if(l_curNode->m_Item == p_item)
            {
                LogDebugLine("Found the item in node at " << (void*)l_curNode);
                return l_curNode;
            }
     
            l_curNode = l_curNode->m_NextNode;
        }

        LogDebugLine("Did not find the item anywhere, returning null.");
        return nullptr;

    }
    /**
     * @brief Same as @ref FindFirstNodeWithItemBetweenNodeAndNode except that
     * m_PreviousNode is dereferenced instead of m_NextNode.
     * 
     * @warning **This function is low level.** 
     * This function makes the same assumptions as
     * @ref FindFirstNodeWithItemBetweenNodeAndNode make sure to read them!
     * 
     */
    template<typename T>
    Node<T>* FindFirstNodeWithItemBetweenNodeAndNodeBackwards(
        const T& p_item,
        const Node<T>& p_start,
        const Node<T>* const p_end
    )
    {

        LogDebugLine("Searching for item at " << (void*)&p_item
        << " between node starting at " << (void*)&p_start << " and ending at "
        "node at " << (void*)p_end << " going backwards.");

        //BUG: What if p_start has the item and the list is not cyclical?
        Node<T>* l_curNode = p_start.m_PreviousNode;
        while(l_curNode != p_end)
        {
            if(l_curNode->m_Item == p_item)
            {
                LogDebugLine("Found the item in node at " << (void*)l_curNode);
                return l_curNode;
            }
     
            l_curNode = l_curNode->m_PreviousNode;
        }

        LogDebugLine("Did not find the item anywhere, returning null.");
        return nullptr;

    }

    /**
     * @brief Returns the node p_num_of_steps steps forward form p_node.
     * 
     * @details Dereferences p_node.m_NextNode->m_NextNode... and so on
     * p_num_of_steps times and returns the last dereferenced next node.
     * 
     * If p_num_of_steps is 0, the memory address of p_node is returned.
     * 
     * @time O(n), n being p_num_of_steps.
     * 
     * @param p_num_of_steps How many times the next node needs to be
     * dereferenced before the function returns the last one.
     * @param p_node The node where the dereferencing should start.
     * 
     * @warning **This function is low level**
     * This function assumes the following:
     * -# p_node is apart of a node chain;
     * -# There are at least p_num_of_steps valid node pointers after p_node.
     * 
     * Is any of these assumptions are false then the behaviour of the function
     * is undefined.
     *  
     */
    template<typename T>
    const Node<T>* FindNodeNumberOfStepsForwardFromNode(
        const Size& p_num_of_steps,
        const Node<T>& p_node
    )
    {

        LogDebugLine("Finding the node after " << p_num_of_steps
        << " steps going forward from node at " << (void*)&p_node);

        const Node<T>* l_returnValue = &p_node;
        for(Size i = 0; i < p_num_of_steps; ++i)
        {
            l_returnValue = l_returnValue->m_NextNode;
        }

        LogDebugLine("Found the node, the address is " << (void*)l_returnValue);
        return l_returnValue;

    }
    /**
     * @brief Same as @ref FindNodeNumberOfStepsForwardFromNode except that
     * m_PreviousNode is dereferenced instead of m_NextNode.
     * 
     * @warning **This function is low level.**
     * This function makes the same assumptions as
     * @ref FindNodeNumberOfStepsForwardFromNode make sure to read them!
     * 
     */
    template<typename T>
    const Node<T>* FindNodeNumberOfStepsBackwardFromNode(
        const Size& p_num_of_steps,
        const Node<T>& p_node
    )
    {

        LogDebugLine("Finding the node after " << p_num_of_steps
        << " steps going backward from node at " << (void*)&p_node);

        const Node<T>* l_returnValue = &p_node;
        for(Size i = 0; i < p_num_of_steps; ++i)
        {
            l_returnValue = l_returnValue->m_PreviousNode;
        }

        LogDebugLine("Found the node, the address is " << (void*)l_returnValue);
        return l_returnValue;

    }


    /**
     * @brief Inserts p_insertee after p_node by changing their next and
     * previous node pointers.
     * 
     * @details By insertion it is meant that p_insertee becomes the next node
     * after p_node. p_node's old next node becomes p_instertee's next node.
     * 
     * This is done by:
     * 
     * Making p_insertee.m_NextNode = p_node.m_NextNode and
     * p_insertee.m_PreviousNode = &p_node.
     * 
     * If p_node.m_NextNode != nullptr then p_node.m_NextNode->m_PreviousNode =
     * &l_instertee.
     * 
     * p_node.m_NextNode = &l_insertee
     * 
     * @param p_insertee The node to insert.
     * @param p_node The node where the insertion will happen.
     * 
     */
    template<typename T>
    void InsertNodeAfterNode(Node<T>& p_insertee, Node<T>& p_node)
    {
        
        LogDebugLine("Inserting node " << p_insertee << " after node " << p_node);

        p_insertee.m_NextNode = p_node.m_NextNode;
        p_insertee.m_PreviousNode = &p_node;

        if(p_node.m_NextNode != nullptr)
        {
            p_node.m_NextNode->m_PreviousNode = &p_insertee;
        }

        p_node.m_NextNode = &p_insertee;

    }
    /**
     * @brief Returns p_node.m_NextNode after unlinking it.
     * 
     * @details If p_node.m_NextNode == nullptr then null is returned, otherwise
     * p_node.m_NextNode = p_node.m_NextNode->NextNode. If p_node's new next
     * node is NOT null then l_returnValue->m_NextNode->m_PreviousNode = &p_node.
     * 
     * After this is done p_node's original next node is returned as is, this
     * means that the original's m_NextNode and m_PreviousNode are not changed
     * making it an invalid node. It is recommended to zero them out if the
     * popped node will not be used.
     * 
     * @param p_node What node's next node will be popped.
     * @return p_node.m_NextNode unlinked. Note that the return value's
     * m_NextNode and m_PreviousNode are not changed.
     * 
     */
    template<typename T>
    Node<T>* PopNodesNextNode(Node<T>& p_node)
    {

        LogDebugLine("Poping the next node of node " << p_node);

        Node<T>* l_returnValue = p_node.m_NextNode;
        if(l_returnValue == nullptr)
        {
            return l_returnValue;
        }

        p_node.m_NextNode = l_returnValue->m_NextNode;
        
        if(l_returnValue->m_NextNode != nullptr)
        {
            l_returnValue->m_NextNode->m_PreviousNode = &p_node;
        }

        return l_returnValue;

    }


    /**
     * @brief Call p_deallocate with p_node.
     * 
     */
    template<typename T>
    inline void DestroyNodeUsingDeallocator(Node<T>* const p_node, void (&p_deallocate) (void*))
    {
        LogDebugLine("Destroying node " << p_node);
        p_deallocate(p_node);
    }
    template<typename T>
    inline void DestroyNodeUsingDeallocator(Node<T>* const p_node)
    {
        LogDebugLine("Destroying node " << p_node << " using the default deallocator");
        Library::LibraryMeta::g_DEFAULT_DEALLOCATOR(p_node);
    }



    #ifdef _DOXYGEN_
    /**
     * @brief Prints p_node's fields to p_stream.
     * 
     * @details This format in which the node is written is:
     * <ADDRESS OF THE NODE>{ m_PreviousNode = <p_node.m_PreviousNode as void*>,
     * m_NextNode = <p_node.m_NextNode as void*>, m_Item = [ <what ever the <<
     * operator does for the type T and p_node.m_Item ] }
     * 
     * Note: There are no newlines and all of the whitespaces outside of the
     * angle brackets are printed.
     * 
     * 
     * @warning T MUST have support for being written to an OutputStream using
     * the << operator or this function won't be able to compile.
     * 
     * This operator is only defined if the header guard of IO.hpp is detected.
     *  
     */
    template<typename T>
    const Library::IO::OutputStream& operator<<(const Library::IO::OutputStream& p_stream, const Node<T>& p_node);
    #endif // _DOXYGEN_

}

#endif //DOUBLY_LINKED_LIST_NODE__DATA_STRUCTURES_LISTS_DOUBLY_LINKED_DOUBLY_LINKED_LIST_NODE_HPP