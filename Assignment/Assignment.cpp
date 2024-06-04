#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <cctype>
#include <vector>

bool isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op) {
  if (op == '+' || op == '-') {
    return 1;
  }
  if (op == '*' || op == '/') {
    return 2;
  }
  return 0;
}

double applyOperation(double a, double b, char op) {
  switch (op) {
  case '+': return a + b;
  case '-': return a - b;
  case '*': return a * b;
  case '/': return a / b;
  default: return 0;
  }
}

std::vector<std::string> tokenize(const std::string& expression) {
  std::vector<std::string> tokens;
  std::istringstream iss(expression);
  std::string token;
  while (iss >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

std::vector<std::string> infixToPostfix(const std::vector<std::string>& tokens) {
  std::vector<std::string> output;
  std::stack<char> operators;

  for (const auto& token : tokens) {
    if (isdigit(token[0])) {
      output.push_back(token);
    }
    else if (isOperator(token[0])) {
      while (!operators.empty() && precedence(operators.top()) >= precedence(token[0])) {
        output.push_back(std::string(1, operators.top()));
        operators.pop();
      }
      operators.push(token[0]);
    }
  }

  while (!operators.empty()) {
    output.push_back(std::string(1, operators.top()));
    operators.pop();
  }

  return output;
}

double evaluatePostfix(const std::vector<std::string>& tokens) {
  std::stack<double> values;

  for (const auto& token : tokens) {
    if (isdigit(token[0])) {
      values.push(std::stod(token));
    }
    else if (isOperator(token[0])) {
      double b = values.top(); values.pop();
      double a = values.top(); values.pop();
      values.push(applyOperation(a, b, token[0]));
    }
  }

  return values.top();
}

int main() {
  std::string expression;
  std::cout << "Enter an expression to evaluate: ";
  std::getline(std::cin, expression);

  // Insert spaces around operators for tokenization
  for (size_t i = 0; i < expression.length(); ++i) {
    if (isOperator(expression[i])) {
      expression.insert(i, " ");
      expression.insert(i + 2, " ");
      i += 2;
    }
  }

  auto tokens = tokenize(expression);
  auto postfix = infixToPostfix(tokens);
  double result = evaluatePostfix(postfix);

  std::cout << "Result: " << result << std::endl;

  return 0;
}
