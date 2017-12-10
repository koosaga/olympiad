#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 100005;
const int offset = 50000;

int g[MAXN];
char buf[MAXN];

pi solve(char *s, int l){
    for(int i=0; i<l-1; i++){
        if(s[i] == '&' && s[i+1] == '&'){
            pi iv = solve(s, i);
            pi jv = solve(s + i + 2, l - i - 2);
            return pi(
                    max(iv.first, jv.first),
                    min(iv.second, jv.second));
        }
    }
    int ans = 0;
    for(int i=0; i<l; i++){
        if(isdigit(s[i])){
            ans = ans * 10 + s[i] - '0';
        }
    }
    for(int i=0; i<l; i++){
        if(s[i] == '-') ans *= -1;
    }
    for(int i=0; i<l; i++){
        if(s[i] == '<'){
            return pi(-32768, ans);
        }
        if(s[i] == '>'){
            return pi(ans, 32767);
        }
    }
    assert(0);
}

void print(int s, int e){
    if(s == -32768){
        printf("x <= %d", e);
    }
    else if(e == 32767){
        printf("x >= %d", s);
    }
    else{
        printf("x >= %d && x <= %d", s, e);
    }
}

int main(){
    freopen("hard.in", "r", stdin);
    freopen("hard.out", "w", stdout);
    while(fgets(buf, 500, stdin) != NULL){
        auto k = solve(buf, strlen(buf));
        if(k.first > k.second){
            continue;
        }
        g[k.first + offset]++;
        g[k.second + offset + 1]--;
    }
    for(int i=1; i<MAXN; i++){
        g[i] += g[i-1];
    }
    vector<pi> v;
    for(int i=-32768 + offset; i<=32768 + offset; i++){
        if(!g[i]) continue;
        int e = i;
        while(g[e]) e++;
        v.push_back(pi(i, e-1));
        i = e-1;
    }
    if(v.empty()){
        puts("false");
        return 0;
    }
    if(v[0] == pi(-32768 + offset, offset + 32767)){
        puts("true");
        return 0;
    }
    for(int i=0; i<v.size(); i++){
        v[i].first -= offset;
        v[i].second -= offset;
        print(v[i].first, v[i].second);
        if(i != v.size() - 1) puts(" ||");
    }
}
