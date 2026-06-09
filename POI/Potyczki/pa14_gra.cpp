#include<bits/stdc++.h>
using namespace std;
struct place
{
    int32_t cnt;
    int16_t x, y;
};
bool operator<(const place& x, const place& y)
{
    return tie(x.cnt, x.x, x.y) < tie(y.cnt, y.x, y.y);
}
bool operator==(const place& x, const place& y)
{
    return tie(x.cnt, x.x, x.y) == tie(y.cnt, y.x, y.y);
}
int c;
vector<vector<place> > Px[17];
vector<pair<uint64_t, pair<int, int> > > TR[17];
pair<uint64_t, pair<int, int> > tr(vector<place> P)
{
    int minx = 0, miny = 0, maxx=0, maxy = 0;
    for(auto p: P)
    {
        minx = min(minx, (int)p.x);
        miny = min(miny, (int)p.y);
        maxx = max(maxx, (int)p.x);
        maxy = max(maxy, (int)p.y);
    }
    pair<int, int> ans = make_pair(-minx, -miny);
    uint64_t H = 0;
    for(auto& p: P)
    {
        p.x += -minx;
        p.y += -miny;
        assert(p.x < 8 && p.y < 8);
        H += uint64_t(1) << (p.x*8 + p.y);
    }
    return make_pair(H, ans);
}
void bktk(vector<place> P)
{
    //split place 0 into two

    assert(P[0].cnt != 0);
    if(P[0].cnt == 1)
    {
        Px[P.size()].push_back(P);
        return;
    }
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, 1, 0, -1};
    for(int d=0; d<4; ++d)
    {
        P[0].cnt /= 2;
        place targ = {P[0].cnt, P[0].x + dx[d], P[0].y + dy[d]};
        P.push_back(targ);

        sort(P.rbegin(), P.rend());
        
        bool flag = false;
        for(int i=0; i<P.size() && !flag; ++i)
            for(int j=0; j<i && !flag; ++j)
            {
                if(P[i].x == P[j].x && P[i].y == P[j].y)
                flag = true;
            }
        if(!flag) bktk(P);
        for(int i=0; i<P.size(); ++i)
        {
            if(P[i].x == targ.x && P[i].y == targ.y && P[i].cnt == targ.cnt)
            {
                P.erase(P.begin()+i);
                break;
            }
        }
        for(int i=0; i<P.size(); ++i)
        {
            if(P[i].x == targ.x-dx[d] && P[i].y == targ.y-dy[d])
                P[i].cnt *= 2;
        }
        sort(P.rbegin(), P.rend());
    }
}
int N, M;
int x[256][256];
int ans[256][256];
int main()
{
    int N, M; scanf("%d%d", &N, &M);
    for(int i=10; i<N+10; ++i)
        for(int j=10; j<M+10; ++j)
            scanf("%1d",&x[i][j]);
    for(int i=1; i<=16; i *= 2)
    {
        vector<place> P;
        P.push_back({i, 0, 0}); bktk(P);
        sort(Px[i].begin(), Px[i].end());
        Px[i].resize(unique(Px[i].begin(), Px[i].end())-Px[i].begin());
        for(auto x: Px[i])
            TR[i].push_back(tr(x));
    }
    for(int i=10; i<N+10; ++i)
        for(int j=10; j<M+10; ++j)
        {
            uint64_t HASH = 0;
            for(int k=0; k<8; ++k)
                for(int s = 0; s<8; ++s)
                    HASH += uint64_t(x[i+k][j+s]) << (k*8+s);
            for(int d=16; d>=1; d/=2)
            {
                for(auto y: TR[d])
                {
                    auto H = y.first;
                    if(H&~HASH) continue;
                    ans[i+y.second.first][j+y.second.second] = max(
                    ans[i+y.second.first][j+y.second.second], d);
                }
            }
        }
    for(int i=10; i<N+10; ++i,puts(""))
        for(int j=10; j<M+10; ++j)
            printf("%d ",ans[i][j]);
    return 0;
}