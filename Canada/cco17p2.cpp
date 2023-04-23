#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 14579;

unordered_map<lint, int> dp;

int f(int x, int y){
    if(x == 0 || y == 0) return 0;
    if(x < y) swap(x, y);
    int p = 2 * y;
    int l = (x - 2 * y) / p;
    lint h = ((1ll * x) << 28) + y;
    if(dp.find(h) != dp.end()) return dp[h];
    if(l > 0) return dp[h] = l + f(x - p * l, y);
    int ret = 1e9;
    if(y % 2 == 0) ret = min(ret, 1 + f(x - y/2, y));
    if(x >= 2 * y) ret = min(ret, 1 + f(x - 2*y, y));
    else if(x % 2 == 0) ret = min(ret,f(x, y-x/2) + 1);
    return dp[h] = ret;
}

int g(int x, int y){
    if(x == 0 || y == 0) return 0;
    if(x < y) swap(x, y);
    int p = (y % 2 ? (y * 2) : (y / 2));
    int l = (x - 2 * y) / p;
    lint h = ((1ll * x) << 28) + y;
    if(dp.find(h) != dp.end()) return dp[h];
    if(l > 0) return dp[h] = l + g(x - p * l, y);
    int ret = 0;
    if(y % 2 == 0) ret = max(ret, 1 + g(x - y/2, y));
    if(x >= 2 * y) ret = max(ret, 1 + g(x - 2*y, y));
    else if(x % 2 == 0) ret = max(ret,g(x, y - x/2) + 1);
    return dp[h] = ret;
}

int gcd(int x, int y){
    return y ? gcd(y, x%y) : x;
}

int main(){
    int x, y;
    cin >> x >> y;
    int p = gcd(x, y);
    while(p % 2 == 0) p /= 2;
    x /= p, y /= p;
    cout << f(x, y) << " ";
    dp.clear();
    cout << g(x, y);
}