
#include <array>

#include <arch/common/assert.h>

using namespace std;

void test_array_main()
{
    array<int,6> a{0,1,2,3,4,5};
    assert(a[0]==0);
    assert(a[1]==1);
    assert(a[2]==2);
    assert(a[3]==3);
    assert(a[4]==4);
    assert(a[5]==5);
    assert(a.at(0)==0);
    assert(a.at(1)==1);
    assert(a.at(2)==2);
    assert(a.at(3)==3);
    assert(a.at(4)==4);
    assert(a.at(5)==5);
    assert(a.size()==6);
    assert(*a.data()==0);
    assert(a.front()==0);
    assert(a.back()==5);
    assert(*a.begin()==0);
    assert(*a.rbegin()==5);

    a.fill(10);
    assert(a[0]==10);

    const array<int,10> ca={1,2,3,4};
}