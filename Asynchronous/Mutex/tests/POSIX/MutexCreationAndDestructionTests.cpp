#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../../include/Mutex.hpp"
#include "../../include/platfrom_specific/POSIXMutex.hpp"
#include "../../../../Debugging/Debugging.hpp"

using namespace Library::Asynchronous;
using namespace Debugging;

TEST_CASE("Allocate and deallocate mutex", "[Mutex][Allocation][Deallocation]")
{

    Mutex* l_mutex;
    bool l_defaults;
    SECTION("Defaults")
    {
        l_defaults = true;
        l_mutex = AllocateMutex();
    }
    SECTION("Customs")
    {
        l_defaults = false;
        bool l_called = false;
        l_mutex = AllocateMutexUsingAllocator(
            malloc,
            &GeneralErrorCallback, &l_called
        );
        REQUIRE(l_called == false);
    }

    REQUIRE(l_mutex != nullptr);

    //Note: Cannot check if m_mutex is valid or not.
    CHECK(l_mutex->m_OwnerDeathCallback == nullptr);
    CHECK(l_mutex->m_OwnerDeathCallbackData == nullptr);

    if(l_defaults == true)
    {
        DeallocateMutex(*l_mutex);
    }
    else
    {
        DeallocateMutexUsingDeallocator(*l_mutex, free);
    }
    

}

TEST_CASE("Allocate mutex allocation error", "[Mutex][Allocation]")
{

    Mutex* l_mutex;

    bool l_called = false;
    l_mutex = AllocateMutexUsingAllocator(
        NullMalloc,
        &GeneralErrorCallback, &l_called
    );
    CHECK(l_called == true);

    CHECK(l_mutex == nullptr);

}

TEST_CASE("Create and destroy mutex", "[Mutex][Creation][Destruction]")
{

    Mutex* l_mutex = AllocateMutex();
    REQUIRE(l_mutex != nullptr);

    CreateMutexAt(*l_mutex);

    //Cannot check if m_Mutex has been intialized.
    REQUIRE(l_mutex->m_OwnerDeathCallback == nullptr);
    REQUIRE(l_mutex->m_OwnerDeathCallbackData == nullptr);

    DestroyMutex(*l_mutex);

    CHECK(l_mutex->m_OwnerDeathCallback == nullptr);
    CHECK(l_mutex->m_OwnerDeathCallbackData == nullptr);

}
