//
// Created by yuval on 5/12/22.
//

#ifndef ORGCHART_ORGCHART_HPP
#define ORGCHART_ORGCHART_HPP
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "Node.hpp"

using std::string;
using std::vector;
using std::ostream;

namespace ariel{
    class OrgChart{
    protected:
        vector<Node*> Employees;
    public:
        OrgChart();
        void add_root(string input);
        void add_sub(string top, string bottom);
        vector<Node*>::iterator begin_level_order();
        vector<Node*>::iterator end_level_order();
        vector<Node*>::iterator begin_reverse_order();
        vector<Node*>::iterator end_reverse_order();
        vector<Node*>::iterator begin_preorder();
        vector<Node*>::iterator end_preorder();

        friend ostream &operator<<(ostream &out, const OrgChart &org);
    };
}

#endif //ORGCHART_ORGCHART_HPP
