//
// Created by Mitchell on 8/26/2025.
//

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Loads the config from config.txt file
 */
Config* load_config() {
    Config *config = malloc(sizeof(Config));

    if (config == NULL) {
        return NULL;
    }

    char buffer[64];
    FILE *fptr = fopen("config.txt", "r");
    if (fptr != NULL) {

        int config_count = 0;

        while (fgets(buffer, sizeof(buffer), fptr) != NULL && config_count < 2) {
            char *equal_pos = strchr(buffer, '=');
            if (equal_pos != NULL) {
                char *value = equal_pos + 1;

                value[strcspn(value, "\n")] = '\0';

                if (config_count == 0) {
                    strncpy(config->api_key, value, sizeof(config->api_key) - 1);
                    config->api_key[sizeof(config->api_key) - 1] = '\0';
                }
                else if (config_count == 1) {
                    strncpy(config->base_url, value, sizeof(config->base_url) - 1);
                    config->base_url[sizeof(config->base_url) - 1] = '\0';
                }
                config_count++;

            }

        }
        fclose(fptr);
    }
    else {
        return NULL;
    }

    return config;
}

void free_config(Config* config) {
    free(config);
}