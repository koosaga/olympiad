#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 1000005;

int n, k;
lint a[MAXN];
lint que[MAXN];
int fr, re;

bool bfs(lint s, lint e){
	if(s == e) return true;
	fr = re = 0;
	unordered_set<lint> vis;
	que[re++] = s;
	vis.insert(s);
	int cnt = 0;
	int l = n * k / 10 + 10000;
	while(fr < re){
		lint x = que[fr++];
		if(cnt > l) return true;
		for(int i=0; i<k; i++){
			lint f = x ^ (1ll << i);
			if(f == e) return true;
			if(vis.find(f) == vis.end() && *lower_bound(a, a+n, f) != f){
				que[re++] = f;
				vis.insert(f);
				cnt++;
			}
		}
	}
	return false;
}

char buf[100];

int main(){
	lint s, e;
	scanf("%d %d\n",&k,&n);
	auto getnum = [&](lint &x){
		x = 0;
		scanf("%s\n", buf);
		for(int i=0; i<k; i++) x = (x << 1) + (buf[i] & 1);
	};
	auto getnum2 = [&](lint &x){
		x = 0;
		fgets(buf, 90, stdin);
		for(int i=0; i<k; i++) x = (x << 1) + (buf[i] & 1);
	};
	getnum(s); getnum(e);
	for(int i=0; i<n; i++){
		getnum2(a[i]);
	}
sort(a, a+n);
a[n] = (1ll << 60);
	puts(bfs(s, e) && bfs(e, s) ? "TAK" : "NIE");
}

