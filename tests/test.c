#include "../inc/test.h"

Test(test_1, create)
{
	cr_expect(my_add(1, 2) == 3, "my_add should return 3");
}
