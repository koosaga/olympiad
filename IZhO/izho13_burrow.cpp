#include <cstdio>
#include <vector>
using namespace std;
 
int n,m,k;
int a[1005][1005];
int t[1005][1005];
 
int eval(){
    vector<int> v;
    int ret = 0;
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            while (!v.empty() && t[i][v.back()] > t[i][j]) {
                int wid = 0;
                int bk = v.back();
                v.pop_back();
                if(v.empty()){
                    wid = j-1;
                }
                else{
                    wid = j - v.back() - 1;
                }
                ret = max(ret,t[i][bk] * wid);
            }
            v.push_back(j);
        }
        while (!v.empty()) {
            int wid = 0;
            int bk = v.back();
            v.pop_back();
            if(v.empty()){
                wid = m;
            }
            else{
                wid = m - v.back();
            }
            ret = max(ret,t[i][bk] * wid);
        }
    }
    return ret;
}
 
int main(){
    scanf("%d %d %d",&n,&m,&k);
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            scanf("%d",&a[i][j]);
        }
    }
    int s = 0, e = 1e9;
    while (s != e) {
        int mi = (s+e+1)/2;
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=m; j++) {
                t[i][j] = (a[i][j] >= mi ? (t[i-1][j] + 1) : 0);
            }
        }
        if(eval() >= k) s = mi;
        else e = mi-1;
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            t[i][j] = (a[i][j] >= s ? (t[i-1][j] + 1) : 0);
        }
    }
    printf("%d %d\n",s,eval());
}