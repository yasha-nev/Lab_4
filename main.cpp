#include <iostream>
#include "list.h"
#include "tree.h"

using namespace std;

int main(int argc, char * argv[])
{
    if (argc < 2){
        return 0;
    }
    cout << "task tree" << endl;
    Tree tree;
    tree.ReadFromFile(argv[1]);
    tree.Print(tree.Head());

    cout << endl;
    task_struct sup = tree.MaxTree(tree.Head());
    cout << "max devide " << sup.devide << "\n";
    cout << "tast max tree\n";
    tree.Print(sup.node);

    cout << endl;
    sup = tree.MinTree(tree.Head());
    cout << "min devide " << sup.devide << "\n";
    cout << "tast min tree\n";
    tree.Print(sup.node);
    return 0;
}
