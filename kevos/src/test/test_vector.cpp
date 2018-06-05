
#include <vector>

#include <arch/common/assert.h>

using namespace std;

class A
{
public:
    A(){}
    A(int __a):a(__a){}
    int a;
};

void test_vector_main()
{
    vector<int> v;
    assert(v.capacity()==0);
    assert(v.size()==0);

    // 11
    v.push_back(11);
    assert(v[0]==11);
    assert(v.at(0)==11);
    assert(v.size()==1);
    assert(v.capacity()==1);
    assert(v.front()==11);
    assert(*v.data()==11);

    // 12 11 13
    v.insert(v.begin(),12);
    v.insert(v.end(),13);
    assert(v[0]==12);
    assert(v[2]==13);
    assert(v.at(0)==12);
    assert(v.at(2)==13);
    assert(v.capacity()==4);
    assert(v.size()==3);

    // 12 14 11 13 5
    v.push_back(5);
    v.insert(v.begin()+1,14);
    assert(v[1]==14);
    assert(v.size()==5);
    assert(v.capacity()==8);
    assert(*v.rbegin()==5);
    assert(v.back()==5);

    v.reserve(50);
    assert(v[0]==12);
    assert(v[1]==14);
    assert(v[2]==11);
    assert(v[3]==13);
    assert(v[4]==5);
    assert(v.size()==5);
    assert(v.capacity()==50);

    vector<int> v2(v.begin(),v.end());
    assert(v2[0]==12);
    assert(v2[1]==14);
    assert(v2[2]==11);
    assert(v2[3]==13);
    assert(v2[4]==5);
    assert(v2.size()==5);
    assert(v2.capacity()==5);

    vector<int> v3=v2;
    assert(v3[0]==12);
    assert(v3[1]==14);
    assert(v3[2]==11);
    assert(v3[3]==13);
    assert(v3[4]==5);
    assert(v3.size()==5);
    assert(v3.capacity()==5);

    v3=v;
    assert(v3[0]==12);
    assert(v3[1]==14);
    assert(v3[2]==11);
    assert(v3[3]==13);
    assert(v3[4]==5);
    assert(v3.size()==5);
    assert(v3.capacity()==5);

    vector<A> v4;
    v4.push_back(A(2));
    assert(v4[0].a==2);

    vector<A> v5(6,A(3));
    assert(v5.size()==6);
    assert(v5.capacity()==6);
    assert(v5[0].a==3);
    assert(v5[5].a==3);

    vector<A> v6(v5.begin()+1,v5.end()-1);
    assert(v6.size()==4);
    assert(v6.capacity()==4);
    assert(v6[0].a==v6[3].a);
    assert(v6[1].a==3);

    v6.reserve(100);
    assert(v6.size()==4);
    assert(v6.capacity()==100);
    assert(v6[0].a==v6[3].a);
    assert(v6[1].a==3);

    v6.shrink_to_fit();
    assert(v6.size()==4);
    assert(v6.capacity()==4);
    assert(v6[3].a==3);

    vector<int> v7{1,2,3,4,5};
    assert(v7[0]==1);
    assert(v7[1]==2);
    assert(v7[2]==3);
    assert(v7[3]==4);
    assert(v7[4]==5);
    assert(v7.capacity()==5);
    assert(v7.size()==5);

    v7.swap(vector<int>{6,7,8});
    assert(v7[0]==6);
    assert(v7[1]==7);
    assert(v7[2]==8);
    assert(v7.size()==3);
    assert(v7.capacity()==3);

    v7.swap(v2);
    assert(v2[0]==6);
    assert(v2[1]==7);
    assert(v2[2]==8);
    assert(v2.size()==3);
    assert(v2.capacity()==3);
    assert(v7[0]==12);
    assert(v7[1]==14);
    assert(v7[2]==11);
    assert(v7[3]==13);
    assert(v7[4]==5);
    assert(v7.size()==5);
    assert(v7.capacity()==5);

    
}

