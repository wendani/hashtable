struct node {
	char *s;
	struct node *next;
};

#define	MULTI	31
#define NBIN	29989

unsigned int hash(char *s)
{
	unsigned int h = 0;

	while (*s) {
		h = MULTI * h + *s;
		s++;
	}

	return h % NBIN;
}

void insert(struct node **a, char *s)
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
