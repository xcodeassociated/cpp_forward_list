//
//  main.cpp
//  Tests
//
//  Created by Janusz Majchrzak on 08/06/16.
//  Copyright © 2016 Janusz Majchrzak. All rights reserved.
//

#include <iostream>

#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include "ListTest.h"

int main(int argc, const char* argv[]) {
    
    CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
    CppUnit::TextUi::TestRunner runner;
    runner.addTest(suite);
    runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(), std::cerr));
    bool res = runner.run();
    
    return res ? 0 : 1;
}
