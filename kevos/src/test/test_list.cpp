
#include <list>

#include <arch/common/assert.h>

using namespace std;

class Test
{
public:
    int* a;
    Test()
    {
        a=new int;
    }
    ~Test()
    {
        delete a;
    }
};

list<Test> gl(0);

void test_list_main()
{
    list<int> t1;
    t1.push_back(1);
    t1.push_back(2);
    t1.push_back(3);
    t1.push_back(4);
    t1.push_back(5);
    t1.push_back(6);
    auto ti1=t1.begin();
    for(int i=0;i<6;++i)
        assert(*ti1++==i+1);
    gl.empty_initialize();
    gl.push_back(Test());
}
