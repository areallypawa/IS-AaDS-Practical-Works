#pragma once
#include <iostream>
#include <string>
#include "../Stack/Stack.h"

using namespace std;

int priority(const string& op)
{
    if (op == "+" || op == "-")
        return 1;

    if (op == "*" || op == "/")
        return 2;

    if (op == "^")
        return 3;

    if (op == "sin" || op == "cos")
        return 4;
        
    return 0;
}

bool isOperator(const string& op)
{
    return op == "+" || op == "-" ||
        op == "*" || op == "/" ||
        op == "^";
}

bool isFunction(const string& op)
{
    return op == "sin" || op == "cos";
}

string shuntingYard(const string& expression)
{
    Stack<string> stack;
    string result;

    for (size_t i = 0; i < expression.length(); i++)
    {
        char c = expression[i];

        if (c == ' ')
            continue;

        // Цифра
        if (c >= '1' && c <= '9')
        {
            result += c;
            result += ' ';
        }

        // sin
        else if (expression.substr(i, 3) == "sin")
        {
            stack.push("sin");
            i += 2;
        }

        // cos
        else if (expression.substr(i, 3) == "cos")
        {
            stack.push("cos");
            i += 2;
        }

        // Открывающая скобка
        else if (c == '(')
        {
            stack.push("(");
        }

        // Закрывающая скобка
        else if (c == ')')
        {
            while (!stack.empty() && stack.top() != "(")
            {
                result += stack.top();
                result += ' ';
                stack.pop();
            }

            if (!stack.empty() && stack.top() == "(")
                stack.pop();

            // Если перед скобкой была функция
            if (!stack.empty() && isFunction(stack.top()))
            {
                result += stack.top();
                result += ' ';
                stack.pop();
            }
        }

        // Оператор
        else if (isOperator(string(1, c)))
        {
            string current(1, c);

            while (!stack.empty() &&
                stack.top() != "(" &&
                priority(stack.top()) >= priority(current))
            {
                result += stack.top();
                result += ' ';
                stack.pop();
            }

            stack.push(current);
        }
    }

    // Вытаскиваем оставшиеся операторы
    while (!stack.empty())
    {
        result += stack.top();
        result += ' ';
        stack.pop();
    }

    return result;
}
