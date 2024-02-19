/** @file IO.hpp
 * @brief Declares everything in the @ref IOMod module.
 *
 */
#ifndef IO__IO_IO_HPP
#define IO__IO_IO_HPP

#include "../../Meta/Meta.hpp"
#include "../../Debugging/Logging/Log.hpp"

/**
 * @brief You can find the entire @ref IOMod under this namespace.
 *
 */
namespace Library::IO
{

    #ifdef DEBUG
    struct Stream;
    /**
     * @brief Logs p_stream's fields to p_log.
     *
     * @details The format in which the stream is logged is:\n
     * <ADDRESS OF p_stream> { Read = <ADDRESS OF READ FUNCTION>,
     * Write = <ADDRESS OF WRITE FUNCTION>, End = <ADDRESS OF END FUNCTION>,
     * Thing = <ADDRESS OF THING> }
     *
     * @note The addresses that are log are the same as the ones that are
     * stored in p_stream.
     *
     * @bug The function pointers are cast to void* this MIGHT cause some
     * issuse in some rare cases.
     *
     * @param p_log The Log to log to.
     * @param p_stream The stream to log.
     * @return p_log
     *
     */
    const Debugging::Log& operator<<(const Debugging::Log& p_log, const Stream& p_stream);
    #endif //DEBUG



    /**
     * @brief A data structure that defines an abstract interface for doing
     * %IO(input output) on anything.
     *
     * @details The abstract %IO interface is defined by a collection of
     * function pointers and object pointers. These pointers are:
     * - m_Thing, this is a void* that points to an opaque object that holds all
     * of the data and state that is needed for %IO.
     * - m_GetLastErrorFromThing, this is a pointer to a function that returns
     * an immutable c string that describes the last %IO error that had occurred
     * in the given thing.
     * - m_ReadBytesFromThing, this is a function pointer that reads a number of
     * bytes from the given thing.
     * - m_WriteBytesToThing, this is a function pointer that write the given
     * bytes to the given thing.
     * - m_EndOfThing, this is a function pointer that returns true if no more
     * reading or writing can be done to the given thing. It returns false
     * otherwise.
     *
     * Check each members' documentation for the full details on how each of
     * them work.
     *
     * @warning **DO NOT** mix and match pointers from different streams. For
     * example do not use the read function of one stream with the m_Thing of
     * a different streams. Doing so is undefined behaviour.
     *
     *
     * @section IOStreamIOThing The IO thing
     * Through out the documentation for this module you'll find the term "IO
     * thing". The %IO thing refers to the thing that %IO is being done on, be it
     * a file, a pipe, a queue, a string ect. It's used as an abstract way to
     * refer to either of those things, what ever it may actually be.
     *
     *
     * @section IOStreamCreating Creating a stream
     * This module does not provide a way to create a valid stream on which %IO
     * can be done. Other modules in the library do this. However this module
     * does provide 4 global and constant streams on which %IO can be done:
     * - @ref g_StandardInputStream, this stream can be used for reading from
     * the process's standard input.
     * - @ref g_StandardOutputStream, this stream can be used for writing to the
     * process's standard output.
     * - @ref g_StandardErrorStream, this stream can be used for writing to the
     * process's standard error.
     * - @ref g_NullStream, this is a special stream to which all writes are
     * discarded but still succeed and all reads zero out any byte buffers.
     *
     * @subsection IOStreamUsefulModules Modules for creating streams
     * Here is a list of other modules in the library that can be helpful in
     * creating streams:
     * //TODO: Link to the modules.
     *
     *
     * @section IOStreamTypes Types of streams
     * A stream can be classified under different types depending on the values
     * of its members. Something you'll notice is that all of the types are
     * determented by the values of m_ReadBytesFromThing and m_WriteByteToThing.
     *
     * Here is a list of all of them:
     * - Null streams or default streams, you cannot do anything with these
     * streams. They are used as either as error indicators or for representing
     * a stream that cannot be used for %IO yet. If a stream is of this type
     * then you can safely assume the following about that stream:
     *      - m_ReadBytesFromThing, m_WriteBytesToThing and m_EndOfThing are set
     *      to null.
     *      - m_GetLastErrorFromThing and m_Thing may be null or something else,
     *      do not make any assumptions about them.
     *
     * You can use the @ref StreamIsNull function to check if a stream is of
     * this type.
     *
     * - Read-only streams, you cannot write to these streams, you can only
     * read from them. If a stream is of this type then you can safely assume
     * the following about that stream:
     *      - m_ReadBytesFromThing is a non null value and can safely be called.
     *      - m_WriteBytesToThing is null and cannot be called.
     *      - m_EndOfThing, m_GetLastErrorFromThing and m_Thing can be anything, do
     *      not make any assumptions about them.
     *
     * You can use the @ref StreamIsReadOnly function to check if a stream is of
     * this type.
     *
     * - Write-only streams, you cannot read form these streams, you can only
     * write to them. If a stream is of this type then you can safely assume the
     * following about that stream:
     *      - m_ReadBytesFromThing is null and cannot be called.
     *      - m_WriteBytesToThing is a non null value and can safely be called.
     *      - m_EndOfThing, m_GetLastErrorFromThing and m_Thing can be anything, do
     *      not make any assumptions about them.
     *
     * You can use the @ref StreamIsWriteOnly function to check if a stream is
     * of this type.
     *
     * - Read-write streams, you can read from and write to these streams. If a
     * stream is of this type then you can safely assume the following about
     * that stream:
     *      - m_ReadBytesFromThing and m_WriteBytesToThing are a non null values
     *      and can be safely called.
     *      - m_EndOfThing, m_GetLastErrorFromThing and m_Thing can be anything, do
     *      not make assumptions about them.
     *
     * You can use the @ref StreamIsReadWrite function to check if a stream is
     * of this type.
     *
     * @subsection IOStreamInfOrFin Infinite and finite streams
     * In addition to the above streams, a stream can also be classified as a:
     *
     * - Inifinite stream, a read or write to this stream can never fail. You
     * can read or write to this type of stream forever. If a stream is of this
     * type then you can safely assume the following about that stream:
     *      - m_ReadBytesFromThing and m_WriteBytesToThing and m_Thing can be
     *      anything, do not make any assumptions about them.
     *      - m_EndOfThing and m_GetLastErrorFromThing are null and cannot be called.
     *
     * You can use the @ref StreamIsInfinite function to check if a stream is
     * of this type.
     *
     * - Finite stream, a read or write to this stream can fail. You cannot read
     * or write to this type of stream forever. If a stream is of this type
     * then you can safely assume the following about that stream:
     *      - m_ReadBytesFromThing and m_WriteBytesToThing and m_Thing can be
     *      anything, do not make any assumptions about them.
     *      - Either m_EndOfThing, m_GetLastErrorFromThing or both are non null
     *      values. This means that either m_EndOfThing, m_GetLastErrorFromThing
     *      or both can be called. You still have to check for null values in
     *      both tho.
     *
     * You can use the @ref StreamIsFinite function to check if a stream is
     * of this type.
     *
     *
     * @section IOStreamYourOwnStream Defining your own %IO thing
     * You can define your own IO thing or make an existant thing compatible
     * with the stream interface. To do this you must:
     * -# Provide a creation function that creates a valid stream that can be
     * used for doing %IO on your thing. The created stream must be of the above
     * types. All of the created stream's pointers must behave exactly as
     * specified in the pointers' documentation.
     * -# If needed provide a destruction function for releasing any resources
     * from the stream once it has been used. If resources are automatically
     * released there is no need for a destruction function.
     *
     */
    struct Stream
    {

        /**
         * @brief Reads as many bytes as possible from p_thing, the %IO thing,
         * and puts them into p_bytes.
         *
         * @details Bytes are read from the %IO thing and put into the buffer
         * pointed by p_bytes. p_bytes is assumed to be able to hold at most
         * p_bytes_size bytes. The first byte read form the %IO thing is put in
         * index 0, the second into index 1 and so on.
         * Reading continues until:
         * - p_bytes_size bytes are read.
         * - no more reading can be done because:
         *      - there are no more bytes to read.
         *      - an error occurred.
         *      - because more bytes will become available in a future read.
         *
         * The details on how to tell how many bytes were read is documented in
         * the returns section.
         *
         * @warning This pointer could be null. Always check before calling.
         *
         * @param p_bytes Assumed to be pointer to a byte buffer. The buffer is
         * assumed to be of length p_bytes_size.
         * @param p_bytes_size How many bytes can be put into p_bytes starting
         * form index 0 and going up (ex: a p_bytes_size of 3 means that a byte
         * can be put into p_bytes[0], p_bytes[1] and p_bytes[2], using any
         * other index is assumed to be undefined behaviour).
         * @param p_thing The %IO thing, you should always pass the stream's
         * m_Thing.
         *
         * @returns A value between 0 and p_bytes_size. This value depends on
         * how the reading went:
         * - 0, an error or the end of the thing had been reached, errors are
         * detailed below. None of the bytes in p_bytes have been mutated by the
         * read. What you should do in this case largely depends on the error.
         * - < p_bytes_size, only *returned_value* number of bytes were read.
         * This means that p_bytes only contains read bytes ranging from index 0
         * to *returned_value* - 1, any other bytes in p_bytes were not mutated
         * by the read function. In this case you should keep trying to read
         * until you get a return value of 0 or read all of the bytes you need.
         * - p_bytes_size, p_bytes was filled with bytes ranging from index 0
         * and index p_bytes_size - 1. No error had occurred and the read was
         * fully successful.
         *
         * The read function might fail and return 0 because:
         * - The end of the %IO thing has been reached, you can confirm this
         * using the @ref m_EndOfThing function. Check its documentation for
         * details.
         * - An error occurred, you can confirm this using the
         * @ref m_GetLastErrorFromThing function. Check its documentation for
         * details.
         *
         * @note This function could potentially block the calling thread until
         * there are bytes available for reading. This is usually specified by
         * the %IO thing.
         *
         * If this pointer is null then the %IO thing cannot be read from. For
         * more details see @ref IOStreamTypes.
         *
         */
        Size (*m_ReadBytesFromThing) (
            Byte* p_bytes, const Size& p_bytes_size,
            void* p_thing
        );
        /**
         * @brief Writes as many bytes as possible from p_bytes and puts them to
         * p_thing, the %IO thing.
         *
         * @details Bytes are written from the buffer pointed by p_bytes and put
         * into the %IO thing. p_bytes is assumed to have p_bytes_size bytes.
         * The first byte written to the %IO thing is index 0, the second is
         * index 1 and so on.
         * Writing continues until:
         * - p_bytes_size bytes are written.
         * - no more writing can be done because:
         *      - there is no more space to write into.
         *      - an error occurred.
         *      - because more space will become available in a future write.
         *
         * The details on how to tell how many bytes were written is documented
         * in the returns section.
         *
         * @warning This pointer could be null. Always check before calling.
         *
         * @param p_bytes Assumed to be pointer to a byte buffer. The buffer is
         * assumed to be of length p_bytes_size.
         * @param p_bytes_size How many bytes are in p_bytes starting form index
         * 0 and going up (ex: a p_bytes_size of 3 means that a byte can be
         * found in p_bytes[0], p_bytes[1] and p_bytes[2], using any other index
         * is assumed to be undefined behaviour).
         * @param p_thing The %IO thing, you should always pass the stream's
         * m_Thing.
         *
         * @returns A value between 0 and p_bytes_size. This value depends on
         * how the writting went:
         * - 0, an error or the end of the thing had been reached, errors are
         * detailed below. None of the bytes in p_bytes have been written. What
         * you should do in this case largely depends on the error.
         * - < p_bytes_size, only *returned_value* number of bytes were written.
         * This means that only bytes ranging from index 0 to *returned_value*
         * - 1 were written, any other bytes in p_bytes were not written. In
         * this case you should keep trying to write until you get a return
         * value of 0 or write all of the bytes you need.
         * - p_bytes_size, bytes ranging from index 0 and index p_bytes_size - 1
         * were written. No error had occurred and the write was fully
         * successful.
         *
         * The write function might fail and return 0 because:
         * - The end of the %IO thing has been reached, you can confirm this
         * using the @ref m_EndOfThing function. Check its documentation for
         * details.
         * - An error occurred, you can confirm this using the
         * @ref m_GetLastErrorFromThing function. Check its documentation for
         * details.
         *
         * @note This function could potentially block the calling thread until
         * there is space available for writing. This is usually specified by
         * the %IO thing.
         *
         * If this pointer is null then the %IO thing cannot be written to. For
         * more details see @ref IOStreamTypes.
         *
         */
        Size (*m_WriteBytesToThing) (
            const Byte* p_bytes, const Size& p_bytes_size,
            void* p_thing
        );

        /**
         * @brief Checks if the end of p_thing, the %IO thing, has been reached.
         *
         * @details "The end of the IO thing" here refers to a point where no
         * more reads or writes can happen due to there being no more resources
         * or because of outside factors. Once the end of thing has been reached
         * it does not mean that it will stay that way forever. It may change
         * after some time or after some event. This largely depends on what the
         * %IO thing is. The stream interface cannot be used to predict the end
         * of the %IO thing or to somehow change it, you have to use %IO thing
         * specific methods (For example seek in a file). %IO things usually
         * document the details of this.
         *
         * @warning The value of this pointer may be null. Always check before
         * calling.
         *
         * @param p_thing The the %IO thing, you should always pass the stream's
         * m_Thing field as this paramater.
         *
         * @return True if the end of the thing has been reached, false if it
         * has not been.
         *
         * If the value of this pointer is null, and the %IO thing was created
         * successfully, without any errors, then the %IO thing is endless, and
         * an end to it can never be reached. If m_GetLastErrorFromThing is also
         * null then the stream is infinite, see @ref IOStreamInfOrFin for more
         * details.
         *
         * @time Depends on the %IO thing.
         * @memory Depends on th %IO thing.
         *
         */
        bool (*m_EndOfThing) (void* p_thing);
        /**
         * @brief Checks if an error had occurred in p_thing, the %IO thing.
         *
         * @details An error here refers to an event from which no recovery can
         * be made. When an error occurs no more %IO can be done on the %IO
         * thing.
         *
         * @warning The value of this pointer may be null. Always check before
         * calling.
         *
         * @param p_thing The %IO thing, you should always pass the stream's
         * m_Thing.
         *
         * @return A pointer to a c string that describes the error, if it had
         * occurred. **DO NOT MODIFY THE C STRING POINTED TO BY THE RETURN VALUE
         * ,** if you do the behaviour is undefined. The c string does not start
         * with a whitespace, new line or tab, no other guarantees can be given
         * for the format of the error message. %IO thing usually document their
         * error messages in detail. You do not need to do any clean up on the
         * return value, error message are USUALLY global string literals.
         * @return If no error had occurred this function returns null.
         *
         * If the value of this pointer is null, and the %IO thing was created
         * successfully, without any errors, then the %IO thing can never be in
         * an error state. If m_EndOfThing is also null then the stream is
         * infinite, see @ref IOStreamInfOrFin for more details.
         *
         * @time Depends on the %IO thing.
         * @memory Depends on th %IO thing.
         *
         */
        const char* (*m_GetLastErrorFromThing) (void* p_thing);

        /**
         * @brief An opaque pointer that holds data about %IO.
         *
         * @details The value of this pointer and what data it points to is
         * entirely dependant on the %IO thing is. You should not
         * modify the value of this pointer or assume that it holds any type of
         * data. The only exception being if the %IO thing defines the value of
         * this pointer and what it points to AND at the same time you expect
         * all of the streams you use to be of that %IO thing.
         *
         * The value of this pointer must be passed to all of the other function
         * pointers in the same stream.
         *
         */
        void* m_Thing;


        /** @brief Sets all fields to null. */
        Stream():
        m_ReadBytesFromThing(nullptr),
        m_WriteBytesToThing(nullptr),

        m_EndOfThing(nullptr),
        m_GetLastErrorFromThing(nullptr),

        m_Thing(nullptr)
        {
            LogDebugLine("Constructed empty stream at " << (void*)this);
        }
        /** @brief Copies all of the fields from p_other to this. */
        Stream(const Stream& p_other):
        m_ReadBytesFromThing(p_other.m_ReadBytesFromThing),
        m_WriteBytesToThing(p_other.m_WriteBytesToThing),

        m_EndOfThing(p_other.m_EndOfThing),
        m_GetLastErrorFromThing(p_other.m_GetLastErrorFromThing),

        m_Thing(p_other.m_Thing)
        {
            LogDebugLine("Constructed stream by copying from stream " << p_other
            << " to stream at " << (void*)this);
        }
        /**
         * @brief Copies all of the fields from p_other to this and sets all of
         * p_other's fields to null.
         *
         */
        Stream(Stream&& p_other):
        m_ReadBytesFromThing(p_other.m_ReadBytesFromThing),
        m_WriteBytesToThing(p_other.m_WriteBytesToThing),

        m_EndOfThing(p_other.m_EndOfThing),
        m_GetLastErrorFromThing(p_other.m_GetLastErrorFromThing),

        m_Thing(p_other.m_Thing)
        {

            p_other.m_ReadBytesFromThing = nullptr;
            p_other.m_WriteBytesToThing = nullptr;

            p_other.m_EndOfThing = nullptr;
            p_other.m_GetLastErrorFromThing = nullptr;

            p_other.m_Thing = nullptr;

            LogDebugLine("Constructed stream by moving from stream "
            << p_other << " to stream at " << (void*)this);

        }

        /**
         * @brief Sets all fields to their coresponding paramater.
         *
         */
        Stream(
            Size (*p_read_bytes_from_thing) (Byte*, const Size&, void*),
            Size (*p_write_bytes_to_thing) (const Byte*, const Size&, void*),
            bool (*p_end_of_thing) (void*),
            const char* (*p_get_last_error_from_thing) (void*),
            void* p_thing
        ):
        m_ReadBytesFromThing(p_read_bytes_from_thing),
        m_WriteBytesToThing(p_write_bytes_to_thing),

        m_EndOfThing(p_end_of_thing),
        m_GetLastErrorFromThing(p_get_last_error_from_thing),

        m_Thing(p_thing)
        {
            LogDebugLine("Constructed stream " << *this);
        }
        /**
         * @brief Sets all fields to their coresponding paramater.
         * m_WriteBytesToThing is set to null.
         *
         */
        Stream(
            Size (*p_read_bytes_from_thing) (Byte*, const Size&, void*),
            bool (*p_end_of_thing) (void*),
            const char* (*p_get_last_error_from_thing) (void*),
            void* p_thing
        ):
        m_ReadBytesFromThing(p_read_bytes_from_thing),
        m_WriteBytesToThing(nullptr),

        m_EndOfThing(p_end_of_thing),
        m_GetLastErrorFromThing(p_get_last_error_from_thing),

        m_Thing(p_thing)
        {
            LogDebugLine("Constructed read only stream: " << *this);
        }
        /**
         * @brief Sets all fields to their coresponding paramater.
         * m_ReadBytesFromThing is set to null.
         *
         */
        Stream(
            Size (*p_write_bytes_to_thing) (const Byte*, const Size&, void*),
            bool (*p_end_of_thing) (void*),
            const char* (*p_get_last_error_from_thing) (void*),
            void* p_thing
        ):
        m_ReadBytesFromThing(nullptr),
        m_WriteBytesToThing(p_write_bytes_to_thing),

        m_EndOfThing(p_end_of_thing),
        m_GetLastErrorFromThing(p_get_last_error_from_thing),

        m_Thing(p_thing)
        {
            LogDebugLine("Constructed write only stream: " << *this);
        }

        /**
         * @brief Same as copy constructor.
         *
         * @return *this.
         *
         */
        Stream& operator=(const Stream& p_other)
        {

            LogDebugLine("Copying from stream " << p_other << " to " << *this);

            m_ReadBytesFromThing = p_other.m_ReadBytesFromThing;
            m_WriteBytesToThing = p_other.m_WriteBytesToThing;
            m_EndOfThing = p_other.m_EndOfThing;

            m_Thing = p_other.m_Thing;
            m_GetLastErrorFromThing = p_other.m_GetLastErrorFromThing;

            return *this;

        }
        /**
         * @brief Same as move constructor.
         *
         * @return *this.
         *
         */
        Stream& operator=(Stream&& p_other)
        {

            LogDebugLine("Moving from stream " << p_other << " to " << *this);

            m_ReadBytesFromThing = p_other.m_ReadBytesFromThing;
            m_WriteBytesToThing = p_other.m_WriteBytesToThing;
            m_EndOfThing = p_other.m_EndOfThing;

            m_Thing = p_other.m_Thing;
            m_GetLastErrorFromThing = p_other.m_GetLastErrorFromThing;


            p_other.m_ReadBytesFromThing = nullptr;
            p_other.m_WriteBytesToThing = nullptr;
            p_other.m_EndOfThing = nullptr;

            p_other.m_Thing = nullptr;
            p_other.m_GetLastErrorFromThing = nullptr;

            return *this;

        }

    };


    /**
     * @brief Checks if p_stream is a null stream.
     *
     * @details For details on the different stream types see @ref StreamTypes
     *
     * @param p_stream The stream to check.
     * @return True if p_stream is a null stream, false otherwise.
     *
     */
    inline bool StreamIsNull(const Stream& p_stream)
    {
        return
            p_stream.m_WriteBytesToThing == nullptr
            &&
            p_stream.m_ReadBytesFromThing == nullptr;
    }
    /**
     * @brief Checks if p_stream is a read-only stream.
     *
     * @details For details on the different stream types see @ref StreamTypes
     *
     * @param p_stream The stream to check.
     * @return True if p_stream is a read-only stream, false otherwise.
     *
     */
    inline bool StreamIsReadOnly(const Stream& p_stream)
    {
        return
            p_stream.m_WriteBytesToThing == nullptr
            &&
            p_stream.m_ReadBytesFromThing != nullptr;
    }
    /**
     * @brief Checks if p_stream is a write-only stream.
     *
     * @details For details on the different stream types see @ref StreamTypes
     *
     * @param p_stream The stream to check.
     * @return True if p_stream is a write-only stream, false otherwise.
     *
     */
    inline bool StreamIsWriteOnly(const Stream& p_stream)
    {
        return
            p_stream.m_WriteBytesToThing != nullptr
            &&
            p_stream.m_ReadBytesFromThing == nullptr;
    }
    /**
     * @brief Checks if p_stream is a read-write stream.
     *
     * @details For details on the different stream types see @ref StreamTypes
     *
     * @param p_stream The stream to check.
     * @return True if p_stream is a read-write stream, false otherwise.
     *
     */
    inline bool StreamIsReadWrite(const Stream& p_stream)
    {
        return
            p_stream.m_WriteBytesToThing != nullptr
            &&
            p_stream.m_ReadBytesFromThing != nullptr;
    }
    /**
     * @brief Checks if p_stream is an infinite stream.
     *
     * @details For details on the different stream types see @ref IOStreamInfOrFin
     *
     * @param p_stream The stream to check.
     * @return True if p_stream is an infinite stream, false otherwise.
     *
     */
    inline bool StreamIsInfinite(const Stream& p_stream)
    {
        return
            p_stream.m_EndOfThing == nullptr
            &&
            p_stream.m_GetLastErrorFromThing == nullptr;
    }
    /**
     * @brief Checks if p_stream is a finite stream.
     *
     * @details For details on the different stream types see @ref IOStreamInfOrFin
     *
     * @param p_stream The stream to check.
     * @return True if p_stream is a finite stream, false otherwise.
     *
     */
    inline bool StreamIsFinite(const Stream& p_stream)
    {
        return
            p_stream.m_EndOfThing != nullptr
            ||
            p_stream.m_GetLastErrorFromThing != nullptr;
    }


    /**
     * @brief Writes p_item as raw bytes to p_stream.
     *
     * @details p_item is assumed to be an array of bytes that has sizeof(T)
     * bytes. This byte array is then given to p_stream.m_WriteBytesToThing. The
     * thing passed to the write function is p_stream.m_WriteBytesToThing.
     *
     * @warning **THIS OPERATOR IS EXTREMELY LOW LEVEL! USE IT AT YOUR OWN RISK.**
     *
     * @warning p_stream.m_WriteBytesToThing is assumed to be a non null value
     * and it is called without any checks.
     *
     * @warning This operator does not take into consideration endianness,
     * padding or alignment. It's very dumb, again use at your own risk.
     *
     * @tparam T Must be a complete type.
     *
     * @param p_stream The stream to write p_item to.
     * @param p_item The thing to write.
     *
     * @return p_stream
     *
     * @section IOStreamSpecializationWriteOperator Specializing the << operator
     * You are expected to specialize this template operator for your own custom
     * types. For example maybe your custom type is an item container and
     * writing each fields' bytes is incorrect, as such you should make a
     * template specialization of this operator for your type.
     *
     * @note Do NOT write text data with this operator, write raw binary data
     * instead. Text should be handled seperalty from binary data. For writing
     * text see //TODO: Link to section about this in ASCII string.
     *
     */
    template<typename T>
    const Stream& operator<<(const Stream& p_stream, const T& p_item)
    {
        p_stream.m_WriteBytesToThing((Byte*)&p_item, sizeof(p_item), p_stream.m_Thing);
        return p_stream;
    }

    /**
     * @brief Reads p_item as raw bytes from p_stream.
     *
     * @details p_item is assumed to be an array of bytes that has sizeof(T)
     * bytes. This byte array is then given to p_stream.m_ReadBytesFromThing.
     * The thing passed to the read function is p_stream.m_ReadBytesFromThing.
     *
     * @warning **THIS OPERATOR IS EXTREMELY LOW LEVEL! USE IT AT YOUR OWN RISK.**
     *
     * @warning p_stream.m_ReadBytesFromThing is assumed to be a non null value
     * and it is called without any checks.
     *
     * @warning This operator does not take into consideration endianness,
     * padding or alignment. It's very dumb, again use at your own risk.
     *
     * @tparam T Must be a complete type.
     *
     * @param p_stream The stream to read a p_item from.
     * @param p_item Where to put the read bytes.
     *
     * @return p_stream
     *
     * @section IOStreamSpecializationReadOperator Specializing the >> operator
     * You are expected to specialize this template operator for your own custom
     * types. For example maybe your custom type is an item container and
     * putting each read byte into the fields of your type is incorrect, as such
     * you should make a template specialization of this operator for your type.
     *
     * @note Do NOT expect to be reading text data with this operator, expect to
     * be reading raw binary data instead. Text is handled seperalty from binary
     * data. For reading text see //TODO: Link to section about this in ASCII string.
     *
     */
    template<typename T>
    const Stream& operator>>(const Stream& p_stream, T& p_item)
    {
        p_stream.m_ReadBytesFromThing((Byte*)&p_item, sizeof(p_item), p_stream.m_Thing);
        return p_stream;
    }


    /**
     * @brief A special infinite read-write stream.
     *
     * @details This stream works by ignoring anything written to it and zeroing
     * out any buffer that is given to it when reading.
     *
     * For example say you want to write an array of 5 bytes to this stream and
     * you call the write function. The write function internally instantly
     * returns the number of bytes without doing anything.
     *
     * For another example let's say you want to read 6 bytes from this stream
     * so you call it's read function. Internally the read function sets each
     * of the buffer's bytes to 0 and returns the number of bytes.
     *
     * This stream is guaranteed to be infinite, see @ref IOStreamInfOrFin for
     * more details.
     *
     * This stream is guaranteed to be read-write, see @ref IOStreamTypes for
     * more details.
     *
     * @warning **DO NOT MUTATE THIS STREAM,** it is not const for nothing >.>.
     *
     * In the case of a null buffer or 0 number of bytes, the number of bytes is
     * returned regardless. In the case of the read function, if the byte buffer
     * is null then the function does not zero out anything and instantly
     * returns the number of bytes.
     *
     * The thing argument is ignored so you may pass anything.
     *
     * @time O(n), for the read function when the byte buffer is a non null
     * value. n here is the number of bytes argument. If the byte buffer is null
     * then O(1).
     *
     */
    extern const Stream g_NullStream;

    /**
     * @brief A special read-only stream that inputs data from the process's
     * standard input.
     *
     * @details Reading is done directly from standard input. For more info on
     * standard input see
     * [this wikipedia article](https://en.wikipedia.org/wiki/Standard_streams)
     *
     * This stream is read-only, for the impications of this see
     * @ref IOStreamTypes.
     *
     * This stream is finite, for the impications of this see
     * @ref IOStreamInfOrFin.
     *
     * The read function of this stream may wait until bytes are available in
     * standard input. The specifics of this are implementation defined.
     *
     * @note Internally, there is no buffering, reading is done directly. You
     * are resposible for buffering any reading done from this stream.
     *
     * @warning DO NOT mutate this stream in any way.
     *
     */
    extern const Stream g_StandardInputStream;
    /**
     * @brief A special write-only stream that outputs data to the process's
     * standard output.
     *
     * @details Writing is done directly to standard output. For more info on
     * standard output see
     * [this wikipedia article](https://en.wikipedia.org/wiki/Standard_streams)
     *
     * This stream is write-only, for the impications of this see
     * @ref IOStreamTypes.
     *
     * This stream is finite, for the impications of this see
     * @ref IOStreamInfOrFin.
     *
     * The write function of this stream may wait until there is empty space
     * available in standard output. The specifics of this are implementation
     * defined.
     *
     * @note Internally, there is no buffering, writing is done directly. You
     * are resposible for buffering any writing done to this stream.
     *
     * @warning DO NOT mutate this stream in any way.
     *
     */
    extern const Stream g_StandardOutputStream;
    /**
     * @brief A special write-only stream that outputs data to the process's
     * standard error.
     *
     * @details Writing is done directly to standard error. For more info on
     * standard error see
     * [this wikipedia article](https://en.wikipedia.org/wiki/Standard_streams)
     *
     * This stream is write-only, for the impications of this see
     * @ref IOStreamTypes.
     *
     * This stream is finite, for the impications of this see
     * @ref IOStreamInfOrFin.
     *
     * The write function of this stream may wait until there is empty space
     * available in standard error. The specifics of this are implementation
     * defined.
     *
     * @note Internally, there is no buffering, writing is done directly. You
     * are resposible for buffering any writing done to this stream.
     *
     * @warning DO NOT mutate this stream in any way.
     *
     */
    extern const Stream g_StandardErrorStream;

}

#endif // !IO__IO_IO_HPP
