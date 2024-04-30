#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#ifdef __linux__
    char* os = "linux";
#elif _WIN32
    char* os = "win";
#endif

char** append_path(char** list, size_t num_strings, char* string) {
    char** pList;

    if (list == NULL)
        pList = malloc(sizeof(char*));
    else
        pList = realloc(list, sizeof(char *) * (num_strings+1));

    if (pList == NULL) {
        perror("malloc / realloc");
        return list;
    }

    list = pList;
    list[num_strings] = malloc(strlen(string) + 1);
    strcpy(list[num_strings], string);

    return list;
}

char** list_files(char* path, int verbose) {
    size_t num_strings = 0;
    DIR* encrypt_dir = opendir(path);
    char** list_to_encrypt = NULL;

    if (encrypt_dir == NULL) {
        perror("Could not open requested directory");
        return NULL;
    }

    struct dirent *entry;

    while ((entry = readdir(encrypt_dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char file_path[1000];
        strcpy(file_path, path);
        strcat(file_path, "/");
        char* ptr = strcat(file_path, entry->d_name);

        if (verbose)
            printf("Found %s\n", file_path);

        if (opendir(file_path) != NULL) {
            char** subfolder_files = list_files(file_path, verbose);

            if (subfolder_files[0] == NULL) 
                continue;

            for (int i = 0; subfolder_files[i] != NULL; i++)
            {
                list_to_encrypt = append_path(list_to_encrypt, num_strings, subfolder_files[i]);
                num_strings++;
            }
        } else {
            list_to_encrypt = append_path(list_to_encrypt, num_strings, file_path);
            num_strings++;

            if (list_to_encrypt == NULL) {
                perror("realloc");
                return NULL;
            }
        }
    }
    
    closedir(encrypt_dir);
    
    char** pList = realloc(list_to_encrypt, sizeof(char *) * (num_strings+1));

    if (pList != NULL) {
        list_to_encrypt = pList;

        list_to_encrypt[num_strings+1] = malloc(sizeof(char*));

        if (list_to_encrypt[num_strings] != NULL)
            list_to_encrypt[num_strings] = NULL;
    } else {
        perror("realloc");
        return NULL;
    }
    
    return list_to_encrypt;
}