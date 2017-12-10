#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 2222;

int isprime(int x){
    for(int i=2; i*i<=x; i++){
        if(x%i ==0) return 0;
    }
    return 1;
}

int f(int x){
    int ret = 0;
    while(x){
        ret++;
        x /= 10;
    }
    return ret;
}


int a[400];
lint dp[MAXN][400];
lint sum[MAXN][400];

char query(vector<int> v, int x){
    if(x == 1) return '[';
    int ret = 0;
    for(int i=0; i<v.size(); i++){
        ret += f(v[i]) + 2;
    }
    assert(x <= ret + 2);
    assert(x > 0);
    if(x == ret + 2) return ' ';
    if(x == ret + 1) return ',';
    if(x == ret) return ']';
    x--;
    for(int i=0; i<v.size(); i++){
        if(x <= f(v[i]) + 2){
            if(x == f(v[i]) + 1) return ',';
            if(x == f(v[i]) + 2) return ' ';
            x = f(v[i]) - x;
            while(x) v[i] /= 10, x--;
            return v[i] % 10 + '0';
        }
        else x -= f(v[i]) + 2;
    }
    assert(0);
}

int n;
char query(lint x){
    for(int i=1; i<MAXN; i++){
        if(x <= sum[i][n]){
            int p = i;
            vector<int> v;
            int cursum = 0;
            for(int j=n; j && p; j--){
                if(p < a[j]) continue;
                if(x <= dp[p - a[j]][j-1] * (f(a[j]) + 2 + cursum) + sum[p - a[j]][j-1]){
                    cursum += f(a[j]) + 2;
                    p -= a[j];
                    v.push_back(a[j]);
                }
                else{
                    x -= dp[p - a[j]][j-1] * (f(a[j]) + 2 + cursum) + sum[p - a[j]][j-1];
                }
            }
            if(p) v.push_back(p);
            return query(v, x);
        }
        else x -= sum[i][n];
    }
}

int main(){
    freopen("list.in", "r", stdin);
    freopen("list.out", "w", stdout);
    int p = 2;
    n = 390;
    for(int i=0; i<n; i++){
        while(!isprime(p)) p++;
        a[i+1] = p;
        p++;
    }
    reverse(a+1, a+n+1);
    for(int i=0; i<=n; i++) dp[0][i] = 1, sum[0][i] = 2;
    for(int i=1; i<MAXN; i++){
        for(int j=1; j<=n; j++){
            dp[i][j] = dp[i][j-1] + (i >= a[j] ? dp[i - a[j]][j-1] : 0);
            sum[i][j] = sum[i][j-1];
            if(i >= a[j]){
                sum[i][j] += sum[i - a[j]][j-1] + dp[i - a[j]][j-1] * (f(a[j]) + 2);
            }
        }
    }
    lint l, r;
    cin >> l >> r;
    for(lint i = l; i<=r; i++){
    //  query(i);
        putchar(query(i));
    }
}
