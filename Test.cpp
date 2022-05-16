#include "doctest.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "sources/OrgChart.hpp"
using namespace std;
using namespace ariel;

TEST_CASE("String Input")
{
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("CCEEOO"));
    CHECK_NOTHROW(organization.add_root("CEO"));
    CHECK_NOTHROW(organization.add_sub("CEO", "CTO"));   // Now the CTO is subordinate to the CEO
    CHECK_NOTHROW(organization.add_sub("CEO", "CFO"));   // Now the CFO is subordinate to the CEO
    CHECK_NOTHROW(organization.add_sub("CEO", "COO"));   // Now the COO is subordinate to the CEO
    CHECK_NOTHROW(organization.add_sub("CTO", "VP_SW")); // Now the VP Software is subordinate to the CTO
    CHECK_NOTHROW(organization.add_sub("COO", "VP_BI")); // Now the VP_BI is subordinate to the COO

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

    for (size_t i = 0; i < expected_level.size(); i++)
    {
        CHECK((*it1) == expected_level.at(i));
        CHECK((*it2) == expected_reverse.at(i));
        CHECK((*it3) == expected_preorder.at(i));
        it1++;
        it2++;
        it3++;
    }

    vector<int> expected_size = {3, 3, 3, 3, 5, 5};
    for (size_t i = 0; i < expected_size.size(); i++)
    {
        CHECK(it1->size() == expected_size.at(i));
        it1++;
    }
}

TEST_CASE("Object Input")
{
    class Employee
    {
    public:
        string _name;
        Employee(string name) : _name(name) {}

        bool operator==(Employee &employee)
        {
            return this->getName() == employee.getName();
        }

        string getName()
        {
            return this->_name;
        }
    };

    Employee CEO("CEO");
    Employee CCEEOO("CCEEOO");
    Employee CTO("CTO");
    Employee CFO("CFO");
    Employee COO("COO");
    Employee VP_SW("VP_SW");
    Employee VP_BI("VP_BI");

    OrgChart<Employee> organization;
    CHECK_NOTHROW(organization.add_root(CEO));
    CHECK_NOTHROW(organization.add_sub(CEO, CTO));   // Now the CTO is subordinate to the CEO
    CHECK_NOTHROW(organization.add_sub(CEO, CFO));   // Now the CFO is subordinate to the CEO
    CHECK_NOTHROW(organization.add_sub(CEO, COO));   // Now the COO is subordinate to the CEO
    CHECK_NOTHROW(organization.add_root(CCEEOO));
    CHECK_NOTHROW(organization.add_sub(CTO, VP_SW)); // Now the VP Software is subordinate to the CTO
    CHECK_NOTHROW(organization.add_sub(COO, VP_BI)); // Now the VP_BI is subordinate to the COO

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

    vector<Employee> expected_level = {CCEEOO, CTO, CFO, COO, VP_SW, VP_BI};
    vector<Employee> expected_reverse = {VP_SW, VP_BI, CTO, CFO, COO, CCEEOO};
    vector<Employee> expected_preorder = {CCEEOO, CTO, VP_SW, CFO, COO, VP_BI};

    for (size_t i = 0; i < expected_level.size(); i++)
    {
        CHECK((*it1).getName() == expected_level.at(i).getName());
        CHECK((*it2).getName() == expected_reverse.at(i).getName());
        CHECK((*it3).getName() == expected_preorder.at(i).getName());
        it1++;
        it2++;
        it3++;
    }
}

TEST_CASE("Merging Two Trees"){
    // TODO: add this test
}


TEST_CASE("Bad Behaviour"){
    // TODO: add this test
}