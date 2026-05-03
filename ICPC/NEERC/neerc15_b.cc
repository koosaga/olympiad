#include<bits/stdc++.h>
using namespace std;

struct fuck
{
    uint64_t vhi;
    uint64_t vmi;
    uint64_t vlo;
};

bool isovf(uint64_t x, uint64_t y, uint64_t & z)
{
    z = x+y;
    if(z<x || z< y) return true;
    return false;
}

fuck add(fuck x, fuck y)
{
    uint64_t carrylo, carrymi;
    fuck z;
    carrylo = isovf(x.vlo, y.vlo, z.vlo);
    carrymi = isovf(x.vmi, y.vmi, z.vmi);
    if(carrylo)
    {
        carrymi |= isovf(z.vmi, (uint64_t) 1, z.vmi);
    }
    isovf(x.vhi, y.vhi, z.vhi);
    if(carrymi)
        isovf(z.vhi, (uint64_t) 1, z.vhi);
    return z;
}

fuck nfill(int n)
{
    fuck z = {0, 0, 0};
    if(n<64)
        z.vlo = ((uint64_t)1 << n) - 1;
    else if( n<128)
    {
        z.vmi = ((uint64_t)1 << (n-64)) - 1;
        z.vlo = (uint64_t) 0 - (uint64_t)1;
    }
    else
    {
        z.vhi = ((uint64_t)1 << (n-128)) - 1;
        z.vmi = (uint64_t) 0 - (uint64_t)1;
        z.vlo = (uint64_t) 0 - (uint64_t)1;
    }
    return z;
}
fuck nshift(int n)
{
    fuck z = {0, 0, 0};
    if(n<64) z.vlo = (uint64_t) 1 << n;
    else if(n<128) z.vmi = (uint64_t) 1 << (n-64);
    else z.vhi = (uint64_t) 1 << (n-128);
    return z;
}
fuck band(fuck x, fuck y)
{
    fuck z;
    z.vlo = x.vlo & y.vlo;
    z.vmi = x.vmi & y.vmi;
    z.vhi = x.vhi & y.vhi;
    return z;
}
void print(fuck x)
{
    bool zero = false;
    for(int i=63; i>=0; --i)
    {
        if(x.vhi&(1ull<<i)) zero = true;
        if(!zero) continue;
        cout << !!(x.vhi&(1ull<<i));
    }
    for(int i=63; i>=0; --i)
    {
        if(x.vmi&(1ull<<i)) zero = true;
        if(!zero) continue;
        cout << !!(x.vmi&(1ull<<i));
    }
    for(int i=63; i>=0; --i)
    {
        if(x.vlo&(1ull<<i)) zero = true;
        if(!zero) continue;
        cout << !!(x.vlo&(1ull<<i));
    }
    return;
    cout << x.vhi << " " << x.vmi << " " << x.vlo << endl;
}
bool eq(fuck x, fuck y)
{
    return x.vlo == y.vlo && x.vmi == y.vmi && x.vhi == y.vhi;
}
fuck ptable[250];
int main()
{
    freopen("binary.in", "r", stdin);
    freopen("binary.out", "w", stdout);
    ptable[0] = {0, 0, 1};
    for(int i=1; i<190; ++i)
    {
        for(int x = 0; x < 10; ++x)
            ptable[i] = add(ptable[i], ptable[i-1]);
        //print(ptable[i]);
    }
    vector<pair< fuck, fuck> > x;
    fuck zero = {0,0,0};
    x.emplace_back(zero, zero);//dec, bin
    for(int n = 1; n < 190; ++n)
    {
        //cout << "*" << n << " " << x.size() << endl;
        vector<pair<fuck,fuck> > res;
        for(auto y: x)
        {
            //print(y.first);
            //print(y.second);
            fuck dec, bin; tie(dec, bin) = y;
            dec = add(dec, ptable[n-1]);
            bin = add(bin, nshift(n-1));
            //print(dec);
            //print(bin);
            if( eq( band(dec,  nfill(n) ) , bin ) )
            res.emplace_back(dec, bin);
        }
        for(auto y: res) x.push_back(y);
    }
    int t; scanf("%d", &t); print(x[t].second); puts("");
}
