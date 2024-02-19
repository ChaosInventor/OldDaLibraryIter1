#include <catch2/catch.hpp>

#include "../Mutex.hpp"

using namespace Library::Asynchronous;

void* HelperThread1(void* p_data)
{

    void** l_unpackData = (void**)p_data;
    volatile int* l_num = (volatile int*)(l_unpackData[0]);
    Mutex* l_mutex = (Mutex*)(l_unpackData[1]);

    if(LockMutex(*l_mutex) == false)
    {
        abort();
    }
        for(Size i = 0; i < 1000; ++i)
        {
            *l_num = -1;
        }
    if(UnlockMutex(*l_mutex) == false)
    {
        abort();
    }

    DestroyMutex(*l_mutex);

    return nullptr;

}
TEST_CASE("Locking and unlocking mutex", "[Mutex][Locking][Unlocking]")
{

    //Volatile so that the compier does not mess with it.
    volatile int l_num = 0;

    Mutex* l_mutex = AllocateMutex();
    REQUIRE(l_mutex != nullptr);
    CreateMutexAt(*l_mutex);

    void* l_data = (void*)&l_num;

    pthread_t l_thread;
    REQUIRE(pthread_create(&l_thread, nullptr, &HelperThread1, (void*)l_data) == 0);

    REQUIRE(LockMutex(*l_mutex) == true);
        l_num = 0;
        for(Size i = 0; i < 100; ++i)
        {
            ++l_num;
        }
        CHECK(l_num == 100);
    REQUIRE(UnlockMutex(*l_mutex) == true);

    DestroyMutex(*l_mutex);

    pthread_join(l_thread, nullptr);

}

void* HelperThread2(void* p_data)
{

    void** l_dataUnpack = (void**)p_data;
    bool* l_gotOwnership = (bool*)l_dataUnpack[0];
    Mutex* l_mutex = (Mutex*)l_dataUnpack[1];
    Mutex* l_superMutex = (Mutex*)l_dataUnpack[2];

    LockMutex(*l_mutex);
    LockMutex(*l_superMutex);

    CHECK(*l_gotOwnership == true);

}
TEST_CASE("Unlock after destruction", "[Mutex][Unlocking][Destruction]")
{

    Mutex* l_superMutex = CreateMutex();
    REQUIRE(l_superMutex != nullptr);

    Mutex* l_mutex = CreateMutex();
    REQUIRE(l_mutex != nullptr);
    Mutex* l_copyOfMutex = CopyMutex(*l_mutex);
    REQUIRE(l_copyOfMutex != nullptr);

    REQUIRE(LockMutex(*l_mutex) == true);

    void* l_data[3];

    DestroyMutex(*l_mutex);

    //TODO: Now have some way to find out if the mutex is unlocked

}

//TODO: Unlock after destruction

//TODO: Try lock

//TODO: Unlock not owner

//TODO: Relock
