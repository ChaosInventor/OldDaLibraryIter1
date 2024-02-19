#include <catch2/catch.hpp>

#include "DoublyLinkedCountedListIntegrityCheck.hpp"
#include "../DoublyLinkedCountedCachedList.hpp"
#include "../../../../../../Debugging/Debugging.hpp"

using namespace Library::DataStructures::Lists::DoublyLinked::Counted::Cached;
using namespace Library::DataStructures::Lists::DoublyLinked;
using namespace Catch::Generators;
using namespace Debugging;

TEST_CASE("Addition of items and nodes to list", "[DoublyLinked][List][Counted][Cached][Mutable]")
{

    Size l_listSize = GENERATE(range(0, 10));
    Size l_numOfAdditions = GENERATE(range(1, 20));

    //I again have no idea on how to do this in a different way.
    Size l_funcToUse = GENERATE(0, 1);
    void (*l_createListFunction)(List<int>&, const Size&);
    if(l_funcToUse == 0)
    {
        l_createListFunction = &CreateCyclicListAtOfSizeUsingAllocator<int>;
    }
    else
    {
        l_createListFunction = &CreateNullTerminatedListAtOfSizeUsingAllocator<int>;
    }

    List<int> l_list;
    l_createListFunction(l_list, l_listSize);
    REQUIRE(l_list.m_Size == l_listSize);

    SECTION("Add node")
    {
        SECTION("To start")
        {
            Node<int>* l_node;
            for(Size i = 0; i < l_numOfAdditions; ++i)
            {
                l_node = AllocateNodeUsingAllocatorNoErrorCheck<int>(malloc);
                REQUIRE(l_node != nullptr);

                AddNodeAsStartToList(*l_node, l_list);
                CHECK(l_list.m_FirstNode == l_node);
            }
        }
        SECTION("To end")
        {
            Node<int>* l_node;
            for(Size i = 0; i < l_numOfAdditions; ++i)
            {
                l_node = AllocateNodeUsingAllocatorNoErrorCheck<int>(malloc);
                REQUIRE(l_node != nullptr);

                AddNodeAsEndToList(*l_node, l_list);
                CHECK(l_list.m_LastNode == l_node);
            }
        }
        SECTION("After index")
        {
            Size l_index;
            if(l_listSize > 1)
            {
                l_index = GENERATE_COPY(range<Size>(0, l_listSize - 1));
            }
            else if(l_listSize == 1)
            {
                l_index = 0;
            }
            else
            {
                //I really don't know how to do this in any different way.
                goto skip;
            }

            Node<int>* l_node;
            for(Size i = 0; i < l_numOfAdditions; ++i)
            {
                l_node = AllocateNodeUsingAllocatorNoErrorCheck<int>(malloc);
                REQUIRE(l_node != nullptr);

                AddNodeAfterIndexToList(*l_node, l_index, nullptr, nullptr, l_list);
                if(l_index < l_listSize - 1)
                {                
                    CHECK(l_list.m_Cache.m_Node == l_node);
                }
            }
        }
    }
    SECTION("Add item")
    {
        int l_item = random(0, 100).get();
        SECTION("To start")
        {
            for(Size i = 0; i < l_numOfAdditions; ++i)
            {
                AddItemAsStartToListUsingAllocator(l_item, l_list);
                CHECK(l_list[0] == l_item);
            }
        }
        SECTION("To end")
        {
            for(Size i = 0; i < l_numOfAdditions; ++i)
            {
                AddItemAsEndToListUsingAllocator(l_item, l_list);

                CHECK(l_list[l_list.m_Size - 1] == l_item);
            }
        }
        SECTION("After index")
        {
            Size l_index;
            if(l_listSize > 1)
            {
                l_index = GENERATE_COPY(range<Size>(0, l_listSize - 1));
            }
            else if(l_listSize == 1)
            {
                l_index = 0;
            }
            else
            {
                //I really don't know how to do this in any different way.
                goto skip;
            }

            for(Size i = 0; i < l_numOfAdditions; ++i)
            {
                AddItemAfterIndexToListUsingAllocator(
                    l_item,
                    l_index, nullptr, nullptr,
                    l_list
                );

                CHECK(l_list[l_index + 1] == l_item);
            }
        }
    }

    CHECK(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_list, l_listSize + l_numOfAdditions));

    skip:
    DestroyListUsingDeallocator(l_list);

}

TEST_CASE("Addition index error", "[DoublyLinked][List][Counted][Cached][Mutable]")
{

    Size l_index = GENERATE(range(1, 20));

    //Can just be empty doesn't matter.
    List<int> l_list;

    bool l_called = false;

    SECTION("Add node")
    {
        Node<int> l_node;
        AddNodeAfterIndexToList(
            l_node,
            l_index, &GeneralErrorCallback, &l_called,
            l_list
        );
    }
    SECTION("Add item")
    {
        bool l_called2 = false;
        AddItemAfterIndexToListUsingAllocator<int>(
            1,
            l_index, &GeneralErrorCallback, &l_called,
            l_list,
            NullMalloc, &GeneralErrorCallback, &l_called2
        );

        CHECK(l_called2 == false);
    }

    CHECK(l_called == true);
    CHECK(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_list, 0));

}

TEST_CASE("Addition alloc error", "[DoublyLinked][List][Counted][Cached][Mutable]")
{

    //Has to be >0 so that no index error
    List<int> l_list;
    CreateCyclicListAtOfSizeUsingAllocator(l_list, 1);

    bool l_called = false;

    SECTION("As start")
    {
        AddItemAsStartToListUsingAllocator(
            1,
            l_list,
            NullMalloc, &GeneralErrorCallback, &l_called
        );
    }
    SECTION("As end")
    {
        AddItemAsEndToListUsingAllocator(
            1,
            l_list,
            NullMalloc, &GeneralErrorCallback, &l_called
        );
    }
    SECTION("After index")
    {
        AddItemAfterIndexToListUsingAllocator(
            1,
            0, nullptr, nullptr,
            l_list,
            NullMalloc, &GeneralErrorCallback, &l_called
        );
    }

    CHECK(l_called == true);
    CHECK(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_list, 1));

    DestroyListUsingDeallocator(l_list);

}

TEST_CASE("Removal of nodes", "[DoublyLinked][List][Counted][Cached][Mutable]")
{

    Size l_listSize = GENERATE(range(0, 10));
    Size l_numOfRemovals = GENERATE(range(1, 10));

    //I again have no idea on how to do this in a different way.
    Size l_funcToUse = GENERATE(0, 1);
    void (*l_createListFunction)(List<int>&, const Size&);
    if(l_funcToUse == 0)
    {
        l_createListFunction = &CreateCyclicListAtOfSizeUsingAllocator<int>;
    }
    else
    {
        l_createListFunction = &CreateNullTerminatedListAtOfSizeUsingAllocator<int>;
    }

    List<int> l_list;
    l_createListFunction(l_list, l_listSize);
    REQUIRE(l_list.m_Size == l_listSize);


    SECTION("Remove and return")
    {
        SECTION("First node")
        {
            Node<int>* l_returnValue;
            Node<int>* l_lastFirstNode = l_list.m_FirstNode;
            for(Size i = 0; i < l_numOfRemovals; ++i)
            {
                l_returnValue = RemoveFirstNodeFromListAndReturnIt(l_list);
                CHECK(l_returnValue == l_lastFirstNode);
                free(l_returnValue);
                l_lastFirstNode = l_list.m_FirstNode;
            }
        }
        SECTION("Last node")
        {
            Node<int>* l_returnValue;
            Node<int>* l_lastLastNode = l_list.m_LastNode;
            for(Size i = 0; i < l_numOfRemovals; ++i)
            {
                l_returnValue = RemoveLastNodeFromListAndReturnIt(l_list);
                CHECK(l_returnValue == l_lastLastNode);
                free(l_returnValue);
                l_lastLastNode = l_list.m_LastNode;
            }
        }
        SECTION("Node at index")
        {
            Size l_index;
            if(l_listSize > 1)
            {
                l_index = GENERATE_COPY(range<Size>(0, l_listSize - 1));
            }
            else if(l_listSize == 1)
            {
                l_index = 0;
            }
            else
            {
                //Can't think of another way to do this.
                goto skip;
            }

            CAPTURE(l_index);
            Node<int>* l_returnValue;
            Node<int>* l_lastNodeAtIndex = FindNodeAtIndexNoErrorCheckInListAndUpdateCache(l_index, l_list);
            for(Size i = 0; i < l_numOfRemovals; ++i)
            {
                if(l_index >= l_list.m_Size)
                {
                    l_numOfRemovals = i;
                    break;
                }

                l_returnValue = RemoveNodeAtIndexFromListAndReturnIt(
                    l_index, nullptr, nullptr,
                    l_list
                );
                CHECK(l_returnValue == l_lastNodeAtIndex);
                free(l_returnValue);
                if(l_index >= l_list.m_Size)
                {
                    l_numOfRemovals = i + 1;
                    break;
                }
                l_lastNodeAtIndex = FindNodeAtIndexNoErrorCheckInListAndUpdateCache(l_index, l_list);
            }
        }
    }
    SECTION("Remove and deallocate")
    {
        //Note: the only real way to test if this works is with something such
        //as valgrind.

        SECTION("First node")
        {
            for(Size i = 0; i < l_numOfRemovals; ++i)
            {
                RemoveFirstNodeFromListAndDeallocateItUsingDeallocator(l_list);
            }
        }
        SECTION("Last node")
        {
            for(Size i = 0; i < l_numOfRemovals; ++i)
            {
                RemoveLastNodeFromListAndDeallocateItUsingDeallocator(l_list);
            }
        }
        SECTION("Node at index")
        {
            Size l_index;
            if(l_listSize > 1)
            {
                l_index = GENERATE_COPY(range<Size>(0, l_listSize - 1));
            }
            else if(l_listSize == 1)
            {
                l_index = 0;
            }
            else
            {
                //Can't think of another way to do this.
                goto skip;
            }

            for(Size i = 0; i < l_numOfRemovals; ++i)
            {
                if(l_index >= l_list.m_Size)
                {
                    l_numOfRemovals = i;
                    break;
                }

                RemoveNodeAtIndexFromListAndDeallocateItUsingDeallocator(
                    l_index, nullptr, nullptr,
                    l_list
                );
            }
        }
    }

    if(l_numOfRemovals > l_listSize)
    {
        INFO("l_listSize = " << l_listSize << " l_numOfRemovals = " << l_numOfRemovals);
        CHECK(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_list, 0));
    }
    else
    {
        INFO("l_listSize = " << l_listSize << " l_numOfRemovals = " << l_numOfRemovals);
        CHECK(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_list, l_listSize - l_numOfRemovals));
    }

    skip:
    DestroyListUsingDeallocator(l_list);

}

TEST_CASE("Removal index error", "[DoublyLinked][List][Counted][Cached][Mutable]")
{

    Size l_index = GENERATE(range(1, 20));

    //Can just be empty doesn't matter.
    List<int> l_list;

    bool l_called = false;

    SECTION("Remove and return")
    {
        Node<int>* l_returnValue = RemoveNodeAtIndexFromListAndReturnIt(
            l_index, &GeneralErrorCallback, &l_called,
            l_list
        );
        
        CHECK(l_returnValue == nullptr);
    }
    SECTION("Remove and deallocate")
    {
        RemoveNodeAtIndexFromListAndDeallocateItUsingDeallocator(
            l_index, &GeneralErrorCallback, &l_called,
            l_list
        );
    }

    CHECK(l_called == true);

    CHECK(ListIntegrityIsGoodAndListSizeIsExpectedSize(l_list, 0));

}
