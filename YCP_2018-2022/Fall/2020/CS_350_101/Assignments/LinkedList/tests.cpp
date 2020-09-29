//
//  tests.cpp
//

#define CATCH_CONFIG_RUNNER

#include <iostream>
#include "LinkedList.h"
#include "catch.hpp"


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing constructor", "[CONSTRUCTOR]") {
    LinkedList<int> testList;

    SECTION("sentinel node (e.g. dummy) must be initialized") {
        REQUIRE(testList.dummy != nullptr);
    }
    
    SECTION("when linked list is empty, the next field of the dummy node should point to the dummy node") {
        REQUIRE(testList.dummy->next == testList.dummy);
    }
    
    SECTION("when linked list is empty, the prev field of the dummy node should point to the dummy node") {
        REQUIRE(testList.dummy->prev == testList.dummy);
    }
    
    SECTION("sentinel node (e.g. dummy) should contain data value of 0") {
        REQUIRE(testList.dummy->data == 0);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing getFirst() method on an empty linked list", "[GETFIRST]") {
    LinkedList<int> testList;

    SECTION("verify getFirst() returns 0 when called on empty linked list") {
        REQUIRE(testList.getFirst() == 0);
    }
}


TEST_CASE("testing getFirst() method on a non-empty linked list", "[GETFIRST]") {
    LinkedList<int> testList;
    testList.insert(1);
    testList.insert(2);
    testList.insert(3);
    INFO("inserted values 1, 2, 3");
    INFO("linked list should be [ <-> dummy <-> 3 <-> 2 <-> 1 <-> ]");

    SECTION("verify first value in list after push 3 integers") {
        REQUIRE(testList.getFirst() == 3);
    }

}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing getLast() method on an empty linked list", "[GETLAST]") {
    LinkedList<int> testList;

    SECTION("verify getLast() returns 0 when called on empty linked list") {
        REQUIRE(testList.getLast() == 0);
    }
}


TEST_CASE("testing getLast() method on a non-empty linked list", "[GETLAST]") {
    LinkedList<int> testList;
    testList.insert(1);
    testList.insert(2);
    testList.insert(3);
    INFO("inserted values 1, 2, 3");
    INFO("linked list should be [ <-> dummy <-> 3 <-> 2 <-> 1 <-> ]");

    SECTION("verify last value in list after push 3 integers") {
        REQUIRE(testList.getLast() == 1);
    }

}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing find() method on an empty linked list", "[FIND]") {
    LinkedList<int> testList;

    SECTION("verify that find() returns false when linked list is empty") {
        REQUIRE(testList.find(11) == false);
    }
}


TEST_CASE("testing find() method on a non-empty linked list", "[FIND]") {
    LinkedList<int> testList;
    testList.insert(1);
    testList.insert(2);
    testList.insert(3);
    testList.insert(4);
    testList.insert(5);
    INFO("inserted values 1, 2, 3, 4, 5");
    INFO("linked list should be [ <-> dummy <-> 5 <-> 4 <-> 3 <-> 2 <-> 1 <-> ]");

    SECTION("verify that find() returns false when linked list does not contain the value") {
        INFO("the value 11 is not in the list");
        REQUIRE(testList.find(11) == false);
    }
    
    SECTION("verify that find() returns true when linked list contains value at head of list") {
        INFO("a node containing the value 1 is at the head of the list");
        REQUIRE(testList.find(1) == true);
    }
    
    SECTION("verify that find() returns true when linked list contains value at tail of list") {
        INFO("a node containing the value 5 is at the tail of the list");
        REQUIRE(testList.find(5) == true);
    }
    
    SECTION("verify that find() returns true when linked list contains value in middle of list") {
        INFO("a node containing the value 3 is in the middle of the list");
        REQUIRE(testList.find(3) == true);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing findNode() method on an empty linked list", "[FINDNODE]") {
    LinkedList<int> testList;

    SECTION("verify that findNode() returns the sentinel node when linked list is empty") {
        REQUIRE(testList.findNode(11) == testList.dummy);
    }
}


TEST_CASE("testing findNode() method on a non-empty linked list", "[FINDNODE]") {
    LinkedList<int> testList;
    testList.insert(1);
    testList.insert(2);
    testList.insert(3);
    testList.insert(4);
    testList.insert(5);
    INFO("inserted values 1, 2, 3, 4, 5");
    INFO("linked list should be [ <-> dummy <-> 5 <-> 4 <-> 3 <-> 2 <-> 1 <-> ]");

    SECTION("verify that findNode() returns the sentinel node when linked list does not contain the value") {
        REQUIRE(testList.findNode(11) == testList.dummy); // make sure it's the sentinel node
        REQUIRE(testList.findNode(11)->data == 0);        // and not just a node that has a 0 in it.
    }
    
    SECTION("verify that findNode() returns the correct node when linked list has a node with the value at the head of the list") {
        INFO("the node containing the value 1 is at the head of the list");
        REQUIRE(testList.findNode(1)->data == 1);
    }
    
    SECTION("verify that findNode() returns the correct node when linked list has a node with the value at the tail of the list") {
        INFO("the node containing the value 5 is at the tail of the list");
        REQUIRE(testList.findNode(5)->data == 5);
    }
    
    SECTION("verify that findNode() returns the correct node when linked list has a node with the value in the middle of the list") {
        INFO("the node containing the value 3 is in the middle of the list");
        REQUIRE(testList.findNode(3)->data == 3);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing insert() method on an empty linked list", "[INSERT]") {
    LinkedList<int> testList;
    testList.insert(1);
    INFO("inserted value 1");
    INFO("linked list should be [ <-> dummy <-> 1 <-> ]");

    SECTION("veriify that pointers of sentinel node (i.e. dummy node) point to the newly inserted node") {
        REQUIRE(testList.dummy->next->data == 1);
        REQUIRE(testList.dummy->prev->data == 1);
    }
    
    SECTION("verify that pointers of newly inserted point to the dummy node") {
        REQUIRE(testList.dummy->next->next == testList.dummy);
        REQUIRE(testList.dummy->next->prev == testList.dummy);
    }
}


TEST_CASE("testing insert() method on a non-empty linked list (multiple inserts)", "[INSERT]") {
    LinkedList<int> testList;
    testList.insert(1);
    testList.insert(2);
    testList.insert(3);
    INFO("inserted values 1, 2, 3");
    INFO("linked list should be [ <-> dummy <-> 3 <-> 2 <-> 1 <-> ]");

    SECTION("verify structure of linked list in the forward direction") {
        REQUIRE(testList.dummy->next->data == 3);
        REQUIRE(testList.dummy->next->next->data == 2);
        REQUIRE(testList.dummy->next->next->next->data == 1);
        REQUIRE(testList.dummy->next->next->next->next->data == 0);        // back to the dummy
        REQUIRE(testList.dummy->next->next->next->next == testList.dummy); // back to the dummy
    }
    
    SECTION("verify structure of linked list in the reverse direction") {
        REQUIRE(testList.dummy->prev->data == 1);
        REQUIRE(testList.dummy->prev->prev->data == 2);
        REQUIRE(testList.dummy->prev->prev->prev->data == 3);
        REQUIRE(testList.dummy->prev->prev->prev->prev->data == 0);        // back to the dummy
        REQUIRE(testList.dummy->prev->prev->prev->prev == testList.dummy); // back to the dummy
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing remove() method on an empty linked list", "[REMOVE]") {
    LinkedList<int> testList;
    INFO("linked list should be [ <-> dummy <-> ]");
    // check structure before calling remove()
    REQUIRE(testList.dummy != nullptr);
    REQUIRE(testList.dummy->next == testList.dummy);
    REQUIRE(testList.dummy->prev == testList.dummy);
    REQUIRE(testList.dummy->data == 0);

    SECTION("verify that remove() doesn't break anything when linked list is empty") {
        testList.remove(11);
        INFO("linked list should still be [ <-> dummy <-> ]");
        REQUIRE(testList.dummy != nullptr);
        REQUIRE(testList.dummy->next == testList.dummy);
        REQUIRE(testList.dummy->prev == testList.dummy);
        REQUIRE(testList.dummy->data == 0);
    }
}


TEST_CASE("testing remove() method on a non-empty linked list", "[REMOVE]") {
    LinkedList<int> testList;
    testList.insert(1);
    testList.insert(2);
    testList.insert(3);
    testList.insert(4);
    testList.insert(5);
    INFO("inserted values 1, 2, 3, 4, 5");
    INFO("linked list should be [ <-> dummy <-> 5 <-> 4 <-> 3 <-> 2 <-> 1 <-> ]");

    SECTION("verify that remove() doesn't break anything when attempting to remove a value not in linked list") {
        testList.remove(11);
        INFO("linked list should still be [ <-> dummy <-> 5 <-> 4 <-> 3 <-> 2 <-> 1 <-> ]");
        // check forward direction
        REQUIRE(testList.dummy->next->data == 5);
        REQUIRE(testList.dummy->next->next->data == 4);
        REQUIRE(testList.dummy->next->next->next->data == 3);
        REQUIRE(testList.dummy->next->next->next->next->data == 2);
        REQUIRE(testList.dummy->next->next->next->next->next->data == 1);
        REQUIRE(testList.dummy->next->next->next->next->next->next->data == 0);        // back to the dummy
        REQUIRE(testList.dummy->next->next->next->next->next->next == testList.dummy); // back to the dummy
        // check reverse direction
        REQUIRE(testList.dummy->prev->data == 1);
        REQUIRE(testList.dummy->prev->prev->data == 2);
        REQUIRE(testList.dummy->prev->prev->prev->data == 3);
        REQUIRE(testList.dummy->prev->prev->prev->prev->data == 4);
        REQUIRE(testList.dummy->prev->prev->prev->prev->prev->data == 5);
        REQUIRE(testList.dummy->prev->prev->prev->prev->prev->prev->data == 0);        // back to the dummy
        REQUIRE(testList.dummy->prev->prev->prev->prev->prev->prev == testList.dummy); // back to the dummy
    }
    
    SECTION("verify that remove() successfully removes a value from the head of the linked list") {
        testList.remove(1);
        INFO("linked list should now be [ <-> dummy <-> 5 <-> 4 <-> 3 <-> 2 <-> ]");
        // check forward direction
        REQUIRE(testList.dummy->next->data == 5);
        REQUIRE(testList.dummy->next->next->data == 4);
        REQUIRE(testList.dummy->next->next->next->data == 3);
        REQUIRE(testList.dummy->next->next->next->next->data == 2);
        REQUIRE(testList.dummy->next->next->next->next->next->data == 0);         // back to the dummy
        REQUIRE(testList.dummy->next->next->next->next->next == testList.dummy);  // back to the dummy
        // check reverse direction
        REQUIRE(testList.dummy->prev->data == 2);
        REQUIRE(testList.dummy->prev->prev->data == 3);
        REQUIRE(testList.dummy->prev->prev->prev->data == 4);
        REQUIRE(testList.dummy->prev->prev->prev->prev->data == 5);
        REQUIRE(testList.dummy->prev->prev->prev->prev->prev->data == 0);         // back to the dummy
        REQUIRE(testList.dummy->prev->prev->prev->prev->prev == testList.dummy);  // back to the dummy
    }
    
    SECTION("verify that remove() successfully removes a value from the tail of the linked list") {
        testList.remove(5);
        INFO("linked list should now be [ <-> dummy <-> 4 <-> 3 <-> 2 <-> 1 <-> ]");
        // check forward direction
        REQUIRE(testList.dummy->next->data == 4);
        REQUIRE(testList.dummy->next->next->data == 3);
        REQUIRE(testList.dummy->next->next->next->data == 2);
        REQUIRE(testList.dummy->next->next->next->next->data == 1);
        REQUIRE(testList.dummy->next->next->next->next->next->data == 0);         // back to the dummy
        REQUIRE(testList.dummy->next->next->next->next->next == testList.dummy);  // back to the dummy
        // check reverse direction
        REQUIRE(testList.dummy->prev->data == 1);
        REQUIRE(testList.dummy->prev->prev->data == 2);
        REQUIRE(testList.dummy->prev->prev->prev->data == 3);
        REQUIRE(testList.dummy->prev->prev->prev->prev->data == 4);
        REQUIRE(testList.dummy->prev->prev->prev->prev->prev->data == 0);         // back to the dummy
        REQUIRE(testList.dummy->prev->prev->prev->prev->prev == testList.dummy);  // back to the dummy
    }
    
    SECTION("verify that remove() successfully removes a value from the middle of the linked list") {
        testList.remove(3);
        INFO("linked list should now be [ <-> dummy <-> 5 <-> 4 <-> 2 <-> 1 <-> ]");
        // check forward direction
        REQUIRE(testList.dummy->next->data == 5);
        REQUIRE(testList.dummy->next->next->data == 4);
        REQUIRE(testList.dummy->next->next->next->data == 2);
        REQUIRE(testList.dummy->next->next->next->next->data == 1);
        REQUIRE(testList.dummy->next->next->next->next->next->data == 0);         // back to the dummy
        REQUIRE(testList.dummy->next->next->next->next->next == testList.dummy);  // back to the dummy
        // check reverse direction
        REQUIRE(testList.dummy->prev->data == 1);
        REQUIRE(testList.dummy->prev->prev->data == 2);
        REQUIRE(testList.dummy->prev->prev->prev->data == 4);
        REQUIRE(testList.dummy->prev->prev->prev->prev->data == 5);
        REQUIRE(testList.dummy->prev->prev->prev->prev->prev->data == 0);         // back to the dummy
        REQUIRE(testList.dummy->prev->prev->prev->prev->prev == testList.dummy);  // back to the dummy
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing isEmpty() method on an empty linked list", "[ISEMPTY]") {
    LinkedList<int> testList;
    INFO("linked list should be [ <-> dummy <-> ]");
    REQUIRE(testList.dummy != nullptr);
    REQUIRE(testList.dummy->next == testList.dummy);
    REQUIRE(testList.dummy->prev == testList.dummy);
    REQUIRE(testList.dummy->data == 0);

    SECTION("verify return value of isEmpty()") {
        INFO("when empty, isEmpty() should return true");
        REQUIRE(testList.isEmpty() == true);
    }
}


TEST_CASE("testing isEmpty() method on a non-empty linked list", "[ISEMPTY]") {
    LinkedList<int> testList;
    testList.insert(1);
    testList.insert(2);
    testList.insert(3);
    INFO("inserted values 1, 2, 3");
    INFO("linked list should be [ <-> dummy <-> 3 <-> 2 <-> 1 <-> ]");
    // feel free to add REQUIRE statements here to ensure list is structured correctly before calling isEmpty()

    SECTION("verify return value of isEmpty()") {
        INFO("when not empty, isEmpty() should return false");
        REQUIRE(testList.isEmpty() == false);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing makeEmpty() method on an empty linked list", "[MAKEEMPTY]") {
    LinkedList<int> testList;
    INFO("linked list should be [ <-> dummy <-> ]");
    // check structure before calling makeEmpty()
    REQUIRE(testList.dummy != nullptr);
    REQUIRE(testList.dummy->next == testList.dummy);
    REQUIRE(testList.dummy->prev == testList.dummy);
    REQUIRE(testList.dummy->data == 0);

    SECTION("verify that makeEmpty() doesn't break anything when linked list is empty") {
        testList.makeEmpty();
        INFO("linked list should still be [ <-> dummy <-> ]");
        REQUIRE(testList.dummy != nullptr);
        REQUIRE(testList.dummy->next == testList.dummy);
        REQUIRE(testList.dummy->prev == testList.dummy);
        REQUIRE(testList.dummy->data == 0);
    }
}


TEST_CASE("testing makeEmpty() method on a non-empty linked list", "[MAKEEMPTY]") {
    LinkedList<int> testList;
    testList.insert(1);
    testList.insert(2);
    testList.insert(3);
    INFO("inserted values 1, 2, 3");
    INFO("linked list should be [ <-> dummy <-> 3 <-> 2 <-> 1 <-> ]");
    // check structure before calling makeEmpty()
    REQUIRE(testList.dummy->next->data == 3);
    REQUIRE(testList.dummy->next->next->data == 2);
    REQUIRE(testList.dummy->next->next->next->data == 1);
    REQUIRE(testList.dummy->next->next->next->next->data == 0);        // back to the dummy
    REQUIRE(testList.dummy->next->next->next->next == testList.dummy); // back to the dummy
    REQUIRE(testList.dummy->prev->data == 1);
    REQUIRE(testList.dummy->prev->prev->data == 2);
    REQUIRE(testList.dummy->prev->prev->prev->data == 3);
    REQUIRE(testList.dummy->prev->prev->prev->prev->data == 0);        // back to the dummy
    REQUIRE(testList.dummy->prev->prev->prev->prev == testList.dummy); // back to the dummy

    SECTION("verify that makeEmpty() successfully empties linked list and structure is correct") {
        testList.makeEmpty();
        INFO("after calling makeEmpty(), linked list should now be [ <-> dummy <-> ]");
        REQUIRE(testList.dummy != nullptr);
        REQUIRE(testList.dummy->next == testList.dummy);
        REQUIRE(testList.dummy->prev == testList.dummy);
        REQUIRE(testList.dummy->data == 0);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing copy constructor on an empty linked list", "[COPY_CONSTRUCTOR]") {
    LinkedList<int> testList;
    INFO("before calling copy constructor, linked list should be:\n  [ <-> dummy <-> ]");
    // check structure of original linked list before calling copy constructor
    REQUIRE(testList.dummy != nullptr);
    REQUIRE(testList.dummy->next == testList.dummy);
    REQUIRE(testList.dummy->prev == testList.dummy);
    REQUIRE(testList.dummy->data == 0);

    SECTION("verify that copy constructor successfully copies an empty linked list") {
        LinkedList<int> testListCopy(testList);  // call copy constructor
        // check structure of original linked list after calling copy constructor (should not have changed)
        INFO("after calling copy constructor, original linked list should still be:\n  [ <-> dummy <-> ]");
        REQUIRE(testList.dummy != nullptr);
        REQUIRE(testList.dummy->next == testList.dummy);
        REQUIRE(testList.dummy->prev == testList.dummy);
        REQUIRE(testList.dummy->data == 0);
        // check structure of new linked list (should be identical to original linked list)
        INFO("after calling copy constructor, copy of linked list should be:\n  [ <-> dummy <-> ]");
        REQUIRE(testListCopy.dummy != nullptr);
        REQUIRE(testListCopy.dummy->next == testListCopy.dummy);
        REQUIRE(testListCopy.dummy->prev == testListCopy.dummy);
        REQUIRE(testListCopy.dummy->data == 0);
        // also make sure that the two linked lists are NOT the same list!!!
        REQUIRE(testList.dummy != testListCopy.dummy);
    }
}


TEST_CASE("testing copy constructor on a non-empty linked list", "[COPY_CONSTRUCTOR]") {
    LinkedList<int> testList;
    testList.insert(1);
    testList.insert(2);
    testList.insert(3);
    INFO("inserted values 1, 2, 3");
    INFO("before calling copy constructor, linked list should be:\n  [ <-> dummy <-> 3 <-> 2 <-> 1 <-> ]");
    // check structure before calling copy constructor
    REQUIRE(testList.dummy->next->data == 3);
    REQUIRE(testList.dummy->next->next->data == 2);
    REQUIRE(testList.dummy->next->next->next->data == 1);
    REQUIRE(testList.dummy->next->next->next->next->data == 0);        // back to the dummy
    REQUIRE(testList.dummy->next->next->next->next == testList.dummy); // back to the dummy
    REQUIRE(testList.dummy->prev->data == 1);
    REQUIRE(testList.dummy->prev->prev->data == 2);
    REQUIRE(testList.dummy->prev->prev->prev->data == 3);
    REQUIRE(testList.dummy->prev->prev->prev->prev->data == 0);        // back to the dummy
    REQUIRE(testList.dummy->prev->prev->prev->prev == testList.dummy); // back to the dummy

    SECTION("verify that copy constructor successfully copies a non-empty linked list") {
        LinkedList<int> testListCopy(testList);  // call copy constructor
        // check structure of original linked list after calling copy constructor (should not have changed)
        INFO("after calling copy constructor, original linked list should still be:\n  [ <-> dummy <-> 3 <-> 2 <-> 1 <-> ]");
        REQUIRE(testList.dummy->next->data == 3);
        REQUIRE(testList.dummy->next->next->data == 2);
        REQUIRE(testList.dummy->next->next->next->data == 1);
        REQUIRE(testList.dummy->next->next->next->next->data == 0);        // back to the dummy
        REQUIRE(testList.dummy->next->next->next->next == testList.dummy); // back to the dummy
        REQUIRE(testList.dummy->prev->data == 1);
        REQUIRE(testList.dummy->prev->prev->data == 2);
        REQUIRE(testList.dummy->prev->prev->prev->data == 3);
        REQUIRE(testList.dummy->prev->prev->prev->prev->data == 0);        // back to the dummy
        REQUIRE(testList.dummy->prev->prev->prev->prev == testList.dummy); // back to the dummy
        // check structure of new linked list (should be identical to original linked list)
        INFO("after calling copy constructor, copy of linked list should be:\n  [ <-> dummy <-> 3 <-> 2 <-> 1 <-> ]");
        REQUIRE(testListCopy.dummy->next->data == 3);
        REQUIRE(testListCopy.dummy->next->next->data == 2);
        REQUIRE(testListCopy.dummy->next->next->next->data == 1);
        REQUIRE(testListCopy.dummy->next->next->next->next->data == 0);            // back to the dummy
        REQUIRE(testListCopy.dummy->next->next->next->next == testListCopy.dummy); // back to the dummy
        REQUIRE(testListCopy.dummy->prev->data == 1);
        REQUIRE(testListCopy.dummy->prev->prev->data == 2);
        REQUIRE(testListCopy.dummy->prev->prev->prev->data == 3);
        REQUIRE(testListCopy.dummy->prev->prev->prev->prev->data == 0);            // back to the dummy
        REQUIRE(testListCopy.dummy->prev->prev->prev->prev == testListCopy.dummy); // back to the dummy
        // also make sure that the two linked lists are NOT the same list!!!
        REQUIRE(testList.dummy != testListCopy.dummy);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing assignment operator using two empty linked lists", "[ASSIGN]") {
    LinkedList<int> testList1;
    Node<int>* testList1OriginalDummy = testList1.dummy;
    INFO("before calling assignment operator, linked list #1 should be:\n  [ <-> dummy <-> ]");
    // check structure of the first linked list before calling assignment operator
    REQUIRE(testList1.dummy != nullptr);
    REQUIRE(testList1.dummy->next == testList1.dummy);
    REQUIRE(testList1.dummy->prev == testList1.dummy);
    REQUIRE(testList1.dummy->data == 0);

    LinkedList<int> testList2;
    Node<int>* testList2OriginalDummy = testList2.dummy;
    INFO("before calling assignment operator, linked list #2 should be:\n  [ <-> dummy <-> ]");
    // check structure of the first linked list before calling assignment operator
    REQUIRE(testList2.dummy != nullptr);
    REQUIRE(testList2.dummy->next == testList2.dummy);
    REQUIRE(testList2.dummy->prev == testList2.dummy);
    REQUIRE(testList2.dummy->data == 0);

    SECTION("verify that the assignment operator successfully assigns an empty linked list to another empty linked list") {
        testList2 = testList1;
        // check structure of linked list #1 after calling the assignment operator (should not have changed)
        INFO("after calling assignment operator, linked list #1 should still be:\n  [ <-> dummy <-> ]");
        REQUIRE(testList1.dummy != nullptr);
        REQUIRE(testList1.dummy->next == testList1.dummy);
        REQUIRE(testList1.dummy->prev == testList1.dummy);
        REQUIRE(testList1.dummy->data == 0);
        INFO("after calling assignment operator, linked list #1 should still have the original dummy node");
        REQUIRE(testList1OriginalDummy == testList1.dummy);
        // check structure of linked list #2 (should be identical to first linked list)
        INFO("after calling assignment operator, linked list #2 should now be:\n  [ <-> dummy <-> ]");
        REQUIRE(testList2.dummy != nullptr);
        REQUIRE(testList2.dummy->next == testList2.dummy);
        REQUIRE(testList2.dummy->prev == testList2.dummy);
        REQUIRE(testList2.dummy->data == 0);
        INFO("after calling assignment operator, linked list #2 should still have the original dummy node");
        REQUIRE(testList2OriginalDummy == testList2.dummy);
        INFO("after calling assignment operator, linked list #1 and linked list #2 should still be distinct lists");
        REQUIRE(testList1.dummy != testList2.dummy);
    }
}


TEST_CASE("testing assignment operator using one empty and one non-empty linked list", "[ASSIGN]") {
    LinkedList<int> testList1;
    Node<int>* testList1OriginalDummy = testList1.dummy;
    INFO("before calling assignment operator, linked list #1 should be:\n  [ <-> dummy <-> ]");
    // check structure of the first linked list before calling assignment operator
    REQUIRE(testList1.dummy != nullptr);
    REQUIRE(testList1.dummy->next == testList1.dummy);
    REQUIRE(testList1.dummy->prev == testList1.dummy);
    REQUIRE(testList1.dummy->data == 0);

    LinkedList<int> testList2;
    Node<int>* testList2OriginalDummy = testList2.dummy;
    testList2.insert(1); // make the second list different than the first
    INFO("before calling assignment operator, linked list #2 should be:\n  [ <-> dummy <-> 1 <-> ]");
    // check structure of the second linked list before calling assignment operator
    REQUIRE(testList2.dummy != nullptr);
    REQUIRE(testList2.dummy->next->data == 1);
    REQUIRE(testList2.dummy->next->next->data == 0);          // back to the dummy
    REQUIRE(testList2.dummy->next->next == testList2.dummy);  // back to the dummy
    REQUIRE(testList2.dummy->prev->data == 1);
    REQUIRE(testList2.dummy->prev->prev->data == 0);          // back to the dummy
    REQUIRE(testList2.dummy->prev->prev == testList2.dummy);  // back to the dummy

    SECTION("verify that the assignment operator successfully assigns an empty linked list to a non-empty linked list") {
        testList2 = testList1;
        // check structure of linked list #1 after calling the assignment operator (should not have changed)
        INFO("after calling assignment operator, linked list #1 should still be:\n  [ <-> dummy <-> ]");
        REQUIRE(testList1.dummy != nullptr);
        REQUIRE(testList1.dummy->next == testList1.dummy);
        REQUIRE(testList1.dummy->prev == testList1.dummy);
        REQUIRE(testList1.dummy->data == 0);
        INFO("after calling assignment operator, linked list #1 should still have the original dummy node");
        REQUIRE(testList1OriginalDummy == testList1.dummy);
        // check structure of linked list #2 (should now be identical to first linked list)
        INFO("after calling assignment operator, linked list #2 should now be:\n  [ <-> dummy <-> ]");
        REQUIRE(testList2.dummy != nullptr);
        REQUIRE(testList2.dummy->next == testList2.dummy);
        REQUIRE(testList2.dummy->prev == testList2.dummy);
        REQUIRE(testList2.dummy->data == 0);
        INFO("after calling assignment operator, linked list #2 should still have the original dummy node");
        REQUIRE(testList2OriginalDummy == testList2.dummy);
        INFO("after calling assignment operator, linked list #1 and linked list #2 should still be distinct lists");
        REQUIRE(testList1.dummy != testList2.dummy);
    }
    
    SECTION("verify that the assignment operator successfully assigns a non-empty linked list to a empty linked list") {
        testList1 = testList2;
        // check structure of linked list #2 after calling the assignment operator (should not have changed)
        INFO("after calling assignment operator, linked list #2 should still be:\n  [ <-> dummy <-> 1 <-> ]");
        REQUIRE(testList2.dummy != nullptr);
        REQUIRE(testList2.dummy->next->data == 1);
        REQUIRE(testList2.dummy->next->next->data == 0);          // back to the dummy
        REQUIRE(testList2.dummy->next->next == testList2.dummy);  // back to the dummy
        REQUIRE(testList2.dummy->prev->data == 1);
        REQUIRE(testList2.dummy->prev->prev->data == 0);          // back to the dummy
        REQUIRE(testList2.dummy->prev->prev == testList2.dummy);  // back to the dummy
        INFO("after calling assignment operator, linked list #2 should still have the original dummy node");
        REQUIRE(testList2OriginalDummy == testList2.dummy);
        // check structure of linked list #1 (should now be identical to second linked list)
        INFO("after calling assignment operator, linked list #1 should now be:\n  [ <-> dummy <-> 1 <-> ]");
        REQUIRE(testList1.dummy != nullptr);
        REQUIRE(testList1.dummy->next->data == 1);
        REQUIRE(testList1.dummy->next->next->data == 0);          // back to the dummy
        REQUIRE(testList1.dummy->next->next == testList1.dummy);  // back to the dummy
        REQUIRE(testList1.dummy->prev->data == 1);
        REQUIRE(testList1.dummy->prev->prev->data == 0);          // back to the dummy
        REQUIRE(testList1.dummy->prev->prev == testList1.dummy);  // back to the dummy
        INFO("after calling assignment operator, linked list #1 should still have the original dummy node");
        REQUIRE(testList1OriginalDummy == testList1.dummy);
        INFO("after calling assignment operator, linked list #1 and linked list #2 should still be distinct lists");
        REQUIRE(testList1.dummy != testList2.dummy);
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
