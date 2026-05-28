#include<bits/stdc++.h>
using namespace std;

int a[1000010];
int b[1000010];
bool chk[1000010];
int t[1000010];
int t2[1000010];

vector<pair<int, int>> vec;

bool pos()
{
    sort(vec.begin(), vec.end());
    vec.resize(unique(vec.begin(), vec.end())-vec.begin());
    for(int i=0; i<vec.size()-1; ++i)
    {
        if(vec[i].first == vec[i+1].first)
            return false;
    }
    for(int i=0; i<vec.size(); ++i)
        for(int j=0; j<i; ++j)
        {
            int clen = __gcd(vec[i].first, vec[j].first);
            int diff = abs(vec[i].second - vec[j].second);
            if(diff % clen != 0) return false;
        }
    return true;
}

int main()
{
    int n, i, j, k;
    scanf("%d", &n);
    for(i=1;i<=n;i++)
        scanf("%d", &a[i]);
    for(i=1;i<=n;i++)
        scanf("%d", &b[i]);
    
    for(i=1;i<=n;i++)
    {
        if(chk[i])
            continue;
        
        int x = i;
        int s = 0;
        while(!chk[x])
        {
            chk[x] = 1;
            t[s++] = x;
            x = a[x];
        }
        
        for(j=0;j<s;j++)
            t2[j] = b[t[j]];
        
        bool ok = 0;
        
        int sp;
        for(j=0;j<s;j++)
        {
            if(t[0] == t2[j])
            {
                sp = j;
                ok = 1;
                for(k=j;k<j+s;k++)
                {
                    if(t[(k-j+s)%s] != t2[k%s])
                    {
                        ok = 0;
                        break;
                    }
                }
                break;
            }
        }
        
        if(!ok)
        {
            printf("NIE\n");
            return 0;
        }
        
        vec.push_back({s, j});
    }
    
    if(!pos()) 
    {
        puts("NIE");
        return 0;
    }

    printf("TAK\n");
    return 0;
}



