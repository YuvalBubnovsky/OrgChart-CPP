#include "iostream"
#include "sources/OrgChart.hpp"

using namespace ariel;
using namespace std;

int main()
{

    OrgChart<> demo_chart;

    /*simple root creation*/
    string root;
    cout << "Insert the root of the chart:"
         << "\n";
    cin >> root;
    demo_chart.add_root(root);

    string choice;
    string sub;

    while (true)
    {
        cout << "A. To add subs to the tree enter: addsub"
             << "\n";
        cout << "B. To apply a certain order insert: \n "
             << "1. level order \n 2. reverse order \n 3. preorder"
             << "\n";
        cout << "C. at anytime you wish to end program and display the chart insert Exit"
             << "\n";
        cout << "D. to display a pre-generated chart insert: pregen"
             << "\n";
        cin >> choice;
        if (choice == "addsub")
        {
            cout << "Enter the root of the sub: "
                 << "\n";
            cin >> root;
            cout << "Now enter the actual sub you want to add: "
                 << "\n";
            cin >> sub;
            demo_chart.add_sub(root, sub);
        }
        else if (choice == "1")
        {
            /*level order*/
            for (auto it = demo_chart.begin_level_order(); it != demo_chart.end_level_order(); ++it)
            {
                cout << (*it) << " ";
            }
            cout << "\n";
        }
        else if (choice == "2")
        {
            /*reverse order*/
            for (auto it = demo_chart.begin_reverse_order(); it != demo_chart.reverse_order(); ++it)
            {
                cout << (*it) << " ";
            }
            cout << "\n";
        }
        else if (choice == "3")
        {
            /*preorder*/
            for (auto it = demo_chart.begin_preorder(); it != demo_chart.end_preorder(); ++it)
            {
                cout << (*it) << " ";
            }
            cout << "\n";
        }
        else if (choice == "Exit")
        {
            cout << "Exit program"
                 << "\n";
            break;
        }
        else if(choice == "pregen"){
            demo_chart.add_root("shir");
            demo_chart.add_sub("shir", "tal");
            demo_chart.add_sub("shir", "sapir");
            demo_chart.add_sub("sapir", "dan");
            demo_chart.add_sub("dan", "ziv");
            demo_chart.add_sub("tal", "avi");
            demo_chart.add_sub("tal", "yossi");
            demo_chart.add_sub("shir", "ido");
            demo_chart.add_sub("ziv", "shaked");
            demo_chart.add_sub("ziv", "ofer");
        }
        else
        {
            cout << "Bad choice enter again..."
                 << "\n";
        }
    }
    cout << "printing chart in someway... : "
         << "\n";
    cout << demo_chart << "\n";
    cout << endl;
}