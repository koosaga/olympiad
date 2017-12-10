#include<bits/stdc++.h>

using namespace std;

vector<pair<int, int>> v[1001];
int p, q, n;
char pp[10], qq[10];

vector<int> rar[301][301];
bool chk[301][301];

bool posi[1001];

void dfs(int x, int y)
{
    chk[x][y] = 1;
    for(int &k : rar[x][y])
    {
        if(posi[k])
            continue;
        
        posi[k] = 1;
        for(auto &p : v[k])
        {
            if(!chk[p.first][p.second])
                dfs(p.first, p.second);
        }
    }
}

int adj[305][305];


int main(){
    map<string, int> mp;
    int piv = 2;
    string x, y;
    cin >> x >> y;
    mp[x] = p = 1;
    mp[y] = q = 2;
    
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        int m;
        scanf("%d",&m);
        for(int j=0; j<m; j++){
            scanf("%s %s",pp,qq);
            string p = pp, q = qq;
            if(mp.find(p) == mp.end()) mp[p] = ++piv;
            if(mp.find(q) == mp.end()) mp[q] = ++piv;
            v[i].push_back(make_pair(mp[p], mp[q]));   
        }
    }
    
    int i;
    for(i=0;i<n;i++)
        for(auto &p: v[i])
            rar[p.first][p.second].push_back(i);
    
    dfs(p, q); adj[p][q] = 1;
    for(i=0;i<n;i++)
    {
        if(!posi[i])
            continue;
        
        for(auto &p : v[i]) adj[p.first][p.second] = 1;

    }
    for(int i=0; i<305; i++){
    for(int j=0; j<305; j++){
    for(int k=0; k<305; k++){
    adj[j][k] |= (adj[j][i] & adj[i][k]);
    }
    }
    }
    
    for(i=1;i<=300;i++)
    {
        if(adj[i][i]){
                printf("No");
                return 0;
        }
    }
    
    for(i=0;i<n;i++)
    {
        if(posi[i])
            continue;
        for(auto &p : v[i])
        {
            if(adj[p.first][p.second])
            {
                printf("No");
                return 0;
            }
        }
    }
    printf("Yes");
    return 0;
}
