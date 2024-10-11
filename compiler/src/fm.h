/**
 * @author Leviathenn
 */

#ifndef FM_H
#define FM_H
#include <stdio.h>
#include <iostream>
class fm{
    public:
        fm(FILE *script, FILE *manifest, char* bundleName);
        fm(FILE* bundle);
        ~fm();
        int bundle();
        char *script;
        char *manifest;
};
#endif
