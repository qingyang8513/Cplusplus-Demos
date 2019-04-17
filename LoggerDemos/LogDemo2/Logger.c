#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <memory.h>

#include "Logger.h"

#ifndef LOG_LEVEL
#define LOG_LEVEL DEBUG
#endif

#define LogPrint printf

static const char* s_loginfo[] = {
    [ERROR] = "ERROR",
    [WARN]  = "WARM",
    [INFO]  = "INFOR",
    [DEBUG] = "DEBUG"
};

static const int S_LOGGER_STR_LEN = 1024;

static void get_timestamp(char *buffer)
{
    time_t t;
    struct tm *p;
    struct timeval tv;
    int len;
    int millsec;

    t = time(NULL);
    p = localtime(&t);
    gettimeofday(&tv, NULL);
    millsec = (int) (tv.tv_usec / 1000);

    len = snprintf(buffer, 32, "%04d-%02d-%02d %02d:%02d:%02d:%03d",
                   p->tm_year+1900, p->tm_mon+1, p->tm_mday,
                   p->tm_hour, p->tm_min, p->tm_sec, millsec);

    buffer[len] = '\0';
}

void SimpleLogger(const char *format, ...)
{
    va_list arg_list;
    char buffer[S_LOGGER_STR_LEN];
    memset(buffer, 0, S_LOGGER_STR_LEN);

    va_start(arg_list, format);
    vsnprintf(buffer, S_LOGGER_STR_LEN, format, arg_list);

    LogPrint("%s\n", buffer);
}

void LoggerTag(const char *tag, enum LogLevel level, const char *format, ...)
{
    if (level > LOG_LEVEL) {
        return;
    }

    va_list arg_list;
    char buffer[S_LOGGER_STR_LEN];
    memset(buffer, 0, S_LOGGER_STR_LEN);

    va_start(arg_list, format);
    vsnprintf(buffer, 1024, format, arg_list);

    LogPrint("[%s] [%s] %s\n", s_loginfo[level], tag, buffer);
}

void LoggerTimeTag(const char *tag, enum LogLevel level, const char *format, ...)
{
    if (level > LOG_LEVEL) {
        return;
    }

    va_list arg_list;
    char buffer[S_LOGGER_STR_LEN];
    memset(buffer, 0, S_LOGGER_STR_LEN);

    va_start(arg_list, format);
    vsnprintf(buffer, 1024, format, arg_list);

    char szTime[32] = {0};
    get_timestamp(szTime);

    LogPrint("%s [%s] [%s] %s\n", szTime, s_loginfo[level], tag, buffer);
}

void Logger(const char *tag, int line, enum LogLevel level, const char *format, ...)
{
    if (level > LOG_LEVEL) {
        return;
    }

    va_list arg_list;
    char buffer[S_LOGGER_STR_LEN];
    memset(buffer, 0, S_LOGGER_STR_LEN);

    va_start(arg_list, format);
    vsnprintf(buffer, 1024, format, arg_list);

    char szTime[32] = {0};
    get_timestamp(szTime);

    LogPrint("%s [%s] [%s:%d] %s\n", szTime, s_loginfo[level], tag, line, buffer);
}

void MyLogger(const char *fileName, int line, enum LogLevel level, const char *format, ...)
{
    if (level > LOG_LEVEL) {
        return;
    }

    va_list arg_list;
    char buffer[1024];
    memset(buffer, 0, 1024);

    va_start(arg_list, format);
    vsnprintf(buffer, 1024, format, arg_list);

    char szTime[32] = {0};
    get_timestamp(szTime);

    const char *tmp = strrchr(fileName, '/');
    if (!tmp) {
        tmp = fileName;
    }
    else {
        tmp++;
    }

    LogPrint("%s [%s] [%s:%d] %s\n", szTime, s_loginfo[level], tmp, line, buffer);
}


