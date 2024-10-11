/**
 * @author Leviathenn
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
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
        std::ifstream manifestStream("compiler.fcc");
        YAML::Node manifestNode = YAML::LoadFile("compiler.fcc");
        if(manifestNode["config"].IsDefined()){
            std::vector<std::string> config = manifestNode["config"].as<std::vector<std::string>>();
            file = fopen(config[0].c_str(), "r");
            if(file == NULL){
                printf("File not found!\n");
                return 1;
            }
            manifest = fopen(config[1].c_str(), "r");
            if(manifest == NULL){
                printf("Manifest not found!\n");
           
            }

        }else{
            std::cout << "Config Not Defined!\n";
            
        };
    }


    FILE *bundle = fopen("bundle.fm", "rb");
    if(bundle == NULL){
        printf("Failed to create bundle.fm\n");
        return 1;
    }
    fm *fmFile = new fm(file, manifest, "bundle.fm");
    fmFile->bundle();
    free(fmFile);
    fm *newFile = new fm(bundle);
    
    fclose(bundle);
    fclose(file);
    fclose(manifest);

};