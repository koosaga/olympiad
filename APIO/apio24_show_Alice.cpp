

#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
#include "Alice.h"

// you may define some global variables, but it does not work if you try to transfer any information from function Alice() to function Bob() through these variables.
// you had better not use the same global variables in function Alice() and in function Bob().

std::vector<std::pair<int, int>> Alice() {
	lint x = setN(1557);
	vector<pi> trees;
	for (int i = 1; i < 1557; i++) {
		trees.emplace_back(x % i + 1, i + 1);
	}
	return trees;
}
