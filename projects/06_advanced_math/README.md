#include <stdio.h>
#include <math.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "MATH_ADVANCED";
#define PI 3.14159265359
#define SQUARE_METERS_PER_RAI 1600.0

typedef struct {
    char name[50];
    double length;
    double width;
    double height;
} shape_t;

// ✅ สี่เหลี่ยม
void calculate_rectangle(shape_t shape) {
    double area = shape.length * shape.width;
    double perimeter = 2 * (shape.length + shape.width);
    double rai = area / SQUARE_METERS_PER_RAI;

    ESP_LOGI(TAG, "\n=== %s ===", shape.name);
    ESP_LOGI(TAG, "พื้นที่: %.2f × %.2f = %.2f ตร.ม.", shape.length, shape.width, area);
    ESP_LOGI(TAG, "ปริเมตร: 2×(%.0f+%.0f) = %.2f ม.", shape.length, shape.width, perimeter);
    ESP_LOGI(TAG, "เท่ากับ: %.4f ไร่", rai);
}

// ✅ วงกลม
void calculate_circle(shape_t shape) {
    double r = shape.length;
    double area = PI * r * r;
    double volume = area * shape.height;

    ESP_LOGI(TAG, "\n=== %s ===", shape.name);
    ESP_LOGI(TAG, "พื้นที่ผิวน้ำ: π × %.0f² = %.2f ตร.ม.", r, area);
    ESP_LOGI(TAG, "ปริมาตรน้ำ: π × %.0f² × %.0f = %.2f ลบ.ม.", r, shape.height, volume);
}

// ✅ กล่อง
void calculate_box(shape_t shape) {
    double volume = shape.length * shape.width * shape.height;
    ESP_LOGI(TAG, "\n=== %s ===", shape.name);
    ESP_LOGI(TAG, "ปริมาตรกล่อง: %.0f×%.0f×%.0f = %.2f ลบ.ซม.", shape.length, shape.width, shape.height, volume);
    ESP_LOGI(TAG, "เท่ากับ: %.2f ลิตร", volume / 1000.0);
}

// ✅ สามเหลี่ยม
void calculate_triangle(double base, double height) {
    double area = 0.5 * base * height;
    ESP_LOGI(TAG, "\n=== สามเหลี่ยม ===");
    ESP_LOGI(TAG, "ฐาน: %.2f ม. สูง: %.2f ม.", base, height);
    ESP_LOGI(TAG, "พื้นที่: ½ × %.2f × %.2f = %.2f ตร.ม.", base, height, area);
}

// ✅ ทรงกรวย
void calculate_cone(double radius, double height) {
    double volume = (1.0/3.0) * PI * radius * radius * height;
    ESP_LOGI(TAG, "\n=== ทรงกรวย ===");
    ESP_LOGI(TAG, "รัศมี: %.2f ม. สูง: %.2f ม.", radius, height);
    ESP_LOGI(TAG, "ปริมาตร: (1/3)π × %.0f² × %.0f = %.2f ลบ.ม.", radius, height, volume);
}

// ✅ แปลงหน่วย
void convert_area(double meters) {
    double rai = meters / SQUARE_METERS_PER_RAI;
    ESP_LOGI(TAG, "\n=== การแปลงหน่วย ===");
    ESP_LOGI(TAG, "%.2f ตร.ม. = %.4f ไร่", meters, rai);
}

void app_main(void) {
    ESP_LOGI(TAG, "🚀 เริ่มคำนวณคณิตศาสตร์ขั้นสูง\n");

    // รูปร่างต่างๆ
    shape_t football_field = {"สนามฟุตบอล", 100.0, 60.0, 0.0};
    shape_t swimming_pool = {"สระน้ำกลม", 5.0, 0.0, 2.0};
    shape_t gift_box = {"กล่องของขวัญ", 20.0, 15.0, 10.0};

    calculate_rectangle(football_field);
    vTaskDelay(pdMS_TO_TICKS(1000));

    calculate_circle(swimming_pool);
    vTaskDelay(pdMS_TO_TICKS(1000));

    calculate_box(gift_box);
    vTaskDelay(pdMS_TO_TICKS(1000));

    calculate_triangle(10.0, 8.0);  // ความท้าทาย 1
    vTaskDelay(pdMS_TO_TICKS(1000));

    calculate_cone(3.0, 5.0);       // ความท้าทาย 2
    vTaskDelay(pdMS_TO_TICKS(1000));

    convert_area(6400.0);          // ความท้าทาย 3
    vTaskDelay(pdMS_TO_TICKS(1000));

}