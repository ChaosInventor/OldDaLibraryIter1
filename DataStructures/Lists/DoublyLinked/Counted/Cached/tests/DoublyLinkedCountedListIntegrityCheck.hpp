/**
 * @file DoublyLinkedCountedListIntegrityCheck.hpp
 * 
 * @brief This file is for tests only.
 * 
 * @details Defines a function that checks a doubly linked list for any flaws or
 * errors.
 * 
 */

#ifndef DOUBLY_LINKED_COUNTED_CACHED_LIST_INTEGRITY_CHECK__DATA_STRUCTURES_LISTS_DOUBLY_LINKED_COUNTED_CACHED__TESTS_DOUBLY_LINKED_COUNTED_CACHED_LIST__INTEGRITY_CHECK_HPP
#define DOUBLY_LINKED_COUNTED_CACHED_LIST_INTEGRITY_CHECK__DATA_STRUCTURES_LISTS_DOUBLY_LINKED_COUNTED_CACHED__TESTS_DOUBLY_LINKED_COUNTED_CACHED_LIST__INTEGRITY_CHECK_HPP

#include "../DoublyLinkedCountedCachedList.hpp"

template<typename T>
bool ListIntegrityIsGoodAndListSizeIsExpectedSize(
    const Library::DataStructures::Lists::DoublyLinked::Counted::Cached::
    List<T>& p_list,
    const Size& p_expected_size)
{

    LogDebugLine("Checking the integrity of list " << p_list);

    bool l_returnValue = true;

    if(p_list.m_Size != p_expected_size)
    {
        l_returnValue = false;
        LogDebugLine("The list's size(" << p_list.m_Size
        << ") is not the expected size(" << p_expected_size << ").");
    }

    //This means that the list is empty.
    if(p_list.m_Size == 0)
    {
        if(p_list.m_FirstNode != nullptr)
        {
            l_returnValue = false;
            LogDebugLine("The list is of size 0 but the first node is not null, it is " << (void*)p_list.m_FirstNode);
        }
        if(p_list.m_LastNode != nullptr)
        {
            l_returnValue = false;
            LogDebugLine("The list is of size 0 but the last node is not null, it is " << (void*)p_list.m_LastNode);
        }
        if(p_list.m_Cache.m_Node != nullptr)
        {
            l_returnValue = false;
            LogDebugLine("The list is of size 0 but the cached node is not null, it is " << (void*)p_list.m_Cache.m_Node);
        }
        if(p_list.m_Cache.m_NodeIndex != 0)
        {
            l_returnValue = false;
            LogDebugLine("The list is of size 0 but the cached index is not 0, it is " << p_list.m_Cache.m_NodeIndex);
        }

        return l_returnValue;
    }

    if(p_list.m_Size == 1)
    {
        if(p_list.m_FirstNode == nullptr)
        {
            l_returnValue = false;
            LogDebugLine("The list is of size 1 but the first node is null.");
        }
        if(p_list.m_LastNode == nullptr)
        {
            l_returnValue = false;
            LogDebugLine("The list is of size 1 but the last node is null.");
        }

        if(p_list.m_FirstNode != p_list.m_LastNode)
        {
            l_returnValue = false;
            LogDebugLine("The first node(" << (void*)p_list.m_FirstNode
            << ") and the last node(" << (void*)p_list.m_LastNode
            << ") are not the same.");

            //Return early since at this point trying anything else could be
            //dangerous so just return.
            return l_returnValue;
        }

        //The list is null terminated.
        if(p_list.m_FirstNode->m_NextNode == nullptr || p_list.m_FirstNode->m_PreviousNode == nullptr)
        {
            if(p_list.m_FirstNode->m_NextNode != nullptr || p_list.m_LastNode->m_NextNode != nullptr)
            {
                l_returnValue = false;
                LogDebugLine("One of the first node's( "
                << *p_list.m_FirstNode
                << " ) node pointers is null while the other isn't.");
            }
        }
        else //The list is cyclic.
        {
            if(p_list.m_FirstNode->m_NextNode != p_list.m_FirstNode || p_list.m_FirstNode->m_PreviousNode != p_list.m_FirstNode)
            {
                l_returnValue = false;
                LogDebugLine("One of the first node's( "
                << *p_list.m_FirstNode
                << " ) node pointers is not the first node it's self.");
            }
        }

        if(p_list.m_Cache != nullptr)
        {
            if(p_list.m_Cache != p_list.m_FirstNode)
            {
                l_returnValue = false;
                LogDebugLine("The cached node is not the first node, it is "
                << (void*)p_list.m_Cache.m_Node);
            }
        }
        if(p_list.m_Cache.m_NodeIndex != 0)
        {
            l_returnValue = false;
            LogDebugLine("The cached index is not 0, it is " << p_list.m_Cache.m_NodeIndex);
        }

        return l_returnValue;
    }

    //The list from here on out is of size >1

    if(p_list.m_FirstNode == nullptr)
    {
        l_returnValue = false;
        LogDebugLine("The list is of size " << p_list.m_Size
        << " but the first node is null.");
        //Can't make any more checks after this point.
        return l_returnValue;
    }
    if(p_list.m_LastNode == nullptr)
    {
        l_returnValue = false;
        LogDebugLine("The list is of size " << p_list.m_Size
        << " but the last node is null.");
        //Can't make any more checks after this point.
        return l_returnValue;
    }

    //The list is null terminated.
    if(p_list.m_LastNode->m_NextNode == nullptr || p_list.m_FirstNode->m_PreviousNode == nullptr)
    {
        if(p_list.m_LastNode->m_NextNode != nullptr)
        {
            l_returnValue = false;
            LogDebugLine("The last node's next node is not null(it is "
            << (void*)p_list.m_LastNode->m_NextNode << " ) while the first node's "
            "previous node is null.");
            //No more checks can be made safely.
            return l_returnValue;
        }
        if(p_list.m_FirstNode->m_PreviousNode != nullptr)
        {
            l_returnValue = false;
            LogDebugLine("The first node's previous node is not null(it is "
            << (void*)p_list.m_FirstNode->m_PreviousNode << " ) while the first node's "
            "next node is null.");
            //No more checks can be made safely.
            return l_returnValue;
        }
    }
    else //The list is cyclic.
    {
        if(p_list.m_FirstNode->m_PreviousNode != p_list.m_LastNode)
        {
            l_returnValue = false;
            LogDebugLine("The first node's previous node is not the list's"
            " last node, it is " << (void*)p_list.m_FirstNode->m_PreviousNode);
            //No more checks can be safely made.
            return l_returnValue;
        }
        if(p_list.m_LastNode->m_NextNode != p_list.m_FirstNode)
        {
            l_returnValue = false;
            LogDebugLine("The last node's next node is not the list's"
            " first node, it is " << (void*)p_list.m_LastNode->m_NextNode);
            //No more checks can be safely made.
            return l_returnValue;
        }
    }

    Size l_countedSize = 0;
    Library::DataStructures::Lists::DoublyLinked::
    Node<T>* l_curNode = p_list.m_FirstNode;
    Library::DataStructures::Lists::DoublyLinked::
    Node<T>* l_previousNode;
    //Depending on if the list is cyclic or null terminated, the first node must
    //point back to diffrent things.
    if(p_list.m_LastNode->m_NextNode ==  nullptr) //The list is null terminated.
    {
        l_previousNode = nullptr;
    }
    else //The list is cyclic.
    {
        l_previousNode = p_list.m_LastNode;
    }

    bool l_isCachedInList = false;

    do
    {
        if(l_curNode == nullptr)
        {
            l_returnValue = false;
            LogDebugLine("The end of the list has not been reached yet a "
            "null node has been encountered. The counted size is "
            << l_countedSize << " the last node address is "
            << (void*)l_previousNode);
            //No more checking can be done safely.
            return l_returnValue;
        }

        if(l_curNode == p_list.m_Cache.m_Node)
        {
            if(l_isCachedInList)
            {
                l_returnValue = false;
                LogDebugLine("Found the cached node in the list more than "
                "once.");
            }
            l_isCachedInList = true;

            if(l_countedSize != p_list.m_Cache.m_NodeIndex)
            {
                l_returnValue = false;
                LogDebugLine("Found the cached node, but it's index( " 
                << p_list.m_Cache.m_NodeIndex << " ) is not the expected index(" 
                << l_countedSize << ").");
            }
        }

        if(l_curNode->m_PreviousNode != l_previousNode)
        {
            l_returnValue = false;
            LogDebugLine("The node " << *l_curNode << " does not point "
            "back to the node at " << (void*)l_previousNode << ", the counted "
            "size is " << l_countedSize);
        }

        l_previousNode = l_curNode;
        l_curNode = l_curNode->m_NextNode;
        ++l_countedSize;
    }
    while (l_curNode != p_list.m_LastNode->m_NextNode);
    
    if(l_countedSize != p_list.m_Size)
    {
        l_returnValue = false;
        LogDebugLine("The counted size( " << l_countedSize << " ) is not "
        "the same as the list's size( " << p_list.m_Size << " ).");
    }
    if(p_expected_size != l_countedSize)
    {
        l_returnValue = false;
        LogDebugLine("The counted size( " << l_countedSize << " ) is not "
        "the same as the expected size( " << p_expected_size << " ).");
    }

    if(p_list.m_Cache == nullptr)
    {
        if(p_list.m_Cache.m_NodeIndex != 0)
        {
            l_returnValue = false;
            LogDebugLine("The cached node is null, but the index is "
            << p_list.m_Cache.m_NodeIndex);
        }
    }
    else
    {
        if(l_isCachedInList == false)
        {
            l_returnValue = false;
            LogDebugLine("Could not find the cached node( "
            << (void*)p_list.m_Cache.m_Node << " ) in the list.");
        }
        if(p_list.m_Cache.m_NodeIndex >= l_countedSize)
        {
            l_returnValue = false;
            LogDebugLine("The cached node's index( "
            << p_list.m_Cache.m_NodeIndex << " ) is out of range of the counted"
            " size( " << l_countedSize << " ).");
        }
    }
    
    //If the code reaches this point without setting l_returnValue to false then
    //the list is ok.
    return l_returnValue;

}

#endif//DOUBLY_LINKED_COUNTED_CACHED_LIST_INTEGRITY_CHECK__DATA_STRUCTURES_LISTS_DOUBLY_LINKED_COUNTED_CACHED__TESTS_DOUBLY_LINKED_COUNTED_CACHED_LIST__INTEGRITY_CHECK_HPP