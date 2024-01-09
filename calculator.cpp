#include "calculator.h"

// Simple calculator
// Currently support 4 basic operation, and one-digit operend
// auxilary methods and conversion between infix and postfix -> Credit to geeksforgeeks.org
// https://www.geeksforgeeks.org/convert-infix-expression-to-postfix-expression/
calculator::calculator() = default;

int calculator::prec(QChar c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Function to return associativity of operators
QChar calculator::associativity(QChar c) {
    if (c == '^')
        return 'R';
    return 'L'; // Default to left-associative
}

// The main function to convert infix expression
// to postfix expression
QString calculator::convertToPostfix(QString infix_expr) {
    QStack<QChar> st;
    QString result;

    for (int i = 0; i < infix_expr.length(); i++) {
        QChar c = infix_expr[i];

        // If the scanned character is
        // an operand, add it to the output string.
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            result += c;

        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if (c == '(')
            st.push('(');

        // If the scanned character is an ‘)’,
        // pop and add to the output string from the stack
        // until an ‘(‘ is encountered.
        else if (c == ')') {
            while (st.top() != '(') {
                result += st.top();
                st.pop();
            }
            st.pop(); // Pop '('
        }

        // If an operator is scanned
        else {
            while (!st.empty() && prec(infix_expr[i]) < prec(st.top()) ||
                   !st.empty() && prec(infix_expr[i]) == prec(st.top()) &&
                       associativity(infix_expr[i]) == 'L') {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // Pop all the remaining elements from the stack
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }

    return result;
}

QString calculator::calculate(QString expression) {
    QString postfix_expr = convertToPostfix(expression);
    int temp;

    for (int i = 0; i < postfix_expr.length(); i++) {
        QChar c = postfix_expr[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            operend_stack.push(c.digitValue());
        else {
            temp = operend_stack.pop();
            if(c == '+') {
                temp = operend_stack.pop() + temp;
            } else if (c == '-') {
                temp = operend_stack.pop() - temp;
            } else if (c == '*') {
                temp = operend_stack.pop() * temp;
            } else {
                temp = operend_stack.pop() / temp;
            }
            operend_stack.push(temp);
        }
    }

    if (operend_stack.isEmpty() == false) {
        return QString::number(operend_stack.pop());
    } else {
        return "ERROR";
    }
}

calculator::~calculator() = default;
