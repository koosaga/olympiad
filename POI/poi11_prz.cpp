#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using point = complex<double>;

int inv(vector<int> a){
	int cnt = 0;
	for(int i = 0; i < sz(a); i++){
		for(int j = 0; j < i; j++){
			if(a[j] > a[i]) cnt++;
		}
	}
	return cnt;
}

int main(){	
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n; cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	vector<int> seqs;
	if(inv(a) % 2){
		seqs.push_back(1);
		rotate(a.begin(), a.begin() + n - 1, a.end());
		if(inv(a) % 2){
			cout << "NIE DA SIE\n";
			return 0;
		}
	}
	for(int i = 0; i < n; i++){
		int pos = find(all(a), i + 1) - a.begin();
		while(pos >= i + 2){
			pos -= 2;
			if(pos) seqs.push_back(n - pos);
			rotate(a.begin() + pos, a.begin() + pos + 2, a.begin() + pos + 3);
			seqs.push_back(-1);
			if(pos) seqs.push_back(pos);
		}
		if(pos == i + 1){
			pos -= 1;
			if(pos) seqs.push_back(n - pos);
			assert(pos + 3 <= n);
			rotate(a.begin() + pos, a.begin() + pos + 2, a.begin() + pos + 3);
			rotate(a.begin() + pos, a.begin() + pos + 2, a.begin() + pos + 3);
			seqs.push_back(-2);
			assert(a[i] == i + 1);
			if(pos) seqs.push_back(pos);
		}
	}
	assert(is_sorted(all(a)));
	vector<int> stk;
	for(auto &x : seqs){
		if(x > 0){
			if(sz(stk) && stk.back() > 0){
				x += stk.back();
				stk.pop_back();
			}
			x %= n;
			if(x) stk.push_back(x);
		}
		else{
			if(sz(stk) && stk.back() < 0){
				x += stk.back();
				stk.pop_back();
			}
			x = -x;
			x %= 3;
			if(x) stk.push_back(-x);
		}
	}
	assert(sz(stk) <= n * n);
	cout << sz(stk) << "\n";
	for(auto &x : stk){
		if(x < 0) cout << -x << "b ";
		else cout << x << "a ";
	}
}

