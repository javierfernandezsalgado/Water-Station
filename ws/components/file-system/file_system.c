
#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>


#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"


extern void get_index_website(char * index_html)
{
    ESP_LOGI(TAG, "Reading index.html");

    // Open for reading hello.txt
    FILE* f = fopen("/website/index.html", "r");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open index.html");
        return;
    }


    memset(index_html, 0, sizeof(index_html));
    fread(index_html, 1, sizeof(index_html), f);
    fclose(f);

    // Display the read contents from the file
    ESP_LOGI(TAG, "Read from index.html: %s", index_html);

}

extern void file_system_initialization(void)
{
    ESP_LOGI(TAG, "Initializing SPIFFS");

    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/website",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = false
    };

    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        assert(false);
    }

}
