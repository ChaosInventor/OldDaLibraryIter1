/**
 * @ingroup DebuggingMod
 * @file Debugging.cpp
 * @brief Implements all of the testing helper functions of the
 * @ref DebuggingMod module.
 * 
 */
#include "Debugging.hpp"

#include <stdlib.h>

namespace Debugging
{
    //This is where the hidden global variables are stored.
    namespace
    {
        //This variable is used as the counter for NullMallocAfterCount
        Library::Size g_NullMallocCount = 0;
        //This variable is used as the counter for NullReallocAfterCount
        Library::Size g_NullReallocCount = 0;
    }
}

void* Debugging::NullMalloc(Library::Size p_size)
{
    (void)p_size; //Ignore p_size.
    return nullptr;
}

void* Debugging::NullRealloc(void* p_pointer, Library::Size p_size)
{
    //Ignore both paramters.
    (void)p_pointer;
    (void)p_size;
    return nullptr;
}

void Debugging::SetCountOfNullMallocAfterCount(const Library::Size& p_count)
{
    g_NullMallocCount = p_count;
}
void* Debugging::NullMallocAfterCount(Library::Size p_size)
{

    if(g_NullMallocCount > 0)
    {
        --g_NullMallocCount;
        return malloc(p_size);
    }

    return nullptr;

}

void Debugging::SetCountOfNullReallocAfterCount(const Library::Size& p_count)
{
    g_NullReallocCount = p_count;
}
void* Debugging::NullReallocAfterCount(void* p_pointer, Library::Size p_size)
{

    if(g_NullReallocCount > 0)
    {
        --g_NullReallocCount;
        return realloc(p_pointer, p_size);
    }
    
    return nullptr;    

}

void Debugging::GeneralErrorCallback(void* p_pointer)
{
    *((bool*)p_pointer) = true;
}
