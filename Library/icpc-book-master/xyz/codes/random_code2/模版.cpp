#include<iostream>
#include<cstdio>
#include<set>
#include<queue>
using namespace std;
struct aa{int a,b;};
priority_queue <int,vector<int>,greater<int> > qu;
set<int>xyz;
bool operator > (aa a,aa b){return a.a*a.b>b.a*b.b;}
int main(){};
