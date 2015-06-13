// Currently only deal with binary operator + - * / %,
// which are left associative, and ( ).
// The operands are integers.
// Currently no check on the validity of the expression.
// Reference: https://en.wikipedia.org/wiki/Shunting-yard_algorithm
#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

int Precedence(char op) {
  if (op == '*' || op == '/' || op == '%')
    return 2;
  if (op == '+' || op == '-')
    return 1;
  return 0;
}

void InfixToPostfix(const string& str, vector<string>& postfix) {
  stack<char> operator_stack;
  for (int i = 0; i < str.size(); ++i) {
    if (str[i] == ' ')
      continue;
    if ('0' <= str[i] && str[i] <= '9') {
      string number(1, str[i]);
      ++i;
      while (i < str.size() && '0' <= str[i] && str[i] <= '9')
        number += str[i++];
      --i;
      postfix.push_back(number);
    } else if (str[i] == '(') {
      operator_stack.push(str[i]);
    } else if (str[i] == ')') {
      while (operator_stack.top() != '(') {
        postfix.push_back(string(1, operator_stack.top()));
        operator_stack.pop();
      }
      operator_stack.pop();
    } else {
      if (operator_stack.empty() || operator_stack.top() == '(') {
        operator_stack.push(str[i]);
      } else {
        while (!operator_stack.empty() && operator_stack.top() != '(' &&
               Precedence(str[i]) <= Precedence(operator_stack.top())) {
          postfix.push_back(string(1, operator_stack.top()));
          operator_stack.pop();
        }
        operator_stack.push(str[i]);
      }
    }
  }
  while (!operator_stack.empty()) {
    postfix.push_back(string(1, operator_stack.top()));
    operator_stack.pop();
  }
}

int Operate(char op, int first, int second) {
  switch (op) {
    case '+':
      return first + second;
    case '-':
      return first - second;
    case '*':
      return first * second;
    case '/':
      return first / second;
    case '%':
      return first % second;
    default:
      return 0;
  }
}

int Evaluate(const vector<string>& postfix) {
  stack<int> operand_stack;
  for (int i = 0; i < postfix.size(); ++i) {
    if (postfix[i] == "+" || postfix[i] == "-" || postfix[i] == "*" ||
        postfix[i] == "/" || postfix[i] == "%") {
      int second = operand_stack.top();
      operand_stack.pop();
      int first = operand_stack.top();
      operand_stack.pop();
      int result = Operate(postfix[i][0], first, second);
      operand_stack.push(result);
    } else {
      operand_stack.push(std::atoi(postfix[i].c_str()));
    }
  }
  return operand_stack.top();
}

int main() {
  string infix;
  vector<string> postfix;
  while (getline(cin, infix)) {
    postfix.clear();
    InfixToPostfix(infix, postfix);
    cout << "The Postfix Notation(RPN) is :" << endl;
    for (int i = 0; i < postfix.size(); ++i)
      cout << postfix[i] << ' ';
    cout << endl << "The value of the expression is :" << endl;
    cout << Evaluate(postfix) << endl;
  }
  return 0;
}
