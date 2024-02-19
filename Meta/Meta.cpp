/** @file Meta.cpp
 * @brief Defines everything in the @ref MetaMod module.
 *  
 */
#include "Meta.hpp"

#include <stdlib.h>

#ifdef ADDITIONAL_INCLUDE
#include ADDITIONAL_INCLUDE
#endif

namespace Library
{

    //This code is hard to read so here it is described with words:
    //
    //If a overwrite macro for some default is defined set it to that macro,
    //otherwise set it to the default value, default values are listed bellow.
    //
    //Default allocator = malloc;
    //Default reallocator = realloc;
    //Default deallocator = free;
    //Default error callback(all) = nullptr;
    //Default error callback data(all) = nullptr;

    #ifndef OVERWRITE_DEFAULT_ALLOCATOR
        const Allocator g_DEFAULT_ALLOCATOR = malloc;
    #else
        const Allocator g_DEFAULT_ALLOCATOR = OVERWRITE_DEFAULT_ALLOCATOR;
    #endif //OVERWRITE_DEFAULT_ALLOCATOR

    #ifndef OVERWRITE_DEFAULT_ALLOC_ERROR
        const Callback g_DEFAULT_ALLOC_ERROR = nullptr;
    #else
        const Callback g_DEFAULT_ALLOC_ERROR = OVERWRITE_DEFAULT_ALLOC_ERROR;
    #endif //OVERWRITE_DEFAULT_ALLOC_ERROR

    #ifndef OVERWRITE_DEFAULT_ALLOC_ERROR_DATA
        void* const g_DEFAULT_ALLOC_ERROR_DATA = nullptr;
    #else
        void* const g_DEFAULT_ALLOC_ERROR_DATA = OVERWRITE_DEFAULT_ALLOC_ERROR_DATA;
    #endif //OVERWRITE_DEFAULT_ALLOC_ERROR_DATA


    #ifndef OVERWRITE_DEFAULT_REALLOCATOR
        const Reallocator g_DEFAULT_REALLOCATOR = realloc;
    #else
        const Reallocator g_DEFAULT_REALLOCATOR = OVERWRITE_DEFAULT_REALLOCATOR;
    #endif //OVERWRITE_DEFAULT_REALLOCATOR

    #ifndef OVERWRITE_DEFAULT_REALLOC_ERROR
        const Callback g_DEFAULT_REALLOC_ERROR = nullptr;
    #else
        const Callback g_DEFAULT_REALLOC_ERROR = OVERWRITE_DEFAULT_REALLOC_ERROR;
    #endif //OVERWRITE_DEFAULT_REALLOC_ERROR

    #ifndef OVERWRITE_DEFAULT_REALLOC_ERROR_DATA
        void* const g_DEFAULT_REALLOC_ERROR_DATA = nullptr;
    #else
        void* const g_DEFAULT_REALLOC_ERROR_DATA = OVERWRITE_DEFAULT_REALLOC_ERROR_DATA;
    #endif //OVERWRITE_DEFAULT_REALLOC_ERROR_DATA


    #ifndef OVERWRITE_DEFAULT_DEALLOCTOR
        const Deallocator g_DEFAULT_DEALLOCATOR = free;
    #else
        const Deallocator g_DEFAULT_DEALLOCATOR = OVERWRITE_DEFAULT_DEALLOCATOR;
    #endif //OVERWRITE_DEFAULT_DEALLOCATOR

}
