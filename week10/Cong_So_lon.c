#include <stdio.h>
#include <string.h>

// include stack element type
#define elType int
#include "stack_linkedlist.h"

#define MAX_NUMBER 10000

void StringToStack(char * nums, StackType ** numstack) {
	StackInitialize(numstack);
	for (int i = 0; i < strlen(nums); ++i) {
		if (nums[i] >= '0' && nums[i] <= '9') {
			StackPush(numstack, nums[i]-'0');
		}
	}
}

void StrIntCompare(char *num1s, char *num2s) {
	char num1[MAX_NUMBER];
	char num2[MAX_NUMBER];

	int i;
	// ignore 0 or other char in the beginning
	i = 0
	while (i < strlen(num1s)) {
		if (num1s[i] >= '1' || num1s[i] <= '9')
			break;
		i++;
	}

	strcpy('', num1);
	strcpy('', num2);
	while (i < strlen(num1s)) {
		num1 += 
		i++;
	}

}

int main(int argc, char const *argv[])
{
	char num1s[MAX_NUMBER];
	char num2s[MAX_NUMBER];
	StackType * num1;
	StackType * num2;

	printf("Nhap so thu nhat: "); scanf("%s", num1s);
	printf("Nhap so thu hai: "); scanf("%s", num2s);



	//============================== CALCULATE SUM =========================
	
	StringToStack(num1s, &num1);
	StringToStack(num2s, &num2);

	StackType * sum;
	StackInitialize(&sum);
	int remember;
	int a, b;
	int tmp_sum;

	remember = 0;

	while ((!StackIsEmpty(num1)) || (!StackIsEmpty(num2))) {
		if (StackIsEmpty(num1)) {
			a = 0;
		} else {
			a = StackPop(&num1);
		}

		if (StackIsEmpty(num2)) {
			b = 0;
		} else {
			b = StackPop(&num2);
		}

		tmp_sum = a+b+remember;
		StackPush(&sum, tmp_sum % 10);
		remember = tmp_sum/10;
	}

	if (remember) {
		StackPush(&sum, remember);
	}

	printf("Tong = ");
	while (!StackIsEmpty(sum)) {
		printf("%d", StackPop(&sum));
	}
	printf("\n");

	//============================== CALCULATE SUBTRACTION =========================


	printf("Hieu = ");
	if (StrIntCompare(num1s, num2s) > 0) {
		StringToStack(num1s, &num1);
		StringToStack(num2s, &num2);
	} else {
		StringToStack(num2s, &num1);
		StringToStack(num1s, &num2);
		printf("- "); // minus sign for result
	}

	StackType * sum;
	StackInitialize(&sum);
	int remember;
	int a, b;
	int tmp_sum;

	remember = 0;




	return 0;
}