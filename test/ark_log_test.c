#include "../ark.h"
#include <time.h>

int main()
{

    // all 4 possibility for logging
    // ark_Log_create(... , ... , true , true);
    // ark_Log_create(... , ... , false , true);
    // ark_Log_create(... , ... , true , false);
    // ark_Log_create(... , ... , false , false);
    ark_Log* log = ark_Log_create(stdout , ARK_INFO , true , true);

    ARK_LOG(log , ARK_ERROR , "An error has occured in this line");
    ARK_LOG(log , ARK_FATAL , "An error has occured in this line");
    ARK_LOG(log , ARK_ERROR , "An error has occured in this line");
    ARK_INFO(log , "This is just for logging");
    ARK_TRACE(log , "this line should not be displayed");

    ark_Log_destroy(log);
    log = NULL;


    log = ark_Log_create(stderr , ARK_WARNING , false , true);
    
    ARK_LOG(log , ARK_ERROR , "An error has occured in this line");
    ARK_LOG(log , ARK_FATAL , "An error has occured in this line");
    ARK_INFO(log , "This is just for logging");
    ARK_ERROR(log , "An error has occured in this line");
    ARK_TRACE(log , "this line should not be displayed");

    ark_Log_destroy(log);


    log = ark_Log_create(stderr , ARK_ERROR , true , false);
    
    ARK_LOG(log , ARK_ERROR , "An error has occured in this line");
    ARK_LOG(log , ARK_FATAL , "An error has occured in this line");
    ARK_INFO(log , "This is just for logging");
    ARK_ERROR(log , "An error has occured in this line");
    ARK_TRACE(log , "this line should not be displayed");

    ark_Log_destroy(log);


    log = ark_Log_create(stderr , ARK_FATAL , false , false);
    
    ARK_LOG(log , ARK_ERROR , "An error has occured in this line");
    ARK_LOG(log , ARK_FATAL , "An error has occured in this line");
    ARK_INFO(log , "This is just for logging");
    ARK_ERROR(log , "An error has occured in this line");
    ARK_TRACE(log , "this line should not be displayed");

    ark_Log_destroy(log);

    // NULL is equal to stdout
    log = ark_Log_create(NULL , ARK_FATAL , false , false);
    
    ARK_LOG(log , ARK_FATAL , "core dumpled");
    ARK_LOG(log , ARK_FATAL , "segmentation error");
    ARK_INFO(log , "This is just for logging");
    ARK_ERROR(log , "An error has occured in this line");
    ARK_TRACE(log , "this line should not be displayed");

    ark_Log_destroy(log);


    // logging in file
    FILE* file = fopen("ark_log_test.txt" , "w");
    log = ark_Log_create(file , ARK_TRACE , true , true);
    
    ARK_LOG(log , ARK_FATAL , "core dumpled");
    ARK_LOG(log , ARK_FATAL , "segmentation error");
    ARK_INFO(log , "This is just for logging");
    ARK_ERROR(log , "An error has occured in this line");
    ARK_TRACE(log , "this line should not be displayed");

    ark_Log_destroy(log);
    fclose(file);

    return 0;
}