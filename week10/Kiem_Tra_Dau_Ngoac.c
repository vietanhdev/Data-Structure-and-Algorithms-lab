#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Common stack
#define elType char
#include "stack_linkedlist.h"

#define MAX_LINE_LEN 1000

int main(int argc, char const *argv[])
{
	if (argc != 2) {
		printf("Nhap theo cu phap: ./Kiem_Tra_Dau_Ngoac <ten_file>\n");
		return 1;
	}

	const char * filename = argv[1];

	FILE * f;
	if ((f = fopen(filename, "r")) == NULL) {
		printf("Không thể mở file: %s\n", filename);
	}

	char line[MAX_LINE_LEN];
	int i;
	StackType * stack;

	StackInitialize(&stack);

	int checkPassed = 1;
	int lineCount = 0;
	while(!feof(f)) {
		lineCount++;
		fgets(line, MAX_LINE_LEN, f);

		for (i = 0; i < strlen(line); ++i) {

			// Xu li mo ngoac
			if (line[i] == '['){
				StackPush(&stack, ']');
			} else if (line[i] == '('){
				StackPush(&stack, ')');
			} else if (line[i] == '{'){
				StackPush(&stack, '}');
			}

			// Xu li dong ngoac
			if (line[i] == ']' || line[i] == ')' || line[i] == '}'){
				if (StackPop(&stack) != line[i]) {
					checkPassed = 0;
					printf("Dấu ngoặc sai ở dòng %d, kí tự %d\n%s\n", lineCount, i+1, line);
					return 0;
				}
			}

		}
	}

	if (!StackIsEmpty(stack)) {
		printf("Thiếu dấu đóng ngoặc!\n");
		return 0;
	}

	if (checkPassed) {
		printf("Tất cả các ngoặc đều đúng!\n");
	}


	fclose(f);
	return 0;
}