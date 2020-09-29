//
//  tests.cpp
//

#define CATCH_CONFIG_RUNNER

#include <iostream>
#include "Queue.h"
#include "catch.hpp"



/* **************************************************************** */
/* **************************************************************** */


void buildSmallTestQueue(Queue<int> & q, std::stringstream & setupInfo) {
    q.head = new Node<int>(1);
    q.tail = q.head;
    setupInfo << "before testing method, queue is:\n";
    setupInfo << " h\n";
    setupInfo << "[1] -> nullptr\n";
    setupInfo << " t\n";
}


void buildLargeTestQueue(Queue<int> & q, std::stringstream & setupInfo) {
    q.head = new Node<int>(1);
    q.head->next = new Node<int>(2);
    q.head->next->next = new Node<int>(3);
    q.head->next->next->next = new Node<int>(4);
    q.head->next->next->next->next = new Node<int>(5);
    q.tail = q.head->next->next->next->next;
    setupInfo << "before testing method, queue is:\n";
    setupInfo << " h\n";
    setupInfo << "[1] -> [2] -> [3] -> [4] -> [5] -> nullptr\n";
    setupInfo << "                             t\n";
}


/* **************************************************************** */
/* **************************************************************** */


// 2.5 points
TEST_CASE("verify constructor initializes the head pointer properly", "[CONSTRUCTOR][11]") {
    Queue<int> q;
    REQUIRE(q.head == nullptr);
}


// 2.5 points
TEST_CASE("verify constructor initializes the tail pointer properly", "[CONSTRUCTOR][12]") {
    Queue<int> q;
    REQUIRE(q.tail == nullptr);
}


/* **************************************************************** */
/* **************************************************************** */


// 5 points
TEST_CASE("verify destructor runs without segmentation fault", "[DESTRUCTOR][1]") {
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    REQUIRE(q.head->data == 1);
    REQUIRE(q.head->next->data == 2);
    REQUIRE(q.head->next->next->data == 3);
}


//// x points
//TEST_CASE("verify destructor frees memory for nodes that were inserted", "[DESTRUCTOR][22]") {
//    Queue<int> *qp;
//    Node<int> *n1p;
//    Node<int> *n2p;
//    Node<int> *n3p;
//    Node<int> *n4p;
//    Node<int> *n5p;
//    {
//        Queue<int> q;
//        std::stringstream setupInfo;
//        buildLargeTestQueue(q, setupInfo);
//        INFO(setupInfo.str());
//        qp = &q;
//        n1p = q.head;
//        n2p = q.head->next;
//        n3p = q.head->next->next;
//        n4p = q.head->next->next->next;
//        n5p = q.head->next->next->next->next;
//        REQUIRE(n1p->data == 1);
//        REQUIRE(n2p->data == 2);
//        REQUIRE(n3p->data == 3);
//        REQUIRE(n4p->data == 4);
//        REQUIRE(n5p->data == 5);
//    }
//    REQUIRE(n1p->data != 1);
//    REQUIRE(n2p->data != 2);
//    REQUIRE(n3p->data != 3);
//    REQUIRE(n4p->data != 4);
//    REQUIRE(n5p->data != 5);
//}


/* **************************************************************** */
/* **************************************************************** */


// 2 points
TEST_CASE("verify enqueue(data) operates correctly when queue is empty", "[ENQUEUE][21]") {
    Queue<int> q;
    INFO("before testing method, queue is empty");
    q.enqueue(1);
    INFO("enqueued value 1");
    INFO("queue should now be [ 1 -> nullptr ]");
    REQUIRE(q.head != nullptr);
    REQUIRE(q.tail != nullptr);
    REQUIRE(q.head->data == 1);
    REQUIRE(q.tail->data == 1);
    REQUIRE(q.head == q.tail);
    REQUIRE(q.head->next == nullptr);
    REQUIRE(q.tail->next == nullptr);
}


// 1 points
TEST_CASE("verify enqueue(data) operates correctly when queue has only a single node", "[ENQUEUE][22]") {
    Queue<int> q;
    std::stringstream setupInfo;
    buildSmallTestQueue(q, setupInfo);
    INFO(setupInfo.str());
    q.enqueue(2);
    REQUIRE(q.head != nullptr);
    REQUIRE(q.tail != nullptr);
    REQUIRE(q.head->data == 1);
    REQUIRE(q.tail->data == 2);
    REQUIRE(q.head->next->data == 2);
    REQUIRE(q.head->next->next == nullptr);
}


// 2 points
TEST_CASE("verify enqueue(data) operates correctly when queue has many nodes", "[ENQUEUE][23]") {
    Queue<int> q;
    std::stringstream setupInfo;
    buildLargeTestQueue(q, setupInfo);
    INFO(setupInfo.str());
    q.enqueue(6);
    REQUIRE(q.head != nullptr);
    REQUIRE(q.tail != nullptr);
    REQUIRE(q.head->data == 1);
    REQUIRE(q.tail->data == 6);
    REQUIRE(q.head->next->data == 2);
    REQUIRE(q.head->next->next->data == 3);
    REQUIRE(q.head->next->next->next->data == 4);
    REQUIRE(q.head->next->next->next->next->data == 5);
    REQUIRE(q.head->next->next->next->next->next->data == 6);
    REQUIRE(q.head->next->next->next->next->next->next == nullptr);
}


/* **************************************************************** */
/* **************************************************************** */


// 3 points
TEST_CASE("verify dequeue() operates correctly when queue has many nodes", "[DEQUEUE][31]") {
    Queue<int> q;
    std::stringstream setupInfo;
    buildLargeTestQueue(q, setupInfo);
    INFO(setupInfo.str());
    int val = q.dequeue();
    REQUIRE(val == 1);
    REQUIRE(q.head != nullptr);
    REQUIRE(q.tail != nullptr);
    REQUIRE(q.head->data == 2);
    REQUIRE(q.tail->data == 5);
    REQUIRE(q.head->next->data == 3);
    REQUIRE(q.head->next->next->data == 4);
    REQUIRE(q.head->next->next->next->data == 5);
    REQUIRE(q.head->next->next->next->next == nullptr);
    
    val = q.dequeue();
    REQUIRE(val == 2);
    REQUIRE(q.head != nullptr);
    REQUIRE(q.tail != nullptr);
    REQUIRE(q.head->data == 3);
    REQUIRE(q.tail->data == 5);
    REQUIRE(q.head->next->data == 4);
    REQUIRE(q.head->next->next->data == 5);
    REQUIRE(q.head->next->next->next == nullptr);
    
    val = q.dequeue();
    REQUIRE(val == 3);
    REQUIRE(q.head != nullptr);
    REQUIRE(q.tail != nullptr);
    REQUIRE(q.head->data == 4);
    REQUIRE(q.tail->data == 5);
    REQUIRE(q.head->next->data == 5);
    REQUIRE(q.head->next->next == nullptr);
}


// 2 points
TEST_CASE("verify dequeue() operates correctly when queue has only a single node", "[DEQUEUE][32]") {
    Queue<int> q;
    std::stringstream setupInfo;
    buildSmallTestQueue(q, setupInfo);
    INFO(setupInfo.str());
    int val = q.dequeue();
    REQUIRE(val == 1);
    REQUIRE(q.head == nullptr);
    REQUIRE(q.tail == nullptr);
}


/* **************************************************************** */
/* **************************************************************** */


// 2 points
TEST_CASE("verify isEmpty() operates correctly when queue is empty", "[ISEMPTY][41]") {
    Queue<int> q;
    INFO("before testing method, queue is empty");
    REQUIRE(q.isEmpty() == true);
    REQUIRE(q.head == nullptr);
    REQUIRE(q.tail == nullptr);
}


// 1 points
TEST_CASE("verify isEmpty() operates correctly when queue has only a single node", "[ISEMPTY][42]") {
    Queue<int> q;
    std::stringstream setupInfo;
    buildSmallTestQueue(q, setupInfo);
    INFO(setupInfo.str());
    REQUIRE(q.isEmpty() == false);
    REQUIRE(q.head != nullptr);
    REQUIRE(q.tail != nullptr);
}


// 2 points
TEST_CASE("verify isEmpty() operates correctly when queue has many nodes", "[ISEMPTY][43]") {
    Queue<int> q;
    std::stringstream setupInfo;
    buildLargeTestQueue(q, setupInfo);
    INFO(setupInfo.str());
    REQUIRE(q.isEmpty() == false);
    REQUIRE(q.head != nullptr);
    REQUIRE(q.tail != nullptr);
}


/* **************************************************************** */
/* **************************************************************** */


// 1 points
TEST_CASE("verify makeEmpty() operates correctly when queue is empty", "[MAKEEMPTY][51]") {
    Queue<int> q;
    INFO("before testing method, queue is empty");
    q.makeEmpty();
    //REQUIRE(q.isEmpty() == true);
    REQUIRE(q.head == nullptr);
    REQUIRE(q.tail == nullptr);
}


// 2 points
TEST_CASE("verify makeEmpty() operates correctly when queue has only a single node", "[MAKEEMPTY][52]") {
    Queue<int> q;
    std::stringstream setupInfo;
    buildSmallTestQueue(q, setupInfo);
    INFO(setupInfo.str());
    q.makeEmpty();
    //REQUIRE(q.isEmpty() == true);
    REQUIRE(q.head == nullptr);
    REQUIRE(q.tail == nullptr);
}


// 2 points
TEST_CASE("verify makeEmpty() operates correctly when queue has many nodes", "[MAKEEMPTY][53]") {
    Queue<int> q;
    std::stringstream setupInfo;
    buildLargeTestQueue(q, setupInfo);
    INFO(setupInfo.str());
    q.makeEmpty();
    //REQUIRE(q.isEmpty() == true);
    REQUIRE(q.head == nullptr);
    REQUIRE(q.tail == nullptr);
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
