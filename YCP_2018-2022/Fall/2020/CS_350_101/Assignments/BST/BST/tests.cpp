//
//  tests.cpp
//

#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_CONSOLE_WIDTH 150

#include <iostream>
#include "BST.h"
#include "catch.hpp"
#include "PrettyPrinter.h"


/* **************************************************************** */
/* **************************************************************** */


void printTreeAsString(std::stringstream & ss) {
    std::string myString = ss.str();
    printf("\"");
    for (unsigned int i=0; i < myString.length(); i++) {
        if (myString[i] == '\n') {
            printf("\\n\"\n\"");
        } else if (myString[i] == '\\') {
            printf("\\\\");
        } else {
            printf("%c", myString[i]);
        }
    }
    printf("\";");
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing constructor", "[CONSTRUCTOR]") {
    BST<int> tree;

    SECTION("when BST is empty, the root node should be set to nullptr") {
        REQUIRE(tree.root == nullptr);
    }
    
    SECTION("when BST is empty, the numNodes field should be set to 0") {
        REQUIRE(tree.numNodes == 0);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing isEmpty() method on an empty BST", "[ISEMPTY]") {
    BST<int> tree;
    INFO("root node should be nullptr");
    REQUIRE(tree.root == nullptr);
    INFO("numNodes should be 0");
    REQUIRE(tree.numNodes == 0);

    SECTION("verify return value of isEmpty()") {
        INFO("when empty, isEmpty() should return true");
        REQUIRE(tree.isEmpty() == true);
    }
}


TEST_CASE("testing isEmpty() method on a non-empty BST", "[ISEMPTY]") {
    BST<int> tree;

    SECTION("verify return value of isEmpty() after single insert") {
        tree.insert(5);
        INFO("inserted value 5");
        INFO("when not empty, isEmpty() should return false");
        REQUIRE(tree.isEmpty() == false);
    }

    SECTION("verify return value of isEmpty() after multiple inserts (left child)") {
        tree.insert(5);
        tree.insert(2);
        INFO("inserted values 5, 2");
        INFO("when not empty, isEmpty() should return false");
        REQUIRE(tree.isEmpty() == false);
    }

    SECTION("verify return value of isEmpty() after multiple inserts (right child)") {
        tree.insert(5);
        tree.insert(10);
        INFO("inserted values 5, 10");
        INFO("when not empty, isEmpty() should return false");
        REQUIRE(tree.isEmpty() == false);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing find(x) method on an empty BST", "[FIND]") {
    BST<int> tree;

    SECTION("verify that find(x) returns false when BST is empty") {
        REQUIRE(tree.find(11) == false);
    }
}


TEST_CASE("testing find(x) method on a non-empty BST", "[FIND]") {
    BST<int> tree;
    tree.insert(15);
    tree.insert(6);
    tree.insert(18);
    tree.insert(3);
    tree.insert(7);
    tree.insert(17);
    tree.insert(20);
    tree.insert(2);
    tree.insert(4);
    tree.insert(13);
    tree.insert(9);
    std::stringstream ss;
    PrettyPrinter::printPretty(tree.root, 1, 0, ss);
    INFO("inserted values 15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9");
    const char *treeString = "\n"
        "                ______________15______________\n"
        "               /                              \\\n"
        "        _______6______                  ______18______\n"
        "       /              \\                /              \\\n"
        "    ___3__             7__            17              20  \n"
        "   /      \\               \\                                \n"
        "   2       4              13                                \n"
        "                         /                                   \n"
        "                         9                                    \n";
    INFO("before calling find(x), BST should be: " << treeString);
    INFO("Your BST is: " << ss.str());
    
    SECTION("verify that find(x) returns false when BST does not contain x") {
        INFO("should fail to find the value 11");
        REQUIRE(tree.find(11) == false);
    }
    
    SECTION("verify that find(x) returns true when BST contains x in a leaf node") {
        INFO("should successfully find the value 9");
        REQUIRE(tree.find(9) == true);
    }
    
    SECTION("verify that find(x) returns true when BST contains x in a middle node with two children") {
        INFO("should successfully find the value 6");
        REQUIRE(tree.find(6) == true);
    }
    
    SECTION("verify that find(x) returns true when BST contains x in a middle node with single left child") {
        INFO("should successfully find the value 13");
        REQUIRE(tree.find(13) == true);
    }

    SECTION("verify that find(x) returns true when BST contains x in a middle node with single right child") {
        INFO("should successfully find the value 7");
        REQUIRE(tree.find(7) == true);
    }

    SECTION("verify that find(x) returns true when BST contains x in the root node") {
        INFO("should successfully find the value 15");
        REQUIRE(tree.find(15) == true);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing findMin() method on an empty BST", "[FINDMIN][!throws]") {
    BST<int> tree;

    SECTION("verify that findMin() throws an exception when BST is empty") {
        INFO("the findMin() method should throw an error when the BST is empty");
        REQUIRE_THROWS(tree.findMin());
    }
}


TEST_CASE("testing findMin() method on a non-empty BST", "[FINDMIN]") {
    BST<int> tree;
    tree.insert(15);
    tree.insert(6);
    tree.insert(18);
    tree.insert(3);
    tree.insert(7);
    tree.insert(17);
    tree.insert(20);
    tree.insert(2);
    tree.insert(4);
    tree.insert(13);
    tree.insert(9);
    std::stringstream ss;
    PrettyPrinter::printPretty(tree.root, 1, 0, ss);
    INFO("inserted values 15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9");
    const char *treeString = "\n"
        "                ______________15______________\n"
        "               /                              \\\n"
        "        _______6______                  ______18______\n"
        "       /              \\                /              \\\n"
        "    ___3__             7__            17              20  \n"
        "   /      \\               \\                                \n"
        "   2       4              13                                \n"
        "                         /                                   \n"
        "                         9                                    \n";
    INFO("before calling findMin(), BST should be: " << treeString);
    INFO("Your BST is: " << ss.str());

    // may want to add tests to indicate that findMin works in all of the following cases:
    // 1) min is root node
    // 2) min is a leaf node
    // 3) min is an internal node with a single right child

    SECTION("verify that findMin() returns the correct value") {
        INFO("the findMin() method should return 2");
        REQUIRE(tree.findMin() == 2);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing findMax() method on an empty BST", "[FINDMAX][!throws]") {
    BST<int> tree;

    SECTION("verify that findMax() throws an exception when BST is empty") {
        INFO("the findMax() method should throw an error when the BST is empty");
        REQUIRE_THROWS(tree.findMax());
    }
}


TEST_CASE("testing findMax() method on a non-empty BST", "[FINDMAX]") {
    BST<int> tree;
    tree.insert(15);
    tree.insert(6);
    tree.insert(18);
    tree.insert(3);
    tree.insert(7);
    tree.insert(17);
    tree.insert(20);
    tree.insert(2);
    tree.insert(4);
    tree.insert(13);
    tree.insert(9);
    std::stringstream ss;
    PrettyPrinter::printPretty(tree.root, 1, 0, ss);
    INFO("inserted values 15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9");
    const char *treeString = "\n"
        "                ______________15______________\n"
        "               /                              \\\n"
        "        _______6______                  ______18______\n"
        "       /              \\                /              \\\n"
        "    ___3__             7__            17              20  \n"
        "   /      \\               \\                                \n"
        "   2       4              13                                \n"
        "                         /                                   \n"
        "                         9                                    \n";
    INFO("before calling findMax(), BST should be: " << treeString);
    INFO("Your BST is: " << ss.str());

    // may want to add tests to indicate that findMax works in all of the following cases:
    // 1) max is root node
    // 2) max is a leaf node
    // 3) max is an internal node with a single left child

    SECTION("verify that findMax() returns the correct value") {
        INFO("the findMax() method should return 20");
        REQUIRE(tree.findMax() == 20);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing insert() method on an empty BST", "[INSERT]") {
    BST<int> tree;

    SECTION("verify structure of BST after single insert into empty BST") {
        tree.insert(4);
        std::stringstream ss;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss);
        INFO("inserted value 4");
        INFO("BST should be: \n 4\n");
        INFO("Your BST is: " << ss.str());
        REQUIRE(tree.root->data == 4);
        REQUIRE(tree.root->left == nullptr);
        REQUIRE(tree.root->right == nullptr);
        INFO("after inserting a single value, BST numNodes should be 1");
        REQUIRE(tree.numNodes == 1);
    }

    SECTION("verify structure of BST after multiple inserts into empty BST") {
        tree.insert(4);
        tree.insert(3);
        tree.insert(5);
        std::stringstream ss;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss);
        INFO("inserted values 4, 3, 5");
        const char *treeString = "\n"
            "  _4\n"
            " /  \\\n"
            " 3   5\n";
        INFO("BST should be: " << treeString);
        INFO("Your BST is: " << ss.str());
        REQUIRE(tree.root != nullptr);                 // checking root node
        REQUIRE(tree.root->data == 4);
        REQUIRE(tree.root->left->data == 3);        // checking node 4 children
        REQUIRE(tree.root->right->data == 5);
        REQUIRE(tree.root->left->left == nullptr);     // checking node 3 children
        REQUIRE(tree.root->left->right == nullptr);
        REQUIRE(tree.root->right->left == nullptr);    // checking node 5 children
        REQUIRE(tree.root->right->right == nullptr);
        INFO("after inserting multiple values, BST numNodes should be 3");
        REQUIRE(tree.numNodes == 3);
    }
}


TEST_CASE("testing insert() method on a non-empty BST (multiple inserts)", "[INSERT]") {
    BST<int> tree;

    SECTION("verify structure of BST after inserting into a non-empty BST (multiple inserts)") {
        tree.insert(50);
        tree.insert(75);
        tree.insert(25);
        tree.insert(10);
        tree.insert(5);
        tree.insert(1);
        tree.insert(6);
        tree.insert(26);
        tree.insert(60);
        tree.insert(51);
        tree.insert(65);
        tree.insert(69);
        std::stringstream ss;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss);
        INFO("inserted values 50, 75, 25, 10, 5, 1, 6, 26, 60, 51, 65, 69");
        const char *treeString = "\n"
            "                ______________50______________\n"
            "               /                              \\\n"
            "        ______25______                  ______75      \n"
            "       /              \\                /               \n"
            "    __10              26            __60__                \n"
            "   /                               /      \\                \n"
            "  _5                              51      65                \n"
            " /  \\                                       \\                \n"
            " 1   6                                      69                \n";
        INFO("BST should be: " << treeString);
        INFO("Your BST is: " << ss.str());
        REQUIRE(tree.root != nullptr);                                   // checking root node
        REQUIRE(tree.root->data == 50);
        REQUIRE(tree.root->left->data == 25);                         // checking node 50 children
        REQUIRE(tree.root->right->data == 75);
        REQUIRE(tree.root->left->left->data == 10);                   // checking node 25 children
        REQUIRE(tree.root->left->right->data == 26);
        REQUIRE(tree.root->right->left->data == 60);                  // checking node 75 children
        REQUIRE(tree.root->right->right == nullptr);
        REQUIRE(tree.root->left->left->left->data == 5);              // checking node 10 children
        REQUIRE(tree.root->left->left->right == nullptr);
        REQUIRE(tree.root->left->right->left == nullptr);                // checking node 26 children
        REQUIRE(tree.root->left->right->right == nullptr);
        REQUIRE(tree.root->right->left->left->data == 51);            // checking node 60 children
        REQUIRE(tree.root->right->left->right->data == 65);
        REQUIRE(tree.root->left->left->left->left->data == 1);        // checking node 5 children
        REQUIRE(tree.root->left->left->left->right->data == 6);
        REQUIRE(tree.root->right->left->left->left == nullptr);          // checking node 51 children
        REQUIRE(tree.root->right->left->left->right == nullptr);
        REQUIRE(tree.root->right->left->right->left == nullptr);         // checking node 65 children
        REQUIRE(tree.root->right->left->right->right->data == 69);
        REQUIRE(tree.root->left->left->left->left->left == nullptr);     // checking node 1 children
        REQUIRE(tree.root->left->left->left->left->right == nullptr);
        REQUIRE(tree.root->left->left->left->right->left == nullptr);    // checking node 6 children
        REQUIRE(tree.root->left->left->left->right->right == nullptr);
        REQUIRE(tree.root->right->left->right->right->left == nullptr);  // checking node 69 children
        REQUIRE(tree.root->right->left->right->right->right == nullptr);
        INFO("after inserting multiple values, BST numNodes should be 12");
        REQUIRE(tree.numNodes == 12);
    }

    SECTION("verify structure of BST after attempting to insert duplicate nodes") {
        tree.insert(4);
        tree.insert(3);
        tree.insert(5);
        tree.insert(3);
        tree.insert(5);
        tree.insert(4);
        std::stringstream ss;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss);
        INFO("inserted values 4, 3, 5, 3 (again), 5 (again), 4 (again)");
        const char *treeString = "\n"
            "  _4\n"
            " /  \\\n"
            " 3   5\n";
        INFO("BST should be: " << treeString);
        INFO("Your BST is: " << ss.str());
        REQUIRE(tree.root != nullptr);                 // checking root node
        REQUIRE(tree.root->data == 4);
        REQUIRE(tree.root->left->data == 3);        // checking node 4 children
        REQUIRE(tree.root->right->data == 5);
        REQUIRE(tree.root->left->left == nullptr);     // checking node 3 children
        REQUIRE(tree.root->left->right == nullptr);
        REQUIRE(tree.root->right->left == nullptr);    // checking node 5 children
        REQUIRE(tree.root->right->right == nullptr);
        INFO("after attempting to insert duplicate nodes, numNodes should still be 3");
        REQUIRE(tree.numNodes == 3);                // check the numNodes value
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing remove(x) method on an empty BST", "[REMOVE]") {
    BST<int> tree;

    SECTION("verify that remove(x) doesn't break anything when BST is empty") {
        INFO("before calling remove(x), BST should be empty [ root -> nullptr ]");
        REQUIRE(tree.root == nullptr);
        INFO("before calling remove(x), BST numNodes should be 0");
        REQUIRE(tree.numNodes == 0);
        tree.remove(11);
        INFO("after calling remove(x), BST should be empty [ root -> nullptr ]");
        REQUIRE(tree.root == nullptr);
        INFO("after calling remove(x), BST numNodes should be 0");
        REQUIRE(tree.numNodes == 0);
    }
    
    SECTION("verify that remove(x) successfully removes the last node in the tree (i.e. the root node)") {
        INFO("before calling remove(x), insert value 50 into empty tree");
        tree.insert(50);
        std::stringstream ss;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss);
        INFO("before calling remove(x), your BST is:: " << ss.str());
        REQUIRE(tree.root != nullptr);         // checking root node
        REQUIRE(tree.root->data == 50);
        REQUIRE(tree.root->left == nullptr);
        REQUIRE(tree.root->right == nullptr);
        INFO("before calling remove(x), BST numNodes should be 1");
        REQUIRE(tree.numNodes == 1);
        
        tree.remove(50);
        INFO("after calling remove(x) to remove the value 50, BST should be empty [ root -> nullptr ]");
        REQUIRE(tree.root == nullptr);         // checking root node
        INFO("after calling remove(x) to remove the value 50, BST numNodes should be 0");
        REQUIRE(tree.numNodes == 0);
    }
}


TEST_CASE("testing remove() method on a non-empty BST", "[REMOVE]") {
    BST<int> tree;
    tree.insert(50);
    tree.insert(75);
    tree.insert(25);
    tree.insert(10);
    tree.insert(5);
    tree.insert(1);
    tree.insert(6);
    tree.insert(26);
    tree.insert(60);
    tree.insert(51);
    tree.insert(65);
    tree.insert(69);
    std::stringstream ss;
    PrettyPrinter::printPretty(tree.root, 1, 0, ss);
    INFO("inserted values 50, 75, 25, 10, 5, 1, 6, 26, 60, 51, 65, 69");
    const char *treeString = "\n"
        "                ______________50______________\n"
        "               /                              \\\n"
        "        ______25______                  ______75      \n"
        "       /              \\                /               \n"
        "    __10              26            __60__                \n"
        "   /                               /      \\                \n"
        "  _5                              51      65                \n"
        " /  \\                                       \\                \n"
        " 1   6                                      69                \n";
    INFO("before calling remove(x), BST should be: " << treeString);
    INFO("Your BST is: " << ss.str());
    INFO("before calling remove(x), BST numNodes should be 12");
    REQUIRE(tree.numNodes == 12);

    SECTION("verify that remove(x) doesn't break anything when attempting to remove a value not in BST") {
        tree.remove(4);
        tree.remove(29);
        tree.remove(53);
        tree.remove(99);
        std::stringstream ss2;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss2);
        INFO("after attempting to remove non-existent values: 4, 29, 53, 99");
        INFO("BST should still be: " << treeString);
        INFO("Your BST is: " << ss2.str());
        REQUIRE(tree.root != nullptr);                                   // checking root node
        REQUIRE(tree.root->data == 50);
        REQUIRE(tree.root->left->data == 25);                         // checking node 50 children
        REQUIRE(tree.root->right->data == 75);
        REQUIRE(tree.root->left->left->data == 10);                   // checking node 25 children
        REQUIRE(tree.root->left->right->data == 26);
        REQUIRE(tree.root->right->left->data == 60);                  // checking node 75 children
        REQUIRE(tree.root->right->right == nullptr);
        REQUIRE(tree.root->left->left->left->data == 5);              // checking node 10 children
        REQUIRE(tree.root->left->left->right == nullptr);
        REQUIRE(tree.root->left->right->left == nullptr);                // checking node 26 children
        REQUIRE(tree.root->left->right->right == nullptr);
        REQUIRE(tree.root->right->left->left->data == 51);            // checking node 60 children
        REQUIRE(tree.root->right->left->right->data == 65);
        REQUIRE(tree.root->left->left->left->left->data == 1);        // checking node 5 children
        REQUIRE(tree.root->left->left->left->right->data == 6);
        REQUIRE(tree.root->right->left->left->left == nullptr);          // checking node 51 children
        REQUIRE(tree.root->right->left->left->right == nullptr);
        REQUIRE(tree.root->right->left->right->left == nullptr);         // checking node 65 children
        REQUIRE(tree.root->right->left->right->right->data == 69);
        REQUIRE(tree.root->left->left->left->left->left == nullptr);     // checking node 1 children
        REQUIRE(tree.root->left->left->left->left->right == nullptr);
        REQUIRE(tree.root->left->left->left->right->left == nullptr);    // checking node 6 children
        REQUIRE(tree.root->left->left->left->right->right == nullptr);
        REQUIRE(tree.root->right->left->right->right->left == nullptr);  // checking node 69 children
        REQUIRE(tree.root->right->left->right->right->right == nullptr);
        INFO("after attempting to remove non-existent values: 4, 29, 53, 99, BST numNodes should still be 12");
        REQUIRE(tree.numNodes == 12);
    }

    SECTION("verify that remove(x) successfully removes a node that has no children") {
        tree.remove(26);
        std::stringstream ss2;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss2);
        INFO("after attempting to remove the value 26");
        const char *treeString2 = "\n"
            "                ______________50______________\n"
            "               /                              \\\n"
            "        ______25                        ______75      \n"
            "       /                               /               \n"
            "    __10                            __60__                \n"
            "   /                               /      \\                \n"
            "  _5                              51      65                \n"
            " /  \\                                       \\                \n"
            " 1   6                                      69                \n";
        INFO("BST should now be: " << treeString2);
        INFO("Your BST is: " << ss2.str());
        REQUIRE(tree.root != nullptr);                                   // checking root node
        REQUIRE(tree.root->data == 50);
        REQUIRE(tree.root->left->data == 25);                         // checking node 50 children
        REQUIRE(tree.root->right->data == 75);
        REQUIRE(tree.root->left->left->data == 10);                   // checking node 25 children
        REQUIRE(tree.root->left->right == nullptr);
        REQUIRE(tree.root->right->left->data == 60);                  // checking node 75 children
        REQUIRE(tree.root->right->right == nullptr);
        REQUIRE(tree.root->left->left->left->data == 5);              // checking node 10 children
        REQUIRE(tree.root->left->left->right == nullptr);
        REQUIRE(tree.root->right->left->left->data == 51);            // checking node 60 children
        REQUIRE(tree.root->right->left->right->data == 65);
        REQUIRE(tree.root->left->left->left->left->data == 1);        // checking node 5 children
        REQUIRE(tree.root->left->left->left->right->data == 6);
        REQUIRE(tree.root->right->left->left->left == nullptr);          // checking node 51 children
        REQUIRE(tree.root->right->left->left->right == nullptr);
        REQUIRE(tree.root->right->left->right->left == nullptr);         // checking node 65 children
        REQUIRE(tree.root->right->left->right->right->data == 69);
        REQUIRE(tree.root->left->left->left->left->left == nullptr);     // checking node 1 children
        REQUIRE(tree.root->left->left->left->left->right == nullptr);
        REQUIRE(tree.root->left->left->left->right->left == nullptr);    // checking node 6 children
        REQUIRE(tree.root->left->left->left->right->right == nullptr);
        REQUIRE(tree.root->right->left->right->right->left == nullptr);  // checking node 69 children
        REQUIRE(tree.root->right->left->right->right->right == nullptr);
        INFO("after attempting to remove the value 26, BST numNodes should now be 11");
        REQUIRE(tree.numNodes == 11);
    }

    SECTION("verify that remove(x) successfully removes a node that has one child (left child)") {
        tree.remove(75);
        std::stringstream ss2;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss2);
        INFO("after attempting to remove the value 75");
        const char *treeString2 = "\n"
            "                ______________50______________\n"
            "               /                              \\\n"
            "        ______25______                  ______60______\n"
            "       /              \\                /              \\\n"
            "    __10              26              51              65__\n"
            "   /                                                      \\\n"
            "  _5                                                      69\n"
            " /  \\                                                        \n"
            " 1   6                                                        \n";
        INFO("BST should now be: " << treeString2);
        INFO("Your BST is: " << ss2.str());
        REQUIRE(tree.root != nullptr);                                   // checking root node
        REQUIRE(tree.root->data == 50);
        REQUIRE(tree.root->left->data == 25);                         // checking node 50 children
        REQUIRE(tree.root->right->data == 60);
        REQUIRE(tree.root->left->left->data == 10);                   // checking node 25 children
        REQUIRE(tree.root->left->right->data == 26);
        REQUIRE(tree.root->right->left->data == 51);                  // checking node 60 children
        REQUIRE(tree.root->right->right->data == 65);
        REQUIRE(tree.root->left->left->left->data == 5);              // checking node 10 children
        REQUIRE(tree.root->left->left->right == nullptr);
        REQUIRE(tree.root->left->right->left == nullptr);                // checking node 26 children
        REQUIRE(tree.root->left->right->right == nullptr);
        REQUIRE(tree.root->right->left->left == nullptr);                // checking node 51 children
        REQUIRE(tree.root->right->left->right == nullptr);
        REQUIRE(tree.root->right->right->left == nullptr);               // checking node 65 children
        REQUIRE(tree.root->right->right->right->data == 69);
        REQUIRE(tree.root->left->left->left->left->data == 1);        // checking node 5 children
        REQUIRE(tree.root->left->left->left->right->data == 6);
        REQUIRE(tree.root->right->right->right->left == nullptr);        // checking node 69 children
        REQUIRE(tree.root->right->right->right->right == nullptr);
        REQUIRE(tree.root->left->left->left->left->left == nullptr);     // checking node 1 children
        REQUIRE(tree.root->left->left->left->left->right == nullptr);
        REQUIRE(tree.root->left->left->left->right->left == nullptr);    // checking node 6 children
        REQUIRE(tree.root->left->left->left->right->right == nullptr);
        INFO("after attempting to remove the value 75, BST numNodes should now be 11");
        REQUIRE(tree.numNodes == 11);
    }

    SECTION("verify that remove(x) successfully removes a node that has one child (right child)") {
        tree.remove(65);
        std::stringstream ss2;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss2);
        INFO("after attempting to remove the value 65");
        const char *treeString2 = "\n"
            "                ______________50______________\n"
            "               /                              \\\n"
            "        ______25______                  ______75      \n"
            "       /              \\                /               \n"
            "    __10              26            __60__                \n"
            "   /                               /      \\                \n"
            "  _5                              51      69                \n"
            " /  \\                                                        \n"
            " 1   6                                                        \n";
        INFO("BST should now be: " << treeString2);
        INFO("Your BST is: " << ss2.str());
        REQUIRE(tree.root != nullptr);                                   // checking root node
        REQUIRE(tree.root->data == 50);
        REQUIRE(tree.root->left->data == 25);                         // checking node 50 children
        REQUIRE(tree.root->right->data == 75);
        REQUIRE(tree.root->left->left->data == 10);                   // checking node 25 children
        REQUIRE(tree.root->left->right->data == 26);
        REQUIRE(tree.root->right->left->data == 60);                  // checking node 75 children
        REQUIRE(tree.root->right->right == nullptr);
        REQUIRE(tree.root->left->left->left->data == 5);              // checking node 10 children
        REQUIRE(tree.root->left->left->right == nullptr);
        REQUIRE(tree.root->left->right->left == nullptr);                // checking node 26 children
        REQUIRE(tree.root->left->right->right == nullptr);
        REQUIRE(tree.root->right->left->left->data == 51);            // checking node 60 children
        REQUIRE(tree.root->right->left->right->data == 69);
        REQUIRE(tree.root->left->left->left->left->data == 1);        // checking node 5 children
        REQUIRE(tree.root->left->left->left->right->data == 6);
        REQUIRE(tree.root->right->left->left->left == nullptr);          // checking node 51 children
        REQUIRE(tree.root->right->left->left->right == nullptr);
        REQUIRE(tree.root->right->left->right->left == nullptr);         // checking node 69 children
        REQUIRE(tree.root->right->left->right->right == nullptr);
        REQUIRE(tree.root->left->left->left->left->left == nullptr);     // checking node 1 children
        REQUIRE(tree.root->left->left->left->left->right == nullptr);
        REQUIRE(tree.root->left->left->left->right->left == nullptr);    // checking node 6 children
        REQUIRE(tree.root->left->left->left->right->right == nullptr);
        INFO("after attempting to remove the value 65, BST numNodes should now be 11");
        REQUIRE(tree.numNodes == 11);
    }

    SECTION("verify that remove(x) successfully removes a node that has two children (successor has right child)") {
        tree.remove(60);
        std::stringstream ss2;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss2);
        INFO("after attempting to remove the value 60");
        const char *treeString2 = "\n"
            "                ______________50______________\n"
            "               /                              \\\n"
            "        ______25______                  ______75      \n"
            "       /              \\                /               \n"
            "    __10              26            __65__                \n"
            "   /                               /      \\                \n"
            "  _5                              51      69                \n"
            " /  \\                                                        \n"
            " 1   6                                                        \n";
        INFO("BST should now be: " << treeString2);
        INFO("Your BST is: " << ss2.str());
        REQUIRE(tree.root != nullptr);                                   // checking root node
        REQUIRE(tree.root->data == 50);
        REQUIRE(tree.root->left->data == 25);                         // checking node 50 children
        REQUIRE(tree.root->right->data == 75);
        REQUIRE(tree.root->left->left->data == 10);                   // checking node 25 children
        REQUIRE(tree.root->left->right->data == 26);
        REQUIRE(tree.root->right->left->data == 65);                  // checking node 75 children
        REQUIRE(tree.root->right->right == nullptr);
        REQUIRE(tree.root->left->left->left->data == 5);              // checking node 10 children
        REQUIRE(tree.root->left->left->right == nullptr);
        REQUIRE(tree.root->left->right->left == nullptr);                // checking node 26 children
        REQUIRE(tree.root->left->right->right == nullptr);
        REQUIRE(tree.root->right->left->left->data == 51);            // checking node 65 children
        REQUIRE(tree.root->right->left->right->data == 69);
        REQUIRE(tree.root->left->left->left->left->data == 1);        // checking node 5 children
        REQUIRE(tree.root->left->left->left->right->data == 6);
        REQUIRE(tree.root->right->left->left->left == nullptr);          // checking node 51 children
        REQUIRE(tree.root->right->left->left->right == nullptr);
        REQUIRE(tree.root->right->left->right->left == nullptr);         // checking node 69 children
        REQUIRE(tree.root->right->left->right->right == nullptr);
        REQUIRE(tree.root->left->left->left->left->left == nullptr);     // checking node 1 children
        REQUIRE(tree.root->left->left->left->left->right == nullptr);
        REQUIRE(tree.root->left->left->left->right->left == nullptr);    // checking node 6 children
        REQUIRE(tree.root->left->left->left->right->right == nullptr);
        INFO("after attempting to remove the value 60, BST numNodes should now be 11");
        REQUIRE(tree.numNodes == 11);
    }
    
    SECTION("verify that remove(x) successfully removes a node that has two children (successor IS right child)") {
        tree.remove(25);
        std::stringstream ss2;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss2);
        INFO("after attempting to remove the value 60");
        const char *treeString2 = "\n"
            "                ______________50______________\n"
            "               /                              \\\n"
            "        ______26                        ______75      \n"
            "       /                                /               \n"
            "    __10                            __60__                \n"
            "   /                               /      \\                \n"
            "  _5                              51      65                \n"
            " /  \\                                       \\                \n"
            " 1   6                                      69                \n";
        INFO("BST should now be: " << treeString2);
        INFO("Your BST is: " << ss2.str());
        REQUIRE(tree.root != nullptr);                                   // checking root node
        REQUIRE(tree.root->data == 50);
        REQUIRE(tree.root->left->data == 26);                         // checking node 50 children
        REQUIRE(tree.root->right->data == 75);
        REQUIRE(tree.root->left->left->data == 10);                   // checking node 26 children
        REQUIRE(tree.root->left->right == nullptr);
        REQUIRE(tree.root->right->left->data == 60);                  // checking node 75 children
        REQUIRE(tree.root->right->right == nullptr);
        REQUIRE(tree.root->left->left->left->data == 5);              // checking node 10 children
        REQUIRE(tree.root->left->left->right == nullptr);
        REQUIRE(tree.root->right->left->left->data == 51);            // checking node 60 children
        REQUIRE(tree.root->right->left->right->data == 65);
        REQUIRE(tree.root->left->left->left->left->data == 1);        // checking node 5 children
        REQUIRE(tree.root->left->left->left->right->data == 6);
        REQUIRE(tree.root->right->left->left->left == nullptr);          // checking node 51 children
        REQUIRE(tree.root->right->left->left->right == nullptr);
        REQUIRE(tree.root->right->left->right->left == nullptr);         // checking node 65 children
        REQUIRE(tree.root->right->left->right->right->data == 69);
        REQUIRE(tree.root->left->left->left->left->left == nullptr);     // checking node 1 children
        REQUIRE(tree.root->left->left->left->left->right == nullptr);
        REQUIRE(tree.root->left->left->left->right->left == nullptr);    // checking node 6 children
        REQUIRE(tree.root->left->left->left->right->right == nullptr);
        REQUIRE(tree.root->right->left->right->right->left == nullptr);  // checking node 69 children
        REQUIRE(tree.root->right->left->right->right->right == nullptr);
        INFO("after attempting to remove the value 60, BST numNodes should now be 11");
        REQUIRE(tree.numNodes == 11);
    }

    SECTION("verify that remove(x) successfully removes a node that is the root node (also successor has no children)") {
        tree.remove(50);
        std::stringstream ss2;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss2);
        INFO("after attempting to remove the value 50");
        const char *treeString2 = "\n"
            "                ______________51______________\n"
            "               /                              \\\n"
            "        ______25______                  ______75      \n"
            "       /              \\                /               \n"
            "    __10              26              60__                \n"
            "   /                                      \\                \n"
            "  _5                                      65                \n"
            " /  \\                                       \\                \n"
            " 1   6                                      69                \n";
        INFO("BST should now be: " << treeString2);
        INFO("Your BST is: " << ss2.str());
        REQUIRE(tree.root != nullptr);                                   // checking root node
        REQUIRE(tree.root->data == 51);
        REQUIRE(tree.root->left->data == 25);                         // checking node 51 children
        REQUIRE(tree.root->right->data == 75);
        REQUIRE(tree.root->left->left->data == 10);                   // checking node 25 children
        REQUIRE(tree.root->left->right->data == 26);
        REQUIRE(tree.root->right->left->data == 60);                  // checking node 75 children
        REQUIRE(tree.root->right->right == nullptr);
        REQUIRE(tree.root->left->left->left->data == 5);              // checking node 10 children
        REQUIRE(tree.root->left->left->right == nullptr);
        REQUIRE(tree.root->left->right->left == nullptr);                // checking node 26 children
        REQUIRE(tree.root->left->right->right == nullptr);
        REQUIRE(tree.root->right->left->left == nullptr);                // checking node 60 children
        REQUIRE(tree.root->right->left->right->data == 65);
        REQUIRE(tree.root->left->left->left->left->data == 1);        // checking node 5 children
        REQUIRE(tree.root->left->left->left->right->data == 6);
        REQUIRE(tree.root->right->left->right->left == nullptr);         // checking node 65 children
        REQUIRE(tree.root->right->left->right->right->data == 69);
        REQUIRE(tree.root->left->left->left->left->left == nullptr);     // checking node 1 children
        REQUIRE(tree.root->left->left->left->left->right == nullptr);
        REQUIRE(tree.root->left->left->left->right->left == nullptr);    // checking node 6 children
        REQUIRE(tree.root->left->left->left->right->right == nullptr);
        REQUIRE(tree.root->right->left->right->right->left == nullptr);  // checking node 69 children
        REQUIRE(tree.root->right->left->right->right->right == nullptr);
        INFO("after attempting to remove the value 50, BST numNodes should now be 11");
        REQUIRE(tree.numNodes == 11);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing makeEmpty() method on an empty BST", "[MAKEEMPTY]") {
    BST<int> tree;

    INFO("before calling makeEmpty(), BST should be empty [ root -> nullptr ]");
    REQUIRE(tree.root == nullptr);
    INFO("before calling makeEmpty(), BST numNodes should be 0");
    REQUIRE(tree.numNodes == 0);

    SECTION("verify that makeEmpty() doesn't break anything when BST is empty") {
        tree.makeEmpty();
        INFO("after calling makeEmpty(), BST should still be empty [ root -> nullptr ]");
        REQUIRE(tree.root == nullptr);
        INFO("after calling makeEmpty(), BST numNodes should still be 0");
        REQUIRE(tree.numNodes == 0);
    }
}


TEST_CASE("testing makeEmpty() method on a non-empty BST", "[MAKEEMPTY]") {
    BST<int> tree;
    tree.insert(4);
    tree.insert(3);
    tree.insert(5);
    std::stringstream ss;
    PrettyPrinter::printPretty(tree.root, 1, 0, ss);
    INFO("inserted values 4, 3, 5");
    const char *treeString = "\n"
        "  _4\n"
        " /  \\\n"
        " 3   5\n";
    INFO("before calling makeEmpty(), BST should be: " << treeString);
    INFO("Your BST is: " << ss.str());
    REQUIRE(tree.root != nullptr);                 // checking root node
    REQUIRE(tree.root->data == 4);
    REQUIRE(tree.root->left->data == 3);        // checking node 4 children
    REQUIRE(tree.root->right->data == 5);
    REQUIRE(tree.root->left->left == nullptr);     // checking node 3 children
    REQUIRE(tree.root->left->right == nullptr);
    REQUIRE(tree.root->right->left == nullptr);    // checking node 5 children
    REQUIRE(tree.root->right->right == nullptr);
    INFO("before calling makeEmpty(), BST numNodes should be 3");
    REQUIRE(tree.numNodes == 3);                // check the numNodes value

    SECTION("verify that makeEmpty() successfully empties BST and structure is correct") {
        tree.makeEmpty();
        INFO("after calling makeEmpty(), BST should be empty [ root -> nullptr ]");
        REQUIRE(tree.root == nullptr);
        INFO("after calling makeEmpty(), BST numNodes should be 0");
        REQUIRE(tree.numNodes == 0);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing findNode(n,x) method on an empty BST", "[FINDNODE]") {
    BST<int> tree;

    INFO("before calling findNode(n,x), BST should be empty [ root -> nullptr ]");
    REQUIRE(tree.root == nullptr);
    INFO("before calling findNode(n,x), BST numNodes should be 0");
    REQUIRE(tree.numNodes == 0);

    SECTION("verify that findNode(n,x) returns nullptr when BST is empty") {
        INFO("attempted to find a node containing the value 11");
        REQUIRE(tree.findNode(nullptr, 11) == nullptr);
    }
}


TEST_CASE("testing findNode(n,x) method on a non-empty BST", "[FINDNODE]") {
    BST<int> tree;
    tree.insert(50);
    tree.insert(75);
    tree.insert(25);
    tree.insert(10);
    tree.insert(5);
    tree.insert(1);
    tree.insert(6);
    tree.insert(26);
    tree.insert(60);
    tree.insert(51);
    tree.insert(65);
    tree.insert(69);
    std::stringstream ss;
    PrettyPrinter::printPretty(tree.root, 1, 0, ss);
    INFO("inserted values 50, 75, 25, 10, 5, 1, 6, 26, 60, 51, 65, 69");
    const char *treeString = "\n"
        "                ______________50______________\n"
        "               /                              \\\n"
        "        ______25______                  ______75      \n"
        "       /              \\                /               \n"
        "    __10              26            __60__                \n"
        "   /                               /      \\                \n"
        "  _5                              51      65                \n"
        " /  \\                                       \\                \n"
        " 1   6                                      69                \n";
    INFO("before calling findNode(n,x), BST should be: " << treeString);
    INFO("Your BST is: " << ss.str());
    INFO("before calling findNode(n,x), BST numNodes should be 12");
    REQUIRE(tree.numNodes == 12);

    SECTION("verify that findNode(root,x) returns nullptr when BST does not contain x") {
        INFO("should fail to find a node containing the value 49");
        REQUIRE(tree.findNode(tree.root, 49) == nullptr);
    }

    SECTION("verify that findNode(root, x) returns correct node when BST contains x in the root node") {
        INFO("should successfully find a node containing the value 50");
        REQUIRE(tree.findNode(tree.root, 50)->data == 50);
    }

    SECTION("verify that findNode(root,x) returns correct node when BST contains x in a leaf node") {
        INFO("should successfully find a node containing the value 69");
        REQUIRE(tree.findNode(tree.root, 69)->data == 69);
    }

    SECTION("verify that findNode(root, x) returns correct node when BST contains x in a middle node with two children") {
        INFO("should successfully find a node containing the value 25");
        REQUIRE(tree.findNode(tree.root, 25)->data == 25);
    }

    SECTION("verify that findNode(root, x) returns correct node when BST contains x in a middle node with single left child") {
        INFO("should successfully find a node containing the value 75");
        REQUIRE(tree.findNode(tree.root, 75)->data == 75);
    }

    SECTION("verify that findNode(root, x) returns correct node when BST contains x in a middle node with single right child") {
        INFO("should successfully find a node containing the value 65");
        REQUIRE(tree.findNode(tree.root, 65)->data == 65);
    }

    SECTION("verify that findNode(m,x) returns correct node when search starts at m and BST contains x in a leaf node") {
        INFO("should successfully find a node containing the value 6 starting from node 25");
        Node<int> *node = tree.findNode(tree.root, 25);
        REQUIRE(tree.findNode(node, 6)->data == 6);
    }

    SECTION("verify that findNode(m,x) returns nullptr when search starts at m and BST contains x in a higher node") {
        INFO("should fail to find a node containing the value 50 when starting from node 25");
        Node<int> *node = tree.findNode(tree.root, 25);
        REQUIRE(tree.findNode(node, 50) == nullptr);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing findMinNode(n) method on an empty BST", "[FINDMINNODE]") {
    BST<int> tree;

    INFO("before calling findMinNode(n), BST should be empty [ root -> nullptr ]");
    REQUIRE(tree.root == nullptr);
    INFO("before calling findMinNode(n), BST numNodes should be 0");
    REQUIRE(tree.numNodes == 0);

    SECTION("verify that findMinNode(n) returns nullptr when BST is empty") {
        REQUIRE(tree.findMinNode(nullptr) == nullptr);
    }
}


TEST_CASE("testing findMinNode(n) method on a non-empty BST", "[FINDMINNODE]") {
    BST<int> tree;
    tree.insert(50);
    tree.insert(75);
    tree.insert(25);
    tree.insert(10);
    tree.insert(5);
    tree.insert(1);
    tree.insert(6);
    tree.insert(26);
    tree.insert(60);
    tree.insert(51);
    tree.insert(65);
    tree.insert(69);
    std::stringstream ss;
    PrettyPrinter::printPretty(tree.root, 1, 0, ss);
    INFO("inserted values 50, 75, 25, 10, 5, 1, 6, 26, 60, 51, 65, 69");
    const char *treeString = "\n"
        "                ______________50______________\n"
        "               /                              \\\n"
        "        ______25______                  ______75      \n"
        "       /              \\                /               \n"
        "    __10              26            __60__                \n"
        "   /                               /      \\                \n"
        "  _5                              51      65                \n"
        " /  \\                                       \\                \n"
        " 1   6                                      69                \n";
    INFO("before calling findMinNode(n), BST should be: " << treeString);
    INFO("Your BST is: " << ss.str());
    INFO("before calling findMinNode(n), BST numNodes should be 12");
    REQUIRE(tree.numNodes == 12);
    
    SECTION("verify that findMinNode(n) returns correct node") {
        INFO("the findMinNode(n) method should return a node containing the value 1");
        REQUIRE(tree.findMinNode(tree.root)->data == 1);
    }

    SECTION("verify that findMinNode(n) returns correct node when search starts at node 25") {
        Node<int> *node25 = tree.findNode(tree.root, 25);
        INFO("the findMinNode(n) method should return a node containing the value 1 when starting from node 25");
        REQUIRE(tree.findMinNode(node25)->data == 1);
    }

    SECTION("verify that findMinNode(n) returns correct node when search starts at node 26") {
        Node<int> *node26 = tree.findNode(tree.root, 26);
        INFO("the findMinNode(n) method should return a node containing the value 26 when starting from node 26");
        REQUIRE(tree.findMinNode(node26)->data == 26);
    }

    SECTION("verify that findMinNode(n) returns correct node when search starts at node 60") {
        Node<int> *node60 = tree.findNode(tree.root, 60);
        INFO("the findMinNode(n) method should return a node containing the value 1 when starting from node 60");
        REQUIRE(tree.findMinNode(node60)->data == 51);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing findMaxNode(n) method on an empty BST", "[FINDMAXNODE]") {
    BST<int> tree;

    INFO("before calling findMaxNode(n), BST should be empty [ root -> nullptr ]");
    REQUIRE(tree.root == nullptr);
    INFO("before calling findMaxNode(n), BST numNodes should be 0");
    REQUIRE(tree.numNodes == 0);

    SECTION("verify that findMaxNode(n) returns nullptr when BST is empty") {
        REQUIRE(tree.findMaxNode(nullptr) == nullptr);
    }
}


TEST_CASE("testing findMaxNode(n) method on a non-empty BST", "[FINDMAXNODE]") {
    BST<int> tree;
    tree.insert(50);
    tree.insert(75);
    tree.insert(25);
    tree.insert(10);
    tree.insert(5);
    tree.insert(1);
    tree.insert(6);
    tree.insert(26);
    tree.insert(60);
    tree.insert(51);
    tree.insert(65);
    tree.insert(69);
    std::stringstream ss;
    PrettyPrinter::printPretty(tree.root, 1, 0, ss);
    INFO("inserted values 50, 75, 25, 10, 5, 1, 6, 26, 60, 51, 65, 69");
    const char *treeString = "\n"
        "                ______________50______________\n"
        "               /                              \\\n"
        "        ______25______                  ______75      \n"
        "       /              \\                /               \n"
        "    __10              26            __60__                \n"
        "   /                               /      \\                \n"
        "  _5                              51      65                \n"
        " /  \\                                       \\                \n"
        " 1   6                                      69                \n";
    INFO("before calling findMaxNode(n), BST should be: " << treeString);
    INFO("Your BST is: " << ss.str());
    INFO("before calling findMaxNode(n), BST numNodes should be 12");
    REQUIRE(tree.numNodes == 12);

    SECTION("verify that findMaxNode(n) returns correct node when search starts at root") {
        INFO("the findMaxNode(n) method should return a node containing the value 75");
        REQUIRE(tree.findMaxNode(tree.root)->data == 75);
    }

    SECTION("verify that findMaxNode(n) returns correct node when search starts at node 25") {
        Node<int> *node25 = tree.findNode(tree.root, 25);
        INFO("the findMaxNode(n) method should return a node containing the value 26 when starting from node 25");
        REQUIRE(tree.findMaxNode(node25)->data == 26);
    }

    SECTION("verify that findMaxNode(n) returns correct node when search starts at node 26") {
        Node<int> *node26 = tree.findNode(tree.root, 26);
        INFO("the findMaxNode(n) method should return a node containing the value 26 when starting from node 26");
        REQUIRE(tree.findMaxNode(node26)->data == 26);
    }

    SECTION("verify that findMaxNode(n) returns correct node when search starts at node 60") {
        Node<int> *node60 = tree.findNode(tree.root, 60);
        INFO("the findMaxNode(n) method should return a node containing the value 69 when starting from node 60");
        REQUIRE(tree.findMaxNode(node60)->data == 69);
    }
}


/* **************************************************************** */
/* **************************************************************** */



TEST_CASE("testing findSuccessor(n) method on a non-empty BST", "[FINDSUCCESSOR]") {
    BST<int> tree;
    tree.insert(50);
    tree.insert(75);
    tree.insert(25);
    tree.insert(10);
    tree.insert(5);
    tree.insert(1);
    tree.insert(6);
    tree.insert(26);
    tree.insert(60);
    tree.insert(51);
    tree.insert(65);
    tree.insert(69);
    std::stringstream ss;
    PrettyPrinter::printPretty(tree.root, 1, 0, ss);
    INFO("inserted values 50, 75, 25, 10, 5, 1, 6, 26, 60, 51, 65, 69");
    const char *treeString = "\n"
        "                ______________50______________\n"
        "               /                              \\\n"
        "        ______25______                  ______75      \n"
        "       /              \\                /               \n"
        "    __10              26            __60__                \n"
        "   /                               /      \\                \n"
        "  _5                              51      65                \n"
        " /  \\                                       \\                \n"
        " 1   6                                      69                \n";
    INFO("before calling findSuccessor(n), BST should be: " << treeString);
    INFO("Your BST is: " << ss.str());
    INFO("before calling findSuccessor(n), BST numNodes should be 12");
    REQUIRE(tree.numNodes == 12);
    
    SECTION("verify that findSuccessor(n) returns nullptr when node has no successor (node has no children)") {
        Node<int> *node26 = tree.findNode(tree.root, 26);
        INFO("should fail to find a successor for node 26 and return nullptr");
        REQUIRE(tree.findSuccessor(node26) == nullptr);
    }
    
    SECTION("verify that findSuccessor(n) returns nullptr when node has no successor (node has only left children)") {
        Node<int> *node10 = tree.findNode(tree.root, 10);
        INFO("should fail to find a successor for node 10 and return nullptr");
        REQUIRE(tree.findSuccessor(node10) == nullptr);
    }

    SECTION("verify that findSuccessor(n) returns correct node when successor is right child") {
        Node<int> *node60 = tree.findNode(tree.root, 60);
        INFO("should successfully find a successor for node 60 and return node containing value 65");
        REQUIRE(tree.findSuccessor(node60)->data == 65);
    }

    SECTION("verify that findSuccessor(n) returns correct node when successor is down left branch of right child") {
        INFO("should successfully find a successor for node 50 and return node containing value 51");
        REQUIRE(tree.findSuccessor(tree.root)->data == 51);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing findParentOf(x) method on an empty BST", "[FINDPARENTOF]") {
    BST<int> tree;

    INFO("before calling findParentOf(x), BST should be empty [ root -> nullptr ]");
    REQUIRE(tree.root == nullptr);
    INFO("before calling findParentOf(x), BST numNodes should be 0");
    REQUIRE(tree.numNodes == 0);

    SECTION("verify that findParentOf(n) returns nullptr when BST is empty") {
        REQUIRE(tree.findParentOf(999) == nullptr);
    }
}


TEST_CASE("testing findParentOf(x) method on a non-empty BST", "[FINDPARENTOF]") {
    BST<int> tree;
    tree.insert(50);
    tree.insert(75);
    tree.insert(25);
    tree.insert(10);
    tree.insert(5);
    tree.insert(1);
    tree.insert(6);
    tree.insert(26);
    tree.insert(60);
    tree.insert(51);
    tree.insert(65);
    tree.insert(69);
    std::stringstream ss;
    PrettyPrinter::printPretty(tree.root, 1, 0, ss);
    INFO("inserted values 50, 75, 25, 10, 5, 1, 6, 26, 60, 51, 65, 69");
    const char *treeString = "\n"
        "                ______________50______________\n"
        "               /                              \\\n"
        "        ______25______                  ______75      \n"
        "       /              \\                /               \n"
        "    __10              26            __60__                \n"
        "   /                               /      \\                \n"
        "  _5                              51      65                \n"
        " /  \\                                       \\                \n"
        " 1   6                                      69                \n";
    INFO("before calling findParentOf(x), BST should be: " << treeString);
    INFO("Your BST is: " << ss.str());
    INFO("before calling findParentOf(x), BST numNodes should be 12");
    REQUIRE(tree.numNodes == 12);
    
    SECTION("verify that findParentOf(x) returns nullptr when search starts at root (it has no parent)") {
        INFO("should return nullptr since root node has no parent");
        REQUIRE(tree.findParentOf(50) == nullptr);
    }

    SECTION("verify that findParentOf(x) returns correct node when searching for parent of leaf node") {
        INFO("should successfully find a parent for node 6 and return node containing value 5");
        REQUIRE(tree.findParentOf(6)->data == 5);
    }

    SECTION("verify that findParentOf(x) returns correct node when searching for parent of non-leaf node") {
        INFO("should successfully find a parent for node 60 and return node containing value 75");
        REQUIRE(tree.findParentOf(60)->data == 75);
    }
    
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing insertNode(n,x) method on an empty BST", "[INSERTNODE]") {
    BST<int> tree;

    INFO("before calling insertNode(n,x), BST should be empty [ root -> nullptr ]");
    REQUIRE(tree.root == nullptr);
    INFO("before calling insertNode(n,x), BST numNodes should be 0");
    REQUIRE(tree.numNodes == 0);

    SECTION("verify structure of BST after single insert into empty BST") {
        tree.root = tree.insertNode(tree.root, 4);
        std::stringstream ss;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss);
        INFO("inserted value 4");
        INFO("BST should be: \n 4\n");
        INFO("Your BST is: " << ss.str());
        REQUIRE(tree.root != nullptr);
        REQUIRE(tree.root->data == 4);
        REQUIRE(tree.root->left == nullptr);
        REQUIRE(tree.root->right == nullptr);
        INFO("after inserting a single value, BST numNodes should be 1");
        REQUIRE(tree.numNodes == 1);
    }

    SECTION("verify structure of BST after multiple inserts into empty BST") {
        INFO("insertNode(n,x) should return a reference to node n");
        tree.root = tree.insertNode(tree.root, 4);
        std::stringstream ss;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss);
        INFO("inserted value 4");
        INFO("BST should be: \n 4\n");
        INFO("Your BST is: " << ss.str());
        REQUIRE(tree.root != nullptr);             // checking root node
        REQUIRE(tree.root->data == 4);
        REQUIRE(tree.root->left == nullptr);       // checking node 4 children
        REQUIRE(tree.root->right == nullptr);
        INFO("after inserting single value, BST numNodes should be 1");
        REQUIRE(tree.numNodes == 1);
        
        tree.root = tree.insertNode(tree.root, 3);
        std::stringstream ss2;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss2);
        INFO("inserted values 4, 3");
        const char *treeString2 = "\n"
            "  _4\n"
            " /   \n"
            " 3    \n";
        INFO("BST should be: " << treeString2);
        INFO("Your BST is: " << ss2.str());
        REQUIRE(tree.root != nullptr);              // checking root node
        REQUIRE(tree.root->data == 4);
        REQUIRE(tree.root->left->data == 3);     // checking node 4 children
        REQUIRE(tree.root->right == nullptr);
        REQUIRE(tree.root->left->left == nullptr);  // checking node 3 children
        REQUIRE(tree.root->left->right == nullptr);
        INFO("after inserting two values, BST numNodes should be 2");
        REQUIRE(tree.numNodes == 2);
        
        tree.root = tree.insertNode(tree.root, 5);
        std::stringstream ss3;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss3);
        INFO("inserted values 4, 3, 5");
        const char *treeString3 = "\n"
            "  _4\n"
            " /  \\\n"
            " 3   5\n";
        INFO("BST should be: " << treeString3);
        INFO("Your BST is: " << ss3.str());
        REQUIRE(tree.root != nullptr);               // checking root node
        REQUIRE(tree.root->data == 4);
        REQUIRE(tree.root->left->data == 3);      // checking node 4 children
        REQUIRE(tree.root->right->data == 5);
        REQUIRE(tree.root->left->left == nullptr);   // checking node 3 children
        REQUIRE(tree.root->left->right == nullptr);
        REQUIRE(tree.root->right->left == nullptr);  // checking node 5 children
        REQUIRE(tree.root->right->right == nullptr);
        
        INFO("after inserting multiple values, BST numNodes should be 3");
        REQUIRE(tree.numNodes == 3);
    }
}


TEST_CASE("testing insertNode(n,x) method on a non-empty BST", "[INSERTNODE]") {
    BST<int> tree;
    
    SECTION("verify structure of BST after inserting into a non-empty BST (multiple inserts)") {
        tree.root = tree.insertNode(tree.root, 50);
        tree.insertNode(tree.root, 75);
        tree.insertNode(tree.root, 25);
        tree.insertNode(tree.root, 10);
        tree.insertNode(tree.root, 5);
        tree.insertNode(tree.root, 1);
        tree.insertNode(tree.root, 6);
        tree.insertNode(tree.root, 26);
        tree.insertNode(tree.root, 60);
        tree.insertNode(tree.root, 51);
        tree.insertNode(tree.root, 65);
        tree.insertNode(tree.root, 69);
        std::stringstream ss;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss);
        INFO("inserted values 50, 75, 25, 10, 5, 1, 6, 26, 60, 51, 65, 69");
        const char *treeString = "\n"
            "                ______________50______________\n"
            "               /                              \\\n"
            "        ______25______                  ______75      \n"
            "       /              \\                /               \n"
            "    __10              26            __60__                \n"
            "   /                               /      \\                \n"
            "  _5                              51      65                \n"
            " /  \\                                       \\                \n"
            " 1   6                                      69                \n";
        INFO("BST should be: " << treeString);
        INFO("Your BST is: " << ss.str());
        REQUIRE(tree.root != nullptr);                                   // checking root node
        REQUIRE(tree.root->data == 50);
        REQUIRE(tree.root->left->data == 25);                         // checking node 50 children
        REQUIRE(tree.root->right->data == 75);
        REQUIRE(tree.root->left->left->data == 10);                   // checking node 25 children
        REQUIRE(tree.root->left->right->data == 26);
        REQUIRE(tree.root->right->left->data == 60);                  // checking node 75 children
        REQUIRE(tree.root->right->right == nullptr);
        REQUIRE(tree.root->left->left->left->data == 5);              // checking node 10 children
        REQUIRE(tree.root->left->left->right == nullptr);
        REQUIRE(tree.root->left->right->left == nullptr);                // checking node 26 children
        REQUIRE(tree.root->left->right->right == nullptr);
        REQUIRE(tree.root->right->left->left->data == 51);            // checking node 60 children
        REQUIRE(tree.root->right->left->right->data == 65);
        REQUIRE(tree.root->left->left->left->left->data == 1);        // checking node 5 children
        REQUIRE(tree.root->left->left->left->right->data == 6);
        REQUIRE(tree.root->right->left->left->left == nullptr);          // checking node 51 children
        REQUIRE(tree.root->right->left->left->right == nullptr);
        REQUIRE(tree.root->right->left->right->left == nullptr);         // checking node 65 children
        REQUIRE(tree.root->right->left->right->right->data == 69);
        REQUIRE(tree.root->left->left->left->left->left == nullptr);     // checking node 1 children
        REQUIRE(tree.root->left->left->left->left->right == nullptr);
        REQUIRE(tree.root->left->left->left->right->left == nullptr);    // checking node 6 children
        REQUIRE(tree.root->left->left->left->right->right == nullptr);
        REQUIRE(tree.root->right->left->right->right->left == nullptr);  // checking node 69 children
        REQUIRE(tree.root->right->left->right->right->right == nullptr);
        INFO("after inserting multiple values, BST numNodes should be 12");
        REQUIRE(tree.numNodes == 12);
    }

    SECTION("verify structure of BST after calling insertNode(n,x) from middle node") {
        tree.insert(4);
        tree.insert(3);
        tree.insert(5);
        Node<int> *inputNode = tree.findNode(tree.root, 5);
        Node<int> *outputNode = tree.insertNode(inputNode, 9);
        INFO("insertNode(n,x) method should return same node that was passed in (unless nullptr was passed");
        REQUIRE(inputNode == outputNode);
        std::stringstream ss;
        PrettyPrinter::printPretty(tree.root, 1, 0, ss);
        INFO("inserted values 4, 3, 5, 9");
        const char *treeString = "\n"
            "    ___4__\n"
            "   /      \\\n"
            "   3       5\n"
            "            \\\n"
            "             9\n";
        INFO("BST should be: " << treeString);
        INFO("Your BST is: " << ss.str());
        REQUIRE(tree.root != nullptr);                      // checking root node
        REQUIRE(tree.root->data == 4);
        REQUIRE(tree.root->left->data == 3);             // checking node 4 children
        REQUIRE(tree.root->right->data == 5);
        REQUIRE(tree.root->left->left == nullptr);          // checking node 3 children
        REQUIRE(tree.root->left->right == nullptr);
        REQUIRE(tree.root->right->left == nullptr);         // checking node 5 children
        REQUIRE(tree.root->right->right->data == 9);
        REQUIRE(tree.root->right->right->left == nullptr);  // checking node 9 children
        REQUIRE(tree.root->right->right->right == nullptr);
        INFO("after inserting multiple values, BST numNodes should be 4");
        REQUIRE(tree.numNodes == 4);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing removeAllNodes(n) method on an empty BST", "[REMOVEALLNODES]") {
    BST<int> tree;

    INFO("before calling removeAllNodes(n), BST should be empty [ root -> nullptr ]");
    REQUIRE(tree.root == nullptr);
    INFO("before calling removeAllNodes(n), BST numNodes should be 0");
    REQUIRE(tree.numNodes == 0);

    SECTION("verify that removeAllNodes(n) doesn't break anything when BST is empty") {
        tree.removeAllNodes(tree.root);
        INFO("after calling removeAllNodes(n), BST should still be empty [ root -> nullptr ]");
        REQUIRE(tree.root == nullptr);
        INFO("after calling removeAllNodes(n), BST numNodes should still be 0");
        REQUIRE(tree.numNodes == 0);
    }
}


TEST_CASE("testing removeAllNodes(n) method on a non-empty BST", "[REMOVEALLNODES]") {
    BST<int> tree;
    tree.insert(50);
    tree.insert(75);
    tree.insert(25);
    tree.insert(10);
    tree.insert(5);
    tree.insert(1);
    tree.insert(6);
    tree.insert(26);
    tree.insert(60);
    tree.insert(51);
    tree.insert(65);
    tree.insert(69);
    std::stringstream ss;
    PrettyPrinter::printPretty(tree.root, 1, 0, ss);
    INFO("inserted values 50, 75, 25, 10, 5, 1, 6, 26, 60, 51, 65, 69");
    const char *treeString = "\n"
        "                ______________50______________\n"
        "               /                              \\\n"
        "        ______25______                  ______75      \n"
        "       /              \\                /               \n"
        "    __10              26            __60__                \n"
        "   /                               /      \\                \n"
        "  _5                              51      65                \n"
        " /  \\                                       \\                \n"
        " 1   6                                      69                \n";
    INFO("before calling removeAllNodes(n), BST should be: " << treeString);
    INFO("Your BST is: " << ss.str());
    INFO("before calling removeAllNodes(n), BST numNodes should be 12");
    REQUIRE(tree.numNodes == 12);

    SECTION("verify that removeAllNodes(n) successfully empties BST and structure is correct") {
        tree.removeAllNodes(tree.root);
        tree.root = nullptr;   // if root is not set to nullptr for this test case, then destructor will SEGFAULT!
        INFO("after calling removeAllNodes(n), BST numNodes should be 0");
        REQUIRE(tree.numNodes == 0);
    }
}


/* **************************************************************** */
/* **************************************************************** */



/* **************************************************************** */
/* **************************************************************** */
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
/* **************************************************************** */
/* **************************************************************** */


int main( int argc, char const* const* const argv )
{
    // global setup...
    std::cout << BOLDCYAN << std::endl;
    std::cout << "###############################################################################" << std::endl;
    std::cout << "############################# Running Unit Tests ##############################" << std::endl;
    std::cout << "###############################################################################" << std::endl;
    std::cout << RESET << std::endl;

    int result = Catch::Session().run( argc, argv );

    // global clean-up...
    std::cout << BOLDCYAN << std::endl;
    std::cout << "###############################################################################" << std::endl;
    std::cout << "########################### Done Running Unit Tests ###########################" << std::endl;
    std::cout << "###############################################################################" << std::endl;
    std::cout << RESET << std::endl;

    return result;
}
