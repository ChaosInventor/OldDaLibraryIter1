#include <catch2/catch.hpp>

#include "../List.hpp"
#include "../../../../../../Debugging/Debugging.hpp"

using namespace Debugging;
using namespace Library::DataStructures::Lists::SinglyLinked::Linear::Uncounted;
using namespace Library::DataStructures::Lists::SinglyLinked;
using namespace Library;
using namespace Catch::Generators;


TEST_CASE("Insert to null list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    int l_item = GENERATE(take(1, random(INT_MIN, INT_MAX)));

    Node<int> l_node;
    l_node.m_NextNode = (Node<int>*)0xdeadbeef;
    l_node.m_Item = l_item;

    List<int> l_list;

    SECTION("Insert to start")
    {
        InsertNodeToStartOfList(l_node, l_list);
    }
    SECTION("Insert to end")
    {
        InsertNodeToEndOfList(l_node, l_list);
    }

    CHECK(l_list.m_FirstNode == &l_node);
    CHECK(l_list.m_LastNode == &l_node);
    CHECK(l_node.m_NextNode == nullptr);
    CHECK(l_node.m_Item == l_item);

}

TEST_CASE("Insert to start of list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    Size l_sizeOfList = GENERATE(take(10, random(1, 1000)));
    int l_item = GENERATE(take(1, random(INT_MIN, INT_MAX)));

    Node<int>* l_node = (Node<int>*)malloc(sizeof(Node<int>));
    REQUIRE(l_node != nullptr);

    l_node->m_NextNode = (Node<int>*)0xdeadbeef;
    l_node->m_Item = l_item;

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    Node<int>* l_oldFirstNode = l_list.m_FirstNode;

    InsertNodeToStartOfList(*l_node, l_list);

    REQUIRE(l_list.m_FirstNode != nullptr);
    REQUIRE(l_list.m_LastNode != nullptr);

    CHECK(l_list.m_FirstNode == l_node);

    CHECK(l_node->m_NextNode == l_oldFirstNode);
    CHECK(l_node->m_Item == l_item);

    CHECK(FindNumberOfNodesInList(l_list) == l_sizeOfList + 1);

    DestroyList(l_list);

}

TEST_CASE("Insert to end of list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    Size l_sizeOfList = GENERATE(take(10, random(1, 1000)));
    int l_item = GENERATE(take(1, random(INT_MIN, INT_MAX)));

    Node<int>* l_node = (Node<int>*)malloc(sizeof(Node<int>));
    REQUIRE(l_node != nullptr);

    l_node->m_NextNode = (Node<int>*)0xdeadbeef;
    l_node->m_Item = l_item;

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    InsertNodeToEndOfList(*l_node, l_list);

    REQUIRE(l_list.m_FirstNode != nullptr);
    REQUIRE(l_list.m_LastNode != nullptr);

    CHECK(l_list.m_LastNode == l_node);

    CHECK(l_node->m_NextNode == nullptr);
    CHECK(l_node->m_Item == l_item);

    CHECK(FindNumberOfNodesInList(l_list) == l_sizeOfList + 1);

    DestroyList(l_list);

}

TEST_CASE("Insert after index of list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    Size l_sizeOfList = GENERATE(take(10, random(2, 1000)));
    Size l_index = GENERATE_COPY(take<Size>(10, random<Size>(0, l_sizeOfList - 1)));
    int l_item = GENERATE(take(1, random(INT_MIN, INT_MAX)));

    Node<int>* l_node = (Node<int>*)malloc(sizeof(Node<int>));
    REQUIRE(l_node != nullptr);

    l_node->m_NextNode = (Node<int>*)0xdeadbeef;
    l_node->m_Item = l_item;

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    Node<int>* l_nodeAtIndex = FindNodeAtIndexNoErrorCheckFromList(l_index, l_list);
    Node<int>* l_nodeAtIndexOldNextNode = l_nodeAtIndex->m_NextNode;

    InsertNodeAfterIndexNoErrorCheckOfList(*l_node, l_index, l_list);

    CHECK(l_nodeAtIndex->m_NextNode == l_node);

    CHECK(l_node->m_NextNode == l_nodeAtIndexOldNextNode);
    CHECK(l_node->m_Item == l_item);

    CHECK(FindNumberOfNodesInList(l_list) == l_sizeOfList + 1);

    DestroyList(l_list);

}

TEST_CASE("Insert after last index of list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    Size l_sizeOfList = GENERATE(take(10, random(1, 1000)));
    int l_item = GENERATE(take(1, random(INT_MIN, INT_MAX)));

    Node<int>* l_node = (Node<int>*)malloc(sizeof(Node<int>));
    REQUIRE(l_node != nullptr);

    l_node->m_NextNode = (Node<int>*)0xdeadbeef;
    l_node->m_Item = l_item;

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    Node<int>* l_oldLastNode = l_list.m_LastNode;

    InsertNodeAfterIndexNoErrorCheckOfList(*l_node, l_sizeOfList - 1, l_list);

    CHECK(l_oldLastNode->m_NextNode == l_node);

    CHECK(l_node->m_Item == l_item);
    CHECK(l_node->m_NextNode == nullptr);

    CHECK(l_list.m_LastNode == l_node);
    CHECK(FindNumberOfNodesInList(l_list) == l_sizeOfList + 1);

    DestroyList(l_list);

}


//None of the add tests do checks for if the node is properly linked since that
//is done by the insert functions which are called by the add functions.
TEST_CASE("Add to null list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    int l_item = GENERATE(take(1, random(INT_MIN, INT_MAX)));

    List<int> l_list;

    SECTION("Add to start")
    {
        SECTION("Defaults")
        {
            AddItemToStartOfList(l_item, l_list);
        }
        SECTION("Customs")
        {
            bool l_called = false;
            AddItemToStartOfListUsingAllocator(l_item, l_list, malloc, &GeneralErrorCallback, &l_called);
            CHECK(l_called == false);
        }
    }
    SECTION("Add to end")
    {
        SECTION("Defaults")
        {
            AddItemToEndOfList(l_item, l_list);
        }
        SECTION("Customs")
        {
            bool l_called = false;
            AddItemToEndOfListUsingAllocator(l_item, l_list, malloc, &GeneralErrorCallback, &l_called);
            CHECK(l_called == false);
        }
    }

    REQUIRE(l_list.m_FirstNode != nullptr);
    CHECK(l_list.m_FirstNode->m_Item == l_item);

    DestroyList(l_list);

}

TEST_CASE("Add to start of list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    Size l_sizeOfList = GENERATE(take(10, random(1, 1000)));
    int l_item = GENERATE(take(1, random(INT_MIN, INT_MAX)));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    l_list.m_FirstNode->m_Item = 0;

    SECTION("Defaults")
    {
        AddItemToStartOfList(l_item, l_list);
    }
    SECTION("Customs")
    {
        bool l_called = false;
        AddItemToStartOfListUsingAllocator(l_item, l_list, malloc, &GeneralErrorCallback, &l_called);
        CHECK(l_called == false);
    }

    REQUIRE(l_list.m_FirstNode != nullptr);
    CHECK(l_list.m_FirstNode->m_Item == l_item);

    DestroyList(l_list);

}

TEST_CASE("Add to end of list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    Size l_sizeOfList = GENERATE(take(10, random(1, 1000)));
    int l_item = GENERATE(take(1, random(INT_MIN, INT_MAX)));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    l_list.m_LastNode->m_Item = 0;

    SECTION("Defaults")
    {
        AddItemToEndOfList(l_item, l_list);
    }
    SECTION("Customs")
    {
        bool l_called = false;
        AddItemToEndOfListUsingAllocator(l_item, l_list, malloc, &GeneralErrorCallback, &l_called);
        CHECK(l_called == false);
    }

    REQUIRE(l_list.m_LastNode != nullptr);
    CHECK(l_list.m_LastNode->m_Item == l_item);

    DestroyList(l_list);

}

TEST_CASE("Add after index of list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    Size l_sizeOfList = GENERATE(take(10, random(2, 1000)));
    Size l_index = GENERATE_COPY(take<Size>(10, random<Size>(0, l_sizeOfList - 1)));
    int l_item = GENERATE(take(1, random(INT_MIN, INT_MAX)));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    Node<int>* l_nodeAtIndex = FindNodeAtIndexNoErrorCheckFromList(l_index, l_list);
    l_nodeAtIndex->m_Item = 0;

    SECTION("Defaults")
    {
        AddItemAfterIndexNoErrorCheckOfList(l_item, l_index, l_list);
    }
    SECTION("Customs")
    {
        bool l_called = false;
        AddItemAfterIndexNoErrorCheckOfListUsingAllocator(
            l_item,
            l_index,
            l_list,
            malloc, &GeneralErrorCallback, &l_called
        );
        CHECK(l_called == false);
    }

    REQUIRE(l_nodeAtIndex->m_NextNode != nullptr);
    CHECK(l_nodeAtIndex->m_NextNode->m_Item == l_item);

    DestroyList(l_list);

}

TEST_CASE("Add alloc error", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    Size l_sizeOfList = GENERATE(take(10, random(2, 1000)));
    Size l_index = GENERATE_COPY(take<Size>(10, random<Size>(0, l_sizeOfList - 1)));
    int l_item = GENERATE(take(1, random(INT_MIN, INT_MAX)));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    bool l_called = false;

    SECTION("Add to start")
    {
        AddItemToStartOfListUsingAllocator(
            l_item,
            l_list,
            NullMalloc, &GeneralErrorCallback, &l_called
        );
    }
    SECTION("Add to end")
    {
        AddItemToEndOfListUsingAllocator(
            l_item,
            l_list,
            NullMalloc, &GeneralErrorCallback, &l_called
        );
    }
    SECTION("Add to start")
    {
        AddItemAfterIndexNoErrorCheckOfListUsingAllocator(
            l_item,
            l_index,
            l_list,
            NullMalloc, &GeneralErrorCallback, &l_called
        );
    }

    CHECK(l_called == true);
    CHECK(FindNumberOfNodesInList(l_list) == l_sizeOfList);

    DestroyList(l_list);

}


TEST_CASE("Extract from null list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    List<int> l_list;

    Node<int>* l_returnValue = (Node<int>*)0xdeadbeef;
    SECTION("Extract from start")
    {
        l_returnValue = ExtractNodeFromStartOfList(l_list);
    }
    SECTION("Extract from end")
    {
        l_returnValue = ExtractNodeFromEndOfList(l_list);
    }

    CHECK(l_list.m_FirstNode == nullptr);
    CHECK(l_list.m_LastNode == nullptr);
    CHECK(l_returnValue == nullptr);

}

TEST_CASE("Extract from list of size 1", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    List<int> l_list;
    CreateListAtOfSize(l_list, 1);
    REQUIRE(l_list.m_FirstNode != nullptr);

    Node<int>* l_onlyNode = l_list.m_FirstNode;

    Node<int>* l_returnValue = (Node<int>*)0xdeadbeef;
    SECTION("Extract from start")
    {
        l_returnValue = ExtractNodeFromStartOfList(l_list);
    }
    SECTION("Extract from end")
    {
        l_returnValue = ExtractNodeFromEndOfList(l_list);
    }
    SECTION("Extract at index")
    {
        l_returnValue = ExtractNodeFromIndexNoErrorCheckOfList(0, l_list);
    }

    CHECK(l_list.m_FirstNode == nullptr);
    CHECK(l_list.m_LastNode == nullptr);
    CHECK(l_returnValue == l_onlyNode);

    DestroyList(l_list);
    free(l_returnValue);

}

TEST_CASE("Extract from start of list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    Size l_sizeOfList = GENERATE(take(10, random(2, 1000)));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    Node<int>* l_oldFirstNode = l_list.m_FirstNode;
    Node<int>* l_newFirstNode = l_list.m_FirstNode->m_NextNode;

    Node<int>* l_returnValue = ExtractNodeFromStartOfList(l_list);

    REQUIRE(l_list.m_FirstNode != nullptr);
    REQUIRE(l_list.m_LastNode != nullptr);

    CHECK(l_oldFirstNode == l_returnValue);
    CHECK(l_newFirstNode == l_list.m_FirstNode);

    CHECK(FindNumberOfNodesInList(l_list) == l_sizeOfList - 1);

    DestroyList(l_list);
    free(l_returnValue);

}

TEST_CASE("Extract from end of list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    Size l_sizeOfList = GENERATE(take(10, random(2, 1000)));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    Node<int>* l_oldLastNode = l_list.m_LastNode;
    Node<int>* l_newLastNode = FindNodeAtIndexNoErrorCheckFromList(l_sizeOfList - 2, l_list);

    Node<int>* l_returnValue = ExtractNodeFromEndOfList(l_list);

    REQUIRE(l_list.m_FirstNode != nullptr);
    REQUIRE(l_list.m_LastNode != nullptr);

    CHECK(l_oldLastNode == l_returnValue);
    CHECK(l_newLastNode == l_list.m_LastNode);
    CHECK(l_newLastNode->m_NextNode == nullptr);

    CHECK(FindNumberOfNodesInList(l_list) == l_sizeOfList - 1);

    DestroyList(l_list);
    free(l_returnValue);

}

TEST_CASE("Extract from index of list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    Size l_sizeOfList = GENERATE(take(10, random(3, 1000)));
    Size l_index = GENERATE_COPY(take<Size>(10, random<Size>(1, l_sizeOfList - 1)));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    Node<int>* l_nodeBeforeIndex = FindNodeAtIndexNoErrorCheckFromList(l_index - 1, l_list);
    Node<int>* l_nodeAtIndex = l_nodeBeforeIndex->m_NextNode;
    Node<int>* l_nodeAfterIndex = l_nodeAtIndex->m_NextNode;

    Node<int>* l_returnValue = ExtractNodeFromIndexNoErrorCheckOfList(l_index, l_list);

    REQUIRE(l_list.m_FirstNode != nullptr);
    REQUIRE(l_list.m_LastNode != nullptr);

    CHECK(l_nodeAtIndex == l_returnValue);
    CHECK(l_nodeBeforeIndex->m_NextNode == l_nodeAfterIndex);

    CHECK(FindNumberOfNodesInList(l_list) == l_sizeOfList - 1);

    DestroyList(l_list);
    free(l_returnValue);

}


//Just like the add tests, the remove tests do not check if the nodes a properly
//linked. This is again the job of the extraction functions that are called by
//the remove functions.
//
//Also the only way to make sure these tests work is if no crashes occur and no
//memory leaks are detected.
TEST_CASE("Remove node from start of list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    Size l_sizeOfList = GENERATE(take(10, random(2, 1000)));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    SECTION("Defaults")
    {
        RemoveNodeFromStartOfList(l_list);
    }
    SECTION("Customs")
    {
        RemoveNodeFromStartOfListUsingDeallocator(l_list, free);
    }

    DestroyList(l_list);

}

TEST_CASE("Remove node from end of list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    Size l_sizeOfList = GENERATE(take(10, random(2, 1000)));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    SECTION("Defaults")
    {
        RemoveNodeFromEndOfList(l_list);
    }
    SECTION("Customs")
    {
        RemoveNodeFromEndOfListUsingDeallocator(l_list, free);
    }

    DestroyList(l_list);

}

TEST_CASE("Remove node at index from list", "[LinkedList][SinglyLinked][Uncounted][Linear][Mutable]")
{

    Size l_sizeOfList = GENERATE(take(10, random(2, 1000)));
    Size l_index = GENERATE_COPY(take<Size>(10, random<Size>(1, l_sizeOfList - 1)));    

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    SECTION("Defaults")
    {
        RemoveNodeFromIndexNoErrorCheckOfList(l_index, l_list);
    }
    SECTION("Customs")
    {
        RemoveNodeFromIndexNoErrorCheckOfListUsingDeallocator(l_index, l_list, free);
    }

    DestroyList(l_list);

}
