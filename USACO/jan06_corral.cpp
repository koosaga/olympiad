#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> vx,vy;
int s[505][505];
int x[505], y[505], n;

int sum(int x1, int x2, int y1, int y2){
    return s[x2][y2] - s[x1-1][y2] - s[x2][y1-1] + s[x1-1][y1-1];
}

int trial(int p){
    int ret = 0;
    int e = 1;
    for (int i=1; i<vx.size(); i++) {
        while(e < vx.size() && vx[i] + p >= vx[e]) e++;
        int k = 1;
        for (int j=1; j<vy.size(); j++){
            while(k < vy.size() && vy[j] + p >= vy[k]) k++;
            ret = max(ret,sum(i,e-1,j,k-1));
        }
    }
    return ret;
}

int main(){
    int c;
    scanf("%d %d",&c,&n);
    for (int i=0; i<n; i++) {
        scanf("%d %d",&x[i],&y[i]);
        vx.push_back(x[i]);
        vy.push_back(y[i]);
    }
    vx.push_back(-1);
    vy.push_back(-1);
    sort(vx.begin(),vx.end());
    sort(vy.begin(),vy.end());
    vx.resize(unique(vx.begin(),vx.end()) - vx.begin());
    vy.resize(unique(vy.begin(),vy.end()) - vy.begin());
    for (int i=0; i<n; i++) {
        x[i] = (int)(lower_bound(vx.begin(),vx.end(),x[i]) - vx.begin());
        y[i] = (int)(lower_bound(vy.begin(),vy.end(),y[i]) - vy.begin());
        s[x[i]][y[i]]++;
    }
    for (int i=1; i<vx.size(); i++) {
        for (int j=1; j<vy.size(); j++) {
            s[i][j] += s[i-1][j] + s[i][j-1] - s[i-1][j-1];
        }
    }
    int s = 0, e = 1e4;
    while (s != e) {
        int m = (s+e)/2;
        if(trial(m) >= c) e = m;
        else s = m+1;
    }
    printf("%d",s+1);
}