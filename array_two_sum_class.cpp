#include <iostream>
#include <vector>
#include <mutex>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class TwoSum
{
public:
    TwoSum(void){
    }
    ~TwoSum(void) {
    }

    void append(int x) {
        a.push_back(x);
    }

    void deleteTail() {
        if (a.empty()) {
            return;
        }
        a.pop_back();
    }

    bool isExist(int target) {
        unordered_set<int> aSet;
        for (const auto &i : a) {
            if (aSet.count(target - i)) {
                return true;
            }
            else {
                aSet.insert(i);
            }
        }
        return false;
    }

private:
    vector<int> a;
};

class TwoSum1
{
public:
    TwoSum1(void) {
    }
    ~TwoSum1(void) {
    }

    void append(int x)
    {
        lock_guard<mutex> lkMgr(mtx);

        for (const auto &i : a) {
            int sum = i + x;
            auto it = sumCnt.find(sum);
            if (it != sumCnt.end()) {
                it->second++;
            }
            else {
                sumCnt.emplace(sum, 1);
            }
        }
        a.push_back(x);
    }

    void deleteTail(void)
    {
        lock_guard<mutex> lkMgr(mtx);

        if (a.empty()) {
            return;
        }

        int x = a.back();
        a.pop_back();
        for (const auto &i : a) {
            int sum = x + i;
            auto it = sumCnt.find(sum);
            if (it != sumCnt.end()) {
                it->second--;
                if (it->second == 0) {
                    sumCnt.erase(it);
                }
            }
        }
    }

    bool isExist(int k)
    {
        lock_guard<mutex> lkMgr(mtx);
        return sumCnt.find(k) == sumCnt.end() ? false : true;
    }

private:
    vector<int> a;
    unordered_map<int, int> sumCnt;
    mutex mtx;
};

bool isExist(vector<int> &a, int target)
{
    unordered_set<int> aSet;
    for (const auto &i : a) {
        if (aSet.count(target - i)) {
            return true;
	}
	else {
            aSet.insert(i);
	}
    }
    return false;
}

bool isExist1(vector<int> &a, int target)
{
    sort(a.begin(), a.end());

    int i = 0;
    int j = a.size() - 1;
    while (i < j) {
        if (a[i] + a[j] == target) {
            return true;
        }
        else if (a[i] + a[j] > target) {
            j--;
        }
        else {
            // a[i] + a[j] < target
            i++;
        }
    }
    return false;
}


int main() {
    TwoSum twoSum;

    twoSum.append(1);
    twoSum.append(2);
    twoSum.append(4);
    twoSum.append(-1);

    int target = 3;
    if (twoSum.isExist(target)) {
        cout << target << ": " << "true" << endl;
    } else {
        cout << target << ": " << "false" << endl;
    }


    TwoSum1 twoSum1;

    twoSum1.append(1);
    twoSum1.append(2);
    twoSum1.append(4);
    twoSum1.append(-1);

    target = 0;
    if (twoSum1.isExist(target)) {
        cout << target << ": " << "true" << endl;
    } else {
        cout << target << ": " << "false" << endl;
    }
    twoSum1.deleteTail();
    if (twoSum1.isExist(target)) {
        cout << target << ": " << "true" << endl;
    } else {
        cout << target << ": " << "false" << endl;
    }
    return 0;
};
