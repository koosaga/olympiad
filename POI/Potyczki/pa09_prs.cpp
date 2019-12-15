#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;

int isqrt(int n){
	int x = 0;
	while((x+1)*(x+1)<=n) x++;
	return x;
}

int main(){
    int n;
    scanf("%d",&n);
    lint ret = isqrt(n);
    for (int i=1; i<=100000; i++) {
    	ret += n / i;
    	int st = 1 + n / (i + 1), ed = n / i;
    	st = max(st, 100001);
    	ret += 1ll * max(0, ed - st + 1) * i;
    }
    ret /= 2;
    printf("%lld",ret);
}
