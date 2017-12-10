#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int MAXN = 50005;
const int inf = 1e9;

int w, n, a[MAXN];
int dp[MAXN];
lint p[MAXN], q[MAXN];

bool trial(int x){
    for(int i=1; i<=n; i++){
        dp[i] = 0;
        p[i] = (a[i] + 1) + p[i-1];
        q[i] = (a[i] + x) + q[i-1];
    }
    dp[0] = 1;
    int ptr = 0;
    for(int i=1; i<=n; i++){
        while(p[i] - p[ptr] > w+1) ptr++;
        while(ptr < i-1 && dp[ptr] == 0) ptr++;
        if(ptr < i-1 && dp[ptr] && (q[i] - q[ptr] >= w + x)) dp[i] = 1;
    }
    if(dp[n]) return true;
    for(int i=0; i<n; i++){
        if(p[n] - p[i] <= w + 1 && dp[i]) return true;
    }
    return false;
}

int main(){
    while(true){
        cin >> w >> n;
        if(!n) break;
        for(int i=1; i<=n; i++) scanf("%d",&a[i]);
        int s = 1, e = 50000;
        while(s != e){
            int m = (s+e)/2;
            if(trial(m)) e = m;
            else s = m+1;
        }
        cout << s << endl;
    }
}
