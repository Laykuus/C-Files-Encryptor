#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#ifdef __linux__
    char* os = "linux";
#elif _WIN32
    char* os = "win";
#endif

char* append_path(char** list, size_t num_strings, char* string) {
    /*if (strcmp(string, "./") != 0 || strcmp(string, "../") == 0)
        return *list;*/

    list[num_strings] = malloc(strlen(string) + 1);
    strcpy(list[num_strings], string);
    num_strings++;

    list = realloc(list, sizeof(char *) * num_strings);

    if (list == NULL) {
        perror("append realloc");
        return NULL;
    }

    return *list;
}

char** linux_list_files(char* path) {
    size_t num_strings = 0;
    DIR* encrypt_dir = opendir(path);
    char** list_to_encrypt = malloc(sizeof(char *));

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

        //printf("%s\n", file_path);
        
        if (opendir(file_path) != NULL) {
            char** subfolder_files = linux_list_files(file_path);

            if (subfolder_files[0] == NULL) 
                continue;

            for (int i = 0; i < sizeof(subfolder_files) / sizeof(subfolder_files[0]); i++)
            {
                append_path(list_to_encrypt, num_strings, subfolder_files[i]);
                num_strings++;
            }
            

        } else {
            append_path(list_to_encrypt, num_strings, file_path);

            if (list_to_encrypt == NULL) {
                perror("file realloc");
                return NULL;
            }
            num_strings++;
        }
    }

    for (int i = 0; i < num_strings-1; i++)
    {
        printf("%s\n", list_to_encrypt[i]);
    }
    
    return list_to_encrypt;
}

char** list_files(char* path) {
    if (strcmp(os, "linux") == 0)
        return linux_list_files(path);
    
    else if (strcmp(os, "win") == 0)
        return linux_list_files(path);
        //return NULL;
}