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

int n, k, a[20005];
int sfx[20005], ord[20005], nord[20005], rev[20005], p = 1;

bool cmp(int a, int b){
	if(ord[a] != ord[b]) return ord[a] < ord[b];
	return ord[a+p] < ord[b+p];
}

int lcp[20005];

int main(){
	cin >> n >> k;
	k--;
	for(int i=0; i<n; i++){
		cin >> a[i];
		sfx[i] = i;
		ord[i] = a[i];
	}
	ord[n] = -1;
	while(1){
		sort(sfx, sfx + n, cmp);
		if(p * 2 >= n) break;
		nord[sfx[0]] = 0;
		for(int i=1; i<n; i++){
			if(cmp(sfx[i-1], sfx[i])){
				nord[sfx[i]] = nord[sfx[i-1]] + 1;
			}
			else nord[sfx[i]] = nord[sfx[i-1]];
		}
		p *= 2;
		memcpy(ord, nord, sizeof(int) * n);
	}
	// sa(i) -> i번째 suffix array의 idx
	// rev(i) -> i번 index가 suffix array상에서 몇번째인지
	for(int i=0; i<n; i++) rev[sfx[i]] = i;
	int h = 0, ret = 0;
	for(int i=0; i<n; i++){
		if(rev[i]){
			int p = sfx[rev[i] - 1];
			while(a[p+h] == a[i+h]) h++;
		}
		lcp[rev[i]] = h;
		if(h) h--;
	}
	deque<int> dq, pos;
	for(int i=1; i<n; i++){
		if(!pos.empty() && pos[0] == i-k){
			pos.pop_front();
			dq.pop_front();
		}
		while(!dq.empty() && dq.back() >= lcp[i]){
			dq.pop_back();
			pos.pop_back();
		}
		dq.push_back(lcp[i]);
		pos.push_back(i);
		ret = max(ret, dq[0]);
	}
	cout << ret;
}