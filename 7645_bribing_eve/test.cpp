#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
const double pi=acos(-1.0);
const double eps=1e-8;
int n,mx=0,mi=0,equ=0;
struct node
{
    int x,y;
}sv[MAXN],zero;
vector<node> svL,svR;
vector<double> L,R;
double getdis(node a,node b)
{
    double ret=sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
    return ret;
}
double angle(double A,double B,double C)
{
    double ret=((A*A)+(B*B)-(C*C))/(2*A*B);
    return pi/2-acos(ret);
}
double get(node a,node b)
{
    double C=getdis(a,zero);
    double B=getdis(b,zero);
    double A=getdis(a,b);
    return angle(A,B,C);
}
int Mx=0,Mi=1e9;
void getans()
{
    int l,r,Lm,Rm;
    int ret=0,k=0;
    double now;
    Lm=L.size(),Rm=R.size();
    l=0,r=0;
    Mx=Rm,Mi=Rm;
    k=Rm;
    while(l<L.size()||r<R.size())
    {
        now=1e9;
        if(l<L.size())
            now=min(L[l],now);
        if(r<R.size())
            now=min(R[r],now);
        while(l<Lm&&now+eps>L[l])
        {
            l++;
            k++;
        }
        Mx=max(Mx,k);
        while(r<Rm&&now+eps>R[r])
        {
            r++;
            k--;
        }
        Mx=max(Mx,k);
    }
    l=0,r=0;
    k=Rm;
    while(l<L.size()||r<R.size())
    {
        now=1e9;
        if(l<L.size())
            now=min(L[l],now);
        if(r<R.size())
            now=min(R[r],now);
        while(r<Rm&&now+eps>R[r])
        {
            r++;
            k--;
        }
        Mi=min(Mi,k);
        while(l<Lm&&now+eps>L[l])
        {
            l++;
            k++;
        }
        Mi=min(Mi,k);
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    zero.x=zero.y=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&sv[i].x,&sv[i].y);
    }
    for(int i=2;i<=n;i++)
    {
        if(sv[i].x>sv[1].x&&sv[i].y>sv[1].y)
        {
            mx++;
        }
        else if(sv[i].x==sv[1].x&&sv[i].y==sv[1].y)
        {
            equ++;
        }
        else if(sv[i].x<=sv[1].x&&sv[i].y>=sv[1].y)
        {
            svL.push_back(sv[i]);
        }
        else if(sv[i].x>=sv[1].x&&sv[i].y<=sv[1].y)
        {
            svR.push_back(sv[i]);
        }
    }
    for(int i=0;i<svR.size();i++)
    {
        double r1=atan2(svR[i].y,svR[i].x);
        double r2=get(sv[1],svR[i]);
        R.push_back(r1+r2);
    }
    for(int i=0;i<svL.size();i++)
    {
        double r1=atan2(svL[i].y,svL[i].x);
        double r2=get(sv[1],svL[i]);
        L.push_back(r1-r2);
    }
    sort(R.begin(),R.end());
    sort(L.begin(),L.end());
    getans();
    printf("%d %d\n",Mi+mx+1,(Mx+mx+equ+1));
    return 0;
}  
