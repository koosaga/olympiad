//by hyea
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 8192;
int grundy[MAXN];
int N;
char buf[MAXN];
bool used[3010][MAXN];
pair<int, int> dat[3010][MAXN];
void init()
{
    grundy[0] = 1;
    used[0][0] = true;
    dat[0][0] = make_pair(1, 0);
    for(int i=1; i<N; ++i)
    {
        used[i][0] = true;
        dat[i][0] = make_pair(1, i);
        for(int gap = 1; gap < N; ++gap)
        {
            int x = 0;
            for(int j=i; j>=0; j -= gap)
            {
                x ^= grundy[j];
                used[i][x] = true;
                dat[i][x] = make_pair(gap, j);
            }
        }
        for(int j=0; j<MAXN; ++j)
        {
            if(!used[i][j])
            {
                grundy[i] = j;
                break;
            }
        }
    }
    //for(int i=0; i<N; ++i)
    //    printf("%d ", grundy[i]);
}
int main()
{
    scanf("%s", buf);
    //N = 3000;
    //for(int i=0; i<N; ++i) buf[i] = 'N';
    N=strlen(buf);
    reverse(buf, buf+N);
    init();
    int ans = 0;
    for(int i=0; i<N; ++i)
        if(buf[i] == 'N') ans ^= grundy[i];
    if(ans == 0)
    {
        puts("NIE");
        return 0;
    }
    for(int i=0; i<N; ++i)
    {
        if(buf[i] == 'N')
            if(used[i][ans^grundy[i]])
            {
                for(int j=i; j>=dat[i][ans^grundy[i]].second; j -= dat[i][ans^grundy[i]].first)
                    buf[j] ^= ('N'^'S');
                reverse(buf, buf+N);
                puts(buf);
                return 0;
            }
    }
    assert(false);
}




