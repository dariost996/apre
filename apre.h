#ifndef _APRE_H_
#define _APRE_H_

#if ((!defined __cplusplus) || (__cplusplus<201100L))
#error C++11 is not supported by the compiler
#endif

#if defined _WIN32
#define APRE_OS_WINDOWS
#elif defined __linux__
#define APRE_OS_LINUX
#elif defined __APPLE__
#define APRE_OS_MAC
#else
#define APRE_OS_UNKNOWN
#endif

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <new>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cctype>
#include <random>
#include <cstring>
#include <cstdint>
#include <cstddef>
#include <cmath>
#include <ciso646>
#include <ctime>
#include <set>
#include <queue>
#include <deque>
#include <map>

/*! \mainpage Angel Player Rendering Engine Documentation
 *
 * \section intro_sec APRE
 *
 * Browse "Classes" and "Files" for find the functions and the classes you need!
 */

///ERRORS

void apreDefaultErrFunc(int e, const char* s)
{
    switch(e)
    {
        case 0:
            fprintf(stdout, "Info: %s\n", s);
        break;

        case 1:
            fprintf(stderr, "Warning: %s\n", s);
            exit(EXIT_FAILURE);
        break;

        case 2:
            fprintf(stderr, "Error: %s\n", s);
            exit(EXIT_FAILURE);
        break;
    }
}
void (*apreErrFunc)(int,const char*)=apreDefaultErrFunc;

///GRAPHICS

#include <GL/glew.h>
#include <GL/glu.h>

///SPECIFIC

#include "apre/apre_base.h"
#include "apre/apre_timer.h"
#include "apre/apre_shader.h"

#endif
