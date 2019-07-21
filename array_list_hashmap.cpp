class MyHashMap {
public:
	/** Initialize your data structure here. */
	MyHashMap() {
		for (int i = 0; i < NBIN; i++) {
			bins[i] = NULL;
		}
	}

	/** value will always be non-negative. */
	void put(int key, int value) {
		int i = hash(key);

		node *curr = bins[i];
		while (curr) {
			if (curr->key == key) {
				curr->value = value;
				return;
			}
			curr = curr->next;
		}
		// reach here when key is not present
		curr = new node(key, value, bins[i]);
		bins[i] = curr;
	}

	/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
	int get(int key) {
		int i = hash(key);

		node *curr = bins[i];
		while (curr) {
			if (curr->key == key) {
				return curr->value;
			}
			curr = curr->next;
		}

		return -1;
	}

	/** Removes the mapping of the specified value key if this map contains a mapping for the key */
	void remove(int key) {
		int i = hash(key);

		bins[i] = _remove(key, bins[i]);
	}

private:
	static const int NBIN = 10000;

	struct node {
		node(int k, int v, node *n = NULL) : key(k), value(v), next(n) {
		}

		int key;
		int value;
		struct node *next;
	};

	node *bins[NBIN];

	int hash(int key) {
		return key % NBIN;
	}

	node *_remove(int key, node *curr) {
		if (!curr) {
			return NULL;
		}

		if (curr->key == key) {
			node *next = curr->next;
			delete curr;
			return next;
		}

		curr->next =  _remove(key, curr->next);
		return curr;
	}
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
