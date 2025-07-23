#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "EGGS_MATH";

void app_main(void)
{
    ESP_LOGI(TAG, "=== แอปเปิ้ลในตะกร้า ===");

    int apples_in_basket = 4;
    int apples_added_today = 2;

    ESP_LOGI(TAG, "แอปเปิ้ลในตะกร้าอยู่แล้ว: %d ผล", apples_in_basket);
    ESP_LOGI(TAG, "ใส่เพิ่มวันนี้: %d ผล", apples_added_today);

    int total_apples = apples_in_basket + apples_added_today;

    ESP_LOGI(TAG, "ขั้นตอนการคิด: %d + %d", apples_in_basket, apples_added_today);

    ESP_LOGI(TAG, "แอปเปิ้ลทั้งหมด: %d + %d = %d ผล", apples_in_basket, apples_added_today, total_apples);
}
