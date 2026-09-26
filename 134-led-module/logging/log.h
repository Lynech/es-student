#pragma once

#include <stdio.h>

#define LOG_LEVEL_ERR 1
#define LOG_LEVEL_INF 2
#define LOG_LEVEL_DBG 3

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_DBG
#endif

void log_version(void);
void log_prefix(const char *level, const char *function, int line);


#define LOG(level, ...)                             \
    do                                              \
    {                                               \
        if (LOG_LEVEL >= level)                     \
        {                                           \
            log_prefix("inf", __func__, __LINE__);  \
            printf(__VA_ARGS__);                    \
        }                                           \
    } while (0)

#define LOG_ERR(...) LOG(LOG_LEVEL_ERR, __VA_ARGS__)  
#define LOG_INF(...) LOG(LOG_LEVEL_INF, __VA_ARGS__)  
#define LOG_DBG(...) LOG(LOG_LEVEL_DBG, __VA_ARGS__)  