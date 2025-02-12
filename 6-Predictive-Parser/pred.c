#include <stdio.h>
#include <string.h>

char input[20];
int len, ln, err = 0;

void E();
void E1();
void T();
void T1();
void F();
void match(char topChar);

void E() {
	T();
	E1();
}

void E1() {
	if (*input == '+') {
    	match('+');
    	T();
    	E1();
	} else return;
}

void T() {
	F();
	T1();
}

void T1() {
	if (*input == '*') {
    	match('*');
    	F();
    	T1();
	} else return;
}

void F() {
	if (*input == '(') {
    	match('(');
    	E();
    	match(')');
	} else match('i');
}

void match(char topChar) {
	if (*input == topChar) {
    	printf("\nPopped %c, input is now: %s", topChar, input + 1);  // Display the character popped and the remaining string
    	ln++;
    	// Shift the input string left to remove the matched character
    	memmove(input, input + 1, strlen(input));  // Move all characters to the left
	} else {
    	printf("\nError: %c didn't match at this point", *input);
    	err++;
	}
}

int main() {
	printf("Enter the Input: ");
	fgets(input, sizeof(input), stdin);

	// Remove the newline character if present
	len = strlen(input);
	if (input[len - 1] == '\n') {
    	input[len - 1] = '\0';
    	len--;
	}

	// Append the end-of-input symbol '$'
	input[len] = '$';
	input[len + 1] = '\0';

	ln = 0;  // Initialize ln to 0

	E();  // Start parsing

	// Check if parsing was successful
	if (err == 0 && ln == len) {
    	printf("\n\nString parsed successfully!!!");
	} else {
    	printf("\n\nString is not parsed successfully.\nErrors occurred or input contains invalid characters.\n");
	}

	return 0;
}
