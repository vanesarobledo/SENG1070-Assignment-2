/*
* FILE			: logger.c
* PROJECT		: SENG1070 Assignment 2
* PROGRAMMER	: Vanesa Robledo
* FIRST VERSION : 2025-02-15
* DESCRIPTION	: This program implements a logging system and test harness for validating the
*				  functionality of a simple C program - basic math operations.
* This file contains the logging functions of the program and file I/O for viewing the log files.
* Most of this code was taken from the IntermediateLogger example from Week 3.
*/

#include "logger.h"
#include "test_harness.h"

// Create pointer to log file
static FILE* logFile = NULL;

/*
 * FUNCTION     : logMessage
 * DESCRIPTION  : Logs a message with a specific log level and timestamp.
 * PARAMETERS   : bool type             : The type
*                 const char *level     : The level of the log (INFO, WARNING, ERROR).
 *                const char *message   : The message to log.
 * RETURNS      : void
 */
void logMessage(bool type, const char* level, const char* message) {
    // Open test.log or program.log
    if (logFile == NULL) {
        if (type == TEST) {
            errno_t err = fopen_s(&logFile, "test.log", "a");
            if (err != 0 || logFile == NULL) {
                perror("Unable to open log file.\n");
                exit(EXIT_FAILURE);
            }
        }
        else {
            errno_t err = fopen_s(&logFile, "program.log", "a");
            if (err != 0 || logFile == NULL) {
                perror("Unable to open log file.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Create timestamp
    time_t now = time(NULL);
    struct tm localTime;
    char timestamp[TIMESTAMP_SIZE];

    if (localtime_s(&localTime, &now) != 0) {
        perror("Failed to get local time.\n");
        exit(EXIT_FAILURE);
    }

    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &localTime);

    // Add log message to file
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
/*
 * FUNCTION     : viewFile
 * DESCRIPTION  : Opens a log file for viewing
 * PARAMETERS   : FILE* file    :   Pointer to file
 *              : bool type     :   
 * RETURNS      : void
 */
void viewFile(FILE* file, bool type) {
    // Clear the screen to view file
    system("clear");

    // Open test.log or program.log by default for reading safely
    errno_t err;
    if (type == TEST) {
        err = fopen_s(&file, "test.log", "r");
        printf("test.log:\n");
    }
    else {
        err = fopen_s(&file, "program.log", "r");
        printf("program.log:\n");
    }
    printf("==================================================================\n");

    // Exit if there is a failure to open file
    if (err != 0) {
        logMessage(PROGRAM, LOG_ERROR, "Error opening file");
        closeLogger();
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read file to screen
    bool eof = false; // Flag for eaching end of file
    char buffer[LINE_SIZE] = ""; // String storing line from file
    char line[LINE_SIZE] = ""; // String storing line after sscanf_s

    while (!eof) {
        // Stop reading file if EOF is reached
        if (feof(file)) {
            eof = true;
        }
        // Stop reading file if some file error occurs
        else if (ferror(file)) {
            printf("Error reading file.\n");
            logMessage(PROGRAM, LOG_ERROR, "Error reading from file");
            closeLogger();
        }
        else
        {
            // Store line in buffer
            fgets(buffer, LINE_SIZE, file);
            // Read line if not empty
            if (sscanf_s(buffer, "%s", &line, (unsigned int)sizeof(line)) > 0) {
                printf("%s", buffer);
            }
        }
    }
    // Close the file safely
    if (fclose(file) != 0) {
        perror("Error closing file.");
        logMessage(PROGRAM, LOG_ERROR, "Error closing file");
        closeLogger();
        exit(EXIT_FAILURE);
    }

    // Prompt for user input to exit viewing file
    printf("==================================================================\n\n");
    printf("End of file. Press any key to continue...");
    getchar();

    // Reset the screen
    system("clear");
    header();
}