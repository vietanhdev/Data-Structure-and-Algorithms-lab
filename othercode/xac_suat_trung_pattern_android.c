#include <stdio.h>
int n = 0; // number of cases
int node[9] = {0}; // flag the node we've gone through
int line[8][3] = { // index of nodes in a line
	{0, 1, 2},
	{3, 4, 5},
	{6, 7, 8},
	{0, 3, 6},
	{1, 4, 7},
	{2, 5, 8},
	{0, 4, 8},
	{2, 4, 6}
};
int checkBetween(int a, int b) { // return 1: a cannot go from a to b; 0: other case
	for (int i = 0; i < 8; ++i)
	{
		if (node[line[i][1]]==0 && ((a==line[i][0] && b==line[i][2]) || (b==line[i][0] && a==line[i][2]))) {
			return 1;
		}
	}
	return 0;
}
int goOK(int a, int b) { // Check validity going from a to b
	if (a==b || node[b] || checkBetween(a, b))
		return 0;
	else
		return 1;
}
void go(from, more) { // Try a move; from: starting point, more: number of left nodes
	if (more == 0) {
		n++;
		return;
	}
	for (int i = 0; i < 9; ++i)
	{
		if (goOK(from, i)) {
			node[i] = 1;
			go(i, more-1);
			node[i] = 0;
		}	
	}
}
int main(int argc, char const *argv[])
{
	for (int i = 0; i < 9; ++i)
	{
		node[i] = 1;
		go(i, 3);
		node[i] = 0;
	}
	printf("Number of cases: %d\n", n);
	return 0;
}