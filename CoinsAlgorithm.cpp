#include <iostream>
#include <vector>
#include <set>

using namespace std;

// the function bellow finds all possible combinations of coins (that sum to a value n) using a backtracking approach (recursive)
void findCombinations(int n, int index, const vector<int>& coins, vector<int>& current, set<vector<int>>& result) {
    // if the remaining value is 0, the combination is added to the result set
    if (n == 0) {
        result.insert(current);
        return;
    }
    // it indicates when there is no combinations left (no more coins or when the remaining value is negative)
    if (n < 0 || index >= coins.size()) {
        return;
    }

    // uses the current coin in all possible ways
    for (int count = 0; count <= n / coins[index]; count++) {
        current[index] = count; // Define a quantidade da moeda atual

        // recursion
        findCombinations(n - count * coins[index], index + 1, coins, current, result);
    }

    current[index] = 0; // reset
}

// the function bellow creates the initial variables, calls the recursive function and returns the set(result)
vector<vector<int>> makeChange(int n) {
    vector<int> coins = {25, 10, 5, 1};
    vector<int> current(4, 0);
    set<vector<int>> result;

    findCombinations(n, 0, coins, current, result);

    return vector<vector<int>>(result.begin(), result.end());
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> combinations = makeChange(n);

    cout << "[";
    for (size_t i = 0; i < combinations.size(); i++) {
        cout << "[" << combinations[i][0] << "," << combinations[i][1] << "," 
             << combinations[i][2] << "," << combinations[i][3] << "]";
        if (i != combinations.size() - 1) {
            cout << ",";
        }
    }
    cout << "]";

    return 0;
}
