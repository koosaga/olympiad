#include "robot.h"
#include <bits/stdc++.h>
using namespace std;

enum { Wall = -2, Block, Empty, Path, Aux, West, South, East, North };

pair<int, char> solve(vector<int> S) {
	// Start path.
	if (S[1] == Wall && S[4] == Wall) {
		if (S[0] == Empty) {
			return {Aux, 'H'};
		}
	}
	// End path.
	if (S[2] == Wall && S[3] == Wall) {
		for (int i = 1; i <= 4; i++) {
			if (S[i] == Aux) {
				return {Path, "WSEN"[i - 1]};
			}
		}
	}
	// Exploration mode.
	if (S[0] == Aux) {
		bool cleanup = (count(S.begin() + 1, S.end(), Path) > 0);
		if (cleanup) {
			// before passing to Path, add childs.
			for (int i = 1; i <= 4; i++) {
				if (S[i] == Empty) {
					return {Aux, "WSEN"[i - 1]};
				}
			}
			return {Path, 'H'};
		}
		for (int i = 1; i <= 4; i++) {
			if (3 <= S[i] && S[i] <= 6 && ((S[i] - 3) ^ (i - 1)) == 2) {
				return {Aux, "WSEN"[i - 1]};
			}
		}
		return {Path, 'H'};
	}
	// Change to exploration mode.
	if (3 <= S[0] && S[0] <= 6) {
		bool cleanup = (count(S.begin() + 1, S.end(), Aux) == 0);
		if (cleanup) {
			// has leaf to descend
			for (int i = 1; i <= 4; i++) {
				if (3 <= S[i] && S[i] <= 6 && ((S[i] - 3) ^ (i - 1)) == 2) {
					return {S[0], "WSEN"[i - 1]};
				}
			}
			// it is leaf, just clean it
			return {Empty, "WSEN"[S[0] - 3]};
		}
		return {Aux, 'H'};
	}
	if (S[0] == Path) {
		bool cleanup = (count(S.begin() + 1, S.end(), Path) > 0);
		if (cleanup) {
			for (int i = 1; i <= 4; i++) {
				if (3 <= S[i] && S[i] <= 6 && ((S[i] - 3) ^ (i - 1)) == 2) {
					return {Path, "WSEN"[i - 1]};
				}
			}
			if (S[1] == Wall && S[4] == Wall) {
				return {Path, 'T'};
			}
		} else {
			for (int i = 1; i <= 4; i++) {
				if (S[i] == Empty) {
					return {Path, "WSEN"[i - 1]};
				}
			}
		}
		for (int i = 1; i <= 4; i++) {
			if (S[i] == Aux) {
				return {cleanup ? Path : Empty, "WSEN"[i - 1]};
			}
		}
		return {Empty, 'H'};
	}
	if (S[0] == Empty) {
		for (int i = 1; i <= 4; i++) {
			if (S[i] == Path || S[i] == Aux) {
				return {i + 2, "WSEN"[i - 1]};
			}
		}
	}
	return {-1, 'H'};
}

void program_pulibot() {
	vector<int> S(5);
	for (S[0] = -2; S[0] <= 6; S[0]++) {
		for (S[1] = -2; S[1] <= 6; S[1]++) {
			for (S[2] = -2; S[2] <= 6; S[2]++) {
				for (S[3] = -2; S[3] <= 6; S[3]++) {
					for (S[4] = -2; S[4] <= 6; S[4]++) {
						auto [z, a] = solve(S);
						if (z != -1)
							set_instruction(S, z, a);
					}
				}
			}
		}
	}
}
