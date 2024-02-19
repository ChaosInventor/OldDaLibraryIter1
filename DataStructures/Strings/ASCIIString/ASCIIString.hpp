/** @file ASCIIString.hpp
 * 
 * @brief This file contains the declarations for ASCIIString and it's associated
 * functions.
 * 
 * @details This file also declares << and >> operators for ASCIIString only if
 * the IO.hpp header guard is detected.
 * 
 */

#ifndef ASCII_STRING__DATA_STRUCTURES_STRINGS_ASCII_STRING_ASCII_STRING_HPP
#define ASCII_STRING__DATA_STRUCTURES_STRINGS_ASCII_STRING_ASCII_STRING_HPP

#include "../../../Meta/Meta.hpp"
#include "../../Array/Array.hpp"
#include "../../../Debugging/Logging/Log.hpp"

/**
 * @brief Contains ASCIIString and all related functions and operators used for
 * it.
 * 
 * @details 
 * @section ASCIIString_overviewNamespace Overview
 * Note that this namespace only contains functions that are specific
 * to ASCIIString and c strings. Since ASCIIString is just a wrapper for 
 * Array<char> this namespace does not contain any functions for manipulating
 * with the string's buffer, there is not need to make wrappers around the Array
 * functions. As such it is recommended that you also take a look at and use the
 * namespace @ref Library::DataStructures::Array in conjunction with this 
 * namespace.
 * 
 * @section ASCIIString_withCString Relation with c strings
 * This project can easily be used with c strings. When a string is mentioned
 * it refers to a buffer of characters ending in the null character 0x0,
 * basically the string litterals defined with double quotes(ex: "Hello, world!").
 * 
 * An ASCIIString can be created from a c string but the null character that
 * marks the end of the string is not copied or used, it is instead ignored.
 * This also applies to the few functions that work with c strings.
 * 
 * @section ASCIIString_namespace_whatis What this namespace actually defines
 * The functions in this namespace are primarily used for changing characters
 * be it making letters lower or upper case, converting ASCIIString from and to
 * numbers and some basic creation and destruction functions.
 * 
 * There are also a few functions that work with c strings.
 * 
 */
namespace Library::DataStructures::Strings
{

    #ifdef DEBUG
    struct ASCIIString;
    const Debugging::Log& operator<<(const Debugging::Log& p_log, const ASCIIString& p_string);    
    #endif // DEBUG



    /**
     * @brief This structure is meant to be used to store a string of ASCII
     * characters that can be mutated by either changing the characters them
     * selfs or changing the buffer that the characters are in.
     * 
     * @details
     * @section ASCIIString_overviewStruct Overview
     * Internally this structure is an Array where T is char. This
     * allows for ASCIIString to be implicitly converted to an Array reference.
     * 
     * For this reason an ASCIIString should be treated as a normal Array, but a
     * normal Array should NOT be treated as an ASCIIString.
     * 
     * @section ASCIIString_reasoning Rational
     * This structure is defined so that the type system can further be used to
     * express what the data in an Array is spoused to mean. Using an ASCIIString
     * means that the data stored in an Array is human readable text that is
     * encoded in ASCII. This also for the IO operators for this structure to
     * directly read and write characters from and to a stream, assuming that
     * the stream is an ASCII encoded text file.
     * 
     */
    struct ASCIIString
    {

        /**
         * @brief The underlying array that is used to store data.
         * 
         */
        Array::Array<char> m_Array;

        /**
         * @brief Construct an empty string.
         * 
         */
        ASCIIString():
        m_Array() 
        { }
        /**
         * @brief Copies p_other.m_Array to this->m_Array.
         * 
         */
        ASCIIString(const ASCIIString& p_other):
        m_Array(p_other.m_Array) 
        { }
        /**
         * @brief Copies p_other.m_Array to this->m_Array and make p_other.m_Array
         * empty.
         * 
         */
        ASCIIString(ASCIIString&& p_other):
        m_Array((Array::Array<char>&&)p_other.m_Array) 
        { }

        /**
         * @brief Copies p_array to m_Array.
         * 
         */
        ASCIIString(const Array::Array<char>& p_array):
        m_Array(p_array) 
        { }
        /**
         * @brief Makes a copy from p_c_string using the default allocator.
         * 
         * @details Copies all of the characters in the same order from p_c_string
         * excluding the null character at the end to a newly allocated array that
         * is stored in m_Array. The new array is allocated using the default
         * allocator.
         * 
         * If p_c_string is null or is only a null character. An emtpy array is
         * created at m_Array.
         * 
         * If allocation failure occurs then the default callback is called and
         * an empty array is created at m_Array.
         * 
         * @param p_c_string The string to copy from.
         * 
         * @warning This function allocates dynamic memory, make sure to free it.
         * 
         */
        explicit ASCIIString(const char* const p_c_string);

        /**
         * @brief Same as copy constructor.
         * 
         * @return *this.
         *  
         */
        ASCIIString& operator= (const ASCIIString& p_other)
        {
            m_Array = p_other.m_Array;
            return *this;
        }
        /**
         * @brief Same as move constructor.
         * 
         * @return *this.
         *  
         */
        ASCIIString& operator= (ASCIIString&& p_other)
        {
            m_Array = (Array::Array<char>&&)p_other.m_Array;
            return *this;
        }

        /**
         * @brief Returns m_Array.
         *  
         */
        operator Array::Array<char>&()
        {
            return m_Array;
        }
        /**
         * @brief Returns m_Array.m_Buffer.
         *  
         */
        operator char*()
        {
            return m_Array.m_Buffer;
        }

        /**
         * @brief Returns m_Array as const.
         *  
         */
        operator const Array::Array<char>&() const
        {
            return m_Array;
        }
        /**
         * @brief Returns m_Array.m_Buffer as const.
         *  
         */
        operator const char*() const
        {
            return m_Array.m_Buffer;
        }

        /**
         * @brief Returns the character at p_index.
         * 
         * @warning This operator **ASSUMES** the following:
         * -# p_index < m_Array.m_Size;
         * -# m_Array.m_Buffer != nullptr.
         * 
         * If these assumptions are false the behaviour is undefined.
         * 
         */
        char& operator[](const Size& p_index)
        {
            return m_Array[p_index];
        }

        /**
         * @brief Compares m_Array and p_other.m_Array see 
         * @ref Array::Array::operator== for details.
         * 
         */
        bool operator== (const ASCIIString& p_other) const
        {
            return m_Array == p_other.m_Array;
        }
        /**
         * @brief Compares the characters in m_Array with the characters in p_c_string.
         * 
         * @details Compares each charater from m_Array and p_c_string starting
         * from the begining. If any missmatch is found false is returned. The
         * null charater at the end of p_c_string is not compared.
         * 
         * If either p_c_string or m_Array.m_Buffer is null, the function returns
         * true if both are null, false otherwise.
         * 
         * After comparison if the end of both strings was not reached, false is
         * returned.
         * 
         * If p_c_string is nothing but a single null character then true is
         * only returned if m_Array.m_Buffer != nullptr && m_Array.m_Size == 0.
         * 
         * @time O(n), n being the minumum of the number of charaters in m_Array
         * and p_c_string.
         * 
         * @param p_c_string The c string to compare with. 
         * 
         * @returns True if p_c_string and p_array have the same characters in the
         * same order and have the same number of chararters. The null character
         * in p_c_string is not compared. False in every other case.
         * 
         */
        bool operator== (const char* const p_c_string) const;

        /**
         * @brief Compares m_Array and p_other.m_Array see 
         * @ref Array::Array::operator!= for details.
         * 
         */
        bool operator!= (const ASCIIString& p_other) const
        {
            return m_Array != p_other.m_Array;
        }
        /**
         * @brief Returns !(*this == p_c_string). See
         * @ref ASCIIString::operator== for details.
         *
         */
        bool operator!= (const char* const p_c_string) const
        {
            return !(*this == p_c_string);
        }

    };


    extern const ASCIIString g_WHITE_SPACES;
    extern const unsigned int g_MAX_BASE;


    ASCIIString& operator>> (const ASCIIString&, ASCIIString&);
    ASCIIString& operator<< (ASCIIString& , const ASCIIString&);


    ASCIIString& operator>> (const char&, ASCIIString&);
    ASCIIString& operator>> (const unsigned char&, ASCIIString&);
    ASCIIString& operator<< (ASCIIString& , const char&);
    ASCIIString& operator<< (ASCIIString& , const unsigned char&);


    ASCIIString& operator>> (const short&, ASCIIString&);
    ASCIIString& operator>> (const unsigned short&, ASCIIString&);
    ASCIIString& operator<< (ASCIIString& , const short&);
    ASCIIString& operator<< (ASCIIString& , const unsigned short&);


    ASCIIString& operator>> (const int&, ASCIIString&);
    ASCIIString& operator>> (const unsigned int&, ASCIIString&);
    ASCIIString& operator<< (ASCIIString& , const int&);
    ASCIIString& operator<< (ASCIIString& , const unsigned int&);

    ASCIIString& operator>> (const long&, ASCIIString&);
    ASCIIString& operator>> (const unsigned long&, ASCIIString&);
    ASCIIString& operator<< (ASCIIString& , const long&);
    ASCIIString& operator<< (ASCIIString& , const unsigned long&);

    ASCIIString& operator>> (const long long&, ASCIIString&);
    ASCIIString& operator>> (const unsigned long long&, ASCIIString&);
    ASCIIString& operator<< (ASCIIString& , const long long&);
    ASCIIString& operator<< (ASCIIString& , const unsigned long long&);


    ASCIIString& operator>> (const float&, ASCIIString&);
    ASCIIString& operator<< (ASCIIString& , const float&);

    ASCIIString& operator>> (const double&, ASCIIString&);
    ASCIIString& operator<< (ASCIIString& , const double&);

    ASCIIString& operator>> (const long double&, ASCIIString&);
    ASCIIString& operator<< (ASCIIString& , const long double&);


    ASCIIString& operator>> (const bool&, ASCIIString&);
    ASCIIString& operator<< (ASCIIString& , const bool&);

    ASCIIString& operator>> (const void* const&, ASCIIString&);
    ASCIIString& operator<< (ASCIIString& , const void* const&);

    ASCIIString& operator>> (const char* const&, ASCIIString&);
    ASCIIString& operator<< (ASCIIString& , const char* const&);



    /**
     * @brief Warpper for Array::CreateArrayAtOfCapacityUsingAllocator
     * 
     */
    inline void CreateASCIIStringAtOfCapacityUsingAllocator(
        ASCIIString& outp_buffer,
        const Size p_capacity,
        Allocator p_allocate,
        Callback p_alloc_error, void* p_alloc_error_data
    )
    {
        Array::CreateArrayAtOfCapacityUsingAllocator<char>(outp_buffer, p_capacity, p_allocate, p_alloc_error, p_alloc_error_data);
    }
    /**
     * @brief Defaults function for @ref CreateASCIIStringAtOfCapacityUsingAllocator
     * 
     * @details For more details on defaults functions see @ref LibraryDefaultsFunctions
     * 
     */
    inline void CreateASCIIStringAtOfCapacity(
        ASCIIString& outp_buffer,
        const Size p_capacity
    )
    {
        LogDebugLine("Using defaults for CreateASCIIStringAtOfCapacityUsingAllocator.");
        CreateASCIIStringAtOfCapacityUsingAllocator(
            outp_buffer,
            p_capacity,
            Library::g_DEFAULT_ALLOCATOR,
            Library::g_DEFAULT_ALLOC_ERROR,
            Library::g_DEFAULT_ALLOC_ERROR_DATA
        );
    }

    //TODO: Document bellow
    inline void CreateCopyAtOfASCIIStringUsingAllocator(
        ASCIIString outp_buffer,
        const ASCIIString& p_string,
        Allocator p_allocate,
        Callback p_alloc_error, void* p_alloc_error_data
    )
    {
        Array::CreateCopyAtOfArrayUsingAllocator<char>(
            outp_buffer.m_Array,
            p_string.m_Array,
            p_allocate,
            p_alloc_error, p_alloc_error_data
        );
    }
    inline void CreateCopyAtOfASCIIString(
        ASCIIString outp_buffer,
        const ASCIIString& p_string
    )
    {
        Array::CreateCopyAtOfArrayUsingAllocator<char>(
            outp_buffer.m_Array,
            p_string.m_Array,
            Library::g_DEFAULT_ALLOCATOR,
            Library::g_DEFAULT_ALLOC_ERROR,
            Library::g_DEFAULT_ALLOC_ERROR_DATA
        );
    }

    /**
     * @brief Creates a copy of p_c_string to outp_buffer by using p_allocate.
     * 
     * @details A new buffer is allocated using p_allocate that is the size of
     * sizeof(T) * FindSizeOfCString(p_c_string). After this is done all of the
     * charaters are copied from p_c_string into the new buffer.
     * outp_buffer.m_Array.m_Buffer is set to the newly allocated buffer, while
     * outp_buffer.m_Array.m_Size and outp_buffer.m_Array.m_Capacity are set to
     * FindSizeOfCString(p_c_string). Note that the null charater at the end of
     * p_c_string is not copied.
     * 
     * If p_c_string is null or is a single null charater an empty string is
     * created at outp_buffer and the function returns.
     * 
     * If allocation fails an empty string is created at outp_buffer,
     * p_alloc_error is called and the function returns.
     * 
     * @time O(n), n being the nubmer of charaters in p_c_string.
     * 
     * @param outp_buffer Where the copy of p_c_string will be made
     * @param p_c_string The c string to copy.
     * @param p_allocate The allocator to use for the copying.
     * @param p_alloc_error A callback for when allocation fails.
     * @param p_alloc_error_data Data that will be passed to p_alloc_error if it
     * is called.
     * 
     */
    void CreateASCIIStringAtFromCopyOfCStringUsingAllocator(
        ASCIIString& outp_buffer,
        const char* const p_c_string,
        Allocator p_allocate,
        Callback p_alloc_error, void* p_alloc_error_data
    );
    inline void CreateASCIIStringAtFromCopyOfCString(
        ASCIIString& outp_buffer,
        const char* const p_c_string
    )
    {
        LogDebugLine("Using defaults for CreateASCIIStringAtFromCopyOfCStringUsingAllocator");
        CreateASCIIStringAtFromCopyOfCStringUsingAllocator(
            outp_buffer,
            p_c_string,
            Library::g_DEFAULT_ALLOCATOR,
            Library::g_DEFAULT_ALLOC_ERROR,
            Library::g_DEFAULT_ALLOC_ERROR_DATA
        );
        LogDebugLine("Returning from defaults function for CreateASCIIStringAtFromCopyOfCStringUsingAllocator");
    }

    //TODO: Document above

    /**
     * @brief Counts the number of characters in p_c_string.
     * 
     * @details The null character is not counted.
     * 
     * @param p_c_string **Assumed** to be a pointer to a c string that ends in
     * a null character.
     * @return The number of characters in p_c_string excluding the null character. 
     * 
     * @warning If p_c_string is null the behaviour of this function is
     * undefined.
     * 
     */
    Size FindSizeOfCString(const char* p_c_string);

    /**
     * @brief Checks if p_char is is an uppercase letter.
     * 
     * @details An uppercase letter is considered to be a character in the
     * range 0x41 to 0x5A inclusive.
     * 
     * @param p_char The character to check.
     * 
     * @return True if p_char is an uppercase letter, false otherwise.
     * 
     */
    inline bool ASCIICharacterIsUppercaseLetter(const char& p_char)
    {
        LogDebugLine("Checking if character at " << (void*)&p_char 
        << " is an uppercase letter.");
        return p_char >= 'A' && p_char <= 'Z';
    }
    /**
     * @brief Checks if p_char is is a lowercase letter.
     * 
     * @details A lowercase letter is considered to be a character in the
     * range 0x61 to 0x7A inclusive.
     * 
     * @param p_char The character to check.
     * 
     * @return True if p_char is a lowercase letter, false otherwise.
     * 
     */
    inline bool ASCIICharacterIsLowercaseLetter(const char& p_char)
    {
       LogDebugLine("Checking if character at " << (void*)&p_char 
       << " is an lowercase letter.");
       return p_char >= 'a' && p_char <= 'z';
    }
    /**
     * @brief Checks if p_char is a letter.
     * 
     * @details A letter is considered to be a character in the range
     * 0x41 to 0x5a inclusive OR in range 0x61 to 0x7a inclusive.
     * f
     * @param p_char The character to check.
     * @return True if p_char is a letter, false otherwise.
     * 
     */
    inline bool ASCIICharacterIsLetter(const char& p_char)
    {
        return ASCIICharacterIsLowercaseLetter(p_char) || ASCIICharacterIsUppercaseLetter(p_char);
    }

    /**
     * @brief Checks if p_char is a pritable character.
     * 
     * @details A printable character is considered to be a character in the
     * range 0x20 to 07F exclusive. (space is not considered pritable).
     * 
     * @param p_char The character to check.
     * @return True if p_char is a printable character, false otherwise.
     * 
     */
    inline bool ASCIICharacterIsPrintable(const char& p_char)
    {
        LogDebugLine("Checking if character at " << (void*)&p_char 
        << " is printable.");
        return p_char > 0x20 && p_char < 0x7F;
    }

    //TODO: Document bellow

    /**
     * @brief Removes all of the whitespaces from p_string and then deallocates
     * it to save on capacity.
     * 
     * @details This function works by moving all of the whitespaces in p_string
     * to the end of it's buffer. After this is done the size of the string is
     * decreased by the number of whitespaces in p_string. The capacity remains
     * unchanged.
     * 
     * If p_string is empty the function returns without doing anything.
     * 
     * If p_string does not have any whitespaces the function returns without
     * mutating it.
     * 
     * If p_string is nothing but whitespaces m_Size is set to 0.
     * 
     * @time O(n), n being the number of characters in p_string.
     * 
     * @param p_string The string in which all of the characters should be removed.
     * @param p_reallocate The reallocator that will be used for the removal.
     * @param p_realloc_error A callback for when reallocation fails.
     * @param p_realloc_error_data Data that will be passed to p_realloc_error
     * if it is called.
     * 
     * @warning This function does NOT reallocate p_string's buffer, as such if
     * you would like to save memory in p_string you have to reallocate it your
     * self. The function 
     * @ref ASCIIString::DecreaseArrayCapacityByAmountUsingReallocator is
     * recommended for this purpose.
     * 
     */
    inline void RemoveAllWhitespacesFromASCIIString(ASCIIString& p_string)
    {
        Array::RemoveEachInstanceOfArrayOfItemsFromArray<char>(
            g_WHITE_SPACES,
            p_string
        );
    }

    /**
     * @brief Removes all of the whitespaces at the end of p_string.
     * 
     * @details Starts looping at the end of p_string and counts all of the
     * whitespaces it finds there. The loop ends once a non whitespace character
     * is encountered. p_string.m_Array.m_Size is reduced by the number of
     * counted whitespaces.
     * 
     * If p_string.m_Array.m_Buffer == nullptr or p_string.m_Array.m_Size == 0
     * the function returns without doing anything.
     * 
     * @time O(n), n being the number of trailing whitespaces.
     * 
     * @param p_string The string where the trailing whitespaces will be removed
     * form
     * 
     * @warning This function does NOT reallocate p_string's buffer, as such if
     * you would like to save memory in p_string you have to reallocate it your
     * self. The function 
     * @ref ASCIIString::DecreaseArrayCapacityByAmountUsingReallocator is
     * recommended for this purpose.
     * 
     */
    void RemoveTrailingWhitespacesFromASCIIString(ASCIIString& p_string);

    //TODO: Document above

    /**
     * @brief Makes outp_char an uppercase version of it's self.
     * 
     * @details @warning If outp_char is not between a-z, the behaviour of this
     * function is undefined.
     * 
     * @param outp_char The character to make uppercased. **ASSUMED** to be a
     * letter ranging from 0x61 to 0x7a inclusive, that is a-z.
     * 
     */
    inline void ASCIILetterAtToUpper(char& outp_char)
    {
        LogDebugLine("Character at " (void*)&outp_char << " to upper");
        //0xDF = 11011111
        outp_char &= (char)0xDF;
    }
    /**
     * @brief Makes outp_char a lowercase version of it's self.
     * 
     * @details @warning If outp_char is not between A-Z, the behaviour of this
     * function is undefined.
     * 
     * @param outp_char The character to make lowercased. **ASSUMED** to be a
     * letter ranging from 0x41 to 0x5a inclusive, that is A-Z.
     * 
     */
    inline void ASCIILetterAtToLower(char& outp_char)
    {
        LogDebugLine("Character at " (void*)&outp_char << " to lower");
        //0x20 = 00100000
        outp_char |= (char)0x20;
    }

    /**
     * @brief Makes all of the letters in p_string uppercased.
     * 
     * @details Non lowercase letters are not mutated.
     * 
     * If p_string is empty the function returns without doing anything.
     *
     * @param p_string The string to make uppercased.
     * 
     */
    void ASCIIStringAtToUpper(ASCIIString& p_string);
    /**
     * @brief Makes all of the letters in p_string lowercased.
     * 
     * @details Non uppercase letters are not mutated.
     * 
     * If p_string is empty the function returns without doing anything.
     *
     * @param p_string The string to make lowercased.
     * 
     */
    void ASCIIStringAtToLower(ASCIIString& p_string);

    //TODO: Document bellow.

    /**
     * @brief Converts p_number to it's character equivalent at outp_char
     * 
     * @details Converts the numbers 0 to 9 to the ASCII characters 0 to 9 (0x30
     * to 0x39), the numbers 10 to 35 are converted to the characters A to Z.
     * Any other value of p_number is undefined.
     * 
     * @tparam T This type must be any number type that can:
     *  - Be compared to a number literal with the > operator and == operator;
     *  - Be added to a number literal with the + operator, the operator the
     *  operator should return a result of type T or type char;
     *  - Be converted to a char using a cast.
     * 
     * @param p_number The number to convert to a character.
     * @param outp_char Where the character version of p_number will be written.
     * 
     * @warning This function **ASSUMES** that p_number is in the range 0-35, if
     * this assumption is false then the value that is written to outp_char is
     * undefined.
     * 
     */
    template<typename T>
    void ConvertNumberToASCIICharacterAtAssumingProperNumber(
        const T& p_number,
        char& outp_char
    )
    {

        LogDebugLine("Converting number at " << (void*)&p_number
        << " to a character at " << (void*)&outp_char);

        //TODO: This could be made branchless by multiplying with the comparison
        //results.
        //For 0-9
        if(p_number <= 9)
        {
            outp_char = (char)(p_number + 0x30); 
        }
        //For A-z
        else
        {
            //a-z
            if(p_number > 25)
            {
                outp_char = (char)(p_number + 61)
            }
            //A-Z
            else
            {
                outp_char = (char)(p_number + 55);
            }
        }

    }
    /**
     * @brief Converts p_char to a number of type T at outp_number in base p_base.
     * 
     * @details Converts the characters '0'-'9' to 0-9(duh), 'A'-'Z' and
     * 'a'-'z' are converted to 10-35 (case insensitive). Any other character
     * sets outp_number to an undefined value.
     * 
     * @tparam T This type must be any type that can be used as a number.
     * It must support the following operators:
     *  - Conversion from a number literal;
     *  - Convertsion from a char.
     * 
     * @param p_char The character to convert.
     * @param outp_number Where to write the converted result.
     * @param p_base The base in witch p_char should be converted.
     * 
     * @warning This function **ASSUMES** that p_char is either the number
     * characters (0-9) or the letter characters (A-z case insensitive). If this
     * assumption is false the value that will be written to outp_number will be
     * undefined.
     * 
     */
    template<typename T>
    void ConvertASCIICharacterToNumberAtAssummingProperCharacter(
        const char& p_char,
        T& outp_number
    )
    {

        LogDebugLine("Converting character " << p_char << " to a number at "
         << (void*)&outp_number);

        //TODO: This could be made branchless by multiplying with the comparison
        //results.
        //For 0-9
        if(p_char <= '9')
        {
            outp_number = (T)(p_char - 0x30); 
        }
        //For A-z
        else
        {
            //a-z
            if(p_char > 'a')
            {
                outp_number = (T)(p_char - 61)
            }
            //A-Z
            else
            {
                outp_number = (T)(p_char - 55);
            }
        }



    }

    //TODO: Way to calculate how many characters would be needed to convert a
    //number to a string in a base.

    template<typename T>
    Size ConvertNumberInBaseToASCIIStringAt(
        const T& p_number,
        const unsigned int& p_base,
        ASCIIString& p_string
    )
    {

        LogDebugLine("Converting number at " << (void*)&p_number << " in base "
        << p_base << " to ASCII string " << p_string);

        //TODO: This assumes an unsigned number, make it support all types of
        //numbers.
        T l_multiple = p_base;
        T l_copy = p_number;
        while(l_copy != 0)
        {
            T l_number = l_copy % l_multiple;
            
            l_copy /= p_base;
            l_multiple *= p_base;
        }

    }
    template<typename T>
    void ConvertASCIIStringInBaseToNumberAt(
        const ASCIIString& p_string,
        const unsigned int& p_base,
        T& outp_number
    )
    {

        LogDebugLine("Converting ASCII string " << p_string << " to a number at"
        << (void*)&outp_number << " in base " << p_base);

        outp_number = 0;
        T l_multiple = 1;
        T l_temp;
        for(Size i = p_string.m_Array.m_Size; i-- > 0; l_multiple *= p_base)
        {
            ConvertASCIICharacterToNumberAtAssummingProperCharacter(
                p_string[i],
                l_temp
            );
            outp_number += l_temp * l_multiple;
        }

    }


    /**
     * @brief Converts p_number to an ASCII string at outp_string in the number
     * base p_base.
     * 
     * @details The function first calculates how many characters are needed to
     * represent p_number as a string. If p_number is less than 0 an addition
     * character is added to the result so that the first character of 
     * outp_string could be a '-'. After this a string is allocated with the 
     * required size and the function starts the actual conversion. Once the
     * conversion is completed the function returns.
     * 
     * Currently only number bases starting from 2 and ending at 36 are
     * supported, any other number base will result in an empty string being
     * created at outp_string. No allocation occurs.
     * 
     * If allocation fails then an empty string is created at outp_string and
     * the function returns.
     * 
     * There is a special edge case where the number of characters needed to
     * convert p_number to a string is greater than SIZE_MAX. In this case the
     * function creates an empty string at outp_string and returns. No 
     * allocation occurs and p_base is a correct base.
     * 
     * @time O(n), n being the number of characters that are required to convert
     * p_number to a string.
     * 
     * @tparam T This is type of p_number, this type must be capabel of the
     * following:
     *  - Copying;
     *  - Comparison using the to it's self and number literals using the <, >,
     *  != and == operators;
     *  -Arithmetic using the %, *=, /=, / operators.
     * This type also must be capable of storing at least p_base^n where n is
     * the smallest number capable of making p_number % p_base^n == p_number true.
     * 
     * @param p_number The number to convert.
     * @param outp_string Where the string version of p_number will be written.
     * @param p_base The number base in which to convert p_number, must be 
     * between 2 and 36.
     * @param p_allocate The allocator that will be used for alloating outp_string. 
     * @param p_alloc_error The callback for when allocation fails.
     * @param p_alloc_error_data The data that will be passed to p_alloc_error
     * if it is called.
     * 
     */
    template<typename T>
    void ConvertNumberToASCIIStringInBaseUsingAllocator(
        const T& p_number,
        ASCIIString& outp_string,
        const int& p_base,
        void* (&p_allocate) (Size),
        void (*p_alloc_error)(void*), void* p_alloc_error_data
    )
    {

        LogDebugLine("Converting number at " << (void*)&p_number 
        << " to an ASCII string at " << outp_string.m_Array << " in base " << p_base);

        if(p_base < 2 || p_base > 36)
        {
            LogDebugLine("The given base is either less than 2 or greater "
            "than 36, creating empty and returning.");
            outp_string = ASCIIString();
            return;
        }

        //1 for the first character.
        Size l_requiredSize = 1;
        //This value will be mutated.
        T l_numberCopy;

        //One more character is needed for the - since the number is negative.
        if(p_number < 0)
        {
            LogDebugLine("The given number is negative so incrementing the"
            " required characters so that there is space for the - character");
            ++l_requiredSize;

            LogDebugLine("Also making the number copy the opposite of p_number");
            l_numberCopy = -p_number;
        }
        else
        {
            //No need to flip the value.
            l_numberCopy = p_number;
        }
        

        //Counts how many characters would be needed for the number to be
        //converted to a string.
        for
        (
            T l_multiple = p_base;
            l_numberCopy % l_multiple != l_numberCopy;
            l_multiple *= p_base
        )
        {
            //If this is true then on the next increment l_requiredSize will
            //overflow.
            if(l_requiredSize == SIZE_MAX)
            {
                LogDebugLine("Error writing p_number as a string requires "
                "more than SIZE_MAX chacaters, creating empty and returning.");
                outp_string = ASCIIString();
                return;
            }
            ++l_requiredSize;
        }
        LogDebugLine("Discovered that " << l_requiredSize << " number of"
        " characters will be needed to convert p_number to a string");

        Array::CreateArrayAtOfCapacityUsingAllocator<char>(
            outp_string,
            l_requiredSize,
            p_allocate, p_alloc_error, p_alloc_error_data
        );
        if(outp_string.m_Array.m_Capacity < l_requiredSize)
        {
            LogDebugLine("Detected alloc error, returning.");
            return;
        }

        Size l_to = 0;
        //If the number was negative add the - .
        if(p_number < 0)
        {
            LogDebugLine("Since p_number is less than 0, the first "
            "character of the string is being set to - .");
            outp_string[0] = '-';

            LogDebugLine("Since the first index is a - the loop will only "
            "be going to the 1st index.");
            l_to = 1;
        }

        for(Size i = l_requiredSize; i-- > l_to;)
        {
            ConvertNumberToASCIICharacterAtAssumingProperNumber<T>(
                l_numberCopy % p_base,
                outp_string[i]
            );

            l_numberCopy /= p_base;
        }
        outp_string.m_Array.m_Size = l_requiredSize;

    }
    template<typename T>
    inline void ConvertNumberToASCIIStringInBaseUsingAllocator(
        const T& p_number,
        ASCIIString& outp_string,
        const int& p_base
    )
    {
        LogDebugLine("Using defaults for ConvertNumberToASCIIStringInBaseUsingAllocator");
        ConvertNumberToASCIIStringInBaseUsingAllocator(
            p_number,
            outp_string,
            p_base,
            Library::g_DEFAULT_ALLOCATOR,
            Library::g_DEFAULT_ALLOC_ERROR,
            Library::g_DEFAULT_ALLOC_ERROR_DATA
        );
        LogDebugLine("Returing from defaults for ConvertNumberToASCIIStringInBaseUsingAllocator");
    }

    /**
     * @brief Converts p_string to a number at outp_number, the number base of
     * p_string is p_base.
     * 
     * @details Conversion is done by looping through the entire string, 
     * converting each character to a number, multiplying that number by a the
     * current multiple, adding the result to outp_number and increasing the
     * multiple to it's next value(note: the case the function is case insensitive).
     * 
     * Currently only number bases starting from 2 and ending at 36 are
     * supported, any other number base will result outp_number being set to 0
     * and the function returning.
     * 
     * If the first character of the string is - the resulting number written to
     * outp_number will be negative.
     * 
     * If p_string is empty, outp_number is set to 0 and the function returns.
     * 
     * If any character in p_string cannot be converted to a number, outp_number
     * is set to 0 and the function returns.
     * 
     * @time O(n), n being the number of characters in p_string.
     * 
     * @tparam T This is type of p_number, this type must be capabel of the
     * following:
     *  - Copying;
     *  - Comparison using the to it's self and number literals using the <, >,
     *  != and == operators;
     *  -Arithmetic using the %, *=, /=, / operators. 
     * This type also must be capable of storing at least p_base^n where n is
     * p_string.m_Array.m_Size.
     * 
     * @param p_string The string to convert. 
     * @param outp_number Where the result of the conversion should be written.
     * @param p_base The base in which p_string is written.
     * 
     */
    template<typename T>
    void ConvertASCIIStringToNumberAtInBase(
        const ASCIIString& p_string,
        T& outp_number,
        const int& p_base
    )
    {

        LogDebugLine("Converting string " << p_string.m_Array
        << " to a number at " << (void*)&outp_number << " in base " << p_base);

        if(Array::ArrayIsEmpty<char>(p_string))
        {
            LogDebugLine("p_string is empty, writing 0 and returning.");
            outp_number = 0;
            return;
        }
        if(p_base < 2 || p_base > 36)
        {
            LogDebugLine("unknow base, writing 0 and returning.");
            outp_number = 0;
            return;
        }

        Size l_to = 0;

        outp_number = 0;
        T l_multiple = 1;

        if(p_string[0] == '-')
        {
            LogDebugLine("The first character of the string is -, convering negative.");
            l_to = 1;
            l_multiple = (T)-1;
        }

        T l_temp;
        for(Size i = p_string.m_Array.m_Size; i-- > l_to;)
        {
            //This block of ifs checks if the current character can be converted
            //to a number.

            if(p_base <= 10)
            {
                //If the base is up to base 10, check if there are any 
                //characters that are not in the range of 0 to p_base - 1 as a
                //character (the + 0x30 part converts the number to a character).
                if(p_string[i] < '0' || p_string[i] > (p_base - 1) + 0x30)
                {
                    LogDebugLine("Unknow character detected in p_string at"
                    " index " << i << " writing 0 and returning.");
                    outp_number = 0;
                    return;
                }
            }
            else
            {
                //In short if the current character is not a letter that can be
                //converted to a number in the context of the given base.
                if
                (
                    //The base is greater than 10, so all number are allowed, 
                    //this checks if the current character is not a number.
                    (p_string[i] < '0' && p_string[i] > '9')
                    
                    //Even tho the current character is not a number it still
                    //may be a valid letter.
                    &&
                    
                    //If the current character is not a letter ranging from
                    //A to the maximum letter that the given base permits 
                    //(the + 0x37 part converts the number to character).
                    (p_string[i] < 'A' && p_string[i] > (p_base - 1) + 0x37)

                    //The case of the letter should not matter.
                    &&

                    //From a to the maximum letter that the given base permits
                    //(the + 0x57 converts the number to a character).
                    (p_string[i] < 'a' && p_string[i] > (p_base - 1) + 0x57)
                )
                {
                    LogDebugLine("Unknow character detected in p_string at"
                    " index " << i << " writing 0 and returning.");
                    outp_number = 0;
                    return;
                }
            }
                
            ConvertASCIICharacterToNumberAtAssummingProperCharacter<T>(
                p_string[i],
                l_temp
            ); 
            l_temp *= l_multiple;

            outp_number += l_temp;

            l_multiple *= p_base;
        }

    }


    /**
     * @brief A wrapper for @ref DestroyArrayUsingDeallocator.
     * 
     */
    inline void DestroyASCIIStringUsingDeallocator(
        ASCIIString& p_string, Deallocator p_deallocate
    )
    {
        Array::DestroyArrayUsingDeallocator<char>(p_string, p_deallocate);
    }
    /**
     * @brief Defaults function for @ref DestroyASCIIStringUsingDeallocator.
     * 
     * @details For more info on defaults functions see @ref LibraryDefaultsFunctions
     * 
     */
    inline void DestroyASCIIString(ASCIIString& p_string)
    {
        LogDebugLine("Using defaults for DestroyASCIIStringUsingDeallocator.");
        DestroyASCIIStringUsingDeallocator(
            p_string,
            Library::g_DEFAULT_DEALLOCATOR
        );
    }

}

#endif // !ASCII_STRING__DATA_STRUCTURES_STRINGS_ASCII_STRING_ASCII_STRING_HPP