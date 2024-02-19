#include <catch2/catch.hpp>

#include "../DoublyLinkedCountedCachedList.hpp"

using namespace Library::DataStructures::Lists::DoublyLinked::Counted::Cached;
using namespace Library::DataStructures::Lists::DoublyLinked;
using namespace Catch::Generators;


TEST_CASE("Get node at index", "[DoublyLinked][Counted][Cached][List][Immutable]")
{

    Size l_size = GENERATE(range(0, 100));
    
    List<int> l_list;
    SECTION("Cyclic")
    {
        CreateCyclicListAtOfSizeUsingAllocator(l_list, l_size);
    }
    SECTION("Null terminated")
    {
        CreateNullTerminatedListAtOfSizeUsingAllocator(l_list, l_size);
    }
    REQUIRE(l_list.m_Size == l_size);

    Node<int>* l_oldCachedNode = l_list.m_Cache.m_Node;
    Size l_oldCachedIndex = l_list.m_Cache.m_NodeIndex;

    Node<int>* l_curNode = l_list.m_FirstNode;
    for(Size i = 0; i < l_size; ++i)
    {
        CHECK(l_curNode == FindNodeAtIndexNoErrorCheckInList(i, l_list));
        CHECK(l_list.m_Cache.m_Node == l_oldCachedNode);
        CHECK(l_list.m_Cache.m_NodeIndex == l_oldCachedIndex);

        CHECK(l_curNode == FindNodeAtIndexNoErrorCheckInListAndUpdateCache(i, l_list));
        CHECK(l_list.m_Cache.m_Node == l_curNode);
        CHECK(l_list.m_Cache.m_NodeIndex == i);

        l_oldCachedNode = l_curNode;
        l_oldCachedIndex = i;
        
        l_curNode = l_curNode->m_NextNode;
    }

    DestroyListUsingDeallocator(l_list);

}

TEST_CASE("Find and contains", "[DoublyLinked][Counted][Cached][List][Immutable]")
{

    List<int> l_list;
    SECTION("Cyclic")
    {
        CreateCyclicListAtOfSizeUsingAllocator(l_list, 10);
    }
    SECTION("Null terminated")
    {
        CreateNullTerminatedListAtOfSizeUsingAllocator(l_list, 10);
    }
    //In case of alloc error.
    REQUIRE(l_list.m_Size == 10);

    List<int> l_empty;

    l_list[1] = 523;
    l_list[7] = 280;
    l_list[9] = 523;

    CHECK(FindIndexOfFirstOccurrenceOfItemInList(523, l_list) == 1);
    CHECK(FindIndexOfFirstOccurrenceOfItemInList(143, l_list) == l_list.m_Size);
    CHECK(FindIndexOfFirstOccurrenceOfItemInList(523, l_empty) == l_empty.m_Size);
    CHECK(FindIndexOfFirstOccurrenceOfItemInList(9321, l_empty) == l_empty.m_Size);

    CHECK(FindIndexOfLastOccurrenceOfItemInList(523, l_list) == 9);
    CHECK(FindIndexOfLastOccurrenceOfItemInList(143, l_list) == l_list.m_Size);
    CHECK(FindIndexOfLastOccurrenceOfItemInList(523, l_empty) == l_empty.m_Size);
    CHECK(FindIndexOfLastOccurrenceOfItemInList(9321, l_empty) == l_empty.m_Size);


    CHECK(FindNodeWithFirstOccurrenceOfItemInList(523, l_list) == l_list.m_FirstNode->m_NextNode);
    CHECK(FindNodeWithFirstOccurrenceOfItemInList(143, l_list) == nullptr);
    CHECK(FindNodeWithFirstOccurrenceOfItemInList(523, l_empty) == nullptr);
    CHECK(FindNodeWithFirstOccurrenceOfItemInList(9321, l_empty) == nullptr);

    CHECK(FindNodeWithLastOccurrenceOfItemInList(523, l_list) == l_list.m_LastNode);
    CHECK(FindNodeWithLastOccurrenceOfItemInList(143, l_list) == nullptr);
    CHECK(FindNodeWithLastOccurrenceOfItemInList(523, l_empty) == nullptr);
    CHECK(FindNodeWithLastOccurrenceOfItemInList(9321, l_empty) == nullptr);


    CHECK(ListContainsItem(l_list, 523) == true);
    CHECK(ListContainsItem(l_list, 143) == false);
    CHECK(ListContainsItem(l_empty, 523) == false);
    CHECK(ListContainsItem(l_empty, 9321) == false);

    Node<int> l_dummy1;
    Node<int> l_dummy2;
    CHECK(ListContainsNode(l_list, *l_list.m_FirstNode->m_NextNode->m_NextNode) == true);
    CHECK(ListContainsNode(l_list, l_dummy1) == false);
    CHECK(ListContainsNode(l_empty, l_dummy2) == false);
    CHECK(ListContainsNode(l_empty, *l_list.m_FirstNode) == false);

    DestroyListUsingDeallocator(l_list);

}
