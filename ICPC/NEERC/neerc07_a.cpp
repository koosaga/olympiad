#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 5005;

struct point{
    int x, y, idx, col;
};

int ccw(point a, point b, point c){
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int n, mat[105];

void solve(vector<point> v){
    if(v.empty()) return;
    swap(v[0], *min_element(v.begin(), v.end(), [&](const point &a, const point &b){
        return pi(a.x, a.y) < pi(b.x, b.y);
    }));
    sort(v.begin() + 1, v.end(), [&](const point &a, const point &b){
        return ccw(v[0], a, b) > 0;
    });
    int cnt = v[0].col;
    for(int i=1; i<v.size(); i++){
        cnt += v[i].col;
        if(cnt == 0){
            vector<point> l, r;
            for(int j=1; j<i; j++) l.push_back(v[j]);
            for(int j=i+1; j<v.size(); j++) r.push_back(v[j]);
            if(v[0].col == -1) mat[v[0].idx] = v[i].idx + 1;
            else mat[v[i].idx] = v[0].idx + 1;
            solve(l);
            solve(r);
            return;
        }
    }
}

int main(){
    cin >> n;
    vector<point> a(2*n);
    for(int i=0; i<2*n; i++){
        cin >> a[i].x >> a[i].y;
        a[i].idx = i % n;
        a[i].col = (i >= n ? 1 : -1);
    }
    solve(a);
    for(int i=0; i<n; i++) printf("%d\n", mat[i]);
}
