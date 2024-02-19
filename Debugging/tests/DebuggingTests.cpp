#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../Debugging.hpp"

using namespace Debugging;

TEST_CASE("Null malloc", "[Debugging][malloc]")
{

    Size l_size = GENERATE(Catch::Generators::range<Size>(0, 10000));

    INFO("You had one job NullMalloc. ONE. F#$*ING. JOB!");
    REQUIRE(NullMalloc(l_size) == nullptr);

}
TEST_CASE("Null realloc", "[Debugging][realloc]")
{

    void* l_pointer = (void*)GENERATE(Catch::Generators::range<intptr_t>(-10000, 10000));
    Size l_size = abs((intptr_t)l_pointer * 2);

    void* l_result = NullRealloc(l_pointer, l_size); 

    INFO("ONE JOB!!111!!1!!");
    CHECK(l_result == nullptr);

}

TEST_CASE("Null malloc after count", "[Debugging][malloc]")
{

    Size l_after = GENERATE(Catch::Generators::range(0, 100));

    SetCountOfNullMallocAfterCount(l_after);

    for(Size i = 0; i < l_after; ++i)
    {
        void* l_result = NullMallocAfterCount(1);

        if(l_result == nullptr)
        {
            FAIL("NullMallocAfterCount returned nullptr before expected");
        }

        free(l_result);
    }

    void* l_result = NullMallocAfterCount(1);
    
    CHECK(l_result == nullptr);

}
TEST_CASE("Null realloc after count", "[Debugging][realloc]")
{

    Size l_count = GENERATE(Catch::Generators::range(5, 100));
    
    Size l_resizeTo = GENERATE_REF(l_count / 2, l_count * 2);
    
    SetCountOfNullReallocAfterCount(l_count);
    for (Size i = 0; i < l_count; i++)
    {
        void* l_mem = malloc(1);

        if(l_mem == nullptr)
        {
            FAIL("Malloc returned null during setup");
        }
        
        void* l_result = NullReallocAfterCount(l_mem, l_resizeTo);
        
        if(l_result == nullptr)
        {
            FAIL("NullReallocAfterCount returned null before expected");
        }

        free(l_result);
        l_mem = nullptr;
    }

    //Should still fail even tho it's a nullptr.
    void* l_result = NullReallocAfterCount(nullptr, l_resizeTo);

    CHECK(l_result == nullptr);

}

TEST_CASE("General error callback", "[debugging][error]")
{

    bool l_called = false;

    GeneralErrorCallback(&l_called);

    INFO("You too, GeneralErrorCallback, you had ONE JOB!");
    REQUIRE(l_called == true);

}
