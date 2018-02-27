#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = (1<<20) + 5;

int n, q;
int cnt1[MAXN];
int cnt2[MAXN];
int pcnt[MAXN];
char str[MAXN];

char buf[25];

int main(){
	scanf("%d %d",&n,&q);
	scanf("%s", str);
	for(int i=0; i<(1<<n); i++){
		if(i) pcnt[i] = pcnt[i-(i&-i)] + 1;
		cnt1[i ^ ((1<<n) - 1)] += str[i] - '0';
		cnt2[i] += str[i] - '0';
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<(1<<n); j++){
			if((j >> i) % 2 == 0){
				cnt1[j] += cnt1[j | (1<<i)];
				cnt2[j] += cnt2[j | (1<<i)];
			}
		}
	}
	for(int i=0; i<q; i++){
		scanf("%s", buf);
		reverse(buf, buf + n);
		int cnt[3] = {};
		for(int j=0; buf[j]; j++){
			if(buf[j] == '?') cnt[2]++;
			else cnt[buf[j] - '0']++;
		}
		int ans = 0;
		if(cnt[0] <= n/3){
			int msk = 0, tmsk = 0;
			for(int j=0; buf[j]; j++){
				if(buf[j] == '0') tmsk |= 1<<j;
				if(buf[j] == '1') msk |= 1<<j;
			}
			ans += cnt2[msk];
			for(int i=tmsk; i>0; i=(i-1)&tmsk){
				ans += cnt2[i | msk] * (pcnt[i] % 2 ? -1 : 1);
			}
		}
		else if(cnt[1] <= n/3){
			int msk = 0, tmsk = 0;
			for(int j=0; buf[j]; j++){
				if(buf[j] == '0') msk |= 1<<j;
				if(buf[j] == '1') tmsk |= 1<<j;
			}
			ans += cnt1[msk];
			for(int i=tmsk; i>0; i=(i-1)&tmsk){
				ans += cnt1[i | msk] * (pcnt[i] % 2 ? -1 : 1);
			}
		}
		else if(cnt[2] <= n/3){
			int msk = 0, tmsk = 0;
			for(int j=0; buf[j]; j++){
				if(buf[j] == '1') msk |= 1<<j;
				if(buf[j] == '?') tmsk |= 1<<j;
			}
			ans += str[msk] - '0';
			for(int i=tmsk; i>0; i=(i-1)&tmsk){
				ans += str[i | msk] - '0';
			}
		}
		printf("%d\n", ans);
	}
}
