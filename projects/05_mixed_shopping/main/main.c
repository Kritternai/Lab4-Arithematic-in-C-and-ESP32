#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "SHOPPING_MATH";

// โครงสร้างข้อมูลสินค้า
typedef struct {
    char name[20];          // ชื่อสินค้า
    int quantity;           // จำนวน
    float price_per_unit;   // ราคาต่อหน่วย
    float total_price;      // ราคารวม
} product_t;

// ฟังก์ชันคำนวณราคาสินค้า
void calculate_product_total(product_t *product) {
    product->total_price = product->quantity * product->price_per_unit;
}

// ฟังก์ชันแสดงรายการสินค้า
void display_product(const product_t *product) {
    ESP_LOGI(TAG, "   %s: %d × %.0f = %.0f บาท", 
             product->name, product->quantity, product->price_per_unit, product->total_price);
}

// ฟังก์ชันคำนวณราคารวมทั้งหมด
float calculate_total_bill(product_t products[], int count) {
    float total = 0.0;
    for (int i = 0; i < count; i++) {
        calculate_product_total(&products[i]);
        total += products[i].total_price;
    }
    return total;
}

// ฟังก์ชันใช้ส่วนลด
float apply_discount(float total, float discount) {
    return total - discount;
}

// ฟังก์ชันแบ่งจ่าย
float split_payment(float amount, int people) {
    if (people <= 0) {
        ESP_LOGE(TAG, "Error: จำนวนคนต้องมากกว่า 0");
        return 0.0;
    }
    return amount / people;
}

void app_main(void)
{
    product_t products[] = {
        {"แอปเปิ้ล", 6, 15.0, 0.0},
        {"กล้วย", 12, 8.0, 0.0},
        {"ส้ม", 8, 12.0, 0.0},
        {"ช็อกโกแลต", 2, 50.0, 0.0} // สินค้าใหม่
    };
    int product_count = sizeof(products) / sizeof(products[0]);
    int people = 3;
    float subtotal = calculate_total_bill(products, product_count);
    float discount = subtotal * 0.10; // ส่วนลด 10%
    float after_discount = apply_discount(subtotal, discount);
    float vat = after_discount * 0.07; // VAT 7%
    float total_with_vat = after_discount + vat;
    float per_person = split_payment(total_with_vat, people);

    ESP_LOGI(TAG, "=== ใบเสร็จซื้อของที่ตลาด ===");
    ESP_LOGI(TAG, "แอปเปิ้ล: %d × %.0f = %.0f บาท", products[0].quantity, products[0].price_per_unit, products[0].total_price);
    ESP_LOGI(TAG, "กล้วย: %d × %.0f = %.0f บาท", products[1].quantity, products[1].price_per_unit, products[1].total_price);
    ESP_LOGI(TAG, "ส้ม: %d × %.0f = %.0f บาท", products[2].quantity, products[2].price_per_unit, products[2].total_price);
    ESP_LOGI(TAG, "ช็อกโกแลต: %d × %.0f = %.0f บาท", products[3].quantity, products[3].price_per_unit, products[3].total_price);
    ESP_LOGI(TAG, "----------------------");
    ESP_LOGI(TAG, "รวม: %.0f บาท", subtotal);
    ESP_LOGI(TAG, "ส่วนลด 10%%: -%.2f บาท", discount);
    ESP_LOGI(TAG, "ยอดหลังหักส่วนลด: %.2f บาท", after_discount);
    ESP_LOGI(TAG, "VAT 7%%: +%.2f บาท", vat);
    ESP_LOGI(TAG, "ยอดสุทธิ: %.2f บาท", total_with_vat);
    ESP_LOGI(TAG, "แบ่งจ่าย %d คน: %.2f บาท/คน", people, per_person);
}
