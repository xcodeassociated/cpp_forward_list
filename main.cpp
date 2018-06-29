//
//  main.cpp
//  Tests
//
//  Created by Janusz Majchrzak on 08/06/16.
//  Copyright © 2016 Janusz Majchrzak. All rights reserved.
//

#include "uj_list.hpp"

int main(int argc, const char* argv[]) {
    uj::list<int> l;
    
    auto init = {1, 2, 3, 4};
    l.assign(init.begin(), init.end());
    
    l.push_back(555);
    l.push_front(5);
    
    l.pop_back();
    l.pop_front();
    
    for(size_t i = 0; i < 8; i++){
        l.insert(l.begin(), i);
    }
    
    auto l2 = l;
    l2.size() == l.size();
    uj::list<int> l3(l2);
    l3.size() == l2.size();
    
    auto l4 = std::move(l3);
    l4.size() == l3.size();
    uj::list<int> l5(std::move(l4));
    
    l.clear();
    
    return 0;
}
