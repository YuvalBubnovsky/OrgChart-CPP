#include "doctest.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "sources/OrgChart.hpp"
using namespace std;
using namespace ariel;

TEST_CASE("String Input"){
    OrgChart organization;
    organization.add_root("CEO")
            .add_sub("CEO", "CTO")         // Now the CTO is subordinate to the CEO
            .add_sub("CEO", "CFO")         // Now the CFO is subordinate to the CEO
            .add_sub("CEO", "COO")         // Now the COO is subordinate to the CEO
            .add_sub("CTO", "VP_SW") // Now the VP Software is subordinate to the CTO
            .add_sub("COO", "VP_BI");      // Now the VP_BI is subordinate to the COO

    /* 
    Tree looks like this:
    
    CEO
       |--------|--------|
       CTO      CFO      COO
       |                 |
       VP_SW             VP_BI
    */

    auto it1 = organization.begin_level_order();
    auto it2 = organization.begin_reverse_order();
    auto it3 = organization.begin_preorder();

    vector<string> expected_level = {"CEO", "CTO", "CFO", "COO", "VP_SW", "VP_BI"};
    vector<string> expected_reverse = {"VP_SW", "VP_BI", "CTO", "CFO", "COO", "CEO"};
    vector<string> expected_preorder = {"CEO", "CTO", "VP_SW", "CFO", "COO", "VP_BI"};

    for (size_t i = 0; i < expected_level.size(); i++) {
        CHECK((*it1) == expected_level.at(i));
        CHECK((*it2) == expected_reverse.at(i));
        CHECK((*it3) == expected_preorder.at(i));
        it1++;
        it2++;
        it3++;
    }

    vector<int> expected_size = {3,3,3,3,5,5};
    for (size_t i = 0; i < expected_size.size(); i++) {
        CHECK(it1->size() == expected_size.at(i));
        it1++;
    }

    

    
}