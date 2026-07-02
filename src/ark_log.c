#include "../ark.h"
#include <stdio.h>

#define LOG_TITLE_LENGTH    37


#define HRT_TRACE(fmt , ...) do { printf("[TRACE] " fmt , __VA_ARGS__); } while(0)
#define HRT_INFO(fmt , ...) do { printf("[INFO] " fmt , __VA_ARGS__); } while(0)
#define HRT_WARNING(fmt , ...) do { printf("[WARNING] " fmt , __VA_ARGS__); } while(0)
#define HRT_ERROR(fmt , ...) do { printf("[ERROR] " fmt , __VA_ARGS__); } while(0)
#define HRT_FATAL(fmt , ...) do { printf("[FATAL] " fmt , __VA_ARGS__); } while(0)


ark_Log* ark_Log_create(const char* title , ark_LogLevel min_level , ark_LogLevel max_level , int log_size)
{
    ark_Log* log = ark_malloc(sizeof(ark_Log) , title);

    log->title = title;
    log->minLevel = min_level;
    log->maxLevel = max_level;
    log->log = ark_malloc(log_size , "log string");
    // log->currLogIdx = 0;

    return log;
}

void ark_Log_add(ark_Log* log , ark_LogLevel level , const char* text)
{
    
}

void ark_Log_flush(ark_Log* log , FILE* dest)
{

}

void ark_Log_destroy(ark_Log* log)
{
    
}