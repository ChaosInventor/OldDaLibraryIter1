/**
 * @file Log.hpp
 * @brief Declares the members of the logging system from the @ref DebuggingMod
 * module
 *
 * @details Everything in this file is only declared if the DEBUG macro is
 * defined. If this macro is not defined this file dose not declare the logging
 * system and the logging macro is replaced with dead code that dose not do
 * anything. For more details see @ref LoggingLogDebugLineToggling.
 *
 * @ingroup DebuggingMod
 *
 */
#ifndef LOGGING__DEBUGGING_LOGGING_LOG_HPP
#define LOGGING__DEBUGGING_LOGGING_LOG_HPP

/** @def LogDebugLine(...)
 *
 * @brief Logs the given arguments to stderr only when the macro DEBUG is
 * defined.
 * @details
 * Arguments given to this function macro are logged by streaming them into a
 * Log& using the << operator. This means that what ever you are trying to log
 * should support being stream into a @ref Log. The inital Log& is gotten by
 * calling the @ref LogLineAndFile function. The line argument supplied to the
 * function is the expansion of __LINE__ and the file argument is the expansion
 * of __FILE__.
 *
 * @note Always put a ; after using this function macro.
 *
 * 
 * @section LoggingToggle Toggling logging
 * Logging can be toggled in 2 ways:
 * - During compile time.
 * - During runtime.
 * 
 * @subsection LoggingToggleCompile Toggling during comple time
 * Logging only occurs when the macro DEBUG is defined.
 *
 * If the DEBUG macro is defined then this macro expands into a series of
 * function calls that do the logging.
 *
 * If the DEBUG macro is not defined then this macro expands into while(0).
 * 
 * @subsection LoggingToggleRuntimeToggling during runtime
 * Logging can also be toggled during runtime. This is done using the
 * @ref LoggingOn and @ref LoggingOff functions. You can call LoggingOn to
 * enable logging at any time and call LoggingOff to disable logging at any time.
 * 
 * By default logging is enabled.
 * 
 * The function LoggingOn won't have an effect if logging is already on and
 * similarly the function LoggingOff won't have an effect if logging is already
 * off.
 * 
 * @warning If the macro DEBUG is not defined then these functions also won't be
 * defined, you won't be able compile your code and you won't be able to switch
 * logging on or off, it will be completely disabled. Only use these functions
 * in a contex where you can be sure that DEBUG will be defined.
 * 
 * 
 * @section LoggingLogDebugLineFormat Format
 * The format in which the messages given to this macro are logged is the
 * following:\n
 * [<FILE_NAME>:<LINE_NUMBER>]:\\n\\t <YOUR ARGUMENTS>\\n
 *
 * @section LoggingLogDebugLineExamples Examples
 * The following examples all show how to log the execution of some imaginary
 * functions:
 *
 * - An add function
 * This function has the following function signature:
 * @code{.cpp}
 * int Add(int, int);
 * @endcode
 * As you might be able to suspect, this function adds it's 2 arguments and
 * returns the result(wow shocker!).
 *
 * This is it's implementation:
 * @code{.cpp}
 * int Add(int x, int y)
 * {
 *      return x + y;
 * }
 * @endcode
 * Ok now, let's say that you want to log what calculation this function
 * preforms when ever it is called. You can use this exact function macro to
 * achieve that!
 *
 * Here is the modified version that logs just that:
 * @code{.cpp}
 * //Assume the file this function is defined in is called Adder.cpp
 *
 * int Add(int x, int y) //Assume this is line 251
 * { //Assume this is line 252
 *      LogDebugLine("OwO adding " << x << " with " << y << " UwU."); //Assume this is line 253
 *      return x + y; //Assume this is line 254
 * } //Assume this is line 255
 * @endcode
 * This modified version will now log what numbers are being added.
 *
 * @note Comments were added to better explain the possible output
 *
 * Ok now let's call the new Add function and see what it will log. For this
 * example assume that we give 42 as the first argument, x, and 24 as the second
 * argument, y.
 *
 * Depending on whether or not the macro DEBUG is defined you can expect the
 * add function to behave in the following ways:
 * - If the DEBUG macro is defined, the function will give an output to stderr
 * similar to this:\n
 * @code
 * [Added.cpp:253]:\n\tOwO adding 42 with 24 UwU.\n
 * @endcode
 *
 * - If the DEBUG macro is not defined, the function will NOT give any output to
 * stderr. Instead the logging macro will expand into a while(0) statement(
 * without the ; ) that will then (hopefully) be optimized away by your compiler.
 *
 */


#ifdef DEBUG

namespace Debugging
{

    /**
     * @brief This is an incomplete type that can be used to write log messages.
     *
     * @details This type is one of the core members of the logging system. It
     * works by having different things streamed to it using the << operator.
     * There are << operators defined for all primitive types as well as for c
     * strings. In order to do logging check @ref LogDebugLine, the rest of this
     * documentation will explain the different concepts behind this system and
     * why certant things are done. There will also be an example on how to
     * define a overload of the << operator to allow custom types to be logged.
     * 
     * @note This is NOT a complete logging system, it's only purpose is to be
     * used for trace level logging. See the documentation bellow for more info.
     * 
     * @section LoggingPurpose Purpose
     * The purpose of the logging system is to allow to log every single step
     * a pice of code takes during it's execution. Everything from with what
     * paramaters it was given to what it is doing currently. This is done in
     * order to aid the debugging proces by skipping the need to go into a
     * debugger and step through code, instead the generated log can be
     * examined to find out exactly what happend.
     * 
     * From this you can come to the conclusion that this system is only useful
     * for debugging and testing. So in order to allow for it's use to be
     * toggled the DEBUG macro is used. If this macro is defined then the
     * logging system will be declared and things will be logged. If this macro
     * is not defined then all of the logging macros will be replaced with dead
     * code and the logging system will not be declared. This allows you to
     * freely write debugging code without having to worry about it having an
     * impact or effect during non debug builds.
     *
     * @section LoggingInterfaceWhy Why the current interface
     * The current interfac for logging is made this way to be disconnected from
     * how logging is done and where the output is sent. Also when the interface
     * is this abstract is makes it easier to turn off during comple time.
     * 
     * The << operator is used to allow for a simple way to log non text. It
     * also allows to define how to log things that are custom types.
     * 
     * @section LoggingLogCustoms Logging custom types
     * This section covers the concept of logging custom types.
     * 
     * @subsection LoggingLogCustomsWhy Why would you want to be able to log
     * custom types in a Log object
     * The primary reason is ease of use, instead of logging each part of your
     * custom type separately you should be able to log the entire thing in one
     * use of the << operator.
     * 
     * @subsection  LoggingLogCustomsBasics Basics
     * In it's core the job of making a custom type loggable is to define a
     * overload of the << operator that takes in a log and your custom type.
     * The form of the overload is always going to be this:
     * @code{.cpp}
     * #ifdef DEBUG
     * const Log& operator<<(const Log& p_log, const YOUR_TYPE& p_type)
     * {
     * 
     *      //Log the type...
     * 
     *      return p_log;
     * 
     * }
     * #endif //DEBUG
     * @endcode
     * Here YOUR_TYPE is your custom type. The comment in the middle should be
     * replaced with the logging for your type.
     * @note Make sure to **ALWAYS** wrap your << operator in a #ifdef DEBUG
     * since the log is struct is not declared if DEBUG is not defined. 
     * 
     * @subsection LoggingLogCustomsExample Example
     * In this example we will make the type Foo logable.
     * This is foo:
     * @code{.cpp}
     * struct Foo
     * {
     *      int m_Number;
     *      void* m_Pointer;
     * };
     * @endcode
     * Now we define the overloaded operator (make sure it's wrapped in a #ifdef!)
     * @code
     * const Log& operator<<(const Log& p_log, const Foo& p_foo)
     * {
     * 
     *      p_log << "Foo.m_Number = " << p_foo.m_Number;
     *      p_log << "Foo.m_Pointer = " << p_foo.m_Pointer;
     *      p_log << "Foo.m_Pointer + Foo.m_Number = " << p_foo.m_Pointer + p_foo.m_Number;
     * 
     *      return p_log;
     * 
     * }
     * #endif //DEBUG
     * @endcode
     * Now you can freely log any foo you have using the @ref LogDebugLine macro.
     * 
     * @subsection LoggingLogCustomsDoAndNot Do's and don'ts
     * Here is a list of things to do and not to do in your << operators for
     * logging:
     * - Only log the minimum amount of information. Don't log too much stuff,
     * it will make the logs harder to read.
     * - Don't log newlines unless they make the log easier to read.
     * - NEVER log that your are logging, this can potentially lead to functions
     * being called recursively forever until a stack overflow or it will
     * produce unreadable logs. An example of this would be doing something like:
     * @code{.cpp}
     * LogDebugLine("Logging Foo at " << &p_foo);
     * //Rest of log << operator
     * @endcode
     * - Always wrap your << operator in a #ifdef DEBUG.
     * - Always return the same Log& that was given to you.
     * 
     * 
     * @section LoggingLogImplementation Current implementation
     * You can find the implementation source at @ref Log.cpp, tho here we'll
     * take a quick overview of how it works.
     * 
     * @warning **DO NOT** rely on the fact that these implementation details
     * will stay the same throughout different versions. They may change at
     * anytime.
     * 
     * Log carries a FILE* in it.
     * 
     * Each << operator calls some of the stdio functions that write things to
     * FILE*s, mainly things like fputc fprintf and others. However before they
     * call any of these functions they check if the FILE* in log is null and if
     * a global bool is true. This global bool is set using the @ref LoggingOn
     * and @ref LoggingOff functions.
     * 
     * A global Log is kept that has stderr as it's FILE*, this exact log is
     * returned by the @ref LogLineAndFile function. The LogLineAndFile function
     * is then called by @ref LogDebugLine to get the initial Log&. This way
     * everything is logged to stderr.
     * 
     */
    struct Log;

    /**
     * @brief Logs p_char to p_log.
     *
     * @details For more details check @ref Log
     *
     * @return p_log.
     * 
     */
    const Log& operator<<(const Log& p_log, const char& p_char);
    /**
     * @brief Logs p_char to p_log
     *
     * @copydetails operator<<(const Log& p_log, const char& p_char)
     *
     */
    const Log& operator<<(const Log& p_log, const unsigned char& p_char);
    /**
     * @brief Logs p_short to p_log.
     *
     * @copydetails operator<<(const Log& p_log, const char& p_char)
     *
     */
    const Log& operator<<(const Log& p_log, const short& p_short);
    /**
     * @brief Logs p_short to p_log.
     *
     * @copydetails operator<<(const Log& p_log, const char& p_char)
     *
     */
    const Log& operator<<(const Log& p_log, const unsigned short& p_short);
    /**
     * @brief Logs p_int to p_log.
     *
     * @copydetails operator<<(const Log& p_log, const char& p_char)
     *
     */
    const Log& operator<<(const Log& p_log, const int& p_int);
    /**
     * @brief Logs p_int to p_log.
     *
     * @copydetails operator<<(const Log& p_log, const char& p_char)
     *
     */
    const Log& operator<<(const Log& p_log, const unsigned int& p_int);
    /**
     * @brief Logs p_long to p_log.
     *
     * @copydetails operator<<(const Log& p_log, const char& p_char)
     *
     */
    const Log& operator<<(const Log& p_log, const long& p_long);
    /**
     * @brief Logs p_long to p_log.
     *
     * @copydetails operator<<(const Log& p_log, const char& p_char)
     *
     */
    const Log& operator<<(const Log& p_log, const unsigned long& p_long);
    /**
     * @brief Logs p_float to p_log.
     *
     * @copydetails operator<<(const Log& p_log, const char& p_char)
     *
     */
    const Log& operator<<(const Log& p_log, const float& p_float);
    /**
     * @brief Logs p_double to p_log.
     *
     * @copydetails operator<<(const Log& p_log, const char& p_char)
     *
     */
    const Log& operator<<(const Log& p_log, const double& p_double);
    /**
     * @brief Logs p_double to p_log.
     *
     * @copydetails operator<<(const Log& p_log, const char& p_char)
     *
     */
    const Log& operator<<(const Log& p_log, const long double& p_double);
    /**
     * @brief Logs p_bool to p_log
     *
     * @copydetails operator<<(const Log& p_log, const char& p_char)
     *
     */
    const Log& operator<<(const Log& p_log, const bool& p_bool);
    /**
     * @brief p_string is assumed to be a c string and each of it's characters
     * is logged to p_log, up to the null character. The null character is not
     * outputted.
     *
     * @copydetails operator<<(const Log& p_log, const char& p_char)
     *
     */
    const Log& operator<<(const Log& p_log, const char* const p_string);
    /**
     * @brief Logs p_pointer to p_log. The value of the pointer it's self is
     * logged, not what it points to.
     *
     * @copydetails operator<<(const Log& p_log, const char& p_char)
     *
     */
    const Log& operator<<(const Log& p_log, const void* const p_pointer);


    /**
     * @brief Logs the start of a log message to stderr.
     *
     * @details This function is used to log the start of a log message as well
     * as to get a reference to the default log.
     *
     * You do not want to use this function to do your logging. See the @ref
     * LogDebugLine macro.
     *
     * @section LoggingFormat Format
     * The start of the message has the following format:
     * [<p_file>:<p_line>]:\\n\\t.
     *
     * @param p_line The line from where the log message is being written.
     * @param p_file The file from where the log message is being written.
     * @warning This pointer is assumed to be a c string.
     *
     */
    Log& LogLineAndFile(const unsigned long& p_line, const char* p_file);

    /**
     * @brief Turns logging off.
     *
     * @details For more details see @ref LoggingToggle
     *
     */
    void LoggingOff();
    /**
     * @brief Turns logging on.
     *
     * @details For more details see @ref LoggingToggle
     *
     */
    void LoggingOn();


}


#define LogDebugLine(...) Debugging::LogLineAndFile(__LINE__, __FILE__) << __VA_ARGS__ << '\n';

#else

#define LogDebugLine(...) while(0)

#endif //DEBUG

#endif // !LOGGING__DEBUGGING_LOGGING_LOG_HPP
