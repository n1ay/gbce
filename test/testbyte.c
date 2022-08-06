#include "test.h"
#include "../src/byte.h"

static void test_low_nibble(void** state) {
    uint8_t input[] = {0x00, 0x01, 0x2f, 0x45, 0xab, 0xff};
    uint8_t expected[] = {0x00, 0x01, 0x0f, 0x05, 0x0b, 0x0f};

    size_t size = sizeof(input);

    for(int i = 0; i < size; i++) {
        assert_true(low_nibble(input[i]) == expected[i]);
    }
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_low_nibble),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
