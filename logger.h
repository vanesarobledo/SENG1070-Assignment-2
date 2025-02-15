#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define log levels
#define LOG_INFO	"INFO"
#define LOG_WARNING	"WARNING"
#define LOG_ERROR	"ERROR"

// Function Prototypes - Logging
void logMessage(const char* level, const char* message);
void closeLogger();