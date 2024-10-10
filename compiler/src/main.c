/**
 * @author Leviathenn
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <yaml.h>
#include "fm.h"

int main(int argc, char *argv[]){

    FILE *file;
    FILE *manifest;
    // check if the file compiler.fcc exists
    FILE *compilerConfig = fopen("compiler.fcc", "r");
    if(compilerConfig == NULL){
        printf("Configuration mode set to \"DEFUALT\".\n");
    
            file = fopen(argv[1], "r");
            if(file == NULL){
                printf("File not found!\n");
                return 1;
            }
            manifest = fopen(argv[2], "r");
            if(manifest == NULL){
                printf("Manifest not found!\n");
                return 1;
            }
    }else{
        yaml_node_t *root = yaml_parse(compilerConfig);
        yaml_node_t *config = yaml_get_child(root, "config");
        yaml_node_t *sourceElement = yaml_get_child(config, 0);
        char *sourcePath = yaml_get_value(sourceElement);
        yaml_node_t *manifestElement = yaml_get_child(config, 1);
        char *manifestPath = yaml_get_value(manifestElement);
        file = fopen(sourcePath, "r");
        if(file == NULL){
            printf("File not found!\n");
            return 1;
        }
        yaml_get_
        manifest = fopen(manifestPath, "r");
        if(manifest == NULL){
            printf("Manifest not found!\n");
            return 1;
        }
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