#include <iostream>
#include <stdexcept>

#include <vector>
#include <stack>
#include <queue>

using std::invalid_argument;
using std::logic_error;
using std::out_of_range;
using std::ostream;
using std::queue;
using std::stack;
using std::deque;
using std::string;
using std::vector;

// Reference for this class was taken from Lecture 8 of the course, presentation 2.

namespace ariel {
    template<class T = string> // Template class, will be deaulted to using string;
    class OrgChart {

    public:
        OrgChart() : p_root(nullptr) {
        }

        ~OrgChart() {
            if (this->p_root == nullptr) {
                delete this->p_root;
                return;
            }
            queue<Node *> aux_queue;
            stack<Node *> aux_stack;

            aux_queue.push(this->p_root);

            while (!aux_queue.empty()) {
                Node *temp = aux_queue.front();
                aux_queue.pop();

                if (!temp->subordinates.empty()) {
                    for (auto i = temp->subordinates.size() - 1; i > 0; i--) {
                        aux_queue.push(temp->subordinates.at(i));
                    }

                    aux_queue.push(temp->subordinates.at(0));
                }

                aux_stack.push(temp);
                this->p_root = aux_stack.top();
                aux_stack.pop();
                delete (this->p_root);
            }
        }

        OrgChart(OrgChart &&) noexcept; // move constructor

        OrgChart &operator=(OrgChart &&) noexcept; // move assignment operator

        OrgChart &add_root(T data) {
            if (this->p_root == nullptr) // Case when no root exists
            {
                this->p_root = new Node(data);
            } else { // If a root exists we just need to switch the data since this is a template class - no need to create a new root for this.
                this->p_root->value = data;
            }
            return *this;
        }

        OrgChart &add_sub(T manager_data, T subordinate_data) {
            // TODO: implement
            if (this->p_root == nullptr) {
                throw invalid_argument("Tree Doesn't Exist!");
            }
            deque<Node *> traversal_queue;
            traversal_queue.push_back(this->p_root);
            bool parent_flag = false;
            while (!traversal_queue.empty()) {
                Node *temp = traversal_queue.front();
                if (temp->value == manager_data) {
                    Node *subordinate = new Node(subordinate_data);
                    temp->subordinates.push_back(subordinate);
                    parent_flag = true;
                    break;
                }
                for (Node *employee: temp->subordinates) {
                    traversal_queue.push_back(employee);
                }
                traversal_queue.pop_front();
            }
            if (!parent_flag) {
                throw invalid_argument("Manager Doesn't Exist!");
            }
            return *this;
        }

        friend ostream &operator<<(ostream &os, OrgChart &orgChart) {
            // TODO: implement
            // Currently implemented as level-order printing.
            for (auto it = orgChart.begin_level_order(); it != orgChart.end_level_order(); ++it) {
                os << (*it) << std::endl;
            }
            return os;
        }

    private:
        // Avoid copying
        OrgChart(const OrgChart &rhs);

        OrgChart &operator=(const OrgChart &rhs);

        // Inner class
        struct Node {
            T value;
            vector<Node *> subordinates;
            Node *next_level_order; // pointer to the next in in level order
            Node *next_reverse_order; // pointer to the next node in reverse level order
            Node *next_preorder; // pointer to the next node in preorder order
            Node *manager;

            Node(T &info) : value(info), manager(nullptr) {}
        };

        // Fields
        Node *p_root;

    public: // START OF ITERATOR CLASS
        // TODO: add enumeration for iterator types

        class iterator {
        private:
            Node *p_node;
            int _flag; // flag to decide what type of iterator do we need to returnenum

            // Auxilary queue & stack to traverse the tree (use will be explained in detail below)
            queue<Node *> aux_queue;
            stack<Node *> aux_stack;
            deque<Node *> aux_deque;

            // FLAGS:
            // 0 - Level Order
            // 1 - Reverse Level Order
            // 2 - Preorder

        public:
            iterator(Node *ptr = nullptr, int flag = 2) : p_node(ptr), _flag(flag) {
                // Making sure auxilary queue and stack are empty
                if (!aux_queue.empty()) {
                    while (aux_queue.size() > 0) {
                        aux_queue.pop();
                    }
                }

                if (!aux_stack.empty()) {
                    while (aux_stack.size() > 0) {
                        aux_stack.pop();
                    }
                }

                if (!aux_deque.empty()) {
                    while (aux_queue.size() > 0) {
                        aux_deque.pop_back();
                    }
                }

                if (this->p_node !=
                    nullptr) { // Check if node is not pointing to null, we can't construct an iterator over it

                    // LEVEL ORDER:
                    // Run an iterative BFS algorithm
                    if (this->_flag == 0) {
                        this->aux_deque.push_back(this->p_node);
                        Node *temp = nullptr;
                        while (!this->aux_deque.empty()) {
                            temp = this->aux_deque.front();
                            this->aux_deque.pop_front();
                            for (Node *subordinate: temp->subordinates) {
                                this->aux_deque.push_back(subordinate);
                            }
                            temp->next_level_order = this->aux_deque.front();
                        }
                        if (temp != nullptr) {
                            temp->next_level_order = nullptr;
                        }
                    }

                    else if (this->_flag == 1) {
                        this->aux_deque.push_back(this->p_node);
                        Node *temp = nullptr;
                        while (!this->aux_deque.empty()) {
                            temp = this->aux_deque.front();
                            this->aux_deque.pop_front();
                            for (int i = (int) temp->subordinates.size() - 1; i >= 0; i--) {
                                this->aux_deque.push_back(temp->subordinates.at((size_t) i));
                            }
                            temp->next_reverse_order = this->aux_deque.front();
                        }
                        if (temp != nullptr) {
                            temp->next_reverse_order = nullptr;
                        }

                        // Reverse the deque
                        Node *prev = nullptr;
                        Node *next = nullptr;
                        Node *curr = this->p_node;

                        while (curr != nullptr) {
                            next = curr->next_reverse_order;
                            curr->next_reverse_order = prev;
                            prev = curr;
                            curr = next;
                        }
                        this->p_node = prev;
                    }

                        // PREORDER:
                        // Exactly the same as reverse level order, while also reversing the roles of the stack and the queue to achieve the
                        // desired resault.
                    else {
                        if (!aux_stack.empty()) {
                            while (aux_stack.size() > 0) {
                                aux_stack.pop();
                            }
                        }
                        this->aux_stack.push(this->p_node);
                        Node *temp = nullptr;
                        while (!this->aux_stack.empty()) {
                            temp = this->aux_stack.top();
                            this->aux_stack.pop();
                            for (int i = (int) temp->subordinates.size() - 1; i >= 0; i--) {
                                this->aux_stack.push(temp->subordinates.at((size_t) i));
                            }
                            if (!this->aux_stack.empty()) {
                                temp->next_preorder = this->aux_stack.top();
                            }
                        }
                        if (temp != nullptr) {
                            temp->next_preorder = nullptr;
                        }
                    }

                }
            }

            T &operator*() const {
                return this->p_node->value;
            }

            T *operator->() const {
                return &(this->p_node->value);
            }

            iterator &operator++() // TODO: improve this
            {
                if (!(this->p_node == nullptr)) {
                    if (this->_flag == 2) {
                        this->p_node = this->p_node->next_preorder;
                    } else if (this->_flag == 1) {
                        this->p_node = this->p_node->next_reverse_order;
                    } else {
                        this->p_node = this->p_node->next_level_order;
                    }
                    return *this;
                }
                this->p_node = nullptr;
                return *this;
            }

            iterator operator++(int) // TODO: improve this
            {
                iterator temp = *this;
                ++(temp);
                return temp;
            }

            bool operator==(const iterator &rhs) const {
                return this->p_node == rhs.p_node;
            }

            bool operator!=(const iterator &rhs) const {
                return this->p_node != rhs.p_node;
            }
        }; // END OF ITERATOR CLASS

        iterator begin() {
            if (this->p_root == nullptr) {
                throw invalid_argument("Chart Is Empty!");
            }
            return (iterator{this->p_root, 0});
        }

        iterator end() {
            if (this->p_root == nullptr) {
                throw invalid_argument("Chart Is Empty!");
            }
            return (iterator{nullptr, 0});
        }

        iterator begin_level_order() {
            if (this->p_root == nullptr) {
                throw invalid_argument("Chart Is Empty!");
            }
            return (iterator{this->p_root, 0});
        }

        iterator end_level_order() {
            if (this->p_root == nullptr) {
                throw invalid_argument("Chart Is Empty!");
            }
            return (iterator{nullptr, 0});
        }

        iterator begin_reverse_order() {
            if (this->p_root == nullptr) {
                throw invalid_argument("Chart Is Empty!");
            }
            return (iterator{this->p_root, 1});
        }

        iterator reverse_order() {
            if (this->p_root == nullptr) {
                throw invalid_argument("Chart Is Empty!");
            }
            return (iterator{nullptr, 1});
        }

        iterator begin_preorder() {
            if (this->p_root == nullptr) {
                throw invalid_argument("Chart Is Empty!");
            }
            return (iterator{this->p_root, 2});
        }

        iterator end_preorder() {
            if (this->p_root == nullptr) {
                throw invalid_argument("Chart Is Empty!");
            }
            return (iterator{nullptr, 2});
        }
    };
}