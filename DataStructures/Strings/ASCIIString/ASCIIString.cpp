#include "ASCIIString.hpp"

using namespace Library::DataStructures::Array;
using namespace Library::IO;

namespace Library::DataStructures::Strings
{

    #ifdef DEBUG
    const Debugging::Log& operator<<(const Debugging::Log& p_log, const ASCIIString& p_string)
    {

        p_log << (void*)&p_string;
        p_log << " { ";
        p_log << "m_Array = " << p_string.m_Array;
        p_log << ", characters:\n\t\t";
        for(Size i = 0; i < p_string.m_Array.m_Size; ++i)
        {
            p_log << p_string[i];
        }
        p_log << " }";

        return p_log;

    }
    #endif // DEBUG



    //TODO: Overwrite macro for this.
    const ASCIIString g_WHITE_SPACES = Array::Array<char>((char*)" \t", 2);


    ASCIIString::ASCIIString(const char* p_c_string)
    {
        CreateASCIIStringAtFromCopyOfCString(*this, p_c_string);
    }

    bool ASCIIString::operator== (const char* const p_c_string) const
    {

        LogDebugLine("Checking if ASCIIString at " << this << " is equaled "
        << "to c string at " << (void*)p_c_string << ".");

        if(p_c_string == nullptr || m_Array.m_Buffer == nullptr)
        {
            LogDebugLine("Etiher c string or m_Array is null, returning " 
            "whether both of them are null.");
            return p_c_string == nullptr && m_Array.m_Buffer == nullptr;
        }

        LogDebugLine("Starting comparison of charaters.");

        Size i;
        for(i = 0; i < m_Array.m_Size && p_c_string[i] != '\0'; ++i)
        {
            if(m_Array[i] != p_c_string[i])
            {
                LogDebugLine("Found missmatch at index " << i << " returning"
                " false.");
                return false;
            }
        }

        LogDebugLine("End of one of the arrays was reached, returning "
        "wheather both ends have been reached.");
        //This is only true if the end of both was reached.
        return i == m_Array.m_Size && p_c_string[i] == '\0';

    }


    Size FindSizeOfCString(const char* const p_c_string)
    {
        LogDebugLine("Finding size of c string at " << (void*)p_c_string);
        Size i;
        for(i = 0; p_c_string[i] != '\0'; ++i);
        return i;
    }


    void CreateASCIIStringAtFromCopyOfCStringUsingAllocator(
        ASCIIString& outp_buffer,
        const char* const p_c_string,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    )
    {

        LogDebugLine("Making copy of c string at " << (void*)p_c_string <<
        " to string " << outp_buffer.m_Array);

        if(p_c_string == nullptr)
        {
            LogDebugLine("The c string is null, creating empty and returning.");
            outp_buffer = ASCIIString();
            return;
        }

        Size l_sizeOfCString = FindSizeOfCString(p_c_string);
        LogDebugLine("The size of the given c string is " << l_sizeOfCString);

        if(l_sizeOfCString == 0)
        {
            LogDebugLine("The c string's size is 0, creating empty and returning.");
            outp_buffer = ASCIIString();
            return;
        }

        LogDebugLine("Allocating buffer of size " << sizeof(char) <<" * "
        << l_sizeOfCString);
        
        CreateArrayAtOfCapacityUsingAllocator<char>(
            outp_buffer,
            l_sizeOfCString,
            p_allocate, p_alloc_error, p_alloc_error_data
        );

        if(outp_buffer.m_Array.m_Buffer == nullptr)
        {
            LogDebugLine("Detected allocation failure, returning.");
            return;
        }

        LogDebugLine("Allocation successful, the allocated buffer is "
        << (void*)outp_buffer.m_Array.m_Buffer);

        LogDebugLine("Copying all of the charaters from the c string to "
        "the new buffer, starting at index 0");
        for(Size i = 0; i < l_sizeOfCString; ++i)
        {
            outp_buffer[i] = p_c_string[i];
        }

        LogDebugLine("Copying completed, setting up the size and capacity of the string and returning");
        outp_buffer.m_Array.m_Size = l_sizeOfCString;

    }


    //TODO: There is some good documentation here. Copy it in the new function
    /*
    void RemoveAllWhitespacesFromASCIIString(ASCIIString& p_string)
    {

        LogDebugLine("Removing all whitespaces from string at " << p_string.m_Array);

        if(p_string == nullptr)
        {
            LogDebugLine("The string has a null buffer returning");
            return;
        }

        //This algorithm works by slowly gravitating all of the whitespaces to
        //the end of the array, after that is done the size of the array is
        //simply shrunk.
        //
        //It does this by first finding the last whitespace in terms of the
        //distance from the end of the array. Then it looks at the next characters
        //after the last whitespace, if the current charater that it is looking
        //at is a non whitespace it swaps it with the last whitespace and the
        //new last whitespace is assumed to be right after the new one. This
        //assumption is true because the whitespace either got swapped with the
        //next character after it making it's position +1 from it's old one or
        //it had encountered another whitespace and the character currently
        //being examined is after a series of other whitespace. This happens
        //because when the current character is a whitespace the last one is not
        //swapped with it and the current character goes on to the next one.
        //This causes all of the white spaces in the string to 'stick' to each 
        //other and slowly move to the end. In otherwords the current character 
        //becomes the index where the glob of white spaces ends, and the last
        //whitespace becomes the index where the glob of whitespaces starts.

        Size l_numberOfWhiteSpaces = 0;
        Size l_lastWhitespace;

        for
        (
            l_lastWhitespace = 0;
            l_lastWhitespace < p_string.m_Array.m_Size;
            ++l_lastWhitespace
        )
        {
            if(p_string[l_lastWhitespace] == ' ')
            {
                LogDebugLine("Found the last whitespace at index " << l_lastWhitespace);
                ++l_numberOfWhiteSpaces;

                break;
            }
        }

        //l_lastWhitespace + 1 cannot overflow here. The reason is since
        //l_lastWhitespace can only be a number between 0 and m_Size - 1
        //and the maximum number that m_Size can be is SIZE_MAX, as such
        //if l_lastWhiteSpace was the very last charater it's value would
        //be SIZE_MAX - 1
        for(Size n = l_lastWhitespace + 1; n < p_string.m_Array.m_Size; ++n)
        {
            //If the current character is not a white space swap it with
            //the last one. This causes the white space to move to the
            //end of the array and the non white spaces to move backward.
            if(p_string[n] != ' ')
            {
                //IDEA: Instead of doing a swap every single time, it may be more
                //efficient to have the start of the whitespace glob sperate from
                //the curret character. This would allow to only string swapping
                //when a whitespace is reached as the current character, this
                //new swapping mechanism would work by swapping the start of the
                //whitespace glob with the current character (which is a
                //whitespace) - 1 and the the start - 1 with cur char - 2, etc.
                //This would lower the number of swaps and would most likely
                //speed up the algorithm.


                LogDebugLine("Swapping the last whitespace with"
                " the charater at index " << n << ", the index of the"
                " last character is " << l_lastWhitespace);

                p_string[l_lastWhitespace] = p_string[n];
                p_string[n] = ' ';

                //After the last whitespace there are only 2 
                //possibilities: either the next charater is the new
                //last white space or it's the same white space.
                ++l_lastWhitespace;
            }
            //If the current character is a whitespace simply skip it,
            //the last white space at this point is right behind it, so
            //when a non whitespace character is occurred it will become
            //the new last whitespace.
            else
            {
                LogDebugLine("Found another whitespace at index "
                << n << "skipping the swap and going onto the next"
                " character");
                //This count is needed for later when reallocation occurs.
                ++l_numberOfWhiteSpaces;
            }
        }

        LogDebugLine("Reached the end of the string, all of the"
        " whitespaces are now at the end of it");
        //All white spaces are at the end of the array at this point.


        LogDebugLine("Discovered " << l_numberOfWhiteSpaces
        << " whitespaces in the string.");

        //This cannot overflow since l_numberOfWhiteSpaces can only range from
        //0 to p_string.m_Array.m_Size.
        p_string.m_Array.m_Size -= l_numberOfWhiteSpaces;

    }
    */

    void RemoveTrailingWhitespacesFromASCIIString(ASCIIString& p_string)
    {

        LogDebugLine("Removing all trailing whitespaces from string at " << p_string.m_Array);

        if(ArrayIsEmpty<char>(p_string))
        {
            LogDebugLine("The given string is empty, returning");
            return;
        }

        Size l_numberOfWhitespaces = 0;
        for(Size i = p_string.m_Array.m_Size; i-- > 0;)
        {
            if(p_string[i] == ' ')
            {
                LogDebugLine("Found whitespace at index " << i);
                ++l_numberOfWhitespaces;
            }
            else
            {
                LogDebugLine("Trailing whitespaces end at index " << i);
                break;
            }
        }        

        LogDebugLine("Discovered " << l_numberOfWhitespaces << " whitespaces");

        //Can't overflow since l_numberOfWhitespace can range between 0 and
        //p_string.m_Array.m_Size.
        p_string.m_Array.m_Size -= l_numberOfWhitespaces;

    }


    void ASCIIStringAtToUpper(ASCIIString& p_string)
    {

        LogDebugLine("Making all characters in ASCII string at "
        << p_string.m_Array << " to be uppercase");

        for(Size i = 0; i < p_string.m_Array.m_Size; ++i)
        {
            if(ASCIICharacterIsLowercaseLetter(p_string[i]))
            {
                ASCIILetterAtToUpper(p_string[i]);
            }
        }

    }
    void ASCIIStringAtToLower(ASCIIString& p_string)
    {

        LogDebugLine("Making all characters in ASCII string at "
        << p_string.m_Array << " to be lowercase");

        for(Size i = 0; i < p_string.m_Array.m_Size; ++i)
        {
            if(ASCIICharacterIsUppercaseLetter(p_string[i]))
            {
                ASCIILetterAtToLower(p_string[i]);
            }
        }

    }

}
