#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005;
using pi = pair<int, int>;
using lint = long long;

int n, a[MAXN][MAXN];
int cnt[MAXN * MAXN];

void my_ass(bool p){
	if(!p){
		puts("0");
		exit(0);
	}
}

int main(){
	scanf("%d",&n);
	for(int i = 0; i < (1<<n); i++){
		for(int j = 0; j < (1<<n); j++){
			scanf("%d",&a[i][j]);
			cnt[a[i][j]]++;
		}
	}
	my_ass(cnt[0] == 1);
	for(int i = 1; i <= (1 << 2*n) / 3; i++){
		my_ass(cnt[i] == 3);
	}
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0; i < (1<<n); i++){
		for(int j = 1; j < (1<<n); j++){
			if(a[i][j] == a[i][j-1]) cnt[a[i][j]]++;
		}
	}
	for(int i = 1; i <= (1 << 2*n) / 3; i++){
		my_ass(cnt[i] == 1);
	}
	memset(cnt, 0, sizeof(cnt));
	for(int i = 1; i < (1<<n); i++){
		for(int j = 0; j < (1<<n); j++){
			if(a[i][j] == a[i-1][j]) cnt[a[i][j]]++;
		}
	}
	for(int i = 1; i <= (1 << 2*n) / 3; i++){
		my_ass(cnt[i] == 1);
	}
	puts("1");
}
