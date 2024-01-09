#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QString>
#include <QStack>
#include <bits/stdc++.h>

class calculator
{
public:
    calculator();
    QString calculate(QString expression);
    ~calculator();
private:
    QStack<int> operend_stack;
    int prec(QChar c);
    QChar associativity(QChar c);
    QString convertToPostfix(QString infix_expr);
};

#endif // CALCULATOR_H
