/** @file Array.hpp
 * @brief Defines everything in the @ref ArrayMod module.
 * 
 */


#ifndef ARRAY__DATA_STRUCTURES_ARRAY_ARRAY_HPP
#define ARRAY__DATA_STRUCTURES_ARRAY_ARRAY_HPP

#include "../../Meta/Meta.hpp"
#include "../../Debugging/Logging/Log.hpp"

/**
 * @brief A
 * 
 */
namespace Library::DataStructures::Array
{

    /**
     * @brief A data structure used for addressing a continuous block of items
     * of type T with a dynamic size and capacity. 
     *
     * @details This structure works by keeping 3 sperate pieces of information,
     * those being a pointer to a region of memory that has items of type T,
     * the number of items currently present in that memory region starting from
     * the pointer and the maximum number of items that can be put into the
     * memory region. The filed names for these are m_Buffer for the pointer,
     * m_Size for the number of items and m_Capacity for the maximum number of
     * items.
     * 
     * //TODO: Undefind behaviour for bad fields.
     * 
     * //TODO: m_Buffer does not have to be heap memory and does and does not
     * need to be freed.
     * 
     * @section ArrayTypes Types of arrays
     * Depending on the state of the 3 fields, the array is said to be some
     * type:
     * 
     * @subsection ArrayTypesNull Null array
     * This array has its m_Buffer set to null, m_Size and
     * m_Capacity set to 0. No items can be stored into or gotten from this
     * array.
     * 
     * @subsection ArrayTypesEmpty Empty array
     * This array has a non null m_Buffer, its m_Size is 0 and
     * its m_Capacity is greater than 0. This type of array can hold m_Capacity
     * items, but has no items.
     * 
     * @subsection ArrayTypesAvailable Available array
     * This array has a non null m_Buffer, its m_Size is
     * greater than 0 but less than its m_Capacity, which is greater than 0.
     * This type of array can hold m_Capacity - m_Size items and has m_Size
     * items.
     * 
     * @subsection ArrayTypesFull Full array
     * This array has a non null m_Buffer, its m_Size is the same
     * as its m_Capacity. m_Capacity is greater than 0. This type of array has
     * m_Capacity items, but cannot store any more items.
     * 
     * @subsection ArrayTypesInvalid Invalid array
     * Any array that is not in any of the above types is this
     * type. Its behaviour is undefined in the contex of this module, its use
     * is not recommended.
     * 
     * 
     * //TODO: Resizing
     * 
     * @tparam T The type of data that this array will store. This type must be
     * a complete type can be:
     * -# Copied using =;
     * -# Moved using =;
     * -# Compared to itself using == and !=;
     * -# Default constructed.
     * 
     */
    template<typename T>
    struct Array
    {

        /**
         * @brief A pointer to the buffer of item, its size is @ref m_Capacity,
         * but only @ref m_Size is used (may be null).
         * 
         * @details If this pointer is null then the array is said to be empty
         * and the values of @ref m_Size and @ref m_Capacity may be any value
         * that may or may not make logical sense.
         * 
         */
        T* m_Buffer;
        /**
         * @brief How many items are defined in the buffer.
         * 
         * @details If this value is greater than @ref m_Capacity, and at the same
         * time @ref m_Buffer is NOT null, using that array is undefined behaviour.
         * 
         */
        Size m_Size;
        /**
         * @brief How many items the buffer can hold maximum.
         * 
         * @details If this value is 0 and @ref m_Buffer is not null the
         * behaviour is undefined.
         * 
         */
        Size m_Capacity;

        /**
         * @brief Sets @ref m_Buffer to nullptr, @ref m_Size and @ref m_Capacity
         * are uninitalized.
         * 
         */
        Array():
        m_Buffer(nullptr),
        m_Size(0),
        m_Capacity(0)
        {
            LogDebugLine("Constructing an empty array at " << this);
        }
        /**
         * @brief Sets each member to its coresponding paramater, 
         * @ref m_Capacity is set to @ref p_size.
         * 
         * @param p_buffer The pointer its self is copied to @ref m_Buffer.
         * @param p_size This is copied to @ref m_Size and @ref m_Capacity.
         * 
         */
        Array(T* const p_buffer, const Size& p_size)
        :
        m_Buffer(p_buffer),
        m_Size(p_size),
        m_Capacity(p_size) 
        {
            LogDebugLine(
                "Constructing array with buffer " << (void*)p_buffer << 
                " and size " << p_size  << " at " << this
            );
        }
        /**
         * @brief Sets each member to its coresponding paramater.
         * 
         * @details If @ref p_size is grater than @ref p_capacity then using
         * the array with those values is undefined behaviour.
         * 
         * @param p_buffer The pointer its self is copied to @ref m_Buffer.
         * @param p_size This is copied to @ref m_Size.
         * @param p_capacity This is copied to @ref m_Capacity.
         * 
         */
        Array(T* const p_buffer, const Size& p_size, const Size& p_capacity)
        :
        m_Buffer(p_buffer),
        m_Size(p_size),
        m_Capacity(p_capacity)
        {
            LogDebugLine(
                "Constructing array with buffer " << (void*)p_buffer << " with size" <<
                p_size << " and capacity " << p_capacity << " at " << this
            );
        }
        /**
         * @brief Creates a array that only has 1 item, p_item.
         * 
         * @details m_Buffer is set to the address of p_item, m_Size and
         * m_Capacity are set to 1.
         * 
         * @param p_item A reference to the item, **assumed to be a valid
         * reference that has the same or greater life time than the array.**
         * 
         * The main point of this constructor is to give an easy way of creating
         * arrays that act as single items. This is useful for when you want to
         * for example add a single item to an array using the
         * @ref AddArrayToArrayAfterIndexUsingReallocator function or for
         * searching for a single item using the
         * @ref FindIndexOfFirstOccurrenceOfArrayInArray function.
         * 
         */
        Array(T& p_item):
        m_Buffer(&p_item),
        m_Size(1),
        m_Capacity(1)
        {
            LogDebugLine("Constructed single item array from item at " << (void*)&p_item);
        }
        /** //TODO: Clean up docs
         * @brief Creates a array that only has 1 item, p_item.
         * 
         * @details m_Buffer is set to the address of p_item, m_Size and
         * m_Capacity are set to 1.
         * 
         * @param p_item A reference to the item, **assumed to be a valid
         * reference that has the same or greater life time than the array.**
         * 
         * The main point of this constructor is to give an easy way of creating
         * arrays that act as single items. This is useful for when you want to
         * for example add a single item to an array using the
         * @ref AddArrayToArrayAfterIndexUsingReallocator function or for
         * searching for a single item using the
         * @ref FindIndexOfFirstOccurrenceOfArrayInArray function.
         * 
         */
        Array(T&& p_item):
        m_Buffer(&p_item),
        m_Size(1),
        m_Capacity(1)
        {
            LogDebugLine("Constructed single item array from item at " << (void*)&p_item);
        }

        /**
         * @brief Copies all members from @ref p_other to this array.
         * 
         * @details @ref m_Buffer is copied as a raw pointer, no new memory is
         * allocated and the same pointer is used.
         * 
         * @warning This can be very dangerous since the pointer is copied raw.
         * 
         * @param p_other Where to copy from.
         */
        Array(const Array<T>& p_other):
        m_Buffer(p_other.m_Buffer),
        m_Size(p_other.m_Size),
        m_Capacity(p_other.m_Capacity) 
        {
            LogDebugLine("Constructing copy from " << p_other << " to " << *this);
        }
        /**
         * @brief Same as @ref Array(const Array& p_other) except the other
         * arrays @ref m_Buffer is set to null. 
         * 
         */
        Array(Array<T>&& p_other):
        m_Buffer(p_other.m_Buffer),
        m_Size(p_other.m_Size),
        m_Capacity(p_other.m_Capacity)
        {
            LogDebugLine(
                "Constructing array by moving from " << p_other << " to " << *this
            );

            p_other.m_Buffer = nullptr;
            p_other.m_Size = 0;
            p_other.m_Capacity = 0;

        }


        /**
         * @brief The same as @ref Array(const Array& p_other).
         * 
         * @return Returns (*this). 
         * 
         */
        Array<T>& operator= (const Array<T>& p_other)
        {

            LogDebugLine("Copying array from " << &p_other << " to " << this);

            m_Buffer = p_other.m_Buffer;
            m_Size = p_other.m_Size;
            m_Capacity = p_other.m_Capacity;

            return *this;

        }
        /**
         * @brief The same as @ref Array(Array&& p_other).
         * 
         * @return Returns *this.
         *  
         */
        Array<T>& operator= (Array<T>&& p_other)
        {

            LogDebugLine("Moving array from " << p_other << " to " << *this);

            m_Buffer = p_other.m_Buffer;
            m_Size = p_other.m_Size;
            m_Capacity = p_other.m_Capacity;

            p_other.m_Buffer = nullptr;
            p_other.m_Capacity = 0;
            p_other.m_Size = 0;

            return *this;

        }


        /**
         * @brief Returns @ref m_Buffer. 
         *  
         */
        operator T*() const
        {
            LogDebugLine("Returning m_Buffer = " << (void*)m_Buffer);
            return m_Buffer;
        }
        /**
         * @brief Returns a COPY of @ref m_Size. 
         * 
         */
        operator Size() const
        {
            LogDebugLine("Returning m_Size = " << m_Size);
            return m_Size;
        } 


        /**
         * @brief Returns m_Buffer[p_index].
         * 
         * @details If the given index is invalid or if this list is empty then
         * the behaviour is undefined.
         * 
         * @param p_index The index to use, if it is invalid then the behaviour
         * is undefined.
         *  
         */
        T& operator[] (const Size& p_index)
        {
            LogDebugLine(
                "Index operator called for array " << *this << " and with index "
                << p_index
            );
            #ifdef DEBUG
            if(p_index >= m_Capacity)
            {
                LogDebugLine("\n------\nError invalid index " << p_index
                << " in array " << *this << ", aborting proccess... (Note: this"
                " sort of check only occurs when DEBUG is defined, otherwise "
                "the behaviour is undefined.\n------\n");
                abort();
            }
            #endif //DEBUG
            return m_Buffer[p_index];
        }
        /**
         * @brief Returns m_Buffer[p_index], readonly version.
         * 
         * @details If the given index is invalid or if this list is empty then
         * the behaviour is undefined.
         * 
         * @param p_index The index to use, if it is invalid then the behaviour
         * is undefined.
         *  
         */
        const T& operator[] (const Size& p_index) const
        {
            LogDebugLine(
                "Index operator called for array " << *this << " and with index "
                << p_index
            );
            #ifdef DEBUG
            if(p_index >= m_Capacity)
            {
                LogDebugLine("\n------\nError invalid index " << p_index
                << " in array " << *this << ", aborting proccess... (Note: this"
                " sort of check only occurs when DEBUG is defined, otherwise "
                "the behaviour is undefined.\n------\n");
                abort();
            }
            #endif //DEBUG
            return m_Buffer[p_index];
        }

        /**
         * @brief Comapres the arrays.
         * 
         * @param p_other The other array that will be compared with this array.
         * @return True is returned if the two arrays have the same size and
         * elements in the same order. True can also be returned if the two
         * arrays are null. The capacity of the arrays is not compared. In any
         * other case false is returned.
         * 
         * @time O(n)
         * 
         */
        bool operator== (const Array<T>& p_other) const
        {

            LogDebugLine("Comparing array " << *this << " and array " << p_other);

            //If either of the arrays have null buffers then return whether both
            //of them are null.
            if(p_other.m_Buffer == nullptr || m_Buffer == nullptr)
            {
                LogDebugLine("One of the arrays has a null buffer!");
                return p_other.m_Buffer == nullptr && m_Buffer == nullptr;
            }

            //If the sizes are diffrent then return false.
            if(p_other.m_Size != m_Size)
            {
                LogDebugLine("The two arrays have diffrent sizes!");
                return false;
            }

            LogDebugLine("Starting to compare each array item.");
            //Comapres each item with each other, if any items are not equal
            //false is returned.
            for(Size i = 0; i < m_Size; ++i)
            {
                if(m_Buffer[i] != p_other.m_Buffer[i])
                {
                    LogDebugLine("Found a missmatch at index " << i);
                    return false;
                }
            }

            LogDebugLine("Both of the arrays are equal so true is being returned.");
            //If control reaches this point then the two arrays are the same.
            return true;

        }
        /**
         * @brief Returns the NOT value of @ref bool operator== (const Array<T> p_other).
         * 
         */
        bool operator!= (const Array<T>& p_other) const
        {
            LogDebugLine("Comparing non equality.");
            return !(*this == p_other);
        }

    };


    /**
     * @brief Creates an @ref ArrayTypesEmpty "empty array" at outp_array with a
     * capacity of p_capacity.
     * 
     * @details The **array is created by** allocating a buffer that is
     * sizeof(T) * p_capacity bytes long using p_allocate.
     *
     * This function **should be used for** creating brand new arrays with
     * dynamic memory.
     *  
     * @warning This function DOES NOT check if there **already is an array at
     * outp_array**, it overwrites it regardless. This could cause a memory
     * leak.
     *
     * @warning Non of **the items** in the new buffer are initalized.
     *  
     * @param outp_array Where the new array will be created.
     * @param p_capacity How many items max should the new array be abel to
     * hold. **If this argument is 0** then a @ref ArrayTypesNull "null array"
     * will be created at outp_array. See the errors section for more details.
     * @param p_allocate The allocator to use for allocating a buffer for the
     * new array. See the errors section on details on what happens when
     * allocation fails.
     * @param p_alloc_error A callback for allocation failure. See errors
     * section for details on allocation failure.
     * @param p_alloc_error_data The argument that will be passed to
     * p_alloc_error, if it is called.
     * 
     * In the case of **allocation failure**, that is p_allocate returns a null
     * pointer, the following happens:
     * -# A @ref ArrayTypesNull "null array" **is created at outp_array**.
     * -# p_alloc_error is called with p_alloc_error_data as its argument.
     * -# The function returns.
     * 
     * In the case of **p_capacity == 0** being true, a @ref ArrayTypesNull
     * "null array" is created at outp_array and the function returns.
     * p_allocate is not called, as such **no allocation failure** can occur.
     * 
     * There is one edge case that can occur, that being **sizeof(T) *
     * p_capacity overflowing.** If this happens then:
     * -# A @ref ArrayTypesNull "null array" **is created at outp_array**.
     * -# The function returns.
     * p_allocate is not called, as such **no allocation failure** can occur.
     * 
     * The best way to **check if this function failed** is to do the following:
     * @code{.cpp}
     * if(outp_array.m_Capacity != p_capacity)
     * {
     *      //Error occurred.
     * }
     * else
     * {
     *      //Error did not occur.
     * }
     * @endcode
     * 
     * @sa DestroyArrayUsingDeallocator CreateCopyAtOfArrayUsingAllocator
     * 
     */
    template<typename T>
    void CreateArrayAtOfCapacityUsingAllocator(
        Array<T>& outp_array,
        const Size& p_capacity,
        Allocator p_allocate, Callback p_alloc_error, void* p_alloc_error_data
    )
    {

        LogDebugLine(
            "Creating array at " << &outp_array << " with capacity " << p_capacity
        );

        if(p_capacity == 0)
        {
            LogDebugLine("The given capacity is 0, returning.");
            return;
        }

        //This checks if sizeof(T) * p_capacity overflows if it does then create
        //an empty array and return. Note: p_capacity is guranteed to be greater
        //than 0 because of the above if statement
        if(p_capacity > SIZE_MAX / sizeof(T))
        {
            LogDebugLine(
                "Unsigned multiplication overflow detected during allocation of "
                " array buffer at line " << __LINE__ << " and in file " << __FILE__
                << "Creating an empty array and returning"
            );
            outp_array = Array<T>();

            return;
        }

        outp_array.m_Buffer = (T*)p_allocate(sizeof(T) * p_capacity);
        if(outp_array.m_Buffer == nullptr)
        {
            LogDebugLine(
                "Allocation error occurred during allocation of array buffer. "
                "Creating empty array."
            );
            outp_array = Array<T>();
            if(p_alloc_error != nullptr)
            {
                LogDebugLine("Alloc error is not null so calling it.");
                p_alloc_error(p_alloc_error_data);
            }

            LogDebugLine("Returning after unsuccessful allocation");
            return;
        }

        LogDebugLine(
            "Allocation successfully completed setting size to 0 and capacity to"
            " the given value. The allocated buffer is " << (void*)outp_array.m_Buffer
        );
        outp_array.m_Size = 0;
        outp_array.m_Capacity = p_capacity;

    }
    /**
     * @brief Default allocator, callback and data.
     * 
     * @details If you don't know about defaults see [//TODO:REPLACE ME WITH LINK]
     * 
     */
    template<typename T>
    inline void CreateArrayAtOfCapacity(
        Array<T>& outp_array,
        const Size& p_capacity
    )
    {
        LogDebugLine("Using defaults for CreateArrayAtOfCapacityUsingAllocator");
        CreateArrayAtOfCapacityUsingAllocator(
            outp_array, p_capacity, 
            Library::g_DEFAULT_ALLOCATOR,
            Library::g_DEFAULT_ALLOC_ERROR, Library::g_DEFAULT_ALLOC_ERROR_DATA
        );
    }

    //TODO: Re-documentation mark, continue bellow.
    /**
     * @brief Create a copy of p_array at outp_buffer.
     * 
     * @details Allocates a new buffer at outp_buffer.m_Buffer that is
     * sizeof(T) * p_array.m_Size bytes long. outp_buffer.m_Size and
     * outp_buffer.m_Capacity are set to p_array.m_Size. After that is done all
     * of the items from p_array are copied into outp_buffer in the same order
     * starting from the begining.
     * 
     * If allocation fails an empty array is created at outp_buffer,
     * p_alloc_error is called and the function returns.
     * 
     * If p_array.m_Buffer is null or p_array.m_Size is 0 an empty array is
     * created at outp_buffer and the function returns.
     * 
     * @time O(n), n being the number of items in the given array.
     * 
     * @param outp_buffer Where the new array will be created.
     * @param p_array The array to copy.
     * @param p_allocate The allocator to use for the new array.
     * @param p_alloc_error The callback to call when allocation fails.
     * @param p_alloc_error_data The data that will be passed to p_alloc_error.
     * 
     */
    template<typename T>
    void CreateCopyAtOfArrayUsingAllocator(
        Array<T>& outp_buffer,
        const Array<T>& p_array,
        Allocator p_allocate, Callback p_alloc_error, void* p_alloc_error_data
    )
    {

        LogDebugLine("Creating copy of array from " << p_array << " and to "
        << outp_buffer);

        if(ArrayIsEmpty(p_array))
        {
            LogDebugLine("p_array is empty, creating empty array and returning");
            outp_buffer = Array<T>();
            return;
        }

        //In this case the sizeof(T) * n cannot overflow since in a valid array
        //a buffer of that size has allready been successfully allocated, as
        //such the same buffer must also be allocatable once again.
        outp_buffer.m_Buffer = (T*)p_allocate(sizeof(T) * p_array.m_Size);
        if(outp_buffer.m_Buffer == nullptr)
        {
            LogDebugLine(
                "Allocation of array buffer was unsuccessful. Creating empty array."
            );
            outp_buffer = Array<T>();
            if(p_alloc_error != nullptr)
            {
                LogDebugLine("Alloc error is not null so calling it.");
                p_alloc_error(p_alloc_error_data);
            }

            LogDebugLine("Returned after unsuccessful allocation");
            return;
        }
        
        
        LogDebugLine(
            "Allocation is has been successful. The allocated buffer is " <<
            (void*)outp_buffer.m_Buffer << ". Copying the capacity and size now."
        );
        
        outp_buffer.m_Capacity = p_array.m_Size;
        outp_buffer.m_Size = p_array.m_Size;

        for(Size i = 0; i < p_array.m_Size; ++i)
        {
            LogDebugLine("Copying item at index " << i);
            outp_buffer.m_Buffer[i] = p_array.m_Buffer[i];
        }

        LogDebugLine("Copying of array has been completed, returning");

    }
    /**
     * @brief Default allocator, callback and data.
     * 
     * @details If you don't know about defaults see [//TODO:REPLACE ME WITH LINK]
     * 
     */
    template<typename T>
    inline void CreateCopyAtOfArray(
        Array<T>& outp_buffer,
        const Array<T>& p_array
    )
    {
        LogDebugLine("Using defaults for CreateCopyAtArrayUsingAllocator.");
        CreateCopyAtOfArrayUsingAllocator(
            outp_buffer, p_array,
            Library::g_DEFAULT_ALLOCATOR,
            Library::g_DEFAULT_ALLOC_ERROR, Library::g_DEFAULT_ALLOC_ERROR_DATA
        );
        LogDebugLine("Returning from inline default for CreateCopyAtOfArrayUsingAllocator");
    }


    /**
     * @brief Returns the index were the first occurrence of the first item and
     * all following items in p_toFind can be found in p_array.
     * 
     * @details Loops through the entire array starting from index zero and
     * ending at the p_array.m_Size. When the first item from p_toFind is located
     * the function checks if the following items are the same as in p_toFind.
     * If they are the same then the index of were the first item was found is
     * returned.
     * 
     * Generally in every error case p_array.m_Size is returned. Such errors are:
     * - Either p_toFind or p_array have a null buffer or a size of 0;
     * - p_toFind cannot be found in p_array;
     * - p_toFind.m_Size > p_array.m_Size;
     * - There is a special case where the index could overflow (see source for
     * more info).
     * 
     * 
     * @time O(n * m), n being the number of items in p_array and m being the
     * number of items in p_toFind.
     * 
     * @param p_toFind The array that will be searched for.
     * @param p_array The array that will be searched in.
     * @return The first occurrence of p_toFind in p_array, the index is where
     * the first item of p_toFind can be found. In any other case p_array.m_Size
     * is returned.
     * 
     */
    template<typename T>
    Size FindIndexOfFirstOccurrenceOfArrayInArray(const Array<T>& p_toFind, const Array<T>& p_array)
    {

        LogDebugLine("Finding the first occurrence of array " << p_toFind 
        << " in array " << p_array);

        if(ArrayIsEmpty(p_toFind))
        {
            LogDebugLine("The array being searched for is empty, returning the size.");
            return p_array.m_Size;
        }
        if(ArrayIsEmpty(p_array))
        {
            LogDebugLine("The array being searched in is empty, returning the size.");
            return p_array.m_Size;
        }
        if(p_toFind.m_Size > p_array.m_Size)
        {
            LogDebugLine("The array that is being searched for has a bigger"
            " size than the array that is being searched in.");
            return p_array.m_Size;
        }

        //Optimized loop for this special case.
        if(p_toFind.m_Size == p_array.m_Size)
        {
            LogDebugLine("The array that is being searched for has a equal"
            " size to the array that is being searched in, using optimized loop.");
            for(Size i = 0; i < p_array.m_Size; ++i)
            {
                if(p_array[i] != p_toFind[i])
                {
                    LogDebugLine("A missmatch was found on index " << i);
                    return p_array.m_Size;
                }
            }

            LogDebugLine("No missmatches found returning 0.");
            return 0;
        }

        for(Size i = 0, n = 0; i < p_array.m_Size; ++i)
        {
            if(p_array[i] == p_toFind[n])
            {
                LogDebugLine("Found match of item at index " << n << " in array"
                " being searched for with index at index " << i << " in array "
                "being searched in.");
                ++n;
                if(n >= p_toFind.m_Size)
                {
                    LogDebugLine("Reached end of array being searched for, "
                    "returning index " << i - (n - 1));
                    return i - (n - 1);
                }
            }
            else
            {
                n = 0;
            }
        }

        LogDebugLine("Did not find the array, returning the size.");
        return p_array.m_Size;

    }
    /**
     * @brief Returns the index were the last occurrence of the first item and
     * all following items in p_toFind can be found in p_array.
     * 
     * @details Loops through the entire array starting from p_array.m_Size - 1
     * and ending at 0. When the first item from p_toFind is located
     * the function checks if the following items are the same as in p_toFind.
     * If they are the same then the index of were the first item was found is
     * returned.
     * 
     * Generally in every error case p_array.m_Size is returned. Such errors are:
     * - Either p_toFind or p_array have a null buffer or a size of 0;
     * - p_toFind cannot be found in p_array;
     * - p_toFind.m_Size > p_array.m_Size;
     * - There is a special case where the index could overflow (see source for
     * more info).
     * 
     * 
     * @time O(n * m), n being the number of items in p_array and m being the
     * number of items in p_toFind.
     * 
     * @param p_toFind The array that will be searched for.
     * @param p_array The array that will be searched in.
     * @return The last occurrence of p_toFind in p_array, the index is where
     * the first item of p_toFind can be found. In any other case p_array.m_Size
     * is returned.
     * 
     */
    template<typename T>
    Size FindIndexOfLastOccurrenceOfArrayInArray(const Array<T>& p_toFind, const Array<T>& p_array)
    {

        LogDebugLine("Finding the last occurrence of array " << p_toFind 
        << " in array " << p_array);

        if(ArrayIsEmpty(p_toFind))
        {
            LogDebugLine("The array being searched for is empty, returning the size.");
            return p_array.m_Size;
        }
        if(ArrayIsEmpty(p_array))
        {
            LogDebugLine("The array being searched in is empty, returning the size.");
            return p_array.m_Size;
        }
        if(p_toFind.m_Size > p_array.m_Size)
        {
            LogDebugLine("The array that is being searched for has a bigger"
            " size than the array that is being searched in.");
            return p_array.m_Size;
        }

        //Optimized loop for this special case.
        if(p_toFind.m_Size == p_array.m_Size)
        {
            LogDebugLine("The array that is being searched for has a equal"
            " size to the array that is being searched in, using optimized loop.");
            for(Size i = 0; i < p_array.m_Size; ++i)
            {
                if(p_array[i] != p_toFind[i])
                {
                    LogDebugLine("A missmatch was found on index " << i);
                    return p_array.m_Size;
                }
            }

            LogDebugLine("No missmatches found returning 0.");
            return 0;
        }

        for(Size i = p_array.m_Size, n = p_toFind.m_Size - 1; i-- > 0;)
        {
            if(p_array[i] == p_toFind[n])
            {
                LogDebugLine("Found match of item at index " << n << " in array"
                " being searched for with index at index " << i << " in array "
                "being searched in.");
                if(n-- == 0)
                {
                    LogDebugLine("Reached end of array being searched for, "
                    "returning index " << i);
                    return i;
                }
            }
            else
            {
                n = p_toFind.m_Size - 1;
            }
        }

        LogDebugLine("Did not find the array, returning the size.");
        return p_array.m_Size;

    }

    /**
     * @brief Finds the number of instances of p_toFind in p_array.
     * 
     * @details Loops from index 0 to p_array.m_Size and each time the first
     * item of p_toFind is found the function checks if all of the following
     * items are the same as in p_toFind. If that is true then the result is
     * incremented. This continues until the end of p_array is reached.
     * 
     * If either p_array or p_toFind have an empty buffer or a size of 0, 0 is
     * returned.\n
     * If p_toFind.m_Size > p_array.m_Size, 0 is returned.
     * 
     * @time O(n), n being the number of items in the given array.
     * 
     * @param p_toFind The array that will be searched for.
     * @param p_array The array that will be searched in.
     * @return The number of instances of p_toFind in p_array.
     */
    template<typename T>
    Size FindNumberOfInstanceOfArrayInArray(const Array<T>& p_toFind, const Array<T>& p_array)
    {

        LogDebugLine("Finding the number of occurrences of array " << p_toFind 
        << " in array " << p_array);

        if(ArrayIsEmpty(p_toFind))
        {
            LogDebugLine("The array being searched for is empty, returning the size.");
            return 0;
        }
        if(ArrayIsEmpty(p_array))
        {
            LogDebugLine("The array being searched in is empty, returning the size.");
            return 0;
        }
        if(p_toFind.m_Size > p_array.m_Size)
        {
            LogDebugLine("The array that is being searched for has a bigger"
            " size than the array that is being searched in.");
            return 0;
        }

        //Optimized loop for this special case.
        if(p_toFind.m_Size == p_array.m_Size)
        {
            LogDebugLine("The array that is being searched for has a equal"
            " size to the array that is being searched in, using optimized loop.");
            for(Size i = 0; i < p_array.m_Size; ++i)
            {
                if(p_array[i] != p_toFind[i])
                {
                    LogDebugLine("A missmatch was found on index " << i);
                    return 0;
                }
            }

            LogDebugLine("No missmatches found returning 1.");
            return 1;
        }

        Size l_returnValue = 0;

        for(Size i = 0, n = 0; i < p_array.m_Size; ++i)
        {
            if(p_array[i] == p_toFind[n])
            {
                LogDebugLine("Found match of item at index " << n << " in array"
                " being searched for with index at index " << i << " in array "
                "being searched in.");
                ++n;
                if(n >= p_toFind.m_Size)
                {
                    LogDebugLine("Found instance of array being searched for");
                    ++l_returnValue;
                    n = 0;
                }
            }
            else
            {
                n = 0;
            }
        }

        LogDebugLine("Returning the return value.");
        return l_returnValue;

    }

    /**
     * @brief Checks if p_array is empty
     * 
     * @details Checks if p_array.m_Buffer is null and if p_array.m_Size is null,
     * if any of these are true, then true is returned, false otherwise.
     * 
     * @param p_array Is this array empty?
     * @return True if either the array has a null buffer or a size of 0.
     */
    template<typename T>
    bool ArrayIsEmpty(const Array<T>& p_array)
    {
        LogDebugLine("Checking if array " << p_array << " is empty.");
        return p_array.m_Buffer == nullptr || p_array.m_Size == 0;
    }

    /**
     * @brief Checks if p_array has p_toFind.
     * 
     * @details Loops through p_array and checks if any item matches the first
     * item of p_toFind, if this is true and all following items are the same as
     * in p_toFind, true is returned, otherwise the loop continues until the end
     * of p_array is reached at which point if no match was found false is 
     * returned.\n
     * If p_array or p_toFind are empty or have a size of 0, false is returned.\n
     * If p_toFind.m_Size > p_array.m_Size, false is returned.
     * 
     * @time O(n * m), n being the number of items in p_array and m being the
     * number of items in p_toFind.
     * 
     * @param p_array The array that will be searched in. 
     * @param p_toFind The array that will be searched for.
     * 
     * @return True if p_item can be found in p_array, false otherwise.
     * 
     */
    template<typename T>
    bool ArrayContainsArray (const Array<T>& p_array, const Array<T>& p_toFind)
    {
        LogDebugLine("Checking if array " << p_array << " contains the array " << p_toFind);
        //Again code reuse!!1!11!!!!1!
        return FindIndexOfFirstOccurrenceOfArrayInArray(p_toFind, p_array) < p_array.m_Size;
    }

    /**
     * @brief Checks if p_array starts with p_start.
     * 
     * @details Loops through index 0 to p_start.m_Size and checks if on each
     * index the two array's items match. If any missmatch is found false is 
     * returned. If the loop is completed successfully true is returned.\n
     * False is also returned if either p_array ot p_start have a null buffer or
     * size of zero.\n
     * If p_start.m_Size > p_array.m_Size false is returned.
     * 
     * @time O(n), n being the number of items in p_start.
     * 
     * @param p_array The array to check in.
     * @param p_start The array to check for.
     * @return True if p_array starts with p_start, false if either of them are
     * empty or p_array does not start with p_start.
     * 
     */
    template<typename T>
    bool ArrayStartsWithArray(const Array<T>& p_array, const Array<T>& p_start)
    {

        LogDebugLine("Checking if array " << p_array << " starts with " <<
        p_start);

        if(ArrayIsEmpty(p_array))
        {
            LogDebugLine("p_array is empty, returning false");
            return false;
        }
        if(ArrayIsEmpty(p_start))
        {
            LogDebugLine("p_start is empty, returning false");
            return false;
        }

        if(p_start.m_Size > p_array.m_Size)
        {
            LogDebugLine("p_start.m_Size is bigger than p_array.m_Size,"
            " returning false");
            return false;
        }

        LogDebugLine("Starting main loop for check.");

        //There is a gurante that p_start.m_Size =< p_array.m_Size
        for(Size i = 0; i < p_start.m_Size; ++i)
        {
            if(p_array[i] != p_start[i])
            {
                LogDebugLine("Missmatch found on index " << i << " returning false");
                return false;
            }
        }

        LogDebugLine("No missmatches found, returning true");
        return true;

    }
    /**
     * @brief Checks if p_array ends with p_end.
     * 
     * @details Loops through index p_end.m_Size to 0 and checks if on each
     * index the two array's items match. If any missmatch is found false is 
     * returned. If the loop is completed successfully true is returned.\n
     * False is also returned if either p_array ot p_start have a null buffer or
     * size of zero.\n
     * If p_end.m_Size > p_array.m_Size false is returned.
     * 
     * @time O(n), n being the number of items in p_end.
     * 
     * @param p_array The array to check in.
     * @param p_end The array to check for.
     * @return True if p_array ends with p_end, false if either of them are
     * empty or p_array does not end with p_end.
     * 
     */
    template<typename T>
    bool ArrayEndsWithArray(const Array<T>& p_array, const Array<T>& p_end)
    {

        LogDebugLine("Checking if array " << p_array << " ends with " <<
        p_end);

        if(ArrayIsEmpty(p_array))
        {
            LogDebugLine("p_array is empty, returning false");
            return false;
        }
        if(ArrayIsEmpty(p_end))
        {
            LogDebugLine("p_end is empty, returning false");
            return false;
        }

        if(p_end.m_Size > p_array.m_Size)
        {
            LogDebugLine("p_end.m_Size is bigger than p_array.m_Size, "
            "returning false");
            return false;
        }

        LogDebugLine("Starting main loop for check.");

        //There is a gurante that p_start.m_Size =< p_array.m_Size
        for
        (
            Size i = p_array.m_Size - 1, n = p_end.m_Size;
            n-- > 0;
            --i
        )
        {
            if(p_array[i] != p_end[n])
            {
                LogDebugLine("Missmatch found on index " << i << " returning false");
                return false;
            }
        }

        LogDebugLine("No missmatches found, returning true");
        return true;

    }


    /**
     * @brief Reverses p_array.
     * 
     * @details If the given array is empty the function returns.
     * 
     * @time O(n / 2), n being the nubmer of items in the array.
     * 
     * @param p_array The array to reverse.
     * 
     * 
     */
    template<typename T>
    void ReverseArray(Array<T>& p_array)
    {

        LogDebugLine("Reversing array " << p_array);

        if(ArrayIsEmpty(p_array))
        {
            LogDebugLine("p_array is empty, returning.");
            return;
        }

        Size l_to = p_array.m_Size / 2;
        LogDebugLine("The middle of the array is index " << l_to);

        LogDebugLine("Begining to loop now.");
        T l_temp;
        //Have two indexes start from the begining of the array and the end of
        //the array. Loop initil you reach the middle.
        for(Size i = 0, n = p_array.m_Size; n-- > l_to; ++i)
        {
            l_temp = p_array[i];
            p_array[i] = p_array[n];
            p_array[n] = l_temp;
        }

        LogDebugLine("Loop finished, returning");

    }

    /**
     * @brief Changes the array's capacity by reallocating its buffer.
     * 
     * @details Reallocates p_array's buffer to be the size of p_new_capacity.
     * After reallocation is successful p_array.m_Capacity is set to p_new_capacity.
     * If p_new_capacity > p_array.m_Size, p_array.m_Size is set to p_new_capacity.
     * 
     * If p_new_capacity is 0 the array is destroyed (m_Buffer = nullptr, m_Size
     * and m_Capacity = 0).
     * 
     * If p_new_capacity == p_array.m_Capacity the function does nothing and
     * returned, p_array is not mutated.
     * 
     * If reallocation fails p_realloc_error is called and the function returns. 
     * The array is not mutated.
     * 
     * If sizeof(T) * p_new_capacity overflows, the function returns without
     * mutating the array or calling p_reallocate. 
     *
     * @param p_array The array who's capacity will be changed. 
     * @param p_new_capacity The new capacity.
     * @param p_reallocate The reallocator that will be used.
     * @param p_realloc_error The callback for a reallocation error.
     * @param p_realloc_error_data The data that will be passed to p_realloc_error.
     * 
     */
    template<typename T>
    void ResizeArrayToCapacityUsingReallocator(
        Array<T>& p_array,
        const Size& p_new_capacity,
        Reallocator p_reallocate,
        Callback p_realloc_error, void* p_realloc_error_data
    )
    {

        LogDebugLine("Changing the capacity of array " << p_array << " to "
        << p_new_capacity);

        if(p_new_capacity == p_array.m_Capacity)
        {
            LogDebugLine("p_new_capacity is the same as p_array.m_Capacity");
            return;
        }

        if(p_new_capacity == 0)
        {
            LogDebugLine("The new capcity is 0, destroying array and returning");
            p_reallocate(p_array.m_Buffer, 0);

            p_array.m_Buffer = nullptr;
            p_array.m_Size = 0;
            p_array.m_Capacity = 0;
            
            return;
        }

        LogDebugLine("Reallocating the buffer.");
        //Checks for overflows occurring during sizeof(T) * p_new_capacity.
        if(p_new_capacity > SIZE_MAX / sizeof(T))
        {
            LogDebugLine("Detected that sizeof(T) = " << sizeof(T) << " * "
            "p_new_capacity = " << p_new_capacity << " would overflow! Returning."
            );
            return;
        }
        T* l_newBuffer = (T*)p_reallocate(p_array.m_Buffer, sizeof(T) * p_new_capacity);
        if(l_newBuffer == nullptr)
        {
            LogDebugLine("Reallocation failed.");
            if(p_realloc_error != nullptr)
            {
                LogDebugLine("Realloc error is not null so calling it.");
                p_realloc_error(p_realloc_error_data);
            }
            LogDebugLine("Returning now.");

            return;
        }
       
        LogDebugLine("Reallocation was successful, new buffer is " << 
        (void*)l_newBuffer << ", configuring the array aproproately");

        p_array.m_Buffer = l_newBuffer;
        p_array.m_Capacity = p_new_capacity;
        if(p_array.m_Size > p_array.m_Capacity)
        {
            LogDebugLine("The array's size is greater than the arrays capacity, "
            "setting the arrays size to its capacity.");
            p_array.m_Size = p_array.m_Capacity;
        }

        LogDebugLine("Capacity change has been successfully completed");

    }
    template<typename T>
    inline void ResizeArrayToCapacity(
        Array<T>& p_array,
        const Size& p_new_capacity
    )
    {
        LogDebugLine("Using defaults for ResizeArrayToCapacityUsingReallocator");
        ResizeArrayToCapacityUsingReallocator(
            p_array, p_new_capacity,
            Library::g_DEFAULT_REALLOCATOR,
            Library::g_DEFAULT_REALLOC_ERROR,
            Library::g_DEFAULT_REALLOC_ERROR_DATA
        );
    }

    /**
     * @brief Increases p_array's capacity by p_amount.
     * 
     * @details Reallocates p_array.m_Buffer using p_reallocate so that the
     * capacity of the buffer is p_array.m_Capacity + p_amount. If
     * p_array.m_Capacity + p_amount overflows the function returns without
     * mutating p_array.
     * 
     * If the array is empty then a new buffer is allocated for it.
     * 
     * If reallocation fails, p_realloc_error is called and the function returns.
     * p_array is not mutated. 
     * 
     * If p_amount is 0 the function returns.
     * 
     * @param p_array The array who's capacity will be increased. 
     * @param p_amount By how much the capacity will be increased.
     * @param p_reallocate The reallocator that will be used to reallocated the buffer.
     * @param p_realloc_error The callback that will be called on failed reallocation.
     * @param p_realloc_error_data The data that will be passed to p_realloc_error.
     * 
     */
    template<typename T>
    void IncreaseArrayCapacityByAmountUsingReallocator(
        Array<T>& p_array,
        const Size& p_amount,
        Reallocator p_reallocate,
        Callback p_realloc_error, void* p_realloc_error_data
    )
    {

        LogDebugLine("Increasing the capacity of array " << p_array << 
        " by " << p_amount);

        Size l_result = p_array.m_Capacity + p_amount;
        LogDebugLine("The new capacity has been calculated it is " << l_result);

        //This indicates an overflow
        if(l_result < p_array.m_Capacity)
        {
            LogDebugLine("An overflow has been detected, returning");
            return;
        }

        ResizeArrayToCapacityUsingReallocator(
            p_array,
            l_result,
            p_reallocate, p_realloc_error, p_realloc_error_data
        );

    }
    template<typename T>
    inline void IncreaseArrayCapacityByAmount(
        Array<T>& p_array,
        const Size& p_amount
    )
    {
        LogDebugLine("Using defaults for IncreaseArrayCapacityByAmountUsingReallocator");
        IncreaseArrayCapacityByAmountUsingReallocator(
            p_array, p_amount,
            Library::g_DEFAULT_REALLOCATOR,
            Library::g_DEFAULT_REALLOC_ERROR,
            Library::g_DEFAULT_REALLOC_ERROR_DATA
        );
    }
    
    /**
     * @brief Decreases p_array's capacity by p_amount.
     * 
     * @details Reallocates p_array.m_Buffer using p_reallocate so that the
     * capacity of the buffer is p_array.m_Capacity - p_amount. If
     * p_array.m_Capacity - p_amount overflows the function returns without
     * mutating p_array. If the new capacity is smaller than p_array.m_Size then
     * p_array.m_Size is set to p_array.m_Capacity.
     *  
     * If reallocation fails, p_realloc_error is called and the function returns.
     * p_array is not mutated. 
     * 
     * If p_amount is 0 the function returns.
     *
     * If p_array.m_Capacity - p_amount == 0, p_array.m_Buffer is reallocated
     * with a size of 0 and it is set to null, p_array.m_Size and
     * p_array.m_Capacity are set to 0.
     *  
     * @param p_array The array who's capacity will be increased. 
     * @param p_amount By how much the capacity will be increased.
     * @param p_reallocate The reallocator that will be used to reallocated the buffer.
     * @param p_realloc_error The callback that will be called on failed reallocation.
     * @param p_realloc_error_data The data that will be passed to p_realloc_error.
     * 
     */
    template<typename T>
    void DecreaseArrayCapacityByAmountUsingReallocator(
        Array<T>& p_array,
        const Size& p_amount,
        Reallocator p_reallocate,
        Callback p_realloc_error, void* p_realloc_error_data
    )
    {

        LogDebugLine("Decreaseing the capacity of array " << p_array 
        << " by " << p_amount);

        Size l_result = p_array.m_Capacity - p_amount;
        LogDebugLine("The needed capacity has been calculated, it is " << l_result);

        //This indicates an overflow
        if(l_result > p_array.m_Capacity)
        {
            LogDebugLine("An overflow has been detected, returning");
            return;
        }

        ResizeArrayToCapacityUsingReallocator(
            p_array, l_result,
            p_reallocate, p_realloc_error, p_realloc_error_data
        );

    }
    template<typename T>
    inline void DecreaseArrayCapacityByAmount(
        Array<T>& p_array,
        const Size& p_amount
    )
    {
        LogDebugLine("Using defaults for DecreaseArrayCapacityByAmountUsingReallocator");
        DecreaseArrayCapacityByAmountUsingReallocator(
            p_array, p_amount,
            Library::g_DEFAULT_REALLOCATOR,
            Library::g_DEFAULT_REALLOC_ERROR,
            Library::g_DEFAULT_REALLOC_ERROR_DATA
        );
    }

    /**
     * @brief Shifts all of the items right in p_array, starting at p_index, by
     * p_shift_amount of spaces.
     * 
     * @details Shifting starts at the end of the array, the last item is
     * copied down to index (p_array.m_Size - 1) + p_shift_amount, then the item
     * before it is copied down to index (p_array.m_Size - 2) + p_shift_amount,
     * then the item before that... and so on until p_index is reached and
     * shifted. All of the items are kept in the same order and non are lost.
     * 
     * @tparam T Must be a valid type. Must be able to be copied using the =
     * operator to other parts of the array. Old items will be overwritten using
     * the = operator.
     * @param p_array The array to shift items in.
     * @param p_shift_amount By how much to shift those items.
     * @param p_index The index where shifting will begin.
     *  
     * @warning This function makes a number of **assumptions** about its input:
     * - p_array.m_Buffer != nullptr.
     * - p_index < p_array.m_Size.
     * - p_array.m_Capacity > (p_array.m_Size - 1) + p_shift_amount
     * If any of these assumptions are false, the behavior of this function is
     * undefined (When the macro DEBUG is defined, this function tests its
     * paramaters for these assumptions and if any of them are false, it prints
     * which one using LogDebugLine and calls abort()).
     * 
     * **If p_shift_amount is 0** then all of the things that this function does
     * will be redundant and p_array will not be mutated in any noticeable way.
     * In other words you'll be wasting CPU cycles. (When the macro DEBUG is
     * defined, this function will check this case and print if it happens.)
     * 
     * **This function is used to** make space in p_array while still keeping
     * all of the items stay in the array and stay in the proper order. To be
     * exact, items in the index range p_index to p_index + (p_shift_amount - 1)
     * inclusive, contain redundant items. That means that you can freely
     * overwrite the items in that index range since there is already a copy of
     * them further down the array.
     * 
     * @time O(n), n being p_array.m_Size - p_index.
     * 
     */
    template<typename T>
    void ShiftItemsRightInArrayByAmountStartingFromIndexNoErrorCheckAssumptions(
        Array<T>& p_array,
        const Size& p_shift_amount,
        const Size& p_index
    )
    {

        LogDebugLine("Shifting items right in array " << p_array << " by "
        << p_array << " starting at index " << p_index);

        #ifdef DEBUG
        if(p_shift_amount == 0)
        {
            LogDebugLine("\nShifting by 0, this is inefficent and a waste of "
            "CPU cycles, consider fixing it.\n");
        }
        if(p_array.m_Buffer == nullptr)
        {
            LogDebugLine("\n\n\n--- ERROR ---\n\n\n");
            LogDebugLine("In function ShiftItemsRightInArrayByAmountStartingFromIndexNoErrorCheckAssumptions"
            " the assumption that p_array.m_Buffer != nullptr is false! This is"
            " undefined behaviour, aborting...");
            LogDebugLine("Note: This is only checked because DEBUG is defined, "
            "normally this is not checked and the behaviour of the function is "
            "undefined.");
            abort();
        }
        if(p_index >= p_array.m_Size)
        {
            LogDebugLine("\n\n\n--- ERROR ---\n\n\n");
            LogDebugLine("In function ShiftItemsRightInArrayByAmountStartingFromIndexNoErrorCheckAssumptions"
            " the assumption that p_index >= p_array.m_Size is false! This is"
            " undefined behaviour, aborting...");
            LogDebugLine("Note: This is only checked because DEBUG is defined, "
            "normally this is not checked and the behaviour of the function is "
            "undefined.");
            abort();
        }
        if(p_array.m_Capacity > (p_array.m_Size - 1) + p_shift_amount)
        {
            LogDebugLine("\n\n\n--- ERROR ---\n\n\n");
            LogDebugLine("In function ShiftItemsRightInArrayByAmountStartingFromIndexNoErrorCheckAssumptions"
            " the assumption that p_array.m_Capacity > (p_array.m_Size - 1) + "
            "p_shift_amount is false! This is undefined behaviour, aborting...");
            LogDebugLine("Note: This is only checked because DEBUG is defined, "
            "normally this is not checked and the behaviour of the function is "
            "undefined.");
            abort();
        }
        #endif //DEBUG

        //Note: None of the arithmetic here can overflow as long as all of the
        //assumptions made by this function are true. (Details given in comment
        //block after the loop.)
        for
        (
            Size i = p_array.m_Size - 1,              //Starts at the last item in the array.
            n = (p_array.m_Size - 1) + p_shift_amount;  //Get extra space after the array.
            i >= p_index;                               //Keep on looping until the item at the index is shifted. 
            --i, --n                                    //Shifting is done backwards, this is so that no temporaries are
                                                        //used, instead already shifted items are overwritten by not yet
                                                        //shifted items.
        )
        {
            p_array[n] = p_array[i];
        }

        /***!!!--- OVERFLOW INFO ---!!!***/
        //TL;DR: The assumptions made by the function do not allow any overflows
        //to occur.
        //
        //1. Why 'p_array.m_Size - 1' cannot overflow:
        //  - The only case where overflow occurs is when p_array.m_Size is 0.
        //  - One of the assumptions made by this function is that p_index <
        //p_array.m_Size.
        //  - Let's assume that p_array.m_Size is 0, what value would p_index
        //have so that the assumption would be true?
        //  - There is none, p_array.m_Size will MUST be > 0, as long as the
        // p_index < p_array.m_Size assumption is true.
        //  - This means that the required condition of p_array.m_Size == 0 can
        //never be met, as such no overflow will ever occur.
        //
        //2. Why '(p_array.m_Size - 1) + p_shift_amount cannot overflow:
        //  - See point 1 for the p_array.m_Size - 1 part.
        //  - One of the assumptions made by this function is that
        //p_array.m_Capacity > (p_array.m_Size - 1) + p_shift_amount.
        //  - If this assumption is true then, p_array.m_Capacity must have a
        //value that can be put into a Size (which is the type of
        //p_array.m_Size and p_shift_amount).
        //  - That means that a number exists which is:
        //      - Equal to or greater than the sum of 'p_array.m_Size - 1' and
        //p_shift_amount
        //      - This number can fit into a Size.
        //  - That means that no matter what the result of the addition is, it
        //can be put into a Size, as such no overflow will occur.
        //3. //TODO: for --i
        //4. //TODO: for --n
        /***!!!--- END OVERFLOW INFO ---!!!***/

    }

    /**
     * @brief Adds p_to_add after the item at p_index in p_array.
     * 
     * @details First all of the items in p_array that are after p_index are
     * shifted to the right by p_to_add.m_Size. After the shift, after p_index
     * there are p_to_add.m_Size empty items, these are overwritten by the items
     * in p_to_add. And finally p_array.m_Size is increased by p_to_add.m_Size.
     * 
     * If p_to_add is empty the function returns without mutating p_array.
     * 
     * @time O(n + m), n being the number of items in p_to_add and m being the
     * number of items after p_index in p_array.
     * 
     * @param p_to_add The array from which items are going to be added from.
     * @param p_array The array in which items are going to be added in.
     * @param p_index The index after which the items will be added.
     * 
     * @warning This function **ASSUMES** that the following conditions are true:
     * -# p_array.m_Buffer != nullptr;
     * -# p_index < p_array.m_Size;
     * -# p_index + p_to_add.m_Size <= p_array.m_Capacity.
     * If any of these assumptions are false, the behaviour of this function is
     * undefined.
     * 
     * For a function that does not make such 
     * assumptions see @ref AddArrayToArrayAfterIndexUsingReallocator.
     * 
     */
    template<typename T>
    void AddArrayToArrayAfterIndexNoErrorCheckAssumingEnoughCapacity(
        const Array<T>& p_to_add,
        Array<T>& p_array,
        const Size& p_index
    )
    {

        LogDebugLine("Adding array " << p_to_add << " to array " << p_array 
        << " after index " << p_index);

        if(ArrayIsEmpty(p_to_add))
        {
            LogDebugLine("p_to_add is empty, returning.");
            return;
        }

        //Note: thanks to all of the assumptions that this function makes, it is
        //guranteed to not cause any overflows.

        //TODO: Why +-1 and why no overflows.
        ShiftItemsRightInArrayByAmountStartingFromIndexNoErrorCheckAssumptions(
            p_array,
            p_to_add.m_Size - 1,
            p_index + 1
        );
        LogDebugLine("Item shifting done.");

        LogDebugLine("Doing the actual addition.");
        for
        (
            Size i = p_index + 1, //Start adding stuff right after the index.
            n = 0; //For indexing the array being added from.
            n < p_to_add.m_Size; //Until all items are added.
            ++i, ++n
        )
        {
            p_array[i] = p_to_add[n];
        }
        //TODO: Overflow why not.
        LogDebugLine("Addition compelted.");

        LogDebugLine("Updating p_array.m_Size and returning.");
        p_array.m_Size += p_to_add.m_Size;

    }

    /**
     * @brief Adds p_to_add to p_array after p_index. This function dose not
     * assume its input data is correct.
     * 
     * @details Internally this function just makes sure that all of the 
     * assumptions made by @ref AddArrayToArrayAfterIndexNoErrorCheckAssumingEnoughCapacity
     * are corrent. It does this by first making sure that p_index less than 
     * p_array.m_Size and making sure that p_array.m_Size + p_to_add.m_Size are
     * less than p_array.m_Capacity.
     * 
     * If p_index is greater than or equaled to p_array.m_Size, p_index_error is
     * called and the function returns.
     * 
     * If p_array.m_Size + p_to_add.m_Size is greater than p_array.m_Capacity the
     * function tries to reallocate a bigger buffer. This is done first by
     * calculating the size of the new buffer, which is (p_to_add.m_Size * 2 +
     * p_array.m_Capacity) * sizeof(T). Here the size of p_to_add is doubled to
     * avoid further reallocations. If any part of this overflows the function
     * tries to reallocate a smaller buffer of size (p_to_add.m_Size + 
     * p_array.m_Capacity) * sizeof(T). Here p_to_add.m_Size is not doubled so
     * that an overflow does not occur. If an overflow still does occur in any
     * part the function gives up and returns.
     * 
     * If reallocation fails then the function first tryies to allocate a smaller
     * buffer. If that reallocation also fails p_realloc_error is called and the
     * function returns.
     * 
     * If p_array.m_Buffer == nullptr, a new buffer is allocated for p_array with
     * a capacity of p_to_add.m_Size and all of the items from p_to_add are
     * copied to p_array, p_array.m_Size is set to p_to_add.m_Size. If
     * reallocation fails during this, p_array is not mutated and p_realloc_error
     * is called and the function returns. The same happens if 
     * p_array.m_Size == 0, but no reallocation occurs except in the case where
     * p_array.m_Capacity < p_to_add.m_Size, in this case the same happens for a
     * reallocation error. 
     * Note that in these cases p_index is not checked and as such any index is
     * valid. However if p_to_add is also empty, the function returns without
     * doing anything.
     * 
     * @time O(n + m), n being the number of items in p_to_add and m being the
     * number of items after p_index in p_array.
     * 
     * @param p_to_add The array to add.
     * @param p_array The array to which the addition will be done.
     * @param p_index The index after which the addition will be done.
     * @param p_index_error A callback for when p_index is incorrect.
     * @param p_index_error_data Data that will be passed to p_index_error.
     * @param p_reallocate A reallocator that will be used to modify the buffer
     * of p_array.
     * @param p_realloc_error A callback for when p_reallocate fails.
     * @param p_realloc_error_data Data that will be passed to p_realloc_error.
     * 
     */
    template<typename T>
    void AddArrayToArrayAfterIndexUsingReallocator(
        const Array<T>& p_to_add,
        Array<T>& p_array,
        const Size& p_index,
        Callback p_index_error, void* p_index_error_data,
        Reallocator p_reallocate,
        Callback p_realloc_error, void* p_realloc_error_data
    )
    {

        LogDebugLine("Adding array " << p_to_add << " to array " << p_array
        << " after index " << p_index << " without making any assumptions");

        //TODO: The way this function handles reallocation is very ad hoc and
        //could benifit from a reduction of lines of code if it were to be
        //refractored.

        if(ArrayIsEmpty(p_array))
        {
            LogDebugLine("p_array is empty, coping items directly.");
            
            if(ArrayIsEmpty(p_to_add))
            {
                LogDebugLine("p_to_add is also empty returning.");
                return;
            }

            if(p_array.m_Capacity < p_to_add.m_Size)
            {
                LogDebugLine("p_array does not have enough capacity, reallocating");

                Size l_newCapacity = p_array.m_Capacity + p_to_add.m_Size;
                if(l_newCapacity < p_array.m_Capacity)
                {
                    LogDebugLine("Error l_newCapacity overflows, returning");
                    return;
                }

                if(l_newCapacity > SIZE_MAX / sizeof(T))
                {
                    LogDebugLine("Error, l_newCapacity * sizeof(T) overflows, returning");
                    return;
                }

                T* l_newBuffer = (T*)p_reallocate(p_array.m_Buffer, sizeof(T) * l_newCapacity);

                if(l_newBuffer == nullptr)
                {
                    LogDebugLine("Reallocation failed.");
                    if(p_realloc_error != nullptr)
                    {
                        LogDebugLine("Realloc error is not null so calling it.");
                        p_realloc_error(p_realloc_error_data);
                    }
                    LogDebugLine("Returning from unsuccessful reallocation");
                    return;
                }

                LogDebugLine("Reallocation successfully completed, new "
                "buffer is " << l_newBuffer << ", updating p_array's fields");

                p_array.m_Buffer = l_newBuffer;
                p_array.m_Capacity = l_newCapacity;
            }

            LogDebugLine("Begining to copy items");
            for(Size i = 0; i < p_to_add.m_Size; ++i)
            {
                p_array[i] = p_to_add[i];
            }
            p_array.m_Size = p_to_add.m_Size;

            LogDebugLine("All items copied, returning.");
            return;
        }

        if(p_index >= p_array.m_Size)
        {
            LogDebugLine("Index error detected! The index is " << p_index
            << " and p_array is " << p_array);
            if(p_index_error != nullptr)
            {
                LogDebugLine("Index error is not null so calling it.");
                p_index_error(p_index_error_data);
            }

            LogDebugLine("Returning because of index error");
            return;
        }

        Size l_newSize = p_array.m_Size + p_to_add.m_Size;
        if(l_newSize < p_array.m_Size)
        {
            LogDebugLine("Error, the new size of p_array overflows, returning");
            return;
        }

        if(l_newSize > p_array.m_Capacity)
        {
            LogDebugLine("There is not enough capacity in p_array, trying "
            "to allocate more.");

            //This can only be described as overflow gore, beware! Also gotos
            //are used and i am sure you have some REALLY strong and long words
            //to say about that. 

            Size l_extraCapacity;
            Size l_newCapacity;
            T* l_newBuffer;

            LogDebugLine("Checking if p_to_add.m_Size * 2 overflows.");
            if(2 > SIZE_MAX / p_to_add.m_Size)
            {
                LogDebugLine("Yes it overflows, trying to allocate less now.");
                goto allocateLess;
            }
            
            l_extraCapacity = p_to_add.m_Size * 2;


            l_newCapacity = p_array.m_Capacity + l_extraCapacity;
            
            LogDebugLine("Checking if p_array.m_Capacity + l_extraCapacity "
            "overflows.");
            if(l_newCapacity <= p_array.m_Capacity)
            {
                LogDebugLine("Yes it overflows, trying to allocate less");
                goto allocateLess;
            }


            LogDebugLine("And finally checking if sizeof(T) * l_newCapacity"
            " overflows.");
            if(l_newCapacity > SIZE_MAX / sizeof(T))
            {
                LogDebugLine("Yes it overflows, trying to allocate less.");
                goto allocateLess;
            }


            LogDebugLine("No overflows detected, doing reallocation.");


            l_newBuffer = 
                (T*)p_reallocate(p_array.m_Buffer, sizeof(T) * l_newCapacity);
            
            if(l_newBuffer == nullptr)
            {
                LogDebugLine("Reallocation failed, trying to reallocate less.");
                allocateLess:

                //Only get the minimum required capacity.
                l_newCapacity = p_array.m_Capacity + p_to_add.m_Size;
                
                LogDebugLine("Checking if l_newCapacity overflows with the"
                " smaller values.");
                if(l_newCapacity <= p_array.m_Capacity)
                {
                    LogDebugLine("Yes it overflows, giving up and returning.");
                    return;
                }


                LogDebugLine("Checking if l_newCapacity * sizeof(T)"
                " overflows with the smaller values.");
                if(l_newCapacity > SIZE_MAX / sizeof(T))
                {
                    LogDebugLine("Yes it overflows, giving up and returning.");
                    return;
                }


                LogDebugLine("No overflows detected with the smaller values,"
                " doing reallocation.");

                l_newBuffer = 
                    (T*)p_reallocate(p_array.m_Buffer, sizeof(T) * l_newCapacity);

                if(l_newBuffer == nullptr)
                {
                    LogDebugLine("Reallocation failed.");
                    if(p_realloc_error != nullptr)
                    {
                        LogDebugLine("Realloc error is not null, calling it");
                        p_realloc_error(p_realloc_error_data);
                    }
                    LogDebugLine("Returning from unsuccessful reallocation.");
                    return;
                }

                LogDebugLine("Reallocation was successful, new buffer is "
                << l_newBuffer << " and new capacity is " << sizeof(T) * l_newCapacity);

                p_array.m_Buffer = l_newBuffer;
                p_array.m_Capacity = sizeof(T) * l_newCapacity;

            }
            else
            {
                LogDebugLine("Reallocation was successful, new buffer is "
                << ((void*)l_newBuffer) << " and new capacity is " << sizeof(T) * l_newCapacity);
                p_array.m_Buffer = l_newBuffer;
                p_array.m_Capacity = sizeof(T) * l_newCapacity;
            }

        }

        LogDebugLine("All assumptions that actual addition function does can"
        " now be safely assumed.");
        //It is now safe to make these assumptions.
        AddArrayToArrayAfterIndexNoErrorCheckAssumingEnoughCapacity(
            p_to_add,
            p_array,
            p_index
        );

    }
    template<typename T>
    inline void AddArrayToArrayAfterIndex(
        const Array<T>& p_to_add,
        Array<T>& p_array,
        const Size& p_index,
        Callback p_index_error, void* p_index_error_data
    )
    {
        LogDebugLine("Using defaults for AddArrayToArrayAfterIndexUsingReallocator");
        AddArrayToArrayAfterIndexUsingReallocator(
            p_to_add,
            p_array,
            p_index, p_index_error, p_index_error_data,
            Library::g_DEFAULT_REALLOCATOR,
            Library::g_DEFAULT_REALLOC_ERROR,
            Library::g_DEFAULT_REALLOC_ERROR_DATA
        );
    }

    /**
     * @brief Removes p_numberOfItems number of items after p_index in p_array.
     * 
     * @details Overwrites all of the items starting, from index p_index and
     * ending at index p_index + p_numberOfItems, with items after p_index +
     * p_numberOfItems. After this is done p_array.m_Size is subtracted by
     * p_numberOfItems + 1.
     * 
     * @time O(n), n being p_numberOfItems + 1.
     * 
     * @param p_numberOfItems The number of items to remove after p_index.
     * @param p_index The index of the first item to remove.
     * @param p_array The array in which the items will be removed.
     * 
     * @warning This function makes a bunch of assumptions. If these assumptions
     * are not met the behaviour of the function is undefined.\n
     * Those are:
     * -# p_index < p_array.m_Size;
     * -# p_index + p_numberOfItems < p_array.m_Size;
     * -# p_array.m_Buffer != nullptr.
     * 
     * For a function that does not make such assumptions see
     * @ref RemoveNumberOfItemsStartingFromAndIncludingIndexFromArray. 
     * 
     */
    template<typename T>
    void RemoveNumberOfItemsStartingFromAndIncludingIndexNoErrorCheckFromArray(
        const Size& p_numberOfItems,
        const Size& p_index,
        Array<T>& p_array
    )
    {

        LogDebugLine("Removing items from array " << p_array << " starting"
        " at and including index " << p_index << " and " << p_numberOfItems <<
        " after it.");

        //Shifts all of the items after the index to the left by p_numberOfItems
        //+ 1. Really this is all this function does it could also just be called
        //shift items to the left and it would still have the effect of removing
        //the items, the only difference is that fact that p_array.m_Size is
        //updated.
        //
        //Regarding overflows the function assumes that p_index + p_numberOfItems
        //< p_array.m_Size, in order for this condition to be met the value of
        //p_array.m_Size has to be able to fit into a Size. The values of i
        //and n never exceed p_array.m_Size and never go bellow 0, therefore i 
        //and n cannot overflow.
        for
        (
            Size i = p_index + p_numberOfItems + 1,/*The first item after the
                                                        remove location.*/
            n = p_index;//The first item that is being removed
            i < p_array.m_Size; //Loops until all items are the remove location
                                //are shifted.
            ++i, ++n
        )
        {
            //Overwrite the item that is being removed with the item after the
            //remove location.
            p_array[n] = p_array[i];
        }

        //+1 since the item at the index is also removed.
        //
        //And again this cannot overflow as long as the assumption of this
        //function is met, that being p_index + p_numberOfItems < p_array.m_Size.
        p_array.m_Size -= p_numberOfItems + 1;

    }

    /**
     * @brief Removes the item at p_index and p_numberOfItems after it in p_array.
     * 
     * @details Internally its just a wrapper for 
     * @ref RemoveNumberOfItemsStartingFromAndIncludingIndexNoErrorCheckFromArray
     * that makes sure that all of the assumptions it makes are true. It dose
     * this by checking the index and array itself.
     * 
     * If p_index >= p_array.m_Size, p_index_error is called and the function
     * returns.
     * 
     * If p_index + p_numberOfItems >= p_array.m_Size, p_index_error is called
     * and the function returns. Note in case p_index + p_numberOfItems overflows,
     * the function returns without calling any callback.
     * 
     * @time O(n), n being p_numberOfItems + 1.
     * 
     * @param p_numberOfItems The number of items to remove after p_index.
     * @param p_index The index of the item to remove.
     * @param p_index_error A callback in case the index is incorrect.
     * @param p_index_error_data Data that will be passed to index error.
     * @param p_array The array in which items will be removed from.
     *
     * @warning This function DOES NOT change p_array.m_Capacity, it does not
     * make it bigger or smaller, in other words you need to manually decrease
     * the capacity of p_array in order to save on memory.
     *   
     */
    template<typename T>
    void RemoveNumberOfItemsStartingFromAndIncludingIndexFromArray(
        const Size& p_numberOfItems,
        const Size& p_index,
        Callback p_index_error, void* p_index_error_data,
        Array<T>& p_array
    )
    {

        LogDebugLine("Doing removeale of items from array " << p_array <<
        ", staring from index " << p_index << " and going " << p_numberOfItems
        << " items forward.");

        //In any valid array p_array.m_Size would be 0 if p_array.m_Buffer is
        //null so this also covers that case.
        if(p_index >= p_array.m_Size)
        {
            LogDebugLine("p_index >= p_array.m_Size.");
            if(p_index_error != nullptr)
            {
                LogDebugLine("Index error is not null so calling it.");
                p_index_error(p_index_error_data);
            }

            LogDebugLine("Returning from index error");
            return;
        }

        Size l_endIndex = p_index + p_numberOfItems;
        if(l_endIndex < p_index)
        {
            LogDebugLine("The end index overflows, returning");
            return;
        }

        if(l_endIndex >= p_array.m_Size)
        {
            LogDebugLine("The ending index >= p_array.m_Size.");

            if(p_index_error != nullptr)
            {
                LogDebugLine("Index error is not null so calling it.");
                p_index_error(p_index_error_data);
            }

            LogDebugLine("Returning from index error.");
            return;
        }

        //It is now safe to make these assumptions.
        RemoveNumberOfItemsStartingFromAndIncludingIndexNoErrorCheckFromArray(
            p_numberOfItems,
            p_index,
            p_array
        );

    }
    
    /**
     * @brief Removes all instances of the items in p_items from p_array.
     * 
     * @details Items are removed by pushing the **matching items (items whose
     * == operator returns true when compared with any of the items in p_items
     * OR whose != operator return false when compared with any of the items in
     * p_items)** to the end of p_array. Once all of the matching items have
     * been pushed to the end of p_array's buffer, p_array's size is shrunk down
     * by the amount of matching items.\n **Non matching items (items whose ==
     * operator returns false when compared with any of the items in p_items OR
     * whose != operator return true when compared with any of the items in
     * p_items)** are swapped with the nearest matching items, with a preference
     * to swap the items closest to the end of p_array (for example an array
     * with the matching items M1,M2,M3 and the non matching items NM1, NM2,
     * NM3, NM4, NM5, NM6, where the items are arrange in the following order:
     * NM1-M1-NM2-NM3-M2-NM4-NM5-M3-NM6, will produce an array with the follow
     * order once all of the swapping is done: NM1-NM2-NM3-NM4-NM5-NM6-M2-M3-M1).
     * 
     * @tparam T Must be complete type that can be copied with the = operator as
     * well as compared to itself with the == and != operators.
     * @param p_items An array of items to remove from p_array.
     * @param p_array The array from which items will be removed.
     * 
     * **p_array.m_Buffer and p_array.m_Capacity** are not mutated in any way.
     * 
     * **p_items** is not mutated in any way.
     * 
     * **If p_array.m_Size is 0** the function returns without doing anything.
     * 
     * **If p_items.m_Size is 0** the function loops p_array.m_Size times and
     * returns without changing anything.
     * 
     * **Items in p_array are swapped with each other** using a temporary
     * variable of type T. Items are copied from p_array into this temporary
     * using = operator and then they are copied form the temporary to p_array
     * once again using the = operator.
     * 
     * **In the case where p_items has repeated items**, the behaviour of this
     * function depends on whether DEBUG is defined:
     * - *If DEBUG is defined* then p_items is checked for repeating items and
     * if they are found the index of all of the repeated items is logged. The
     * function will still run normally, but it will be wasting item checking
     * redundant items.
     * - *If DEBUG is not defined* then this function only wastes time checking
     * redundant items, no error will occur and the function will execute
     * properly.
     * 
     * @time **O(n * m)**, n being the number of items in p_array and m being
     * the number of items in p_items. **HOWEVER if DEBUG is defined** the time
     * complexity of this function changes to **O(m^2)** since the function also
     * checks to see if there are any repeating items.
     * 
     */
    template<typename T>
    void RemoveEachInstanceOfArrayOfItemsFromArray(
        const Array<T>& p_items,
        Array<T>& p_array
    )
    {

        LogDebugLine("Removing each instance of items in array " << p_items
        << " from array " << p_array);

        //This algorithm works by "pushing" all of the matching items in p_array
        //by constantly swapping them with non matching items. The entire
        //algorithm only loops through the entire array once.
        //
        //"Pushing" of the matching items is done in the following way:
        //There are 2 indexes, 1 is the matching item with the lowest index and
        //the other is the index of the current item. Once a non matching item
        //is found, the matching item with the lowest index is swapped with it
        //and the lowest item index is incremented. The new index is either the
        //location of a new matching item or the same matching item that was
        //just swapped.
        //Once a matching item is found, it is ignored.
        //
        //This is turn causes a matching item blob to slowly form in the array.
        //By the time the algorightm is done all matching items are now at the
        //end of the array right next to each other and all other non matching
        //items have been arranged in their proper space. Then all that is left
        //is to decrease the array's size.

        #ifdef DEBUG
        LogDebugLine("Checking if there are any repeated items in the item "
        "array. (This check only occurs when DEBUG is defined, it also doesn't "
        "do anything other than log the indexes of the repeated items.)");
        for(Size i = 0; i < p_items.m_Size; ++i)
        {
            //The item will never be mutated anyway.
            Array<T> l_tmp((int&)p_items[i]);
            if(FindNumberOfInstanceOfArrayInArray<T>(l_tmp, p_items) > 1)
            {
                LogDebugLine("Repeated item found at index " << i);
            }
        }
        #endif //DEBUG

        if(p_array.m_Size == 0)
        {
            LogDebugLine("The array having items removed does not contain any "
            "items itself, bummer! Returning.");
            return;
        }
        //Case of p_items.m_Size being 0 is covered by the all of the loops and
        //checks them selfs. In this case the first case will make it so that
        //l_firstMatch is equal to p_array.m_Size(since no match will be found
        //due to the ArrayContainsArray function returning false all of the time
        //), this inturn causes the second loop to be skipped and the last
        //assignment of p_array.m_Size will have no effect as l_firstMatch is
        //equal to p_array.m_Size.

        //l_firstMatch is the smallest index that has a matching item.
        Size l_firstMatch;

        LogDebugLine("Searching for first item match.");
        //The first loop finds the first item that matches p_items
        for(l_firstMatch = 0; l_firstMatch < p_array.m_Size; ++l_firstMatch)
        {
            if(ArrayContainsArray<T>(p_items, p_array[l_firstMatch]))
            {
                LogDebugLine("Found first item match at index " << l_firstMatch);
                break;
            }
        }

        //This condition is here mainly because it would cause an overflow in
        //the loop below.
        if(l_firstMatch == SIZE_MAX)
        {
            LogDebugLine("Special case of the only matching index being "
            "SIZE_MAX, decrementing array " << p_array
            << "'s m_Size by 1 and returning.");
            //p_array.m_Size is guranteed to be SIZE_MAX in the case so it won't
            //underflow.
            --p_array.m_Size;
            return;
        }

        LogDebugLine("Pushing all matches to the end of the array.");
        T l_tmp;
        for(Size i = l_firstMatch + 1; i < p_array.m_Size; ++i)
        {
            if(ArrayContainsArray<T>(p_items, p_array[i]))
            {
                LogDebugLine("Found match at index " << i  << ", not swaping "
                "and skipping.");
                continue;
            }
            else
            {
                LogDebugLine("Did not find match at index " << i << ", swaping "
                "and incrementing the first item index.");
                l_tmp = p_array[i];
                p_array[i] = p_array[l_firstMatch];
                p_array[l_firstMatch] = l_tmp;

                ++l_firstMatch;
            }
        }

        LogDebugLine("All matches have been pushed to the end, adjusting array "
        "size...");
        //l_firstMatch is the smallest index that has a matching item, which in
        //this case is the exact value that needs to be in p_array.m_Size.
        p_array.m_Size = l_firstMatch;

    }


    /**
     * @brief Destoys the given array with the given deallocator.
     * 
     * @details @ref p_array has its buffer passed to @ref p_deallocate. Then
     * p_arrays' m_Buffer is set to null, m_Size is set to 0 and m_Capacity is
     * set to 0.
     *  
     * @param p_array The array to destroy.
     * @param p_deallocate The deallocator to use.
     */
    template<typename T>
    void DestroyArrayUsingDeallocator(Array<T>& p_array, Deallocator p_deallocate)
    {

        LogDebugLine("Destroying array at " << p_array);

        p_deallocate(p_array.m_Buffer);

        p_array.m_Buffer = nullptr;
        p_array.m_Capacity = 0;
        p_array.m_Size = 0;

    }
    template<typename T>
    inline void DestoryArray(Array<T>& p_array)
    {
        LogDebugLine("Using defaults for DestroyArrayAtUsingDeallocator");
        DestroyArrayUsingDeallocator(p_array, Library::g_DEFAULT_DEALLOCATOR);
    }



    #ifdef DEBUG
    /**
     * @brief Logs the given arrays fields to the given log. Individual items
     * are not logged.
     * 
     * @details The format is "<THE ARRAY REFERENCE'S MEMORY LOCATION> { 
     * m_Buffer = <p_array.m_Buffer as void*>, m_Size = <p_array.m_Size>,
     * m_Capacity = <p_array.m_Capacity> }"
     *  
     */
    template<typename T>
    const Debugging::Log& operator<< (const Debugging::Log& p_log, const Array<T>& p_array)
    {

        p_log << &p_array;
        p_log << " { m_Buffer = " << (void*)p_array.m_Buffer;
        p_log << ", m_Size = " << p_array.m_Size;
        p_log << ", m_Capacity = " << p_array.m_Capacity;
        p_log << " }";

        return p_log;

    }
    #endif //DEBUG

}

#endif //ARRAY__DATA_STRUCTURES_ARRAY_ARRAY_HPP