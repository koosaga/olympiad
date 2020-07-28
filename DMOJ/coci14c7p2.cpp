// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci14c7p2
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e5 + 10;

int N,K,whereIs[MAXN],whereAmI;
ll pref[MAXN],misPlacements;

int getDistance(int cur, int nxt){
	if(nxt >= cur) return nxt - cur;
	return N - abs(nxt - cur);
}

int main(){

	cin >> N >> K;

	for(int i = 1;i<=N;i++){
		int x;
		cin >> x;
		whereIs[x] = i;
	}

	whereAmI = 1;

	for(int door = 1;door<=N && K > 0;door++,K--){
		int nxt = whereIs[door];
		misPlacements += getDistance(whereAmI,nxt);
		whereAmI = nxt;
	}

	if(K == 0){
		cout << misPlacements << endl;
		return 0;
	}

	for(int door = 1;door<=N;door++){
		int nxt = whereIs[door];
		pref[door] = pref[door-1] + getDistance(whereAmI,nxt);
		whereAmI = nxt;
	}

	misPlacements += 1LL*(K/N)*pref[N];

	misPlacements += pref[K%N];
	cout << misPlacements << endl;

	return 0;

}