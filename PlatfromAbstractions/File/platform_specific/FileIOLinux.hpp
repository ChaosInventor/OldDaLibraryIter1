#ifndef FILE_IO_LINUX__IO_INCLUDE_PLATFROM_SPECIFIC_FILE_IO_LINUX_HPP
#define FILE_IO_LINUX__IO_INCLUDE_PLATFROM_SPECIFIC_FILE_IO_LINUX_HPP 

#include "../../../LibraryMeta/LibraryMeta.hpp"
#include "../../../Debugging/Logging/Log.hpp"
#include "../IO.hpp"

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

namespace Library::IO
{

    #ifdef DEBUG
    struct File;
    /**
     * @brief Logs p_file to p_log.
     * 
     * @details The format is:
     * 
     * <ADDRESS OF p_file> { m_FileDescroptor = <p_file.m_FileDescriptor>, 
     * m_EndOfFile = <p_file.m_EndOfFile> }
     * 
     * @param p_log The log to log to.
     * @param p_file The file to log.
     * 
     * @return p_log
     * 
     */
    const Debugging::Log& operator<<(const Debugging::Log& p_log, const File& p_file);
    #endif // DEBUG



    //TODO: Add last error stuff.
    struct File
    {

        /**
         * @brief The underlying file descriptor.
         * 
         */
        int m_FileDescriptor;
        /**
         * @brief Indicates whether the end of the file has been reached.
         * 
         */
        bool m_EndOfFile;
        /**
         * @brief A pointer to a c string describing the last error, may be null.
         * 
         */
        const char* m_LastErrorText;
        /**
         * @brief The last value of errno when an error occurred.
         * 
         */
        int m_LastErrorValue;

        /**
         * @brief Sets m_FileDescriptor to -1 and m_EndOfFile to false.
         * 
         */
        File():
        m_FileDescriptor(-1),
        m_EndOfFile(false),
        m_LastErrorText(nullptr),
        m_LastErrorValue(0)
        {
            LogDebugLine("Constructed default file at " << (void*)this);
        }
        /**
         * @brief Sets m_FileDescriptor to p_other.m_FileDescroptor and
         * m_EndOfFile to p_other.m_EndOfFile.
         * 
         */
        File(const File& p_other):
        m_FileDescriptor(p_other.m_FileDescriptor),
        m_EndOfFile(p_other.m_EndOfFile),
        m_LastErrorText(p_other.m_LastErrorText),
        m_LastErrorValue(p_other.m_LastErrorValue)
        {
            LogDebugLine("Constructed File by copying from " << p_other);
        }
        /**
         * @brief Does everything as the copy constructor, but at the end
         * makes p_other a default File.
         * 
         */
        File(File&& p_other):
        m_FileDescriptor(p_other.m_FileDescriptor),
        m_EndOfFile(p_other.m_EndOfFile),
        m_LastErrorText(p_other.m_LastErrorText),
        m_LastErrorValue(p_other.m_LastErrorValue)
        {
            
            LogDebugLine("Constructed File by moving from " << p_other);
            LogDebugLine("Clearing the other File now.");

            p_other.m_EndOfFile = false;
            p_other.m_FileDescriptor = -1;
            p_other.m_LastErrorText = nullptr;
            p_other.m_LastErrorValue = 0;

        }


        /**
         * @brief Sets m_FileDescriptor to p_file_descriptor and m_EndOfFile
         * to false.
         * 
         */
        File(const int& p_file_descriptor):
        m_FileDescriptor(p_file_descriptor),
        m_EndOfFile(false),
        m_LastErrorText(nullptr),
        m_LastErrorValue(0)
        {
            LogDebugLine("Constructed file at " << (void*)this
            << " with file descriptor " << p_file_descriptor);
        }


        /**
         * @brief Same as copy constructor.
         * 
         * @return *this
         *  
         */
        File& operator=(const File& p_other)
        {

            LogDebugLine("Copying File from " << p_other << " to " << *this);
        
            m_FileDescriptor = p_other.m_FileDescriptor;
            m_EndOfFile = p_other.m_EndOfFile;

            return *this;

        }
        /**
         * @brief Same as move constructor.
         * 
         * @return *this
         *  
         */
        File& operator=(File&& p_other)
        {

            LogDebugLine("Moving File from " << p_other << " to " << *this);
        
            m_FileDescriptor = p_other.m_FileDescriptor;
            m_EndOfFile = p_other.m_EndOfFile;
            m_LastErrorText = p_other.m_LastErrorText;
            m_LastErrorValue =  p_other.m_LastErrorValue;

            p_other.m_FileDescriptor = -1;
            p_other.m_EndOfFile = false;
            p_other.m_LastErrorText = nullptr;
            p_other.m_LastErrorValue = 0;

            return *this;

        }


        /**
         * @brief Returns m_FileDescriptor.
         * 
         */
        operator int() const
        {
            return m_FileDescriptor;
        }


        /**
         * @brief Checks if the file descriptors of this and p_other refer
         * to the same file on the system.
         * 
         * @details Using the fstat system call, this operator checks if
         * the two file desciptors have the same st_dev and st_ino numbers.
         * If they do have the same numbers true is returned. Otherwise
         * false is returned.
         * 
         * @note If any of the fstat calls fail for whatever reason,
         * false is returned. The most notable reason for failure might be
         * if any of the two Files have file descroptors of -1.
         * 
         * @warning There is NO special case for when the either of the
         * Files are default versions.
         * 
         * @note The end of file indicators are not compared.
         * 
         * @return True if m_FileDescriptor refers to the same file as
         * p_other.m_FileDescriptor.
         * @return False if m_FileDescriptor doesn't refer to the same file
         * as p_other.m_FileDescriptor OR if any of the system calls fail.
         * 
         */
        bool operator==(const File& p_other) const
        {

            LogDebugLine("Checking if File " << *this << " and " << p_other
            << " refer to the same file.");

            struct stat l_bufThis, l_bufOther;
            if(fstat(m_FileDescriptor, &l_bufThis) < 0)
            {
                LogDebugLine("First fstat call failed, retruning false.");
                return false;
            }
            if(fstat(p_other.m_FileDescriptor, &l_bufOther) < 0)
            {
                LogDebugLine("Second fstat call failed, retruning false.");
                return false;
            }

            LogDebugLine("Got all of the data, doing comparison now.");

            //https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/sys_stat.h.html:
            //"The st_ino and st_dev fields taken together uniquely identify the file within the system."
            return 
                (l_bufThis.st_dev == l_bufOther.st_dev)
                &&
                (l_bufThis.st_ino == l_bufOther.st_ino);

        }
        /**
         * @brief Returns the opposite of @ref operator==(const File& p_other)
         * 
         */
        bool operator!=(const File& p_other) const
        {
            LogDebugLine("Flipping the result of the comparison.");
            return !(*this == p_other);
        }

    };

    Size ReadBytesFromFile(Byte* p_bytes, const Size& p_bytes_size, void* p_file);
    Size WriteBytesToFile(const Byte* p_bytes, const Size& p_bytes_size, void* p_file);
    bool EndOfFile(void* p_file);

    Size ReadBytesFromStandardInput(Byte* p_bytes, const Size& p_bytes_size, void* p_file);

    Size WriteBytesToStandardOutput(const Byte* p_bytes, const Size& p_bytes_size, void* p_file);

    Size WriteBytesToStandardError(const Byte* p_bytes, const Size& p_bytes_size, void* p_file);

    void OpenFileStreamAtWithFileNameFlagsAndModeUsingAllocator(
        Stream& outp_stream,
        const char* p_file_name,
        const int& p_flags,
        const mode_t& p_mode,
        void* (&p_allocate) (Size),
        void (*p_alloc_error) (void*), void* p_alloc_error_data
    );

}

#endif // !FILE_IO_LINUX__IO_INCLUDE_PLATFROM_SPECIFIC_FILE_IO_LINUX_HPP
