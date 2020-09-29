//
//  PrettyPrinter.h
//
#ifndef _PRETTYPRINTREE_CPP_
#define _PRETTYPRINTREE_CPP_

#include <fstream>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>
#include "Node.h"
using namespace std;

class PrettyPrinter
{
public:
    static void printPretty(Node<int> *root, int level, int indentSpace, stringstream& out);

private:
    static int maxHeight(Node<int> * node);
    static string intToString(int val);
    static void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node<int> *>& nodesQueue, stringstream& out);
    static void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Node<int> *>& nodesQueue, stringstream& out);
    static void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<Node<int> *>& nodesQueue, stringstream& out);
};
#endif

