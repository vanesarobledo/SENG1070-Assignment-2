#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define	TIMESTAMP_SIZE	64
#define	LINE_SIZE	256

// Define log levels
#define LOG_INFO	"INFO"
#define LOG_WARNING	"WARNING"
#define LOG_ERROR	"ERROR"

// Define type of log file
#define	TEST	0
#define	PROGRAM	1

// Function Prototypes - Logging
void logMessage(bool type, const char* level, const char* message);
void closeLogger();

// File I/O
void viewFile(FILE* file, bool type);