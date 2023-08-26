#include <core/logging.h>
#include <core/asserts.h>

int main(void)
{
    CVUL_FATAL("testing: %f", 3.14f);
    CVUL_ERROR("testing: %i", 3344);
    CVUL_INFO("testing: %s", "Just a string value!");

    CVUL_ASSERT(1 == 0);

    return 0;
}