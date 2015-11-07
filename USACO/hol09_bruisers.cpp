#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<double,double> pd;
 
int n, r, sx, sy, svx, svy;
vector<double> add, erase;
 
inline double trial(int a, int b, int c, double x){
    return a * x * x + b * x + c;
}
 
int main(){
    scanf("%d %d %d %d %d %d",&n,&r,&sx,&sy,&svx,&svy);
    for (int i=0; i<n; i++) {
        int px, py, vx, vy;
        scanf("%d %d %d %d",&px,&py,&vx,&vy);
        int a = (vx - svx) * (vx - svx) + (vy - svy) * (vy - svy);
        int b = (vx - svx) * (px - sx) + (vy - svy) * (py - sy);
        b *= 2;
        int c = (px - sx) * (px - sx) + (py - sy) * (py - sy);
        double s = 0, e = 1e4;
        for (int j=0; j<50; j++) {
            double m1 = (2*s+e)/3;
            double m2 = (s+2*e)/3;
            if(trial(a,b,c,m1) < trial(a,b,c,m2)) e = m2;
            else s = m1;
        }
        if(trial(a,b,c,s) >= r * r) continue;
        else{
            double ns = 0, ne = e;
            for (int j=0; j<50; j++) {
                double m = (ns + ne)/2;
                if(trial(a,b,c,m) > r * r) ns = m;
                else ne = m;
            }
            add.push_back(ns);
            ns = e, ne = 1e4;
            for (int j=0; j<50; j++) {
                double m = (ns + ne)/2;
                if(trial(a,b,c,m) > r * r) ne = m;
                else ns = m;
            }
            erase.push_back(ne);
        }
    }
    sort(add.begin(),add.end());
    sort(erase.begin(),erase.end());
    int pa = 0, pe = 0, ret = 0, cnt = 0;
    while (pa < add.size() && pe < erase.size()) {
        if(add[pa] < erase[pe]){
            cnt++;
            pa++;
        }
        else{
            cnt--;
            pe++;
        }
        ret = max(ret,cnt);
    }
    printf("%d",ret);
}