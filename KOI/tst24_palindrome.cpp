#include <bits/stdc++.h>
using namespace std;
using lint = long long;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

extern int count_pair(int, int, int);
extern int find_character(int, std::vector<int>);

int guess_palindromicity(int N) {
	vector<int> ones;
	for (int i = 0; i < (N - 1) / 2; i++) {
		int w = count_pair(i, N - 1 - i, N / 2);
		if (w == 1) {
			ones.push_back(i);
			ones.push_back(N - 1 - i);
		}
		else if (w != 3) return false;
	}
	if (N % 2 == 1) {
		if (sz(ones) == 0 || find_character(N / 2, ones) == 0) {
			return true;
		}
		return false;
	}
	if (sz(ones) == 0) {
		int w = count_pair(0, N / 2 - 1, N / 2);
		return (w == 3);
	}
	if (find_character(N / 2, ones) != 0)
		return false;
	int w1 = count_pair(ones[0], N - 1 - ones[0], N / 2 - 1);
	int w2 = count_pair(ones[0], N / 2, N / 2 - 1);
	return w1 == 1 && w2 == 1;
}
