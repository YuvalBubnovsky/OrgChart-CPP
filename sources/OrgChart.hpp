#include <iostream>
#include <fstream>
#include <sstream>

#include <stdexcept>

#include <vector>
#include <stack>
#include <queue>

namespace ariel
{
    template<class T=string>
    class OrgChart{

    public:
        OrgChart(): p_root(nullptr){
        }

        ~OrgChart(){
            // TODO: Free all nodes
        }

        OrgChart &add_root(T data){
            if(this->p_root == nullptr){
                this->p_root = new Node(data);
            }
            else{
                throw logic_error("Organization Tree Already Exists");
            }
            return *this;}

        OrgChart &add_sub(T manager_data, T subordinate_data){
            // TODO: implement
            return *this;
        }

        friend ostream & operator<< (ostream& output, const OrgChart& orgChart){
            output  << " ";
            return output;
        }


    private:
        // Avoid copying
        OrgChart(const OrgChart& rhs);
        OrgChart& operator=(const OrgChart& rhs);

        // Inner class
        struct Node{
            T value;
            vector<Node *> subordinates;
            Node *manager;

            Node(T &info): value(info), manager(nullptr){}
        };

        // Fields
        Node *p_root;

    public:
        class iterator{
            private:
            Node* p_node;
            int _flag;

            public:
                iterator(Node* ptr = nullptr, int flag=0): p_node(ptr), _flag(flag){
                    if(ptr==nullptr){
                        throw logic_error("Pointing To Nothing!");
                    }

                    if(ptr->subordinates.empty()){
                        // TODO: add logic if this is a leaf node
                    }

                    // TODO: add this
                }

                T& operator*() const {
                    return p_node->value;
                }

                T* operator->() const {
                    return &(p_node->value);
                }

                iterator& operator++(){
                    // TODO: implement this based on the order flag
                    return *this;
                }

                iterator operator++(int){
                    // TODO: implement this based on order flag
                 }

                 bool operator==(const iterator& rhs) const {
                     return p_node == rhs.p_node;
        } 
                bool operator!=(const iterator& rhs) const {
                    return p_node != rhs.p_node;
                }
        }; // END OF ITERATOR CLASS

        iterator begin(){
            return (iterator{p_root,0});
        }

        iterator end(){
            return (iterator{nullptr,0});
        }

        iterator begin_level_order(){
            return (iterator{p_root,0});
        }

        iterator end_level_order() {
            return (iterator{nullptr, 0});
        }

        iterator begin_reverse_order() {
            return (iterator{p_root, 1});
        }

        iterator reverse_order() {
            //not sure about this because we need to stop when we reach root
            return (iterator{nullptr, 1});
        }

        iterator begin_preorder() {
            return (iterator{p_root, 2});
        }

        iterator end_preorder() {
            return (iterator{nullptr, 2});
        }
    };
}