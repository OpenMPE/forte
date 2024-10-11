/**
 * @author Leviathenn
 */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>

class fm{
    private:
        FILE *bundleF;
        FILE *scriptF;
        FILE *manifestF;
    public:
        fm(FILE *script, FILE *manifest, char* bundleName);
        fm(FILE* bundle);
        ~fm();
        int bundle();
        char *script;
        char *manifest;
};

fm::fm(FILE *script, FILE *manifest, char* bundleName){
    this->bundleF = fopen(bundleName, "wb");
    this->scriptF = script;
    this->manifestF = manifest;
    
};
fm::fm(FILE *bundle){
    
    int totalSize;
    int scriptSize;
    int manifestSize;
    int readIndex = 0;
    fseek(bundle, 0, SEEK_SET);
    char header[2];
    fread(header, 2, 1, bundle);
    if(header[0] != 'F' || header[1] != 'M'){
        printf("Invalid header\n");
        return;
    };
    readIndex = 2;
    // read at index 3
    fread(&totalSize, sizeof(totalSize), 1, bundle);
    readIndex += sizeof(totalSize);
    printf("Total size: %d\n", totalSize);
    fread(&scriptSize, sizeof(scriptSize), 1, bundle);
    readIndex += sizeof(scriptSize);
    printf("Script size: %d\n", scriptSize);
    fseek(bundle, readIndex, SEEK_SET);
    char *scriptContent = (char*)malloc(scriptSize + 1);
    memset(scriptContent, 0, scriptSize + 1);
    fread(scriptContent,1, scriptSize, bundle);
    
    for(int i = 0; i < scriptSize; i++){
        scriptContent[i] = scriptContent[i] - 0xAC;
    }
    this->script = scriptContent;
    
    memset(scriptContent, 0, 0);
    fread(&manifestSize, sizeof(manifestSize), 1, bundle);
    readIndex += sizeof(manifestSize);
    printf("Manifest size: %d\n", manifestSize);

    char *manifestContent = (char*)malloc(manifestSize + 1);
    memset(manifestContent, 0, manifestSize + 1);
    fread(manifestContent,1, manifestSize, bundle);
    for(int i = 0; i < manifestSize; i++){
        manifestContent[i] = manifestContent[i] - 0xAC;
    }
    this->manifest = manifestContent;
};

int fm::bundle(){
    FILE *bundle =this->bundleF;
    FILE *script = this->scriptF;
    FILE *manifest = this->manifestF;
    if(bundle == NULL){
        printf("Failed to create bundle.fm\n");
        return 1;
    }
    if(script == NULL){
        printf("Failed to create bundle.fm\n");
        return 1;
    };
    if(manifest == NULL){
        printf("Failed to create bundle.fm\n");
        return 1;
    }
    fseek(bundle, 0, SEEK_SET);
    
    fseek(script, 0, SEEK_END);
    int scriptSize = ftell(script);
    
    fseek(manifest, 0, SEEK_END);   
    
    int manifestSize = ftell(manifest);
    fseek(script, 0, SEEK_SET);
    char *writeContentSC = (char*)malloc(scriptSize + 1);

    char *scriptContent = (char*)malloc(scriptSize + 1);
    fread(scriptContent, scriptSize, 1, script);
    fseek(manifest, 0, SEEK_SET);
    for( int i = 0; i < scriptSize; i++){
        
        writeContentSC[i] = scriptContent[i] + 0xAC;
    }
    char * manifestContent = (char*)malloc(manifestSize + 1);
    fread(manifestContent, manifestSize, 1, manifest);
    char header[2] = {'F','M'};
    int totalSize = scriptSize + manifestSize;
    for (int i = 0; i < manifestSize; i++){
        manifestContent[i] = manifestContent[i] + 0xAC;
    }
    fwrite(header, 2, 1, bundle);
    fwrite(&totalSize, sizeof(totalSize), 1, bundle);
    fwrite(&scriptSize, sizeof(scriptSize), 1, bundle);
        printf("Script size: %d\n", scriptSize);
    fwrite(writeContentSC, scriptSize, 1, bundle);
    fwrite(&manifestSize, 4, 1, bundle);
    fwrite(manifestContent, manifestSize, 1, bundle);
    fclose(bundle);
}
