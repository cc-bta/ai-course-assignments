#include <iostream>
#include <sstream>

double calculate(double operand1, double operand2, char op) {
  switch (op) {
  case '+': return operand1 + operand2;
  case '-': return operand1 - operand2;
  case '*': return operand1 * operand2;
  case '/': return operand1 / operand2;
  default: return 0; // This case should never be reached
  }
}

int main() {
  std::string expression;
  std::cout << "Enter an expression (e.g., 2 + 3): ";
  std::getline(std::cin, expression);

  std::istringstream iss(expression);
  double operand1, operand2;
  char op;

  iss >> operand1 >> op >> operand2;

  double result = calculate(operand1, operand2, op);
  std::cout << "Result: " << result << std::endl;

  return 0;
}
