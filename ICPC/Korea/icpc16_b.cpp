#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int cnt[10005], n;

int main(){
	cin >> n;
	int sum = 0;
	for(int i=0; i<n; i++){
		int x;
		scanf("%d",&x);
		cnt[x]++;
		sum += x;
	}
	if(sum != n * (n-1) / 2){
		puts("-1");
		return 0;
	}
	int t = n;
	for(int i=n-1; i; i--){
		while(cnt[i]){
			int tmp[10005] = {};
			cnt[i]--;
			int d = t-1-i;
			for(int j=i; j && d; j--){
				int w = min(d, cnt[j]);
				cnt[j] -= w;
				tmp[j-1] += w;
				d -= w;
			}
			if(d){
				puts("-1");
				return 0;
			}
			for(int j=0; j<=i; j++) cnt[j] += tmp[j];
			t--;
		}
	}
	puts("1");
}

