//
// Created by Mitchell on 8/26/2025.
//

#ifndef STOCK_PIPELINE_CONFIG_H
#define STOCK_PIPELINE_CONFIG_H

typedef struct {
    char api_key[64];
    char base_url[128];
} Config;

Config* load_config();
void free_config(Config* config);

#endif //STOCK_PIPELINE_CONFIG_H