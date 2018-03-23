#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
typedef pair<int,int> pi;

int n, x[100005], y[100005];

int lowx, lowy, highx, highy;
int st, ed;
int arr[4000005];

struct sweepset{
    vector<pi> qins, qdel;
    multiset<int> ms;
    void init(){
        ms.clear();
        qins.clear();
        qdel.clear();
    }
    void addq(int s, int e, int x){
        if(s > e) return;
        qins.push_back(pi(s,x));
        qdel.push_back(pi(e,x));
    }
    void process1(){
        sort(qins.begin(), qins.end());
        sort(qdel.begin(), qdel.end());
        int p1 = 0, p2 = 0, cmax = 1e9;
        for(int i=st; i<=ed; i++){
            while(p1 < qins.size() && qins[p1].first == i){
                ms.insert(qins[p1++].second);
                if(ms.empty()) cmax = 1e9;
                else cmax = *ms.begin();
            }
            arr[i - st] = min(arr[i - st], - i + cmax);
            while(p2 < qdel.size() && qdel[p2].first == i){
                ms.erase(ms.find(qdel[p2++].second));
                if(ms.empty()) cmax = 1e9;
                else cmax = *ms.begin();
            }
        }
    }
    void process2(){
        sort(qins.begin(), qins.end());
        sort(qdel.begin(), qdel.end());
        int p1 = 0, p2 = 0, cmax = 1e9;
        for(int i=st; i<=ed; i++){
            while(p1 < qins.size() && qins[p1].first == i){
                ms.insert(qins[p1++].second);
                if(ms.empty()) cmax = 1e9;
                else cmax = *ms.begin();
            }
            arr[i - st] = min(arr[i - st], cmax);
            while(p2 < qdel.size() && qdel[p2].first == i){
                ms.erase(ms.find(qdel[p2++].second));
                if(ms.empty()) cmax = 1e9;
                else cmax = *ms.begin();
            }
        }
    }
    void process3(){
        sort(qins.begin(), qins.end());
        sort(qdel.begin(), qdel.end());
        int p1 = 0, p2 = 0, cmax = 1e9;
        for(int i=st; i<=ed; i++){
            while(p1 < qins.size() && qins[p1].first == i){
                ms.insert(qins[p1++].second);
                if(ms.empty()) cmax = 1e9;
                else cmax = *ms.begin();
            }
            arr[i - st] = min(arr[i - st], i + cmax);
            while(p2 < qdel.size() && qdel[p2].first == i){
                ms.erase(ms.find(qdel[p2++].second));
                if(ms.empty()) cmax = 1e9;
                else cmax = *ms.begin();
            }
        }
    }
}s1, s2, s3;

void solve(){
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        scanf("%d %d",&x[i],&y[i]);
    }
    lowx = *min_element(x,x+n);
    lowy = *min_element(y,y+n);
    highx = *max_element(x,x+n);
    highy = *max_element(y,y+n);
    if(highx - lowx < highy - lowy){
        swap(lowx,lowy);
        swap(highx,highy);
        for(int i=0; i<n; i++){
            swap(x[i],y[i]);
        }
    }
    int diam = highx - lowx;
     st = 2 * highy - diam;
     ed = 2 * lowy + diam;
    int mid = highx + lowx;
    for(int i=0; i<n; i++){
        x[i] *= 2, y[i] *= 2;
    }
    fill(arr, arr + ed - st + 1, diam);
    s1.init();
    s2.init();
    s3.init();
    for(int i=0; i<n; i++){
        int d = abs(x[i] - mid);
        s1.addq(st, min(y[i] - d, ed), y[i]);
        s2.addq(max(st, y[i] - d), min(ed, y[i] + d), d);
        s3.addq(max(st, y[i] + d), ed, -y[i]);
    }
    s1.process1();
    s2.process2();
    s3.process3();
    int p = *max_element(arr, arr + ed - st + 1);
    printf("%.1f\n", 0.5 * (diam - p));
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        solve();
    }
}