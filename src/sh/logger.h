#ifndef LOG_H_
#define LOG_H_

#ifdef __cplusplus 
extern "C" {
#endif

enum LogLevel
{
    ERROR = 1,
    WARNING  = 2,
    INFO  = 3,
    DEBUG = 4,
    FATAL = 5,
};

void mylog1(const char* filename, int line, enum LogLevel level, const char* fmt, ...) __attribute__((format(printf,4,5)));

#define Log(level, format, ...) mylog1(__FILE__, __LINE__, level, format, ## __VA_ARGS__)

#ifdef __cplusplus 
};
#endif

#endif