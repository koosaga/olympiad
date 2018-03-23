#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
int mpa[MAXN], mpe[MAXN], v[MAXN], dep[MAXN];

void solve(int n){
    memset(mpa, 0, sizeof(mpa));
    memset(mpe, 0, sizeof(mpe));
    memset(dep, 0, sizeof(dep));
    memset(v, 0, sizeof(v));
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int f = q.front();
        q.pop();
        if(f == 0){
            stack<int> s;
            printf("1");
            while (f != 1) {
                s.push(mpe[f]);
                f = mpa[f];
            }
            while (!s.empty()) {
                putchar(s.top() + 48);
                s.pop();
            }
            puts("");
            return;
        }
        else{
            int p = 10*f%n;
            if(!v[p]){
                v[p] = 1;
                mpa[p] = f;
                mpe[p] = 0;
                dep[p] = dep[f] + 1;
                q.push(p);
            }
            p++;
            p %= n;
            if(!v[p]){
                v[p] = 1;
                mpa[p] = f;
                mpe[p] = 1;
                dep[p] = dep[f] + 1;
                q.push(p);
            }
        }
    }
    puts("BRAK");
}

int main(){
int tc;
    cin >> tc;
    while(tc--){
        int n;
        scanf("%d",&n);
        if(n == 1) puts("1");
        else solve(n);
    }
}

