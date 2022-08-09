#include "test.h"
#include "../src/cpu.h"

#include <string.h>

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

static void test_set_flag(void** state) {
    Cpu cpu;
    cpu.F = 0x00;
    set_flag(&cpu, FLAG_Z);
    assert_true(cpu.F == 0x80);

    cpu.F = 0x00;
    set_flag(&cpu, FLAG_N);
    assert_true(cpu.F == 0x40);

    cpu.F = 0x00;
    set_flag(&cpu, FLAG_H);
    assert_true(cpu.F == 0x20);

    cpu.F = 0x00;
    set_flag(&cpu, FLAG_C);
    assert_true(cpu.F == 0x10);
}

static void test_unset_flag(void** state) {
    Cpu cpu;
    cpu.F = 0xff;
    unset_flag(&cpu, FLAG_Z);
    assert_true(cpu.F == 0x7f);

    cpu.F = 0xff;
    unset_flag(&cpu, FLAG_N);
    assert_true(cpu.F == 0xbf);

    cpu.F = 0xff;
    unset_flag(&cpu, FLAG_H);
    assert_true(cpu.F == 0xdf);

    cpu.F = 0xff;
    unset_flag(&cpu, FLAG_C);
    assert_true(cpu.F == 0xef);
}

static void test_init_cpu(void** state) {
    Cpu cpu;
    memset(&cpu, 0, sizeof(Cpu));
    init_cpu(&cpu);

    assert_true(cpu.A == 0x01);
    assert_true(cpu.F == 0x00);
    assert_true(cpu.B == 0xff);
    assert_true(cpu.C == 0x13);
    assert_true(cpu.D == 0x00);
    assert_true(cpu.E == 0xc1);
    assert_true(cpu.H == 0x84);
    assert_true(cpu.L == 0x03);
    assert_true(cpu.PC == 0x0100);
    assert_true(cpu.SP == 0x0fffe);
}

static void test_cpu_def(void** state) {
    Cpu cpu;
    memset(&cpu, 0, sizeof(Cpu));
    init_cpu(&cpu);

    assert_true(cpu.AF == 0x0001);
    assert_true(cpu.BC == 0x13ff);
    assert_true(cpu.DE == 0xc100);
    assert_true(cpu.HL == 0x0384);
    assert_true(cpu.PC == 0x0100);
    assert_true(cpu.SP == 0x0fffe);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_get_flag),
        cmocka_unit_test(test_set_flag),
        cmocka_unit_test(test_unset_flag),
        cmocka_unit_test(test_init_cpu),
        cmocka_unit_test(test_cpu_def),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
