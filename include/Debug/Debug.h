//small library of debugging functions
#ifndef DEBUG_H
#define DEBUG_H
#include <iostream>
#include <stdio.h>

//#define DEBUG_MSG //are we printing debug messages?
//#define DEBUG_LOG //should we log the debug?
#define DEBUG_LOG_FILE fopen("dLog.txt","a")

#ifdef DEBUG_LOG
#define fprintd(stream, ...) fprintf(stream, __VA_ARGS__)
#else
#define fprintd(stream, ...)
#endif

#ifdef DEBUG_MSG
#define printd(...) printf(__VA_ARGS__); fprintd(DEBUG_LOG_FILE, __VA_ARGS__) //regular print statement
#define printv(X) std::cout << #X " = " << X << std::endl //print the value of a variable
#else
#define printd(...)
#define printv(X)
#endif


#endif
