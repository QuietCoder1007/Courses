#include <iostream>
#include "Node.h"
#include "Tree.h"
#include "PrettyPrinter.h"


int main() {
    srand(time(nullptr));
    Tree<int> *t = Tree<int>::makeRandomTree(1, 50);

    std::cout << "\nThe tree has the following structure:";
    std::stringstream ss;
    PrettyPrinter::printPretty(t->root, 1, 0, ss);
    cout << ss.str() << std::endl;

    std::cout << "Printing keys using PreOrder traversal:" << std::endl;
    t->printKeysPreOrder(t->root);

    std::cout << "\n\nPrinting keys using PostOrder traversal:" << std::endl;
    t->printKeysPostOrder(t->root);

    std::cout << "\n\nPrinting keys using InOrder traversal:" << std::endl;
    t->printKeysInOrder(t->root);

    std::cout << "\n\nPrinting keys using LevelOrder traversal:" << std::endl;
    t->printKeysLevelOrder(t->root);

    std::cout << "\n\n======== DONE ========" << std::endl << std::endl;
    return 0;
}
