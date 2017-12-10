#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const lint mod = 1e18;

lint ipow(lint x, lint p){
    lint ret = 1, piv = x % mod;
    while(p){
        if(p&1) ret *= piv;
        piv *= piv;
        ret %= mod;
        piv %= mod;
        p >>= 1;
    }
    return ret % mod;
}

vector<int> v;
lint n, k;

lint f(int n, int k){
    if(n == 0){
        return v[n];
    }
    lint ret = 0;
    if(v[n-1] > 0){
        ret += ipow(k, n/2) * (v[n] + 1);
    }
    else{
        ret += ipow(k, n/2) * v[n];
        ret += f(n-2, k);
    }
    return ret;
}
int main(){
    cin >> n >> k;
    n++;
    while(n){
        v.push_back(n%k);
        n /= k;
    }
    if(v.size() % 2 == 0){
        cout << ipow(k, v.size() / 2);
    }
    else{
        cout << f(v.size()-1, k);
    }
}
