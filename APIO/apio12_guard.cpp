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
typedef set<int> ::iterator aauto;

int n, k, m;

struct s1{
	int a, b, c;
	bool operator<(const s1 &p)const{
		return pi(b, -a) < pi(p.b, -p.a);
	}
}a[100005];

int ok[100005], nok[100005];
int lst1[100005], lst2[100005];
vector<s1> seglist;

int dp1[100005], pos1[100005];
int dp2[100005], pos2[100005];

void process(){
	int cnt = 0;
	for(int i=0; i<seglist.size(); ){
		int e = i;
		int pos = lst1[seglist[i].b];
		while(e < seglist.size() && seglist[e].a <= pos) e++;
		cnt++;
		for(int j=i; j<e; j++){
			dp1[j] = cnt;
			pos1[j] = pos;
		}
		i = e;
	}
	cnt = 0;
	for(int i=(int)seglist.size()-1; i>=0; ){
		int e = i;
		int pos = lst2[seglist[i].a];
		while(e >= 0 && seglist[e].b >= pos) e--;
		cnt++;
		for(int j=e+1; j<=i; j++){
			dp2[j] = cnt;
			pos2[j] = pos;
		}
		i = e;
	}
}

bool cmp1(s1 a, s1 b){
	return a.a < b.a;
}

bool cmp2(s1 a, s1 b){
	return a.b < b.b;
}

int fok(int x){
	int p1 = lower_bound(seglist.begin(), seglist.end(), (s1){0, x, 0}, cmp2) - seglist.begin() - 1;
	int p2 = upper_bound(seglist.begin(), seglist.end(), (s1){x, 0, 0}, cmp1) - seglist.begin();
	int st = 0, ed = n+1, ret = 0;
	if(p1 >= 0){
		ret += dp1[p1];
		st = pos1[p1];
	}
	if(p2 != seglist.size()){
		ret += dp2[p2];
		ed = pos2[p2];
	}
	p1 = upper_bound(seglist.begin(), seglist.end(), (s1){st, 0, 0}, cmp1) - seglist.begin();
	p2 = lower_bound(seglist.begin(), seglist.end(), (s1){0, ed, 0}, cmp2) - seglist.begin() - 1;
	while(p1 <= p2){
		int p = lst1[seglist[p1].b];
		if(p == x) p = lst1[x-1];
		if(p < seglist[p1].a) return 1e9;
		ret++;
		p1 = upper_bound(seglist.begin(), seglist.end(), (s1){p, 0, 0}, cmp1) - seglist.begin();
	}
	return ret;
}


int main(){
	cin >> n >> k >> m;
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&a[i].a,&a[i].b,&a[i].c);
		if(a[i].c == 0){
			nok[a[i].a]++;
			nok[a[i].b+1]--;
		}
		else{
			ok[a[i].a]++;
			ok[a[i].b+1]--;
		}
	}
	lst2[n+1] = 1e9;
	for(int i=1; i<=n; i++){
		ok[i] += ok[i-1];
		nok[i] += nok[i-1];
	}
	for(int i=1; i<=n; i++){
		if(!nok[i]) lst1[i] = i;
		else lst1[i] = lst1[i-1];
		if(!nok[n+1-i]) lst2[n+1-i] = n+1-i;
		else lst2[n+1-i] = lst2[n+2-i];
	}
	int cnt = 0;
	for(int i=1; i<=n; i++){
		if(!nok[i]) cnt++;
	}
	if(cnt == k){
		for(int i=1; i<=n; i++){
			if(!nok[i]) printf("%d\n",i);
		}
		return 0;
	}
	sort(a, a+m);
	int cmax = 0;
	for(int i=0; i<m; i++){
		if(a[i].c == 0 || a[i].a <= cmax) continue;
		cmax = a[i].a;
		seglist.push_back(a[i]);
	}
	if(seglist.empty()){
		puts("-1");
		return 0;
	}
	process();
	vector<int> v;
	for(int i=1; i<=n; i++){
		if(!nok[i] && fok(i) > k) v.push_back(i);
	}
	if(v.empty()){
		puts("-1");
	}
	else{
		for(int i=0; i<v.size(); i++){
			printf("%d\n",v[i]);
		}
	}
}