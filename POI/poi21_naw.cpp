#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 1000005;

int n;
priority_queue<int, vector<int>, greater<int>> pq;
int a[MAXN];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	pq.push(a[0]);
	string ans(n, ')');
	for (int i = 1; i <= n / 2; i++) {
		ans[pq.top() - 1] = '(';
		pq.pop();
		pq.push(a[2 * i - 1]);
		pq.push(a[2 * i]);
	}
	{
		int b = 0;
		for (int i = 0; i < n; i++) {
			if (ans[i] == '(')
				b++;
			else
				b--;
			if (b < 0) {
				cout << "NIE\n";
				return 0;
			}
		}
	}
	cout << ans << endl;
}
