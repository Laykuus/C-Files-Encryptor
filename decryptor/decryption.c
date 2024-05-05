#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void char_replacment(char* file_name) {
    FILE* pFile;
    char c;
    int file_size;

    // Extracting file's content
    pFile = fopen(file_name, "r");

    if (pFile == NULL) {
        perror("Could not open file");
        exit(1);
    }

    fseek(pFile, 0L, SEEK_END);
    file_size = ftell(pFile);
    rewind(pFile);
    
    char* file_content = malloc(file_size);

    if (file_content == NULL) {
        perror("malloc");
        exit(1);
    }

    fread(file_content, sizeof(char), file_size, pFile);
    fclose(pFile);

    // modifying its content
    for (int i = 0; i < strlen(file_content); i++)
    {
        c = file_content[i] - 100;
        file_content[i] = c;
    }
    
    pFile = fopen(file_name, "w");

    if (pFile == NULL) {
        perror("Could not open file");
        exit(1);
    }

    fwrite(file_content, sizeof(char), file_size, pFile);
}

int decryption(char** files_to_encrypt, int verbose) {

    for (int i = 0; files_to_encrypt[i] != NULL; i++)
    {
        if (verbose)
            printf("Encrypting %s\n", files_to_encrypt[i]);

        char_replacment(files_to_encrypt[i]);
    }
    
    return 0;
}