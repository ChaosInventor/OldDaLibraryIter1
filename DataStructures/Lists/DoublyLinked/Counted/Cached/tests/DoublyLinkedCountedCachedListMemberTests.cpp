#include <catch2/catch.hpp>

#include "../DoublyLinkedCountedCachedList.hpp"

using namespace Library::DataStructures::Lists::DoublyLinked::Counted::Cached;
using namespace Library::DataStructures::Lists::DoublyLinked;

TEST_CASE("List default constructor", "[DoublyLinked][Counted][Cached][List][Member]")
{

    List<int> l_list;

    CHECK(l_list.m_FirstNode == nullptr);
    CHECK(l_list.m_LastNode == nullptr);
    CHECK(l_list.m_Size == 0);
    CHECK(l_list.m_Cache == ListCache<int>());

}

TEST_CASE("List first and last node constructor", "[DoublyLinked][Counted][Cached][List][Member]")
{

    Node<int>* l_firstNode;
    Node<int>* l_lastNode;
    Size l_size;

    Node<int> l_node1;
    Node<int> l_node2;
    Node<int> l_node3;
    Node<int> l_node4;

    SECTION("Cyclic list")
    {
        l_node1.m_PreviousNode = &l_node4;
        l_node1.m_NextNode = &l_node2;

        l_node2.m_PreviousNode = &l_node1;
        l_node2.m_NextNode = &l_node3;

        l_node3.m_PreviousNode = &l_node2;
        l_node3.m_NextNode = &l_node4;

        l_node4.m_PreviousNode = &l_node3;
        l_node4.m_NextNode = &l_node1;

        l_firstNode = &l_node1;
        l_lastNode = &l_node4;
        l_size = 4;

    }
    SECTION("Null term list")
    {
        l_node1.m_PreviousNode = nullptr;
        l_node1.m_NextNode = &l_node2;

        l_node2.m_PreviousNode = &l_node1;
        l_node2.m_NextNode = &l_node3;

        l_node3.m_PreviousNode = &l_node2;
        l_node3.m_NextNode = nullptr;
    
        l_firstNode = &l_node1;
        l_lastNode = &l_node3;
        l_size = 3;
    }
    SECTION("Empty list")
    {
        l_firstNode = nullptr;
        l_lastNode = nullptr;
        l_size = 0;
    }

    List<int> l_list(l_firstNode, l_lastNode);

    CHECK(l_list.m_FirstNode == l_firstNode);
    CHECK(l_list.m_LastNode == l_lastNode);
    CHECK(l_list.m_Size == l_size);
    CHECK(l_list.m_Cache == ListCache<int>());

}

TEST_CASE("List first, last node and size constructor", "[DoublyLinked][Counted][Cached][List][Member]")
{

    Node<int> l_dummy1;
    Node<int> l_dummy2;
    Size l_dummySize = 23;

    List<int> l_list(&l_dummy1, &l_dummy2, l_dummySize);

    CHECK(l_list.m_FirstNode == &l_dummy1);
    CHECK(l_list.m_LastNode == &l_dummy2);
    CHECK(l_list.m_Size == l_dummySize);
    CHECK(l_list.m_Cache == ListCache<int>());

}

TEST_CASE("Copying and moving list", "[DoublyLinked][Counted][Cached][List][Member]")
{

    Node<int> l_dummy1;
    Node<int> l_dummy2;
    Size l_dummySize = 23;

    List<int> l_from(&l_dummy1, &l_dummy2, l_dummySize);
    List<int> l_to;

    SECTION("Copy constructor")
    {
        l_to = List<int>(l_from);
    }
    SECTION("Copy operator")
    {
        l_to = l_from;
    }
    SECTION("Move constructor")
    {
        l_to = List<int>((List<int>&&)l_from);

        CHECK(l_from.m_FirstNode == nullptr);
        CHECK(l_from.m_LastNode == nullptr);
        CHECK(l_from.m_Size == 0);
        CHECK(l_from.m_Cache == ListCache<int>());
    }
    SECTION("Move operator")
    {
        l_to = (List<int>&&)l_from;

        CHECK(l_from.m_FirstNode == nullptr);
        CHECK(l_from.m_LastNode == nullptr);
        CHECK(l_from.m_Size == 0);
        CHECK(l_from.m_Cache == ListCache<int>());
    }

    CHECK(l_to.m_FirstNode == &l_dummy1);
    CHECK(l_to.m_LastNode == &l_dummy2);
    CHECK(l_to.m_Size == l_dummySize);
    CHECK(l_to.m_Cache == ListCache<int>());

}

TEST_CASE("Comparison of lists", "[DoublyLinked][Counted][Cached][List][Member]")
{

    //For l_list
    Node<int> l_node1;
    Node<int> l_node2;
    Node<int> l_node3;
    Node<int> l_node4;

    l_node1.m_PreviousNode = &l_node4;
    l_node1.m_NextNode = &l_node2;
    l_node1.m_Item = 1;

    l_node2.m_PreviousNode = &l_node1;
    l_node2.m_NextNode = &l_node3;
    l_node2.m_Item = 2;

    l_node3.m_PreviousNode = &l_node2;
    l_node3.m_NextNode = &l_node4;
    l_node3.m_Item = 3;

    l_node4.m_PreviousNode = &l_node3;
    l_node4.m_NextNode = &l_node1;
    l_node4.m_Item = 4;


    //For l_sameCyclic
    Node<int> l_2node1;
    Node<int> l_2node2;
    Node<int> l_2node3;
    Node<int> l_2node4;

    l_2node1.m_PreviousNode = &l_2node4;
    l_2node1.m_NextNode = &l_2node2;
    l_2node1.m_Item = 1;

    l_2node2.m_PreviousNode = &l_2node1;
    l_2node2.m_NextNode = &l_2node3;
    l_2node2.m_Item = 2;

    l_2node3.m_PreviousNode = &l_2node2;
    l_2node3.m_NextNode = &l_2node4;
    l_2node3.m_Item = 3;

    l_2node4.m_PreviousNode = &l_2node3;
    l_2node4.m_NextNode = &l_2node1;
    l_2node4.m_Item = 4;


    //For l_sameNullTerm
    Node<int> l_3node1;
    Node<int> l_3node2;
    Node<int> l_3node3;
    Node<int> l_3node4;

    l_3node1.m_PreviousNode = nullptr;
    l_3node1.m_NextNode = &l_3node2;
    l_3node1.m_Item = 1;

    l_3node2.m_PreviousNode = &l_3node1;
    l_3node2.m_NextNode = &l_3node3;
    l_3node2.m_Item = 2;

    l_3node3.m_PreviousNode = &l_3node2;
    l_3node3.m_NextNode = &l_3node4;
    l_3node3.m_Item = 3;

    l_3node4.m_PreviousNode = &l_3node3;
    l_3node4.m_NextNode = nullptr;
    l_3node4.m_Item = 4;


    //For l_differentItems
    Node<int> l_4node1;
    Node<int> l_4node2;
    Node<int> l_4node3;
    Node<int> l_4node4;

    l_4node1.m_PreviousNode = nullptr;
    l_4node1.m_NextNode = &l_4node2;
    l_4node1.m_Item = 5;

    l_4node2.m_PreviousNode = &l_4node1;
    l_4node2.m_NextNode = &l_4node3;
    l_4node2.m_Item = 6;

    l_4node3.m_PreviousNode = &l_4node2;
    l_4node3.m_NextNode = &l_4node4;
    l_4node3.m_Item = 7;

    l_4node4.m_PreviousNode = &l_4node3;
    l_4node4.m_NextNode = nullptr;
    l_4node4.m_Item = 8;


    //For l_differentSizes
    Node<int> l_5node1;
    Node<int> l_5node2;
    Node<int> l_5node3;

    l_5node1.m_PreviousNode = &l_5node3;
    l_5node1.m_NextNode = &l_5node2;
    l_5node1.m_Item = 1;

    l_5node2.m_PreviousNode = &l_5node1;
    l_5node2.m_NextNode = &l_5node3;
    l_5node2.m_Item = 2;

    l_5node3.m_PreviousNode = &l_5node2;
    l_5node3.m_NextNode = &l_5node1;
    l_5node3.m_Item = 3;


    List<int> l_list(&l_node1, &l_node4);
    
    List<int> l_sameCyclic(&l_2node1, &l_2node4);
    List<int> l_sameNullTerm(&l_3node1, &l_3node4);

    List<int> l_differentItems(&l_4node1, &l_4node4);
    List<int> l_differentSize(&l_5node1, &l_5node3);

    List<int> l_empty1;
    List<int> l_empty2;

    CHECK((l_list == l_sameCyclic));
    CHECK((l_list == l_sameNullTerm));
    CHECK_FALSE((l_list == l_differentItems));
    CHECK_FALSE((l_list == l_differentSize));
    CHECK_FALSE((l_list == l_empty1));
    CHECK((l_empty1 == l_empty2));
    CHECK((l_list == l_list));

    CHECK_FALSE((l_list != l_sameCyclic));
    CHECK_FALSE((l_list != l_sameNullTerm));
    CHECK((l_list != l_differentItems));
    CHECK((l_list != l_differentSize));
    CHECK((l_list != l_empty1));
    CHECK_FALSE((l_empty1 != l_empty2));
    CHECK_FALSE((l_list != l_list));


}

TEST_CASE("Get item at index", "[DoublyLinked][Counted][Cached][List][Member]")
{

    Node<int> l_node1;
    Node<int> l_node2;
    Node<int> l_node3;
    Node<int> l_node4;

    SECTION("Null terminated")
    {
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
    }
    SECTION("Cyclic")
    {
        l_node1.m_PreviousNode = &l_node4;
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
        l_node4.m_NextNode = &l_node1;
    }

    List<int> l_list(&l_node1, &l_node4);
    const List<int> l_constList(&l_node1, &l_node4);

    Node<int>* l_oldCachedNode = l_constList.m_Cache.m_Node;
    Size l_oldCachedIndex = l_constList.m_Cache.m_NodeIndex;

    Node<int>* l_expectedCachedNode = l_list.m_FirstNode;
    Size l_expectedCachedIndex = 0;

    for(Size i = 0; i < l_list.m_Size; ++i)
    {
        int l_item1 = l_list[i];
        int l_item2 = l_constList[i];

        CHECK(l_item1 == (int)i + 1);
        CHECK(l_item2 == (int)i + 1);

        CHECK(l_constList.m_Cache == l_oldCachedNode);
        CHECK(l_constList.m_Cache == l_oldCachedIndex);
        
        CHECK(l_list.m_Cache == l_expectedCachedNode);
        CHECK(l_list.m_Cache == l_expectedCachedIndex);

        l_expectedCachedNode = l_expectedCachedNode->m_NextNode;
        ++l_expectedCachedIndex;
    }

}
