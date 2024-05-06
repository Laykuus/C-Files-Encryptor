#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int is_file_relevent(char* file_name) {
    char* researched_file_types[] = {".jpg", ".jpeg", ".png", ".docx", ".txt", ".mkv", ".mp3", ".mp4"};
    int nbr_file_types = sizeof(researched_file_types) / sizeof(researched_file_types[0]);
    
    for (int i = strlen(file_name)-1; i > 0; i--)
    {
        char* file_type;

        if (file_name[i] != '.')
            continue;
        file_type = file_name + i;

        for (int j = 0; j < nbr_file_types; j++)
        {
            if (!strcmp(file_type, researched_file_types[j]))
                return 1;   
        }
        break;
    }
    
    return 0;
}