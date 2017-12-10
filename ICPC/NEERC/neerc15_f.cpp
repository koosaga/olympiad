#include<bits/stdc++.h>
using namespace std;
typedef pair<double, double> pi;

const int MAXN = 1005;
int w, n;
pi a[MAXN];
double dist[MAXN][MAXN];
bool vis1[MAXN], vis2[MAXN];
queue<int> que;
pi ans;

void bfs(double cur, bool *vis){
    while(!que.empty()){
        int x = que.front();
        que.pop();
        for(int i=0; i<n; i++){
            if(!vis[i] && dist[x][i] <= cur){
                que.push(i);
                vis[i] = 1;
            }
        }
    }
}

bool trial(double x){
    memset(vis1, 0, sizeof(vis1));
    memset(vis2, 0, sizeof(vis2));
    for(int i=0; i<n; i++) if(a[i].first <= x){
        vis1[i] = 1;
        que.push(i);
    }
    bfs(x, vis1);
    for(int i=0; i<n; i++) if(a[i].first >= w - x){
        vis2[i] = 1;
        que.push(i);
    }
    bfs(x, vis2);
    ans.first = 0.5 * w;
    ans.second = 0;
    for(int i=0; i<n; i++){
        if(vis1[i] && vis2[i]){
            return true;
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(vis1[i] && vis2[j] && dist[i][j] <= 2 * x){
                ans.first = 0.5 * (a[i].first + a[j].first);
                ans.second = 0.5 * (a[i].second + a[j].second);
                return true;
            }
        }
    }
    for(int i=0; i<n; i++){
        if(vis2[i] && a[i].first <= 2 * x){
            ans.first = a[i].first * 0.5;
            ans.second = a[i].second;
            return true;
        }
        if(vis1[i] && a[i].first >= w - 2 * x){
            ans.first = (a[i].first + w) * 0.5;
            ans.second = a[i].second;
            return true;
        }
    }
    return false;
}

int main(){
    cin >> w >> n;
    if(n == 0){
        printf("%.10f 0\n", w * 0.5);
        return 0;
    }
    for(int i=0; i<n; i++) cin >> a[i].first >> a[i].second;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            dist[i][j] = hypot(a[j].first - a[i].first, a[j].second - a[i].second);
        }
    }
    double s = 0, e = w;
    for(int i=0; i<70; i++){
        double m = (s+e)/2;
        if(trial(m)) e = m;
        else s = m;
    }
    trial(s + 1e-6);
    printf("%.10f %.10f\n", ans.first, ans.second);
}
