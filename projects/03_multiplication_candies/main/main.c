#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "CANDIES_MATH";

void app_main(void)
{
    ESP_LOGI(TAG, "=== ลูกอมในถุง ===");
    int number_of_bags = 5;
    int candies_per_bag = 6;
    int total_candies = number_of_bags * candies_per_bag;
    ESP_LOGI(TAG, "จำนวนถุง: %d ถุง", number_of_bags);
    ESP_LOGI(TAG, "ลูกอมต่อถุง: %d เม็ด", candies_per_bag);
    ESP_LOGI(TAG, "ลูกอมทั้งหมด: %d × %d = %d เม็ด", number_of_bags, candies_per_bag, total_candies);

    ESP_LOGI(TAG, "");
    ESP_LOGI(TAG, "การบวกซ้ำๆ: ");
    char sum_str[100] = "";
    int sum = 0;
    for (int i = 1; i <= number_of_bags; i++) {
        sum += candies_per_bag;
        char buf[16];
        if (i == 1) {
            snprintf(sum_str, sizeof(sum_str), "%d", candies_per_bag);
        } else {
            snprintf(buf, sizeof(buf), " + %d", candies_per_bag);
            strncat(sum_str, buf, sizeof(sum_str) - strlen(sum_str) - 1);
        }
    }
    snprintf(sum_str + strlen(sum_str), sizeof(sum_str) - strlen(sum_str), " = %d", sum);
    ESP_LOGI(TAG, "%s", sum_str);

    // แบบฝึกหัดที่ 4: แจกลูกอมให้เพื่อน
    int friends = 12;
    int candies_per_friend = total_candies / friends;
    int remaining_candies = total_candies % friends;
    ESP_LOGI(TAG, "");
    ESP_LOGI(TAG, "👥 แจกให้เพื่อน %d คน:", friends);
    ESP_LOGI(TAG, "   คนละ %d เม็ด", candies_per_friend);
    ESP_LOGI(TAG, "   เหลือ %d เม็ด", remaining_candies);
}
