
#include <utility>

#include <arch/common/assert.h>

using namespace std;

class AAA
{
public:
    AAA(int m);
    int foo();
};

void test_utility_main()
{
    decltype(declval<AAA>().foo()) n=1;
    assert(n==1);
}