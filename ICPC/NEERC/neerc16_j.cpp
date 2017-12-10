#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 10005;

int n, h, q;
vector<int> v[MAXN];

bool in(int s, lint up, lint dn, int e){
    if(s >= e) return 0;
    if(dn == 0) return 1;
    return s * dn < up && up < e * dn;
}

bool query(int x, int y){
    auto l = lower_bound(v[x].begin(), v[x].end(), y);
    v[x].insert(l, y);
    lint totx = 0, toty = 0, csum = 0;
    for(int i=h; i; i--){
        int sx = 0, sy = 0, ex = n, ey = n;
        for(auto &j : v[i]){
            if(i % 2 && sx + 1 == j) sx++;
            else if(i % 2 == 0 && sy + 1 == j) sy++;
            else break;
        }
        for(int ii = (int)v[i].size() - 1; ii>=0; ii--){
            int j = v[i][ii];
            if(i % 2 && ex == j) ex--;
            else if(i % 2 == 0 && ey == j) ey--;
            else break;
        }
        if(!in(2 * sx, totx, csum, 2 * ex) || !in(2 * sy, toty, csum, 2 * ey)){
            return 1;
        }
        totx += n * n, toty += n * n;
        csum += n;
        for(auto &j : v[i]){
            if(i % 2) totx -= 2 * j - 1, toty -= n;
            else toty -= 2 * j - 1, totx -= n;
            csum--;
        }
    }
    return 0;
}

int main(){
    freopen("jenga.in", "r", stdin);
    freopen("jenga.out", "w", stdout);
    scanf("%d %*d %d %d",&n,&h,&q);
    for(int i=0; i<q; i++){
        int x, y;
        scanf("%d %d",&x,&y);
        if(query(x, y)){
            printf("yes\n%d",i+1);
            return 0;
        }
    }
    puts("no");
}
