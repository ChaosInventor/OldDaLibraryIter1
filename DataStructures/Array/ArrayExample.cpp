//TODO: Decide if to keep this file or not.

#include <stdlib.h>
#include <Array.hpp>

using namespace Library::DataStructures::Array;

int randoSum(unsigned int p_number_of_rands)
{

    //Can't really do anything in this case.
    if(p_number_of_rands == 0)
    {
        //"In case of any failures return 0" - the incredible spec UwU.
        return 0;
    }

    //This is our array
    Array<int> l_array;

    //Makes an array that can hold p_number_of_rands ints.
    CreateArrayAtOfCapacity(l_array, p_number_of_rands);
    //There is a lot happening in this one line. First l_array is being
    //implicitly converted to an int*, the value of this int* is the array's
    //buffer which is the memory region that the array uses to store it's items.
    //You can also access the buffer directly by doing l_array.m_Buffer.
    //
    //Next we are comaring the array's buffer with null since if the above
    //creation function fails due to allocation failure the array's buffer will
    //be set to 0.
    if(l_array == nullptr)
    {
        //"In case of any failures return 0" - the incredible spec UwU.
        return 0;
    }

    //Just your normal for loop.
    for(Size i = 0; i < p_number_of_rands; ++i)
    {
        //Here we're calling the array's overloaded [] operator. This is
        //equivalent to doing l_array.m_Buffer[i].
        l_array[i] = rand();
    }

    //Ok so the array has 2 numbers: m_Size and m_Capacity.
    //m_Capacity tells us how many items the array CAN store MAX.
    //m_Size tells us how many items the array IS storing CURRENTLY.
    //
    //This can be useful for addition and removal, instead of always doing a 
    //reallocation we change m_Size.
    //
    //Since we manually added items with the above loop we'll need to update
    //the size. The size by default is 0.
    l_array.m_Size = p_number_of_rands;

    //Odd + even = odd
    for(Size i = 1; i < p_number_of_rands; i += 2)
    {
        l_array[i] *= 3;   
    }

    //Even + even = even
    for(Size i = 0; i < p_number_of_rands; i += 2)
    {
        AddArrayToArrayAfterIndex<int>(
            rand(), //The array we're adding FROM. Wait a minute this isn't an
            //array! Thats right, you can create a temporary array from a single
            //item. This temporary array has its buffer set to the memory
            //address of the item and its m_Size and m_Capacity to 1. Note:
            //In function calls such as this you must specify the type. You
            //can see this here, int is specified in the angle brackets. If you
            //don't do this your compiler will get confused and refuse to
            //compile your source code.
            l_array, //The array we're adding TO.
            i, nullptr, nullptr //The index and callbacks.
        );
    }

    int l_result = 0;
    //Since we added items in the last step the p_number_of_rands number no
    //longer represents the actual number of items in the array. Now we must use
    //th array's size. We cannot use the array's capacity since the add function
    //might of allocated more memory than necessary.
    for(Size i = 0; i < l_array.m_Size; ++i)
    {
        l_result += l_array[i];
    }

    //Remember, data structures in the library don't manage their own resources!
    DestoryArray(l_array);
    return l_result;

}