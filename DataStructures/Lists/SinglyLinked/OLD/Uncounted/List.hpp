#ifndef SINGLY_LINKED_UNCOUNTED_LIST__DATA_STRUCTURES_LISTS_SINGLY_LINKED_UNCOUNTED_LIST_HPP
#define SINGLY_LINKED_UNCOUNTED_LIST__DATA_STRUCTURES_LISTS_SINGLY_LINKED_UNCOUNTED_LIST_HPP

#include "../../../../Meta/Meta.hpp"
#include "../Node.hpp"

namespace Library::DataStructures::Lists::SinglyLinked::Uncounted
{

    #ifdef DEBUG
    //TODO: << operator for log and list.
    #endif //DEBUG



    template<typename T>
    struct List
    {

        Node<T>* m_FirstNode;

        List():
        m_FirstNode(nullptr),
        m_LastNode(nullptr)
        {
            LogDebugLine("Constructed default singly linked uncounted list at "
            << (void*)this);
        }
        List(Node<T>* p_first_node, Node<T>* p_last_node):
        m_FirstNode(p_first_node),
        m_LastNode(p_last_node)
        {
            LogDebugLine("Constructed default singly linked uncounted list at "
            << (void*)this << " with first node at " << (void*)p_first_node
            << " and last node at " << (void*)p_last_node);
        }

        List(const List<T>& p_other):
        m_FirstNode(p_other.m_FirstNode),
        m_LastNode(p_other.m_LastNode)
        {
            LogDebugLine("Constructed singly linked uncounted list at "
            << (void*)this << " by copying from list " << p_other);
        }
        List(List<T>&& p_other):
        m_FirstNode(p_other.m_FirstNode),
        m_LastNode(p_other.m_LastNode)
        {
            p_other.m_FirstNode = nullptr;
            p_other.m_LastNode = nullptr;

            LogDebugLine("Constructed singly linked uncounted list at "
            << (void*)this << " by moving from list " << p_other);
        }

        
        List<T>& operator=(const List<T>& p_other)
        {

            LogDebugLine("Copying from singly linked uncounted list "
            << p_other << " to list " << *this);
        
            m_FirstNode = p_other.m_FirstNode;
            m_LastNode = p_other.m_LastNode;

        }
        List<T>& operator=(List<T>&& p_other)
        {

            LogDebugLine("Moving from singly linked uncounted list "
            << p_other << " to list " << *this);
        
            m_FirstNode = p_other.m_FirstNode;
            m_LastNode = p_other.m_LastNode;

            p_other.m_FirstNode = nullptr;
            p_other.m_LastNode = nullptr;

        }

    };

    template<typename T>
    Node<T>* FindNodeAtIndexNoErrorCheckFromList(
        const Size& p_index,
        const List<T>& p_list
    )
    {

        LogDebugLine("Finding node at index " << p_index
        << " in singly linked uncounted list " << p_list);

        Node<T>* l_returnValue = p_list.m_FirstNode;
        for(size_t i = 0; i < p_index; ++i)
        {
            l_returnValue = l_returnValue->m_NextNode;
        }

        return l_returnValue;

    }



}

#endif SINGLY_LINKED_UNCOUNTED_LIST__DATA_STRUCTURES_LISTS_SINGLY_LINKED_UNCOUNTED_LIST_HPP