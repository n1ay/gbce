#include "test.h"
#include "../src/cpu.h"

static void test_get_flag(void** state) {
    Cpu cpu;
    cpu.F = 0x00;
    assert_false(get_flag(cpu, FLAG_Z));
    assert_false(get_flag(cpu, FLAG_N));
    assert_false(get_flag(cpu, FLAG_H));
    assert_false(get_flag(cpu, FLAG_C));

    cpu.F = 0x10;
    assert_false(get_flag(cpu, FLAG_Z));
    assert_false(get_flag(cpu, FLAG_N));
    assert_false(get_flag(cpu, FLAG_H));
    assert_true(get_flag(cpu, FLAG_C));

    cpu.F = 0x20;
    assert_false(get_flag(cpu, FLAG_Z));
    assert_false(get_flag(cpu, FLAG_N));
    assert_true(get_flag(cpu, FLAG_H));
    assert_false(get_flag(cpu, FLAG_C));

    cpu.F = 0x40;
    assert_false(get_flag(cpu, FLAG_Z));
    assert_true(get_flag(cpu, FLAG_N));
    assert_false(get_flag(cpu, FLAG_H));
    assert_false(get_flag(cpu, FLAG_C));

    cpu.F = 0x80;
    assert_true(get_flag(cpu, FLAG_Z));
    assert_false(get_flag(cpu, FLAG_N));
    assert_false(get_flag(cpu, FLAG_H));
    assert_false(get_flag(cpu, FLAG_C));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_get_flag),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
