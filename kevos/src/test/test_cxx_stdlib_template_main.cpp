
#include <type_traits>

#include <arch/common/assert.h>

using namespace std;

void test_cxx_stdlib_template_main()
{
    integral_constant<int,1> one;
    int b=one();
    int c=(int)one;

    is_integral<wchar_t> s;

    is_enum<int>::value;
}
