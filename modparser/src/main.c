/**
 * @author Leviathenn
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "fm.h"

int main(){
    FILE *file = fopen("example.ommf", "r");
    if(file == NULL){
        printf("File not found!\n");
        return 1;
    }
    FILE *manifest = fopen("example.fmmf", "r");
    if(manifest == NULL){
        printf("Manifest not found!\n");
        return 1;
    }
    bundle(file, manifest);
    FILE *bundle = fopen("bundle.fm", "rb");
    if(bundle == NULL){
        printf("Failed to create bundle.fm\n");
        return 1;
    }
    read(bundle);
    fclose(bundle);
    fclose(file);
    fclose(manifest);

};