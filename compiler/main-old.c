/**
    * @author Leviathenn
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>
enum {
    COMPILE_TYPE_MANIFEST,
    COMPILE_TYPE_BUILD
} typedef compileType;

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    compileType type = COMPILE_TYPE_MANIFEST; // default
    // load the .so file
    void *handle = dlopen("./libmodparser.so", RTLD_LOCAL | RTLD_LAZY);
     if (!handle) {
        fputs (dlerror(), stderr);
        exit(1);
    }

    char* (*cosine)();
    char* error;
    cosine = dlsym(handle, "echo");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }
    printf("%s\n", cosine());
    dlclose(handle);
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "--compile-type") == 0) {

            if(i + 1 < argc) {

                if(strcmp(argv[i + 1], "manifest") == 0) {
                    type = COMPILE_TYPE_MANIFEST;
                } else if(strcmp(argv[i + 1], "build") == 0) {
                    type = COMPILE_TYPE_BUILD;
                } else {
                    printf("Invalid compile type!\n");
                }
            } else {
                printf("No argument after the flag!\n");
            }
        }
    }
   
    return 0;
}