/*
* FILE			: logger.c
* PROJECT		: SENG1070 Assignment 2
* PROGRAMMER	: Vanesa Robledo
* FIRST VERSION : 2025-02-15
* DESCRIPTION	: This program implements a logging system and test harness for validating the
*				  functionality of a simple C program - basic math operations.
* This file contains the logging functions of the program. Most of this code was taken from the
* IntermediateLogger example from Week 3.
*/

#include "logger.h"
#include "math_library.h"
#include "test_harness.h"

// Create pointer to log file
static FILE* logFile = NULL;

/*
 * FUNCTION     : logMessage
 * DESCRIPTION  : Logs a message with a specific log level and timestamp.
 * PARAMETERS   : const char *level: The level of the log (INFO, WARNING, ERROR).
 *                const char *message: The message to log.
 * RETURNS      : void
 */
void logMessage(const char* level, const char* message) {
    if (logFile == NULL) {
        errno_t err = fopen_s(&logFile, "test.log", "a");
        if (err != 0 || logFile == NULL) {
            perror("Unable to open log file.\n");
            exit(EXIT_FAILURE);
        }
    }

    time_t now = time(NULL);
    struct tm localTime;
    char timestamp[64];

    if (localtime_s(&localTime, &now) != 0) {
        perror("Failed to get local time.\n");
        exit(EXIT_FAILURE);
    }

    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &localTime);

    fprintf(logFile, "[%s] [%s]: %s\n", timestamp, level, message);
}

/*
 * FUNCTION     : closeLogger
 * DESCRIPTION  : Closes the log file if it is open.
 * PARAMETERS   : none
 * RETURNS      : void
 */
void closeLogger() {
    if (logFile != NULL) {
        fclose(logFile);
        logFile = NULL;
    }
}