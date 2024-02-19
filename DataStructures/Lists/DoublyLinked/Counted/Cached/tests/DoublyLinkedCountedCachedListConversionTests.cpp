#include <catch2/catch.hpp>

#include "../DoublyLinkedCountedCachedList.hpp"
#include "DoublyLinkedCountedListIntegrityCheck.hpp"

using namespace Library::DataStructures::Lists::DoublyLinked::Counted::Cached;
using namespace Library::DataStructures::Lists::DoublyLinked;



TEST_CASE("Convert from and to null terminated and cyclic", "[DoublyLinked][List][Counted][Cached][Conversion]")
{

    Node<int> l_node1;
    Node<int> l_node2;
    Node<int> l_node3;
    Node<int> l_node4;

    l_node1.m_PreviousNode = nullptr;
    l_node1.m_Item = 1;
    l_node1.m_NextNode = &l_node2;
    
    l_node2.m_PreviousNode = &l_node1;
    l_node2.m_Item = 2;
    l_node2.m_NextNode = &l_node3;

    l_node3.m_PreviousNode = &l_node2;
    l_node3.m_Item = 3;
    l_node3.m_NextNode = &l_node4;

    l_node4.m_PreviousNode = &l_node3;
    l_node4.m_Item = 4;
    l_node4.m_NextNode = nullptr;
    
    Node<int> l_node5;
    Node<int> l_node6;
    Node<int> l_node7;
    Node<int> l_node8;

    l_node5.m_PreviousNode = &l_node8;
    l_node5.m_Item = 1;
    l_node5.m_NextNode = &l_node6;
    
    l_node6.m_PreviousNode = &l_node5;
    l_node6.m_Item = 2;
    l_node6.m_NextNode = &l_node7;

    l_node7.m_PreviousNode = &l_node6;
    l_node7.m_Item = 3;
    l_node7.m_NextNode = &l_node8;

    l_node8.m_PreviousNode = &l_node7;
    l_node8.m_Item = 4;
    l_node8.m_NextNode = &l_node5;
    
    List<int> l_nullTerminatedList(&l_node1, &l_node4);
    List<int> l_cyclicList(&l_node5, &l_node8);
    
    ConvertCyclicListToNullTerminatedList(l_cyclicList);
    ConvertNullTerminatedListToCyclicList(l_nullTerminatedList);

    REQUIRE(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_cyclicList, 4));
    REQUIRE(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_nullTerminatedList, 4));

    //The list has become cyclic.
    CHECK(l_nullTerminatedList.m_LastNode->m_NextNode == l_nullTerminatedList.m_FirstNode);
    CHECK(l_nullTerminatedList.m_FirstNode->m_PreviousNode == l_nullTerminatedList.m_LastNode);

    //The list has become null terminated.
    CHECK(l_cyclicList.m_FirstNode->m_PreviousNode == nullptr);
    CHECK(l_cyclicList.m_LastNode->m_NextNode == nullptr);

}

