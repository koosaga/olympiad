#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

vector<int> gph[40005];
int n, par[40005];
char str[40005], buf[4];

int lmx[40005], rmx[40005];
int lpmx[40005], rpmx[40005];
priority_queue<int> pql[40005], pqr[40005];

int main(){
	freopen("btree.in","r",stdin);
	freopen("btree.out","w",stdout);
	scanf("%d",&n);
	for(int i=2; i<=n; i++){
		scanf("%d",&par[i]);
		gph[par[i]].push_back(i);
	}
	for(int i=1; i<=n; i++){
		scanf("%s",buf);
		str[i] = *buf;
	}
	for(int i=n; i; i--){
		for(auto &j : gph[i]){
			lmx[i] = max(lmx[i], lmx[j]);
			rmx[i] = max(rmx[i], rmx[j]);
			pql[i].push(lmx[j]);
			pqr[i].push(rmx[j]);
		}
		if(str[i] == '(') lmx[i]++, rmx[i]--;
		else rmx[i]++, lmx[i]--;
	}
	for(int i=1; i<=n; i++){
		if(par[i]){
			int p = par[i];
			lpmx[i] = max(lpmx[i], lpmx[p]);
			rpmx[i] = max(rpmx[i], rpmx[p]);
			int ok1 = 0, ok2 = 0;
			if(!pql[p].empty() && pql[p].top() == lmx[i]){
				pql[p].pop();
				ok1 = 1;
			}
			if(!pqr[p].empty() && pqr[p].top() == rmx[i]){
				pqr[p].pop();
				ok2 = 1;
			}
			if(!pql[p].empty()) lpmx[i] = max(lpmx[i], pql[p].top());
			if(!pqr[p].empty()) rpmx[i] = max(rpmx[i], pqr[p].top());
			if(ok1) pql[p].push(lmx[i]);
			if(ok2) pqr[p].push(rmx[i]);
			if(str[p] == '(') lpmx[i]++, rpmx[i]--;
			else lpmx[i]--, rpmx[i]++;
		}
	}
	int ret = 0;
	for(int i=1; i<=n; i++){
		vector<int> l, r;
		l.push_back(0);
		r.push_back(0);
		for(auto &j : gph[i]){
			l.push_back(lmx[j]);
			r.push_back(rmx[j]);
		}
		if(par[i]){
			l.push_back(lpmx[i]);
			r.push_back(rpmx[i]);
		}
		int lg = (str[i] == '(');
		int rg = (str[i] == ')');
		int p = 0, q = 0;
		for(int i=0; i<l.size(); i++){
			ret = max(ret, min(l[i] + lg, q + rg));
			ret = max(ret, min(p + lg, r[i] + rg));
			p = max(p, l[i]);
			q = max(q, r[i]);
		}
	}
	cout << ret;
}