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


static const char* s_loginfo[] = {
    [ERROR] = "ERROR",
    [WARN]  = "WARM",
    [INFO]  = "INFOR",
    [DEBUG] = "DEBUG"
};

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

    printf("%s [%s] [%s:%d] %s\n", szTime, s_loginfo[level], tmp, line, buffer);
}
