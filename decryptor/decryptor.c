#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "decrypt_dependencies.h"

int main(int argc, char* argv[]) {
    // args handling
    int contained_mode = 0;
    int verbose = 0;
    char* encryption_path = malloc(2 * sizeof(char));

    printf("=== Decryption ===");

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-c") == 0) {
            printf("Contained mode \n");
            contained_mode = 1;
        }

        if (strcmp(argv[i], "-v") == 0) {
            printf("Verbose mode \n");
            verbose = 1;
        }
    }

    printf("\nPress enter to continue...");
    scanf("%*c");

    if (contained_mode == 1) {
        encryption_path = realloc(encryption_path, strlen(argv[argc-1]) + 1);

        if (encryption_path == NULL)
            return 1;
        
        strcpy(encryption_path, argv[argc-1]);
    }
    else
        encryption_path = "~";

    // Decryption process
    char** files = list_files(encryption_path, verbose);
    decryption(files, verbose);

    return 0;
}