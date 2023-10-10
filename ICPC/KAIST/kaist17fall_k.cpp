//hyea
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1010101;
int N, M;
vector<int> adj[MAXN];
vector<int> invadj[MAXN];
int cycnode[MAXN];
int cycnum[MAXN];
int Sx, Sy;
int Ex, Ey;
int main()
{
    scanf("%d%d",&N,&M);
    for(int i=0; i<M; ++i)
    {
        int s, e; scanf("%d%d",&s,&e);
        adj[s].push_back(e);
        invadj[e].push_back(s);
    }
    int S, E;
    for(int i=1; i<=N; ++i)
    {
        int diff = (int)adj[i].size()-(int)invadj[i].size();
        if(diff==1) S = i;
        if(diff==-1) E = i;
    }
    int ss; int ee;
    scanf("%d%d",&ss,&ee);
    int node = S, pnode = -1;
    int t;
    
    for(t=0;node!=E; ++t)
    {
        int nextnode = 0;
        int cl = 0;
        if(invadj[node].size()==2)
        {
            int u = invadj[node][0]^invadj[node][1]^pnode;
            int now = u, pnow = -1;
            cl = 1;
            while(now != node)
            {
                if(now==ss)
                {
                    Sx = t; Sy = cl;
                }
                if(now==ee)
                {
                    Ex = t; Ey = cl;
                }
                pnow = now;
                now = invadj[now][0]; ++cl;
            }
            nextnode = adj[node][0]^adj[node][1]^pnow;
        }
        else nextnode = adj[node][0]; 
        //printf("%d %d %d\n", node ,ss ,ee);
        if(node==ss) Sx = t;
        if(node==ee) Ex = t;
        
        cycnode[t] = node;
        cycnum[t] = cl;
        pnode = node;
        node = nextnode;
    }
    cycnode[t] = E;
    cycnum[t] = 0;
    if(E==ss) Sx = t;
    if(E==ee) Ex = t;
    ++t;

    if(make_pair(Sx, Sy) > make_pair(Ex, Ey))
    {
        swap(Sx, Ex);
        swap(Sy, Ey);
    }
    
    /*
    for(int i=0; i<t; ++i)
    {
        printf("%d %d\n", cycnode[i], cycnum[i]);
    }
    printf("S: %d %d\n", Sx, Sy);
    printf("E: %d %d\n", Ex, Ey);
    */
    int g = 0, d = abs(Ex-Sx + Sy-Ey);
    int i;
    for(i=Sx; i<Ex; ++i) g = __gcd(g, cycnum[i]);
    //printf("--%d\n", g);
    //printf(">%d %d %d\n", i, t, cycnum[i]);
    for(;!cycnum[i] && i<t; ++i);// printf(">%d %d %d\n", i, t, cycnum[i]);
    for(;i<t; ++i)
    {
        g = __gcd(g, cycnum[i]);
        if(d==0 || (g!=0 && d%g==0))
        {
            printf("%d\n", cycnode[i]);
            return 0;
        }
    }
    puts("MUSUBI");
    return 0;
    
    
}