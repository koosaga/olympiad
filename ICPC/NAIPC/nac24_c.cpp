#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
using pi = array<int, 2>;

namespace FUCK {
bool isval(char v) {
	if ('a' <= v && v <= 'z') {
		return true;
	}
	return '0' == v || '1' == v || 'x' == v || 'y' == v;
}

int isop(char v) {
	if ('^' == v) {
		return 1;
	}
	if ('|' == v) {
		return 2;
	}
	if ('&' == v) {
		return 3;
	}
	if ('=' == v) {
		return 4;
	}
	if ('!' == v) {
		return 5;
	}
	return 99;
}

string conv(string S) {
	vector<char> V;

	string ret;
	for (char c : S) {
		if (isval(c)) {
			ret.push_back(c);
			continue;
		}

		int op = isop(c);

		if ('(' == c) {
			V.emplace_back('(');
			continue;
		} else if (')' == c) {
			while (!V.empty() && '(' != V.back()) {
				ret.push_back(V.back());
				V.pop_back();
			}
			assert(V.back() == '(');
			V.pop_back();
			continue;
		}

		if ('!' == c) {
			// 0 =
			ret.push_back('0');
			c = '=';
			op = isop('=');
		}

		while (!V.empty() && '(' != V.back() && op <= isop(V.back())) {
			ret.push_back(V.back());
			V.pop_back();
		}

		V.emplace_back(c);
	}

	while (!V.empty()) {
		ret.push_back(V.back());
		V.pop_back();
	}

	return ret;
}

struct RET {
	// x val, y val
	int ans[2][2];
};

int compute(string S, int x, int y) {
	vector<int> V;

	for (char v : S) {
		if ('0' == v) {
			V.emplace_back(0);
		} else if ('1' == v) {
			V.emplace_back(1);
		} else if ('x' == v) {
			V.emplace_back(x);
		} else if ('y' == v) {
			V.emplace_back(y);
		} else {
			assert(2 <= V.size());
			int a = V.back();
			V.pop_back();
			int b = V.back();
			V.pop_back();

			if ('=' == v) {
				V.emplace_back(a == b);
			} else if ('&' == v) {
				V.emplace_back(a & b);
			} else if ('|' == v) {
				V.emplace_back(a | b);
			} else if ('^' == v) {
				V.emplace_back(a ^ b);
			} else {
				assert(false);
			}
		}
	}

	assert(1 == V.size());
	return V[0];
}

RET calc(string S) {
	string V = conv(S);

	RET ret;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++)
			ret.ans[i][j] = compute(V, i, j);
	}

	return ret;
}

void test() { cout << conv("!a&!!!!!b=!c=!(a=b&c^d=e)") << endl; }
} // namespace FUCK

pi whatif[10][10][2][2]; // (time, returns)
bitset<1024> F[1024], R[1024];
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 2; k++) {
				for (int l = 0; l < 2; l++) {
					whatif[i][j][k][l] = pi{int(1e9), -1};
				}
			}
		}
	}
	for (int t = 0; t < n; t++) {
		int a, b;
		string expr;
		int d;
		cin >> a >> b >> expr >> d;
		auto z = FUCK::calc(expr);
		a--;
		b--;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				if (z.ans[i][j]) {
					whatif[a][b][i][j] = min(whatif[a][b][i][j], pi{t, d});
				}
				//	cout << z.ans[i][j];
			}
		}
		//	cout << endl;
	}
	{
		int z;
		cin >> z;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				for (int k = 0; k < 2; k++) {
					for (int l = 0; l < 2; l++) {
						if (whatif[i][j][k][l][0] > 1e8) {
							whatif[i][j][k][l][1] = z;
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < (1 << k); i++) {
		for (int j = 0; j < (1 << k); j++) {
			pi ret = pi{int(2e9), -1};
			for (int a = 0; a < k; a++) {
				for (int b = 0; b < k; b++) {
					ret = min(ret, whatif[a][b][(i >> a) & 1][(j >> b) & 1]);
				}
			}
			F[i][j] = ret[1];
			R[j][i] = ret[1];
		}
	}
	{
		int ans = 0;
		for (int i = 0; i < (1 << k); i++)
			if (F[i][i])
				ans++;
		cout << ans << " ";
	}
	{
		int ans = 0;
		for (int i = 0; i < (1 << k); i++) {
			for (int j = 0; j < (1 << k); j++) {
				if (F[i][j] && F[j][i])
					ans++;
			}
		}
		cout << ans << " ";
	}
	{

		int ans = 0;
		for (int i = 0; i < (1 << k); i++) {
			for (int j = 0; j < (1 << k); j++) {
				if (F[i][j] == 0)
					ans += (F[i] & R[j]).count();
			}
		}
		cout << ans << "\n";
	}
}