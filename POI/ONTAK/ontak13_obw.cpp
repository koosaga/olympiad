// by hyea
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 505050;
int N, M;
int ufd[MAXN];
void init(){for(int i=0;i<MAXN;++i)ufd[i]=i;}
int Find(int a){if(a==ufd[a]) return a; else return ufd[a] = Find(ufd[a]);}
void Union(int a, int b){ufd[Find(a)] = Find(b);}

int main()
{
    int ans = 0;
    using ti = tuple<int, int, int>;
    vector<ti> V;
    scanf("%d%d", &N, &M);
    for(int i=0; i<M; ++i)
    {
        int s, e, x;
        scanf("%d%d%d", &s, &e, &x);
        V.emplace_back(x, s, e);
    }
    sort(V.rbegin(), V.rend());
    long long cost = 0;
    
    init();
    for(int i=0; i<V.size(); ++i)
    {
        int x, s, e; tie(x,s,e) = V[i];
        if(Find(s) != Find(e))
        {
            Union(s, e);
            if(x<0) cost += x;
        }
        else cost += x;   
    }
    printf("%lld\n", cost);
    return 0;
    
}
