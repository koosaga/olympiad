#include <cstdio>
#include <stack>
#include <utility>
#include <set>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

int n,p,q;
int d[250005];
pi a[250005];
stack<pi> st;

struct tree1{
    int tree[530000], lim;
    void init(){
        for(lim = 1; lim <= p; lim <<= 1);
        for(int i=1; i<p; i++){
            tree[i+lim] = i;
        }
        for(int i=lim; i; i--){
            if(d[tree[2*i]] < d[tree[2*i+1]]){
                tree[i] = tree[2*i+1];
            }
            else tree[i] = tree[2*i];
        }
    }
    void upd(int p){
        p += lim;
        while(p > 1){
            p >>= 1;
            if(d[tree[2*p]] < d[tree[2*p+1]]){
                tree[p] = tree[2*p+1];
            }
            else tree[p] = tree[2*p];
        }
    }
    int low(int pos){
        int p = 1;
        while(p < lim){
            if(d[tree[2*p+1]] > d[pos]){
                p = 2*p+1;
            }
            else p = 2*p;
        }
        return tree[p];
    }
    int q(int s, int e){
        int ret = 0;
        s += lim;
        e += lim;
        while(s < e){
            if(s%2 == 1){
                if(d[tree[s]] > d[ret]){
                    ret = tree[s];
                }
                s++;
            }
            if(e%2 == 0){
                if(d[tree[e]] > d[ret]){
                    ret = tree[e];
                }
                e--;
            }
            s >>= 1;
            e >>= 1;
        }
        if(s == e && d[tree[s]] > d[ret]) ret = tree[s];
        return ret;
    }
}tree1;

struct tree2{
    int tree[530000], lim;
    void init(){
        for(lim = 1; lim <= n - p; lim <<= 1);
        for(int i=1; i<=n-p; i++){
            tree[i+lim] = i + p;
        }
        for(int i=lim; i; i--){
            if(d[tree[2*i]] < d[tree[2*i+1]]){
                tree[i] = tree[2*i+1];
            }
            else tree[i] = tree[2*i];
        }
    }
    void upd(int p){
        p -= ::p;
        p += lim;
        while(p > 1){
            p >>= 1;
            if(d[tree[2*p]] < d[tree[2*p+1]]){
                tree[p] = tree[2*p+1];
            }
            else tree[p] = tree[2*p];
        }
    }
    int low(int pos){
        int p = 1;
        while(p < lim){
            if(d[tree[2*p]] > d[pos]){
                p = 2*p;
            }
            else p = 2*p+1;
        }
        return tree[p];
    }
    int q(int s, int e){
        int ret = 0;
        s -= p;
        e -= p;
        s += lim;
        e += lim;
        while(s < e){
            if(s%2 == 1){
                if(d[tree[s]] > d[ret]){
                    ret = tree[s];
                }
                s++;
            }
            if(e%2 == 0){
                if(d[tree[e]] > d[ret]){
                    ret = tree[e];
                }
                e--;
            }
            s >>= 1;
            e >>= 1;
        }
        if(s == e && d[tree[s]] > d[ret]) ret = tree[s];
        return ret;
    }
}tree2;

int count(int t){
    if(t == p) return 0;
    if(t < p){
        int pos = tree1.q(t,p-1);
        if(d[tree2.q(p+1,n)] < d[pos]) return n - t;
        return tree2.low(pos) - t - 1;
    }
    else{
        int pos = tree2.q(p+1,t);
        if(d[tree1.q(1,p-1)] < d[pos]) return t - 1;
        int cnt = t  - tree1.low(pos) - 1;
        return cnt;
    }
}

int main(){
    scanf("%d %d",&n,&p);
    for (int i=1; i<=n; i++) {
        scanf("%d",&d[i]);
        a[i] = pi(d[i],i);
    }
    scanf("%d",&q);
    sort(a+1,a+n+1);
    for (int i=1; i<=n; i++) {
        st.push(a[i]);
    }
    tree1.init();
    tree2.init();
    for (int i=0; i<q; i++) {
        char str[3];
        scanf("%s",str);
        if(str[0] == 'E'){
            int p,q;
            scanf("%d %d",&p,&q);
            stack<pi> st2;
            set<int> s;
            for (int j=0; j<q-1; j++) {
                pi t = st.top();
                st.pop();
                if(s.find(t.second) != s.end()){
                    j--;
                    continue;
                }
                s.insert(t.second);
                d[t.second]++;
                t.first++;
                st2.push(t);
            }
            if(st.empty()) d[p] = 1;
            else d[p] = st.top().first+1;
            st.push(pi(d[p],p));
            while (!st2.empty()) {
                st.push(st2.top());
                st2.pop();
            }
            if(p < ::p) tree1.upd(p);
            else tree2.upd(p);
        }
        else if(str[0] == 'F'){
            int t;
            scanf("%d",&t);
            printf("%d\n",count(t));
        }
    }
}