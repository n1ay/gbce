#include "test.h"
#include "../src/byte.h"

static void test_low_nibble(void** state) {
    uint8_t input[] = {0x00, 0x01, 0x2f, 0x45, 0xab, 0xff};
    uint8_t expected[] = {0x00, 0x01, 0x0f, 0x05, 0x0b, 0x0f};

    size_t size = sizeof(input)/sizeof(uint8_t);
    for (int i = 0; i < size; i++) {
        assert_true(low_nibble(input[i]) == expected[i]);
    }
}

static void test_high_nibble(void** state) {
    uint8_t input[] = {0x00, 0x01, 0x2f, 0x45, 0xab, 0xff};
    uint8_t expected[] = {0x00, 0x00, 0x20, 0x40, 0xa0, 0xf0};

    size_t size = sizeof(input)/sizeof(uint8_t);
    for (int i = 0; i < size; i++) {
        assert_true(high_nibble(input[i]) == expected[i]);
    }
}

static void test_low_byte(void** state) {
    uint16_t input[] = {0x0000, 0x0157, 0x2fda, 0x45a1, 0x3aab, 0xeeff};
    uint8_t expected[] = {0x00, 0x57, 0xda, 0xa1, 0xab, 0xff};

    size_t size = sizeof(input)/sizeof(uint16_t);
    for (int i = 0; i < size; i++) {
        assert_true(low_byte(input[i]) == expected[i]);
    }
}

static void test_high_byte(void** state) {
    uint16_t input[] = {0x0000, 0x0157, 0x2fda, 0x45a1, 0x3aab, 0xeeff};
    uint8_t expected[] = {0x00, 0x01, 0x2f, 0x45, 0x3a, 0xee};

    size_t size = sizeof(input)/sizeof(uint16_t);
    for (int i = 0; i < size; i++) {
        assert_true(high_byte(input[i]) == expected[i]);
    }
}

static void test_merge_bytes(void** state) {
    uint8_t high_bytes[] = {0x00, 0x01, 0x2f, 0x45, 0xab, 0xef};
    uint8_t low_bytes[] = {0x00, 0x57, 0xda, 0xa1, 0x3a, 0xff};
    uint16_t expected[] = {0x0000, 0x0157, 0x2fda, 0x45a1, 0xab3a, 0xefff};

    size_t size = sizeof(high_bytes)/sizeof(uint8_t);
    for (int i = 0; i < size; i++) {
        assert_true(merge_bytes(high_bytes[i], low_bytes[i]) == expected[i]);
    }
}

static void test_get_bit(void** state) {
    uint8_t bytes[] = {0xdf, 0xe4, 0x2f, 0x45, 0xab, 0xef, 0x45, 0xa1};
    Bit bits[] = {BIT0, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7};
    uint8_t expected[] = {0x01, 0x00, 0x04, 0x00, 0x00, 0x20, 0x40, 0x80};

    size_t size = sizeof(bytes)/sizeof(uint8_t);
    for (int i = 0; i < size; i++) {
        assert_true(get_bit(bytes[i], bits[i]) == expected[i]);
    }
}

static void test_set_bit(void** state) {
    uint8_t bytes[] = {0xdf, 0xe4, 0x2f, 0x45, 0xab, 0xef, 0x45, 0xa1};
    Bit bits[] = {BIT0, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7};
    uint8_t expected[] = {0xdf, 0xe6, 0x2f, 0x4d, 0xbb, 0xef, 0x45, 0xa1};

    size_t size = sizeof(bytes)/sizeof(uint8_t);
    for (int i = 0; i < size; i++) {
        set_bit(&bytes[i], bits[i]);
        assert_true(bytes[i] == expected[i]);
    }
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_low_nibble),
        cmocka_unit_test(test_high_nibble),
        cmocka_unit_test(test_low_byte),
        cmocka_unit_test(test_high_byte),
        cmocka_unit_test(test_merge_bytes),
        cmocka_unit_test(test_get_bit),
        cmocka_unit_test(test_set_bit),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
