#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
typedef long long lint;

int p, v, t;
int s[MAXN], e[MAXN];
char buf[55];

bool check(int L, int R){
	if(L > R) return false;
	printf("check %d %d\n", L, R);
	fflush(stdout);
	scanf("%s", buf);
	t++;
	return *buf == 'Y';
}

void answer(int x){
	printf("answer %d\n", x);
	fflush(stdout);
	exit(0);
}

lint trial(int x){
	lint ans = 0;
	for(int i=0; i<=v; i++){
		ans += max(min(x - i * t, e[i]) - s[i] + 1, 0);
	}
	return ans;
}

int main(){
	scanf("%d %d",&p,&v);
	for(int i=0; i<=v; i++) s[i] = 0, e[i] = p;
	while(true){
		int si = 0, ei = 1e9;
		lint sum = 0;
		for(int i=0; i<=v; i++) sum += max(e[i] - s[i] + 1, 0);
		if(sum * 2 + t < 98) break;
		while(si != ei){
			int m = (si+ei)/2;
			if(trial(m) <= sum / 2) si = m + 1;
			else ei = m;
		}
		int point = si;
		bool p = check(0, point);
		if(p == false){
			for(int i=0; i<=v; i++){
				s[i] = max(s[i], point + 1 - i * (t - 1));
			}
		}
		else{
			for(int i=0; i<=v; i++){
				e[i] = min(e[i], point - i * (t - 1));
			}
		}
	}
	for(int i=0; i<=v; i++){
		for(int j=s[i]; j<=e[i]; j++){
			if(check(i * t + j, i * t + j)){
				if(check(i * t + j, i * t + j)){
					answer(i * t + j);
				}
			}
		}
	}
	assert(0);
}
