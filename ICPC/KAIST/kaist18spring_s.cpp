#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

vector<string> str = {"New Customer", "Promising",			"About to Sleep", "Hibernating",
					  "Lost",		  "Potential Loyalist", "Need Attention", "About to Leave",
					  "Champion",	  "Loyal Customer",		"Can't Lose Them"};
int mp[5][5] = {{0, 1, 2, 4, 4}, {5, 5, 2, 3, 4}, {5, 5, 6, 7, 7}, {9, 9, 9, 7, 7}, {8, 9, 9, 7, 10}};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	vector<int> r(4), f(4);
	for (auto &x : r)
		cin >> x;
	for (auto &x : f)
		cin >> x;
	sort(all(r));
	sort(all(f));
	int q;
	cin >> q;
	map<string, int> fr, ls;
	map<string, int> freq, las;
	for (int i = 1; i <= q; i++) {
		string x, y;
		cin >> x >> y;
		if (x == "1")
			las[y] = i, freq[y]++;
		else if (!freq.count(y))
			cout << "None\n";
		else {
			int cnt1 = lower_bound(all(f), freq[y]) - f.begin();
			int cnt2 = lower_bound(all(r), i - las[y]) - r.begin();
			cout << str[mp[cnt1][cnt2]] << '\n';
		}
	}
}