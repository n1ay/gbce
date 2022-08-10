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


static void test_unset_bit(void** state) {
    uint8_t bytes[] = {0xdf, 0xe6, 0x2f, 0x4d, 0xbb, 0xef, 0x45, 0xa1};
    Bit bits[] = {BIT0, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7};
    uint8_t expected[] = {0xde, 0xe4, 0x2b, 0x45, 0xab, 0xcf, 0x05, 0x21};

    size_t size = sizeof(bytes)/sizeof(uint8_t);
    for (int i = 0; i < size; i++) {
        unset_bit(&bytes[i], bits[i]);
        assert_true(bytes[i] == expected[i]);
    }
}

static void test_ptr_offset(void** state) {
    uint16_t greater_ptrs[] = {0x0001, 0xabcd, 0x1111, 0xa000};
    uint16_t lesser_ptrs[] = {0x0001, 0x0abc, 0x0101, 0x9999};
    uint16_t expected[] = {0x0000, 0xa111, 0x1010, 0x0667};

    size_t size = sizeof(greater_ptrs)/sizeof(uint16_t);
    for (int i = 0; i < size; i++) {
        assert_true(ptr_offset(greater_ptrs[i], lesser_ptrs[i]) == expected[i]);
    }
}

static void test_ptr_in(void** state) {
    uint16_t ptrs[] = {0x0001, 0x0001, 0x0001, 0xaaaa, 0xaaaa, 0xaaaa};
    uint16_t high_addrs[] = {0x0001, 0x0001, 0xa000, 0xbbbb, 0x9999, 0xeeee};
    uint16_t low_addrs[] = {0x0001, 0x0000, 0x0001, 0x9999, 0x8888, 0xdddd};
    uint8_t expected[] = {1, 1, 1, 1, 0, 0};

    size_t size = sizeof(ptrs)/sizeof(uint16_t);
    for (int i = 0; i < size; i++) {
        assert_true(ptr_in(ptrs[i], low_addrs[i], high_addrs[i]) == expected[i]);
    }
}

static void test_get_bit_number(void** state) {
    Bit bits[] = {BIT0, BIT1, BIT2, BIT3, BIT4, BIT5, BIT6, BIT7, BIT8, BIT9, BIT10, BIT11, BIT12, BIT13, BIT14, BIT15};
    uint8_t expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    size_t size = sizeof(bits)/sizeof(Bit);
    for (int i = 0; i < size; i++) {
        assert_true(get_bit_number(bits[i]) == expected[i]);
    }
}


static void test_get_8b_half_carry_bit(void** state) {
    uint8_t values1[] = {0xaa, 0xa2, 0xaa, 0xa2};
    uint8_t values2[] = {0xbb, 0xbb, 0xb4, 0xb4};
    uint8_t expected[] = {1, 0, 0, 0};

    size_t size = sizeof(values1)/sizeof(uint8_t);
    for (int i = 0; i < size; i++) {
        assert_true(get_8b_half_carry_bit(values1[i], values2[i]) == expected[i]);
    }
}

static void test_get_8b_carry_bit(void** state) {
    uint8_t values1[] = {0xaa, 0x2a, 0xaa, 0x2a};
    uint8_t values2[] = {0xbb, 0xbb, 0x4b, 0x4b};
    uint8_t expected[] = {1, 0, 0, 0};

    size_t size = sizeof(values1)/sizeof(uint8_t);
    for (int i = 0; i < size; i++) {
        assert_true(get_8b_carry_bit(values1[i], values2[i]) == expected[i]);
    }
}

static void test_get_16b_half_carry_bit(void** state) {
    uint16_t values1[] = {0xaa00, 0xa200, 0xaa00, 0xa200};
    uint16_t values2[] = {0xbb00, 0xbb00, 0xb400, 0xb400};
    uint8_t expected[] = {1, 0, 0, 0};

    size_t size = sizeof(values1)/sizeof(uint16_t);
    for (int i = 0; i < size; i++) {
        assert_true(get_16b_half_carry_bit(values1[i], values2[i]) == expected[i]);
    }
}

static void test_get_16b_carry_bit(void** state) {
    uint16_t values1[] = {0xaa00, 0x2a00, 0xaa00, 0x2a00};
    uint16_t values2[] = {0xbb00, 0xbb00, 0x4b00, 0x4b00};
    uint8_t expected[] = {1, 0, 0, 0};

    size_t size = sizeof(values1)/sizeof(uint16_t);
    for (int i = 0; i < size; i++) {
        assert_true(get_16b_carry_bit(values1[i], values2[i]) == expected[i]);
    }
}

static void test_get_8b_half_borrow_bit(void** state) {
    uint8_t minuends[] = {0xaa, 0xcc, 0xaa, 0x2a};
    uint8_t subtrahends[] = {0xbb, 0xbb, 0x44, 0x4a};
    uint8_t expected[] = {1, 0, 0, 0};

    size_t size = sizeof(minuends)/sizeof(uint8_t);
    for (int i = 0; i < size; i++) {
        assert_true(get_8b_half_borrow_bit(minuends[i], subtrahends[i]) == expected[i]);
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
        cmocka_unit_test(test_unset_bit),
        cmocka_unit_test(test_ptr_offset),
        cmocka_unit_test(test_ptr_in),
        cmocka_unit_test(test_get_bit_number),
        cmocka_unit_test(test_get_8b_half_carry_bit),
        cmocka_unit_test(test_get_8b_carry_bit),
        cmocka_unit_test(test_get_16b_half_carry_bit),
        cmocka_unit_test(test_get_16b_carry_bit),
        cmocka_unit_test(test_get_8b_half_borrow_bit),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
