#include <cstdio>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;
 
int n,m;
int st[1000005], back[1000005], link[1000005], v[500005], nex[1000005], sz;
 
vector<int> cyc, temp;
 
void add_edge(int s, int e){
    sz++;
    link[sz] = e; back[sz] = st[s]; st[s] = sz; nex[back[sz]] = sz;
    sz++;
    link[sz] = s; back[sz] = st[e]; st[e] = sz; nex[back[sz]] = sz;
}
 
void f(int x){
    stack<int> s;
    s.push(1);
    while (!s.empty()) {
        int x = s.top();
        int p = st[x];
        int pushed = 0;
        while (p) {
            int pos = link[p];
            int q = (p+1)/2;
            int r = p;
            if(p&1) r++;
            else r--;
            st[x] = p = back[p];
            if(r == st[pos]){
                st[pos] = back[r];
            }
            else{
                int s = nex[r];
                back[s] = back[r];
                nex[back[r]] = s;
            }
            if(!v[q]){
                v[q]=1;
                s.push(pos);
                pushed++;
                break;
            }
        }
        if(!pushed) s.pop();
        if(!pushed) cyc.push_back(x);
    }
}
 
int vis[500005];
int main(){
    scanf("%d %d",&n,&m);
    for (int i=0; i<m; i++) {
        int s,e;
        scanf("%d %d",&s,&e);
        add_edge(s,e);
    }
    f(1);
    for (int i=0; i<cyc.size(); i++) {
        temp.push_back(cyc[i]);
        if(vis[cyc[i]]){
            printf("%d",temp.back());
            temp.pop_back();
            while(temp.back() != cyc[i]){
                printf(" %d",temp.back());
                vis[temp.back()] = 0;
                temp.pop_back();
                if(temp.back() == cyc[i]) printf("\n");
            }
        }
        else vis[cyc[i]] = 1;
    }
}