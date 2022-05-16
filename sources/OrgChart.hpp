#include <iostream>
#include <stdexcept>

#include <vector>
#include <stack>
#include <queue>

using std::invalid_argument;
using std::logic_error;
using std::ostream;
using std::queue;
using std::stack;
using std::string;
using std::vector;

// Reference for this class was taken from Lecture 8 of the course, presentation 2.

namespace ariel
{
    template <class T = string> // Template class, will be deaulted to using string;
    class OrgChart
    {

    public:
        OrgChart() : p_root(nullptr)
        {
        }

        ~OrgChart() 
        { // Destructor works the same as reverse-level-order iterator, that way we can delete the tree in the same way and free the memory

            queue<Node *> aux_queue;
            stack<Node *> aux_stack;

            aux_queue.push(p_root);

            while (!aux_queue.empty())
            {
                Node *temp = aux_queue.front(); 
                aux_queue.pop();

                if (!temp->subordinates.empty())
                { 
                    for (auto i = temp->subordinates.size() - 1; i > 0; i--)
                    {
                        aux_queue.push(temp->subordinates.at(i));
                    }

                    aux_queue.push(temp->subordinates.at(0));
                }

                aux_stack.push(temp);
                p_root = aux_stack.top();
                aux_stack.pop();
                delete(p_root);
            }
        }

        OrgChart(OrgChart &&) noexcept; // move constructor

        OrgChart &operator=(OrgChart &&) noexcept; // move assignment operator

        OrgChart &add_root(T data)
        {
            if (this->p_root == nullptr) // Case when no root exists
            {
                this->p_root = new Node(data);
            }
            else
            { // If a root exists we just need to switch the data since this is a template class - no need to create a new root for this.
                this->p_root->value = data;
            }
            return *this;
        }

        OrgChart &add_sub(T manager_data, T subordinate_data)
        {
            // TODO: implement
            if (this->p_root == nullptr)
            {
                throw logic_error("Tree Doesn't Exist!");
            }
            bool parent_flag = false;
            Node *temp = p_root;
            while (temp != nullptr)
            {
                if (temp->value == manager_data)
                {
                    parent_flag = true;
                    Node *new_sub = new Node(subordinate_data);
                    temp->subordinates.push_back(new_sub);
                    break;
                }

                for (auto &subordinate : temp->subordinates)
                {
                    if (subordinate->value == manager_data)
                    {
                        Node *new_sub = new Node(subordinate_data);
                        subordinate->subordinates.push_back(new_sub);
                        return *this;
                    }
                }

                temp = temp->subordinates.front();
            }
            if (!parent_flag)
            {
                throw logic_error("Manager Doesn't Exist!");
            }
            return *this;
        }

        friend ostream &operator<<(ostream &os, OrgChart &orgChart)
        {
            // TODO: implement
            // Currently implemented as level-order printing.
            for (auto it = orgChart.begin_level_order(); it != orgChart.end_level_order(); ++it)
            {
                os << (*it) << std::endl;
            }
            return os;
        }

    private:
        // Avoid copying
        OrgChart(const OrgChart &rhs);
        OrgChart &operator=(const OrgChart &rhs);

        // Inner class
        struct Node
        {
            T value;
            vector<Node *> subordinates;
            Node *manager;

            Node(T &info) : value(info), manager(nullptr) {}
        };

        // Fields
        Node *p_root;

    public: // START OF ITERATOR CLASS

        class iterator
        {
        private:
            Node *p_node;
            int _flag; // flag to decide what type of iterator do we need to return

            // Auxilary queue & stack to traverse the tree (use will be explained in detail below)
            queue<Node *> aux_queue;
            stack<Node *> aux_stack;

            // FLAGS:
            // 0 - Level Order
            // 1 - Reverse Level Order
            // 2 - Preorder

        public: // CREDIT TO SHAULI TARAGIN FOR HELPING ME WITH THIS
            iterator(Node *ptr = nullptr, int flag = 0) : p_node(ptr), _flag(flag)
            {
                // Making sure auxilary queue and stack are empty
                if (!aux_queue.empty())
                {
                    while (aux_queue.size() > 0)
                    {
                        aux_queue.pop();
                    }
                }

                if (!aux_queue.empty())
                {
                    while (aux_stack.size() > 0)
                    {
                        aux_stack.pop();
                    }
                }

                if (p_node != nullptr)
                { // Check if node is not pointing to null, we can't construct an iterator over it

                    if (!p_node->subordinates.empty())
                    { // If node has no sons, we can't return an iterator for it as there
                      // is nothing to iterate over.

                        // LEVEL ORDER:
                        // Iterate over all the subordinates of a node in the orgtree and push them to the queue, thus
                        // creating a level-order traversal of the tree
                        if (_flag == 0)
                        {
                            for (auto &subordinate : p_node->subordinates)
                            { // we're using auto here because this is a template class and we don't know the type
                                aux_queue.push(subordinate);
                            }
                        }

                        // REVERSE LEVEL ORDER:
                        // Iterate over all the subordinates of a node in the orgtree and enqueue them to the auxilary queue, same
                        // as in the level order traversal, then pop them from the queue and push them to the stack, thus
                        // reversing the level order.
                        else if (_flag == 1)
                        {
                            aux_queue.push(p_node);

                            while (!aux_queue.empty())
                            {
                                Node *temp = aux_queue.front(); // temp node because we can't use pop() here, otherwise we'll get an error
                                aux_queue.pop();

                                if (!temp->subordinates.empty())
                                { // same iteration concept as in level order, removing 1 since we already popped the queue front
                                    for (auto i = temp->subordinates.size() - 1; i > 0; i--)
                                    {
                                        aux_queue.push(temp->subordinates.at(i));
                                    }

                                    aux_queue.push(temp->subordinates.at(0));
                                }
                                // We finished iterating, so push the last node to the stack
                                aux_stack.push(temp);
                            }
                            // Now the stack is the entire level order - reversed, so we can iterate over it
                            p_node = aux_stack.top();
                            aux_stack.pop();
                        }

                        // PREORDER:
                        // Exactly the same as reverse level order, while also reversing the roles of the stack and the queue to achieve the
                        // desired resault.
                        else
                        {
                            aux_stack.push(p_node);
                            while (!aux_stack.empty())
                            {
                                Node *temp = aux_stack.top();
                                aux_stack.pop();
                                if (!temp->subordinates.empty())
                                {
                                    for (auto i = temp->subordinates.size() - 1; i > 0; i--)
                                    {
                                        aux_stack.push(temp->subordinates.at(i));
                                    }
                                    aux_stack.push(temp->subordinates.at(0));
                                }
                                aux_queue.push(temp);
                            }
                            aux_queue.pop();
                        }
                    }
                }
            }

            T &operator*() const
            {
                return p_node->value;
            }

            T *operator->() const
            {
                return &(p_node->value);
            }

            iterator &operator++() // TODO: improve this
            {
                if (!aux_queue.empty() || !aux_stack.empty())
                {
                    if (_flag == 0 || _flag == 2)
                    { // Auxilary queue is already filled in level order, so we can just pop the front, we have now incremented by one
                      // Same goes for preorder.
                        p_node = aux_queue.front();
                        aux_queue.pop();
                    }
                    else
                    { // Auxilary stack is already in reverse level order, so just pop it, we have now incremented by one
                        p_node = aux_stack.top();
                        aux_stack.pop();
                    }
                    return *this;
                }

                // If stack and queue are empty, we have reached the end of the tree, so we return an iterator pointing to nullptr
                p_node = nullptr;
                return *this;
            }

            iterator operator++(int) // TODO: improve this
            {
                iterator temp = *this;
                ++(temp);
                return temp;
            }

            bool operator==(const iterator &rhs) const
            {
                return p_node == rhs.p_node;
            }
            bool operator!=(const iterator &rhs) const
            {
                return p_node != rhs.p_node;
            }
        }; // END OF ITERATOR CLASS

        iterator begin()
        {
            return (iterator{p_root, 0});
        }

        iterator end()
        {
            return (iterator{nullptr, 0});
        }

        iterator begin_level_order()
        {
            return (iterator{p_root, 0});
        }

        iterator end_level_order()
        {
            return (iterator{nullptr, 0});
        }

        iterator begin_reverse_order()
        {
            return (iterator{p_root, 1});
        }

        iterator reverse_order()
        {
            return (iterator{nullptr, 1});
        }

        iterator begin_preorder()
        {
            return (iterator{p_root, 2});
        }

        iterator end_preorder()
        {
            return (iterator{nullptr, 2});
        }
    };
}