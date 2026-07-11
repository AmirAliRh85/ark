#include "../ark.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

struct ark_Log
{
    FILE* output;
    ark_LogLevel minLevel;
    bool showTimestamp;
    bool showLocation;
};

static const char* _levels[] = {
    "TRACE"     ,
    "INFO"      ,
    "WARNING"   ,
    "ERROR"     ,
    "FATAL"
};

ark_Log* ark_Log_create(FILE* output , ark_LogLevel min_log_level , bool show_timestamp , bool show_location)
{
    ark_Log* log = (ark_Log*)malloc(sizeof(ark_Log));
    if (!log)
        return NULL;

    if (!output)
        log->output = stdout;
    else
        log->output = output;
    log->minLevel = min_log_level;
    log->showTimestamp = show_timestamp;
    log->showLocation = show_location;

    
    return log;
}

void ark_Log_log(ark_Log* log , ark_LogLevel level , const char* text , const char* file , const char* function , int line)
{
    if (!log)
    {
        fprintf(stdout , "[%s] %s\n" , _levels[(int)level % 5] , text);
        return;
    }

    if (!(log->output))
        log->output = stdout;

    if (level < log->minLevel)
        return;

    char buff[128];
    char sbuff[128];
    if (log->showTimestamp)
    {
        time_t t = time(NULL);
        struct tm* tm_info = localtime(&t);

        strftime(buff , 128 , "[%Y-%m-%d %H:%M:%S" , tm_info);

        if (log->showLocation)
        {
            sprintf(sbuff , " %s > %s > line %i]" , file , function , line);
            strcat(buff , sbuff);
        }
        else
        {
            strcat(buff , "]");
        }
    }
    else
    {
        if (log->showLocation)
        {
            sprintf(buff , "[%s > %s > line %i]" , file , function , line);
        }
        else
        {
            fprintf(log->output , "[%s] %s\n" , _levels[(int)level % 5] , text);
            return;
        }
    }

    fprintf(log->output , "%s [%s] %s\n" , buff , _levels[(int)level % 5] , text);
}

void ark_Log_destroy(ark_Log* log)
{
    if (!log)
        free(log);
}