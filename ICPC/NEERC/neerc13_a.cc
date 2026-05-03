#include<bits/stdc++.h>
using namespace std;

char a[17][14][14];

void p(char c)
{
    if(c == 0)
        printf(".");
    else
        printf("%c", c);
}

char tmp[23][23];
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

void flood(int x, int y)
{
    tmp[x][y] = 'Y';
    for(int d=0;d<4;d++)
    {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if(0<=nx&&nx<23&&0<=ny&&ny<23&&!tmp[nx][ny])
            flood(nx, ny);
    }
}

int n, k, w, h, W, H;
bool ver[17][17];
bool hor[17][17];

bool chk[17];
int sta[4][4];

bool f(int x, int y)
{
    if(y == n)
    {
        x++;
        y = 0;
    }
    
    if(x == n)
        return 1;
    
    for(int b=1;b<=k;b++)
    {
        if(chk[b])
            continue;
        
        if(!(x == 0 ? ver[0][b] : ver[sta[x-1][y]][b]))
            continue;
        
        if(!(y == 0 ? hor[0][b] : hor[sta[x][y-1]][b]))
            continue;
        
        if(x == n-1 && !ver[b][0])
            continue;
        
        if(y == n-1 && !hor[b][0])
            continue;
        
        chk[b] = 1;
        sta[x][y] = b;
        
        if(f(x, y+1))
            return 1;
        
        chk[b] = 0;
    }
    
    return 0;
}

char res[21][21];

int main()
{
    int i, j;
    scanf("%d%d%d", &k, &w, &h);
    for(int b=1;b<=k;b++)
        for(i=0;i<3*h-2;i++)
            scanf("%s", a[b][i]);
    
    for(int b=1;b<=k;b++)
        for(i=0;i<3*h-2;i++)
            for(j=0;j<3*w-2;j++)
                if(a[b][i][j] == '.')
                    a[b][i][j] = 0;
    
    for(i=1;i<=4;i++)
        if(i*i == k)
            n = i;
    
    for(i=h-1;i<2*h-1;i++)
        for(j=w-1;j<2*w-1;j++)
            a[0][i][j] = 'Z';
    
    for(int b1=0;b1<=k;b1++)
    {
        for(int b2=0;b2<=k;b2++)
        {
            if(b1 == b2)
                continue;
                
            memset(tmp, 0, sizeof tmp);
            
            for(i=0;i<3*h-2;i++)
                for(j=0;j<3*w-2;j++)
                    tmp[i][j] = a[b1][i][j];
            
            bool ok = 1;
            for(i=0;i<3*h-2;i++)
            {
                for(j=0;j<3*w-2;j++)
                {
                    if(a[b2][i][j])
                    {
                        if(tmp[i+h][j])
                        {
                            tmp[i+h][j] = 'X';
                            ok = 0;
                        }
                        else
                            tmp[i+h][j] = a[b2][i][j];
                    }
                }
            }
            
            for(i=0;i<=22;i++)
            {
                for(j=0;j<=22;j++)
                {
                    if(i == 0 || i == 22 || j == 0 || j == 22)
                    {
                        if(!tmp[i][j])
                            flood(i, j);
                    }
                }
            }
            
            
            for(i=h;i<3*h-2;i++)
            {
                for(j=w;j<2*w-2;j++)
                {
                    if(!tmp[i][j])
                        ok = 0;
                }
            }
            
            if(ok)
                ver[b1][b2] = 1;
                
                
            /*
            for(i=0;i<4*h-2;i++)
            {
                for(j=0;j<4*w-2;j++)
                    p(tmp[i][j]);
                puts("");
            }
            printf("ok = %d\n", (int)ok);
            */
            
            memset(tmp, 0, sizeof tmp);
            
            for(i=0;i<3*h-2;i++)
                for(j=0;j<3*w-2;j++)
                    tmp[i][j] = a[b1][i][j];
            
            ok = 1;
            for(i=0;i<3*h-2;i++)
            {
                for(j=0;j<3*w-2;j++)
                {
                    if(a[b2][i][j])
                    {
                        if(tmp[i][j+w])
                        {
                            tmp[i][j+w] = 'X';
                            ok = 0;
                        }
                        else
                            tmp[i][j+w] = a[b2][i][j];
                    }
                }
            }
            
            for(i=0;i<=22;i++)
            {
                for(j=0;j<=22;j++)
                {
                    if(i == 0 || i == 22 || j == 0 || j == 22)
                    {
                        if(!tmp[i][j])
                            flood(i, j);
                    }
                }
            }
            
            for(i=h;i<2*h-2;i++)
            {
                for(j=w;j<3*w-2;j++)
                {
                    if(!tmp[i][j])
                        ok = 0;
                }
            }
            
            if(ok)
                hor[b1][b2] = 1;
            
            
            /*
            for(i=0;i<4*h-2;i++)
            {
                for(j=0;j<4*w-2;j++)
                    p(tmp[i][j]);
                puts("");
            }
            printf("ok = %d\n", (int)ok);
            */
        }
    }
    
    assert(f(0, 0));
    
    H = n*h;
    W = n*w;
    
    for(int ti=0;ti<n;ti++)
    {
        for(int tj=0;tj<n;tj++)
        {
            int b = sta[ti][tj];
            for(i=0;i<3*h-2;i++)
            {
                for(j=0;j<3*w-2;j++)
                {
                    if(a[b][i][j])
                    {
                        assert(!res[i + h*ti - h + 1][j + w*tj - w + 1]);
                        res[i + h*ti - h + 1][j + w*tj - w + 1] = a[b][i][j];
                    }
                }
            }
        }
    }
    /*
    for(i=0;i<H;i++)
    {
        for(j=0;j<W;j++)
            p(res[i][j]);
        puts("");
    }
    */
    for(i=0;i<H;i++)
        for(j=0;j<W;j++)
            assert(res[i][j]);
    
    printf("%d %d\n", W, H);
    for(i=0;i<H;i++)
        printf("%s\n", res[i]);
    
    return 0;
}

