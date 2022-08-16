#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 1550000;

int n, a[69];
lint m;

bool good(lint x){
    if(x == 1) return 1;
    for(int i=0; i<n; i++){
        while(x % a[i] == 0) x /= a[i];
        if(x == 1) return 1;
    }
    return 0;
}

int dp[MAXN];
lint cur_found = 1;

lint f(lint x, int y = 0, lint gseq = 1){
    if(gseq * x <= cur_found) return 1;
    if(x < MAXN) return dp[x];
    lint ret = 1;
    for(int i = y; i < n; i++){
        ret = max(ret, f(x / a[i], i, gseq * a[i]) * a[i]);
        cur_found = max(cur_found, gseq * ret);
    }
    return ret;
}

int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++) cin >> a[i];
    dp[1] = 1;
    for(int i=2; i<MAXN; i++){
        if(good(i)) dp[i] = i;
        else dp[i] = dp[i - 1];
    }
    cout << f(m) << endl;
}
