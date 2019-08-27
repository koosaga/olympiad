/**
 * Author: THU
 * Description: O(EV) general matching
 */

// vertices 1~n, chd[x]=0 or y (x match y)
int n;
vector<int> g[N];
int chd[N],nex[N],fl[N],fa[N];
int gf(int x){return fa[x]==x?x:fa[x]=gf(fa[x]);}
void un(int x,int y){x=gf(x),y=gf(y);fa[x]=y;}
int qu[N],p,q;
int lca(int u,int v){
	static int t=0,x[N];
	t++;
	for(;; swap(u,v) )
		if(u){
			u=gf(u);
			if(x[u]==t)return u;
			x[u]=t;
			u= chd[u] ? nex[chd[u]] : 0;
		}
}
void lk(int a,int x){
	while(a!=x){
		int b=chd[a],c=nex[b];
		if(gf(c)!=x)nex[c]=b;
		if(fl[b]==2)fl[qu[q++]=b]=1;
		if(fl[c]==2)fl[qu[q++]=c]=1;
		un(a,b);un(b,c);
		a=c;
	}
}
void find(int rt){
	rep(i,1,n+1)nex[i]=fl[i]=0,fa[i]=i;
	p=q=0;qu[q++]=rt;fl[rt]=1;
	while(p!=q){
		int u=qu[p++];
		trav(v, g[u]) {
			if(gf(v)==gf(u) || fl[v]==2 || v==chd[u])continue;
			if(fl[v]==1){
				int x=lca(u,v);
				if(gf(u)!=x)nex[u]=v;
				if(gf(v)!=x)nex[v]=u;
				lk(u,x);
				lk(v,x);
			}else if(!chd[v]){
				nex[v]=u;
				while(v){
					u=nex[v];
					int t=chd[u];
					chd[v]=u;chd[u]=v;
					v=t;
				}
				return;
			}else{
				nex[v]=u;
				fl[v]=2;
				fl[qu[q++]=chd[v]]=1;
			}
		}
	}
}
int run_match(){
	memset(chd,0,sizeof(chd));
	rep(i,1,n+1)if(!chd[i])find(i);
	int cnt = 0;
	rep(i,1,n+1) cnt += bool(chd[i]);
	return cnt/2;
}
