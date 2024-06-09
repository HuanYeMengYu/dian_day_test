/**
日志打印示例。
使用：
Log(DEBUG, "This is debug info\n");
结果：
[2018-07-22 23:37:27:172] [DEBUG] [main.cpp:5] This is debug info
默认打印当前时间（精确到毫秒）、文件名称、行号。
*/
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "logger.h"

#ifndef LOGLEVEL
#define LOGLEVEL DEBUG
#endif

// 使用了GNU C扩展语法，只在gcc（C语言）生效，
// g++的c++版本编译不通过
static const char* s_loginfo[] = {
    [ERROR] = "ERROR",
    [WARNING]  = "WARNING",
    [INFO]  = "INFO",
    [DEBUG] = "DEBUG",
    [FATAL] = "FATAL",
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
    millsec = (int)(tv.tv_usec / 1000);

    /* 时间格式：[2011-11-15 12:47:34:888] */
    len = snprintf(buffer, 32, "[%04d-%02d-%02d %02d:%02d:%02d]",
        p->tm_year+1900, p->tm_mon+1,
        p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);

    buffer[len] = '\0';
}

void mylog1(const char* filename, int line, enum LogLevel level, const char* fmt, ...)
{
    if(level > LOGLEVEL)
        return;

    va_list arg_list;
    char buf[1024];
    memset(buf, 0, 1024);
    va_start(arg_list, fmt);
    vsnprintf(buf, 1024, fmt, arg_list);
    char time[32] = {0};

    // 去掉*可能*存在的目录路径，只保留文件名
    const char* tmp = strrchr(filename, '/');
    if (!tmp) tmp = filename;
    else tmp++;
    get_timestamp(time);

    switch(level){
        case DEBUG:
            //绿色
            printf("[%s:%d]-%s-[\033[1;32m%s\033[0m] - %s\n", tmp, line, time, s_loginfo[level], buf);
            break;
        case INFO:
            //蓝色
            printf("[%s:%d]-%s-[\033[1;34m%s\033[0m] - %s\n", tmp, line, time, s_loginfo[level], buf);
            break;
        case ERROR:
            //红色
            printf("[%s:%d]-%s-[\033[1;31m%s\033[0m] - %s\n", tmp, line, time, s_loginfo[level], buf);
            break;
        case WARNING:
            //黄色
            printf("[%s:%d]-%s-[\033[1;33m%s\033[0m] - %s\n", tmp, line, time, s_loginfo[level], buf);
            break;
        case FATAL:
            //红色
            printf("[%s:%d]-%s-[\033[1;31m%s\033[0m] - %s\n", tmp, line, time, s_loginfo[level], buf);
            break;
    }
    va_end(arg_list);
}