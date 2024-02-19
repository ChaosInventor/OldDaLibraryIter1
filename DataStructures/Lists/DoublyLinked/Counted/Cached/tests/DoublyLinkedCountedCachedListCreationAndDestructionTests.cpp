#include <catch2/catch.hpp>

#include "../DoublyLinkedCountedCachedList.hpp"
#include "../../../../../../Debugging/Debugging.hpp"
#include "DoublyLinkedCountedListIntegrityCheck.hpp"

using namespace Library::DataStructures::Lists::DoublyLinked::Counted::Cached;
using namespace Library::DataStructures::Lists::DoublyLinked;
using namespace Catch::Generators;
using namespace Debugging;

int SimpleItemGenerator(void* p_data)
{
    int* l_item = (int*)p_data;
    (*l_item) += 1;
    return *l_item;
}

TEST_CASE("Create cyclic list of size using item generator", "[DoublyLinked][Counted][Cached][List][Creation]")
{

    List<int> l_list;
    int l_rand = random(0, 1000).get();

    SECTION("Empty list")
    {
        SECTION("Defaults")
        {
            CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator(
                l_list,
                0,
                SimpleItemGenerator, &l_rand
            );
        }
        SECTION("Customs")
        {
            bool l_called = false;

            CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator(
                l_list,
                0,
                malloc, &GeneralErrorCallback, &l_called,
                SimpleItemGenerator, &l_rand
            );

            CHECK(l_called == false);
        }

        CHECK(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_list, 0));
    }

    SECTION("Non empty list")
    {
        Size l_size = GENERATE(range(1, 100));
        int l_randCopy = l_rand;

        SECTION("Defaults")
        {
            CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator(
                l_list,
                l_size,
                SimpleItemGenerator, &l_randCopy
            );
        }
        SECTION("Customs")
        {
            bool l_called = false;

            CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator(
                l_list,
                l_size,
                malloc, &GeneralErrorCallback, &l_called,
                SimpleItemGenerator, &l_randCopy
            );

            CHECK(l_called == false);
        }

        REQUIRE(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_list, l_size));
        Node<int>* l_curNode = l_list.m_FirstNode;
        int l_expectedItem = l_rand + 1;
        do
        {
            CHECK(l_curNode->m_Item == l_expectedItem);

            l_curNode = l_curNode->m_NextNode;
            ++l_expectedItem;
        }
        while (l_curNode != l_list.m_LastNode->m_NextNode);
        
    }

    SECTION("Alloc error")
    {
        bool l_called = false;
        CreateCyclicListAtOfSizeUsingAllocator(
            l_list,
            10,
            NullMalloc, &GeneralErrorCallback, &l_called
        );

        CHECK(l_called == true);
        CHECK(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_list, 0));
    }

    SECTION("Alloc error after first node")
    {
        bool l_called = false;
        Size l_after = GENERATE(range(2, 20));
        SetCountOfNullMallocAfterCount(l_after);

        CreateCyclicListAtOfSizeUsingAllocator(
            l_list,
            l_after * 2,
            NullMallocAfterCount, &GeneralErrorCallback, &l_called
        );

        CHECK(l_called == true);
        CHECK(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_list, l_after));
    }

    DestroyListUsingDeallocator(l_list);

}

TEST_CASE("Create cyclic list without item generator", "[DoublyLinked][Counted][Cached][List][Creation]")
{

    //Note: This test only tests the function's ability to create a list that
    //has all of it's items default constructed, it does not test if the list
    //is correct or has any errors, the test case above allready does that and
    //there is no point in copy pasting code.

    Size l_size = GENERATE(range(1, 100));
    List<int> l_list;

    SECTION("Defaults")
    {    
        CreateCyclicListAtOfSizeUsingAllocator(l_list, l_size);
    }
    SECTION("Customs")
    {
        bool l_called = false;
        CreateCyclicListAtOfSizeUsingAllocator(
            l_list,
            l_size,
            malloc, &GeneralErrorCallback, &l_called
        );

        CHECK(l_called == false);
    }

    REQUIRE(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_list, l_size));

    Node<int>* l_curNode = l_list.m_FirstNode;
    do
    {    
        CHECK(l_curNode->m_Item == int());
        l_curNode = l_curNode->m_NextNode;
    }
    while (l_curNode != l_list.m_LastNode->m_NextNode);

    DestroyListUsingDeallocator(l_list);

}

TEST_CASE("Create null terminated list of size", "[DoublyLinked][Counted][Cached][List][Creation]")
{

    //Note: This test primarily checks if the list is null terminated or not,
    //it does not check if the items are correct since that is allready tested
    //in the above 2 test cases and there is no need to reapeat code.

    int l_rand = random(0, 1000).get();
    Size l_size = GENERATE(range(1, 100));

    List<int> l_list;

    SECTION("With item generator")
    {
        SECTION("Defaults")
        {
            CreateNullTerminatedListAtOfSizeUsingAllocatorAndCallItemGenerator(
                l_list,
                l_size,
                SimpleItemGenerator, &l_rand
            );
        }
        SECTION("Customs")
        {
            bool l_called = false;
            CreateNullTerminatedListAtOfSizeUsingAllocatorAndCallItemGenerator(
                l_list,
                l_size,
                malloc, &GeneralErrorCallback, &l_called,
                SimpleItemGenerator, &l_rand
            );
            CHECK(l_called == false);
        }
    }
    SECTION("Without item generator")
    {
        SECTION("Defaults")
        {
            CreateNullTerminatedListAtOfSizeUsingAllocator(
                l_list,
                l_size
            );
        }
        SECTION("Customs")
        {
            bool l_called = false;
            CreateNullTerminatedListAtOfSizeUsingAllocator(
                l_list,
                l_size,
                malloc, &GeneralErrorCallback, &l_called
            );
            CHECK(l_called == false);
        }
    }

    REQUIRE(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_list, l_size));
    CHECK(l_list.m_FirstNode->m_PreviousNode == nullptr);
    CHECK(l_list.m_LastNode->m_NextNode == nullptr);

    DestroyListUsingDeallocator(l_list);

}

TEST_CASE("Create copy of list", "[DoublyLinked][Counted][Cached][List][Creation]")
{

    //Note: This test only tests if the copy function properly copies all of the
    //items and if the type of the list is preserved.

    Size l_size = GENERATE(range(1, 100));
    int l_rand = random(0, 1000).get();

    List<int> l_newCyclic;
    List<int> l_newNullTerm;

    List<int> l_cyclic;
    List<int> l_nullTerm;

    int l_randCopy1 = l_rand;
    int l_randCopy2 = l_rand;
    CreateCyclicListAtOfSizeUsingAllocatorAndCallItemGenerator(
        l_cyclic,
        l_size,
        SimpleItemGenerator, &l_randCopy1
    );
    CreateNullTerminatedListAtOfSizeUsingAllocatorAndCallItemGenerator(
        l_nullTerm,
        l_size,
        SimpleItemGenerator, &l_randCopy2
    );

    //In case of alloc errors.
    REQUIRE(l_cyclic.m_Size == l_size);
    REQUIRE(l_nullTerm.m_Size == l_size);

    SECTION("Defaults")
    {
        CreateCopyAtOfListUsingAllocator(l_newCyclic, l_cyclic);
        CreateCopyAtOfListUsingAllocator(l_newNullTerm, l_nullTerm);
    }
    SECTION("Customs")
    {
        bool l_called1 = false;
        bool l_called2 = false;
        
        CreateCopyAtOfListUsingAllocator(
            l_newCyclic,
            l_cyclic,
            malloc, &GeneralErrorCallback, &l_called1
        );
        CreateCopyAtOfListUsingAllocator(
            l_newNullTerm,
            l_nullTerm,
            malloc, &GeneralErrorCallback, &l_called2
        );

        CHECK(l_called1 == false);
        CHECK(l_called2 == false);
    }

    REQUIRE(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_newCyclic, l_size));
    REQUIRE(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_newNullTerm, l_size));

    //Make sure that it is cyclic
    CHECK(l_newCyclic.m_FirstNode->m_PreviousNode == l_newCyclic.m_LastNode);
    CHECK(l_newCyclic.m_LastNode->m_NextNode == l_newCyclic.m_FirstNode);

    //Make sure that is is null termianted.
    CHECK(l_newNullTerm.m_FirstNode->m_PreviousNode == nullptr);
    CHECK(l_newNullTerm.m_LastNode->m_NextNode == nullptr);

    int l_expectedItem = l_rand + 1;
    Node<int>* l_curNodeCyclic = l_newCyclic.m_FirstNode;
    Node<int>* l_curNodeNullTerm = l_newNullTerm.m_FirstNode;
    do
    {
        CHECK(l_curNodeCyclic->m_Item == l_expectedItem);
        CHECK(l_curNodeNullTerm->m_Item == l_expectedItem);

        ++l_expectedItem;
        l_curNodeCyclic = l_curNodeCyclic->m_NextNode;
        l_curNodeNullTerm = l_curNodeNullTerm->m_NextNode;
    }
    while (l_curNodeCyclic != l_newCyclic.m_LastNode->m_NextNode);
    

    DestroyListUsingDeallocator(l_newCyclic);
    DestroyListUsingDeallocator(l_newNullTerm);
    DestroyListUsingDeallocator(l_cyclic);
    DestroyListUsingDeallocator(l_nullTerm);

}

TEST_CASE("Destroy list", "[DoublyLinked][Counted][Cached][List][Destruction]")
{

    Node<int>* l_node1 = AllocateNodeUsingAllocatorNoErrorCheck<int>(malloc);
    Node<int>* l_node2 = AllocateNodeUsingAllocatorNoErrorCheck<int>(malloc);
    Node<int>* l_node3 = AllocateNodeUsingAllocatorNoErrorCheck<int>(malloc);

    l_node1->m_PreviousNode = nullptr;
    l_node1->m_NextNode = l_node2;

    l_node2->m_PreviousNode = l_node1;
    l_node2->m_NextNode = l_node3;

    l_node3->m_PreviousNode = l_node2;
    l_node3->m_NextNode = nullptr;

    Node<int>* l_node4 = AllocateNodeUsingAllocatorNoErrorCheck<int>(malloc);
    Node<int>* l_node5 = AllocateNodeUsingAllocatorNoErrorCheck<int>(malloc);
    Node<int>* l_node6 = AllocateNodeUsingAllocatorNoErrorCheck<int>(malloc);

    l_node4->m_PreviousNode = l_node6;
    l_node4->m_NextNode = l_node5;

    l_node5->m_PreviousNode = l_node4;
    l_node5->m_NextNode = l_node6;

    l_node6->m_PreviousNode = l_node5;
    l_node6->m_NextNode = l_node4;

    List<int> l_listNullTerm(l_node1, l_node3);
    List<int> l_listCyclic(l_node4, l_node6);

    DestroyListUsingDeallocator(l_listNullTerm, free);
    DestroyListUsingDeallocator(l_listCyclic);

    CHECK(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_listNullTerm, 0));
    CHECK(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_listCyclic, 0));

}
