#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
typedef long long lint;
 
int n,k;
vector<pi> sol;
 
lint solve(){
    if(sol.empty()) return 0;
    vector<int> ret;
    for(auto i : sol){
        ret.push_back(i.first);
        ret.push_back(i.second);
    }
    sort(ret.begin(),ret.end());
    int med = ret[ret.size()/2];
    lint res = 0;
    for(auto i : ret){
        lint t = i;
        t -= med;
        res += max(t,-t);
    }
    return res;
}
 
bool cmp(pi a, pi b){
    return a.first + a.second < b.first + b.second;
}
 
vector<int> cand;
 
struct bit{
    lint tree[200005];
    int piv;
    void init(int n){
        piv = n+2;
        memset(tree,0,sizeof(tree));
    }
    void add(int x, int v){
        x += 2;
        while(x <= piv){
            tree[x] += v;
            x += x & -x;
        }
    }
    int kth(int k){
        int p = 0;
        for(int i=17; i>=0; i--){
            if((p|1<<i) <= piv && tree[p|(1<<i)] < k){
                p |= 1<<i;
                k -= tree[p];
            }
        }
        return p-1;
    }
    lint sum(int x){
        x += 2;
        lint ret = 0;
        while(x){
            ret += tree[x];
            x -= x & -x;
        }
        return ret;
    }
    lint sum_range(int s, int e){
        return sum(e) - sum(s-1);
    }
}bit1, bit2;
 
lint dp1[100005], dp2[100005];
 
lint solve2(){
    if(sol.empty()) return 0;
    sort(sol.begin(), sol.end(), cmp);
    for (auto &i : sol){
        cand.push_back(i.first);
        cand.push_back(i.second);
    }
    sort(cand.begin(), cand.end());
    cand.resize(unique(cand.begin(),cand.end()) - cand.begin());
    for (auto &i : sol){
        i.first = (int)(lower_bound(cand.begin(),cand.end(),i.first) - cand.begin());
        i.second = (int)(lower_bound(cand.begin(),cand.end(),i.second) - cand.begin());
    }
    bit1.init((int)cand.size());
    bit2.init((int)cand.size());
    for (int i=0; i<sol.size(); i++){
        pi t = sol[i];
        bit1.add(t.first,1);
        bit1.add(t.second,1);
        bit2.add(t.first,cand[t.first]);
        bit2.add(t.second,cand[t.second]);
        int piv = bit1.kth(i+1);
        dp1[i] += bit2.sum_range(piv+1,(int)cand.size()-1);
        dp1[i] -= bit1.sum_range(piv+1,(int)cand.size()-1) * cand[piv];
        dp1[i] += bit1.sum_range(0,piv-1) * cand[piv];
        dp1[i] -= bit2.sum_range(0,piv-1);
    }
    bit1.init((int)cand.size());
    bit2.init((int)cand.size());
    for (int i=(int)sol.size()-1; i>=0; i--) {
        pi t = sol[i];
        bit1.add(t.first,1);
        bit1.add(t.second,1);
        bit2.add(t.first,cand[t.first]);
        bit2.add(t.second,cand[t.second]);
        int piv = bit1.kth((int)sol.size()-i);
        dp2[i] += bit2.sum_range(piv+1,(int)cand.size()-1);
        dp2[i] -= bit1.sum_range(piv+1,(int)cand.size()-1) * cand[piv];
        dp2[i] += bit1.sum_range(0,piv-1) * cand[piv];
        dp2[i] -= bit2.sum_range(0,piv-1);
    }
    lint ans = 1e18;
    for (int i=0; i<=sol.size(); i++) {
        ans = min(ans,(i ? dp1[i-1] : 0) + dp2[i]);
    }
    return ans;
}
 
int main(){
    lint ret = 0;
    scanf("%d %d",&k,&n);
    for(int i=0; i<n; i++){
        char s1[5], s2[5];
        int t,u;
        scanf("%s %d %s %d",s1,&t,s2,&u);
        if(t > u) swap(t,u);
        if(s1[0] != s2[0]){
            sol.push_back(pi(t,u));
        }
        else{
            ret += u - t - 1;
        }
    }
    ret += n;
    if(k == 1) ret += solve();
    else ret += solve2();
    printf("%lld",ret);
}