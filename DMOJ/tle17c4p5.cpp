// Ivan Carvalho
// Solution to https://dmoj.ca/problem/tle17c4p5
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200010;

ll seg[4*MAXN],MOD;
int maior_primo[MAXN],frequencia[MAXN],N;

ll binary_expo(ll x,int y){
	ll ans = 1,sq = x;
	for(int i = 0;(1 << i) <= y;i++){
		if(y & (1 << i)) ans = (ans*sq) % MOD;
		sq = (sq*sq) % MOD;
	}
	return ans;
}

void update(int pos,int left,int right,int x){
	if(left == right){
		seg[pos] = binary_expo(x,frequencia[x]);
		return;
	}
	int mid = (left+right)/2;
	if(x <= mid) update(2*pos,left,mid,x);
	else update(2*pos+1,mid+1,right,x);
	seg[pos] = (seg[2*pos]*seg[2*pos+1]) % MOD;
}

void add(int x){
	while(x > 1){
		int y = maior_primo[x];
		frequencia[y]++;
		update(1,1,N,y);
		x /= y;
	}
}

void remove(int x){
	while(x > 1){
		int y = maior_primo[x];
		frequencia[y]--;
		update(1,1,N,y);
		x /= y;
	}
}

int main(){

	scanf("%d %lld",&N,&MOD);

	maior_primo[1] = 1;
	for(int i = 2;i <= N;i++){
		if(maior_primo[i] != 0) continue;
		for(int j = i;j<=N;j+=i) maior_primo[j] = i;
	}

	for(int i = 1;i<=4*N;i++) seg[i] = 1;

	printf("1\n");
	for(int i = N,j = 1;i>=1;i--,j++){
		add(i);
		remove(j);
		printf("%lld\n",seg[1]);
	}

	return 0;

}