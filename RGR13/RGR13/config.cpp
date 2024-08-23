#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int readConfigFile(char* filename, int key[5], const char* confname) {
    FILE* configFile = fopen(confname, "r");
    if (configFile == NULL) {
        printf("Unable to open configuration file");
        return 0;
    }

    char line[255];
    while (fgets(line, sizeof(line), configFile) != NULL) {
        if (strncmp(line, "DB =", 4) == 0) {
            sscanf(line, "DB = %s", filename);
            // Remove newline character from filename if present
            size_t len = strlen(filename);
            if (len > 0 && filename[len - 1] == '\n') {
                filename[len - 1] = '\0';
            }
        }
        else if (strncmp(line, "KEY =", 5) == 0) {
            sscanf(line, "KEY = %1d%1d%1d%1d%1d", &key[0], &key[1], &key[2], &key[3], &key[4]);
        }
    }

    fclose(configFile);

    return 1;
}

void displayConfigFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open config file for reading");
        exit(EXIT_FAILURE);
    }

    char line[255]; // Buffer to store each line read from the file
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line); // Print each line
    }

    fclose(file); // Close the file after reading
}