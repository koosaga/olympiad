#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int n,t;

struct adja{
    int adj[205][205];
    void init(){
        memset(adj,0x3f,sizeof(adj));
    }
};

vector<int> x;

adja operator*(adja a, adja b){
    adja c;
    c.init();
    for (int i=1; i<x.size(); i++) {
        for (int j=1; j<x.size(); j++) {
            for (int k=1; k<x.size(); k++) {
                c.adj[i][j] = min(c.adj[i][j],a.adj[i][k] + b.adj[k][j]);
            }
        }
    }
    return c;
}

int s[105], e[105], c[105];

adja piv;

int main(){
    piv.init();
    int p,q;
    scanf("%d %d %d %d",&n,&t,&p,&q);
    x.push_back(p);
    x.push_back(q);
    for (int i=0; i<t; i++) {
        scanf("%d %d %d",&c[i],&s[i],&e[i]);
        x.push_back(s[i]);
        x.push_back(e[i]);
    }
    x.push_back(-1);
    sort(x.begin(),x.end());
    x.resize(unique(x.begin(),x.end()) - x.begin());
    for (int i=0; i<t; i++) {
        s[i] = (int)(lower_bound(x.begin(),x.end(),s[i]) - x.begin());
        e[i] = (int)(lower_bound(x.begin(),x.end(),e[i]) - x.begin());
    }
    p = (int)(lower_bound(x.begin(),x.end(),p) - x.begin());
    q = (int)(lower_bound(x.begin(),x.end(),q) - x.begin());
    for (int i=0; i<t; i++) {
        piv.adj[s[i]][e[i]] = piv.adj[e[i]][s[i]] = c[i];
    }
    int occu = 0;
    adja ret;
    while (n) {
        if(n&1){
            if(occu == 0){
                occu = 1;
                memcpy(ret.adj,piv.adj,sizeof(ret.adj));
            }
            else{
                ret = ret * piv;
            }
        }
        piv = piv * piv;
        n >>= 1;
    }
    printf("%d",ret.adj[p][q]);
}