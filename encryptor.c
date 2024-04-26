#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encrypt_dependencies.h"

int main(int argc, char* argv[]) {
    int contained_mode = 0;
    int verbose = 0;
    char* encryption_path = malloc(2 * sizeof(char));

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
        encryption_path = (char*)realloc(encryption_path, strlen(argv[argc-1]) + 1);

        if (encryption_path == NULL)
            return 1;
        
        strcpy(encryption_path, argv[argc-1]);
    }
    else
        encryption_path = "~";

    list_files(encryption_path);

    return 0;
}