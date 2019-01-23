#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
using real_t = double;
const int mod = 1e9 + 7;
const int MAXN = 12;
const lint inf = 2e15;

int n, m, k, s;
int a[MAXN][MAXN];
int b[MAXN][MAXN];

void Yeah(){
    puts("Yes");
    exit(0);
}

void Do2(int n, int m, int p){// p \in [1, n]
    int slack[MAXN] = {};
    for(int i=1; i<=m; i++){
        int sum = 0;
        for(int j=1; j<p; j++) sum = max(0, sum) + a[j][i];
        slack[i] += sum;
        sum = 0;
        for(int j=n; j>p; j--) sum = max(0, sum) + a[j][i];
        slack[i] += sum;
    }
    for(int i=1; i<=m; i++){
        if(slack[i] - a[p][i] <= s){
            int sum = 0;
            for(int j=1; j<=m; j++){
                if(j == i) sum = max(0, sum) - a[p][j];
                else sum = max(0, sum) + a[p][j];
                if(sum > s) break;
            }
            if(sum <= s) Yeah();
        }
    }
}

bool good(){
    for(int i=1; i<=n; i++){
        int sum = 0;
        for(int j=1; j<=m; j++){
            sum = max(0, sum) + a[i][j];
            if(sum > s) return 0;
        }
    }
    for(int j=1; j<=m; j++){
        int sum = 0;
        for(int i=1; i<=n; i++){
            sum = max(0, sum) + a[i][j];
            if(sum > s) return 0;
        }
    }
    return 1;
}

void Do(){
    // flip at most 1. can all <= S?
    int rowV = -1;
    int colV = -1;
    for(int i=1; i<=n; i++){
        int sum = 0;
        for(int j=1; j<=m; j++){
            sum = max(0, sum) + a[i][j];
            if(sum > s){
                if(~rowV) return;
                rowV = i;
                break;
            }
        }
    }
    for(int j=1; j<=m; j++){
        int sum = 0;
        for(int i=1; i<=n; i++){
            sum = max(0, sum) + a[i][j];
            if(sum > s){
                if(~colV) return;
                colV = j;
                break;
            }
        }
    }
    if(rowV == -1 && colV == -1) Yeah();
    if(rowV != -1 && colV != -1){
        a[rowV][colV] *= -1;
        if(good()) Yeah();
        a[rowV][colV] *= -1;
    }
    if(rowV == -1){
        swap(rowV, colV);
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                b[j][i] = a[i][j];
            }
        }
        Do2(m, n, rowV);
    }
    else{
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                b[i][j] = a[i][j];
            }
        }
        Do2(n, m, rowV);
    }
}

vector<pi> v;

void bktk(int x, int p){
    if(p == 0){
        Do();
        return;
    }
    if(x == n * m) return;
    bktk(x + 1, p);
    a[v[x].first][v[x].second] *= -1;
    bktk(x + 1, p - 1);
    a[v[x].first][v[x].second] *= -1;
}

int main(){
    scanf("%d %d %d %d",&n,&m,&k,&s);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            scanf("%d",&a[i][j]);
            v.emplace_back(i, j);
        }
    }
    bktk(0, k - 1);
    if(k >= 3){
        for(auto &i : v){
            a[i.first][i.second] *= -1;
            Do();
            a[i.first][i.second] *= -1;
        }
    }
    puts("No");
}
