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

// Xoá số 0 thừa ở đầu và chỉ lấy các chữ số 0->9
void StandardlizeStrNum (char * num, char * num_out) {

	char num_std[MAX_NUMBER];

	int i;
	// ignore 0 or other char in the beginning
	i = 0;
	while (i < strlen(num)) {
		if (num[i] >= '1' && num[i] <= '9')
			break;
		i++;
	}

	num_std[0] = '\0';

	while (i < strlen(num)) {
		if (num[i] >= '0' && num[i] <= '9') {
			num_std[strlen(num_std)+1] = '\0';

			num_std[strlen(num_std)] = num[i];
		}

		i++;
	}


	if (strcmp(num_std, "") == 0) {
		strcpy(num_std, "0");
	}

	strcpy(num_out, num_std);

}

// So sánh 2 số dương (ở dạng xâu)
int StrIntCompare(char *num1s, char *num2s) {
	char num1[MAX_NUMBER];
	char num2[MAX_NUMBER];

	StandardlizeStrNum(num1s, num1);
	StandardlizeStrNum(num2s, num2);


	if (strlen(num1) > strlen(num2)) {
		return 1;
	} else if (strlen(num2) > strlen(num1)) {
		return -1;
	} else {
		for (int i = 0; i < strlen(num1); ++i) {
			if (num1[i] > num2[i]) {
				return 1;
			} else if (num1[i] < num2[i]) {
				return -1;
			}
		}
	}
	return 0;

}

int main(int argc, char const *argv[])
{
	char num1s[MAX_NUMBER];
	char num2s[MAX_NUMBER];
	StackType * num1;
	StackType * num2;

	printf("Nhap so thu nhat: "); scanf("%s", num1s);
	printf("Nhap so thu hai: "); scanf("%s", num2s);

	StandardlizeStrNum(num1s, num1s);
	StandardlizeStrNum(num2s, num2s);

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

	printf("%s + %s = ", num1s, num2s);
	while (!StackIsEmpty(sum)) {
		printf("%d", StackPop(&sum));
	}
	printf("\n");

	//============================== CALCULATE SUBTRACTION =========================

	printf("%s - %s = ", num1s, num2s);
	if (StrIntCompare(num1s, num2s) > 0) {
		StringToStack(num1s, &num1);
		StringToStack(num2s, &num2);
	} else {
		StringToStack(num2s, &num1);
		StringToStack(num1s, &num2);
		printf("-"); // minus sign for result
	}

	StackType * subtract;
	StackInitialize(&subtract);

	remember = 0;
	int tmp_subtract = 0;

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

		b += remember; 


		if (a - b < 0) {
			a += 10;
			remember = 1;
		} else {
			remember = 0;
		}

		tmp_subtract = a-b;

		StackPush(&subtract, tmp_subtract);
	}

	while (!StackIsEmpty(subtract)) {
		printf("%d", StackPop(&subtract));
	}
	printf("\n");


	return 0;
}