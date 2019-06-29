#include <stdlib.h>
#include <string.h>

struct node {
	char *s;
	struct node *next;
};

#define	MULTI	31
#define NBIN	29989

struct node *a[NBIN];

unsigned int hash(char *s)
{
	unsigned int h = 0;

	while (*s) {
		h = MULTI * h + *s;
		s++;
	}

	return h % NBIN;
}

void insert(char *s)
{
	if (!s) {
		return;
	}

	int i = hash(s);

	struct node *curr = a[i];
	while (curr) {
		if (!strcmp(curr->s, s)) {
			return;
		}
		curr = curr->next;
	}

	// reach here when we do not
	// have string s in the hash table
	curr = (struct node *)malloc(sizeof(struct node));
	curr->s = (char *)malloc(strlen(s) + 1);
	strcpy(curr->s, s);

	// insert
	curr->next = a[i];
	a[i] = curr;
}

int main(int argc, char *argv[])
{
	int i;

	for (i = 0; i < NBIN; i++) {
		a[i] = NULL;
	}

	insert("hello");
	insert("world");

	return 0;
}
