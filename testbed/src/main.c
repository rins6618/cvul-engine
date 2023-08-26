#include <core/logging.h>
#include <core/asserts.h>

// NOTE: This is just a test of the platform code.
#include <platform/platform.h>

int main(void)
{
    CVUL_FATAL("This is a test fatal error message. It should have a red background and black text. formatted value: %i", 64);
    CVUL_ERROR("This is a test error message. It should have red text. formatted value: %i", 32);
    CVUL_WARN("This is a test warn message. It should have yellow text. formatted value: %i", 16);
    CVUL_INFO("This is a test info message. It should have green text. formatted value: %i", 8);
    CVUL_DEBUG("This is a test debug message. It should have blue text. formatted value: %i", 4);
    CVUL_TRACE("This is a test trace message. It should have grey text. formatted values: integer %i, float %f, hexadecimal value %x (%i)", 2, 1.55555f, 0x40, 0x40);

    platform_state state;
    if (platform_startup(&state, "CVulkan Engine Testbed App", 100, 100, 854, 480))
    {
        while (TRUE)
        {
            platform_pump_messages(&state);
        }
    }
    platform_shutdown(&state);

    return 0;
}