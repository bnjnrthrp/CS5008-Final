/**
 * A quick and dirty logging utility that only prints to stdout.
 *
 * More advanced ones changes the log to vary
 * which print stream it uses, and allows logging
 * to files. Logging is very common for long running applications
 * and is a good way to debug and see what is going on. However,
 * the log files can be very large, so more advanced logging
 * will often clear the log file after a certain size, or
 * only keep the last X number of lines.
 *
 * One can then grep (search) the logging file to find certain
 * messages.
 *
 * @author Albert Lionelle
 *
 * Written for CS 5008 @ Northeastern University
 *
 *
 */

#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>

#define LOG_LEVEL __shared__log_level
#define LOG_LEVEL_ERROR 3 // mainly want error messages to always show
#define LOG_LEVEL_WARN 2  // sometimes want warning messages to show in addition to errors
#define LOG_LEVEL_INFO 1  // info is pretty common, also called verbose.
#define LOG_LEVEL_DEBUG 0 // the most detailed, only for debugging, shows everything

int LOG_LEVEL = LOG_LEVEL_ERROR;

#define LOG(level, str, ...)     \
    if (level >= LOG_LEVEL)      \
    {                            \
        printf(str __VA_ARGS__); \
    }
#define LOG_ERROR(...) LOG(LOG_LEVEL_WARN, "(ERROR): ", __VA_ARGS__)
#define LOG_WARN(...) LOG(LOG_LEVEL_WARN, "(WARNING): ", __VA_ARGS__)
#define LOG_DEBUG(...) LOG(LOG_LEVEL_DEBUG, "(DEBUG): ", __VA_ARGS__)
#define LOG_INFO(...) LOG(LOG_LEVEL_INFO, "(INFO): ", __VA_ARGS__)

#endif // LOGGING_H