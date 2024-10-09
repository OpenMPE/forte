/**
 * @author Leviathenn
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int bundle(FILE *script, FILE *manifest){
    FILE *bundle = fopen("bundle.fm", "wb");
    if(bundle == NULL){
        printf("Failed to create bundle.fm\n");
        return 1;
    }
    
    fseek(bundle, 0, SEEK_SET);
    
    fseek(script, 0, SEEK_END);
    int scriptSize = ftell(script);
    
    fseek(manifest, 0, SEEK_END);   
    
    int manifestSize = ftell(manifest);
    fseek(script, 0, SEEK_SET);
    char *scriptContent = malloc(scriptSize + 1);
    fread(scriptContent, scriptSize, 1, script);
    fseek(manifest, 0, SEEK_SET);
    char * manifestContent = malloc(manifestSize + 1);
    fread(manifestContent, manifestSize, 1, manifest);
    char header[2] = {'F','M'};
    int totalSize = scriptSize + manifestSize;

    fwrite(header, 2, 1, bundle);
    fwrite(&totalSize, sizeof(totalSize), 1, bundle);
    fwrite(&scriptSize, sizeof(scriptSize), 1, bundle);
        printf("Script size: %d\n", scriptSize);
    fwrite(scriptContent, scriptSize, 1, bundle);
    fwrite(&manifestSize, 4, 1, bundle);
    fwrite(manifestContent, manifestSize, 1, bundle);
    fclose(bundle);
}
int read(FILE* bundle){
    FILE *script = fopen("script.txt", "wb");
    FILE *manifest = fopen("manifest.txt", "wb");
    if(script == NULL || manifest == NULL){
        printf("Failed to create script.txt or manifest.txt\n");
        return 1;
    }
    int readIndex = 0;
    fseek(bundle, 0, SEEK_SET);
    char header[2];
    fread(header, 2, 1, bundle);
    if(header[0] != 'F' || header[1] != 'M'){
        printf("Invalid header\n");
        printf("Header: %c%c\n", header[0], header[1]);
        return 1;
    }
    readIndex = 2;
    // read at index 3
    int totalSize;
    fread(&totalSize, sizeof(totalSize), 1, bundle);
    readIndex += sizeof(totalSize);
    printf("Total size: %d\n", totalSize);

    int scriptSize;
    fread(&scriptSize, sizeof(scriptSize), 1, bundle);
    readIndex += sizeof(scriptSize);
    printf("Script size: %d\n", scriptSize);
    fseek(bundle, readIndex, SEEK_SET);
    char *scriptContent = malloc(scriptSize + 1);
    memset(scriptContent, 0, scriptSize + 1);
    fread(scriptContent,1, scriptSize, bundle);
    printf("Script content: %s\n", scriptContent);
    fwrite(scriptContent,scriptSize,1, script);

}