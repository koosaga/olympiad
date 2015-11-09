#include "treasure.h"
#include <cstdlib>
#include <map>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
typedef pair<pi,pi> pip;

map<pip,short> mp;

int n;
short count2(int s, int e, int x, int y){
    if(mp.find(pip(pi(s,e),pi(x,y))) != mp.end()) return mp[pip(pi(s,e),pi(x,y))];
    return mp[pip(pi(s,e),pi(x,y))] = count(s,e,x,y);
}

void findTreasure(int N)
{
    n = N;
    int half = N/2;
    for (int i=1; i<=half; i++) {
        int b1 = count2(i,1,N,N);
        int b2 = count2(i+1,1,N,N);
        for (int j=1; j<=half; j++) {
            int s3 = count2(i,j+1,N,N);
            int s4 = count2(i+1,j+1,N,N);
            result(i,j,abs(b1 - b2 - s3 + s4) + '0');
            b1 = s3;
            b2 = s4;
        }
        b1 = count2(i,1,N,N) - b1;
        b2 = count2(i+1,1,N,N) - b2;
        for (int j=half+1; j<=N; j++) {
            int s3 = count2(i,1,N,j);
            int s4 = count2(i+1,1,N,j);
            result(i,j,abs(b1 - b2 - s3 + s4) + '0');
            b1 = s3;
            b2 = s4;
        }
    }
    for (int j=1; j<=half; j++) {
        mp[pip(pi(1,j),pi(half,N))] = count2(1,j,N,N) - count2(half+1,j,N,N);
    }
    for (int j=half+1; j<=N; j++) {
        mp[pip(pi(1,1),pi(half,j))] = count2(1,1,N,j) - count2(half+1,1,N,j);
    }
    mp[pip(pi(1,half+1),pi(half,N))] = count2(1,half+1,N,N) - count2(half+1,half+1,N,N);
    for (int i=half+1; i<=N; i++) {
        int b1 = count2(1,1,i-1,N);
        int b2 = count2(1,1,i,N);
        for (int j=1; j<=half; j++) {
            int s3 = count2(1,j+1,i-1,N);
            int s4 = count2(1,j+1,i,N);
            result(i,j,abs(b1 - b2 - s3 + s4) + '0');
            b1 = s3;
            b2 = s4;
        }
        b1 = count2(1,1,i-1,N) - b1;
        b2 = count2(1,1,i,N) - b2;
        for (int j=half+1; j<=N; j++) {
            int s3 = count2(1,1,i-1,j);
            int s4 = count2(1,1,i,j);
            result(i,j,abs(b1 - b2 - s3 + s4) + '0');
            b1 = s3;
            b2 = s4;
        }
    }
    return;
}