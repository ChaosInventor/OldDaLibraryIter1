/**
 * @ingroup DebuggingMod
 * @file Debugging.hpp @details 
 * @brief Declares all of the testing helper functions of the
 * @ref DebuggingMod module.
 * 
 * @details See the @ref Debugging namespace for details.
 * 
 */

#ifndef DEBUGGING__DEBUGGING_DEBUGGING_HPP
#define DEBUGGING__DEBUGGING_DEBUGGING_HPP

#include "../Meta/Meta.hpp"

/**
 * @ingroup DebuggingMod
 * @brief The namespace under which all of the members of the @ref DebuggingMod
 * module can be found.
 * 
 * @details You can use the members of this namespace to:
 * - Test allocation failure (see @ref NullMalloc @ref NullMallocAfterCount).
 * - Test reallocation failure (see @ref NullRealloc @ref NullReallocAfterCount).
 * - Test if a callback was called (see @ref GeneralErrorCallback)
 * - Log (see @ref LogDebugLine)
 * 
 */
namespace Debugging
{

    /**
     * @brief Always returns nullptr when called.
     * 
     * @details This function can be used to simulate an allocation error. To do
     * so pass this function as the allocator for what ever you are testing.
     * 
     * @param p_size This paramater is ignored and is only here so that the
     * function has the same function signature as an allocator.
     * 
     * See also @ref NullRealloc, @ref NullMallocAfterCount.
     *  
     */
    void* NullMalloc(Library::Size p_size);

    /**
     * @brief Sets the count of @ref NullMallocAfterCount.
     * 
     * @details This function is used to set the the hidden global variable of
     * @ref NullMallocAfterCount to p_count.
     * 
     * The hidden global variable dictates how many allocations need to occur
     * before @ref NullMallocAfterCount starts returning null. See
     * @ref NullMallocCountWork for more info on the subject.
     * 
     * See also @ref NullMallocAfterCount.
     * 
     * @param p_count The number of allocations that must occur before
     * @ref NullMallocAfterCount starts returning null.
     *  
     */
    void SetCountOfNullMallocAfterCount(const Library::Size& p_count);
    /**
     * @brief Returns null after some number of allocations.
     * 
     * @details This function can be used to simulate an allocation failure
     * that needs to occur after a series of other successful allocations.
     * This is useful, for example, when a function allocates memory multiple
     * times, and you need to test if it properly handels a scenario where, for
     * example, the second allocation fails.
     *  
     * @section NullMallocCountWork How NullMallocAfterCount works
     * 
     * This function works by keeping a count in a global hidden variable in
     * Debugging.cpp. **The default value of the count is 0**. Each time this
     * function is called, it checks the count and if it is:
     * - >0, the function decrements the count and returns the return value
     * of malloc called with p_size.
     * - =0, the function returns null.
     * 
     * In order to set the value of this count use the
     * @ref SetCountOfNullMallocAfterCount function.
     * 
     * @section NullMallocCountUseHow How to use this function
     * 
     * To use this function:
     * -# Use @ref SetCountOfNullMallocAfterCount to set the number of
     * allocations that need to be done before this function starts to return null.
     * -# Pass this function as an allocator to what ever you are testing.
     * 
     * @section NullMallocCountCaveats Caveats
     * 
     * Because this function uses global state, **it is not thread safe**. For
     * more info see @ref NullMallocCountWork.
     * 
     * You must free the memory allocated with this function. malloc is used to
     * allocation so free should be used for deallocation.
     * 
     * When calling malloc it may fail and return null before the count reaches
     * 0. There is nothing you can really do about this though, however it is
     * useful to keep in mind.
     * 
     * See also @ref SetCountOfNullMallocAfterCount, @ref NullMalloc,
     * @ref NullReallocAfterCount.
     * 
     */
    void* NullMallocAfterCount(Library::Size p_size);


    /**
     * @brief Always returns nullptr when called.
     * 
     * @details This function can be used to simulate a reallocation error. To
     * do so pass this function as the reallocator for what ever you are testing.
     * 
     * @param p_size This paramater is ignored and is only here so that the
     * function has the same function signature as a reallocator.
     * @param p_pointer This paramater is ignored and is only here so that the
     * function has the same function signature as a reallocator.
     * 
     * See also @ref NullMalloc, @ref NullReallocAfterCount.
     *  
     */
    void* NullRealloc(void* p_pointer, Library::Size p_size);

    /**
     * @brief Sets the count of @ref NullReallocAfterCount.
     * 
     * @details This function is used to set the the hidden global variable of
     * @ref NullReallocAfterCount to p_count.
     * 
     * The hidden global variable dictates how many reallocations need to occur
     * before @ref NullReallocAfterCount starts returning null. See
     * @ref NullReallocCountWork for more info on the subject.
     * 
     * See also @ref NullMallocAfterCount.
     * 
     * @param p_count The number of reallocations that must occur before
     * @ref NullMallocAfterCount starts returning null.
     *  
     */
    void SetCountOfNullReallocAfterCount(const Library::Size& p_count);
    /**
     * @brief Returns null after some number of reallocations.
     * 
     * @details This function can be used to simulate a reallocation failure
     * that needs to occur after a series of other successful reallocations.
     * This is useful, for example, when a function reallocates memory multiple
     * times, and you need to test if it properly handels a scenario where, for
     * example, the fourth reallocation fails.
     *  
     * @section NullReallocCountWork How NullReallocAfterCount works
     * 
     * This function works by keeping a count in a global hidden variable in
     * Debugging.cpp. **The default value of the count is 0**. Each time this
     * function is called, it checks the count and if it is:
     * - >0, the function decrements the count and returns the return value
     * of realloc called with p_size and p_pointer.
     * - =0, the function returns null.
     * 
     * In order to set the value of this count use the
     * @ref SetCountOfNullReallocAfterCount function.
     * 
     * @section NullReallocCountUseHow How to use this function
     * 
     * To use this function:
     * -# Use @ref SetCountOfNullReallocAfterCount to set the number of
     * reallocations that need to be done before this function starts to return
     * null.
     * -# Pass this function as a reallocator to what ever you are testing.
     * 
     * @section NullReallocCountCaveats Caveats
     * 
     * Because this function uses global state, **it is not thread safe**. For
     * more info see @ref NullReallocCountWork.
     * 
     * The memory reallocated with this function must be allocated using malloc.
     * This is because realloc is used internally in the function.
     * 
     * When calling realloc it may fail and return null before the count reaches
     * 0. There is nothing you can really do about this though, however it is
     * useful to keep in mind.
     * 
     * See also @ref SetCountOfNullReallocAfterCount, @ref NullRealloc,
     * @ref NullMallocAfterCount.
     * 
     */
    void* NullReallocAfterCount(void* p_pointer, Library::Size p_size);


    /**
     * @brief A function that can be used to check if a callback was called.
     * 
     * @details This functions assumes that p_data is of type bool*. p_data is
     * dereferenced and set to true.
     * 
     * @warning If p_data is NOT a valid pointer to a bool, the behavior of this
     * function is **undefined**.
     * 
     * @section GeneralCallbackExample Example
     * For this example assume that there is a function called XyZ and it's
     * declaration is as follows:
     * @code{.cpp}
     * void XyZ(const Foo& p_fluf_mluf, void (*p_bar_err) (void*), void* p_bar_err_data);
     * @endcode
     * Assume that Foo is some object that XyZ does work on.
     * 
     * Now during XyZ's very important work, there is a case where p_fluf_mluf
     * is invalid. When this occurs XyZ is supposed to call p_bar_err with
     * p_bar_err_data being the first paramater.
     * 
     * You would now want to test if XyZ properly calls p_bar_err in this
     * special case.
     * 
     * To do so you take the following steps:
     * -# Create that special invalid foo object.
     * -# Define a variable of type bool, the variable's name may be anything
     * you'd like but it is most often named l_called.
     * -# Set the bool's value to false.
     * -# Call XyZ in the following way:
     * @code{.cpp}
     * bool l_called = false;
     * XyZ(g_FILTHY_AND_DISCUSTING_FOO, &GeneralErrorCallback, &l_called);
     * //Assume that g_FILTHY_AND_DISCUSTING_FOO is the incorrect foo object you had created in step 1.
     * @endcode
     * -# After XyZ returns check the value of l_called, if l_called is true
     * the callback was called, if l_called is false then the callback was not
     * called.
     * 
     */
    void GeneralErrorCallback(void* p_data);

}

#endif //DEBUGGING__DEBUGGING_DEBUGGING_HPP
