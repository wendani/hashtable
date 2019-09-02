class Solution {
public:
	int numJewelsInStones(string J, string S) {
		int stoneCounts[58] = {0};

		for (const auto &s : S) {
			stoneCounts[s - 'A']++;
		}

		int cnt = 0;
		for (const auto &j : J) {
			cnt += stoneCounts[j - 'A'];
		}

		return cnt;
	}
};

class Solution {
public:
	int numJewelsInStones(string J, string S) {
		unordered_set<char> jewels;

		for (const auto &j : J) {
			jewels.insert(j);
		}

		int cnt = 0;
		for (const auto &s : S) {
			if (jewels.count(s)) {
				cnt++;
			}
		}

		return cnt;
	}
};

/*
 * Example 1:
 *
 * Input: J = "aA", S = "aAAbbbb"
 * Output: 3
 *
 * Example 2:
 *
 * Input: J = "z", S = "ZZ"
 * Output: 0
 */
