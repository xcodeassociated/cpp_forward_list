//
//  ListTest.h
//  
//
//  Created by Janusz Majchrzak on 08/06/16.
//  Copyright © 2016 Janusz Majchrzak. All rights reserved.
//

#ifndef ListTest_h
#define ListTest_h

#include <cppunit/TestSuite.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestCaller.h>
#include <cppunit/extensions/HelperMacros.h>

class ListTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( ListTest );
    
    CPPUNIT_TEST( testConstructor );
    CPPUNIT_TEST( testAssign );
    CPPUNIT_TEST( testPushBack );
    CPPUNIT_TEST( testPushFront );
    CPPUNIT_TEST( testPopBack );
    CPPUNIT_TEST( testPopFront );
    CPPUNIT_TEST( testFront );
    CPPUNIT_TEST( testBack );
    CPPUNIT_TEST( testInsert );
    CPPUNIT_TEST( testSize );
    CPPUNIT_TEST( testMaxSize );
    CPPUNIT_TEST( testEmpty );
    CPPUNIT_TEST( testErase );
    CPPUNIT_TEST( testBegin );
    CPPUNIT_TEST( testEnd );
    CPPUNIT_TEST( testIter );
    CPPUNIT_TEST( testClear );
    CPPUNIT_TEST( testOperators );
    CPPUNIT_TEST( testMove );
    CPPUNIT_TEST( testArrow );
    CPPUNIT_TEST( testSwap );
    CPPUNIT_TEST( testResize );
    CPPUNIT_TEST( testReverse );
    CPPUNIT_TEST( testRemove );
    CPPUNIT_TEST( testSplice );
    CPPUNIT_TEST( testMerge );
    CPPUNIT_TEST( testSort );
//    CPPUNIT_TEST( testUnique );
    
    CPPUNIT_TEST_SUITE_END();
    
public:
    void setUp();
    void tearDown();
    
    void testConstructor();
    void testAssign();
    void testPushBack();
    void testPushFront();
    void testPopBack();
    void testPopFront();
    void testFront();
    void testBack();
    void testInsert();
    void testErase();
    void testSize();
    void testMaxSize();
    void testEmpty();
    void testClear();
    void testOperators();
    void testBegin();
    void testEnd();
    void testIter();
    void testMove();
    void testArrow();
    void testSwap();
    void testResize();
    void testReverse();
    void testRemove();
    void testSplice();
    void testMerge();
    void testSort();
//    void testUnique();
};


#endif /* ListTest_h */
