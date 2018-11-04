#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;

int n;
int dx[MAXN];
int edp[MAXN], stp[MAXN];
int st[MAXN], ed[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&st[i],&ed[i]);
		edp[ed[i]]++;
		stp[st[i]]++;
		dx[st[i]]++;
		dx[ed[i]]--;
	}
	for(int i=1; i<MAXN; i++){
		dx[i] += dx[i-1];
		edp[i] += edp[i-1];
	}
	for(int i=MAXN-2; i>=0; i--) stp[i] += stp[i+1];
	int st1 = 0;
	for(int i=0; i<n; i++){
		int deg = n;
		deg -= edp[st[i]] + stp[ed[i]];
		st1 = max(st1, deg);
	}
	int st2 = *max_element(dx, dx + MAXN);
	cout << st1 << " " << st2 << endl;
}