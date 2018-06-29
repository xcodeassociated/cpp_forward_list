//
//  ListTest.cpp
//  
//
//  Created by Janusz Majchrzak on 08/06/16.
//  Copyright © 2016 Janusz Majchrzak. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>

#include "ListTest.h"

#include "uj_list.hpp"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ListTest );

struct TestClass{
    int testInt = 0;
    
    int getTestInt() const{
        return this->testInt;
    }
    
    TestClass() {
        ;
    }
    
    TestClass(const TestClass& t):testInt(t.testInt){
        ;
    }
    
    TestClass(int testInt): testInt(testInt){
        ;
    }
    
    ~TestClass(){
        ;
    }
};

void ListTest::setUp() {
    ;
}

void ListTest::tearDown() {
    ;
}

void ListTest::testConstructor() {
    uj::list<int> l;
    
    CPPUNIT_ASSERT(l.size() == 0);
    CPPUNIT_ASSERT(l.begin() == l.end());
    
    auto init = {1, 2, 3, 4};
    uj::list<int> l2(init.begin(),init.end());
    
    CPPUNIT_ASSERT(l2.front() == 1);
    CPPUNIT_ASSERT(l2.back() == 4);
    CPPUNIT_ASSERT(l2.size() == 4);
    CPPUNIT_ASSERT(l2.begin() != l2.end());
    
    uj::list<int> l3(std::move(l2));
    
    CPPUNIT_ASSERT(l3.front() == 1);
    CPPUNIT_ASSERT(l3.back() == 4);
    CPPUNIT_ASSERT(l3.size() == 4);
    CPPUNIT_ASSERT(*(l3.begin()) == 1);
    
    uj::list<int> l4(5u, 5);
    
    CPPUNIT_ASSERT(l4.size() == 5);
    CPPUNIT_ASSERT(l4.front() == 5);
    CPPUNIT_ASSERT(l4.back() == 5);
}

void ListTest::testAssign(){
    uj::list<int> l;
    
    CPPUNIT_ASSERT(l.size() == 0);
    CPPUNIT_ASSERT(l.begin() == l.end());
    
    auto init = {1, 2, 3, 4};
    l.assign(init.begin(), init.end());
    
    CPPUNIT_ASSERT(l.front() == 1);
    CPPUNIT_ASSERT(l.back() == 4);
    CPPUNIT_ASSERT(l.size() == 4);
    
    l.assign(10u, 555);
    
    CPPUNIT_ASSERT(l.front() == 555);
    CPPUNIT_ASSERT(l.back() == 555);
    CPPUNIT_ASSERT(l.size() == 10);
}

void ListTest::testPushBack(){
    uj::list<int> l;
    
    l.push_back(5);

    CPPUNIT_ASSERT(l.front() == 5);
    CPPUNIT_ASSERT(l.back() == 5);
    CPPUNIT_ASSERT(l.size() == 1);
    
    l.push_back(555);
    
    CPPUNIT_ASSERT(l.front() == 5);
    CPPUNIT_ASSERT(l.back() == 555);
    CPPUNIT_ASSERT(l.size() == 2);
}

void ListTest::testPushFront() {
    uj::list<int> l;
    
    l.push_front(5);
    
    CPPUNIT_ASSERT(l.front() == 5);
    CPPUNIT_ASSERT(l.back() == 5);
    CPPUNIT_ASSERT(l.size() == 1);
    
    l.push_front(555);
    
    CPPUNIT_ASSERT(l.front() == 555);
    CPPUNIT_ASSERT(l.back() == 5);
    CPPUNIT_ASSERT(l.size() == 2);
}

void ListTest::testPopBack(){
    uj::list<int> l;
    
    for(size_t i = 0; i < 8; i++){
        l.insert(l.begin(),i);
    }
    l.pop_back();
    
    CPPUNIT_ASSERT(l.front() == 7);
    CPPUNIT_ASSERT(l.back() == 1);
    CPPUNIT_ASSERT(l.size() == 7);
}

void ListTest::testPopFront(){
    uj::list<int> l;
    
    for(size_t i = 0; i < 8; i++){
        l.insert(l.begin(), i);
    }
    
    l.pop_front();
    
    CPPUNIT_ASSERT(l.front() == 6);
    CPPUNIT_ASSERT(l.back() == 0);
    CPPUNIT_ASSERT(l.size() == 7);
}

void ListTest::testFront(){
    uj::list<int> l;
    
    for(size_t i = 0; i < 8; i++){
        l.insert(l.begin(), i);
    }
    
    CPPUNIT_ASSERT(l.front() == 7);
}

void ListTest::testBack(){
    uj::list<int> l;
    
    for(size_t i = 0; i < 8; i++){
        l.insert(l.begin(), i);
    }
    
    CPPUNIT_ASSERT(l.back() == 0);
}

void ListTest::testInsert(){
    uj::list<int> l;
    
    CPPUNIT_ASSERT(l.begin() == l.end());
    l.insert(l.begin(), 100);
    l.insert(l.end(), 200);
    l.insert(l.end(), 300);
    l.insert(l.end(), l.back() + 100);
    
    CPPUNIT_ASSERT(l.back() == 400);
    CPPUNIT_ASSERT(l.size() == 4);
    CPPUNIT_ASSERT(l.front() == 100);
    
    l.insert(++l.begin(), 150);
    
    CPPUNIT_ASSERT(*l.begin() == 100);
    CPPUNIT_ASSERT(*(++l.begin()) == 150);
    
    l.erase(l.begin() + 1);
    
    CPPUNIT_ASSERT(*(++l.begin()) == 200);
    
    l.erase(l.begin() + 1);
    
    CPPUNIT_ASSERT(*(++l.begin()) == 300);
    CPPUNIT_ASSERT(l.back() == 400);
    
    auto beg = l.begin();
    std::advance(beg,(l.size() - 1));
    l.erase(beg);
    
    CPPUNIT_ASSERT(l.back() == 300);
    
    l.clear();
    
    CPPUNIT_ASSERT(l.size() == 0);
    
    l.insert(l.begin(), 5u,5);
    
    CPPUNIT_ASSERT(l.front() == 5);
    CPPUNIT_ASSERT(l.back() == l.front());
    
    l.clear();
    auto init = { 5,6,7,8,9,10 };
    l.insert(l.begin(), init.begin(),init.end());
    
    CPPUNIT_ASSERT(l.size() == 6);
    CPPUNIT_ASSERT(l.front() == 5);
    CPPUNIT_ASSERT(l.back() == 10);
}

void ListTest::testErase(){
    uj::list<int> l;
    
    l.push_back(10);
    l.push_back(20);
    
    CPPUNIT_ASSERT(l.back() == 20 && l.size() == 2);
    
    l.erase(l.begin());
    
    CPPUNIT_ASSERT(l.back() == l.front() && l.size() == 1);
    
    l.push_front(10);
    
    CPPUNIT_ASSERT(l.front() == 10 && l.size() == 2 && l.back() == 20);
    
    l.push_front(5);
    
    CPPUNIT_ASSERT(l.front() == 5 && l.back() == 20 && l.size() == 3);
    
    l.push_back(30);
    
    CPPUNIT_ASSERT(l.front() == 5 && l.back() == 30 && l.size() == 4);
    
    auto beg = l.begin();
    std::advance(beg, (l.size() - 1));
    l.erase(beg);
    
    CPPUNIT_ASSERT(l.back() == 20 && l.size() == 3 && l.front() == 5);
    
    l.erase(l.begin(), l.end());
    
    CPPUNIT_ASSERT(l.empty());
}

void ListTest::testBegin(){
    uj::list<int> l;
    
    l.push_back(10);
    l.push_back(20);
    const uj::list<int> l2(l);
    
    CPPUNIT_ASSERT(*(l.begin()) == 10);
    
    l.pop_back();
    
    CPPUNIT_ASSERT(*(l.begin()) == 10);
    
    l.push_back(20);
    l.pop_front();
    
    CPPUNIT_ASSERT(*(l.begin()) == 20);
    CPPUNIT_ASSERT(*(l2.begin()) == 10);
}

void ListTest::testEnd(){
    uj::list<int> l;
    
    l.push_back(10);
    l.push_back(20);
    const uj::list<int> l2(l);
    
    int iterations = 0;
    for(auto iter = l.begin(); iter != l.end(); ++iter, ++iterations){
        ;
    }
    
    CPPUNIT_ASSERT(iterations==2);
    
    iterations = 0;
    for(auto iter = l2.begin(); iter != l2.end(); ++iter, ++iterations){
        ;
    }
    
    CPPUNIT_ASSERT(iterations == 2);
}

void ListTest::testIter() {
    uj::list<TestClass> l;
    
    l.push_back(TestClass(5));
    l.push_back(TestClass(7));
    l.push_back(TestClass(9));
    
    auto it = l.begin();
    ++it;
    
    CPPUNIT_ASSERT(it->testInt == 7);
    CPPUNIT_ASSERT(it->getTestInt() == 7);
    CPPUNIT_ASSERT(it->testInt == it->getTestInt());
    
}

void ListTest::testSize(){
    uj::list<int> l;
    
    CPPUNIT_ASSERT(l.size() == 0);
    l.push_back(10);
    CPPUNIT_ASSERT(l.size() == 1);
    l.push_back(20);
    CPPUNIT_ASSERT(l.size() == 2);
    l.push_back(30);
    CPPUNIT_ASSERT(l.size() == 3);
    l.pop_back();
    CPPUNIT_ASSERT(l.size() == 2);
    l.pop_back();
    CPPUNIT_ASSERT(l.size() == 1);
    l.pop_back();
    CPPUNIT_ASSERT(l.size() == 0 && l.empty() == true);
    l.push_back(10);
    CPPUNIT_ASSERT(l.size() == 1);
    l.push_back(20);
    CPPUNIT_ASSERT(l.size() == 2);
    l.push_back(30);
    CPPUNIT_ASSERT(l.size() == 3);
    
    l.pop_front();
    l.pop_front();
    l.pop_front();
    
    CPPUNIT_ASSERT(l.size() == 0 && l.empty() == true);
}

void ListTest::testMaxSize() {
    uj::list<int> l;
    
    CPPUNIT_ASSERT(l.max_size() == std::numeric_limits<uj::list<int>::size_type>::max());
}

void ListTest::testEmpty(){
    uj::list<int> l;
    
    CPPUNIT_ASSERT_EQUAL(l.empty(), true);
    
    l.push_back(10);
    CPPUNIT_ASSERT_EQUAL(l.empty(), false);
    l.pop_front();
    CPPUNIT_ASSERT_EQUAL(l.empty(), true);
    l.push_back(20);
    CPPUNIT_ASSERT_EQUAL(l.empty(), false);
    l.pop_back();
    CPPUNIT_ASSERT_EQUAL(l.empty(), true);
}

void ListTest::testClear(){
    uj::list<int> l;
    
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.clear();
    
    CPPUNIT_ASSERT(l.size() == 0 && l.empty());
    
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    CPPUNIT_ASSERT(l.size() == 3);
    CPPUNIT_ASSERT(l.front() == 1);
    CPPUNIT_ASSERT(l.back() == 3);
    
    l.clear();
    
    CPPUNIT_ASSERT(l.size() == 0);
    CPPUNIT_ASSERT(l.begin() == l.end());
}

void ListTest::testOperators(){
    uj::list<int> l, l2;
    
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_back(40);
    l2.push_back(1);
    l2.push_front(0);
    l2.push_back(2);
    
    CPPUNIT_ASSERT(l2.front() == 0);
    CPPUNIT_ASSERT(l2.back() == 2);
    
    l2 = l;
    
    CPPUNIT_ASSERT(l.size() == l2.size());
    CPPUNIT_ASSERT(l.back() == l2.back());
    CPPUNIT_ASSERT(l.front() == l2.front());
    
    auto b1 = l.begin();
    auto b2 = l2.begin();
    
    CPPUNIT_ASSERT(*(b1) == *(b2));
    CPPUNIT_ASSERT(*(++b1) == *(++b2));
    CPPUNIT_ASSERT(*(++b1) == *(++b2));
    CPPUNIT_ASSERT(*(++b1) == *(++b2));
    CPPUNIT_ASSERT(*(b1) == l.back() && *(b2) == l2.back());
}

void ListTest::testMove(){
    uj::list<int> l, l2;
    
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    l.push_back(40);
    l2.push_back(1);
    l2.push_front(0);
    l2.push_back(2);
    
    CPPUNIT_ASSERT(l2.front() == 0);
    CPPUNIT_ASSERT(l2.back() == 2);
    
    l2 = std::move(l);
    
    CPPUNIT_ASSERT(l2.front() != 1);
    CPPUNIT_ASSERT(l2.front() == 10);
    CPPUNIT_ASSERT(l2.back() == 40);
    
    auto b = l2.begin();
    
    CPPUNIT_ASSERT(*b++ == 10);
    CPPUNIT_ASSERT(*(b++) == 20);
    CPPUNIT_ASSERT(*(b++) == 30);
    CPPUNIT_ASSERT(*(b) == 40);
    
}

void ListTest::testArrow(){
    uj::list<int> l;
    
    l.push_front(3);
    l.push_front(2);
    l.push_front(1);
    
    CPPUNIT_ASSERT(l.front() == 1);
    CPPUNIT_ASSERT(l.back() == 3);
    CPPUNIT_ASSERT(l.size() == 3);
    
    int* fptr = (l.begin().operator->());
    
    CPPUNIT_ASSERT(*fptr == 1);
    
    *fptr = 100;
    
    CPPUNIT_ASSERT(l.front() == 100);
}

void ListTest::testSwap() {
    uj::list<int> l;
    
    l.push_front(3);
    l.push_front(2);
    l.push_front(1);
    
    uj::list<int> l2;
    
    l2.swap(l);
    
    CPPUNIT_ASSERT(l2.front() == 1);
    CPPUNIT_ASSERT(l2.back() == 3);
    CPPUNIT_ASSERT(l2.size() == 3);
    CPPUNIT_ASSERT( l.size() == 0);
}

void ListTest::testResize() {
    uj::list<int> l;
    
    l.push_front(3);
    l.push_front(2);
    l.push_front(1);
    l.resize(5, 4);
    
    CPPUNIT_ASSERT(l.front() == 1);
    CPPUNIT_ASSERT(l.back() == 4);
    CPPUNIT_ASSERT(l.size() == 5);
    
    l.resize(2);
    
    CPPUNIT_ASSERT(l.front() == 1);
    CPPUNIT_ASSERT(l.back() == 2);
    CPPUNIT_ASSERT(l.size() == 2);
}

void ListTest::testReverse() {
    uj::list<int> l;
    
    l.push_front(3);
    l.push_front(2);
    l.push_front(1);
    l.reverse();
    
    CPPUNIT_ASSERT(l.front() == 3);
    CPPUNIT_ASSERT(l.back() == 1);
    CPPUNIT_ASSERT(l.size() == 3);
}

void ListTest::testRemove() {
    auto init = {1,2,1,2};
    uj::list<int> l(init.begin(),init.end());
    l.remove(2);
    
    CPPUNIT_ASSERT(l.front() == 1);
    CPPUNIT_ASSERT(l.back() == 1);
    CPPUNIT_ASSERT(l.size() == 2);
    
    init = {1,2,3,4,5,6,7,8,9,0};
    l.assign(init.begin(), init.end());
    
    l.remove_if([](int i)->bool {
        return i < 5; });
    
    init = {5,6,7,8,9};
    
    CPPUNIT_ASSERT(std::equal(init.begin(),init.end(),l.begin()));
}

void ListTest::testSplice() {
    auto init = {1,2,3,4,5,6,7,8,9,0};
    uj::list<int> l(init.begin(), init.end());
    l.splice(l.begin(), l, std::find(l.begin(), l.end(), 0));
    init = {0,1,2,3,4,5,6,7,8,9};
    
    CPPUNIT_ASSERT(std::equal(init.begin(), init.end(), l.begin()));
    
    init = {0,1,2,3,4,5,6,7,8,9};
    uj::list<int> l2(init.begin(), init.end());
    l.splice(l.end(), l2);
    init = {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9};
    
    CPPUNIT_ASSERT(std::equal(init.begin(), init.end(), l.begin()));
    
    uj::list<int> l3;
    l.splice(l3.end(), l);
    init = {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9};
    
    CPPUNIT_ASSERT(std::equal(init.begin(), init.end(), l.begin()));
}

void ListTest::testMerge() {
    auto init = {1,3,5,7,9};
    uj::list<int> l(init.begin(), init.end());
    init = {0,2,4,6,8,};
    uj::list<int> l2(init.begin(), init.end());
    init = {0,1,2,3,4,5,6,7,8,9};
    l.merge(l2);
    
    CPPUNIT_ASSERT(std::equal(init.begin(), init.end(), l.begin()));
    
    init = {8,6,4,2,0};
    l.assign(init.begin(), init.end());
    init = {9,7,5,3,1};
    l2.assign(init.begin(), init.end());
    init = {9,8,7,6,5,4,3,2,1};
    l.merge(l2,std::greater<int>());
    
    CPPUNIT_ASSERT(std::equal(init.begin(), init.end(), l.begin()));
}

void ListTest::testSort() {
    auto init = {5,78,2,8,2,7,54,341,6423,14,64243,4,54235};
    uj::list<int> l(init.begin(), init.end());
    l.sort();
    
    CPPUNIT_ASSERT(std::is_sorted(l.begin(),l.end()));
    
    l.sort(std::greater<int>());
    
    CPPUNIT_ASSERT(std::is_sorted(l.begin(), l.end(), std::greater<int>()));
}

//void ListTest::testUnique() {
//    uj::list<int> l(15u,1);
//    
//    l.insert(l.end(), 15u, 2);
//    l.unique();
//    
//    CPPUNIT_ASSERT(l.front() == 1);
//    CPPUNIT_ASSERT(l.back() == 2);
//    CPPUNIT_ASSERT(l.size() == 2);
//    
//    auto init = {1,3,4,5,7,8};
//    l.assign(init.begin(),init.end());
//    l.unique([](int a, int b)->bool {return a % 2 && b % 2; });
//    init = {1,4,5,8};
//    
//    CPPUNIT_ASSERT(std::equal(init.begin(), init.end(), l.begin()));
//}
