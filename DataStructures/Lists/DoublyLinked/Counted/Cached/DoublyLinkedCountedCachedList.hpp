/**
 * @file DoublyLinkedCountedCachedList.hpp
 * 
 * @brief Defines the doubly linked counted cached list along with some
 * functions that can be used with it.
 * 
 */

#ifndef DOUBLY_LINKED_COUNTED_CACHED_LIST__DATA_STRUCTURES_LISTS_DOUBLY_LINKED_COUNTED_CACHED_DOUBLY_LINKED_COUNTED_CACHED_LIST_HPP
#define DOUBLY_LINKED_COUNTED_CACHED_LIST__DATA_STRUCTURES_LISTS_DOUBLY_LINKED_COUNTED_CACHED_DOUBLY_LINKED_COUNTED_CACHED_LIST_HPP

#include <stdint.h>
#include "../../DoublyLinkedListNode.hpp"
#include "../../../../../LibraryMeta/LibraryMeta.hpp"

/**
 * @brief The cached variant of counted lists. This variant uses a special list
 * chache structure in order to speed up lookup time in the list.
 * 
 */
namespace Library::DataStructures::Lists::DoublyLinked::Counted::Cached
{

    /**
     * @brief A list cache. This structure is used to cache a node that can then
     * be used to find other nodes near it.
     * 
     * @details This structure works by having 2 fields:
     * - m_Node - this is a pointer to some node that belongs to a doubly linked
     * linked node chain.
     * - m_NodeIndex - this is the index of m_Node, the index must be the
     * distance from the inital node to m_Node.
     * 
     * @section CacheDefinitions
     *
     * 2 types of caches and 2 actions that be done on them can be defined.
     * 
     * The 2 types being:
     * -# An empty cache. This type of cache is defined as having it's m_Node
     * set to null AND having it's m_NodeIndex set to 0.\n If a cache is of this
     * type then it cannot be used to accesses nodes in the chain. Make sure to
     * alway check if a cache is empty before using it.
     * -# A non empty cache. This type of cache is defined as having it's m_Node
     * set to a non null value and it's m_NodeIndex as the index of m_Node in
     * the contex of what ever chain m_Node belongs to.\n
     * In other words the opposite of an empty cache.\n If a cache is of this
     * type then it CAN be used to accesses nodes in the chain it's pointing to.
     * 
     * Note: m_NodeIndex may be 0 even if the cache is non empty. The best way
     * to check if a cache is empty is to check if it's m_Node is null.
     * 
     * The 2 actions being:
     * -# Emptying the cache. This is simply means setting it's m_Node to null
     * and it's m_NodeIndex to 0, making an empty cache, hence the name of the
     * action.
     * -# Updating the cache. This action involves setting the cache's m_Node to
     * some node that needs to be cached and setting it's m_NodeIndex to the
     * newly cached nodes index. You must not skip any of these steps, however
     * if you do the cache would become invalid and using it will be undefined
     * behaviour.\n
     * The 'some node' that was refereed to here can be any valid node that is
     * apart of some node chain. See the section on when to update the cache for
     * extra information.
     * 
     * @subsection CacheWhenUpdate When to update the cache
     * The cache should only be updated after any operation that leads to
     * discovering some node, this operation must have a time or memory
     * complexity that is NOT constant. If the node that was found through the
     * operation will no longer be available for what ever reason, the cache
     * should either be updated to store the discovered nodes next or previous
     * node. If neither of these can be done, the cache should not be updated.
     * 
     * **The cache should never be updated if the update would require any extra
     * operations that would take a long time.** \n
     * An example of this would be an operation that discovers some node in a
     * chain. The operation takes linear time, however the operation does not
     * keep track of the index of the node and discovering the index would
     * require a lengthy operation. In this case the cache should not be updated.
     * 
     * @section CacheUse Intended use 
     * The cache should be used when having access to some unknow 'middle' part
     * of the chain would speed up some algorightm. First you should always
     * check if the cache is empty. If it is empty consider an alternative to
     * the cache, if it is not empty check if with the current index there would
     * actually be a speed up over other alternitives, you can choose to skip
     * this step and simply assume that there would be a speed up. If you
     * decided to use the cache then start at it's m_Node and either go up or
     * down the chain using m_Node's next and last node pointers, what ever
     * suits your algorithm.
     * 
     * @section CacheEdgy Edge cases
     * There is one specific edge case involving the cache. This edge case
     * involves removing nodes from a chain, if the removed node is the node in
     * the cache then the cache will become invalid since it would point to a
     * node that is no longer in the chain. There are 2 methods to prevent this
     * from happening:
     * -# Check if the node your removing is in the cache, if so then either
     * empty the cache or update it with the removed node's next or previous
     * nodes.
     * -# Alway update the cache with some node after removing. This node can be
     * any node that is in the node chain, all of the updating rules must be
     * followed however. The simplest implementation of this always updates the
     * cache with the removed node's next node.
     *
     */
    template<typename T>
    struct ListCache
    {

        Node<T>* m_Node;
        Size m_NodeIndex;


        /**
         * @brief Sets m_Node to null and m_NodeIndex to 0.
         * 
         */
        ListCache():
        m_Node(nullptr),
        m_NodeIndex(0)
        {
            LogDebugLine("Constructed default list cache at " << (void*)this);
        }
        /**
         * @brief Sets m_Node to p_node and m_NodeIndex to p_node_index.
         * 
         */
        ListCache(Node<T>* const p_node, const Size& p_node_index):
        m_Node(p_node),
        m_NodeIndex(p_node_index)
        {
            LogDebugLine("Constructed list cache at " << *this << " from "
            "node and index");
        }

        /**
         * @brief Sets m_Node to p_other.m_Node and sets m_NodeIndex to
         * p_other.m_NodeIndex
         * 
         */
        ListCache(const ListCache& p_other):
        m_Node(p_other.m_Node),
        m_NodeIndex(p_other.m_NodeIndex)
        {
            LogDebugLine("Constructed list cache by copying from "
            << p_other << " to " << *this);
        }
        /**
         * @brief Sets m_Node to p_other.m_Node and sets m_NodeIndex to
         * p_other.m_NodeIndex. p_other.m_Node is set to null and
         * p_other.m_NodeIndex is set 0.
         * 
         */
        ListCache(ListCache&& p_other):
        m_Node(p_other.m_Node),
        m_NodeIndex(p_other.m_NodeIndex)
        {
            
            p_other.m_Node = nullptr;
            p_other.m_NodeIndex = 0;
        
            LogDebugLine("Constructed list cache by moving from " << p_other
            << " to " << *this);

        }


        /**
         * @brief Same as copy constructor.
         * 
         * @return *this.
         *  
         */
        ListCache& operator=(const ListCache& p_other)
        {
            
            LogDebugLine("Copying list cache from " << p_other << " to " << *this);

            m_Node = p_other.m_Node;
            m_NodeIndex = p_other.m_NodeIndex;

            return *this;

        }
        /**
         * @brief Same as move constructor.
         * 
         * @return *this.
         *  
         */
        ListCache& operator=(ListCache&& p_other)
        {

            LogDebugLine("Moving list cache from " << p_other << " to " << *this);

            m_Node = p_other.m_Node;
            m_NodeIndex = p_other.m_NodeIndex;

            p_other.m_Node = nullptr;
            p_other.m_NodeIndex = 0;

            return *this;
        
        }

    //TODO:
        operator Node<T>*&()
        {
            return m_Node;
        }
        operator Size&()
        {
            return m_NodeIndex;
        }
        operator const Node<T>* const&() const
        {
            return m_Node;
        }
        operator const Size&() const
        {
            return m_NodeIndex;
        }


        /**
         * @brief Returns m_Node == p_other.m_Node && m_NodeIndex ==
         * p_other.m_NodeIndex.
         * 
         */
        bool operator==(const ListCache& p_other) const
        {
            LogDebugLine("Comparing if list cache" << p_other << " and "
            << *this << " are identical.");
            return m_Node == p_other.m_Node && m_NodeIndex == p_other.m_NodeIndex;
        }
        /**
         * @brief Returns m_Node != p_other.m_Node || m_NodeIndex !=
         * p_other.m_NodeIndex.
         * 
         */
        bool operator!=(const ListCache& p_other) const
        {
            LogDebugLine("Comparing if list cache" << p_other << " and "
            << *this << " are not identical.");
            return m_Node != p_other.m_Node || m_NodeIndex != p_other.m_NodeIndex;
        }
    
    };

    /**
     * @brief A structure for holding a doubly linked node chain.
     * 
     * @details This structure contains a m_FirstNode and m_LastNode field.
     * These fields are used to mark the beginning and end of a node chain.
     * The m_Size field keeps track of the number of nodes in the node chain
     * pointer to by m_FirstNode and m_LastNode. And finally m_Cache is the
     * list's cache that is used to speed up look up times.
     * 
     * @section ListTypes Types of lists
     * There are 3 different types of valid lists that are currently accepted,
     * those being:
     * -# An empty list - this type of list is characterized by having it's
     * m_FirstNode and m_LastNode set to null, it's m_Size to 0, and m_Cache to
     * an empty cache. All of these conditions must be true fro a list to be
     * consider empty. An empty list does not point to a node chain(duh) and
     * as such does not hold any data. This type of list may also be refer to as
     * a **default list**
     * -# A cyclic list - this type if list is characterized by having it's
     * m_FirstNode and m_LastNode be non null pointer, m_Size > 0, and m_Cache
     * either being empty or having a cached node. m_FirstNode->m_PreviousNode
     * must point to m_LastNode and m_LastNode->m_NextNode must point to
     * m_FirstNode. m_FirstNode can be any node in a doubly linked node chain,
     * however m_LastNode must be m_FirstNode's previous node, the only
     * exception being when the node chain only has 1 node, here the first and
     * last nodes can point to the same node. The node pointed to by m_FirstNode
     * will be considered to be the node at index 0, while the node pointer to
     * by m_LastNode will be consider to be the node at the last index. m_Cache
     * may have any node in the chain cached, be it the first or last or some
     * node in the middle. m_Size must alway be precisely the number of nodes in
     * the chain.
     * -# A null terminated list - this list type is identical to the cyclic
     * list type execpt that m_FirstNode->m_PreviousNode must be null and
     * m_LastNode->m_NextNode must also be null. Every thing else stays the same
     * as the cyclic list type.
     * 
     * @tparam T This type must be any type that supports the following
     * operations:
     * - Copying by construction or the = operator;
     * - Moving by construction or the = operator;
     * - Comparing using the == operator;
     * - Comparing using the != operator.
     * Additionally when debug logging is enabled the type must also be able to
     * be written to an output stream using the << operator.
     *  
     */
    template<typename T>
    struct List
    {
    
        /**
         * @brief The first node of the chain.
         * 
         */
        Node<T>* m_FirstNode;
        /**
         * @brief The last node of the chain.
         * 
         */
        Node<T>* m_LastNode;
        /**
         * @brief How many nodes are in the chain.
         * 
         */
        Size m_Size;
        /**
         * @brief The cache. Stores the last accessed node and it's index.
         * 
         */
        ListCache<T> m_Cache;


        /**
         * @brief All pointers are set to null and all numbers are set to 0.
         * 
         */
        List():
        m_FirstNode(nullptr),
        m_LastNode(nullptr),
        m_Size(0),
        m_Cache()
        {
            LogDebugLine("Constructed empty list at " << (void*)this);
        }
        /**
         * @brief Sets m_FirstNode to p_first_node, m_LastNode to p_last_node,
         * m_Cache is made empty and m_Size is counted.
         * 
         */
        List(Node<T>* p_first_node, Node<T>* p_last_node):
        m_FirstNode(p_first_node),
        m_LastNode(p_last_node),
        m_Cache()
        {
            LogDebugLine("Constructed list at " << (void*)this
            << " from first node at " << (void*)p_first_node
            << " and last node at " << (void*)p_last_node);
        
            LogDebugLine("Discovering the size now.");
        
            if(p_first_node == nullptr || p_last_node == nullptr)
            {
                LogDebugLine("The first node and the last node are null, setting size to 0");
                m_Size = 0;
                return;
            }
        
            m_Size = DoublyLinked::CountDistanceFromNodeToNode<int>(*p_first_node, p_last_node->m_NextNode);

            LogDebugLine("The discovered size is " << m_Size);

        }
        /**
         * @brief Sets all fields to their paramater equivalents, m_Cache is
         * made empty.
         * 
         */
        List(Node<T>* p_first_node, Node<T>* p_last_node, const Size& p_size):
        m_FirstNode(p_first_node),
        m_LastNode(p_last_node),
        m_Size(p_size),
        m_Cache()
        {
            LogDebugLine("Constructed list at " << (void*)this
            << " from first node at " << (void*)p_first_node
            << ", last node at " << (void*)p_last_node << " and size " << p_size);
        }

        /**
         * @brief Copies each field from p_other to this.
         * 
         */
        List(const List<T>& p_other):
        m_FirstNode(p_other.m_FirstNode),
        m_LastNode(p_other.m_LastNode),
        m_Size(p_other.m_Size),
        m_Cache(p_other.m_Cache)
        {
            LogDebugLine("Constructed list by copying from " << p_other);
        }
        /**
         * @brief Copies each field from p_other to this and makes p_other a
         * default list.
         * 
         */
        List(List<T>&& p_other):
        m_FirstNode(p_other.m_FirstNode),
        m_LastNode(p_other.m_LastNode),
        m_Size(p_other.m_Size),
        m_Cache(p_other.m_Cache)
        {
        
            LogDebugLine("Constructed list by moving from " << p_other
            << " clearing the other list now.");
            p_other.m_FirstNode = nullptr;
            p_other.m_LastNode = nullptr;
            p_other.m_Size = 0;
            p_other.m_Cache = ListCache<T>();
        
        }
        

        /**
         * @brief Same as copy constructor.
         * 
         * @return *this.
         *  
         */
        List<T>& operator=(const List<T>& p_other)
        {
            
            LogDebugLine("Copying list from " << p_other << " to " << *this);
            m_FirstNode = p_other.m_FirstNode;
            m_LastNode = p_other.m_LastNode;
            m_Size = p_other.m_Size;
            m_Cache = p_other.m_Cache;

            return *this;

        }
        /**
         * @brief Same as move constructor.
         * 
         * @return *this.
         *  
         */
        List<T>& operator=(List<T>&& p_other)
        {
        
            LogDebugLine("Moving list from " << p_other << " to " << *this);
            m_FirstNode = p_other.m_FirstNode;
            m_LastNode = p_other.m_LastNode;
            m_Size = p_other.m_Size;
            m_Cache = p_other.m_Cache;

            p_other.m_FirstNode = nullptr;
            p_other.m_LastNode = nullptr;
            p_other.m_Size = 0;
            p_other.m_Cache = ListCache<T>();

            return *this;

        }


        /**
         * @brief Returns the item at p_index.
         * 
         * @details For details check @ref FindNodeAtIndexNoErrorCheckInListAndUpdateCache.
         * 
         * @warning **This operator is low level**
         * This operator **ASSUMES** the following:
         * -# p_index < p_list.m_Size;
         * -# p_list.m_FirstNode != nullptr;
         * -# p_list.m_LastNode != nullptr.
         * 
         * If any of these conditions are false then the behaviour of the operator
         * is undefined.
         * 
         */
        T& operator[](const Size& p_index)
        {
            LogDebugLine("Returning the item at index " << p_index
            << " from list " << *this);
            return FindNodeAtIndexNoErrorCheckInListAndUpdateCache(p_index, *this)->m_Item;
        }
        /**
         * @brief Same as the other [] operator except that this one is const and
         * does not update the cache.
         * 
         * @param p_index 
         * @return const T& 
         */
        const T& operator[](const Size& p_index) const
        {
            LogDebugLine("Returning the item at index " << p_index
            << " from list " << *this);
            return FindNodeAtIndexNoErrorCheckInList(p_index, *this)->m_Item;
        }


        /**
         * @brief Comapres this and p_other.
         * 
         * @details Returns true if this list and p_other have the same number of
         * items, in the same order and the items are the same. True is also
         * returned if this list and p_other are empty. False is returned in all
         * other cases.
         * 
         * Note: This operator dose not care if the 2 lists are either null
         * terminated or cyclic, only the items and sizes will be compared.
         * 
         */
        bool operator==(const List<T>& p_other)
        {
            
            LogDebugLine("Checking if list " << p_other << " and list "
            << *this << " are the same.");

            if(p_other.m_Size != m_Size)
            {
                LogDebugLine("The lists have diffrent sizes, returning false");
                return false;
            }
            LogDebugLine("Sizes are the same.");

            //If the lists are empty.
            if(m_Size == 0)
            {
                //We can return true here since we know form the first if that
                //the 2 lists' sizes are the same meaning that both are 0 and
                //that both are inturn empty.
                LogDebugLine("Both lists are empty, returning true");
                return true;
            }
            LogDebugLine("They are not emtpy.");

            Node<T>* l_curNodeThis = m_FirstNode;
            Node<T>* l_curNodeOther = p_other.m_FirstNode;

            //Cyclic and null lists need to be compared to diffrent pointers.
            Node<T>* l_endPointer;
            if(m_LastNode->m_NextNode == nullptr)
            {
                LogDebugLine("Detected that this list is null terminated.");
                l_endPointer = nullptr;
            }
            else
            {
                LogDebugLine("Detected that this list is cyclic.");
                l_endPointer = m_FirstNode;
            }
            
            LogDebugLine("Starting to loop through both lists now.");
            
            //Do is used here to check the first ones without making an exception
            //for cyclic lists.
            do
            {
                if(l_curNodeThis->m_Item != l_curNodeOther->m_Item)
                {
                    LogDebugLine("Found missmatch in the lists' items at "
                    "nodes " << l_curNodeOther << " and " << l_curNodeThis
                    << ", returning false.");
                    return false;
                }

                l_curNodeThis = l_curNodeThis->m_NextNode;
                l_curNodeOther = l_curNodeOther->m_NextNode;

            } while (l_curNodeThis != l_endPointer); //We know for the first if
            //that both lists are the same size. As such we only need to check
            //if the end of one has been reached.
            
            LogDebugLine("Found no differences in the 2 lists, returning true");
            //By this point the lists are the same.
            return true;

        }
        /**
         * @brief Returns the opposite of @ref operator==(const List<T>& p_other).
         * 
         */
        bool operator!=(const List<T>& p_other)
        {
            LogDebugLine("Returning the opposite of the comparison");
            return !(*this == p_other);
        }

    };


    #ifdef IO__IO_IO_HPP
    /**
     * @brief Writes p_cache's fields to p_stream.
     * 
     * @details The format is:<ADDRESS OF p_cache> { m_Node = <p_cache.m_Node>,
     * m_NodeIndex = <p_cache.m_NodeIndex> }
     * 
     * There are no new lines written and all of the whitespaces outside of < >
     * are also written.
     * 
     * @param p_stream The stream to write to.
     * @param p_cache The cache to write.
     *  
     */
    template<typename T>
    const Library::IO::OutputStream& operator<<(const Library::IO::OutputStream& p_stream, const ListCache<T>& p_cache)
    {

        p_stream << &p_cache;
        p_stream << " { m_Node = " << (void*)p_cache.m_Node;
        p_stream << ", m_NodeIndex = " << p_cache.m_NodeIndex;
        p_stream << " }";

        return p_stream;

    }
    /**
     * @brief Prints p_list's paramaters to p_stream.
     * 
     * @details The format is: <ADDRESS OF p_list> { m_FirstNode =
     * <p_list.m_FirstNode AS POINTER>, m_LastNode = <l_list.LastNode AS POINTER>,
     * m_Size = <p_list.m_Size AS NUMBER>, m_Cache = <OUTPUT OF
     * @ref operator<<(const Library::IO::OutputStream& p_stream,
     * const ListCache<T>& p_cache)> }
     * 
     * Note: All whitespaces outside of <> are also printed. No new lines are
     * printed.
     * 
     * @param p_stream The stream to write p_list to.
     * @param p_list The list to write.
     *  
     */
    template<typename T>
    const Library::IO::OutputStream& operator<<(const Library::IO::OutputStream& p_stream, const List<T>& p_list)
    {

        p_stream << (void*)&p_list;
        p_stream << " { m_FirstNode = " << (void*)p_list.m_FirstNode;
        p_stream << ", m_LastNode = " << (void*)p_list.m_LastNode;
        p_stream << ", m_Size = " << p_list.m_Size;
        p_stream << ", m_Cache = " << p_list.m_Cache;
        p_stream << " }";

        return p_stream;

    }
    #endif //IO__IO_IO_HPP


    /**
     * @brief Used by CreateListAtOfSizeUsingAllocator. 
     */
    template<typename T>
    static T DefaultItemGenerator(void* p_data)
    {
        (void)p_data;
        return T();
    }
    /**
     * @brief Used by CreateCopyAtOfListUsingAllocator
     */
    template<typename T>
    static T CopyListItemGenerator(void* p_data)
    {
    
        Node<T>** l_node = (Node<T>**)p_data;

        T l_returnValue = (*l_node)->m_Item;

        //Advances the node.
        *l_node = (*l_node)->m_NextNode;

        return l_returnValue;
    
    }

    
    //Note: Out of all of the creation functions,
    //CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator is the only
    //one that actually does any creation. Any other function either changes the
    //item generator or quickly transforms it's output in some way. This is done
    //in order to fully eliminate all copy and pasted code.

    /**
     * @brief Creates a cyclic list at outp_list that has p_size nodes.
     * 
     * @details Creates a cyclic list that contains p_size nodes. It does this
     * by allocating p_size nodes. Each node is linked and configured properly
     * by the time the function returns. On each node allocation p_generate_item
     * is called and the newly allocated node's m_Item field is set to the
     * return value of it.
     * 
     * If p_size is 0, a default list is created at outp_list and the function
     * returns. No calls are made to p_allocate or p_generate_item.
     * 
     * If allocation fails then the outcome depends on where the failure occurred:
     * - If allocation failed while trying to allocate the first node, a default
     * list is created at outp_list, p_alloc_error is called and the function
     * returns. No calls are made to p_generate_item.
     * - If allocation failed while allocating any other node, p_alloc_error is
     * called, once that returns the list is properly configured. Note that when
     * p_alloc_error is called in this case the list is left in an invalid sate,
     * do not attempt to use it. A minimum of 1 calls has been made to
     * p_generate_item in this case.
     * 
     * @time O(n), n being p_size.
     * 
     * @tparam T In order for the item generator function to work, T must have
     * the ability to be assigned another T using the = operator.
     * 
     * @param outp_list Where the output of this function will be written.
     * @param p_size What the size should be of the newly created list.
     * @param p_allocate The allocator to use for all node allocations.
     * @param p_alloc_error A callback for when allocation fails.
     * @param p_alloc_error_data Data for p_alloc_error.
     * @param p_generate_item A function that is called to get a new item for a
     * newly allocated node.
     * @param p_generate_item_data Data that is passed to p_generate_item.
     * 
     */
    template<typename T>
    void CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator(
        List<T>& outp_list,
        const Size& p_size,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data,
        T (&p_generate_item) (void*), void* p_generate_item_data
    )
    {

        LogDebugLine("Creating cyclic list at " << outp_list << " of size " << p_size);

        if(p_size == 0)
        {
            LogDebugLine("The given size is 0, creating empty and returning.");
            outp_list = List<T>();
            return;
        }

        outp_list.m_FirstNode = AllocateNodeUsingAllocatorNoErrorCheck<T>(p_allocate);
        if(outp_list.m_FirstNode == nullptr)
        {
            LogDebugLine("Allocation of the first node failed.");
            LogDebugLine("Creating empty list.");
            outp_list = List<T>();
            
            if(p_alloc_error != nullptr)
            {
                LogDebugLine("Alloc error is not null so calling it.");
                p_alloc_error(p_alloc_error_data);
            }

            LogDebugLine("Returning.");
            return;
        }

        outp_list.m_FirstNode->m_Item = p_generate_item(p_generate_item_data);

        //The reason why l_curNode is the first node is because then if p_size
        //is 1 the loop will be skiped and the list will be configured properly
        //thanks to  the the 2 statements after the loop. This avoids making a
        //special case for p_size == 1.
        Node<T>* l_lastNode = outp_list.m_FirstNode;
        Node<T>* l_curNode = outp_list.m_FirstNode;
        
        Size i;
        for(i = 1; i < p_size; ++i)
        {
            l_curNode = AllocateNodeUsingAllocatorNoErrorCheck<T>(p_allocate);
            if(l_curNode == nullptr)
            {
                LogDebugLine("Allocation of node node number(counting "
                "starting from 0) " << i << " failed.");

                if(p_alloc_error != nullptr)
                {
                    LogDebugLine("Alloc error is not null so calling it.");
                    p_alloc_error(p_alloc_error_data);
                }

                LogDebugLine("Configuring properly and returning.");
                //Fall back to the last node since l_curNode is now null.
                l_curNode = l_lastNode;
                
                //The break skips the rest of the loop and the last few
                //statements are executed causing the list to be configured
                //properly.
                break;
            }
            LogDebugLine("Successfully allocated node number(counting from"
            " 0) " << i << ", the address is " << (void*)l_curNode);

            l_curNode->m_Item = p_generate_item(p_generate_item_data);

            //Inserts l_curNode after l_lastNode.
            l_lastNode->m_NextNode = l_curNode;
            l_curNode->m_PreviousNode = l_lastNode;

            l_lastNode = l_curNode;
        }

        //This is the thing that makes the list cyclic.
        l_curNode->m_NextNode = outp_list.m_FirstNode;
        outp_list.m_FirstNode->m_PreviousNode = l_curNode;

        //l_curNode is now the last node.
        outp_list.m_LastNode = l_curNode;

        //If the loop stopped early i will be the number of allocated nodes,
        //otherwise if the loop ran fully i will be equal to p_size. This is
        //used to reduce the amount of redundant code.
        outp_list.m_Size = i;

    }
    template<typename T>
    inline void CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator(
        List<T>& outp_list,
        const Size& p_size,
        T (&p_generate_item) (void*), void* p_generate_item_data
    )
    {
        LogDebugLine("Using defaults for CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator");
        CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator(
            outp_list,
            p_size,
            Library::LibraryMeta::g_DEFAULT_ALLOCATOR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR_DATA,
            p_generate_item, p_generate_item_data
        );
        LogDebugLine("Returning from using defaults");
    }
    
    /**
     * @brief Same as
     * @ref CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator except
     * that each node's item is set to the default value of T(in other words:
     * T()).
     * 
     */
    template<typename T>
    inline void CreateCyclicListAtOfSizeUsingAllocator(
        List<T>& outp_list,
        const Size& p_size,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {
        LogDebugLine("Using default item generator.");
        CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator(
            outp_list,
            p_size,
            p_allocate, p_alloc_error, p_alloc_error_data,
            DefaultItemGenerator, nullptr
        );
    }
    template<typename T>
    inline void CreateCyclicListAtOfSizeUsingAllocator(
        List<T>& outp_list,
        const Size& p_size
    )
    {
        LogDebugLine("Using default item generator.");
        CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator(
            outp_list,
            p_size,
            DefaultItemGenerator, nullptr
        );
    }

    /**
     * @brief Calls @ref CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator
     * and the result is converted from a cyclic list to a null terminated one.
     * 
     */
    template<typename T>
    inline void 
    CreateNullTerminatedListAtOfSizeUsingAllocatorAndCallItemGenerator(
        List<T>& outp_list,
        const Size& p_size,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data,
        T (&p_generate_item) (void*), void* p_generate_item_data
    )
    {
        CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator(
            outp_list,
            p_size,
            p_allocate, p_alloc_error, p_alloc_error_data,
            p_generate_item, p_generate_item_data
        );
        ConvertCyclicListToNullTerminatedList(outp_list);
    }
    template<typename T>
    inline void 
    CreateNullTerminatedListAtOfSizeUsingAllocatorAndCallItemGenerator(
        List<T>& outp_list,
        const Size& p_size,
        T (&p_generate_item) (void*), void* p_generate_item_data
    )
    {
        LogDebugLine("Using defaults for CreateNullTerminatedListAtOfSizeUsingAllocatorAndCallItemGenerator.");
        CreateNullTerminatedListAtOfSizeUsingAllocatorAndCallItemGenerator(
            outp_list,
            p_size,
            Library::LibraryMeta::g_DEFAULT_ALLOCATOR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR_DATA,
            p_generate_item, p_generate_item_data
        );
        LogDebugLine("Returning from defaults function.");
    }

    /**
     * @brief Same as 
     * @ref CreateNullTerminatedListAtOfSizeUsingAllocatorAndCallItemGenerator
     * except that each node's item is set to the default value of T(in other
     * words: T())
     * 
     */
    template<typename T>
    inline void CreateNullTerminatedListAtOfSizeUsingAllocator(
        List<T>& outp_list,
        const Size& p_size,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {
        LogDebugLine("Using default item generator.");
        CreateNullTerminatedListAtOfSizeUsingAllocatorAndCallItemGenerator(
            outp_list,
            p_size,
            p_allocate, p_alloc_error, p_alloc_error_data,
            DefaultItemGenerator, nullptr
        );
    }
    template<typename T>
    inline void CreateNullTerminatedListAtOfSizeUsingAllocator(
        List<T>& outp_list,
        const Size& p_size
    )
    {
        LogDebugLine("Using default item generator.");
        CreateNullTerminatedListAtOfSizeUsingAllocatorAndCallItemGenerator(
            outp_list,
            p_size,
            DefaultItemGenerator, nullptr
        );
    }

    /**
     * @brief Same as
     * @ref CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator but with
     * 2 exceptions...
     * 
     * @details Those exceptions being:
     * -# Each node's item is set to an item from p_list's nodes. Example:
     * the item of the node at index 0 in outp_list will be the same as the
     * item of the node at index 0 in p_list.
     * -# If p_list is null terminated then so will be outp_list. Same applies
     * for if p_list is cyclic.
     * 
     */
    template<typename T>
    void CreateCopyAtOfListUsingAllocator(
        List<T>& outp_list,
        const List<T>& p_list,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {

        LogDebugLine("Copying list " << p_list << " to " << outp_list);

        //While the create of size function does do the same check, this function
        //must ensure that p_list.m_LastNode is not null so that it can determen
        //if the source list is cyclic or null terminated. 
        if(p_list.m_Size == 0)
        {
            LogDebugLine("The source list is empty so creating empty and returning.");
            outp_list = List<T>();
            return;
        }

        Node<T>* l_temp = p_list.m_FirstNode;

        //The source list is cyclic.
        if(p_list.m_LastNode->m_NextNode != nullptr)
        {
            LogDebugLine("The source list is cyclic so creating a cyclic list.");
            CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator(
                outp_list,
                p_list.m_Size,
                p_allocate, p_alloc_error, p_alloc_error_data,
                CopyListItemGenerator, (void*)&l_temp
            );
        }
        else //The source list is null terminated
        {
            LogDebugLine("The source list is null terminated so creating a"
            " null terminated list.");
            CreateNullTerminatedListAtOfSizeUsingAllocatorAndCallItemGenerator(
                outp_list,
                p_list.m_Size,
                p_allocate, p_alloc_error, p_alloc_error_data,
                CopyListItemGenerator, (void*)&l_temp
            );
        }

    }
    template<typename T>
    inline void CreateCopyAtOfListUsingAllocator(
        List<T>& outp_list,
        const List<T>& p_list
    )
    {
        LogDebugLine("Using defaults for CreateCopyAtOfListUsingAllocator");
        CreateCopyAtOfListUsingAllocator(
            outp_list,
            p_list,
            Library::LibraryMeta::g_DEFAULT_ALLOCATOR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR_DATA
        );
        LogDebugLine("Returning from defaults function");
    }


    /**
     * @brief Converts p_list from a null terminated list to a cyclic list.
     * 
     * @details If p_list is empty this function returns without mutating
     * anything.
     * 
     * @param p_list The list to convert.
     * 
     * @warning This function **ASSUMES** that p_list is null terminated, if any
     * other type of list is passed then the behaviour of the function is
     * undefined. The only case where this does not apply is when p_list is 
     * empty.
     * 
     */
    template<typename T>
    void ConvertNullTerminatedListToCyclicList(List<T>& p_list)
    {
        
        LogDebugLine("Converting list " << p_list
        << " from null terminated to cyclic.");

        if(p_list.m_Size > 0)
        {
            p_list.m_FirstNode->m_PreviousNode = p_list.m_LastNode;
            p_list.m_LastNode->m_NextNode = p_list.m_FirstNode;
        }

    }
    /**
     * @brief Converts p_list for a cyclic list to a null terminated list.
     * 
     * @details If p_list is empty this function returns without mutating
     * anything.
     * 
     * @param p_list The list to convert.
     * 
     * @warning This function **ASSUMES** that p_list is cyclic, if any
     * other type of list is passed then the behaviour of the function is
     * undefined. The only case where this does not apply is when p_list is 
     * empty.
     * 
     */
    template<typename T>
    void ConvertCyclicListToNullTerminatedList(List<T>& p_list)
    {
        
        LogDebugLine("Converting list " << p_list
        << " from cyclic to null terminated.");

        if(p_list.m_Size > 0)
        {
            p_list.m_LastNode = p_list.m_FirstNode->m_PreviousNode;

            p_list.m_FirstNode->m_PreviousNode = nullptr;
            p_list.m_LastNode->m_NextNode = nullptr;
        }

    }


    /**
     * @brief Finds the node at p_index in p_list.
     * 
     * @details This function works by first calculating what p_index is closest
     * to, the start of list, the end of the list or the cache. After it
     * finds the shortest path to p_index the function loops until it reaches
     * the node at p_index.
     * 
     * @time O(n), n being the number of steps it takes to reach the node at
     * p_index. Thanks to the cache the number of steps can be drastically
     * reduced given that the cache is close to p_index and that the cache is
     * not empty.
     * 
     * @param p_index What index to search for.
     * @param p_list The list in which to search in.
     * 
     * @warning **This function is low level**
     * This function **ASSUMES** the following:
     * -# p_index < p_list.m_Size;
     * -# p_list.m_FirstNode != nullptr;
     * -# p_list.m_LastNode != nullptr.
     * 
     * If any of these conditions are false then the behaviour of the function
     * is undefined.
     * 
     * @return The node at p_index in p_list.
     *  
     */
    template<typename T>
    const Node<T>* FindNodeAtIndexNoErrorCheckInList(const Size& p_index, const List<T>& p_list)
    {

        LogDebugLine("Finding the node at index " << p_index << " (will be "
        "referred to as p_index from now on) in list " << p_list);

        const Node<T>* l_returnValue;

        Size l_distanceFromCache;
        const Node<T>* (*l_cacheFunction) (const Size&, const Node<T>&);

        //If the cache is empty then it cannot be used.
        if(p_list.m_Cache != nullptr)
        {
            //Note: can't use abs since Size is unsigned. Also the proper
            //function would still need to be computed.
            if(p_index > p_list.m_Cache)
            {
                l_distanceFromCache = p_index - p_list.m_Cache;
                l_cacheFunction = &FindNodeNumberOfStepsForwardFromNode<T>;
            }
            else
            {
                l_distanceFromCache = p_list.m_Cache - p_index;
                l_cacheFunction = &FindNodeNumberOfStepsBackwardFromNode<T>;
            }

            LogDebugLine("The distance from p_index and to the cached "
            "node is " << l_distanceFromCache);
        }
        else
        {
            LogDebugLine("The cache is empty so not using it.");
            l_distanceFromCache = SIZE_MAX;
            l_cacheFunction = nullptr;
        }

        //Is p_index closer to the end or the start of the list.
        Size l_distanceFromEnd = (p_list.m_Size - 1) - p_index;
        Size l_distanceFromStart = p_index;

        LogDebugLine("The distance from the index and start of the list is "
        << l_distanceFromStart);
        LogDebugLine("The distance from the index and end of the list is "
        << l_distanceFromEnd);

        Size l_distanceFromStartOrEnd;
        Node<T>* l_startOrEnd;
        const Node<T>* (*l_startOrEndFunction) (const Size&, const Node<T>&);
        if(l_distanceFromEnd > l_distanceFromStart)
        {
            l_distanceFromStartOrEnd = l_distanceFromStart;
            l_startOrEnd = p_list.m_FirstNode;
            l_startOrEndFunction = &FindNodeNumberOfStepsForwardFromNode<T>;
            LogDebugLine("p_index is closer to the start of the list.");
        }
        else
        {
            l_distanceFromStartOrEnd = l_distanceFromEnd;
            l_startOrEnd = p_list.m_LastNode;
            l_startOrEndFunction = &FindNodeNumberOfStepsBackwardFromNode<T>;
            LogDebugLine("p_index is closer to the end of the list.");
        }
        

        //Note: since l_distanceFromCache is set to the max value of Size
        //when the cache is empty, if at the same time for some reason the
        //distance from the start or end is also the max value then this
        //expresion will be false making the function use either the first
        //or last node instead of the cache which in this case is empty.
        //
        //What i am trying to say is, there won't be a bug if
        //p_list.m_Cache == nullptr and l_distanceFromStartOrEnd == SIZE_MAX.
        if(l_distanceFromCache < l_distanceFromStartOrEnd)
        {
            LogDebugLine("p_index is closest to the cache.");
            l_returnValue = l_cacheFunction(l_distanceFromCache, *p_list.m_Cache.m_Node);
        }
        else
        {
            LogDebugLine("p_index is closest to either the start or end of"
            " the list");
            l_returnValue = l_startOrEndFunction(l_distanceFromStartOrEnd, *l_startOrEnd);
        }
        
        //this one and updates the cache.
        LogDebugLine("Found the node at p_index, the address is "
        << (void*)l_returnValue);

        return l_returnValue;
        
    }
    /**
     * @brief Same as @ref FindNodeAtIndexNoErrorCheckInList, except that
     * p_list.m_Cache is updated to store the return value of this function.
     * 
     */
    template<typename T>
    Node<T>* FindNodeAtIndexNoErrorCheckInListAndUpdateCache(
        const Size& p_index,
        List<T>& p_list
    )
    {

        //p_list is not const so non of the nodes are expected to be const either.
        Node<T>* l_returnValue = (Node<T>*)FindNodeAtIndexNoErrorCheckInList(p_index, p_list);

        p_list.m_Cache.m_Node = l_returnValue;
        p_list.m_Cache.m_NodeIndex = p_index;

        return l_returnValue;

    }


    /**
     * @brief Finds the index of the node that has the first occurrence of p_item
     * in p_list.
     * 
     * @details Loops form start to end in the list until p_item is found.
     * When it is found the index is returned.
     * If p_list dose not have a node with p_item then p_list.m_Size is returned.
     * 
     * The cache is not used and it is not updated.
     * 
     * @time O(n), n being the number of nodes in the list.
     * 
     * @tparam T The == operator is used to comapre the items.
     * 
     * @param p_item The item to find.
     * @param p_list The list in which to search.
     * @return The index of the node with the first occurrence of p_item. If no
     * node in p_list has p_item then p_list.m_Size is returned.
     *  
     */
    template<typename T>
    Size FindIndexOfFirstOccurrenceOfItemInList(const T& p_item, const List<T>& p_list)
    {

        LogDebugLine("Finding the index of the first occurrence of item at " 
        << (void*)&p_item << " in list " << p_list);

        Node<T>* l_curNode = p_list.m_FirstNode;
        for(Size i = 0; i < p_list.m_Size; ++i)
        {
            if(l_curNode->m_Item == p_item)
            {
                LogDebugLine("Found the item at index " << i);
                return i;
            }

            l_curNode = l_curNode->m_NextNode;
        }

        LogDebugLine("Did not find the item, returning the size of the list.");
        return p_list.m_Size;

    }
    /**
     * @brief Finds the index of the node that has the last occurrence of p_item
     * in p_list.
     * 
     * @details Loops form end to start in the list until p_item is found.
     * When it is found the index is returned.
     * If p_list dose not have a node with p_item then p_list.m_Size is returned.
     * 
     * The cache is not used and it is not updated.
     * 
     * @time O(n), n being the number of nodes in the list.
     * 
     * @tparam T The == operator is used to comapre the items.
     * 
     * @param p_item The item to find.
     * @param p_list The list in which to search.
     * @return The index of the node with the last occurrence of p_item. If no
     * node in p_list has p_item then p_list.m_Size is returned.
     *  
     */
    template<typename T>
    Size FindIndexOfLastOccurrenceOfItemInList(const T& p_item, const List<T>& p_list)
    {

        LogDebugLine("Finding the index of the last occurrence of item at " 
        << (void*)&p_item << " in list " << p_list);

        Node<T>* l_curNode = p_list.m_LastNode;
        for(Size i = p_list.m_Size; i-- > 0;)
        {
            if(l_curNode->m_Item == p_item)
            {
                LogDebugLine("Found the item at index " << i);
                return i;
            }

            l_curNode = l_curNode->m_PreviousNode;
        }

        LogDebugLine("Did not find the item, returning the size of the list.");
        return p_list.m_Size;

    }

    /**
     * @brief Finds the node that has the first occurrence of p_item in p_list.
     * 
     * @details Loops form start to end in the list until p_item is found.
     * When it is found the address of the node that has it is returned.
     * If p_list dose not have a node with p_item then nullptr is returned.
     * 
     * The cache is not used and it is not updated.
     * 
     * @time O(n), n being the number of nodes in the list.
     * 
     * @tparam T The == operator is used to comapre the items.
     * 
     * @param p_item The item to find.
     * @param p_list The list in which to search.
     * @return The address of the node with the first occurrence of p_item. If no
     * node in p_list has p_item then nullptr is returned.
     * 
     */
    template<typename T>
    Node<T>* FindNodeWithFirstOccurrenceOfItemInList(const T& p_item, const List<T>& p_list)
    {

        LogDebugLine("Finding the index of the first occurrence of item at " 
        << (void*)&p_item << " in list " << p_list);

        Node<T>* l_curNode = p_list.m_FirstNode;
        for(Size i = 0; i < p_list.m_Size; ++i)
        {
            if(l_curNode->m_Item == p_item)
            {
                LogDebugLine("Found the item at index " << i);
                return l_curNode;
            }

            l_curNode = l_curNode->m_NextNode;
        }

        LogDebugLine("Did not find the item, returning null.");
        return nullptr;

    }
    /**
     * @brief Finds the node that has the last occurrence of p_item in p_list.
     * 
     * @details Loops form end to start in the list until p_item is found.
     * When it is found the address of the node that has it is returned.
     * If p_list dose not have a node with p_item then nullptr is returned.
     * 
     * The cache is not used and it is not updated.
     * 
     * @time O(n), n being the number of nodes in the list.
     * 
     * @tparam T The == operator is used to comapre the items.
     * 
     * @param p_item The item to find.
     * @param p_list The list in which to search.
     * @return The address of the node with the last occurrence of p_item. If no
     * node in p_list has p_item then nullptr is returned.
     * 
     */
    template<typename T>
    Node<T>* FindNodeWithLastOccurrenceOfItemInList(const T& p_item, const List<T>& p_list)
    {

        LogDebugLine("Finding the index of the last occurrence of item at " 
        << (void*)&p_item << " in list " << p_list);

        Node<T>* l_curNode = p_list.m_LastNode;
        for(Size i = p_list.m_Size; i-- > 0;)
        {
            if(l_curNode->m_Item == p_item)
            {
                LogDebugLine("Found the item at index " << i);
                return l_curNode;
            }

            l_curNode = l_curNode->m_PreviousNode;
        }

        LogDebugLine("Did not find the item, returning null.");
        return nullptr;

    }

    /**
     * @brief Checks if p_list has a node with p_item.
     * 
     * @details Loops from start to end in p_list until p_item is found. Once it
     * is found returns true. If p_item is not found in any node false is
     * returned.
     * 
     * The cache is not used or updated.
     * 
     * @time O(n), n being the number of nodes in p_list.
     * 
     * @tparam T The == operator is used to compare the items.
     * @param p_list The list to search for p_item in.
     * @param p_item The item to search for.
     * @return True if p_list has atleast 1 node with p_item, false otherwise. 
     * 
     */
    template<typename T>
    bool ListContainsItem(const List<T>& p_list, const T& p_item)
    {
        //The function that will be called prints p_list and p_item, no need to
        //reprint.
        LogDebugLine("Checking if the list contains the item.");
        //Yay code reuse!!!
        return FindIndexOfFirstOccurrenceOfItemInList(p_item, p_list) < p_list.m_Size;
    }
    /**
     * @brief Checks if p_list has a node identical to p_node.
     * 
     * @details Loops from start to end in p_list until a node identical to
     * p_node is found. Once it is found returns true. If p_node is not found in
     * false is returned. Identical refers to the fact that the 2 nodes have the
     * same addresses for their next and previous nodes as well as have the same
     * items.
     * 
     * The cache is not used or updated.
     * 
     * @time O(n), n being the number of nodes in p_list.
     * 
     * @tparam T The == operator is used to compare the items.
     * @param p_list The list to search for p_item in.
     * @param p_item The item to search for.
     * @return True if p_list has p_node as part of it's chain, false otherwise. 
     * 
     */
    template<typename T>
    bool ListContainsNode(const List<T>& p_list, const Node<T>& p_node)
    {

        LogDebugLine("Checking if list " << p_list << " has the node "
        << p_node);

        Node<T>* l_curNode = p_list.m_FirstNode;
        for(Size i = 0; i < p_list.m_Size; ++i)
        {
            if(*l_curNode == p_node)
            {
                LogDebugLine("Found the node at index " << i
                << " returning true");
                return true;
            }
            l_curNode = l_curNode->m_NextNode;
        }

        LogDebugLine("Did not find the node, returning false");
        return false;

    }


    /**
     * @brief Adds p_node as the first node to p_list.
     * 
     * @details p_node is made to be the new first node of p_list. This is done
     * by making p_node point to p_list.m_FirstNode and making p_node point back
     * to what ever p_list.m_FirstNode is pointing back to and then finally
     * p_list.m_FirstNode is made to point back to p_node and p_list.m_FirstNode
     * is set to be p_node.
     * 
     * This causes p_node to be added to the node chain that p_list points to.
     * 
     * p_list.m_Size is incremented. Note: no check is made if p_list.m_Size
     * would for the increment, however this is highly unlikely.
     * 
     * If p_list is cyclic then the last node is made to point forward to p_node.
     * 
     * If p_list is empty then p_node is made to be the only node and p_node is
     * made to point to null, making a null terminated list of size 0. Making a
     * null terminated list in this scenario is the most efficient thing that
     * can be done with the algorithm that is used for the addition.
     * 
     * @param p_node The node to add.
     * @param p_list The list to add the node to.
     * 
     */
    template<typename T>
    void AddNodeAsStartToList(Node<T>& p_node, List<T>& p_list)
    {

        LogDebugLine("Adding node " << p_node << " as first node to list "
        << p_list);

        //First part of linking the new node.
        p_node.m_NextNode = p_list.m_FirstNode;

        if(p_list.m_FirstNode != nullptr)
        {
            LogDebugLine("The list has a size > 0, linking the new node "
            "accordingly.");
            //Inherits the previous node. The previous node is either null or
            //the last node, either way it needs to be inherited.
            p_node.m_PreviousNode = p_list.m_FirstNode->m_PreviousNode;
            //Second part of linking the new node.
            p_list.m_FirstNode->m_PreviousNode = &p_node;

            //Node: if the first node is not null then the last node is not null
            //either.
            if(p_list.m_LastNode->m_NextNode != nullptr) //Is the list cyclic?
            {
                LogDebugLine("The list is cyclic so updating the last node.");
                p_list.m_LastNode->m_NextNode = &p_node;
            }
        }
        else
        {
            LogDebugLine("The list is of size 0. Making null terminated "
            "list is size 1...");
            //p_node.m_NextNode is null now thanks to the first statement.
            //This completes the null terminated list of size 1 along with the
            //last statement.
            p_node.m_PreviousNode = nullptr;
            p_list.m_LastNode = &p_node;
        }
        
        LogDebugLine("Final configuration of size and first node pointer");
        p_list.m_FirstNode = &p_node;
        //In any case the list's size has been increased by 1.
        ++p_list.m_Size;

    }
    /**
     * @brief Adds p_node as the last node of p_list.
     * 
     * @details The same as @ref AddNodeAsStartToList except that p_node is
     * made to be the last node.
     * 
     * The same thing applies when adding p_node to an empty list, a null
     * terminated list of size 0 is created.
     * 
     * In terms of speed and memory, this function and @ref AddNodeAsStartToList
     * are pretty much the same if not identical.
     * 
     * @param p_node The node to add.
     * @param p_list The list to add the node to.
     * 
     */
    template<typename T>
    void AddNodeAsEndToList(Node<T>& p_node, List<T>& p_list)
    {

        LogDebugLine("Adding node " << p_node << " as last node to list "
        << p_list);

        //First part of linking the new node.
        p_node.m_PreviousNode = p_list.m_LastNode;

        if(p_list.m_LastNode != nullptr)
        {
            LogDebugLine("The list has a size > 0, linking the new node "
            "accordingly.");
            //Inherits the next node. The next node is either null or
            //the first node, either way it needs to be inherited.
            p_node.m_NextNode = p_list.m_LastNode->m_NextNode;
            //Second part of linking the new node.
            p_list.m_LastNode->m_NextNode = &p_node;

            //Node: if the last node is not null then the first node is not null
            //either.
            if(p_list.m_FirstNode->m_PreviousNode != nullptr) //Is the list cyclic?
            {   
                LogDebugLine("The list is cyclic so updating the first node.");
                p_list.m_FirstNode->m_PreviousNode = &p_node;
            }
        }
        else
        {
            LogDebugLine("The list is of size 0. Making null terminated "
            "list is size 1...");
            //p_node.m_PreviousNode is null now thanks to the first statement.
            //This completes the null terminated list of size 1 along with the
            //last statement.
            p_node.m_NextNode = nullptr;
            p_list.m_FirstNode = &p_node;
        }
        
        LogDebugLine("Final configuration of size and last node pointer");
        p_list.m_LastNode = &p_node;
        //In any case the list's size has been increased by 1.
        ++p_list.m_Size;

    }
    /**
     * @brief Adds p_node after the node at p_index in p_list.
     * 
     * @details Adds p_node to the node chain pointed to by p_list. p_node is
     * inserted after the node at index p_index in p_list. This is done by having
     * p_node point forward to what ever the node at p_index is pointing, having
     * p_node point back to the node at p_index and finally having the node at
     * p_index pointing forward to p_node.
     * 
     * If p_index is equaled to or greater than p_list.m_Size then this is
     * consider an index error. p_index_error is called and the function returns
     * without having mutated anything.
     * 
     * If p_index is p_list.m_Size - 1 then the @ref AddNodeAsLastNodeToList
     * function is used to do the addition. Check it's details for it's own
     * quarks an inner workings.
     * 
     * p_list.m_Size is incremented if addition is successfully completed.
     * 
     * Once addition is successfully completed p_list.m_Cache is updated to
     * point to p_node.
     * 
     * @time O(n), n being the number of steps it takes to reach p_index. This
     * can vary greatly depending on p_index it's self and p_list.m_Cache.
     * 
     * @param p_node The node add. 
     * @param p_index After which index should p_node be added.
     * @param p_index_error The callback to call when p_index is invalid.
     * @param p_index_error_data Data that will be passed to p_index_error.
     * @param p_list The list on which all of this addition will take place.
     * 
     */
    template<typename T>
    void AddNodeAfterIndexToList(
        Node<T>& p_node,
        const Size& p_index,
        void (*p_index_error) (void*), void* p_index_error_data,
        List<T>& p_list
    )
    {

        LogDebugLine("Adding node " << p_node << " to list " << p_list
        << " after index " << p_index);

        //Index error
        if(p_index >= p_list.m_Size)
        {
            LogDebugLine("The given index, " << p_index << ", is bigger "
            "than equaled to the list's size, " << p_list.m_Size);
            if(p_index_error != nullptr)
            {
                LogDebugLine("Index error is not null so calling it.");
                p_index_error(p_index_error_data);
            }

            LogDebugLine("Returning.");
            return;
        }

        //This would be equivalent to adding the node to the end of the list.
        //See inside for extra details as to why this is done.
        //
        //p_list.m_Size - 1 cannot overflow because:
        //1. The only case where p_list.m_Size can overflow is when
        // p_list.m_Size == 1.
        //2. If p_list.m_Size == 0 then the index check above will fail for any
        // value of p_index, this happens because there is no positive integer
        // that is smaller than 0. This causes the function to return before
        // reaching this point.
        if(p_index == p_list.m_Size - 1)
        {
            LogDebugLine("The given index is the last index so calling the"
            " add as end function.");

            //The reason why this function is called is because it reduces the
            //complexity of THIS function. If this exception was not made then
            //the main algorithm below would need to check if the node it got is
            //the last node and if the list cyclic so that it can update the
            //first node etc. You get the point... right? This would increase
            //the number of ifs which would not only cause this function to be
            //more complex but also it would make a little slower thanks to all
            // of the extra unecessary checks(ok ok ok, i know that on modern
            //hardware it won't really make a difference, but even then extra
            //unecessary complexity will be added to this function).
            AddNodeAsEndToList(p_node, p_list);

            LogDebugLine("Returning from the add index function.");
            return;
        }
        //Also this check covers the scenario when the list is of size 1 and the
        //first/last pointers must be changed.

        Node<T>* l_nodeAtIndex = FindNodeAtIndexNoErrorCheckInListAndUpdateCache(
            p_index,
            p_list
        );

        LogDebugLine("The node after which the new node will be addded is "
        "at address " << (void*)l_nodeAtIndex);

        //Links the new node in the chain.
        p_node.m_PreviousNode = l_nodeAtIndex;
        l_nodeAtIndex->m_NextNode->m_PreviousNode = &p_node;
        
        p_node.m_NextNode = l_nodeAtIndex->m_NextNode;
        l_nodeAtIndex->m_NextNode = &p_node;

        LogDebugLine("New node has been linked, updating cache and list "
        "size before returning.");

        //Update the cache.
        p_list.m_Cache.m_Node = &p_node;
        //Note: p_index + 1 cannot overflow, it's a similar reason as to why
        //p_list.m_Size - 1 cannot overflow, but i am too lazy to explain that
        //so here is a todo for you :D.
        //TODO: Explain why this can't overflow.
        p_list.m_Cache.m_NodeIndex = p_index + 1;

        //The size must be increased.
        ++p_list.m_Size;

    }

    template<typename T>
    static void AddItemToListUsingAllocatorGeneric(
        const T& p_item,
        List<T>& p_list,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data,
        void (&p_add_node_function) (Node<T>&, List<T>&)
    )
    {

        Node<T>* l_node = AllocateNodeUsingAllocatorNoErrorCheck<T>(p_allocate);
        if(l_node == nullptr)
        {
            LogDebugLine("Allocation failed.");
            if(p_alloc_error != nullptr)
            {
                LogDebugLine("Alloc error is not null so calling it.");
                p_alloc_error(p_alloc_error_data);
            }

            LogDebugLine("Returning after failed allocation.");
            return;
        }

        l_node->m_Item = p_item;

        LogDebugLine("Doing actual addition");
        p_add_node_function(*l_node, p_list);

        LogDebugLine("Returning from item function.");

    }
    
    /**
     * @brief Allocates a node using p_allocate and adds it to p_list as it's
     * first node. The newly allocated node's item is set to p_item.
     * 
     * @details Basically equivalent to @ref AddNodeAsFirstNodeToList except
     * that the node being added is allocated using p_allocate.
     * 
     * If allocation fails then p_alloc_error is called, this function and
     * returns. In this case this function does not mutated anything.
     * 
     * @tparam T This type must support being copied using the = operator.
     * @param p_item The item to add.
     * @param p_list The list to add the item to.
     * @param p_allocate The function to use to allocated memory for the addition.
     * @param p_alloc_error A callback to call in case of failed allocation.
     * @param p_alloc_error_data Data that is passed to p_alloc_error.
     * 
     */
    template<typename T>
    inline void AddItemAsStartToListUsingAllocator(
        const T& p_item,
        List<T>& p_list,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {
        LogDebugLine("Adding item at address " << p_item << " to list "
        << p_list << " as the first node.");

        AddItemToListUsingAllocatorGeneric(
            p_item,
            p_list,
            p_allocate, p_alloc_error, p_alloc_error_data,
            AddNodeAsStartToList
        );
    }
    template<typename T>
    inline void AddItemAsStartToListUsingAllocator(
        const T& p_item,
        List<T>& p_list
    )
    {
        LogDebugLine("Using defaults for AddItemAsStartToListUsingAllocator");
        AddItemAsStartToListUsingAllocator(
            p_item,
            p_list,
            Library::LibraryMeta::g_DEFAULT_ALLOCATOR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR_DATA
        );
        LogDebugLine("Returning from defaults function");
    }
    
    /**
     * @brief Allocates a node using p_allocate and adds it to p_list as it's
     * last node. The newly allocated node's item is set to p_item.
     * 
     * @details Basically equivalent to @ref AddNodeAsLastNodeToList except
     * that the node being added is allocated using p_allocate.
     * 
     * If allocation fails then p_alloc_error is called, this function and
     * returns. In this case this function does not mutated anything.
     * 
     * @tparam T This type must support being copied using the = operator.
     * @param p_item The item to add.
     * @param p_list The list to add the item to.
     * @param p_allocate The function to use to allocated memory for the addition.
     * @param p_alloc_error A callback to call in case of failed allocation.
     * @param p_alloc_error_data Data that is passed to p_alloc_error.
     * 
     */
    template<typename T>
    inline void AddItemAsEndToListUsingAllocator(
        const T& p_item,
        List<T>& p_list,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {
        LogDebugLine("Adding item at address " << p_item << " to list "
        << p_list << " as the last node.");

        AddItemToListUsingAllocatorGeneric(
            p_item,
            p_list,
            p_allocate, p_alloc_error, p_alloc_error_data,
            AddNodeAsEndToList
        );
    }
    template<typename T>
    inline void AddItemAsEndToListUsingAllocator(
        const T& p_item,
        List<T>& p_list
    )
    {
        LogDebugLine("Using defaults for AddItemAsEndToListUsingAllocator");
        AddItemAsEndToListUsingAllocator(
            p_item,
            p_list,
            Library::LibraryMeta::g_DEFAULT_ALLOCATOR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR_DATA
        );
        LogDebugLine("Returning from defaults function");
    }
    
    /**
     * @brief Allocates a node using p_allocate and adds it to p_list after the
     * node at p_index. The newly allocated node's item is set to p_item.
     * 
     * @details Basically equivalent to @ref AddNodeAfterIndexToList except
     * that the node being added is allocated using p_allocate.
     * 
     * If allocation fails then p_alloc_error is called, this function and
     * returns. In this case this function does not mutated anything.
     * 
     * In the case of an index error, p_index_error is called and the function
     * returns. No calls are made to p_allocate and nothing is mutated.
     * 
     * @tparam T This type must support being copied using the = operator.
     * @param p_item The item to add.
     * @param p_list The list to add the item to.
     * @param p_allocate The function to use to allocated memory for the addition.
     * @param p_alloc_error A callback to call in case of failed allocation.
     * @param p_alloc_error_data Data that is passed to p_alloc_error.
     * 
     */
    template<typename T>
    void AddItemAfterIndexToListUsingAllocator(
        const T& p_item,
        const Size& p_index,
        void (*p_index_error) (void*), void* p_index_error_data,
        List<T>& p_list,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {

        LogDebugLine("Adding item at index " << (void*)&p_item
        << " to list " << p_list << " after index " << p_index);

        //Note: This check must be made in order to not pointlessly allocate a
        //node that logically cannot be added.
        if(p_index >= p_list.m_Size)
        {
            LogDebugLine("The given index, " << p_index << ", is bigger "
            "than equaled to the list's size, " << p_list.m_Size);
            if(p_index_error != nullptr)
            {
                LogDebugLine("Index error is not null so calling it.");
                p_index_error(p_index_error_data);
            }

            LogDebugLine("Returning.");
            return;
        }

        Node<T>* l_node = AllocateNodeUsingAllocatorNoErrorCheck<int>(p_allocate);
        if(l_node == nullptr)
        {
            LogDebugLine("Allocation failed.");
            if(p_alloc_error != nullptr)
            {
                LogDebugLine("Alloc error is not null so calling it.");
                p_alloc_error(p_alloc_error_data);
            }

            LogDebugLine("Returning after failed allocation.");
            return;
        }

        l_node->m_Item = p_item;

        LogDebugLine("Doing actual addition");
        AddNodeAfterIndexToList(
            *l_node,
            p_index, p_index_error, p_index_error_data,
            p_list
        );

        LogDebugLine("Returning from item function.");

    }
    template<typename T>
    inline void AddItemAfterIndexToListUsingAllocator(
        const T& p_item,
        const Size& p_index,
        void (*p_index_error) (void*), void* p_index_error_data,
        List<T>& p_list
    )
    {
        LogDebugLine("Using defaults for AddItemAfterIndexToListUsingAllocator");
        AddItemAfterIndexToListUsingAllocator(
            p_item,
            p_index, p_index_error, p_index_error_data,
            p_list,
            Library::LibraryMeta::g_DEFAULT_ALLOCATOR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR,
            Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR_DATA
        );
        LogDebugLine("Returning from defaults function.");
    }

    /**
     * @brief Remove the first node from p_list and returns it.
     * 
     * @details Unlinks p_list's current first node and returns it. The new first
     * node is set to be the old first node's next node. The old first node's
     * next and previous node pointers are not cleared.
     * 
     * If the list is cyclic then the last node is also configured.
     * 
     * If the list only has 1 node then the first and last node pointers are
     * set to null.
     * 
     * If the list has no nodes then null is returned.
     * 
     * p_list.m_Size is reduced by 1.
     * 
     * @param p_list The list to remove from.
     * 
     * @return p_list's first node, the first node is not fully unlinked and
     * as such still points to nodes in the chain it was in. If p_list has no
     * nodes, null is returned.
     * 
     * @warning The node returned by this function dose not have it's next and
     * previous node pointers cleared, they will contain junk from when the node
     * was still in the list's node chain.
     * 
     */
    template<typename T>
    Node<T>* RemoveFirstNodeFromListAndReturnIt(List<T>& p_list)
    {

        LogDebugLine("Removing the first node of list " << p_list);

        Node<T>* l_returnValue = p_list.m_FirstNode;

        if(p_list.m_Size == 0)
        {
            LogDebugLine("The given list is of size 0, returning null.");
            //Null will be returned.
            return l_returnValue;
        }

        if(p_list.m_Size == 1)
        {
            LogDebugLine("The list is of size 1 so setting first and last "
            "node to null.");
            p_list.m_FirstNode = nullptr;
            p_list.m_LastNode = nullptr;
        }
        else
        {
            LogDebugLine("Unlinking the first node and configuring the new"
            " first node.");
            p_list.m_FirstNode = p_list.m_FirstNode->m_NextNode;
            p_list.m_FirstNode->m_PreviousNode = l_returnValue->m_PreviousNode;

            if(p_list.m_LastNode->m_NextNode != nullptr)
            {
                LogDebugLine("The list is cyclic so configuring the last node.");
                p_list.m_LastNode->m_NextNode = p_list.m_FirstNode;
            }
        }

        if(p_list.m_Cache == l_returnValue)
        {
            LogDebugLine("The cache has the node that is being removed, "
            "emptying the cache.");
            p_list.m_Cache = ListCache<T>();
        }

        LogDebugLine("Decreasing the list's size and returning the old "
        "first node.");
        --p_list.m_Size;
        return l_returnValue;

    }
    /**
     * @brief Removes the last node from p_list and returns it.
     * 
     * @details Same as @ref RemoveFirstNodeFromListAndReturnIt except that the
     * last node is removed and returned.
     * 
     */
    template<typename T>
    Node<T>* RemoveLastNodeFromListAndReturnIt(List<T>& p_list)
    {

        LogDebugLine("Removing the last node of list " << p_list);

        Node<T>* l_returnValue = p_list.m_LastNode;

        if(p_list.m_Size == 0)
        {
            LogDebugLine("The given list is of size 0, returning null.");
            //Null will be returned.
            return l_returnValue;
        }

        if(p_list.m_Size == 1)
        {
            LogDebugLine("The list is of size 1 so setting first and last "
            "node to null.");
            p_list.m_FirstNode = nullptr;
            p_list.m_LastNode = nullptr;
        }
        else
        {
            LogDebugLine("Unlinking the last node and configuring the new"
            " last node.");
            p_list.m_LastNode = p_list.m_LastNode->m_PreviousNode;
            p_list.m_LastNode->m_NextNode = l_returnValue->m_NextNode;

            if(p_list.m_FirstNode->m_PreviousNode != nullptr)
            {
                LogDebugLine("The list is cyclic so configuring the first node.");
                p_list.m_FirstNode->m_PreviousNode = p_list.m_LastNode;
            }
        }
        
        if(p_list.m_Cache == l_returnValue)
        {
            LogDebugLine("The cache has the node that is being removed, "
            "emptying the cache.");
            p_list.m_Cache = ListCache<T>();
        }

        LogDebugLine("Decreasing the list's size and returning the old "
        "last node.");
        --p_list.m_Size;
        return l_returnValue;

    }
    /**
     * @brief Removes the node at p_index from p_list and returns it.
     * 
     * @details Unlinks the node at p_index and returns it. The new node at
     * p_index is set to be the old node at that index's next node. The returned
     * 
     * p_index is considered to be invalid when: p_index >= p_index.m_Size. In
     * this case the function returns null and p_index_error is called.
     * 
     * The list is properly configured in all cases(that being removing the
     * first or last node, removing the last node or leaving no more nodes
     * behind.).
     * 
     * If the list has no nodes, null is returned.
     * 
     * p_list.m_Size is reduced by 1.
     * 
     * @time O(n), n being the number of steps the function needs to take to
     * reach the node at p_index.
     * 
     * @param p_index The node at this index will be removed.
     * @param p_index_error A callback to call when p_index is invalid.
     * @param p_index_error_data Data that is passed to p_index_error,
     * @param p_list The list on which to do the removal.
     * 
     * @return The node at p_index in p_list if p_index is valid and the list
     * has a size >0, null otherwise. The returned node's next and previous node
     * pointers are not cleared.
     * 
     * @warning The returned node dose not have it's next and previous node 
     * pointers cleared, they will contain junk from when the node was still
     * apart of p_list's node chain.
     * 
     */
    template<typename T>
    Node<T>* RemoveNodeAtIndexFromListAndReturnIt(
        const Size& p_index,
        void (*p_index_error) (void*), void* p_index_error_data,
        List<T>& p_list
    )
    {

        LogDebugLine("Removing the node at index " << p_index
        << " from list " << p_list);

        if(p_index >= p_list.m_Size)
        {
            LogDebugLine("The given index is invalid.");

            if(p_index_error != nullptr)
            {
                LogDebugLine("Index error is not a null pointer so calling it.");
                p_index_error(p_index_error_data);
            }

            LogDebugLine("Returing null from removal function.");
            return nullptr;
        }

        if(p_index == 0)
        {
            LogDebugLine("The given index is 0 so calling the remove first"
            " node function and returning.");
            return RemoveFirstNodeFromListAndReturnIt(p_list);
        }
        if(p_index == p_list.m_Size - 1)
        {
            LogDebugLine("The given index is the last index so calling the"
            " remove last node function and returning.");
            return RemoveLastNodeFromListAndReturnIt(p_list);
        }

        //Cast so that it is not const, which should be valid in this contex.
        Node<T>* l_nodeAtIndex = (Node<T>*)FindNodeAtIndexNoErrorCheckInList(p_index, p_list);

        LogDebugLine("Unlinking the node at the given index.");
        l_nodeAtIndex->m_NextNode->m_PreviousNode = l_nodeAtIndex->m_PreviousNode;
        l_nodeAtIndex->m_PreviousNode->m_NextNode = l_nodeAtIndex->m_NextNode;

        LogDebugLine("Caching the node after the node that is being removed.");
        p_list.m_Cache.m_Node = l_nodeAtIndex->m_NextNode;
        p_list.m_Cache.m_NodeIndex = p_index;

        --p_list.m_Size;

        return l_nodeAtIndex;

    }

    /**
     * @brief Removes and deallocates p_list's first node.
     * 
     * @details In reality it just calls p_deallocate with the return value of
     * @ref RemoveFirstNodeFromListAndReturnIt. p_deallocate is still called
     * even if the function returns null.
     *
     * @param p_list The list from which the first node will be deallocated.
     * @param p_deallocate The function to use to deallocate the first node of 
     * p_list.
     *  
     */
    template<typename T>
    inline void RemoveFirstNodeFromListAndDeallocateItUsingDeallocator(
        List<T>& p_list,
        void (&p_deallocate) (void*)
    )
    {
        LogDebugLine("Deallocating the first node.");
        p_deallocate(RemoveFirstNodeFromListAndReturnIt(p_list));
    }
    template<typename T>
    inline void RemoveFirstNodeFromListAndDeallocateItUsingDeallocator(
        List<T>& p_list
    )
    {
        LogDebugLine("Using defaults for RemoveFirstNodeFromListAndDeallocateItUsingDeallocator.");
        RemoveFirstNodeFromListAndDeallocateItUsingDeallocator(
            p_list,
            Library::LibraryMeta::g_DEFAULT_DEALLOCATOR
        );
        LogDebugLine("Returning from defaults function.");
    }
    
    /**
     * @brief Removes and deallocates p_list's last node.
     * 
     * @details In reality it just calls p_deallocate with the return value of
     * @ref RemoveLastNodeFromListAndReturnIt. p_deallocate is still called
     * even if the function returns null.
     *
     * @param p_list The list from which the last node will be deallocated.
     * @param p_deallocate The function to use to deallocate the last node of 
     * p_list.
     *  
     */
    template<typename T>
    inline void RemoveLastNodeFromListAndDeallocateItUsingDeallocator(
        List<T>& p_list,
        void (&p_deallocate) (void*)
    )
    {
        LogDebugLine("Deallocating the last node.");
        p_deallocate(RemoveLastNodeFromListAndReturnIt(p_list));
    }
    template<typename T>
    inline void RemoveLastNodeFromListAndDeallocateItUsingDeallocator(
        List<T>& p_list
    )
    {
        LogDebugLine("Using defaults for RemoveLastNodeFromListAndDeallocateItUsingDeallocator.");
        RemoveLastNodeFromListAndDeallocateItUsingDeallocator(
            p_list,
            Library::LibraryMeta::g_DEFAULT_DEALLOCATOR
        );
        LogDebugLine("Returning from defaults function.");
    }

    /**
     * @brief Removes and deallocates the node at p_index from p_list.
     * 
     * @details In reality it just calls p_deallocate with the return value of
     * @ref RemoveNodeAtIndexFromListAndReturnIt. p_deallocate is still called
     * even if the function returns null.
     *
     * @param p_index The node at this index will be removed.
     * @param p_index_error A callback to call when p_index is invalid.
     * @param p_index_error_data Data that is passed to p_index_error,
     * @param p_list The list on which to do the removal.
     * @param p_deallocate The function to use to deallocate the node at p_index 
     * from p_list.
     *  
     */
    template<typename T>
    inline void RemoveNodeAtIndexFromListAndDeallocateItUsingDeallocator(
        const Size& p_index,
        void (*p_index_error) (void*), void* p_index_error_data,
        List<T>& p_list,
        void (&p_deallocate) (void*)
    )
    {
        LogDebugLine("Deallocating the node at the given index.");
        p_deallocate(RemoveNodeAtIndexFromListAndReturnIt(
            p_index, p_index_error, p_index_error_data,
            p_list
            )
        );
    }
    template<typename T>
    inline void RemoveNodeAtIndexFromListAndDeallocateItUsingDeallocator(
        const Size& p_index,
        void (*p_index_error) (void*), void* p_index_error_data,
        List<T>& p_list
    )
    {
        LogDebugLine("Using defaults for RemoveNodeAtIndexFromListAndDeallocateItUsingDeallocator.");
        RemoveNodeAtIndexFromListAndDeallocateItUsingDeallocator(
            p_index, p_index_error, p_index_error_data,
            p_list,
            Library::LibraryMeta::g_DEFAULT_DEALLOCATOR
        );
        LogDebugLine("Returning from defaults function.");
    }


    /**
     * @brief Destroyies p_list using p_deallocated
     * 
     * @details Loops through each node in p_list and calls p_deallocate on each
     * node in p_list. After all nodes have been deallocated creates an empty
     * list at p_list.
     * 
     * @time O(n), n being the number of elements in p_list.
     * 
     * @param p_list The list to destroy.
     * @param p_deallocate The deallocator to use in the destruction.
     * 
     * @warning This function **ASSUMES** that p_list is null terminated or is
     * empty. If p_list is any other type of list the behaviour of the function
     * is undefined.
     * 
     */
    template<typename T>
    void DestroyListUsingDeallocator(
        List<T>& p_list,
        void (&p_deallocate) (void*)
    )
    {

        LogDebugLine("Destroying list " << p_list);

        if(p_list.m_Size == 0)
        {
            LogDebugLine("The list is allready empty, returning.");
            return;
        }

        Node<T>* l_curNode = p_list.m_FirstNode;
        Node<T>* l_nextNode = nullptr;

        //This pointer needs to be stored here so that when the last node is
        //deallocated the loop does not try to read it to find out if it had
        //deallocated all nodes.
        Node<T>* l_lastNode = p_list.m_LastNode->m_NextNode;
        do
        {
            l_nextNode = l_curNode->m_NextNode;

            LogDebugLine("Destroying node at address " << (void*)l_curNode);
            p_deallocate(l_curNode);
            l_curNode = l_nextNode;
        }
        while(l_curNode != l_lastNode);

        p_list = List<T>();

        LogDebugLine("List destruction has been completed.");

    }
    template<typename T>
    inline void DestroyListUsingDeallocator(List<T>& p_list)
    {
        LogDebugLine("Using defaults for DestroyListUsingDeallocator.");
        DestroyListUsingDeallocator(
            p_list,
            Library::LibraryMeta::g_DEFAULT_DEALLOCATOR
        );
        LogDebugLine("Returning from defaults function.");
    }
    
    //TODO: More advanced destruction here mainly for calling functions on the
    //node items.

}

#endif //DOUBLY_LINKED_COUNTED_CACHED_LIST__DATA_STRUCTURES_LISTS_DOUBLY_LINKED_COUNTED_CACHED_DOUBLY_LINKED_COUNTED_CACHED_LIST_HPP
