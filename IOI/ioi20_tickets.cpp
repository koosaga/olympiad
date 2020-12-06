#include "tickets.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 1505;
 
struct node{
	int x, y, v;
	bool operator<(const node &n)const{
		if(v != n.v) return v < n.v;
		return y > n.y;
	}
};
 
void BACKTRACK(vector<vector<int>> B, int k){
	deque<int> dq[MAXN];
	int bcnt[MAXN] = {};
	for(int i=0; i<sz(B); i++){
		for(auto &j : B[i]){
			if(j > 0) bcnt[i]++;
		}
		for(int j=0; j<sz(B[i]); j++){
			if(B[i][j] == -1) dq[i].push_back(j);
		}
		for(int j=0; j<sz(B[i]); j++){
			if(B[i][j] == +1) dq[i].push_back(j);
		}
		for(int j=0; j<sz(B[i]); j++){
			if(B[i][j] == 0) B[i][j] = -1;
			else B[i][j] = 0;
		}
	}
	for(int i = 0; i < k; i++){
		vector<int> idx(sz(B));
		iota(all(idx), 0);
		sort(all(idx), [&](const int &a, const int &b){
			return bcnt[a] < bcnt[b];
		});
		for(int j=0; j<sz(B); j++){
			int x = idx[j];
			int y = (j < sz(B) / 2 ? dq[x].front() : dq[x].back());
			B[x][y] = i;
			if(j < sz(B) / 2) dq[x].pop_front();
			else{
				dq[x].pop_back();
				bcnt[x]--;
			}
		}
	}
	allocate_tickets(B);
}
 
long long find_maximum(int k, std::vector<std::vector<int>> x) {
	int n = sz(x);
	int m = sz(x[0]);
	vector<vector<int>> B(n);
	vector<node> v;
	for(auto &i : B) i.resize(m);
	lint sum = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<k; j++){
			sum -= x[i][j];
			B[i][j] = -1;
			v.push_back({i, j, x[i][m-1-j]+x[i][k-1-j]});
		}
	}
	sort(all(v));
	reverse(all(v));
	for(int i=0; i<sz(v)/2; i++){
		sum += v[i].v;
		B[v[i].x][k - 1 - v[i].y] = 0;
		B[v[i].x][m - 1 - v[i].y] = +1;
	}
	BACKTRACK(B, k);
	return sum;
}
