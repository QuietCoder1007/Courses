//
//  tests.cpp
//

#define CATCH_CONFIG_RUNNER

#include <iostream>
#include "IntArrayStack.h"
#include "catch.hpp"


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing constructor", "[CONSTRUCTOR]") {
    IntArrayStack s;

    SECTION("initial capacity should be 1") {
        REQUIRE(s.getCapacity() == 1);  // should initialize capacity to 1
    }
    
    SECTION("initial top pointer should be -1") {
        REQUIRE(s.getTop() == -1);      // should initialize top to -1
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing push() method", "[PUSH]") {
    IntArrayStack s;
    s.push(1);                      // insert some data into the stack
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    INFO("pushed values 1, 2, 3, 4, 5");
    INFO("stack arr should be [1, 2, 3, 4, 5]");

    SECTION("verify stack size after pushing 5 integers") {
        INFO("after pushing 5 integers, the size should be 5");
        REQUIRE(s.getSize() == 5);
    }

    SECTION("verify stack capacity after pushing 5 integers") {
        INFO("after pushing 5 integers, the capacity should be 8");
        REQUIRE(s.getCapacity() == 8);
    }

    SECTION("verify stack contents after pushing 5 integers") {
        int *arr = new int[s.getCapacity()];
        s.toArray(arr);
        REQUIRE(arr[0] == 1);
        REQUIRE(arr[1] == 2);
        REQUIRE(arr[2] == 3);
        REQUIRE(arr[3] == 4);
        REQUIRE(arr[4] == 5);
        delete [] arr;
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing pop() method on empty stack", "[POP]") {
    IntArrayStack s;

    SECTION("verify pop returns -1 when popping empty stack") {
        INFO("popping an empty stack should return -1");
        REQUIRE(s.pop() == -1);
        INFO("after popping an empty stack, the capacity should be 1");
        REQUIRE(s.getCapacity() == 1);
        INFO("after popping an empty stack, the size should be 0");
        REQUIRE(s.getSize() == 0);
    }
}


TEST_CASE("testing pop() method on stack with only a single value", "[POP]") {
    IntArrayStack s;
    s.push(1);

    SECTION("verify capacity and size before popping") {
        INFO("before popping, the capacity should be 1");
        REQUIRE(s.getCapacity() == 1);
        INFO("before popping, the size should be 1");
        REQUIRE(s.getSize() == 1);
    }

    SECTION("verify value, capacity and size after popping one value") {
        INFO("the value of the popped integer should be 1");
        REQUIRE(s.pop() == 1);
        INFO("after popping, the capacity should be 1");
        REQUIRE(s.getCapacity() == 1);
        INFO("after popping, the size should be 0");
        REQUIRE(s.getSize() == 0);
    }
}


TEST_CASE("testing pop() method on non-empty stack", "[POP]") {
    IntArrayStack s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    SECTION("verify capacity and size before popping") {
        INFO("before popping, the capacity should be 8");
        REQUIRE(s.getCapacity() == 8);
        INFO("before popping, the size should be 5");
        REQUIRE(s.getSize() == 5);
    }

    SECTION("verify value, capacity and size after popping one value") {
        INFO("the value of the popped integer should be 5");
        REQUIRE(s.pop() == 5);
        INFO("after popping, the capacity should be 8");
        REQUIRE(s.getCapacity() == 8);
        INFO("after popping, the size should be 4");
        REQUIRE(s.getSize() == 4);
    }
    
    SECTION("verify value, capacity and size after popping two values") {
        INFO("the value of the popped integer should be 4");
        s.pop();
        REQUIRE(s.pop() == 4);
        INFO("after popping, the capacity should be 8");
        REQUIRE(s.getCapacity() == 8);
        INFO("after popping, the size should be 3");
        REQUIRE(s.getSize() == 3);
    }
    
    SECTION("verify value, capacity and size after popping three values") {
        INFO("the value of the popped integer should be 3");
        s.pop();
        s.pop();
        REQUIRE(s.pop() == 3);
        INFO("after popping, the capacity should be 4");
        REQUIRE(s.getCapacity() == 4);
        INFO("after popping, the size should be 2");
        REQUIRE(s.getSize() == 2);
    }
    
    SECTION("verify value, capacity and size after popping four values") {
        INFO("the value of the popped integer should be 2");
        s.pop();
        s.pop();
        s.pop();
        REQUIRE(s.pop() == 2);
        INFO("after popping, the capacity should be 2");
        REQUIRE(s.getCapacity() == 2);
        INFO("after popping, the size should be 1");
        REQUIRE(s.getSize() == 1);
    }
    
    SECTION("verify value, capacity and size after popping five values") {
        INFO("the value of the popped integer should be 1");
        s.pop();
        s.pop();
        s.pop();
        s.pop();
        REQUIRE(s.pop() == 1);
        INFO("after popping, the capacity should be 1");
        REQUIRE(s.getCapacity() == 1);
        INFO("after popping, the size should be 0");
        REQUIRE(s.getSize() == 0);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing peek() method", "[PEEK]") {
    IntArrayStack s;

    SECTION("verify peek() returns -1 when peeking at empty stack") {
        INFO("peeking at an empty stack should return -1");
        REQUIRE(s.peek() == -1);
        INFO("top pointer should still be -1");
        REQUIRE(s.getTop() == -1);
    }

    SECTION("verify peek() returns correct value when peeking at non-empty stack") {
        s.push(44);
        s.push(21);
        s.push(64);
        s.push(33);
        s.push(98);
        s.push(23);
        s.push(56);
        s.push(77);
        s.push(99);
        INFO("peeking at non-empty stack should return 99");
        REQUIRE(s.peek() == 99);
        INFO("top pointer should be 8");
        REQUIRE(s.getTop() == 8);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing isEmpty() method", "[ISEMPTY]") {
    IntArrayStack s;

    SECTION("verify capacity, size, and isEmpty() when stack is empty") {
        INFO("when empty, the capacity should be 1");
        REQUIRE(s.getCapacity() == 1);       // empty stack should have a capacity of 1
        INFO("when empty, the size should be 0");
        REQUIRE(s.getSize() == 0);           // stack should contain no data
        INFO("when empty, isEmpty() should return true");
        REQUIRE(s.isEmpty() == true);        // verify stack is emtpy
    }

    SECTION("verify capacity, size, and isEmpty() when stack is not empty") {
        s.push(1);                           // insert some data into the stack
        s.push(2);
        INFO("after pushing 2 integers, the capacity should be 2");
        REQUIRE(s.getCapacity() == 2);       // empty stack should have a capacity of 1
        INFO("after pushing 2 integers, the size should be 2");
        REQUIRE(s.getSize() == 2);           // if push fails, then this will fail
        INFO("after pushing 2 integers, isEmpty() should return false");
        REQUIRE(s.isEmpty() == false);       // verify stack is not emtpy
    }

    SECTION("verify capacity, size, and isEmpty() after emptyStack() is called") {
        s.push(1);                           // insert some data into the stack
        s.push(2);
        s.emptyStack();
        INFO("after calling emptyStack(), the capacity should be 1");
        REQUIRE(s.getCapacity() == 1);       // empty stack should have a capacity of 1
        INFO("after calling emptyStack(), the size should be 0");
        REQUIRE(s.getSize() == 0);           // stack should contain no data
        INFO("after calling emptyStack(), isEmpty() should return true");
        REQUIRE(s.isEmpty() == true);        // verify stack is emtpy
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing emptyStack() method", "[EMPTYSTACK]") {
    IntArrayStack s;

    SECTION("verify capacity, size, and top after emptyStack() is called on empty stack") {
        s.emptyStack();
        INFO("after calling emptyStack(), the capacity should be 1");
        REQUIRE(s.getCapacity() == 1);       // empty stack should have a capacity of 1
        INFO("after calling emptyStack(), the size should be 0");
        REQUIRE(s.getSize() == 0);           // stack should contain no data
        INFO("after calling emptyStack(), the top pointer should be -1");
        REQUIRE(s.getTop() == -1);
    }

    SECTION("verify capacity, size, and top after emptyStack() is called on non-empty stack") {
        s.push(1);                           // insert some data into the stack
        s.push(2);
        s.push(3);
        s.push(4);
        s.push(5);
        s.push(6);
        s.push(7);
        s.push(8);
        s.push(9);
        s.push(10);
        s.emptyStack();
        INFO("after calling emptyStack(), the capacity should be 1");
        REQUIRE(s.getCapacity() == 1);       // empty stack should have a capacity of 1
        INFO("after calling emptyStack(), the size should be 0");
        REQUIRE(s.getSize() == 0);           // stack should contain no data
        INFO("after calling emptyStack(), the top pointer should be -1");
        REQUIRE(s.getTop() == -1);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing resize() method with many push/pop operations", "[RESIZE]") {
    IntArrayStack s;
    for (int i = 1; i <= 16; i++) { s.push(i); }
    INFO("pushed values 1, 2, 3, ..., 16");
    INFO("stack arr should be [1, 2, 3, ..., 16]");

    SECTION("verify stack size after pushing 16 integers") {
        INFO("after pushing 16 integers, the size should be 16");
        REQUIRE(s.getSize() == 16);
    }

    SECTION("verify stack capacity after pushing 16 integers") {
        INFO("after pushing 16 integers, the capacity should be 16");
        REQUIRE(s.getCapacity() == 16);
    }

    SECTION("verify stack contents after pushing 16 integers") {
        int *arr = new int[s.getCapacity()];
        s.toArray(arr);
        REQUIRE(arr[0] == 1);
        REQUIRE(arr[1] == 2);
        REQUIRE(arr[2] == 3);
        REQUIRE(arr[3] == 4);
        REQUIRE(arr[4] == 5);
        REQUIRE(arr[5] == 6);
        REQUIRE(arr[6] == 7);
        REQUIRE(arr[7] == 8);
        REQUIRE(arr[8] == 9);
        REQUIRE(arr[9] == 10);
        REQUIRE(arr[10] == 11);
        REQUIRE(arr[11] == 12);
        REQUIRE(arr[12] == 13);
        REQUIRE(arr[13] == 14);
        REQUIRE(arr[14] == 15);
        REQUIRE(arr[15] == 16);
        delete [] arr;
    }

    SECTION("verify stack size after pushing 16 integers, and then popping 12") {
        for (int i = 0; i < 12; i++) { s.pop(); }
        INFO("after pushing 16 integers and popping 12, the size should be 4");
        REQUIRE(s.getSize() == 4);
    }

    SECTION("verify stack capacity after pushing 16 integers, and then popping 12") {
        for (int i = 0; i < 12; i++) { s.pop(); }
        INFO("after pushing 16 integers and popping 12, the capacity should be 8");
        REQUIRE(s.getCapacity() == 8);
    }

    SECTION("verify stack contents after pushing 16 integers, and then popping 12") {
        for (int i = 0; i < 12; i++) { s.pop(); }
        int *arr = new int[s.getCapacity()];
        s.toArray(arr);
        INFO("after popping, stack arr should be [1, 2, 3, 4]");
        REQUIRE(arr[0] == 1);
        REQUIRE(arr[1] == 2);
        REQUIRE(arr[2] == 3);
        REQUIRE(arr[3] == 4);
        delete [] arr;
    }

    SECTION("verify that only valid data is copied after pushing 16 integers, and then popping 12") {
        INFO("after popping, stack arr should be [1, 2, 3, 4]");
        INFO("when shrinking the backing array, only copy valid data to new backing array");
        for (int i = 0; i < 12; i++) { s.pop(); }
        int *arr = new int[s.getCapacity()];
        s.toArray(arr);
        /* This is a good test to ensure that only valid data is being copied from
         * source IntArrayStack to destination IntArrayStack.  However, to test this
         * the following REQUIRE assertions access memory locations that are potentially
         * uninitialized.  In fact, the memory locations that are accessed below SHOULD
         * be uninitialized if only VALID data was copied.
         * A memory check will flag access to uninitialized memory as an error.
         * As such, the following REQUIRE assertions are currently commented out. */
        // REQUIRE(arr[5] != 6);   
        // REQUIRE(arr[6] != 7);   
        // REQUIRE(arr[7] != 8);   
        delete [] arr;
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

