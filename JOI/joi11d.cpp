#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
 
struct bit{
    long long tree[100005];
    int n;
    void init(int _n){
        n = _n;
    }
    void add(int x, int v){
        while(x <= n){
            tree[x]+=v;
            x += x & -x;
        }
    }
    int kth(int x){
        int pos = 0;
        for(int i=16; i>=0; i--){
            if((pos|1<<i) <= n){
                if(tree[pos|1<<i] < x){
                    x -= tree[pos|1<<i];
                    pos |= (1<<i);
                }
            }
        }
        return pos+1;
    }
    long long sum(int x){
        long long ret = 0;
        while(x){
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
}bitx, bity, sumx, sumy;
 
int n, x[100005], y[100005];
vector<int> vx, vy;
 
int main(){
    scanf("%*d %*d %d",&n);
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
    bitx.init((int)vx.size());
    bity.init((int)vy.size());
    sumx.init((int)vx.size());
    sumy.init((int)vy.size());
    for (int i=0; i<n; i++) {
        x[i] = (int)(lower_bound(vx.begin(),vx.end(),x[i]) - vx.begin());
        y[i] = (int)(lower_bound(vy.begin(),vy.end(),y[i]) - vy.begin());
        bitx.add(x[i],2);
        bity.add(y[i],2);
        sumx.add(x[i],vx[x[i]]*2);
        sumy.add(y[i],vy[y[i]]*2);
    }
    long long ret = 1e18;
    int retx = 1e9, rety = 1e9;
    for (int i=0; i<n; i++) {
        bitx.add(x[i],-1);
        bity.add(y[i],-1);
        sumx.add(x[i],-vx[x[i]]);
        sumy.add(y[i],-vy[y[i]]);
        int px = bitx.kth(n);
        int py = bity.kth(n);
        long long sum = 0;
         
        long long cnt = bitx.sum((int)vx.size()) - bitx.sum(px);
        sum += sumx.sum((int)vx.size()) - sumx.sum(px) - cnt * vx[px];
        sum += bitx.sum(px-1) * vx[px] - sumx.sum(px-1);
         
         
        cnt = bity.sum((int)vy.size()) - bity.sum(py);
        sum += sumy.sum((int)vy.size()) - sumy.sum(py) - cnt * vy[py];
        sum += bity.sum(py-1) * vy[py] - sumy.sum(py-1);
         
        if(ret > sum){
            ret = sum;
            retx = vx[px];
            rety = vy[py];
        }
        else if(ret == sum && make_pair(retx,rety) > make_pair(vx[px],vy[py])){
            retx = vx[px];
            rety = vy[py];
        }
         
        bitx.add(x[i],1);
        bity.add(y[i],1);
        sumx.add(x[i],vx[x[i]]);
        sumy.add(y[i],vy[y[i]]);
    }
    printf("%lld\n%d %d",ret,retx,rety);
}