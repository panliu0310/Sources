#include <stdio.h>
#include <stdlib.h>

typedef struct stackCDT* stackADT;

typedef char stackElementT;

struct stackCDT {
	stackElementT elements[100];
	int count;
};

stackADT EmptyStack() {
	stackADT stack;
	stack = (stackADT)malloc(sizeof(struct stackCDT));
	if (stack)
	{
		stack->count = 0;
		return stack;
	}
}

void Push(stackADT stack, stackElementT element) {
	stack->elements[stack->count] = element;
	(stack->count)++;
}

stackElementT Pop(stackADT stack) {
	(stack->count)--;
	return stack->elements[stack->count];
}

int StackDepth(stackADT stack) {
	return stack->count;
}

int StackIsEmpty(stackADT stack) {
	if (stack->count == 0)
		return 1;
	else return 0;
}

int main() {
	char parentheses[100] = { 0 };
	scanf_s("%s", &parentheses, sizeof(parentheses));
	stackADT operandStack;
	operandStack = EmptyStack();
	for (int i = 0; i <= 99; i++)
	{
		if (parentheses[i] == '(')
			Push(operandStack, '(');
		if (parentheses[i] == ')')
			Pop(operandStack);
		if (parentheses[i] == 'T')
			 printf("%d",StackDepth(operandStack));
	}
	
	return 0;
}