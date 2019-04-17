#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

/// Log output level. There are 4 levels.
enum LogLevel {
    ERROR = 1,
    WARN  = 2,
    INFO  = 3,
    DEBUG = 4
};

/// Simple logger.
void SimpleLogger(const char *format, ...);

/// Logout with a tag.
void LoggerTag(const char *tag, enum LogLevel level, const char *format, ...);

/// Logout with a timestamp and a tag.
void LoggerTimeTag(const char *tag, enum LogLevel level, const char *format, ...);

/// Logout with a timestamp, tag and line number.
void Logger(const char *tag, int line, enum LogLevel level, const char *format, ...);

/// Logout for test.
void MyLogger(const char *fileName, int line, enum LogLevel level, const char *format, ...) __attribute__((format(printf, 4, 5)));


#ifdef __cplusplus
}
#endif

#endif // LOGGER_H
