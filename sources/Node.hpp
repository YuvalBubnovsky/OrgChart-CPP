//
// Created by yuval on 5/12/22.
//

#ifndef ORGCHART_NODE_HPP
#define ORGCHART_NODE_HPP

#pragma once
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

using std::string;

namespace ariel{
    class Node{

    protected:
        string _value;
        int _id;


    public:
        Node();
        ~Node();

        Node* top;
        Node* bottom;
        Node* left;
        Node* right;

        void set_value(string value);
        void set_id(int id);
        string get_value();
        int get_id();
    };
}

#endif //ORGCHART_NODE_HPP
