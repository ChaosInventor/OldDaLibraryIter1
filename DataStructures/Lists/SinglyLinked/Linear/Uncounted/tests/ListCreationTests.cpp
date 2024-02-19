#include <catch2/catch.hpp>

#include "../List.hpp"
#include "../../../../../../Debugging/Debugging.hpp"

using namespace Debugging;
using namespace Library::DataStructures::Lists::SinglyLinked::Linear::Uncounted;
using namespace Library::DataStructures::Lists::SinglyLinked;
using namespace Library;
using namespace Catch::Generators;

TEST_CASE("Create list of size normal", "[LinkedList][SinglyLinked][Uncounted][Linear][Creation]")
{

    Size l_sizeOfList = GENERATE(take<Size>(10, random<Size>(2, 10000)));

    List<int> l_list;

    SECTION("Defaults")
    {
        CreateListAtOfSize(l_list, l_sizeOfList);
    }
    SECTION("Customs")
    {
        bool l_called = false;
        CreateListAtOfSizeUsingAllocator(
            l_list, l_sizeOfList,
            malloc, &GeneralErrorCallback, &l_called
        );
        CHECK(l_called == false);
    }

    REQUIRE(l_list.m_FirstNode != nullptr);
    REQUIRE(l_list.m_LastNode != nullptr);
    REQUIRE(l_list.m_FirstNode != l_list.m_LastNode);
    REQUIRE(l_list.m_LastNode->m_NextNode == nullptr);

    Size l_countedNodes = 0;
    Node<int>* l_curNode = l_list.m_FirstNode;
    while(l_curNode != nullptr)
    {
        l_curNode = l_curNode->m_NextNode;
        ++l_countedNodes;
    }

    CHECK(l_countedNodes == l_sizeOfList);

    DestroyList(l_list);

}

TEST_CASE("Create list of size 0", "[LinkedList][SinglyLinked][Uncounted][Linear][Creation]")
{

    List<int> l_list;

    SECTION("Defaults")
    {
        CreateListAtOfSize(l_list, 0);
    }
    SECTION("Customs")
    {
        bool l_called = false;
        CreateListAtOfSizeUsingAllocator(
            l_list, 0,
            NullMalloc, &GeneralErrorCallback, &l_called
        );
        CHECK(l_called == false);
    }

    CHECK(l_list.m_FirstNode == nullptr);
    CHECK(l_list.m_LastNode == nullptr);

}

TEST_CASE("Create list of size 1", "[LinkedList][SinglyLinked][Uncounted][Linear][Creation]")
{

    List<int> l_list;

    SECTION("Defaults")
    {
        CreateListAtOfSize(l_list, 1);
    }
    SECTION("Customs")
    {
        bool l_called = false;
        CreateListAtOfSizeUsingAllocator(
            l_list, 1,
            malloc, &GeneralErrorCallback, &l_called
        );
        CHECK(l_called == false);
    }

    CHECK(l_list.m_FirstNode != nullptr);
    REQUIRE(l_list.m_LastNode != nullptr);
    CHECK(l_list.m_FirstNode == l_list.m_LastNode);
    CHECK(l_list.m_LastNode->m_NextNode == nullptr);

    free(l_list.m_FirstNode);

}

TEST_CASE("Create list alloc error first node", "[LinkedList][SinglyLinked][Uncounted][Linear][Creation]")
{

    Size l_sizeOfList = GENERATE(take<Size>(10, random<Size>(2, 10000)));

    List<int> l_list;
    
    bool l_called = false;
    CreateListAtOfSizeUsingAllocator(
        l_list, l_sizeOfList,
        NullMalloc, &GeneralErrorCallback, &l_called
    );
    CHECK(l_called == true);

    CHECK(l_list.m_FirstNode == nullptr);
    CHECK(l_list.m_LastNode == nullptr);

}

TEST_CASE("Create list alloc error second node", "[LinkedList][SinglyLinked][Uncounted][Linear][Creation]")
{

    Size l_sizeOfList = GENERATE(take<Size>(10, random<Size>(3, 10000)));

    List<int> l_list;
    
    SetCountOfNullMallocAfterCount(1);
 
    bool l_called = false;
    CreateListAtOfSizeUsingAllocator(
        l_list, l_sizeOfList,
        NullMallocAfterCount, &GeneralErrorCallback, &l_called
 
    );
    CHECK(l_called == true);

    CHECK(l_list.m_FirstNode != nullptr);
    REQUIRE(l_list.m_LastNode != nullptr);
    CHECK(l_list.m_FirstNode == l_list.m_LastNode);
    CHECK(l_list.m_LastNode->m_NextNode == nullptr);

    free(l_list.m_FirstNode);

}

TEST_CASE("Create list alloc error middle node", "[LinkedList][SinglyLinked][Uncounted][Linear][Creation]")
{

    Size l_sizeOfList = GENERATE(take<Size>(10, random<Size>(4, 100)));
    Size l_allocErrorAfter = GENERATE_COPY(take<Size>(10, random<Size>(2, l_sizeOfList - 1)));

    List<int> l_list;
    
    SetCountOfNullMallocAfterCount(l_allocErrorAfter);
 
    bool l_called = false;
    CreateListAtOfSizeUsingAllocator(
        l_list, l_sizeOfList,
        NullMallocAfterCount, &GeneralErrorCallback, &l_called
 
    );
    CHECK(l_called == true);

    REQUIRE(l_list.m_FirstNode != nullptr);
    REQUIRE(l_list.m_LastNode != nullptr);
    REQUIRE(l_list.m_LastNode->m_NextNode == nullptr);

    Size l_countedNodes = 0;
    Node<int>* l_curNode = l_list.m_FirstNode;
    while(l_curNode != nullptr)
    {
        l_curNode = l_curNode->m_NextNode;
        ++l_countedNodes;
    }

    CHECK(l_countedNodes == l_allocErrorAfter);

    DestroyList(l_list);

}


TEST_CASE("Create copy of list normal", "[LinkedList][SinglyLinked][Uncounted][Linear][Creation]")
{

    Size l_sizeOfList = GENERATE(take<Size>(10, random<Size>(2, 10000)));
    int l_items[3];
    l_items[0] = GENERATE(take(1, random(INT_MIN, INT_MAX)));
    l_items[1] = GENERATE(take(1, random(INT_MIN, INT_MAX)));
    l_items[2] = GENERATE(take(1, random(INT_MIN, INT_MAX)));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    Size l_itemIndex = 0;
    for
    (
        Node<int>* l_curNode = l_list.m_FirstNode;
        l_curNode != nullptr;
        l_curNode = l_curNode->m_NextNode
    )
    {
        l_curNode->m_Item = l_items[l_itemIndex];
        ++l_itemIndex;
        l_itemIndex %= 3;
    }

    List<int> l_copy;

    SECTION("Defaults")
    {
        CreateCopyAtOfList(l_copy, l_list);
    }
    SECTION("Customs")
    {
        bool l_called = false;
        CreateCopyAtOfListUsingAllocator(
            l_copy,
            l_list,
            malloc, &GeneralErrorCallback, &l_called
        );
        CHECK(l_called == false);
    }

    REQUIRE(l_copy.m_FirstNode != nullptr);
    REQUIRE(l_copy.m_LastNode != nullptr);
    REQUIRE(l_copy.m_LastNode->m_NextNode == nullptr);

    l_itemIndex = 0;
    for
    (
        Node<int>* l_curNode = l_copy.m_FirstNode;
        l_curNode != nullptr;
        l_curNode = l_curNode->m_NextNode
    )
    {
        CHECK(l_curNode->m_Item == l_items[l_itemIndex]);
        ++l_itemIndex;
        l_itemIndex %= 3;
    }

    CHECK(FindNumberOfNodesInList(l_copy) == l_sizeOfList);

    DestroyList(l_list);
    DestroyList(l_copy);

}

TEST_CASE("Create copy of list size 0", "[LinkedList][SinglyLinked][Uncounted][Linear][Creation]")
{

    List<int> l_list;

    List<int> l_copy;

    SECTION("Defaults")
    {
        CreateCopyAtOfList(l_copy, l_list);
    }
    SECTION("Customs")
    {
        bool l_called = false;
        CreateCopyAtOfListUsingAllocator(
            l_copy,
            l_list,
            malloc, &GeneralErrorCallback, &l_called
        );
        CHECK(l_called == false);
    }

    CHECK(l_copy.m_FirstNode == nullptr);
    CHECK(l_copy.m_LastNode == nullptr);

    DestroyList(l_list);
    DestroyList(l_copy);

}

TEST_CASE("Create copy of list size 1", "[LinkedList][SinglyLinked][Uncounted][Linear][Creation]")
{

    int l_item = GENERATE(take(1, random(INT_MIN, INT_MAX)));

    List<int> l_list;
    CreateListAtOfSize(l_list, 1);
    REQUIRE(l_list.m_FirstNode != nullptr);

    l_list.m_FirstNode->m_Item = l_item;

    List<int> l_copy;

    SECTION("Defaults")
    {
        CreateCopyAtOfList(l_copy, l_list);
    }
    SECTION("Customs")
    {
        bool l_called = false;
        CreateCopyAtOfListUsingAllocator(
            l_copy,
            l_list,
            malloc, &GeneralErrorCallback, &l_called
        );
        CHECK(l_called == false);
    }

    REQUIRE(l_copy.m_FirstNode != nullptr);
    REQUIRE(l_copy.m_LastNode != nullptr);
    CHECK(l_copy.m_FirstNode == l_copy.m_LastNode);
    CHECK(l_copy.m_FirstNode->m_NextNode == nullptr);
    CHECK(l_copy.m_LastNode->m_Item == l_item);

    DestroyList(l_list);
    DestroyList(l_copy);

}

TEST_CASE("Create copy of alloc error first node", "[LinkedList][SinglyLinked][Uncounted][Linear][Creation]")
{

    Size l_sizeOfList = GENERATE(take<Size>(10, random<Size>(2, 1000)));
    int l_items[3];
    l_items[0] = GENERATE(take(1, random(INT_MIN, INT_MAX)));
    l_items[1] = GENERATE(take(1, random(INT_MIN, INT_MAX)));
    l_items[2] = GENERATE(take(1, random(INT_MIN, INT_MAX)));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    Size l_itemIndex = 0;
    for
    (
        Node<int>* l_curNode = l_list.m_FirstNode;
        l_curNode != nullptr;
        l_curNode = l_curNode->m_NextNode
    )
    {
        l_curNode->m_Item = l_items[l_itemIndex];
        ++l_itemIndex;
        l_itemIndex %= 3;
    }

    List<int> l_copy;

    bool l_called = false;
    CreateCopyAtOfListUsingAllocator(
        l_copy,
        l_list,
        NullMalloc, &GeneralErrorCallback, &l_called
    );
    CHECK(l_called == true);

    CHECK(l_copy.m_FirstNode == nullptr);
    CHECK(l_copy.m_LastNode == nullptr);

    DestroyList(l_list);
    DestroyList(l_copy);

}

TEST_CASE("Create copy of alloc error second node", "[LinkedList][SinglyLinked][Uncounted][Linear][Creation]")
{

    Size l_sizeOfList = GENERATE(take<Size>(10, random<Size>(2, 1000)));
    int l_items[3];
    l_items[0] = GENERATE(take(1, random(INT_MIN, INT_MAX)));
    l_items[1] = GENERATE(take(1, random(INT_MIN, INT_MAX)));
    l_items[2] = GENERATE(take(1, random(INT_MIN, INT_MAX)));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    Size l_itemIndex = 0;
    for
    (
        Node<int>* l_curNode = l_list.m_FirstNode;
        l_curNode != nullptr;
        l_curNode = l_curNode->m_NextNode
    )
    {
        l_curNode->m_Item = l_items[l_itemIndex];
        ++l_itemIndex;
        l_itemIndex %= 3;
    }

    List<int> l_copy;

    SetCountOfNullMallocAfterCount(1);
    bool l_called = false;
    CreateCopyAtOfListUsingAllocator(
        l_copy,
        l_list,
        NullMallocAfterCount, &GeneralErrorCallback, &l_called
    );
    CHECK(l_called == true);

    REQUIRE(l_copy.m_FirstNode != nullptr);
    REQUIRE(l_copy.m_LastNode != nullptr);
    CHECK(l_copy.m_FirstNode == l_copy.m_LastNode);
    CHECK(l_copy.m_FirstNode->m_NextNode == nullptr);
    CHECK(l_copy.m_LastNode->m_Item == l_items[0]);

    DestroyList(l_list);
    DestroyList(l_copy);

}

TEST_CASE("Create copy of alloc error middle node", "[LinkedList][SinglyLinked][Uncounted][Linear][Creation]")
{

    Size l_sizeOfList = GENERATE(take<Size>(10, random<Size>(4, 1000)));
    Size l_allocErrorAfter = GENERATE_COPY(take<Size>(10, random<Size>(2, l_sizeOfList - 1)));

    int l_items[3];
    l_items[0] = GENERATE(take(1, random(INT_MIN, INT_MAX)));
    l_items[1] = GENERATE(take(1, random(INT_MIN, INT_MAX)));
    l_items[2] = GENERATE(take(1, random(INT_MIN, INT_MAX)));

    List<int> l_list;
    CreateListAtOfSize(l_list, l_sizeOfList);
    REQUIRE(l_list.m_FirstNode != nullptr);

    Size l_itemIndex = 0;
    for
    (
        Node<int>* l_curNode = l_list.m_FirstNode;
        l_curNode != nullptr;
        l_curNode = l_curNode->m_NextNode
    )
    {
        l_curNode->m_Item = l_items[l_itemIndex];
        ++l_itemIndex;
        l_itemIndex %= 3;
    }

    List<int> l_copy;

    SetCountOfNullMallocAfterCount(l_allocErrorAfter);
    bool l_called = false;
    CreateCopyAtOfListUsingAllocator(
        l_copy,
        l_list,
        NullMallocAfterCount, &GeneralErrorCallback, &l_called
    );
    CHECK(l_called == true);

    REQUIRE(l_copy.m_FirstNode != nullptr);
    REQUIRE(l_copy.m_LastNode != nullptr);
    REQUIRE(l_copy.m_LastNode->m_NextNode == nullptr);

    l_itemIndex = 0;
    for
    (
        Node<int>* l_curNode = l_copy.m_FirstNode;
        l_curNode != nullptr;
        l_curNode = l_curNode->m_NextNode
    )
    {
        CHECK(l_curNode->m_Item == l_items[l_itemIndex]);
        ++l_itemIndex;
        l_itemIndex %= 3;
    }

    CHECK(FindNumberOfNodesInList(l_copy) == l_allocErrorAfter);

    DestroyList(l_list);
    DestroyList(l_copy);

}
