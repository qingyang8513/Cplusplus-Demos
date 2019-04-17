#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

enum LogLevel {
    ERROR = 1,
    WARN  = 2,
    INFO  = 3,
    DEBUG = 4
};

void MyLogger(const char *fileName, int line, enum LogLevel level, const char *format, ...) __attribute__((format(printf, 4, 5)));

#ifdef __cplusplus
}
#endif

#endif // LOGGER_H
