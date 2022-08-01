#include "mushrooms.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
using word = bitset<450>;
const int MAXL = 8;
const int THR = 250;

int f[MAXL], sz[MAXL];
vector<word> queries[MAXL];
pi dp[THR], ans;

void gen(){
	f[0] = 1;
	for(int i = 1; i < MAXL; i++){
		f[i] = f[i - 1] * 2 + (1 << (i - 1)) - 1;
	}
	queries[0].push_back(1);
	for(int i = 1; i < MAXL; i++){
		queries[i].push_back(0);
		for(int j = f[i - 1]; j < 2 * f[i - 1]; j++) queries[i][0][j] = 1;
		auto S = queries[i][0];
		for(int j = 0; j < sz(queries[i - 1]) - 1; j++){
			queries[i].push_back(queries[i - 1][j] | (queries[i - 1][j] << f[i - 1]));
			queries[i].push_back(queries[i - 1][j] | (S ^ (queries[i - 1][j] << f[i - 1])) | (word(1) << (2 * f[i - 1] + j)));
		}
		queries[i].push_back(0);
		for(int j = 0; j < f[i]; j++) queries[i][sz(queries[i]) - 1][j] = 1;
	}
	dp[0] = pi(1, 0);
	dp[1] = pi(2, 0);
	dp[2] = pi(3, 0);
	for(int i = 0; i < MAXL; i++){
		vector<int> vect;
		for(int j = 0; j < sz(queries[i]); j++){
			vect.push_back(queries[i][j].count());
		}
		vect[sz(vect) - 1] -= vect[sz(vect) - 2];
		sort(all(vect));
		for(int j = 0; j < sz(vect); j++){
			sz[i] = max(sz[i], 2 * vect[j] + 1 - j);
		}
	}
	ans = pi(1e9, 1e9);
	for(int i = 3; i < THR; i++){
		for(int j = 0; j < MAXL; j++){
			if(i >= (1 << j) + 2 && dp[i - (1 << j)].first >= sz[j]){
				dp[i] = max(dp[i], pi(dp[i - (1 << j)].first + f[j] + (1 << j), j));
			}
		}
		int cur = dp[i].first;
		for(int j = i + 1; ; j++){
			cur += (dp[i].first + (j - i)) / 2;
			if(cur >= 20000){
				ans = min(ans, pi(j, i));
				break;
			}
		}
	}
}

void reconstruct(int i, vector<int> &ans, vector<int> v){
	if(i == 0){
		ans[0] = v[0];
		return;
	}
	vector<int> l, r, b;
	for(int j = 0; j < (1 << (i - 1)) - 1; j++){
		l.push_back((v[2 * j + 1] + v[2 * j + 2] - v[0]) / 2);
		r.push_back((v[2 * j + 1] - v[2 * j + 2] + v[0] + 1) / 2);
		b.push_back(v[2 * j + 2] - v[0] - l.back() + r.back());
		assert(b.back() >= 0 && b.back() <= 1);
	}
	r.push_back(v[0]);
	l.push_back(v.back() - v[0] - accumulate(all(b), 0));
	vector<int> pl(f[i - 1]), pr(f[i - 1]);
	reconstruct(i - 1, pl, l);
	reconstruct(i - 1, pr, r);
	for(int i = 0; i < sz(pl); i++) ans[i] = pl[i];
	for(int i = 0; i < sz(pr); i++) ans[i + sz(pl)] = pr[i];
	for(int i = 0; i < sz(b); i++) ans[i + sz(pl) + sz(pr)] = b[i];
}

int count_mushrooms(int n) {
	gen();
	if(n <= 300){
		int cnt = 1;
		for(int i=1; i+1<n; i+=2){
			cnt += 2 - use_machine({i + 1, 0, i});
		}
		if(n % 2 == 0) cnt += 1 - use_machine({0, n - 1});
		return cnt;
	}
	// flex
	for(int i = 203; i < 226; i++) use_machine({69, 4, 20, 15, 57});

	// phase 1
	vector<int> A = {0}, B;
	(use_machine({0, 1}) ? B : A).push_back(1);
	(use_machine({0, 2}) ? B : A).push_back(2);
	vector<int> seq;
	for(int k = ans.second; k != 2; k -= (1 << dp[k].second)){
		seq.push_back(dp[k].second);
	}
	reverse(all(seq));
	int pos = 3;
	for(auto &i : seq){
		if(pos >= n) break;
//		cout << i << endl;
//		cout << pos << endl;
		if(i > 0) queries[i][sz(queries[i]) - 1] ^= queries[i][sz(queries[i]) - 2];
		vector<int> idx(sz(queries[i]));
		iota(all(idx), 0);
		sort(all(idx), [&](const int &a, const int &b){
			return queries[i][a].count() < queries[i][b].count();
		});
		vector<int> retValue(sz(idx));
		for(int j = 0; j < sz(idx); j++){
			vector<int> v, qr;
			for(int k = 0; k < f[i]; k++){
				if(queries[i][idx[j]][k]){
					v.push_back(pos + (1 << i) + k);
	//				cout << v.back() << " ";
					if(v.back() >= n) v.pop_back();
				}
			}
	//		cout <<"?" ;
			if(sz(A) > sz(v)){
				for(int k = 0; k < sz(v); k++){
					qr.push_back(A[k]);
					qr.push_back(v[k]);
				}
				qr.push_back(A[sz(v)]);
				if(pos + j < n) qr.push_back(pos + j);
				int um = (sz(qr) < 2 ? 0 : use_machine(qr));
				retValue[idx[j]] = um / 2;
				if(pos + j < n){
					if(um % 2 == 0) A.push_back(pos + j);
					else B.push_back(pos + j);
				}
			}
			else if(sz(B) > sz(v)){
				for(int k = 0; k < sz(v); k++){
					qr.push_back(B[k]);
					qr.push_back(v[k]);
				}
				qr.push_back(B[sz(v)]);
				if(pos + j < n) qr.push_back(pos + j);
				int um = (sz(qr) < 2 ? 0 : use_machine(qr));
				retValue[idx[j]] = sz(v) - um / 2; 
				if(pos + j < n){
					if(um % 2 == 1) A.push_back(pos + j);
					else B.push_back(pos + j);
				}
			}
			else assert(0);
		}
		pos += (1 << i);
		if(i > 0){
			queries[i][sz(queries[i]) - 1] ^= queries[i][sz(queries[i]) - 2];
			retValue[sz(retValue) - 1] += retValue[sz(retValue) - 2];
		}
		vector<int> ans(f[i]);
		reconstruct(i, ans, retValue);
		for(int k = 0; k < sz(ans) && pos < n; k++){
			if(ans[k]) B.push_back(pos++);
			else A.push_back(pos++);
		}
	}
	//for(auto &x : A) cout << "A" << x << endl;
	//for(auto &x : B) cout << "B" << x << endl;
	// phase 2
	int surplus = 0;
	while(pos < n){
		vector<int> foo;
		for(int i = 0; i < max(sz(A), sz(B)); i++){
			foo.push_back(pos);
			pos++;
			if(pos == n) break;
		}
		if(sz(A) >= sz(B)){
			vector<int> ans;
			for(int i = 0; i < sz(foo); i++){
				ans.push_back(foo[i]);
				ans.push_back(A[i]);
			}
			int q = use_machine(ans);
			surplus += sz(foo) - 1 - (q / 2);
			if(q & 1) B.push_back(foo[0]);
			else A.push_back(foo[0]);
		}
		else{
			vector<int> ans;
			for(int i = 0; i < sz(foo); i++){
				ans.push_back(foo[i]);
				ans.push_back(B[i]);
			}
			int q = use_machine(ans);
			surplus += (q / 2);
			if(q & 1) A.push_back(foo[0]);
			else B.push_back(foo[0]);
		}
	}
	return sz(A) + surplus;
}

