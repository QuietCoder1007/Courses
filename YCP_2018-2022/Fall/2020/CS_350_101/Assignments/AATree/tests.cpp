//
//  tests.cpp
//

#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_CONSOLE_WIDTH 150

#include <iostream>
#include "AATree.h"
#include "catch.hpp"
#include "AATreePrettyPrinter.h"


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
    AATree<int> tree;
    
    SECTION("constructor must initialize bottomNode") {
        REQUIRE(tree.bottomNode != nullptr);
    }
    
    SECTION("constructor must initialize children of bottomNode") {
        INFO("left and right pointers of bottomNode should point back to bottomNode");
        REQUIRE(tree.bottomNode->left == tree.bottomNode);
        REQUIRE(tree.bottomNode->right == tree.bottomNode);
    }
    
    SECTION("constructor must initialize level of bottomNode") {
        INFO("level of bottomNode should be initialized to 0");
        REQUIRE(tree.bottomNode->level == 0);
    }
    
    SECTION("constructor must initialize data of bottomNode") {
        INFO("data of bottomNode should be initialized to -1");
        REQUIRE(tree.bottomNode->data == -1);
    }
    
    SECTION("constructor must assign bottomNode to root") {
        REQUIRE(tree.root == tree.bottomNode);
    }
    
    SECTION("constructor must assign bottomNode to lastNode") {
        REQUIRE(tree.lastNode == tree.bottomNode);
    }
    
    SECTION("constructor must assign bottomNode to deletedNode") {
        REQUIRE(tree.deletedNode == tree.bottomNode);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing isEmpty() method on an empty AATree", "[ISEMPTY]") {
    AATree<int> tree;
    
    INFO("root node should be same as bottomNode");
    REQUIRE(tree.root == tree.bottomNode);
    
    SECTION("verify return value of isEmpty()") {
        INFO("when empty, isEmpty() should return true");
        REQUIRE(tree.isEmpty() == true);
    }
}


TEST_CASE("testing isEmpty() method on a non-empty AATree", "[ISEMPTY]") {
    AATree<int> tree;

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


TEST_CASE("testing find(x) method on an empty AATree", "[FIND]") {
    AATree<int> tree;
    
    SECTION("verify that find(x) returns false when AATree is empty") {
        REQUIRE(tree.find(11) == false);
    }
}


TEST_CASE("testing find(x) method on a non-empty AATree", "[FIND]") {
    AATree<int> tree;
    tree.insert(15);
    tree.insert(6);
    tree.insert(18);
    tree.insert(3);
    tree.insert(7);
    tree.insert(20);
    tree.insert(2);
    tree.insert(4);
    tree.insert(13);
    tree.insert(9);
    std::stringstream ss;
    AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
    INFO("inserted values 15, 6, 18, 3, 7, 20, 2, 4, 13, 9");
    const char *treeString = "\n"
        "                       _____________________6.3______________________\n"
        "                      /                                              \\\n"
        "           _________3.2__________                          _________9.2__________\n"
        "          /                      \\                        /                      \\\n"
        "        2.1                     4.1                     7.1                  __15.2____\n"
        "                                                                            /          \\\n"
        "                                                                          13.1         18.1_\n"
        "                                                                                          \\\n"
        "                                                                                        20.1\n";
    INFO("before calling find(x), AATree should be: " << treeString);
    INFO("Your AATree is: " << ss.str());

    SECTION("verify that find(x) returns false when AATree does not contain x") {
        INFO("should fail to find the value 11");
        REQUIRE(tree.find(11) == false);
    }
    
    SECTION("verify that find(x) returns true when AATree contains x in the root node") {
        INFO("should successfully find the value 6");
        REQUIRE(tree.find(6) == true);
    }
    
    SECTION("verify that find(x) returns true when AATree contains x in a leaf node (left child)") {
        INFO("should successfully find the value 2");
        REQUIRE(tree.find(2) == true);
    }
    
    SECTION("verify that find(x) returns true when AATree contains x in a leaf node (right child)") {
        INFO("should successfully find the value 4");
        REQUIRE(tree.find(4) == true);
    }
    
    SECTION("verify that find(x) returns true when AATree contains x in a leaf node (right child, same level)") {
        INFO("should successfully find the value 20");
        REQUIRE(tree.find(20) == true);
    }
    
    SECTION("verify that find(x) returns true when AATree contains x in a middle node with two children") {
        INFO("should successfully find the value 3");
        REQUIRE(tree.find(3) == true);
    }
    
    SECTION("verify that find(x) returns true when AATree contains x in a middle node with single right child") {
        INFO("should successfully find the value 18");
        REQUIRE(tree.find(18) == true);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing findMin() method on an empty AATree", "[FINDMIN]") {
    AATree<int> tree;

    SECTION("verify that findMin() returns -1 when AATree is empty") {
        INFO("the findMin() method should return -1 when AATree is empty");
        REQUIRE(tree.findMin() == -1);
    }
}


TEST_CASE("testing findMin() method on a non-empty AATree", "[FINDMIN]") {
    AATree<int> tree;
    tree.insert(15);
    tree.insert(6);
    tree.insert(18);
    tree.insert(3);
    tree.insert(7);
    tree.insert(20);
    tree.insert(2);
    tree.insert(4);
    tree.insert(13);
    tree.insert(9);
    std::stringstream ss;
    AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
    INFO("inserted values 15, 6, 18, 3, 7, 20, 2, 4, 13, 9");
    const char *treeString = "\n"
        "                       _____________________6.3______________________\n"
        "                      /                                              \\\n"
        "           _________3.2__________                          _________9.2__________\n"
        "          /                      \\                        /                      \\\n"
        "        2.1                     4.1                     7.1                  __15.2____\n"
        "                                                                            /          \\\n"
        "                                                                          13.1         18.1_\n"
        "                                                                                          \\\n"
        "                                                                                        20.1\n";
    INFO("before calling findMin(), AATree should be: " << treeString);
    INFO("Your AATree is: " << ss.str());

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


TEST_CASE("testing findMax() method on an empty AATree", "[FINDMAX]") {
    AATree<int> tree;
    
    SECTION("verify that findMax() returns -1 when AATree is empty") {
        INFO("the findMax() method should return -1 when AATree is empty");
        REQUIRE(tree.findMax() == -1);
    }
}


TEST_CASE("testing findMax() method on a non-empty AATree", "[FINDMAX]") {
    AATree<int> tree;
    tree.insert(15);
    tree.insert(6);
    tree.insert(18);
    tree.insert(3);
    tree.insert(7);
    tree.insert(20);
    tree.insert(2);
    tree.insert(4);
    tree.insert(13);
    tree.insert(9);
    std::stringstream ss;
    AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
    INFO("inserted values 15, 6, 18, 3, 7, 20, 2, 4, 13, 9");
    const char *treeString = "\n"
        "                       _____________________6.3______________________\n"
        "                      /                                              \\\n"
        "           _________3.2__________                          _________9.2__________\n"
        "          /                      \\                        /                      \\\n"
        "        2.1                     4.1                     7.1                  __15.2____\n"
        "                                                                            /          \\\n"
        "                                                                          13.1         18.1_\n"
        "                                                                                          \\\n"
        "                                                                                        20.1\n";
    INFO("before calling findMax(), AATree should be: " << treeString);
    INFO("Your AATree is: " << ss.str());
    
    // may want to add tests to indicate that findMax works in all of the following cases:
    // 1) min is root node
    // 2) min is a leaf node
    // 3) min is an internal node with a single left child
    
    SECTION("verify that findMax() returns the correct value") {
        INFO("the findMax() method should return 20");
        REQUIRE(tree.findMax() == 20);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing insert(x) method on an empty AATree", "[INSERT]") {
    AATree<int> tree;

    SECTION("verify structure of AATree after single insert into empty AATree") {
        tree.insert(4);
        std::stringstream ss;
        AATreePrettyPrinter::printPretty(&tree, 1, 0, ss);
        INFO("inserted value 4");
        INFO("AATree should be: \n 4.1\n");
        INFO("Your AATree is: " << ss.str());
        
        REQUIRE(tree.root->data == 4);              // checking root node data
        REQUIRE(tree.root->level == 1);
        REQUIRE(tree.root->left == tree.bottomNode);
        REQUIRE(tree.root->right == tree.bottomNode);
    }
    
    SECTION("verify structure of AATree after two inserts into empty AATree (insert right child)") {
        tree.insert(4);
        tree.insert(5);
        std::stringstream ss;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
        INFO("inserted values 4, 5");
        const char *treeString = "\n"
            "  4.1_\n"
            "      \\\n"
            "     5.1\n";
        INFO("AATree should be: " << treeString);
        INFO("Your AATree is: " << ss.str());

        REQUIRE(tree.root->data == 4);                          // checking root node data
        REQUIRE(tree.root->level == 1);                         // checking node 4
        REQUIRE(tree.root->left == tree.bottomNode);
        REQUIRE(tree.root->right->data == 5);

        REQUIRE(tree.root->right->level == 1);                  // checking node 5
        REQUIRE(tree.root->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right == tree.bottomNode);
    }
    
    SECTION("verify structure of AATree after two inserts into empty AATree (insert left child and skew)") {
        tree.insert(4);
        tree.insert(3);
        std::stringstream ss;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
        INFO("inserted values 4, 3");
        const char *treeString = "\n"
            "  3.1_\n"
            "      \\\n"
            "     4.1\n";
        INFO("AATree should be: " << treeString);
        INFO("Your AATree is: " << ss.str());

        REQUIRE(tree.root->data == 3);                          // checking root node data
        REQUIRE(tree.root->level == 1);                         // checking node 3
        REQUIRE(tree.root->left == tree.bottomNode);
        REQUIRE(tree.root->right->data == 4);

        REQUIRE(tree.root->right->level == 1);                  // checking node 4
        REQUIRE(tree.root->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right == tree.bottomNode);
    }
    
    SECTION("verify structure of AATree after three inserts into empty AATree") {
        tree.insert(4);
        tree.insert(3);
        tree.insert(5);
        std::stringstream ss;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
        INFO("inserted values 4, 3, 5");
        const char *treeString = "\n"
            "  4.2_\n"
            " /    \\\n"
            "3.1   5.1\n";
        INFO("AATree should be: " << treeString);
        INFO("Your AATree is: " << ss.str());
        
        REQUIRE(tree.root->data == 4);                          // checking root node data
        REQUIRE(tree.root->level == 2);                         // checking node 4
        REQUIRE(tree.root->left->data == 3);
        REQUIRE(tree.root->right->data == 5);

        REQUIRE(tree.root->left->level == 1);                   // checking node 3
        REQUIRE(tree.root->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->right == tree.bottomNode);

        REQUIRE(tree.root->right->level == 1);                  // checking node 5
        REQUIRE(tree.root->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right == tree.bottomNode);
    }
}


TEST_CASE("testing insert(x) method on a non-empty AATree (multiple inserts)", "[INSERT]") {
    AATree<int> tree;

    SECTION("verify structure of AATree after inserting into a non-empty AATree (multiple inserts)") {
        tree.insert(4);
        tree.insert(10);
        tree.insert(2);
        tree.insert(6);
        tree.insert(12);
        tree.insert(3);
        tree.insert(1);
        tree.insert(8);
        tree.insert(13);
        tree.insert(11);
        tree.insert(5);
        tree.insert(9);
        tree.insert(7);
        std::stringstream ss;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
        INFO("inserted values 4, 10, 2, 6, 12, 3, 1, 8, 13, 11, 5, 9, 7");
        const char *treeString = "\n"
            "                       _____________________4.3______________________\n"
            "                      /                                              \\\n"
            "           _________2.2__________                          ________10.3__________\n"
            "          /                      \\                        /                      \\\n"
            "        1.1                     3.1                  ___6.2____              __12.2____\n"
            "                                                    /          \\            /          \\\n"
            "                                                  5.1         8.2_        11.1         13.1 \n"
            "                                                             /    \\                        \n"
            "                                                           7.1   9.1                        \n";
        INFO("AATree should be: " << treeString);
        INFO("Your AATree is: " << ss.str());
        
        REQUIRE(tree.root->data == 4);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 4
        REQUIRE(tree.root->left->data == 2);
        REQUIRE(tree.root->right->data == 10);

        REQUIRE(tree.root->left->level == 2);                                       // checking node 2
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 3);

        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 6);
        REQUIRE(tree.root->right->right->data == 12);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 3
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 6
        REQUIRE(tree.root->right->left->left->data == 5);
        REQUIRE(tree.root->right->left->right->data == 8);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 12
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 13);
        
        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 5
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 2);                         // checking node 8
        REQUIRE(tree.root->right->left->right->left->data == 7);
        REQUIRE(tree.root->right->left->right->right->data == 9);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 13
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->left->level == 1);                   // checking node 7
        REQUIRE(tree.root->right->left->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->right->level == 1);                  // checking node 9
        REQUIRE(tree.root->right->left->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right->right == tree.bottomNode);
    }
    
    SECTION("verify structure of AATree after attempting to insert duplicate nodes") {
        tree.insert(4);
        tree.insert(3);
        tree.insert(5);
        tree.insert(3);
        tree.insert(5);
        tree.insert(4);
        std::stringstream ss;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
        INFO("inserted values 4, 3, 5, 3 (again), 5 (again), 4 (again)");
        const char *treeString = "\n"
            "  4.2_\n"
            " /    \\\n"
            "3.1   5.1\n";
        INFO("AATree should be: " << treeString);
        INFO("Your AATree is: " << ss.str());
        
        REQUIRE(tree.root->data == 4);                          // checking root node data
        REQUIRE(tree.root->level == 2);                         // checking node 4
        REQUIRE(tree.root->left->data == 3);
        REQUIRE(tree.root->right->data == 5);
        
        REQUIRE(tree.root->left->level == 1);                   // checking node 3
        REQUIRE(tree.root->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->level == 1);                  // checking node 5
        REQUIRE(tree.root->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right == tree.bottomNode);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing remove(x) method on an empty AATree", "[REMOVE]") {
    AATree<int> tree;
    
    INFO("before calling remove(x), AATree should be empty [ root == bottomNode ]");
    REQUIRE(tree.root == tree.bottomNode);
    REQUIRE(tree.root->left == tree.bottomNode);
    REQUIRE(tree.root->right == tree.bottomNode);
    REQUIRE(tree.root->level == 0);
    REQUIRE(tree.root->data == -1);

    SECTION("verify that remove(x) doesn't break anything when AATree is empty") {
        tree.remove(11);
        INFO("after calling remove(x), AATree should be empty [ root == bottomNode ]");
        REQUIRE(tree.root == tree.bottomNode);
        REQUIRE(tree.root->left == tree.bottomNode);
        REQUIRE(tree.root->right == tree.bottomNode);
        REQUIRE(tree.root->level == 0);
        REQUIRE(tree.root->data == -1);
    }
}


TEST_CASE("testing remove(x) method on a non-empty AATree", "[REMOVE]") {
    AATree<int> tree;
    tree.insert(4);
    tree.insert(10);
    tree.insert(2);
    tree.insert(6);
    tree.insert(12);
    tree.insert(3);
    tree.insert(1);
    tree.insert(8);
    tree.insert(13);
    tree.insert(11);
    tree.insert(5);
    tree.insert(9);
    tree.insert(7);
    tree.insert(15);
    std::stringstream ss;
    AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
    INFO("inserted values 4, 10, 2, 6, 12, 3, 1, 8, 13, 11, 5, 9, 7, 15");
    const char *treeString = "\n"
        "                       _____________________4.3______________________\n"
        "                      /                                              \\\n"
        "           _________2.2__________                          ________10.3__________\n"
        "          /                      \\                        /                      \\\n"
        "        1.1                     3.1                  ___6.2____              __12.2____\n"
        "                                                    /          \\            /          \\\n"
        "                                                  5.1         8.2_        11.1         13.1_\n"
        "                                                             /    \\                       \\\n"
        "                                                           7.1   9.1                    15.1\n";
    INFO("AATree should be: " << treeString);
    INFO("Your AATree is: " << ss.str());
    
    SECTION("verify that remove(x) doesn't break anything when attempting to remove a value not in AATree") {
        tree.remove(0);
        tree.remove(14);
        tree.remove(16);
        std::stringstream ss2;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss2);
        INFO("after attempting to remove non-existent values: 0, 15, 16");
        INFO("AATree should still be: " << treeString);
        INFO("Your AATree is: " << ss2.str());
        
        REQUIRE(tree.root->data == 4);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 4
        REQUIRE(tree.root->left->data == 2);
        REQUIRE(tree.root->right->data == 10);
        
        REQUIRE(tree.root->left->level == 2);                                       // checking node 2
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 3);
        
        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 6);
        REQUIRE(tree.root->right->right->data == 12);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 3
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 6
        REQUIRE(tree.root->right->left->left->data == 5);
        REQUIRE(tree.root->right->left->right->data == 8);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 12
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 13);
        
        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 5
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 2);                         // checking node 8
        REQUIRE(tree.root->right->left->right->left->data == 7);
        REQUIRE(tree.root->right->left->right->right->data == 9);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 13
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->data == 15);
        
        REQUIRE(tree.root->right->left->right->left->level == 1);                   // checking node 7
        REQUIRE(tree.root->right->left->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->right->level == 1);                  // checking node 9
        REQUIRE(tree.root->right->left->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->right->level == 1);                 // checking node 15
        REQUIRE(tree.root->right->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->right == tree.bottomNode);
    }
    
    SECTION("verify that remove(x) successfully removes a node that has no children") {
        tree.remove(3);
        std::stringstream ss2;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss2);
        INFO("after attempting to remove the value 3");
        const char *treeString2 = "\n"
            "                       _____________________6.3______________________\n"
            "                      /                                              \\\n"
            "           _________4.2__________                          ________10.3__________\n"
            "          /                      \\                        /                      \\\n"
            "        1.1____                 5.1                  ___8.2____              __12.2____\n"
            "               \\                                    /          \\            /          \\\n"
            "              2.1                                 7.1         9.1         11.1         13.1_\n"
            "                                                                                          \\\n"
            "                                                                                        15.1\n";
        INFO("AATree should now be: " << treeString2);
        INFO("Your AATree is: " << ss2.str());
        
        REQUIRE(tree.root->data == 6);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 6
        REQUIRE(tree.root->left->data == 4);
        REQUIRE(tree.root->right->data == 10);
        
        REQUIRE(tree.root->left->level == 2);                                       // checking node 4
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 5);
        
        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 8);
        REQUIRE(tree.root->right->right->data == 12);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right->data == 2);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 5
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 8
        REQUIRE(tree.root->right->left->left->data == 7);
        REQUIRE(tree.root->right->left->right->data == 9);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 12
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 13);
        
        REQUIRE(tree.root->left->left->right->level == 1);                          // checking node 2
        REQUIRE(tree.root->left->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 7
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 1);                         // checking node 9
        REQUIRE(tree.root->right->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 13
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->data == 15);
        
        REQUIRE(tree.root->right->right->right->right->level == 1);                 // checking node 15
        REQUIRE(tree.root->right->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->right == tree.bottomNode);
    }
    
    SECTION("verify that remove(x) successfully removes a node that has one child (right child)") {
        tree.remove(13);
        std::stringstream ss2;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss2);
        INFO("after attempting to remove the value 13");
        const char *treeString2 = "\n"
            "                       _____________________4.3______________________\n"
            "                      /                                              \\\n"
            "           _________2.2__________                          ________10.3__________\n"
            "          /                      \\                        /                      \\\n"
            "        1.1                     3.1                  ___6.2____              __12.2____\n"
            "                                                    /          \\            /          \\\n"
            "                                                  5.1         8.2_        11.1         15.1 \n"
            "                                                             /    \\                        \n"
            "                                                           7.1   9.1                        \n";
        INFO("AATree should now be: " << treeString2);
        INFO("Your AATree is: " << ss2.str());
        
        REQUIRE(tree.root->data == 4);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 4
        REQUIRE(tree.root->left->data == 2);
        REQUIRE(tree.root->right->data == 10);
        
        REQUIRE(tree.root->left->level == 2);                                       // checking node 2
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 3);
        
        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 6);
        REQUIRE(tree.root->right->right->data == 12);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 3
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 6
        REQUIRE(tree.root->right->left->left->data == 5);
        REQUIRE(tree.root->right->left->right->data == 8);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 12
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 15);
        
        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 5
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 2);                         // checking node 8
        REQUIRE(tree.root->right->left->right->left->data == 7);
        REQUIRE(tree.root->right->left->right->right->data == 9);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 15
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->left->level == 1);                   // checking node 7
        REQUIRE(tree.root->right->left->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->right->level == 1);                  // checking node 9
        REQUIRE(tree.root->right->left->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right->right == tree.bottomNode);
    }
    
    SECTION("verify that remove(x) successfully removes a node that has two children") {
        tree.remove(2);
        std::stringstream ss2;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss2);
        INFO("after attempting to remove the value 2");
        const char *treeString2 = "\n"
            "                       _____________________6.3______________________\n"
            "                      /                                              \\\n"
            "           _________4.2__________                          ________10.3__________\n"
            "          /                      \\                        /                      \\\n"
            "        1.1____                 5.1                  ___8.2____              __12.2____\n"
            "               \\                                    /          \\            /          \\\n"
            "              3.1                                 7.1         9.1         11.1         13.1_\n"
            "                                                                                          \\\n"
            "                                                                                        15.1\n";
        INFO("AATree should now be: " << treeString2);
        INFO("Your AATree is: " << ss2.str());
        
        REQUIRE(tree.root->data == 6);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 6
        REQUIRE(tree.root->left->data == 4);
        REQUIRE(tree.root->right->data == 10);
        
        REQUIRE(tree.root->left->level == 2);                                       // checking node 4
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 5);
        
        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 8);
        REQUIRE(tree.root->right->right->data == 12);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right->data == 3);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 5
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 8
        REQUIRE(tree.root->right->left->left->data == 7);
        REQUIRE(tree.root->right->left->right->data == 9);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 12
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 13);

        REQUIRE(tree.root->left->left->right->level == 1);                          // checking node 3
        REQUIRE(tree.root->left->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right->right == tree.bottomNode);

        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 7
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 1);                         // checking node 9
        REQUIRE(tree.root->right->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 13
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->data == 15);
        
        REQUIRE(tree.root->right->right->right->right->level == 1);                 // checking node 15
        REQUIRE(tree.root->right->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->right == tree.bottomNode);
    }
    
    SECTION("verify that remove(x) successfully removes a node that has two children with right grandchild") {
        tree.remove(12);
        std::stringstream ss2;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss2);
        INFO("after attempting to remove the value 12");
        const char *treeString2 = "\n"
            "                       _____________________4.3______________________\n"
            "                      /                                              \\\n"
            "           _________2.2__________                          ________10.3__________\n"
            "          /                      \\                        /                      \\\n"
            "        1.1                     3.1                  ___6.2____              __13.2____\n"
            "                                                    /          \\            /          \\\n"
            "                                                  5.1         8.2_        11.1         15.1 \n"
            "                                                             /    \\                        \n"
            "                                                           7.1   9.1                        \n";
        INFO("AATree should now be: " << treeString2);
        INFO("Your AATree is: " << ss2.str());
        
        REQUIRE(tree.root->data == 4);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 4
        REQUIRE(tree.root->left->data == 2);
        REQUIRE(tree.root->right->data == 10);
        
        REQUIRE(tree.root->left->level == 2);                                       // checking node 2
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 3);
        
        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 6);
        REQUIRE(tree.root->right->right->data == 13);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 3
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 6
        REQUIRE(tree.root->right->left->left->data == 5);
        REQUIRE(tree.root->right->left->right->data == 8);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 13
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 15);
        
        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 5
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 2);                         // checking node 8
        REQUIRE(tree.root->right->left->right->left->data == 7);
        REQUIRE(tree.root->right->left->right->right->data == 9);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 15
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->left->level == 1);                   // checking node 7
        REQUIRE(tree.root->right->left->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->right->level == 1);                  // checking node 9
        REQUIRE(tree.root->right->left->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right->right == tree.bottomNode);
    }
    
    SECTION("verify that remove(x) successfully removes a node that is right grandchild") {
        tree.remove(15);
        std::stringstream ss2;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss2);
        INFO("after attempting to remove the value 15");
        const char *treeString2 = "\n"
            "                       _____________________4.3______________________\n"
            "                      /                                              \\\n"
            "           _________2.2__________                          ________10.3__________\n"
            "          /                      \\                        /                      \\\n"
            "        1.1                     3.1                  ___6.2____              __12.2____\n"
            "                                                    /          \\            /          \\\n"
            "                                                  5.1         8.2_        11.1         13.1 \n"
            "                                                             /    \\                        \n"
            "                                                           7.1   9.1                        \n";
        INFO("AATree should now be: " << treeString2);
        INFO("Your AATree is: " << ss2.str());
        
        REQUIRE(tree.root->data == 4);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 4
        REQUIRE(tree.root->left->data == 2);
        REQUIRE(tree.root->right->data == 10);
        
        REQUIRE(tree.root->left->level == 2);                                       // checking node 2
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 3);
        
        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 6);
        REQUIRE(tree.root->right->right->data == 12);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 3
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 6
        REQUIRE(tree.root->right->left->left->data == 5);
        REQUIRE(tree.root->right->left->right->data == 8);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 12
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 13);
        
        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 5
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 2);                         // checking node 8
        REQUIRE(tree.root->right->left->right->left->data == 7);
        REQUIRE(tree.root->right->left->right->right->data == 9);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 13
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->left->level == 1);                   // checking node 7
        REQUIRE(tree.root->right->left->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->right->level == 1);                  // checking node 9
        REQUIRE(tree.root->right->left->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right->right == tree.bottomNode);
    }
    
    SECTION("verify that remove(x) successfully removes a node that is the root node") {
        tree.remove(4);
        std::stringstream ss2;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss2);
        INFO("after attempting to remove the value 4");
        const char *treeString2 = "\n"
            "                       _____________________5.3______________________\n"
            "                      /                                              \\\n"
            "           _________2.2__________                          ________10.3__________\n"
            "          /                      \\                        /                      \\\n"
            "        1.1                     3.1                  ___7.2____              __12.2____\n"
            "                                                    /          \\            /          \\\n"
            "                                                  6.1         8.1_        11.1         13.1_\n"
            "                                                                  \\                       \\\n"
            "                                                                 9.1                    15.1\n";
        INFO("AATree should now be: " << treeString2);
        INFO("Your AATree is: " << ss2.str());
        
        REQUIRE(tree.root->data == 5);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 5
        REQUIRE(tree.root->left->data == 2);
        REQUIRE(tree.root->right->data == 10);
        
        REQUIRE(tree.root->left->level == 2);                                       // checking node 2
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 3);
        
        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 7);
        REQUIRE(tree.root->right->right->data == 12);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 3
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 7
        REQUIRE(tree.root->right->left->left->data == 6);
        REQUIRE(tree.root->right->left->right->data == 8);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 12
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 13);
        
        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 6
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 1);                         // checking node 8
        REQUIRE(tree.root->right->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right->data == 9);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 13
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->data == 15);
        
        REQUIRE(tree.root->right->left->right->right->level == 1);                  // checking node 9
        REQUIRE(tree.root->right->left->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->right->level == 1);                 // checking node 15
        REQUIRE(tree.root->right->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->right == tree.bottomNode);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing makeEmpty() method on an empty AATree", "[MAKEEMPTY]") {
    AATree<int> tree;

    INFO("before calling makeEmpty(), AATree should be empty [ root == bottomNode ]");
    REQUIRE(tree.root == tree.bottomNode);
    REQUIRE(tree.root->left == tree.bottomNode);
    REQUIRE(tree.root->right == tree.bottomNode);
    REQUIRE(tree.root->level == 0);
    REQUIRE(tree.root->data == -1);

    SECTION("verify that makeEmpty() doesn't break anything when AATree is empty") {
        tree.makeEmpty();
        INFO("after calling makeEmpty(), AATree should still be empty [ root == bottomNode ]");
        REQUIRE(tree.root == tree.bottomNode);
        REQUIRE(tree.root->left == tree.bottomNode);
        REQUIRE(tree.root->right == tree.bottomNode);
        REQUIRE(tree.root->level == 0);
        REQUIRE(tree.root->data == -1);
    }
}


TEST_CASE("testing makeEmpty() method on a non-empty AATree", "[MAKEEMPTY]") {
    AATree<int> tree;
    tree.insert(4);
    tree.insert(3);
    tree.insert(5);
    std::stringstream ss;
    AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
    INFO("inserted values 4, 3, 5");
    const char *treeString = "\n"
        "  4.2_\n"
        " /    \\\n"
        "3.1   5.1\n";
    INFO("before calling makeEmpty(), AATree should be: " << treeString);
    INFO("Your AATree is: " << ss.str());
    
    REQUIRE(tree.root->data == 4);                          // checking root node data
    REQUIRE(tree.root->level == 2);                         // checking node 4
    REQUIRE(tree.root->left->data == 3);
    REQUIRE(tree.root->right->data == 5);
    
    REQUIRE(tree.root->left->level == 1);                   // checking node 3
    REQUIRE(tree.root->left->left == tree.bottomNode);
    REQUIRE(tree.root->left->right == tree.bottomNode);

    REQUIRE(tree.root->right->level == 1);                  // checking node 5
    REQUIRE(tree.root->right->left == tree.bottomNode);
    REQUIRE(tree.root->right->right == tree.bottomNode);

    SECTION("verify that makeEmpty() successfully empties AATree and structure is correct") {
        tree.makeEmpty();
        INFO("after calling makeEmpty(), AATree should be empty [ root == bottomNode ]");
        REQUIRE(tree.root == tree.bottomNode);
        REQUIRE(tree.root->left == tree.bottomNode);
        REQUIRE(tree.root->right == tree.bottomNode);
        REQUIRE(tree.root->level == 0);
        REQUIRE(tree.root->data == -1);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing findNode(n,x) method on an empty AATree", "[FINDNODE]") {
    AATree<int> tree;
    
    INFO("before calling findNode(n,x), AATree should be empty [ root == bottomNode ]");
    REQUIRE(tree.root == tree.bottomNode);
    REQUIRE(tree.root->left == tree.bottomNode);
    REQUIRE(tree.root->right == tree.bottomNode);
    REQUIRE(tree.root->level == 0);
    REQUIRE(tree.root->data == -1);

    SECTION("verify that findNode(n,x) returns bottomNode when AATree is empty") {
        INFO("attempted to find a node containing the value 11");
        REQUIRE(tree.findNode(tree.root, 11) == tree.bottomNode);
    }
}


TEST_CASE("testing findNode(n,x) method on a non-empty AATree", "[FINDNODE]") {
    AATree<int> tree;
    tree.insert(15);
    tree.insert(6);
    tree.insert(18);
    tree.insert(3);
    tree.insert(7);
    tree.insert(20);
    tree.insert(2);
    tree.insert(4);
    tree.insert(13);
    tree.insert(9);
    std::stringstream ss;
    AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
    INFO("inserted values 15, 6, 18, 3, 7, 20, 2, 4, 13, 9");
    const char *treeString = "\n"
        "                       _____________________6.3______________________\n"
        "                      /                                              \\\n"
        "           _________3.2__________                          _________9.2__________\n"
        "          /                      \\                        /                      \\\n"
        "        2.1                     4.1                     7.1                  __15.2____\n"
        "                                                                            /          \\\n"
        "                                                                          13.1         18.1_\n"
        "                                                                                          \\\n"
        "                                                                                        20.1\n";
    INFO("before calling findNode(n,x), AATree should be: " << treeString);
    INFO("Your AATree is: " << ss.str());

    SECTION("verify that findNode(root,x) returns the bottomNode when AATree does not contain x") {
        INFO("should successfully find a node containing the value 49");
        REQUIRE(tree.findNode(tree.root, 49) == tree.bottomNode);
    }
    
    SECTION("verify that findNode(root, x) returns correct node when AATree contains x in the root node") {
        INFO("should successfully find a node containing the value 6");
        REQUIRE(tree.findNode(tree.root, 6)->data == 6);
    }
    
    SECTION("verify that findNode(root,x) returns correct node when AATree contains x in a leaf node (left child)") {
        INFO("should successfully find a node containing the value 13");
        REQUIRE(tree.findNode(tree.root, 13)->data == 13);
    }
    
    SECTION("verify that findNode(root,x) returns correct node when AATree contains x in a leaf node (right child)") {
        INFO("should successfully find a node containing the value 4");
        REQUIRE(tree.findNode(tree.root, 4)->data == 4);
    }
    
    SECTION("verify that findNode(root,x) returns correct node when AATree contains x in a leaf node (right child, same level)") {
        INFO("should successfully find a node containing the value 20");
        REQUIRE(tree.findNode(tree.root, 20)->data == 20);
    }
    
    SECTION("verify that findNode(root, x) returns correct node when AATree contains x in a middle node with two children") {
        INFO("should successfully find a node containing the value 9");
        REQUIRE(tree.findNode(tree.root, 9)->data == 9);
    }
    
    SECTION("verify that findNode(root, x) returns correct node when AATree contains x in a middle node with single right child") {
        INFO("should successfully find a node containing the value 18");
        REQUIRE(tree.findNode(tree.root, 18)->data == 18);
    }
    
    SECTION("verify that findNode(m,x) returns correct node when search starts at m and AATree contains x in a leaf node") {
        INFO("should successfully find a node containing the value 13 starting from node 9");
        Node<int> *node = tree.findNode(tree.root, 9);
        REQUIRE(tree.findNode(node, 13)->data == 13);
    }
    
    SECTION("verify that findNode(m,x) returns bottomNode when search starts at m and AATree contains x in a higher node") {
        INFO("should fail to find a node containing the value 50 when starting from node 25");
        Node<int> *node = tree.findNode(tree.root, 9);
        REQUIRE(tree.findNode(node, 6) == tree.bottomNode);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing findMinNode(n) method on an empty AATree", "[FINDMINNODE]") {
    AATree<int> tree;

    INFO("before calling findMinNode(n), AATree should be empty [ root == bottomNode ]");
    REQUIRE(tree.root == tree.bottomNode);
    REQUIRE(tree.root->left == tree.bottomNode);
    REQUIRE(tree.root->right == tree.bottomNode);
    REQUIRE(tree.root->level == 0);
    REQUIRE(tree.root->data == -1);

    SECTION("verify that findMinNode(n) returns bottomNode when AATree is empty") {
        REQUIRE(tree.findMinNode(tree.root) == tree.bottomNode);
        REQUIRE(tree.bottomNode->data == -1);
    }
}


TEST_CASE("testing findMinNode(n) method on a non-empty AATree", "[FINDMINNODE]") {
    AATree<int> tree;
    tree.insert(15);
    tree.insert(6);
    tree.insert(18);
    tree.insert(3);
    tree.insert(7);
    tree.insert(20);
    tree.insert(2);
    tree.insert(4);
    tree.insert(13);
    tree.insert(9);
    std::stringstream ss;
    AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
    INFO("inserted values 15, 6, 18, 3, 7, 20, 2, 4, 13, 9");
    const char *treeString = "\n"
        "                       _____________________6.3______________________\n"
        "                      /                                              \\\n"
        "           _________3.2__________                          _________9.2__________\n"
        "          /                      \\                        /                      \\\n"
        "        2.1                     4.1                     7.1                  __15.2____\n"
        "                                                                            /          \\\n"
        "                                                                          13.1         18.1_\n"
        "                                                                                          \\\n"
        "                                                                                        20.1\n";
    INFO("before calling findNode(n,x), AATree should be: " << treeString);
    INFO("Your AATree is: " << ss.str());

    SECTION("verify that findMinNode(n) returns correct node") {
        INFO("the findMinNode(n) method should return a node containing the value 2");
        REQUIRE(tree.findMinNode(tree.root)->data == 2);
    }
    
    SECTION("verify that findMinNode(n) returns correct node when search starts at node 9") {
        Node<int> *node9 = tree.findNode(tree.root, 9);
        INFO("the findMinNode(n) method should return a node containing the value 7 when starting from node 9");
        REQUIRE(tree.findMinNode(node9)->data == 7);
    }
    
    SECTION("verify that findMinNode(n) returns correct node when search starts at node 15") {
        Node<int> *node15 = tree.findNode(tree.root, 15);
        INFO("the findMinNode(n) method should return a node containing the value 13 when starting from node 15");
        REQUIRE(tree.findMinNode(node15)->data == 13);
    }
    
    SECTION("verify that findMinNode(n) returns correct node when search starts at node 18") {
        Node<int> *node18 = tree.findNode(tree.root, 18);
        INFO("the findMinNode(n) method should return a node containing the value 18 when starting from node 18");
        REQUIRE(tree.findMinNode(node18)->data == 18);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing findMaxNode(n) method on an empty AATree", "[FINDMAXNODE]") {
    AATree<int> tree;
    
    INFO("before calling findMaxNode(n), AATree should be empty [ root == bottomNode ]");
    REQUIRE(tree.root == tree.bottomNode);
    REQUIRE(tree.root->left == tree.bottomNode);
    REQUIRE(tree.root->right == tree.bottomNode);
    REQUIRE(tree.root->level == 0);
    REQUIRE(tree.root->data == -1);
    
    SECTION("verify that findMaxNode(n) returns bottomNode when AATree is empty") {
        REQUIRE(tree.findMaxNode(tree.root) == tree.bottomNode);
        REQUIRE(tree.bottomNode->data == -1);
    }
}


TEST_CASE("testing findMaxNode(n) method on a non-empty AATree", "[FINDMAXNODE]") {
    AATree<int> tree;
    tree.insert(15);
    tree.insert(6);
    tree.insert(18);
    tree.insert(3);
    tree.insert(7);
    tree.insert(20);
    tree.insert(2);
    tree.insert(4);
    tree.insert(13);
    tree.insert(9);
    std::stringstream ss;
    AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
    INFO("inserted values 15, 6, 18, 3, 7, 20, 2, 4, 13, 9");
    const char *treeString = "\n"
        "                       _____________________6.3______________________\n"
        "                      /                                              \\\n"
        "           _________3.2__________                          _________9.2__________\n"
        "          /                      \\                        /                      \\\n"
        "        2.1                     4.1                     7.1                  __15.2____\n"
        "                                                                            /          \\\n"
        "                                                                          13.1         18.1_\n"
        "                                                                                          \\\n"
        "                                                                                        20.1\n";
    INFO("before calling findNode(n,x), AATree should be: " << treeString);
    INFO("Your AATree is: " << ss.str());

    SECTION("verify that findMaxNode(n) returns correct node when search starts at root") {
        INFO("the findMaxNode(n) method should return a node containing the value 20");
        REQUIRE(tree.findMaxNode(tree.root)->data == 20);
    }
    
    SECTION("verify that findMaxNode(n) returns correct node when search starts at node 3") {
        Node<int> *node3 = tree.findNode(tree.root, 3);
        INFO("the findMaxNode(n) method should return a node containing the value 4 when starting from node 3");
        REQUIRE(tree.findMaxNode(node3)->data == 4);
    }
    
    SECTION("verify that findMaxNode(n) returns correct node when search starts at node 15") {
        Node<int> *node15 = tree.findNode(tree.root, 15);
        INFO("the findMaxNode(n) method should return a node containing the value 20 when starting from node 15");
        REQUIRE(tree.findMaxNode(node15)->data == 20);
    }
    
    SECTION("verify that findMaxNode(n) returns correct node when search starts at node 20") {
        Node<int> *node20 = tree.findNode(tree.root, 20);
        INFO("the findMaxNode(n) method should return a node containing the value 20 when starting from node 20");
        REQUIRE(tree.findMaxNode(node20)->data == 20);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing insertNode(n,x) method on an empty AATree", "[INSERTNODE]") {
    AATree<int> tree;

    INFO("before calling insertNode(n,x), AATree should be empty [ root == bottomNode ]");
    REQUIRE(tree.root == tree.bottomNode);
    REQUIRE(tree.root->left == tree.bottomNode);
    REQUIRE(tree.root->right == tree.bottomNode);
    REQUIRE(tree.root->level == 0);
    REQUIRE(tree.root->data == -1);
    

    SECTION("verify structure of AATree after single insert into empty AATree") {
        tree.insertNode(tree.root, 4);
        std::stringstream ss;
        AATreePrettyPrinter::printPretty(&tree, 1, 0, ss);
        INFO("inserted value 4");
        INFO("AATree should be: \n 4.1\n");
        INFO("Your AATree is: " << ss.str());
        
        REQUIRE(tree.root->data == 4);              // checking root node data
        REQUIRE(tree.root->level == 1);
        REQUIRE(tree.root->left == tree.bottomNode);
        REQUIRE(tree.root->right == tree.bottomNode);
    }
    
    SECTION("verify structure of AATree after two inserts into empty AATree (insert right child)") {
        tree.insertNode(tree.root, 4);
        tree.insertNode(tree.root, 5);
        std::stringstream ss;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
        INFO("inserted values 4, 5");
        const char *treeString = "\n"
            "  4.1_\n"
            "      \\\n"
            "     5.1\n";
        INFO("AATree should be: " << treeString);
        INFO("Your AATree is: " << ss.str());
        
        REQUIRE(tree.root->data == 4);                          // checking root node data
        REQUIRE(tree.root->level == 1);                         // checking node 4
        REQUIRE(tree.root->left == tree.bottomNode);
        REQUIRE(tree.root->right->data == 5);
        
        REQUIRE(tree.root->right->level == 1);                  // checking node 5
        REQUIRE(tree.root->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right == tree.bottomNode);
    }
    
    SECTION("verify structure of AATree after two inserts into empty AATree (insert left child and skew)") {
        tree.insertNode(tree.root, 4);
        tree.insertNode(tree.root, 3);
        std::stringstream ss;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
        INFO("inserted values 4, 3");
        const char *treeString = "\n"
            "  3.1_\n"
            "      \\\n"
            "     4.1\n";
        INFO("AATree should be: " << treeString);
        INFO("Your AATree is: " << ss.str());
        
        REQUIRE(tree.root->data == 3);                          // checking root node data
        REQUIRE(tree.root->level == 1);                         // checking node 3
        REQUIRE(tree.root->left == tree.bottomNode);
        REQUIRE(tree.root->right->data == 4);
        
        REQUIRE(tree.root->right->level == 1);                  // checking node 4
        REQUIRE(tree.root->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right == tree.bottomNode);
    }
    
    SECTION("verify structure of AATree after three inserts into empty AATree") {
        tree.insertNode(tree.root, 4);
        tree.insertNode(tree.root, 3);
        tree.insertNode(tree.root, 5);
        std::stringstream ss;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
        INFO("inserted values 4, 3, 5");
        const char *treeString = "\n"
            "  4.2_\n"
            " /    \\\n"
            "3.1   5.1\n";
        INFO("AATree should be: " << treeString);
        INFO("Your AATree is: " << ss.str());
        
        REQUIRE(tree.root->data == 4);                          // checking root node data
        REQUIRE(tree.root->level == 2);                         // checking node 4
        REQUIRE(tree.root->left->data == 3);
        REQUIRE(tree.root->right->data == 5);
        
        REQUIRE(tree.root->left->level == 1);                   // checking node 3
        REQUIRE(tree.root->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->level == 1);                  // checking node 5
        REQUIRE(tree.root->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right == tree.bottomNode);
    }
}


TEST_CASE("testing insertNode(n,x) method on a non-empty AATree (multiple inserts)", "[INSERTNODE]") {
    AATree<int> tree;
    
    SECTION("verify structure of AATree after inserting into a non-empty AATree (multiple inserts)") {
        tree.insertNode(tree.root, 4);
        tree.insertNode(tree.root, 10);
        tree.insertNode(tree.root, 2);
        tree.insertNode(tree.root, 6);
        tree.insertNode(tree.root, 12);
        tree.insertNode(tree.root, 3);
        tree.insertNode(tree.root, 1);
        tree.insertNode(tree.root, 8);
        tree.insertNode(tree.root, 13);
        tree.insertNode(tree.root, 11);
        tree.insertNode(tree.root, 5);
        tree.insertNode(tree.root, 9);
        tree.insertNode(tree.root, 7);
        std::stringstream ss;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
        INFO("inserted values 4, 10, 2, 6, 12, 3, 1, 8, 13, 11, 5, 9, 7");
        const char *treeString = "\n"
            "                       _____________________4.3______________________\n"
            "                      /                                              \\\n"
            "           _________2.2__________                          ________10.3__________\n"
            "          /                      \\                        /                      \\\n"
            "        1.1                     3.1                  ___6.2____              __12.2____\n"
            "                                                    /          \\            /          \\\n"
            "                                                  5.1         8.2_        11.1         13.1 \n"
            "                                                             /    \\                        \n"
            "                                                           7.1   9.1                        \n";
        INFO("AATree should be: " << treeString);
        INFO("Your AATree is: " << ss.str());
        
        REQUIRE(tree.root->data == 4);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 4
        REQUIRE(tree.root->left->data == 2);
        REQUIRE(tree.root->right->data == 10);
        
        REQUIRE(tree.root->left->level == 2);                                       // checking node 2
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 3);
        
        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 6);
        REQUIRE(tree.root->right->right->data == 12);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 3
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 6
        REQUIRE(tree.root->right->left->left->data == 5);
        REQUIRE(tree.root->right->left->right->data == 8);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 12
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 13);
        
        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 5
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 2);                         // checking node 8
        REQUIRE(tree.root->right->left->right->left->data == 7);
        REQUIRE(tree.root->right->left->right->right->data == 9);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 13
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->left->level == 1);                   // checking node 7
        REQUIRE(tree.root->right->left->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->right->level == 1);                  // checking node 9
        REQUIRE(tree.root->right->left->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right->right == tree.bottomNode);
    }
    
    SECTION("verify structure of AATree after attempting to insert duplicate nodes") {
        tree.insertNode(tree.root, 4);
        tree.insertNode(tree.root, 3);
        tree.insertNode(tree.root, 5);
        tree.insertNode(tree.root, 3);
        tree.insertNode(tree.root, 5);
        tree.insertNode(tree.root, 4);
        std::stringstream ss;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
        INFO("inserted values 4, 3, 5, 3 (again), 5 (again), 4 (again)");
        const char *treeString = "\n"
            "  4.2_\n"
            " /    \\\n"
            "3.1   5.1\n";
        INFO("AATree should be: " << treeString);
        INFO("Your AATree is: " << ss.str());
        
        REQUIRE(tree.root->data == 4);                          // checking root node data
        REQUIRE(tree.root->level == 2);                         // checking node 4
        REQUIRE(tree.root->left->data == 3);
        REQUIRE(tree.root->right->data == 5);
        
        REQUIRE(tree.root->left->level == 1);                   // checking node 3
        REQUIRE(tree.root->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->level == 1);                  // checking node 5
        REQUIRE(tree.root->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right == tree.bottomNode);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing removeNode(n,x) method on an empty AATree", "[REMOVENODE]") {
    AATree<int> tree;
    
    INFO("before calling removeNode(n,x), AATree should be empty [ root == bottomNode ]");
    REQUIRE(tree.root == tree.bottomNode);
    REQUIRE(tree.root->left == tree.bottomNode);
    REQUIRE(tree.root->right == tree.bottomNode);
    REQUIRE(tree.root->level == 0);
    REQUIRE(tree.root->data == -1);
    
    SECTION("verify that removeNode(n,x) doesn't break anything when AATree is empty") {
        tree.removeNode(tree.root, 11);
        INFO("after calling removeNode(n,x), AATree should be empty [ root == bottomNode ]");
        REQUIRE(tree.root == tree.bottomNode);
        REQUIRE(tree.root->left == tree.bottomNode);
        REQUIRE(tree.root->right == tree.bottomNode);
        REQUIRE(tree.root->level == 0);
        REQUIRE(tree.root->data == -1);
    }
}


TEST_CASE("testing removeNode(n,x) method on a non-empty AATree", "[REMOVENODE]") {
    AATree<int> tree;
    tree.insert(4);
    tree.insert(10);
    tree.insert(2);
    tree.insert(6);
    tree.insert(12);
    tree.insert(3);
    tree.insert(1);
    tree.insert(8);
    tree.insert(13);
    tree.insert(11);
    tree.insert(5);
    tree.insert(9);
    tree.insert(7);
    tree.insert(15);
    std::stringstream ss;
    AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
    INFO("inserted values 4, 10, 2, 6, 12, 3, 1, 8, 13, 11, 5, 9, 7, 15");
    const char *treeString = "\n"
        "                       _____________________4.3______________________\n"
        "                      /                                              \\\n"
        "           _________2.2__________                          ________10.3__________\n"
        "          /                      \\                        /                      \\\n"
        "        1.1                     3.1                  ___6.2____              __12.2____\n"
        "                                                    /          \\            /          \\\n"
        "                                                  5.1         8.2_        11.1         13.1_\n"
        "                                                             /    \\                       \\\n"
        "                                                           7.1   9.1                    15.1\n";
    INFO("AATree should be: " << treeString);
    INFO("Your AATree is: " << ss.str());
    
    SECTION("verify that removeNode(n,x) doesn't break anything when attempting to remove a value not in AATree") {
        tree.removeNode(tree.root, 0);
        tree.removeNode(tree.root, 14);
        tree.removeNode(tree.root, 16);
        std::stringstream ss2;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss2);
        INFO("after attempting to remove non-existent values: 0, 15, 16");
        INFO("AATree should still be: " << treeString);
        INFO("Your AATree is: " << ss2.str());
        
        REQUIRE(tree.root->data == 4);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 4
        REQUIRE(tree.root->left->data == 2);
        REQUIRE(tree.root->right->data == 10);
        
        REQUIRE(tree.root->left->level == 2);                                       // checking node 2
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 3);
        
        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 6);
        REQUIRE(tree.root->right->right->data == 12);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 3
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 6
        REQUIRE(tree.root->right->left->left->data == 5);
        REQUIRE(tree.root->right->left->right->data == 8);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 12
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 13);
        
        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 5
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 2);                         // checking node 8
        REQUIRE(tree.root->right->left->right->left->data == 7);
        REQUIRE(tree.root->right->left->right->right->data == 9);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 13
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->data == 15);
        
        REQUIRE(tree.root->right->left->right->left->level == 1);                   // checking node 7
        REQUIRE(tree.root->right->left->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->right->level == 1);                  // checking node 9
        REQUIRE(tree.root->right->left->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->right->level == 1);                 // checking node 15
        REQUIRE(tree.root->right->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->right == tree.bottomNode);
    }
    
    SECTION("verify that removeNode(n,x) successfully removes a node that has no children") {
        tree.removeNode(tree.root, 3);
        std::stringstream ss2;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss2);
        INFO("after attempting to remove the value 3");
        const char *treeString2 = "\n"
            "                       _____________________6.3______________________\n"
            "                      /                                              \\\n"
            "           _________4.2__________                          ________10.3__________\n"
            "          /                      \\                        /                      \\\n"
            "        1.1____                 5.1                  ___8.2____              __12.2____\n"
            "               \\                                    /          \\            /          \\\n"
            "              2.1                                 7.1         9.1         11.1         13.1_\n"
            "                                                                                          \\\n"
            "                                                                                        15.1\n";
        INFO("AATree should now be: " << treeString2);
        INFO("Your AATree is: " << ss2.str());
        
        REQUIRE(tree.root->data == 6);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 6
        REQUIRE(tree.root->left->data == 4);
        REQUIRE(tree.root->right->data == 10);
        
        REQUIRE(tree.root->left->level == 2);                                       // checking node 4
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 5);
        
        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 8);
        REQUIRE(tree.root->right->right->data == 12);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right->data == 2);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 5
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 8
        REQUIRE(tree.root->right->left->left->data == 7);
        REQUIRE(tree.root->right->left->right->data == 9);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 12
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 13);
        
        REQUIRE(tree.root->left->left->right->level == 1);                          // checking node 2
        REQUIRE(tree.root->left->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 7
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 1);                         // checking node 9
        REQUIRE(tree.root->right->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 13
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->data == 15);
        
        REQUIRE(tree.root->right->right->right->right->level == 1);                 // checking node 15
        REQUIRE(tree.root->right->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->right == tree.bottomNode);
    }
    
    SECTION("verify that removeNode(n,x) successfully removes a node that has one child (right child)") {
        tree.removeNode(tree.root, 13);
        std::stringstream ss2;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss2);
        INFO("after attempting to remove the value 13");
        const char *treeString2 = "\n"
            "                       _____________________4.3______________________\n"
            "                      /                                              \\\n"
            "           _________2.2__________                          ________10.3__________\n"
            "          /                      \\                        /                      \\\n"
            "        1.1                     3.1                  ___6.2____              __12.2____\n"
            "                                                    /          \\            /          \\\n"
            "                                                  5.1         8.2_        11.1         15.1 \n"
            "                                                             /    \\                        \n"
            "                                                           7.1   9.1                        \n";
        INFO("AATree should now be: " << treeString2);
        INFO("Your AATree is: " << ss2.str());
        
        REQUIRE(tree.root->data == 4);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 4
        REQUIRE(tree.root->left->data == 2);
        REQUIRE(tree.root->right->data == 10);
        
        REQUIRE(tree.root->left->level == 2);                                       // checking node 2
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 3);
        
        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 6);
        REQUIRE(tree.root->right->right->data == 12);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 3
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 6
        REQUIRE(tree.root->right->left->left->data == 5);
        REQUIRE(tree.root->right->left->right->data == 8);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 12
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 15);
        
        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 5
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 2);                         // checking node 8
        REQUIRE(tree.root->right->left->right->left->data == 7);
        REQUIRE(tree.root->right->left->right->right->data == 9);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 15
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->left->level == 1);                   // checking node 7
        REQUIRE(tree.root->right->left->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->right->level == 1);                  // checking node 9
        REQUIRE(tree.root->right->left->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right->right == tree.bottomNode);
    }
    
    SECTION("verify that removeNode(n,x) successfully removes a node that has two children") {
        tree.removeNode(tree.root, 2);
        std::stringstream ss2;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss2);
        INFO("after attempting to remove the value 2");
        const char *treeString2 = "\n"
            "                       _____________________6.3______________________\n"
            "                      /                                              \\\n"
            "           _________4.2__________                          ________10.3__________\n"
            "          /                      \\                        /                      \\\n"
            "        1.1____                 5.1                  ___8.2____              __12.2____\n"
            "               \\                                    /          \\            /          \\\n"
            "              3.1                                 7.1         9.1         11.1         13.1_\n"
            "                                                                                          \\\n"
            "                                                                                        15.1\n";
        INFO("AATree should now be: " << treeString2);
        INFO("Your AATree is: " << ss2.str());
        
        REQUIRE(tree.root->data == 6);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 6
        REQUIRE(tree.root->left->data == 4);
        REQUIRE(tree.root->right->data == 10);
        
        REQUIRE(tree.root->left->level == 2);                                       // checking node 4
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 5);
        
        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 8);
        REQUIRE(tree.root->right->right->data == 12);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right->data == 3);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 5
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 8
        REQUIRE(tree.root->right->left->left->data == 7);
        REQUIRE(tree.root->right->left->right->data == 9);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 12
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 13);
        
        REQUIRE(tree.root->left->left->right->level == 1);                          // checking node 3
        REQUIRE(tree.root->left->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 7
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 1);                         // checking node 9
        REQUIRE(tree.root->right->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 13
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->data == 15);
        
        REQUIRE(tree.root->right->right->right->right->level == 1);                 // checking node 15
        REQUIRE(tree.root->right->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->right == tree.bottomNode);
    }
    
    SECTION("verify that removeNode(n,x) successfully removes a node that has two children with right grandchild") {
        tree.removeNode(tree.root, 12);
        std::stringstream ss2;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss2);
        INFO("after attempting to remove the value 12");
        const char *treeString2 = "\n"
            "                       _____________________4.3______________________\n"
            "                      /                                              \\\n"
            "           _________2.2__________                          ________10.3__________\n"
            "          /                      \\                        /                      \\\n"
            "        1.1                     3.1                  ___6.2____              __13.2____\n"
            "                                                    /          \\            /          \\\n"
            "                                                  5.1         8.2_        11.1         15.1 \n"
            "                                                             /    \\                        \n"
            "                                                           7.1   9.1                        \n";
        INFO("AATree should now be: " << treeString2);
        INFO("Your AATree is: " << ss2.str());
        
        REQUIRE(tree.root->data == 4);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 4
        REQUIRE(tree.root->left->data == 2);
        REQUIRE(tree.root->right->data == 10);
        
        REQUIRE(tree.root->left->level == 2);                                       // checking node 2
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 3);
        
        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 6);
        REQUIRE(tree.root->right->right->data == 13);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 3
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 6
        REQUIRE(tree.root->right->left->left->data == 5);
        REQUIRE(tree.root->right->left->right->data == 8);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 13
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 15);
        
        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 5
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 2);                         // checking node 8
        REQUIRE(tree.root->right->left->right->left->data == 7);
        REQUIRE(tree.root->right->left->right->right->data == 9);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 15
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->left->level == 1);                   // checking node 7
        REQUIRE(tree.root->right->left->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->right->level == 1);                  // checking node 9
        REQUIRE(tree.root->right->left->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right->right == tree.bottomNode);
    }
    
    SECTION("verify that removeNode(n,x) successfully removes a node that is right grandchild") {
        tree.removeNode(tree.root, 15);
        std::stringstream ss2;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss2);
        INFO("after attempting to remove the value 15");
        const char *treeString2 = "\n"
            "                       _____________________4.3______________________\n"
            "                      /                                              \\\n"
            "           _________2.2__________                          ________10.3__________\n"
            "          /                      \\                        /                      \\\n"
            "        1.1                     3.1                  ___6.2____              __12.2____\n"
            "                                                    /          \\            /          \\\n"
            "                                                  5.1         8.2_        11.1         13.1 \n"
            "                                                             /    \\                        \n"
            "                                                           7.1   9.1                        \n";
        INFO("AATree should now be: " << treeString2);
        INFO("Your AATree is: " << ss2.str());
        
        REQUIRE(tree.root->data == 4);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 4
        REQUIRE(tree.root->left->data == 2);
        REQUIRE(tree.root->right->data == 10);
        
        REQUIRE(tree.root->left->level == 2);                                       // checking node 2
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 3);
        
        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 6);
        REQUIRE(tree.root->right->right->data == 12);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 3
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 6
        REQUIRE(tree.root->right->left->left->data == 5);
        REQUIRE(tree.root->right->left->right->data == 8);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 12
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 13);
        
        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 5
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 2);                         // checking node 8
        REQUIRE(tree.root->right->left->right->left->data == 7);
        REQUIRE(tree.root->right->left->right->right->data == 9);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 13
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->left->level == 1);                   // checking node 7
        REQUIRE(tree.root->right->left->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->right->level == 1);                  // checking node 9
        REQUIRE(tree.root->right->left->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right->right == tree.bottomNode);
    }
    
    SECTION("verify that removeNode(n,x) successfully removes a node that is the root node") {
        tree.removeNode(tree.root, 4);
        std::stringstream ss2;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss2);
        INFO("after attempting to remove the value 4");
        const char *treeString2 = "\n"
            "                       _____________________5.3______________________\n"
            "                      /                                              \\\n"
            "           _________2.2__________                          ________10.3__________\n"
            "          /                      \\                        /                      \\\n"
            "        1.1                     3.1                  ___7.2____              __12.2____\n"
            "                                                    /          \\            /          \\\n"
            "                                                  6.1         8.1_        11.1         13.1_\n"
            "                                                                  \\                       \\\n"
            "                                                                 9.1                    15.1\n";
        INFO("AATree should now be: " << treeString2);
        INFO("Your AATree is: " << ss2.str());
        
        REQUIRE(tree.root->data == 5);                                              // checking root node data
        REQUIRE(tree.root->level == 3);                                             // checking node 5
        REQUIRE(tree.root->left->data == 2);
        REQUIRE(tree.root->right->data == 10);
        
        REQUIRE(tree.root->left->level == 2);                                       // checking node 2
        REQUIRE(tree.root->left->left->data == 1);
        REQUIRE(tree.root->left->right->data == 3);
        
        REQUIRE(tree.root->right->level == 3);                                      // checking node 10
        REQUIRE(tree.root->right->left->data == 7);
        REQUIRE(tree.root->right->right->data == 12);
        
        REQUIRE(tree.root->left->left->level == 1);                                 // checking node 1
        REQUIRE(tree.root->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->left->right->level == 1);                                // checking node 3
        REQUIRE(tree.root->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->left->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->level == 2);                                // checking node 7
        REQUIRE(tree.root->right->left->left->data == 6);
        REQUIRE(tree.root->right->left->right->data == 8);
        
        REQUIRE(tree.root->right->right->level == 2);                               // checking node 12
        REQUIRE(tree.root->right->right->left->data == 11);
        REQUIRE(tree.root->right->right->right->data == 13);
        
        REQUIRE(tree.root->right->left->left->level == 1);                          // checking node 6
        REQUIRE(tree.root->right->left->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->left->right->level == 1);                         // checking node 8
        REQUIRE(tree.root->right->left->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right->data == 9);
        
        REQUIRE(tree.root->right->right->left->level == 1);                         // checking node 11
        REQUIRE(tree.root->right->right->left->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->left->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->level == 1);                        // checking node 13
        REQUIRE(tree.root->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->data == 15);
        
        REQUIRE(tree.root->right->left->right->right->level == 1);                  // checking node 9
        REQUIRE(tree.root->right->left->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->left->right->right->right == tree.bottomNode);
        
        REQUIRE(tree.root->right->right->right->right->level == 1);                 // checking node 15
        REQUIRE(tree.root->right->right->right->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right->right->right->right == tree.bottomNode);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing skew(n) method on a node", "[SKEW]") {
    AATree<int> tree;
    tree.insert(4);
    Node<int> *n = new Node<int>(3, tree.bottomNode, tree.bottomNode, 1);
    tree.root->left = n;
    
    INFO("before calling skew(n), AATree should contain two nodes: a root node (node 4) and its ILLEGAL left child (node 3)");
    const char *treeString = "\n"
        "  4.1 \n"
        " /     \n"
        "3.1      \n";
    INFO("before calling skew(n), AATree is: " << treeString);
    REQUIRE(tree.root->data == 4);                          // checking root node
    REQUIRE(tree.root->level == 1);                         // checking ndoe 4
    REQUIRE(tree.root->left->data == 3);
    REQUIRE(tree.root->right == tree.bottomNode);
    REQUIRE(tree.root->left->level == 1);                   // checking node 3
    REQUIRE(tree.root->left->left == tree.bottomNode);
    REQUIRE(tree.root->left->right == tree.bottomNode);
    REQUIRE(tree.bottomNode->data == -1);                   // checking bottomNode
    REQUIRE(tree.bottomNode->level == 0);
    
    SECTION("verify that skew(n) successfully adjusts AATree") {
        tree.skew(tree.root);
        std::stringstream ss;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
        INFO("after calling skew(n), AATree should contain two nodes: a root node (node 3) and its LEGAL right child (node 4)");
        const char *treeString2 = "\n"
            "  3.1_\n"
            "      \\\n"
            "     4.1\n";
        INFO("after calling skew(n), AATree should be: " << treeString2);
        INFO("Your AATree is: " << ss.str());
        REQUIRE(tree.root->data == 3);                      // checking root node
        REQUIRE(tree.root->level == 1);                     // checking node 3
        REQUIRE(tree.root->left == tree.bottomNode);
        REQUIRE(tree.root->right->data == 4);
        REQUIRE(tree.root->right->level == 1);              // checking node 4
        REQUIRE(tree.root->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right == tree.bottomNode);
        REQUIRE(tree.bottomNode->data == -1);               // checking bottomNode
        REQUIRE(tree.bottomNode->level == 0);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing split(n) method on a node", "[SPLIT]") {
    AATree<int> tree;
    tree.insert(3);
    tree.insert(4);
    Node<int> *n = new Node<int>(5, tree.bottomNode, tree.bottomNode, 1);
    tree.root->right->right = n;
    
    INFO("before calling split(n), AATree should contain three nodes: a root node (node 3), its right child (node 4), and an ILLEGAL right grandchild (node 5)");
    const char *treeString = "\n"
        "    3.1____\n"
        "           \\\n"
        "          4.1_\n"
        "              \\\n"
        "             5.1\n";
    INFO("before calling split(n), AATree is: " << treeString);
    
    REQUIRE(tree.root->data == 3);                              // checking root node
    REQUIRE(tree.root->level == 1);                             // checking node 3
    REQUIRE(tree.root->left == tree.bottomNode);
    REQUIRE(tree.root->right->data == 4);
    REQUIRE(tree.root->right->level == 1);                      // checking node 4
    REQUIRE(tree.root->right->left == tree.bottomNode);
    REQUIRE(tree.root->right->right->data == 5);
    REQUIRE(tree.root->right->right->level == 1);               // checking node 5
    REQUIRE(tree.root->right->right->left == tree.bottomNode);
    REQUIRE(tree.root->right->right->right == tree.bottomNode);
    REQUIRE(tree.bottomNode->data == -1);                       // checking bottomNode
    REQUIRE(tree.bottomNode->level == 0);
    
    SECTION("verify that split(n) successfully adjusts AATree") {
        tree.split(tree.root);
        std::stringstream ss;
        AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
        INFO("after calling split(n), AATree should contain three nodes: a root node (node 4), its left child (node 3), and its right child (node 5)");
        const char *treeString2 ="\n"
            "  4.2_\n"
            " /    \\\n"
            "3.1   5.1\n";
        INFO("after calling split(n), AATree should be: " << treeString2);
        INFO("Your AATree is: " << ss.str());
        REQUIRE(tree.root->data == 4);                              // checking root node
        REQUIRE(tree.root->level == 2);                             // checking node 4
        REQUIRE(tree.root->left->data == 3);
        REQUIRE(tree.root->right->data == 5);
        REQUIRE(tree.root->left->level == 1);                       // checking node 3
        REQUIRE(tree.root->left->left == tree.bottomNode);
        REQUIRE(tree.root->left->right == tree.bottomNode);
        REQUIRE(tree.root->right->level == 1);                      // checking node 5
        REQUIRE(tree.root->right->left == tree.bottomNode);
        REQUIRE(tree.root->right->right == tree.bottomNode);
        REQUIRE(tree.bottomNode->data == -1);                       // checking bottomNode
        REQUIRE(tree.bottomNode->level == 0);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing removeAllNodes(n) method on an empty AATree", "[REMOVEALLNODES]") {
    AATree<int> tree;
    
    INFO("before calling removeAllNodes(n), AATree should be empty [ root == bottomNode ]");
    REQUIRE(tree.root == tree.bottomNode);
    REQUIRE(tree.root->left == tree.bottomNode);
    REQUIRE(tree.root->right == tree.bottomNode);
    REQUIRE(tree.root->level == 0);
    REQUIRE(tree.root->data == -1);
    
    SECTION("verify that removeAllNodes(n) doesn't break anything when AATree is empty") {
        tree.removeAllNodes(tree.root);
        INFO("after calling removeAllNodes(n), AATree should be empty [ root == bottomNode ]");
        REQUIRE(tree.root == tree.bottomNode);
        REQUIRE(tree.root->left == tree.bottomNode);
        REQUIRE(tree.root->right == tree.bottomNode);
        REQUIRE(tree.root->level == 0);
        REQUIRE(tree.root->data == -1);
    }
}


TEST_CASE("testing removeAllNodes(n) method on a non-empty AATree", "[REMOVEALLNODES]") {
    AATree<int> tree;
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
    AATreePrettyPrinter::printPretty(&tree, 2, 0, ss);
    INFO("inserted values 50, 75, 25, 10, 5, 1, 6, 26, 60, 51, 65, 69");
    const char *treeString = "\n"
        "                       ____________________10.3______________________\n"
        "                      /                                              \\\n"
        "           _________5.2__________                          ________60.3__________\n"
        "          /                      \\                        /                      \\\n"
        "        1.1                     6.1                  __50.2____              __69.2____\n"
        "                                                    /          \\            /          \\\n"
        "                                                  25.1_        51.1         65.1         75.1 \n"
        "                                                      \\                                    \n"
        "                                                    26.1                                    \n";
    INFO("before calling removeAllNodes(n), AATree should be: " << treeString);
    INFO("Your AATree is: " << ss.str());

    SECTION("verify that removeAllNodes(n) successfully empties AATree and structure is correct") {
        tree.removeAllNodes(tree.root);
        tree.root = tree.bottomNode;  // if root is not set to bottomNode for this test case, then destructor will SEGFAULT!
        INFO("after calling removeAllNodes(n), AATree should be empty [ root == bottomNode ]");
        REQUIRE(tree.root == tree.bottomNode);
        REQUIRE(tree.root->left == tree.bottomNode);
        REQUIRE(tree.root->right == tree.bottomNode);
        REQUIRE(tree.root->level == 0);
        REQUIRE(tree.root->data == -1);
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
