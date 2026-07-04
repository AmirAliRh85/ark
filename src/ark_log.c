#include "../ark.h"
#include <stdio.h>
#include <stdarg.h>


#define ARK_TRACE(fmt , ...) do { printf("[TRACE] " fmt , __VA_ARGS__); } while(0)
#define ARK_INFO(fmt , ...) do { printf("[INFO] " fmt , __VA_ARGS__); } while(0)
#define ARK_WARNING(fmt , ...) do { printf("[WARNING] " fmt , __VA_ARGS__); } while(0)
#define ARK_ERROR(fmt , ...) do { printf("[ERROR] " fmt , __VA_ARGS__); } while(0)
#define ARK_FATAL(fmt , ...) do { printf("[FATAL] " fmt , __VA_ARGS__); } while(0)

static const char* _levels[] = {
    "TRACE"     ,
    "INFO"      ,
    "WARNING"   ,
    "ERROR"     ,
    "FATAL"
};

void ark_log(ark_LogLevel level , FILE* dest , const char* format , ...)
{
    printf("[%s] " , _levels[(int)level % 5]);

    if (dest == NULL)
        dest = stdout;

    va_list args;
    va_start(args , format);
    vfprintf(dest , format , args);
    va_end(args);
}

/*
ark_Log* ark_Log_create(const char* title , ark_LogLevel min_level , ark_LogLevel max_level , size_t log_size)
{
    ark_Log* log = malloc(sizeof(ark_Log));

    log->title = title;
    log->minLevel = min_level;
    log->maxLevel = max_level;
    log->log = malloc(log_size);

    return log;
}

void ark_Log_add(ark_Log* log , ark_LogLevel level , const char* fmt , ...)
{
    
}

void ark_Log_flush(ark_Log* log , FILE* dest)
{
    fprintf(dest , log->log);
    log->log[0] = '\0';
}

void ark_Log_destroy(ark_Log* log)
{
    free(log->log);
    free(log);
}
*/