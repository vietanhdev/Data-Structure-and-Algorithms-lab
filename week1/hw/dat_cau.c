#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// article > N > V > preposition > article > N

char * article[5] = {"the", "a", "one", "some", "any"};
char * noun[5] = {"boy", "girl", "dog", "town", "car"};
char * verb[5] = {"drove", "jumped", "ran", "walked", "skipped"};
char * preposition[5] = {"to", "from", "over", "under", "on"};

int main(int argc, char *argv[])
{
  char s[100];
  int rannum;
    for (int i = 1; i < 10; i++) {
      	printf("%d: ", i);

		s[0] = 0; // empty s string

		rannum = rand()%5;
		snprintf(s, sizeof(s), "%s %s", s, article[rannum]);

		rannum = rand()%5;
		snprintf(s, sizeof(s), "%s %s", s, noun[rannum]);

		rannum = rand()%5;
		snprintf(s, sizeof(s), "%s %s", s, verb[rannum]);

		rannum = rand()%5;
		snprintf(s, sizeof(s), "%s %s", s, preposition[rannum]);

		rannum = rand()%5;
		snprintf(s, sizeof(s), "%s %s", s, article[rannum]);

		rannum = rand()%5;
		snprintf(s, sizeof(s), "%s %s", s, noun[rannum]);
		
		printf("%s\n", s);
    }
    return 0;
}
