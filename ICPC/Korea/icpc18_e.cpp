#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 300005;
using pi = pair<int, int>;
#define sz(v) int((v).size())

int n;
pi a[MAXN];

bool trial(int v){
	int ptr = 0;
	while(ptr < n && a[ptr].second <= v / 2){
		ptr++;
	}
	if(ptr == n) return 1;
	int st = 2e9, ed = 0;
	while(ptr < n && max(ed, a[ptr].second) - min(st, a[ptr].second) <= v){
		ed = max(ed, a[ptr].second);
		st = min(st, a[ptr].second);
		ptr++;
	}
	if(ptr == n) return 1;
	if(a[ptr].second < st) return 0;
	st = 2e9, ed = 0;
	while(ptr < n && max(ed, a[ptr].second) - min(st, a[ptr].second) <= v){
		ed = max(ed, a[ptr].second);
		st = min(st, a[ptr].second);
		ptr++;
	}
	return ptr == n;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	sort(a, a + n);
	int l = 0, r = 2e9;
	if(a[0].first == 0) l = 2 * a[0].second;
	while(l != r){
		int m = l + (r - l) / 2;
		if(trial(m)) r = m;
		else l = m + 1;
	}
	printf("%.1f\n", 0.5 * l);
}
