/**
 * @ingroup DebuggingMod
 *
 * @file Log.cpp
 * @brief Implements the logging system for the @ref DebuggingMod module.
 *
 * @details Everything in this file is only implemented if the DEBUG macro is
 * defined, otherwise this file does not implement anthing.
 * 
 */
#include "Log.hpp"

#include<stdio.h>

#ifdef DEBUG
namespace Debugging
{

    struct Log
    {
        FILE* m_File;

        Log(FILE* p_file):
        m_File(p_file)
        { }

        operator FILE*() const
        {
            return m_File;
        }
    };

    static bool g_CanLog = true;
    static Log g_STDError = stderr;

    const Log& operator<<(const Log& p_log, const char& p_char)
    {

        if(p_log != nullptr && g_CanLog)
        {
            fputc(p_char, p_log);
        }

        return p_log;

    }
    const Log& operator<<(const Log& p_log, const unsigned char& p_char)
    {

        if(p_log != nullptr && g_CanLog)
        {
            fputc(p_char, p_log);
        }

        return p_log;

    }
    const Log& operator<<(const Log& p_log, const short& p_short)
    {

        if(p_log != nullptr && g_CanLog)
        {
            fprintf(p_log, "%d", p_short);
        }

        return p_log;

    }
    const Log& operator<<(const Log& p_log, const unsigned short& p_short)
    {

        if(p_log != nullptr && g_CanLog)
        {
            fprintf(p_log, "%u", p_short);
        }

        return p_log;

    }
    const Log& operator<<(const Log& p_log, const int& p_int)
    {

        if(p_log != nullptr && g_CanLog)
        {
            fprintf(p_log, "%d", p_int);
        }

        return p_log;

    }
    const Log& operator<<(const Log& p_log, const unsigned int& p_int)
    {

        if(p_log != nullptr && g_CanLog)
        {
            fprintf(p_log, "%u", p_int);
        }

        return p_log;

    }
    const Log& operator<<(const Log& p_log, const long& p_long)
    {

        if(p_log != nullptr && g_CanLog)
        {
            fprintf(p_log, "%ld", p_long);
        }

        return p_log;

    }
    const Log& operator<<(const Log& p_log, const unsigned long& p_long)
    {

        if(p_log != nullptr && g_CanLog)
        {
            fprintf(p_log, "%lu", p_long);
        }

        return p_log;

    }
    const Log& operator<<(const Log& p_log, const float& p_float)
    {

        if(p_log != nullptr && g_CanLog)
        {
            fprintf(p_log, "%f", p_float);
        }

        return p_log;

    }
    const Log& operator<<(const Log& p_log, const double& p_double)
    {

        if(p_log != nullptr && g_CanLog)
        {
            fprintf(p_log, "%lf", p_double);
        }

        return p_log;

    }
    const Log& operator<<(const Log& p_log, const long double& p_double)
    {

        if(p_log != nullptr && g_CanLog)
        {
            fprintf(p_log, "%Lf", p_double);
        }

        return p_log;

    }
    const Log& operator<<(const Log& p_log, const bool& p_bool)
    {

        if(p_log != nullptr && g_CanLog)
        {
            if(p_bool)
            {
                fputc('1', p_log);
            }
            else
        {
            fputc('0', p_log);
        }
        }

        return p_log;

    }
    const Log& operator<<(const Log& p_log, const char* const p_string)
    {

        if(p_log != nullptr && g_CanLog)
        {
            fputs(p_string, p_log);
        }

        return p_log;

    }
    const Log& operator<<(const Log& p_log, const void* const p_pointer)
    {

        if(p_log != nullptr && g_CanLog)
        {
            fprintf(p_log, "%p", p_pointer);
        }

        return p_log;

    }


    Log& LogLineAndFile(const unsigned long& p_line, const char* p_file)
    {

        g_STDError << '[' << p_file << ':' << p_line << "]:\n\t";

        return g_STDError;

    }

    void LoggingOff()
    {
        g_CanLog = false;
    }
    void LoggingOn()
    {
        g_CanLog = true;
    }


}
#endif
