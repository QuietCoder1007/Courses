//
//  AATreePrettyPrinter.h
//
#ifndef _AATREEPRETTYPRINTREE_CPP_
#define _AATREEPRETTYPRINTREE_CPP_

#include <fstream>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>
#include "AATree.h"
#include "Node.h"
using namespace std;

class AATreePrettyPrinter
{
public:
    static void printPretty(AATree<int> *tree, int level, int indentSpace, stringstream& out);

private:
    static int maxHeight(Node<int> * node, Node<int> * bottomNode);
    static string intToString(Node<int> *node);
    static void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node<int> *>& nodesQueue, stringstream& out);
    static void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node<int> *>& nodesQueue, stringstream& out);
    static void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<Node<int> *>& nodesQueue, stringstream& out);
};
#endif

