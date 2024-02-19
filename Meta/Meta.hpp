/**
 * @file Meta.hpp
 * @brief This file contains declarations for default and global values used
 * throughout the library.
 *
 * @details @section LibraryMetahpp_Overview Overview
 * This file is one of the most important files in the library. It is
 * include in nearly all other files.
 * Everything in this file is declared under the Library::LibraryMeta namespace.
 * The reason this file is important is since it declares the default:
 * - Allocator and its callbacks;
 * - Reallocator and its callbacks;
 * - Deallocator;
 * - Standard streams.
 *
 * See each defaults documentation for more info.
 * All of the defaults are defined in the LibraryMeta.cpp file.
 *
 * @section LibraryMetahpp_Overwriting Overwriting default values
 * Additionally all default values can be overwritten at comple time by defining
 * a macro of the form (case sensitive) OVERWRITE_<NAME OF DEFAULT>, note that
 * any prefix (g_ p_ m_ l_) does not go into the macro name.
 *
 * After the macro for the required default is defined, the value of the default
 * will be set to be equaled to the macro its self.
 *
 * In order for this to take effect the LibraryMeta.cpp file needs to be
 * recompiled, for this reason LibraryMeta can be linked dynamicly to the main
 * program if for some reason the default values need to change after compilation.
 *
 * @subsection LibraryMetahpp_Include_extrenal_files Include extrenal files
 * If the default value you are trying to overwrite in declared in the another
 * header file you can define yet another macro (yes i know lots of macros, but
 * what can ya do ;p) called ADDITIONAL_INCLUDE. If this macro is defined then
 * a #include statment is added in the cpp file that includes the value of the
 * macro or in other words this:
 * @code{.cpp}
 * #include ADDITIONAL_INCLUDE
 * @endcode
 * This also requires recompilation to take effect. See
 * <a href="https://gcc.gnu.org/onlinedocs/cpp/Computed-Includes.html"> computed
 * include</a> for more info. If you need to include multiple files then one
 * solution is to make a file that includes everything else you need or
 * alternately just modify the LibraryMeta.cpp file, like who cares.
 *
 * @subsection LibraryMetahpp_Overwrite_example Example
 * For an example lets say you think that malloc is crap and you would like to
 * overwrite the default allocator with your own custom one called CoolMalloc.
 * CoolMalloc is defined in the in the header CoolAllocation.hpp. What you would
 * do is define the ADDITIONAL_INCLUDE macro to be <CoolAllocation.hpp>, note
 * you can also use "CoolAllocation.hpp" if you would like to. For the sake of
 * this example we will assume that CoolAllocation.hpp is in one of your include
 * paths. Next you would define OVERWRITE_DEFAULT_ALLOCATOR to be CoolMalloc.
 * The default allocator is a function REFERENCE so you don't need to put a &
 * at the beginning. Now you compile your LibraryMeta.cpp file and ta-da no more
 * malloc just CoolMalloc. A concret code example where you define the overwrite
 * macros in a file would be:
 * @code{.cpp}
 * #define ADDITIONAL_INCLUDE "CoolAllocation.hpp"
 * #define OVERWRITE_DEFAULT_ALLOCATOR CoolMalloc
 * @endcode
 *
 * @section Libraymetahpp_Rational Rational
 * Why do these defaults even exist?\n
 * -The reason for them to exist is simple, it makes fine tuning and configuring
 * the library much more easier, instead of modifying individual modules you can
 * simply modify this central file.
 *
 * Why have all of those overwrite macros?\n
 * -This is to enable a way to change the default values without changing any
 * actual code, while you could do it it makes the entire process much more
 * cleaner and easyier.
 *
 * @section Librarymetahpp_IORelationship Library meta and IO's Relationship
 * IO is only included by this file if DEBUG is defined, making IO a conditional
 * dependence for library meta. Additionally if IO is included anywhere else or
 * by this file in the case of DEBUG, all of the standard streams are defined in
 * this file. This is done by checking if IO's include guard is defined. The
 * reason why this is done is so that all of the configuration of the library
 * is in one file, otherwise it would make much more sense to put the redefinitions
 * of the standard streams in IO.hpp.
 *
 */
#ifndef META__META_META_HPP
#define META__META_META_HPP

//Included for the definition of size_t
#include <stddef.h>
//Included for SIZE_MAX and UINT8_MAX
#include <stdint.h>
//Included for CHAR_BIT
#include <limits.h>

namespace Library
{

    /**
     * @ingroup MetaMod
     * @brief The smallest addressable unit of memory.
     * 
     * @details This type is an unsigned integer that represent the smallest
     * addressable unit of memory.
     * 
     * You should use this type for when ever you need the smallest possible
     * number.
     * 
     * The value that this type can hold ranges from 0 to
     * @ref Library::BYTE_MAXIMUM, inclusive.
     * 
     * This type is defined to make the code more readable, unsigned char is
     * harder to type than and it also makes less sense than Byte.
     * 
     * Currently this type is implemented as a unsigned char. This is subject to
     * change in the future, do not depend of these implementation details.
     * 
     */
    using Byte = unsigned char;
    /**
     * @ingroup MetaMod
     * @brief The maximum value that a @ref Library::Byte can hold.
     * 
     * @details This macro expands into a number or expression that calculates
     * a number.
     * 
     * Currently this macro is defined as UINT8_MAX.
     * 
     */
    #define BYTE_MAXIMUM UINT8_MAX
    /**
     * @ingroup MetaMod
     * @brief The number of bits that a single @ref Library::Byte occupies.
     * 
     * @details This macro expands into a number or expression that calculates
     * a number.
     * 
     * Currently this macro is defined as CHAR_BIT.
     * 
     */
    #define BITS_PER_BYTE CHAR_BIT

    /**
     * @ingroup MetaMod
     * @brief A type that can hold the maximum size of any possible object of
     * any type.
     * 
     * @details This type is an unsigned integer that can hold values the size,
     * **expressed in bytes**, of any possible object of any type.
     * 
     * The value of type type can range from 0 to @ref Library::SIZE_MAXIMUM,
     * inclusive.
     * 
     * This type is ideally used for indexing and keeping size information on
     * objects.
     * 
     * Currently this type is implemented as size_t. This is subject to change
     * in the future, do not depend on these implementation details.
     * 
     */
    using Size = size_t;
    /**
     * @ingroup MetaMod
     * @brief The maximum value that a @ref Library::Size can hold.
     * 
     * @details This macro expands into a number or expression that calculates
     * a number.
     * 
     * Currently this macro is defined as SIZE_MAX.
     * 
     */
    #define SIZE_MAXIMUM SIZE_MAX

    /**
     * @ingroup MetaMod
     * @brief An alias for a function reference that can be used to allocate
     * memory.
     * 
     * @details The function reference takes the form of: void* (&) (Size).
     * 
     * **ALL Allocator type objects MUST behave like malloc.** If a variable is
     * of this type and that variable does not refer to a function that behaves
     * like malloc, it is considered a bug and using the function reference is
     * undefined behaviour.
     * 
     * If a variable is of this type then you can assume that you can safely
     * call it.
     * 
     * //TODO: Mention how allocators, reallocators and deallocators come in
     * "bundels".
     * 
     * This type is defined for:
     * - The sake of convenience, typing and reading the complex function
     * reference syntax is hard, this type makes it easier.
     * - Better documentation, in the HTML generated documentation, wherever
     * this type is used a link will be automatically generated to this
     * documentation which allows for a quick way to find out what an allocator
     * is in the contex of the library.
     * 
     */
    using Allocator = void* (&) (Size);
    /**
     * @ingroup MetaMod
     * @brief 
     * 
     */
    using Reallocator = void* (&) (void*, Size);
    /**
     * @ingroup MetaMod
     * @brief 
     * 
     */
    using Deallocator = void (&) (void*);
    /**
     * @ingroup MetaMod
     * @brief 
     * 
     */
    using Callback = void (*) (void*);
    

    /**
     * @ingroup MetaMod
     * 
     * @brief A function reference to the default allocator.
     * @details The default allocator is a function reference that allocates the
     * given amount of bytes and returns a pointer at the start of that byte
     * block, in other words malloc. ALL allocators are required to behave like
     * malloc. Since this is a function reference it is garanteed to exist so no
     * need to check for it.
     *
     * The overwrite macro for this value is:
     * @code{.cpp}
     * OVERWRITE_DEFAULT_ALLOCATOR
     * @endcode
     * If you don't know what an overwrite is please refer to the file docs at
     * @ref LibraryMetahpp_Overwriting :).
     *
     * This value MUST NOT be mutated at runtime, i mean not that you really can.
     *
     */
    extern const Allocator g_DEFAULT_ALLOCATOR;
    /**
     * @ingroup MetaMod     
     * @brief A function pointer that should be called when allocation fails and
     * who ever did the allocation cannot recover from it them selfs AND at the
     * same time a diffrent callback was not provided.
     *
     * @details This is a simple callback that takes a void* as its paramaters
     * and returns nothing. In this specific case this callback should always
     * be called with @ref Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR_DATA
     * even if the data is null.
     *
     * This specific callback should mainly be called on allocation failure of
     * any allocator, not just the default one and of course if a recovery from
     * the error can be made the callback should not be called.
     *
     * The overwrite macro for this one is:
     * @code{.cpp}
     * OVERWRITE_DEFAULT_ALLOC_ERROR
     * @endcode
     * If you don't know what an overwrite is please refer to the file docs at
     * @ref LibraryMetahpp_Overwriting :).
     *
     * This value MUST NOT be mutated at runtime, it's const for a reason >.>.
     *
     * @warning Since this is a function pointer the value may be null ALWAYS
     * check if this callback exists before calling, heck the default value IS
     * null.
     *
     * @param p_data A void pointer to some data, may be null. The callback (if any)
     * is resposible for intepreting it.
     *
     */
    extern const Callback g_DEFAULT_ALLOC_ERROR;
    /**
     * @ingroup MetaMod     
     * @brief This is a pointer to some data that may or may not be null.
     *
     * @details This pointer should be passed to the default alloc error callback
     * @ref Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR. What this pointer
     * points to and how it should be interpreted is entirely up to the callback.
     *
     * The overwrite macro is;
     * @code{.cpp}
     * OVERWRITE_DEFAULT_ALLOC_ERROR_DATA
     * @endcode
     * If you don't know what an overwrite is please refer to the file docs at
     * @ref LibraryMetahpp_Overwriting :).
     *
     * @warning This pointer may be null, c'mon the default value IS null.
     *
     */
    extern void* const g_DEFAULT_ALLOC_ERROR_DATA;

    /**
     * @ingroup MetaMod
     * @brief A function reference to the default reallocator.
     *
     * @details This function should be used when you need to reallocate some
     * thing that was previously allocated with the default allocator, a new
     * buffer will be given with the desired new size and yes, ALL reallocators
     * are required to behave like realloc. The only memory that should be
     * reallocated with this function should be one that was previously allocated
     * with the default allocator, @ref Library::LibraryMeta::g_DEFAULT_ALLOCATOR,
     * but of course if you DO decide to do some funky stuff with this, you do you
     * i won't judge ;).
     *
     * Since this is a function reference there is no need to check if it exist,
     * its existence is guranteed.
     *
     * The overwrite macro for this one is:
     * @code{.cpp}
     * OVERWRITE_DEFAULT_REALLOCATOR
     * @endcode
     * If you don't know what an overwrite is please refer to the file docs at
     * @ref LibraryMetahpp_Overwriting :).
     *
     * This value MUST NOT be mutated at run time.
     *
     */
    extern const Reallocator g_DEFAULT_REALLOCATOR;
    /**
     * @ingroup MetaMod     
     * @brief A function pointer to a callback that should be called when
     * reallocation fails, there is not way to recover from it AND another
     * callback is not provided.
     *
     * @details This callback is practically the same as
     * @ref Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR except that instead of
     * allocation we are dealing with reallocation which in the contex of a
     * callback doesn't really change much, so in order to avoid copy, paste,
     * find and repace just read the details for the allocation callback.
     *
     * The overwrite for this one is:
     * @code{.cpp}
     * OVERWRITE_DEFAULT_REALLOC_ERROR
     * @endcode
     * If you don't know what an overwrite is please refer to the file docs at
     * @ref LibraryMetahpp_Overwriting :).
     *
     * This value MUST NOT be mutated at run time.
     *
     * @warning This is a function pointer so before calling it ALWAYS check
     * that it is not a null pointer, an if a day keeps the seg fault away.
     *
     */
    extern const Callback g_DEFAULT_REALLOC_ERROR;
    /**
     * @ingroup MetaMod     
     * @brief A pointer to some data that may be null.
     *
     * @details This is practically the same as
     * @ref Library::LibraryMeta::g_DEFAULT_ALLOC_ERROR_DATA so just read that
     * and instead of allocation we are thinking about reallocation.
     *
     * The overwrite for this one is:
     * @code{.cpp}
     * OVERWRITE_REALLOC_ERROR_DATA
     * @endcode
     * If you don't know what an overwrite is please refer to the file docs at
     * @ref LibraryMetahpp_Overwriting :).
     *
     * This value MUST NOT be mutated at run time.
     *
     */
    extern void* const g_DEFAULT_REALLOC_ERROR_DATA;

    /**
     * @ingroup MetaMod     
     * @brief A function reference to the default deallocator.
     *
     * @details This is a function reference that frees up the given memory that
     * was previously either allocated or deallocated with the default allocator
     * or reallocator and yes ALL deallocators should behave like free.
     *
     * This deallocator should only be used with memory that is handeled by the
     * other default memory functions, but hey if you wanna get funky then you
     * do you.
     *
     * This is function reference so there is no need to check if it exists, it
     * is guaranteed to exist.
     *
     * The overwrite for this one is:
     * @code{.cpp}
     * OVERWRITE_DEFAULT_DEALLOCATOR
     * @endcode
     * If you don't know what an overwrite is please refer to the file docs at
     * @ref LibraryMetahpp_Overwriting :).
     *
     * Also unlike the other memory function, there are no callbacks for this
     * one since the only way this ones' failin' is by a seg fault or some
     * strange and mystical undefined behaviour :D.
     *
     * This value MUST NOT be mutated at run time.
     *
     */
    extern const Deallocator g_DEFAULT_DEALLOCATOR;

}

#endif //META__META_META_HPP