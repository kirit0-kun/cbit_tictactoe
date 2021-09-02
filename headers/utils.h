#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define CHECK(X) ({int __val = (X); \
                    (__val == -1 ? \
                    ({fprintf(stderr, "ERROR (" __FILE__ ":%d) -- %s\n", __LINE__, strerror(errno)); \
                    exit(-1);-1;}) \
                    : __val);})

#define STR(X) #X

#define MAX(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

#define MIN(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define CLAMP(v,a,b) MAX(a, MIN(v, b))

#define IS(L,R) (((L & R) == R) && ((L | R) == R)) 

#endif //UTILS_HEADER