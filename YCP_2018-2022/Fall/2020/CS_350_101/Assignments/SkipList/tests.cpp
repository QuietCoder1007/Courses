//
//  tests.cpp
//

#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_CONSOLE_WIDTH 150

#include <iostream>
#include "SkipList.h"
#include "catch.hpp"


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing constructor", "[CONSTRUCTOR]") {
    SkipList<int> list;

    SECTION("head node must be initialized") {
        REQUIRE(list.head != nullptr);
    }
    
    SECTION("head node height should be initialized to maxHeight") {
        REQUIRE(list.head->height == SkipList<int>::maxHeight);
    }
    
    SECTION("head node data should be initialized to 0") {
        REQUIRE(list.head->data == 0);
    }
    
    SECTION("array in head node should be properly initialized") {
        REQUIRE(list.head->next != nullptr);
        for (int i=0; i < SkipList<int>::maxHeight; i++) {
            REQUIRE(list.head->next[i] == nullptr);
        }
    }
    
    SECTION("skip list height should be initialized to 1") {
        REQUIRE(list.height == 1);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing find() method on an empty skip list", "[FIND]") {
    SkipList<int> list;

    SECTION("verify that find() returns false when skip list is empty") {
        REQUIRE(list.find(11) == false);
    }
}


TEST_CASE("testing find() method on a non-empty skip list", "[FIND]") {
    SkipList<int> list;
    while(list.getRandomNumber() != 0.22502); // ensure random number generator is at known location
    list.insert(2);
    list.insert(4);
    list.insert(6);
    list.insert(8);
    list.insert(10);
    list.insert(12);
    list.insert(14);
    list.insert(16);
    list.insert(18);
    list.insert(20);
    list.insert(22);
    INFO("inserted values 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22");
    const char *listString = "\n"
        "[ head(4) ---------------------------------------------------> 20 -------> nullptr ]\n"
        "[ head(3) ---------------------------> 12 -------------------> 20 -------> nullptr ]\n"
        "[ head(2) ------> 4 -----------------> 12 -> 14 -------------> 20 -------> nullptr ]\n"
        "[ head(1) -> 2 -> 4 ------> 8 -------> 12 -> 14 -> 16 -------> 20 -> 22 -> nullptr ]\n"
        "[ head(0) -> 2 -> 4 -> 6 -> 8 -> 10 -> 12 -> 14 -> 16 -> 18 -> 20 -> 22 -> nullptr ]\n";
    INFO("skip list should be: " << listString);

    SECTION("verify that find() returns false when skip list does not contain the value") {
        INFO("the value 11 is not in the list");
        REQUIRE(list.find(11) == false);
    }
    
    SECTION("verify that find() returns true when skip list contains value at head of list") {
        INFO("a node containing the value 2 is at the head of the list");
        REQUIRE(list.find(2) == true);
    }
    
    SECTION("verify that find() returns true when skip list contains value at tail of list") {
        INFO("a node containing the value 22 is at the tail of the list");
        REQUIRE(list.find(22) == true);
    }
    
    SECTION("verify that find() returns true when skip list contains value in middle of list") {
        INFO("the values 4, 6, 8, 10, 12, 14, 16, 18, and 20 are all in the list");
        REQUIRE(list.find(4) == true);
        REQUIRE(list.find(6) == true);
        REQUIRE(list.find(8) == true);
        REQUIRE(list.find(10) == true);
        REQUIRE(list.find(12) == true);
        REQUIRE(list.find(14) == true);
        REQUIRE(list.find(16) == true);
        REQUIRE(list.find(18) == true);
        REQUIRE(list.find(20) == true);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing insert() method on an empty skip list", "[INSERT]") {
    SkipList<int> list;
    while(list.getRandomNumber() != 0.22502); // ensure random number generator is at known location

    SECTION("verify structure of skip list after single insert at low level") {
        list.insert(1);
        INFO("inserted value 1");
        const char *listString = "\n"
        "[ head(1) -> 1 -> nullptr ]\n"
        "[ head(0) -> 1 -> nullptr ]\n";
        INFO("skip list should be: " << listString);
        
        REQUIRE(list.height == 2);                        // verify list height after insert
        REQUIRE(list.head->next[0]->data == 1);           // verify list order after insert
        REQUIRE(list.head->next[0]->height == 2);         // verify node heights after insert

        REQUIRE(list.head->next[4] == nullptr);           // verify node pointers after insert - head node
        REQUIRE(list.head->next[3] == nullptr);
        REQUIRE(list.head->next[2] == nullptr);
        REQUIRE(list.head->next[1]->data == 1);
        REQUIRE(list.head->next[0]->data == 1);

        REQUIRE(list.head->next[0]->next[1] == nullptr);  // verify node pointers after insert - node 1
        REQUIRE(list.head->next[0]->next[0] == nullptr);
    }
    
    SECTION("verify structure of skip list after single insert at high level") {
        list.height = 5;
        list.insert(1);
        INFO("inserted value 1");
        const char *listString = "\n"
        "[ head(4) -> 1 -> nullptr ]\n"
        "[ head(3) -> 1 -> nullptr ]\n"
        "[ head(2) -> 1 -> nullptr ]\n"
        "[ head(1) -> 1 -> nullptr ]\n"
        "[ head(0) -> 1 -> nullptr ]\n";
        INFO("skip list should be: " << listString);

        REQUIRE(list.height == 5);                        // verify list height after insert
        REQUIRE(list.head->next[0]->data == 1);           // verify list order after insert
        REQUIRE(list.head->next[0]->height == 5);         // verify node heights after insert

        REQUIRE(list.head->next[4]->data == 1);           // verify node pointers after insert - head node
        REQUIRE(list.head->next[3]->data == 1);
        REQUIRE(list.head->next[2]->data == 1);
        REQUIRE(list.head->next[1]->data == 1);
        REQUIRE(list.head->next[0]->data == 1);

        REQUIRE(list.head->next[0]->next[4] == nullptr);  // verify node pointers after insert - node 1
        REQUIRE(list.head->next[0]->next[3] == nullptr);
        REQUIRE(list.head->next[0]->next[2] == nullptr);
        REQUIRE(list.head->next[0]->next[1] == nullptr);
        REQUIRE(list.head->next[0]->next[0] == nullptr);
    }
}


TEST_CASE("testing insert() method on a non-empty skip list (multiple inserts, always appending)", "[INSERT]") {
    SkipList<int> list;
    while(list.getRandomNumber() != 0.22502); // ensure random number generator is at known location
    list.insert(2);
    list.insert(4);
    list.insert(6);
    list.insert(8);
    list.insert(10);
    list.insert(12);
    list.insert(14);
    list.insert(16);
    list.insert(18);
    list.insert(20);
    list.insert(22);
    INFO("inserted values 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22");
    const char *listString = "\n"
    "[ head(4) ---------------------------------------------------> 20 -------> nullptr ]\n"
    "[ head(3) ---------------------------> 12 -------------------> 20 -------> nullptr ]\n"
    "[ head(2) ------> 4 -----------------> 12 -> 14 -------------> 20 -------> nullptr ]\n"
    "[ head(1) -> 2 -> 4 ------> 8 -------> 12 -> 14 -> 16 -------> 20 -> 22 -> nullptr ]\n"
    "[ head(0) -> 2 -> 4 -> 6 -> 8 -> 10 -> 12 -> 14 -> 16 -> 18 -> 20 -> 22 -> nullptr ]\n";
    INFO("skip list should be: " << listString);

    SECTION("verify structure of skip list after multiple appending inserts") {
        // verify list height after multiple inserts
        REQUIRE(list.height == 5);

        // verify list order after multiple inserts
        REQUIRE(list.head->next[0]->data == 2);
        REQUIRE(list.head->next[0]->next[0]->data == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 6);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 10);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 18);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 22);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);

        // verify node heights after multiple inserts
        REQUIRE(list.head->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 5);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);

        // verify all node pointers after multiple inserts
        // Head Node (height 5)
        REQUIRE(list.head->next[4]->data == 20);
        REQUIRE(list.head->next[3]->data == 12);
        REQUIRE(list.head->next[2]->data == 4);
        REQUIRE(list.head->next[1]->data == 2);
        REQUIRE(list.head->next[0]->data == 2);
        // Node 2  (height 2)
        REQUIRE(list.head->next[0]->next[1]->data == 4);
        REQUIRE(list.head->next[0]->next[0]->data == 4);
        // Node 4  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[2]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[1]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 6);
        // Node 6  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 8);
        // Node 8  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[1]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 10);
        // Node 10  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        // Node 12  (height 4)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[3]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        // Node 14  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        // Node 16  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 18);
        // Node 18  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 20);
        // Node 20  (height 5)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[4] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[3] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 22);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 22);
        // Node 22  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
    }
}


TEST_CASE("testing insert() method on a non-empty skip list (multiple inserts, always prepending)", "[INSERT]") {
    SkipList<int> list;
    while(list.getRandomNumber() != 0.22502); // ensure random number generator is at known location
    list.insert(22);  // 2 high
    list.insert(20);  // 3
    list.insert(18);  // 1
    list.insert(16);  // 2
    list.insert(14);  // 1
    list.insert(12);  // 4
    list.insert(10);  // 3
    list.insert(8);   // 2
    list.insert(6);   // 1
    list.insert(4);   // 5
    list.insert(2);   // 2
    INFO("inserted values 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2");
    const char *listString = "\n"
                             "[ head(4) ------> 4 -----------------------------------------------------> nullptr ]\n"
                             "[ head(3) ------> 4 -----------------> 12 -------------------------------> nullptr ]\n"
                             "[ head(2) ------> 4 -----------> 10 -> 12 -------------------> 20 -------> nullptr ]\n"
                             "[ head(1) -> 2 -> 4 ------> 8 -> 10 -> 12 -------> 16 -------> 20 -> 22 -> nullptr ]\n"
                             "[ head(0) -> 2 -> 4 -> 6 -> 8 -> 10 -> 12 -> 14 -> 16 -> 18 -> 20 -> 22 -> nullptr ]\n";
    INFO("skip list should be: " << listString);

    SECTION("verify structure of skip list after multiple prepending inserts") {
        // verify list height after multiple inserts
        REQUIRE(list.height == 5);

        // verify list order after multiple inserts
        REQUIRE(list.head->next[0]->data == 2);
        REQUIRE(list.head->next[0]->next[0]->data == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 6);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 10);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 18);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 22);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);

        // verify node heights after multiple inserts
        REQUIRE(list.head->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->height == 5);
        REQUIRE(list.head->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);

        // verify all node pointers after multiple inserts
        // Head Node (height 5)
        REQUIRE(list.head->next[4]->data == 4);
        REQUIRE(list.head->next[3]->data == 4);
        REQUIRE(list.head->next[2]->data == 4);
        REQUIRE(list.head->next[1]->data == 2);
        REQUIRE(list.head->next[0]->data == 2);
        // Node 2  (height 2)
        REQUIRE(list.head->next[0]->next[1]->data == 4);
        REQUIRE(list.head->next[0]->next[0]->data == 4);
        // Node 4  (height 5)
        REQUIRE(list.head->next[0]->next[0]->next[4] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[3]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[2]->data == 10);
        REQUIRE(list.head->next[0]->next[0]->next[1]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 6);
        // Node 6  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 8);
        // Node 8  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[1]->data == 10);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 10);
        // Node 10  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[2]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        // Node 12  (height 4)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[3] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        // Node 14  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        // Node 16  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 18);
        // Node 18  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 20);
        // Node 20  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 22);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 22);
        // Node 22  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
    }
}


TEST_CASE("testing insert() method on a non-empty skip list (inserting a node into the middle of the list (shorter than predecessor))", "[INSERT]") {
    SkipList<int> list;
    while(list.getRandomNumber() != 0.22502); // ensure random number generator is at known location
    list.insert(2);   // 2
    list.insert(10);  // 3
    list.insert(18);  // 1
    list.insert(15);  // 2  (this node is in middle of list and shorter than predecessor)
    INFO("inserted values 2, 10, 18, 15");
    INFO("node 15 is the shorter middle node");
    const char *listString = "\n"
                             "[ head(4) ------------------------> nullptr ]\n"
                             "[ head(3) ------------------------> nullptr ]\n"
                             "[ head(2) ------> 10 -------------> nullptr ]\n"
                             "[ head(1) -> 2 -> 10 -- 15 -------> nullptr ]\n"
                             "[ head(0) -> 2 -> 10 -> 15 -> 18 -> nullptr ]\n";
    INFO("skip list should be: " << listString);

    SECTION("verify structure of skip list after inserting a node into the middle of the list (shorter than predecessor)") {
        // verify list height after multiple inserts
        REQUIRE(list.height == 3);

        // verify list order after multiple inserts
        REQUIRE(list.head->next[0]->data == 2);
        REQUIRE(list.head->next[0]->next[0]->data == 10);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 15);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 18);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);

        // verify node heights after multiple inserts
        REQUIRE(list.head->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->height == 1);

        // verify all node pointers after multiple inserts
        // Head Node (height 5)
        REQUIRE(list.head->next[4] == nullptr);
        REQUIRE(list.head->next[3] == nullptr);
        REQUIRE(list.head->next[2]->data == 10);
        REQUIRE(list.head->next[1]->data == 2);
        REQUIRE(list.head->next[0]->data == 2);
        // Node 2  (height 2)
        REQUIRE(list.head->next[0]->next[1]->data == 10);
        REQUIRE(list.head->next[0]->next[0]->data == 10);
        // Node 10  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[2] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[1]->data == 15);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 15);
        // Node 15  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[1] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 18);
        // Node 18  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
    }
}


TEST_CASE("testing insert() method on a non-empty skip list (inserting a node into the middle of the list (taller than predecessor))", "[INSERT]") {
    SkipList<int> list;
    while(list.getRandomNumber() != 0.22502); // ensure random number generator is at known location
    list.insert(2);   // 2
    list.insert(10);  // 3
    list.insert(18);  // 1
    list.insert(26);  // 2
    list.insert(30);  // 1
    list.insert(15);  // 4  (this node is in middle of list and taller than predecessor)
    INFO("inserted values 2, 10, 18, 26, 30, 15");
    INFO("node 15 is the taller middle node");
    const char *listString = "\n"
                             "[ head(4) ------------------------------------> nullptr ]\n"
                             "[ head(3) ------------> 15 -------------------> nullptr ]\n"
                             "[ head(2) ------> 10 -> 15 -------------------> nullptr ]\n"
                             "[ head(1) -> 2 -> 10 -> 15 -------> 26 -------> nullptr ]\n"
                             "[ head(0) -> 2 -> 10 -> 15 -> 18 -> 26 -> 30 -> nullptr ]\n";
    INFO("skip list should be: " << listString);

    SECTION("verify structure of skip list after inserting a node into the middle of the list (taller than predecessor)") {
        // verify list height after multiple inserts
        REQUIRE(list.height == 4);

        // verify list order after multiple inserts
        REQUIRE(list.head->next[0]->data == 2);
        REQUIRE(list.head->next[0]->next[0]->data == 10);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 15);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 18);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 26);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 30);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);

        // verify node heights after multiple inserts
        REQUIRE(list.head->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->height == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 1);

        // verify all node pointers after multiple inserts
        // Head Node (height 5)
        REQUIRE(list.head->next[4] == nullptr);
        REQUIRE(list.head->next[3]->data == 15);
        REQUIRE(list.head->next[2]->data == 10);
        REQUIRE(list.head->next[1]->data == 2);
        REQUIRE(list.head->next[0]->data == 2);
        // Node 2  (height 2)
        REQUIRE(list.head->next[0]->next[1]->data == 10);
        REQUIRE(list.head->next[0]->next[0]->data == 10);
        // Node 10  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[2]->data == 15);
        REQUIRE(list.head->next[0]->next[0]->next[1]->data == 15);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 15);
        // Node 15  (height 4)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[3] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[2] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[1]->data == 26);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 18);
        // Node 18  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 26);
        // Node 26  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]  == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 30);
        // Node 30  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
    }
}


TEST_CASE("testing insert() method on a non-empty skip list (multiple duplicate inserts)", "[INSERT]") {
    SkipList<int> list;
    while(list.getRandomNumber() != 0.22502); // ensure random number generator is at known location
    list.insert(2);
    list.insert(4);
    list.insert(6);
    list.insert(8);
    list.insert(10);
    list.insert(12);
    list.insert(14);
    list.insert(16);
    list.insert(18);
    list.insert(20);
    list.insert(22);
    INFO("inserted values 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22");
    const char *listString = "\n"
                             "[ head(4) ---------------------------------------------------> 20 -------> nullptr ]\n"
                             "[ head(3) ---------------------------> 12 -------------------> 20 -------> nullptr ]\n"
                             "[ head(2) ------> 4 -----------------> 12 -> 14 -------------> 20 -------> nullptr ]\n"
                             "[ head(1) -> 2 -> 4 ------> 8 -------> 12 -> 14 -> 16 -------> 20 -> 22 -> nullptr ]\n"
                             "[ head(0) -> 2 -> 4 -> 6 -> 8 -> 10 -> 12 -> 14 -> 16 -> 18 -> 20 -> 22 -> nullptr ]\n";
    INFO("skip list should be: " << listString);
    
    SECTION("verify structure of skip list after attempting duplicate inserts") {
        INFO("duplcate inserts are not permitted");
        list.insert(2);
        list.insert(6);
        list.insert(12);
        list.insert(14);
        list.insert(22);
        INFO("after attempting to insert the following duplicate values 2, 6, 12, 14, 22");
        const char *listString = "\n"
        "[ head(4) ---------------------------------------------------> 20 -------> nullptr ]\n"
        "[ head(3) ---------------------------> 12 -------------------> 20 -------> nullptr ]\n"
        "[ head(2) ------> 4 -----------------> 12 -> 14 -------------> 20 -------> nullptr ]\n"
        "[ head(1) -> 2 -> 4 ------> 8 -------> 12 -> 14 -> 16 -------> 20 -> 22 -> nullptr ]\n"
        "[ head(0) -> 2 -> 4 -> 6 -> 8 -> 10 -> 12 -> 14 -> 16 -> 18 -> 20 -> 22 -> nullptr ]\n";
        INFO("skip list should be: " << listString);
        
        // verify list height after attempting duplicate inserts
        REQUIRE(list.height == 5);
        
        // verify list order after attempting duplicate inserts
        REQUIRE(list.head->next[0]->data == 2);
        REQUIRE(list.head->next[0]->next[0]->data == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 6);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 10);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 18);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 22);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
        
        // verify node heights after attempting duplicate inserts
        REQUIRE(list.head->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 5);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);
        
        // verify all node pointers after attempting duplicate inserts
        // Head Node (height 5)
        REQUIRE(list.head->next[4]->data == 20);
        REQUIRE(list.head->next[3]->data == 12);
        REQUIRE(list.head->next[2]->data == 4);
        REQUIRE(list.head->next[1]->data == 2);
        REQUIRE(list.head->next[0]->data == 2);
        // Node 2  (height 2)
        REQUIRE(list.head->next[0]->next[1]->data == 4);
        REQUIRE(list.head->next[0]->next[0]->data == 4);
        // Node 4  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[2]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[1]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 6);
        // Node 6  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 8);
        // Node 8  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[1]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 10);
        // Node 10  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        // Node 12  (height 4)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[3]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        // Node 14  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        // Node 16  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 18);
        // Node 18  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 20);
        // Node 20  (height 5)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[4] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[3] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 22);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 22);
        // Node 22  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing remove() method on an empty skip list", "[REMOVE]") {
    SkipList<int> list;
    INFO("skip list should be: [ head(0) -> nullptr ]");
    // check structure before calling remove()
    REQUIRE(list.head->next[0] == nullptr);

    SECTION("verify that remove() doesn't break anything when skip list is empty") {
        list.remove(11);
        INFO("skip list should still be: [ head(0) -> nullptr ]");
        REQUIRE(list.head->next[0] == nullptr);
    }
}


TEST_CASE("testing remove() method on a non-empty skip list", "[REMOVE]") {
    SkipList<int> list;
    while(list.getRandomNumber() != 0.22502); // ensure random number generator is at known location
    list.insert(2);
    list.insert(4);
    list.insert(6);
    list.insert(8);
    list.insert(10);
    list.insert(12);
    list.insert(14);
    list.insert(16);
    list.insert(18);
    list.insert(20);
    list.insert(22);
    INFO("inserted values 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22");
    const char *listString = "\n"
    "[ head(4) ---------------------------------------------------> 20 -------> nullptr ]\n"
    "[ head(3) ---------------------------> 12 -------------------> 20 -------> nullptr ]\n"
    "[ head(2) ------> 4 -----------------> 12 -> 14 -------------> 20 -------> nullptr ]\n"
    "[ head(1) -> 2 -> 4 ------> 8 -------> 12 -> 14 -> 16 -------> 20 -> 22 -> nullptr ]\n"
    "[ head(0) -> 2 -> 4 -> 6 -> 8 -> 10 -> 12 -> 14 -> 16 -> 18 -> 20 -> 22 -> nullptr ]\n";
    INFO("skip list should be: " << listString);

    SECTION("verify that remove() doesn't break anything when attempting to remove a value not in skip list") {
        list.remove(11);
        INFO("attempted to remove the value 11");
        INFO("skip list should still be: " << listString);

        // verify list height after attempted remove
        REQUIRE(list.height == 5);
        
        // verify list order after attempted remove
        REQUIRE(list.head->next[0]->data == 2);
        REQUIRE(list.head->next[0]->next[0]->data == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 6);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 10);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 18);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 22);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
        
        // verify node heights after attempted remove
        REQUIRE(list.head->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 5);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);
        
        // verify all node pointers after attempted remove
        // Head Node (height 5)
        REQUIRE(list.head->next[4]->data == 20);
        REQUIRE(list.head->next[3]->data == 12);
        REQUIRE(list.head->next[2]->data == 4);
        REQUIRE(list.head->next[1]->data == 2);
        REQUIRE(list.head->next[0]->data == 2);
        // Node 2  (height 2)
        REQUIRE(list.head->next[0]->next[1]->data == 4);
        REQUIRE(list.head->next[0]->next[0]->data == 4);
        // Node 4  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[2]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[1]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 6);
        // Node 6  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 8);
        // Node 8  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[1]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 10);
        // Node 10  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        // Node 12  (height 4)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[3]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        // Node 14  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        // Node 16  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 18);
        // Node 18  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 20);
        // Node 20  (height 5)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[4] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[3] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 22);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 22);
        // Node 22  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
    }
    
    SECTION("verify that remove() successfully removes a value from the beginning of the skip list") {
        list.remove(2);
        INFO("attempted to remove the value 2");
        const char *listString = "\n"
        "[ head(4) ----------------------------------------------> 20 -------> nullptr ]\n"
        "[ head(3) ----------------------> 12 -------------------> 20 -------> nullptr ]\n"
        "[ head(2) -> 4 -----------------> 12 -> 14 -------------> 20 -------> nullptr ]\n"
        "[ head(1) -> 4 ------> 8 -------> 12 -> 14 -> 16 -------> 20 -> 22 -> nullptr ]\n"
        "[ head(0) -> 4 -> 6 -> 8 -> 10 -> 12 -> 14 -> 16 -> 18 -> 20 -> 22 -> nullptr ]\n";
        INFO("skip list should now be: " << listString);

        // verify list height after attempted remove
        REQUIRE(list.height == 5);

        // verify list order after attempted remove
        REQUIRE(list.head->next[0]->data == 4);
        REQUIRE(list.head->next[0]->next[0]->data == 6);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 10);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 18);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 22);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
        
        // verify node heights after attempted remove
        REQUIRE(list.head->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->height == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 5);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);

        // verify all node pointers after attempted remove
        // Head Node (height 5)
        REQUIRE(list.head->next[4]->data == 20);
        REQUIRE(list.head->next[3]->data == 12);
        REQUIRE(list.head->next[2]->data == 4);
        REQUIRE(list.head->next[1]->data == 4);
        REQUIRE(list.head->next[0]->data == 4);
        // Node 4  (height 3)
        REQUIRE(list.head->next[0]->next[2]->data == 12);
        REQUIRE(list.head->next[0]->next[1]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->data == 6);
        // Node 6  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 8);
        // Node 8  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[1]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 10);
        // Node 10  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        // Node 12  (height 4)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[3]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[2]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        // Node 14  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        // Node 16  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 18);
        // Node 18  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 20);
        // Node 20  (height 5)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[4] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[3] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 22);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 22);
        // Node 22  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
    }
    
    SECTION("verify that remove() successfully removes a value from the end of the skip list") {
        list.remove(22);
        INFO("attempted to remove the value 22");
        const char *listString = "\n"
        "[ head(4) ---------------------------------------------------> 20 -> nullptr ]\n"
        "[ head(3) ---------------------------> 12 -------------------> 20 -> nullptr ]\n"
        "[ head(2) ------> 4 -----------------> 12 -> 14 -------------> 20 -> nullptr ]\n"
        "[ head(1) -> 2 -> 4 ------> 8 -------> 12 -> 14 -> 16 -------> 20 -> nullptr ]\n"
        "[ head(0) -> 2 -> 4 -> 6 -> 8 -> 10 -> 12 -> 14 -> 16 -> 18 -> 20 -> nullptr ]\n";
        INFO("skip list should now be: " << listString);
        
        // verify list height after attempted remove
        REQUIRE(list.height == 5);
        
        // verify list order after attempted remove
        REQUIRE(list.head->next[0]->data == 2);
        REQUIRE(list.head->next[0]->next[0]->data == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 6);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 10);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 18);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
        
        // verify node heights after attempted remove
        REQUIRE(list.head->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 5);
        
        // verify all node pointers after attempted remove
        // Head Node (height 5)
        REQUIRE(list.head->next[4]->data == 20);
        REQUIRE(list.head->next[3]->data == 12);
        REQUIRE(list.head->next[2]->data == 4);
        REQUIRE(list.head->next[1]->data == 2);
        REQUIRE(list.head->next[0]->data == 2);
        // Node 2  (height 2)
        REQUIRE(list.head->next[0]->next[1]->data == 4);
        REQUIRE(list.head->next[0]->next[0]->data == 4);
        // Node 4  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[2]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[1]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 6);
        // Node 6  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 8);
        // Node 8  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[1]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 10);
        // Node 10  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        // Node 12  (height 4)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[3]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        // Node 14  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        // Node 16  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 18);
        // Node 18  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 20);
        // Node 20  (height 5)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[4] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[3] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
    }
    
    SECTION("verify that remove() successfully removes a value from the middle of the skip list (short node)") {
        list.remove(18);
        INFO("attempted to remove the value 18");
        const char *listString = "\n"
        "[ head(4) ---------------------------------------------> 20 -------> nullptr ]\n"
        "[ head(3) ---------------------------> 12 -------------> 20 -------> nullptr ]\n"
        "[ head(2) ------> 4 -----------------> 12 -> 14 -------> 20 -------> nullptr ]\n"
        "[ head(1) -> 2 -> 4 ------> 8 -------> 12 -> 14 -> 16 -> 20 -> 22 -> nullptr ]\n"
        "[ head(0) -> 2 -> 4 -> 6 -> 8 -> 10 -> 12 -> 14 -> 16 -> 20 -> 22 -> nullptr ]\n";
        INFO("skip list should now be: " << listString);

        // verify list height after attempted remove
        REQUIRE(list.height == 5);
        
        // verify list order after attempted remove
        REQUIRE(list.head->next[0]->data == 2);
        REQUIRE(list.head->next[0]->next[0]->data == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 6);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 10);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 22);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
        
        // verify node heights after attempted remove
        REQUIRE(list.head->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 5);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);
        
        // verify all node pointers after attempted remove
        // Head Node (height 5)
        REQUIRE(list.head->next[4]->data == 20);
        REQUIRE(list.head->next[3]->data == 12);
        REQUIRE(list.head->next[2]->data == 4);
        REQUIRE(list.head->next[1]->data == 2);
        REQUIRE(list.head->next[0]->data == 2);
        // Node 2  (height 2)
        REQUIRE(list.head->next[0]->next[1]->data == 4);
        REQUIRE(list.head->next[0]->next[0]->data == 4);
        // Node 4  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[2]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[1]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 6);
        // Node 6  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 8);
        // Node 8  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[1]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 10);
        // Node 10  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        // Node 12  (height 4)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[3]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        // Node 14  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        // Node 16  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 20);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 20);
        // Node 20  (height 5)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[4] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[3] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 22);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 22);
        // Node 22  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
    }
    
    SECTION("verify that remove() successfully removes a value from the middle of the skip list (tall node)") {
        list.remove(20);
        INFO("attempted to remove the value 20");
        const char *listString = "\n"
        "[ head(4) ---------------------------------------------------------> nullptr ]\n"
        "[ head(3) ---------------------------> 12 -------------------------> nullptr ]\n"
        "[ head(2) ------> 4 -----------------> 12 -> 14 -------------------> nullptr ]\n"
        "[ head(1) -> 2 -> 4 ------> 8 -------> 12 -> 14 -> 16 -------> 22 -> nullptr ]\n"
        "[ head(0) -> 2 -> 4 -> 6 -> 8 -> 10 -> 12 -> 14 -> 16 -> 18 -> 22 -> nullptr ]\n";
        INFO("skip list should now be: " << listString);
        
        // verify list height after attempted remove
        REQUIRE(list.height == 4);
        
        // verify list order after attempted remove
        REQUIRE(list.head->next[0]->data == 2);
        REQUIRE(list.head->next[0]->next[0]->data == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 6);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 10);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 18);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 22);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
        
        // verify node heights after attempted remove
        REQUIRE(list.head->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 4);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 3);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 1);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->height == 2);
        
        // verify all node pointers after attempted remove
        // Head Node (height 5)
        REQUIRE(list.head->next[4] == nullptr);
        REQUIRE(list.head->next[3]->data == 12);
        REQUIRE(list.head->next[2]->data == 4);
        REQUIRE(list.head->next[1]->data == 2);
        REQUIRE(list.head->next[0]->data == 2);
        // Node 2  (height 2)
        REQUIRE(list.head->next[0]->next[1]->data == 4);
        REQUIRE(list.head->next[0]->next[0]->data == 4);
        // Node 4  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[2]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[1]->data == 8);
        REQUIRE(list.head->next[0]->next[0]->next[0]->data == 6);
        // Node 6  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->data == 8);
        // Node 8  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[1]->data == 12);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->data == 10);
        // Node 10  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 12);
        // Node 12  (height 4)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[3] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 14);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 14);
        // Node 14  (height 3)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[2] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 16);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 16);
        // Node 16  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1]->data == 22);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 18);
        // Node 18  (height 1)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->data == 22);
        // Node 22  (height 2)
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[1] == nullptr);
        REQUIRE(list.head->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0]->next[0] == nullptr);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing isEmpty() method on an empty skip list", "[ISEMPTY]") {
    SkipList<int> list;
    REQUIRE(list.head->next[0] == nullptr);

    SECTION("verify return value of isEmpty()") {
        INFO("when empty, isEmpty() should return true");
        REQUIRE(list.isEmpty() == true);
    }
}


TEST_CASE("testing isEmpty() method on a non-empty skip list", "[ISEMPTY]") {
    SkipList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    INFO("inserted values 1, 2, 3");
    const char *listString = "\n"
    "[ head(2) ------> 2 ------> nullptr ]\n"
    "[ head(1) -> 1 -> 2 ------> nullptr ]\n"
    "[ head(0) -> 1 -> 2 -> 3 -> nullptr ]\n";
    INFO("skip list should be: " << listString);

    REQUIRE(list.head->next[0]->data == 1);
    REQUIRE(list.head->next[0]->next[0]->data == 2);
    REQUIRE(list.head->next[0]->next[0]->next[0]->data == 3);
    REQUIRE(list.head->next[0]->next[0]->next[0]->next[0] == nullptr);

    SECTION("verify return value of isEmpty()") {
        INFO("when empty, isEmpty() should return false");
        REQUIRE(list.isEmpty() == false);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing makeEmpty() method on an empty skip list", "[MAKEEMPTY]") {
    SkipList<int> list;
    list.makeEmpty();

    SECTION("head node must be re-initialized") {
        REQUIRE(list.head != nullptr);
    }
    
    SECTION("new head node height should be set to maxHeight") {
        REQUIRE(list.head->height == SkipList<int>::maxHeight);
    }
    
    SECTION("new head node data should be set to 0") {
        REQUIRE(list.head->data == 0);
    }
    
    SECTION("array in new head node should be properly initialized") {
        REQUIRE(list.head->next != nullptr);
        for (int i=0; i < SkipList<int>::maxHeight; i++) {
            REQUIRE(list.head->next[0] == nullptr);
        }
    }
    
    SECTION("skip list height should be reset to 1") {
        REQUIRE(list.height == 1);
    }
}


TEST_CASE("testing makeEmpty() method on a non-empty skip list", "[MAKEEMPTY]") {
    SkipList<int> list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.insert(5);
    INFO("inserted values 1, 2, 3, 4, 5");
    list.makeEmpty();

    SECTION("head node must be re-initialized") {
        REQUIRE(list.head != nullptr);
    }
    
    SECTION("new head node height should be set to maxHeight") {
        REQUIRE(list.head->height == SkipList<int>::maxHeight);
    }
    
    SECTION("new head node data should be set to 0") {
        REQUIRE(list.head->data == 0);
    }
    
    SECTION("array in new head node should be properly initialized") {
        REQUIRE(list.head->next != nullptr);
        for (int i=0; i < SkipList<int>::maxHeight; i++) {
            REQUIRE(list.head->next[0] == nullptr);
        }
    }
    
    SECTION("skip list height should be reset to 1") {
        REQUIRE(list.height == 1);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing randomLevel() method", "[RANDOMLEVEL]") {
    SkipList<int> list;
    while(list.getRandomNumber() != 0.22502); // ensure random number generator is at known location

    SECTION("verify randomLevel() returns appropriate values when list height equals 1") {
        list.height = 1;
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 1);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 1);
        REQUIRE(list.randomLevel() == 2);
    }
    
    SECTION("verify randomLevel() returns appropriate values when list height equals 2") {
        list.height = 2;
        REQUIRE(list.randomLevel() == 3);
        REQUIRE(list.randomLevel() == 3);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 1);
        REQUIRE(list.randomLevel() == 3);
        REQUIRE(list.randomLevel() == 3);
        REQUIRE(list.randomLevel() == 1);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 1);
        REQUIRE(list.randomLevel() == 3);
    }
    
    SECTION("verify randomLevel() returns appropriate values when list height equals 3") {
        list.height = 3;
        REQUIRE(list.randomLevel() == 4);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 1);
        REQUIRE(list.randomLevel() == 4);
        REQUIRE(list.randomLevel() == 3);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 1);
        REQUIRE(list.randomLevel() == 4);
        REQUIRE(list.randomLevel() == 3);
    }
    
    SECTION("verify randomLevel() returns appropriate values when list height equals 4") {
        list.height = 4;
        REQUIRE(list.randomLevel() == 5);
        REQUIRE(list.randomLevel() == 1);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 1);
        REQUIRE(list.randomLevel() == 5);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 1);
        REQUIRE(list.randomLevel() == 5);
        REQUIRE(list.randomLevel() == 2);
    }
    
    SECTION("verify randomLevel() returns appropriate values when list height equals 5") {
        list.height = 5;
        REQUIRE(list.randomLevel() == 5);
        REQUIRE(list.randomLevel() == 1);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 1);
        REQUIRE(list.randomLevel() == 5);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 2);
        REQUIRE(list.randomLevel() == 1);
        REQUIRE(list.randomLevel() == 5);
        REQUIRE(list.randomLevel() == 2);
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
