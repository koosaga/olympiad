#include<bits/stdc++.h>
using namespace std;

char arr[1010][1010];
bool las[1010][1010];

struct str
{
    int x1, y1, x2, y2;
};

vector<str> res;

int main()
{
    int n, k, i, j;
    scanf("%d%d", &n, &k);
    for(i=0;i<n;i++)
        scanf("%s", arr[i]);
    
    int lastrow = 0;
    for(i=0;i<n;i++)
    {
        for(j=n-1;j>=0;j--)
        {
            if(arr[i][j] == 'x')
            {
                lastrow = i;
                las[i][j] = 1;
                break;
            }
        }
    }
    
    int p = 0, q = 0, c = 0;
    for(i=0;i<n;i++)
    {
        bool upd = 0;
        for(j=0;j<n;j++)
        {
            if(arr[i][j] == '.')
                continue;
                
            c++;
            
            str t;
            t.x1 = (i == lastrow) ? n-1 : i;
            t.y1 = q;
            t.x2 = p;
            t.y2 = (las[i][j]) ? n-1 : j;
            res.push_back(t);
            
            q = j+1;
            upd = 1;
            
            if(c == k)
                break;
        }
        
        if(c == k)
                break;
        
        q = 0;
        if(upd)
            p = i+1;
    }
    
    res.back().y2 = n-1;
    int tx = res.back().x1;
    
    for(str &t : res)
    {
        if(t.x1 == tx)
            t.x1 = n - 1;
    }
    
    for(str &t : res)
    {
        str r;
        r.y1 = n - t.x1 - 1;
        r.x1 = t.y1;
        r.y2 = n - t.x2;
        r.x2 = t.y2 + 1;
        
        printf("%d %d %d %d\n", r.x1, r.y1, r.x2, r.y2);
    }
    
    return 0;
}





