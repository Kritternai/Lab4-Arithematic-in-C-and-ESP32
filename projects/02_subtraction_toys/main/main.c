#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "TOYS_MATH";

void app_main(void)
{
    ESP_LOGI(TAG, "=== ของเล่นของน้อง ===");
    int toys_have = 8;
    int toys_give_away = 3;
    int toys_remaining = toys_have - toys_give_away;
    ESP_LOGI(TAG, "น้องมีของเล่นอยู่: %d ชิ้น", toys_have);
    ESP_LOGI(TAG, "แจกให้เพื่อน: %d ชิ้น", toys_give_away);
    ESP_LOGI(TAG, "ของเล่นที่เหลือ: %d - %d = %d ชิ้น", toys_have, toys_give_away, toys_remaining);

    // แบบฝึกหัดที่ 4: แจกของเล่นให้เพื่อน 10 คน คนละ 2 ชิ้น
    int friends = 10;
    int toys_per_friend = 2;
    int total_needed = friends * toys_per_friend;
    ESP_LOGI(TAG, "");
    ESP_LOGI(TAG, "แจกของเล่นให้เพื่อน %d คน คนละ %d ชิ้น ต้องมีของเล่นทั้งหมด: %d ชิ้น", friends, toys_per_friend, total_needed);

    int toys_have2 = 15;
    int shortage = total_needed - toys_have2;
    if (shortage > 0) {
        ESP_LOGI(TAG, "ถ้ามีของเล่น %d ชิ้น จะขาดอีก %d ชิ้น", toys_have2, shortage);
    } else {
        ESP_LOGI(TAG, "ถ้ามีของเล่น %d ชิ้น เพียงพอสำหรับแจกเพื่อนทุกคน", toys_have2);
    }
}
