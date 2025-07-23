#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "COOKIES_MATH";

void app_main(void)
{
    ESP_LOGI(TAG, "=== คุกกี้แบ่งกัน ===");
    int total_cookies = 12;
    int number_of_friends = 4;
    int cookies_per_person = total_cookies / number_of_friends;
    int remaining_cookies = total_cookies % number_of_friends;
    ESP_LOGI(TAG, "คุกกี้ทั้งหมด: %d ชิ้น", total_cookies);
    ESP_LOGI(TAG, "จำนวนเพื่อน: %d คน", number_of_friends);
    ESP_LOGI(TAG, "แต่ละคนได้: %d ÷ %d = %d ชิ้น", total_cookies, number_of_friends, cookies_per_person);
    ESP_LOGI(TAG, "เศษที่เหลือ: %d ชิ้น", remaining_cookies);

    // แบบฝึกหัดที่ 3: หาจำนวนเพื่อนที่เหมาะสม
    int cookies = 30;
    ESP_LOGI(TAG, "\n🔍 คุกกี้ %d ชิ้น หารลงตัวกับ:", cookies);
    for (int people = 1; people <= 10; people++) {
        if (cookies % people == 0) {
            ESP_LOGI(TAG, "   ✅ %d คน → คนละ %d ชิ้น", people, cookies / people);
        }
    }
}
