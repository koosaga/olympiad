#include <cstdio>
#include <cmath>
using namespace std;

int n, w, h;
int x[51], y[51];

int hypot(int p, int q){
    return p * p + q * q;
}

bool trial(int a, int b, int c, int d){
    int rad1 = hypot(x[b] - x[a], y[b] - y[a]);
    int rad2 = hypot(x[d] - x[c], y[d] - y[c]);
    if(rad1 > rad2) return 0;
    if(hypot(x[a],0) < rad1 || hypot(w - x[a],0) < rad1) return 0;
    if(hypot(0,y[a]) < rad1 || hypot(0,h - y[a]) < rad1) return 0;
    if(hypot(x[c],0) < rad2 || hypot(w - x[c],0) < rad2) return 0;
    if(hypot(0,y[c]) < rad2 || hypot(0,h - y[c]) < rad2) return 0;
    return sqrt(rad1) + sqrt(hypot(x[c] - x[a],y[c] - y[a])) <= sqrt(rad2) - 1e-9;
}

int main(){
    scanf("%d %d %d",&n,&w,&h);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&x[i],&y[i]);
    }
    int ret = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if(i == j) continue;
            for (int k=i+1; k<n; k++) {
                if(j == k) continue;
                for (int l=0; l<n; l++) {
                    if(i == l || j == l || k == l) continue;
                    if(trial(i,j,k,l)) ret++;
                    if(trial(k,l,i,j)) ret++;
                }
            }
        }
    }
    printf("%d",ret);
}