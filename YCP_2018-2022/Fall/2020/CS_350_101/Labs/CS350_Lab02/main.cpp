#include <stack>
#include <string>
#include <iostream>
#include <cstdlib>

int main()
{
    std::stack<int> stack;
    int operand_1, operand_2, sum;
    while (!std::cin.eof()) {
        std::string tok;
        if (!(std::cin >> tok) || tok == "END") {
            break;
        }

        // Debugging:
        std::cout << "Token: " << tok << std::endl;

        if (tok == "+") {
            // TODO: plus operator
            sum = operand_1 + operand_2;
        } else if (tok == "-") {
            // TODO: minus operator
            sum = operand_1 - operand_2;
        } else if (tok == "*") {
            // TODO: times operator
            sum = operand_1 * operand_2;
        } else if (tok == "/") {
            // TODO: divide operator
            sum = operand_1 / operand_2;
        } else {
            int value = atoi(tok.c_str());

            // TODO: an operand
            operand_1 == NULL ? value/10 : operand_2 = value/10;
            std::cout<<"stack: " << stack.top();
                stack.push(value);
        }
        operand_1 = sum;

    }

    // print the final result
    std::cout << "Result: " << stack.top() << std::endl;

    return 0;
}
