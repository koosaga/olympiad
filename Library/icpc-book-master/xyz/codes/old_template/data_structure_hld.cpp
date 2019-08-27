///////////////////////////
//
// Heavy light + segtree
//
///////////////////////////
inline int rand(){static int A=123456789;return A=A*1000000007+1023476;}
const int inf=~0U>>1;
class T {
private:
  struct nd{int v,w,s;nd*c[2];nd(){}nd(int V,nd*n):v(V),w(rand()),s(1){c[0]=c[1]=n;}void rz(){s=c[0]->s+c[1]->s+1;}}*h,*null;
  void rt(nd*&x,bool t){nd*y=x->c[t];x->c[t]=y->c[!t],y->c[!t]=x,x->rz(),y->rz(),x=y;}
  void ins(nd*&x,int y) {
    if(x==null){x=new nd(y,null);return;}
    int t=y>=x->v;ins(x->c[t],y);
    if(x->c[t]->w<x->w)rt(x,t);else x->rz();
  }
  void del(nd*&x,int y) {
    if(x==null)return;
    if(x->v==y) {
      int t=x->c[0]->w>x->c[1]->w;
      if(x->c[t]==null){delete x;x=null;return;}
      rt(x,t),del(x->c[!t],y);
    }else del(x->c[x->v<=y],y);
    x->rz();
  }
  int rnk(nd*x,int y) {
    if(x==null)return 0;
    if(x->v>=y)return rnk(x->c[0],y);
    return x->c[0]->s+1+rnk(x->c[1],y);
  }
  int slt(nd*x,int y) {
    int r=x->c[0]->s;
    if(y==r)return x->v;
    if(y<r)return slt(x->c[0],y);
    return slt(x->c[1],y-r-1);
  }
public:
  T(){null=new nd(0,0);null->s=0,null->w=inf,h=null;}
  void ins(int x){ins(h,x);}
  void del(int x){del(h,x);}
  int rnk(int x){return rnk(h,x);}
  int slt(int x){return h->s<x?inf:slt(h,x-1);}
};
#define N 88888
#define M N*2
#define P 17
#define add(x,y) ++et,ne[et]=he[x],he[x]=et,ad[et]=y
#define tree(x) rt[bl[x]],1,1,le[bl[x]]
#define lc(x) x*2
#define rc(x) x*2+1
int n,w[N],he[N],ne[M],ad[M],fa[N][P],de[N],sz[N],bl[N],po[N],le[N],m;
T *rt[N],tp[N*4],*tr;bool v[N];
void upd(T*f,int x,int l,int r,int a,int p) {
  while(1) {
    if(l==r){f[x].ins(p);return;}
    int mid=(l+r)/2;f[x].ins(p);
    if(a<=mid)r=mid,x=x*2;else l=mid+1,x=x*2+1;
  }
}
void upd(T*f,int x,int l,int r,int a,int p,int q) {
  while(1) {
    if(l==r){f[x].del(p),f[x].ins(q);return;}
    int mid=(l+r)/2;f[x].del(p),f[x].ins(q);
    if(a<=mid)r=mid,x=x*2;else l=mid+1,x=x*2+1;
  }
}
int ask(T*f,int x,int l,int r,int L,int R,int p) {
  if(L<=l&&r<=R)return f[x].rnk(p);
  int mid=(l+r)/2,S=0;
  if(L<=mid)S+=ask(f,x*2,l,mid,L,R,p);
  if(R>mid)S+=ask(f,x*2+1,mid+1,r,L,R,p);
  return S;
}
void fd1(int x) {
  v[x]=1,sz[x]=1;for(int k=1;k<P;k++)fa[x][k]=fa[fa[x][k-1]][k-1];
  for(int i=he[x];i;i=ne[i])
    if(!v[ad[i]])de[ad[i]]=de[x]+1,fa[ad[i]][0]=x,fd1(ad[i]),sz[x]+=sz[ad[i]];
}
void fd2(int x,int l) {
  v[x]=1;int hc=0,hz=0;
  for(int i=he[x];i;i=ne[i])
    if(!v[ad[i]]&&sz[ad[i]]>hz)hz=sz[ad[i]],hc=ad[i];
  if(!hc) {
    int p=x;for(int i=1;i<l;i++)p=fa[p][0];
    rt[p]=tr,tr+=l*4,le[p]=l;
    for(int i=l;i;i--) bl[x]=p,po[x]=i,upd(tree(x),i,w[x]),x=fa[x][0];
    return;
  }
  fd2(hc,l+1);
  for(int i=he[x];i;i=ne[i])
    if(!v[ad[i]])fd2(ad[i],1);
}
void goup(int &x,int l) {
  for(int k=0;k<P;l/=2,k++)if(l&1)x=fa[x][k];
}
int lca(int x,int y) {
  if(de[x]>de[y])swap(x,y);
  goup(y,de[y]-de[x]);
  if(x==y)return x;
  for(int k=P-1;k>=0;k--)
    if(fa[x][k]!=fa[y][k])x=fa[x][k],y=fa[y][k];
  return fa[x][0];
}
#define INF 100000060
int can(int x,int y,int p) {
  int S=0;
  while(1)
    if(bl[x]!=bl[y])S+=ask(tree(y),1,po[y],p),y=fa[bl[y]][0]; else{S+=ask(tree(y),po[x],po[y],p);break;};
  return S;
}
void ask(int x,int y,int p) {
  int l=1,r=INF,z=lca(x,y);
  if(de[x]+de[y]-de[z]*2+1<p){puts("invalid request!");return;}
  p=de[x]+de[y]-de[z]*2+1-p+1;
  while(l<=r) {
    int mid=(l+r)/2;
    if(can(z,x,mid)+can(z,y,mid)-(w[z]<mid)<p)l=mid+1;else r=mid-1;
  }
  printf("%d\n",r);
}
int main() { freopen("network.in","r",stdin),freopen("network.out","w",stdout);
  GN(n);GN(m);for(int i=1,x;i<=n;i++){GN(x);w[i]=x;}
  for(int i=1,et=0,x,y;i<n;i++){GN(x);GN(y);add(x,y),add(y,x);}
  fd1(1),memset(v,0,sizeof v),tr=tp,fd2(1,1);
  while(m--) {
    int x,y,z;GN(x);GN(y);GN(z); if(x==0)upd(tree(y),po[y],w[y],z),w[y]=z;
    else ask(y,z,x);
  }
  return 0;
} 
