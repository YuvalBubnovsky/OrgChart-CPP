/**
 * Demo file for the exercise on iterators
 *
 * @author Tal Zichlinsky
 * @since 2022-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "sources/OrgChart.hpp"
using namespace ariel;

int main()
{
    OrgChart<string> org;
    OrgChart<string> org_empty;
    OrgChart<string> org_double_names;
    /* create normal tree */
    org.add_root("dana");
    org.add_root("shir");
   org.add_sub("shir", "tal");
   org.add_sub("shir", "sapir");
    org.add_sub("sapir", "dan");
    org.add_sub("dan", "ziv");
    org.add_sub("tal", "avi");
    org.add_sub("tal", "yossi");
    org.add_sub("shir", "ido");
    org.add_sub("ziv", "shaked");
    org.add_sub("ziv", "ofer");

    org_double_names.add_root("adi");
    for (size_t i = 0; i < 11; i++)
    {
        org_double_names.add_sub("adi", "adi");
    }

    /*check reverse level order with normal tree*/
    std::vector<std::string> v = {"shaked", "ofer", "ziv", "avi", "yossi", "dan", "tal", "sapir", "ido", "shir"};
    size_t i = 0;
    for(auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it){
        cout << *it << "\t" << v.at(i++) << "\t" << endl;
    }


    return 0;
}