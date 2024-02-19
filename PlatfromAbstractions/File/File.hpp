#ifndef FILE__PLATFROM_ABSTRACTIONS_FILE_FILE_HPP
#define FILE__PLATFROM_ABSTRACTIONS_FILE_FILE_HPP

#include "../../Meta/Meta.hpp"
#include "../../Debugging/Logging/Log.hpp"

//Includes the proper file for the definiton of Offset.
#ifdef __unix__
#include "platform_specific/OffsetDefPosix.hpp"
#else
#error "The file module has not been implemented for this platfrom yet, or the platfrom detection macros are working"
#endif

namespace Library::PlatfromAbstractions::File
{

    enum class FileError : signed
    {
        NotFound = 1,
        NoPermission,
        Exists,
        Directory,
        InUseByOther,
        TooManyOpenFiles,
        NoMoreSpace,
        FilePathTooLong,
        InvalidArguments,
        InvalidHandle,
        LowLevelError
    };

    struct File;


    using FileErrorHandler = void(*)(const FileError&, void*, File*, const char*);


    extern const FileErrorHandler g_DEFAULT_FILE_ERROR_HANDLER;
    extern void* const g_DEFAULT_FILE_ERROR_HANDLER_DATA;


    File* AllocateFileUsingAllocator(
        Allocator p_allocate, Callback p_alloc_error, void* p_alloc_error_data
    );
    Size AllocateFilesAtUsingAllocator(
        File** const& outp_files, const Size& p_files_size,
        Allocator p_allocate, Callback p_alloc_error, void* p_alloc_error_data
    );

    void CreateFilePathUsingFileErrorHandler(
        const char* p_file_path,
        FileErrorHandler p_file_error, void* p_file_error_data
    );

    void OpenFilePathForWritingInFileUsingFileErrorHandler(
        const char* p_file_path,
        File& p_file,
        FileErrorHandler p_file_error, void* p_file_error_data
    );
    void OpenFilePathForReadingInFileUsingFileErrorHandler(
        const char* p_file_path,
        File& p_file,
        FileErrorHandler p_file_error, void* p_file_error_data
    );
    void OpenFilePathForReadingAndWritingInFileUsingFileErrorHandler(
        const char* p_file_path,
        File& p_file,
        FileErrorHandler p_file_error, void* p_file_error_data
    );


    bool FileIsReadable(File& p_file);
    bool FileIsWritable(File& p_file);

    Offset GetLengthOfFile(File& p_file);


    Size ReadBytesFromFileStartingAtOffsetUsingFileErrorHandler(
        Byte* p_bytes, const Size& p_bytes_size,
        File& p_file,
        Offset p_offset,
        FileErrorHandler p_file_error, void* p_file_error_data
    );

    Size WriteBytesToFileStartingAtOffsetUsingFileErrorHandler(
        const Byte* p_bytes, const Size& p_bytes_size,
        File& p_file,
        Offset p_offset,
        FileErrorHandler p_file_error, void* p_file_error_data
    );

    void SetSizeOfFileToOffset(File& p_file, const Offset& p_offset);
    void IncreaseSizeOfFileByOffset(File& p_file, const Offset& p_offset);
    void DecreaseSizeOfFileByOffset(File& p_file, const Offset& p_offset);

    void CloseFile(File& p_file);

    void DeleteFilePathUsingFileErrorHandler(
        const char* p_file_path,
        FileErrorHandler p_file_error, void* p_file_error_data
    );

    void DeallocateFileUsingDeallocator(File& p_file, Deallocator p_deallocate);
    void DeallocateFilesUsingDeallocator(
        File* const* const& p_files, const Size& p_files_size,
        Deallocator p_deallocate
    );



    inline File* AllocateFile()
    {
        LogDebugLine("Using defaults for AllocateFileUsingAllocator");
        AllocateFileUsingAllocator(
            g_DEFAULT_ALLOCATOR,
            g_DEFAULT_ALLOC_ERROR, g_DEFAULT_ALLOC_ERROR_DATA
        );
    }
    inline Size AllocateFilesAt(File** const& outp_files, const Size& p_files_size)
    {
        LogDebugLine("Using defaults for AllocateFilesAtUsingAllocator");
        return AllocateFilesAtUsingAllocator(
            outp_files, p_files_size,
            g_DEFAULT_ALLOCATOR, g_DEFAULT_ALLOC_ERROR, g_DEFAULT_ALLOC_ERROR_DATA
        );
    }

    inline void CreateFilePath(const char* p_file_path)
    {
        LogDebugLine("Using defaults for CreateFilePathUsingFileErrorHandler");
        CreateFilePathUsingFileErrorHandler(
            p_file_path,
            g_DEFAULT_FILE_ERROR_HANDLER, g_DEFAULT_FILE_ERROR_HANDLER_DATA
        );
    }

    inline void OpenFilePathForWritingInFile(
        const char* p_file_path,
        File& p_file
    )
    {
        LogDebugLine("Using defaults for OpenFilePathForWritingInFileUsingFileErrorHandler");
        OpenFilePathForWritingInFileUsingFileErrorHandler(
            p_file_path, p_file,
            g_DEFAULT_FILE_ERROR_HANDLER, g_DEFAULT_FILE_ERROR_HANDLER_DATA
        );
    }
    inline void OpenFilePathForWritingInFile(
        const char* p_file_path,
        File& p_file
    )
    {
        LogDebugLine("Using defaults for OpenFilePathForReadingInFileUsingFileErrorHandler");
        OpenFilePathForReadingInFileUsingFileErrorHandler(
            p_file_path, p_file,
            g_DEFAULT_FILE_ERROR_HANDLER, g_DEFAULT_FILE_ERROR_HANDLER_DATA
        );
    }
    inline void OpenFilePathForReadingAndWritingInFile(
        const char* p_file_path,
        File& p_file
    )
    {
        LogDebugLine("Using defaults for OpenFilePathForReadingAndWritingInFileUsingFileErrorHandler");
        OpenFilePathForReadingAndWritingInFileUsingFileErrorHandler(
            p_file_path, p_file,
            g_DEFAULT_FILE_ERROR_HANDLER, g_DEFAULT_FILE_ERROR_HANDLER_DATA
        );
    }


    inline Size ReadBytesFromFileStartingAtOffset(
        Byte* p_bytes, const Size& p_bytes_size,
        File& p_file,
        Offset p_offset
    )
    {
        LogDebugLine("Using defaults for ReadBytesFromFileStartingAtOffsetUsingFileErrorHandler");
        ReadBytesFromFileStartingAtOffsetUsingFileErrorHandler(
            p_bytes, p_bytes_size,
            p_file,
            p_offset,
            g_DEFAULT_FILE_ERROR_HANDLER, g_DEFAULT_FILE_ERROR_HANDLER_DATA
        );
    }

    inline Size WriteBytesToFileStartingAtOffset(
        const Byte* p_bytes, const Size& p_bytes_size,
        File& p_file,
        Offset p_offset
    )
    {
        LogDebugLine("Using defaults for WriteBytesToFileStartingAtOffsetUsingFileErrorHandler");
        WriteBytesToFileStartingAtOffsetUsingFileErrorHandler(
            p_bytes, p_bytes_size,
            p_file,
            p_offset,
            g_DEFAULT_FILE_ERROR_HANDLER, g_DEFAULT_FILE_ERROR_HANDLER_DATA
        );
    }


    inline void DeleteFilePath(const char* p_file_path)
    {
        LogDebugLine("Using defaults for DeleteFilePathUsingFileErrorHandler");
        DeleteFilePathUsingFileErrorHandler(
            p_file_path,
            g_DEFAULT_FILE_ERROR_HANDLER, g_DEFAULT_FILE_ERROR_HANDLER_DATA
        );
    }

    inline void DeallocateFile(File& p_file)
    {
        LogDebugLine("Using defaults for DeallocateFileUsingDeallocator");
        DeallocateFileUsingDeallocator(p_file, g_DEFAULT_DEALLOCATOR);
    }
    inline void DeallocateFiles(File* const* const& p_files, const Size& p_files_size)
    {
        LogDebugLine("Using defaults for DeallocateFilesUsingDeallocator");
        DeallocateFilesUsingDeallocator(p_files, p_files_size, g_DEFAULT_DEALLOCATOR);
    }


}

#endif //FILE__PLATFROM_ABSTRACTIONS_FILE_FILE_HPP