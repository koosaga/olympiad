#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
#define end sex

int trie[500005][2], cnt[500005], end[500005], p;
int n, q;

int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<n; i++){
		int s, pt = 0;
		scanf("%d",&s);
		while(s--){
			int x;
			scanf("%d",&x);
			if(!trie[pt][x]) trie[pt][x] = ++p;
			pt = trie[pt][x];
			cnt[pt]++;
		}
		cnt[pt]--;
		end[pt]++;
	}
	for(int i=0; i<q; i++){
		int s, pt = 0, ret = 0;
		scanf("%d",&s);
		while(s){
			s--;
			int x;
			scanf("%d",&x);
			pt = trie[pt][x];
			ret += end[pt];
			if(pt == 0) break;
		}
		while(s--) scanf("%*d");
		ret += cnt[pt];
		printf("%d\n", ret);
	}
}

