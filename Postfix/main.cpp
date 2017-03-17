#include <iostream>
#include <assert.h>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

bool is_operator(const char& c) {
  return c == '+' || c == '-' || c == '*' || c == '/' ;
}

bool is_operand(const char& c) {
  return (c >= '0' && c <= '9');
}

int calculate(const string& input) {
  stack<char> stack;	
  char operand1;
  char operand2;

  for(int i(0); i < input.size(); ++i) {
    if(is_operand(input[i])) { 
      assert(input[i] >= '0' && input[i] <= '9');
      stack.push(input[i]); continue;
    }
    if(is_operator(input[i])) {
      assert(stack.size() >= 2);
      operand1 = stack.top();
      stack.pop();
      operand2 = stack.top();
      stack.pop();
      switch(input[i]) {
        case'+':{ stack.push((operand2-'0') + (operand1-'0') + '0');continue; }
        case'-':{ stack.push((operand2-'0') - (operand1-'0') + '0');continue; }
        case'*':{ stack.push((operand2-'0') * (operand1-'0') + '0');continue; }
        case'/':{ stack.push((operand2-'0') / (operand1-'0') + '0');continue; }
      }
    }
  }
  int result = stack.top() - '0';
  stack.pop();
  return result;
}

int main(int argc, char* argv[]) {
  if (argc != 2 ) {
    cout << "You must input a file path!\n";
    return 1;
  }
  else {
    fstream f;
    string expression;
    string data;
    f.open(argv[1], ios::in);
    getline(f, data); 
    while(data != "") {
      expression.append(data);
      getline(f, data);
    }
    f.close(); 
    cout<<"result: " << calculate(expression) << endl;
  }
  return 0;
}
