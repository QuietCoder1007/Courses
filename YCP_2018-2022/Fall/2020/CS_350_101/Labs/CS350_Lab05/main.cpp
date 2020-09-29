#include <iostream>
#include <cstdlib>

// The linked list nodes are instances of this class
class Node {
public:
    explicit Node(int v) : value(v), next(nullptr) { }
    int value;
    Node *next;
};

int main()
{
    Node *head;
    Node *tail;

    // TODO: initialize the empty list (by assigning to head and tail)
    head = tail;

    // Get values from the user
    std::cout << "Enter integer values (-1 to end):" << std::endl;

    bool done = false;
    while (!done) {
        int userVal;
        std::cin >> userVal;

        if (userVal < 0) {
            done = true;
        } else {
            // TODO: append the value to the end (tail) of the linked list
            Node* input = new Node(userVal);
            head = input;
            input->next = tail;
            tail->next = NULL;
        }
    }

    std::cout << "Here are your values:" << std::endl;

    // TODO: print out the values, in order
//    Node *iter = NULL;
//    int i = 0;
//    while(iter->value != -1 || i < 10) {
//        iter = head;
//        std::cout << iter->value << std::endl;
//        head->next;
//        i++;
//    }

    // TODO: Cleanup memory


    return 0;
}
