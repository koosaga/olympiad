///////////////////////////
//
// Splay  7k+
//
///////////////////////////
#define INF 1000000007
#define N 555555
class Splay
{
private:
  struct nd
  {
    int s,v,a,la,ra,sz;bool sm,rv;nd*c[2],*p;
    nd(){}
    nd(int _v,nd*n=0)
    {
      s=v=a=la=ra=_v,sz=1,
      sm=rv=0,c[0]=c[1]=p=n;
    }
    void upd1(int z){sm=1,v=z,s=v*sz;if(v<0)a=la=ra=v;else a=la=ra=s;}
    void upd2(){rv^=1,swap(c[0],c[1]),swap(la,ra);}
    void U()
    {
      s=c[0]->s+c[1]->s+v,sz=c[0]->sz+c[1]->sz+1,
      la=max(c[0]->la,c[0]->s+v+max(c[1]->la,0)),
      ra=max(c[1]->ra,c[1]->s+v+max(c[0]->ra,0)),
      a=max(max(c[0]->ra,0)+v+max(c[1]->la,0),max(c[0]->a,c[1]->a));
    }
    void D()
    {
      if(sm)c[0]->upd1(v),c[1]->upd1(v),sm=0;
      if(rv)c[0]->upd2(),c[1]->upd2(),rv=0;
    }
    bool t(){return p->c[1]==this;}
    void sc(nd*x,bool t){x->p=this,c[t]=x;}
  }*h,*u;
  void rt(nd*x)
  {
    nd*y=x->p;bool t=x->t();
    y->D(),x->D();
    y->p->sc(x,y->t()),y->sc(x->c[!t],t),x->sc(y,!t);
    y->U();if(y==h)h=x;
  }
  void spl(nd*x,nd*y)
  {
    x->D();
    while(x->p!=y)
      if(x->p->p==y)rt(x);
      else (x->t()==x->p->t())?(rt(x->p),rt(x)):(rt(x),rt(x));
    x->U();
  }
  nd* slt(int x)
  {
    nd*p=h;
    while(1)
    {
      p->D();
      int r=p->c[0]->sz;
      if(r==x)return p;
      p=p->c[x>r];
      if(x>r)x-=r+1;
    }
  }
  nd* get(int x,int y)
  {
    spl(slt(x),u),spl(slt(y),h);
    return h->c[1]->c[0];
  }
  void del(nd*x)
  {
    if(x==u)return;
    del(x->c[0]),del(x->c[1]);
    delete x;
  }
public:
  Splay()
  {
    u=new nd(-INF),u->sz=u->s=0,h=new nd(-INF,u);
    nd*r=new nd(-INF,u);h->sc(r,1),spl(r,u);
  }
  void ins(int x,int l,int*a)
  {
    get(x,x+1);
    nd*p=new nd(a[0],u);
    h->c[1]->sc(p,0);
    for(int i=1;i<l;i++)
    {
      nd*r=new nd(a[i],u);
      p->sc(r,1),p=r;
    }
    spl(p,u);
  }
  void del(int x,int y)
  {
    del(get(x-1,y+1));
    h->c[1]->sc(u,0),spl(h->c[1],u);
  }
  void upd1(int x,int y,int z)
  {
    nd*p=get(x-1,y+1);
    p->upd1(z),spl(p,u);
  }
  void upd2(int x,int y)
  {
    nd*p=get(x-1,y+1);
    p->upd2(),spl(p,u);
  }
  int ask1(int x,int y){return get(x-1,y+1)->s;}
  int ask2(){return h->a;}
}*T;
int a[N],n,m;
int main()
{
  GN(n);GN(m);
  for(int i=0,x;i<n;i++){GN(x);a[i]=x;}
  T=new Splay();T->ins(0,n,a);
  for(int __=1;__<=m;__++)
  {
    char c;int x,y,z;GC(c);GC(c);GC(c);
    if(c=='S'){GN(x);GN(n);for(int i=0;i<n;i++){GN(y);a[i]=y;}T->ins(x,n,a);}else
    if(c=='L'){GN(x);GN(y);T->del(x,x+y-1);}else
    if(c=='K'){GN(x);GN(y);GN(z);T->upd1(x,x+y-1,z);}else
    if(c=='V'){GN(x);GN(y);T->upd2(x,x+y-1);}else
    if(c=='T'){GN(x);GN(y);printf("%d\n",T->ask1(x,x+y-1));}else
    if(c=='X'){while(CHA(INP))GET(INP);printf("%d\n",T->ask2());}
  }
  return 0;
}
