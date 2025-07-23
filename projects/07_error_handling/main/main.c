#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "ERROR_HANDLING";

typedef enum {
    ERROR_NONE = 0,
    ERROR_DIVISION_BY_ZERO,
    ERROR_INVALID_INPUT,
    ERROR_OUT_OF_RANGE,
    ERROR_NEGATIVE_VALUE,
    ERROR_OVERFLOW,
    ERROR_UNDERFLOW,
    ERROR_INVALID_EMAIL,
    ERROR_INVALID_PHONE,
    ERROR_INVALID_ID
} error_code_t;

typedef struct {
    double result;
    error_code_t error;
    char message[100];
} calculation_result_t;

// 🎨 ASCII Art
void show_ascii_art(error_code_t error) {
    switch (error) {
        case ERROR_DIVISION_BY_ZERO:
            ESP_LOGI(TAG, "   🍕 ÷ 0 = ❌");
            ESP_LOGI(TAG, "   😱 โอ้ะโอ!");
            break;
        case ERROR_INVALID_INPUT:
            ESP_LOGI(TAG, "   🤔 ข้อมูลไม่ถูกต้อง!");
            break;
        case ERROR_OUT_OF_RANGE:
            ESP_LOGI(TAG, "   😵 ค่าเกินขอบเขต!");
            break;
        case ERROR_NEGATIVE_VALUE:
            ESP_LOGI(TAG, "   ➖ ค่าติดลบไม่เหมาะสม!");
            break;
        case ERROR_OVERFLOW:
            ESP_LOGI(TAG, "   ⬆️ Overflow!");
            break;
        case ERROR_INVALID_EMAIL:
            ESP_LOGI(TAG, "   📧 Email ผิดรูปแบบ!");
            break;
        case ERROR_INVALID_PHONE:
            ESP_LOGI(TAG, "   📱 เบอร์โทรไม่ถูกต้อง!");
            break;
        case ERROR_INVALID_ID:
            ESP_LOGI(TAG, "   🆔 เลขบัตรประชาชนไม่ถูกต้อง!");
            break;
        default:
            ESP_LOGI(TAG, "   ✅ ไม่มีข้อผิดพลาด");
    }
}

// 🔢 แปลงตัวเลข
calculation_result_t validate_number(const char *input) {
    calculation_result_t result = {0};
    char *endptr;
    double value = strtod(input, &endptr);

    if (*endptr != '\0' || isnan(value) || isinf(value)) {
        result.error = ERROR_INVALID_INPUT;
        strcpy(result.message, "❌ ข้อมูลไม่ใช่ตัวเลข");
        return result;
    }

    result.result = value;
    result.error = ERROR_NONE;
    return result;
}

// 🛡️ หารแบบปลอดภัย
calculation_result_t safe_divide(double a, double b) {
    calculation_result_t result = {0};

    if (b == 0.0) {
        result.error = ERROR_DIVISION_BY_ZERO;
        strcpy(result.message, "❌ ไม่สามารถหารด้วยศูนย์ได้!");
        return result;
    }

    result.result = a / b;
    result.error = ERROR_NONE;
    return result;
}

// 💰 ตรวจเงิน
calculation_result_t validate_money(double amount) {
    calculation_result_t result = {0};

    if (amount < 0) {
        result.error = ERROR_NEGATIVE_VALUE;
        strcpy(result.message, "❌ จำนวนเงินติดลบ");
        return result;
    }

    if (amount > 1e12) {
        result.error = ERROR_OUT_OF_RANGE;
        strcpy(result.message, "❌ จำนวนเงินเกินขอบเขต");
        return result;
    }

    result.result = amount;
    result.error = ERROR_NONE;
    return result;
}

// 🏦 ดอกเบี้ย
calculation_result_t calculate_interest(double principal, double rate, int years) {
    calculation_result_t result = {0};

    if (principal <= 0 || years < 0) {
        result.error = ERROR_NEGATIVE_VALUE;
        strcpy(result.message, "❌ เงินต้นหรือระยะเวลาไม่เหมาะสม");
        return result;
    }

    if (rate < -100 || rate > 100) {
        result.error = ERROR_OUT_OF_RANGE;
        strcpy(result.message, "❌ อัตราดอกเบี้ยไม่สมเหตุผล");
        return result;
    }

    double interest = principal * (rate / 100.0) * years;
    double total = principal + interest;

    if (total > 1e308) {
        result.error = ERROR_OVERFLOW;
        strcpy(result.message, "❌ ผลรวมล้น");
        return result;
    }

    result.result = total;
    result.error = ERROR_NONE;
    return result;
}

// 📧 ตรวจ Email
bool is_valid_email(const char *email) {
    const char *at = strchr(email, '@');
    const char *dot = strrchr(email, '.');
    return at && dot && (at < dot);
}

// 📱 ตรวจเบอร์โทร (10 หลักตัวเลข)
bool is_valid_phone(const char *phone) {
    if (strlen(phone) != 10) return false;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) return false;
    }
    return true;
}

// 🆔 ตรวจเลขบัตรประชาชนไทย (13 หลัก + checksum)
bool is_valid_thai_id(const char *id) {
    if (strlen(id) != 13) return false;
    int sum = 0;
    for (int i = 0; i < 12; i++) {
        if (!isdigit(id[i])) return false;
        sum += (id[i] - '0') * (13 - i);
    }
    int checksum = (11 - (sum % 11)) % 10;
    return (id[12] - '0') == checksum;
}

// 🔁 Retry mechanism
calculation_result_t retry_safe_divide(double a, double b, int max_attempts) {
    for (int i = 0; i < max_attempts; i++) {
        calculation_result_t res = safe_divide(a, b);
        if (res.error == ERROR_NONE) return res;
        ESP_LOGW(TAG, "❗ Attempt %d failed: %s", i + 1, res.message);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    calculation_result_t fail = {0};
    fail.error = ERROR_DIVISION_BY_ZERO;
    strcpy(fail.message, "❌ ล้มเหลวหลังจากพยายามหลายครั้ง");
    return fail;
}

// 🌈 main
void app_main(void) {
    ESP_LOGI(TAG, "🚀 เริ่มโปรเจค 7: การจัดการข้อผิดพลาด");

    calculation_result_t r;

    // 🍕 พิซซ่า
    r = retry_safe_divide(12, 0, 3);
    show_ascii_art(r.error);
    ESP_LOGI(TAG, "%s", r.message);

    // 💰 ร้านขายของ
    r = validate_number("ABC");
    show_ascii_art(r.error);
    ESP_LOGI(TAG, "%s", r.message);

    r = validate_money(-50.0);
    show_ascii_art(r.error);
    ESP_LOGI(TAG, "%s", r.message);

    // 🏦 ธนาคาร
    r = validate_money(999999999999.0);
    show_ascii_art(r.error);
    ESP_LOGI(TAG, "%s", r.message);

    r = calculate_interest(100000, -5.0, 5);
    show_ascii_art(r.error);
    ESP_LOGI(TAG, "%s", r.message);

    // ✅ อีเมล
    const char* email = "user@example.com";
    if (is_valid_email(email))
        ESP_LOGI(TAG, "✅ Email ถูกต้อง: %s", email);
    else {
        show_ascii_art(ERROR_INVALID_EMAIL);
        ESP_LOGE(TAG, "❌ Email ไม่ถูกต้อง: %s", email);
    }

    // ✅ เบอร์โทร
    const char* phone = "0812345678";
    if (is_valid_phone(phone))
        ESP_LOGI(TAG, "✅ เบอร์โทรถูกต้อง: %s", phone);
    else {
        show_ascii_art(ERROR_INVALID_PHONE);
        ESP_LOGE(TAG, "❌ เบอร์โทรไม่ถูกต้อง: %s", phone);
    }

    // ✅ เลขบัตรประชาชน
    const char* id = "1101700230675"; // ถูกต้อง
    if (is_valid_thai_id(id))
        ESP_LOGI(TAG, "✅ บัตรประชาชนถูกต้อง: %s", id);
    else {
        show_ascii_art(ERROR_INVALID_ID);
        ESP_LOGE(TAG, "❌ บัตรประชาชนไม่ถูกต้อง: %s", id);
    }

    ESP_LOGI(TAG, "🎉 จบโปรเจค 7!");
}