#include "xylophone.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
static int A[5000];
int ans[MAXN];
int q1[MAXN], q2[MAXN];

void solve(int N) {
	for(int i=1; i+1<=N; i++) q1[i] = query(i, i + 1);
	for(int i=1; i+2<=N; i++) q2[i] = query(i, i + 2);
	ans[1] = 0;
	ans[2] = q1[1];
	for(int i=3; i<=N; i++){
		if(q1[i-2] + q1[i-1] == q2[i-2]){
			if(ans[i-2] < ans[i-1]) ans[i] = ans[i-1] + q1[i-1];
			else ans[i] = ans[i-1] - q1[i-1];
		}
		else{
			if(ans[i-2] < ans[i-1]) ans[i] = ans[i-1] - q1[i-1];
			else ans[i] = ans[i-1] + q1[i-1];
		}
	}
	int minv = *min_element(ans + 1, ans + N + 1);
	for(int i=1; i<=N; i++) ans[i] += 1 - minv;
	int pos1 = find(ans + 1, ans + N + 1, 1) - ans;
	int posn = find(ans + 1, ans + N + 1, N) - ans;
	if(pos1 > posn){
		for(int i=1; i<=N; i++) ans[i] = N + 1 - ans[i];
	}
	for(int i=1; i<=N; i++){
		answer(i, ans[i]);
	}
}
