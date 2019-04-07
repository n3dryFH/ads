#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>
#include "FixedCapacityStackOfStrings.h"

#define TASK 4

int main()
{
#if TASK == 1
	FixedCapacityStackOfStrings stack(5);
	if (stack.isEmpty())
		std::cout << "Stack is empty!" << std::endl;
	stack.push("str1");
	assert(!stack.isFull());
	stack.push("str2");
	stack.push("str3");
	stack.push("str4");	
	assert(stack.peek() == "str4");
	stack.push("str5");
	assert(stack.peek() == "str5");
	stack.push("str6");
	assert(stack.isFull());

	stack.print();
	
	stack.pop();
	stack.pop();
	stack.pop();
	stack.pop();
	assert(!stack.isEmpty());
	stack.pop();
	assert(stack.isEmpty());
	assert(stack.pop() == "str1");		

	stack.resize(3);
	stack.print();
#else
	FixedCapacityStackOfStrings OperandStack(5);
	FixedCapacityStackOfStrings OperatorStack(5);
	std::string line;
	while (std::getline(cin, line))
	{
		std::istringstream iss(line);
		std::string word;
		unsigned int operandCount = 0, operatorCount = 0;
		while (iss >> word)
		{
			if (word == "+" || word == "-" || word == "*" || word == "/")
			{
				if (OperatorStack.isFull())
					OperatorStack.resize(operatorCount + 5);
				OperatorStack.push(word);
				++operatorCount;
			}	
			else if (word == ")")
			{
				const std::string& str2 = OperandStack.pop();				
				const std::string& str1 = OperandStack.pop();
				operandCount -= 2;
				const std::string& opt = OperatorStack.pop();
				--operatorCount;
				std::string operandsWithOperator = "(" + str1 + opt + str2 + ")";
				OperandStack.push(operandsWithOperator);
				++operandCount;
			}
			else // todo check for int
			{
				if (OperandStack.isFull())
					OperandStack.resize(operandCount + 5);
				OperandStack.push(word);
				++operandCount;
			}
		}
		std::cout << OperandStack.peek() << std::endl;
	}

#endif
	system("PAUSE");
}