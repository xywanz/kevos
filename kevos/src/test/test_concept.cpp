
#include <future/concept.hpp>

#include <arch/common/assert.h>

using namespace std;

template<class T>
concept C
{
    concept_signed_member_method(empty);
    concept_member_method(empty);

    require_member_method(empty);
};


class A
{
public:
    void empty();
    void empty(int,int);
    void empty(int,int,int,int=0);
};

class B
{
public:
    void empty(int b,int c);
};

template<class T>
void test()
{
    T t;
    t.empty();
}


void test_concept_main()
{
    // C<int> c;
    C<B> c;

    // test<int>();
}