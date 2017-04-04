#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int n,m,i,j,k,l,r,ans,xl,xr,yl,yr;
int st1[100005],top1;
int st2[100005],top2;
int f[505][505],g[505][505];
bool flag1,flag2;

struct node
{
	int x,y;
}t[100005],q[505],a;
inline bool cmp(const node &a,const node &b)
{
	if(a.x!=b.x)return a.x<b.x;
	return a.y<b.y;
}

long long calc(node a,node b,node c,node d){return (long long)(b.x-a.x)*(d.y-c.y)-(long long)(d.x-c.x)*(b.y-a.y);}

bool check1(node a,node b)
{
	if(a.x==b.x)return (xl!=xr||a.x!=xl)&&xr<=a.x;
	int l=1,r=top1-1,mid,aim=0;
	while(l<=r)
	{
		mid=l+r>>1;
		if(calc(t[st1[mid]],t[st1[mid+1]],a,b)>0)aim=mid,l=mid+1;
		else r=mid-1;
	}
	return calc(a,t[st1[aim+1]],a,b)<=0;
}

bool check2(node a,node b)
{
	if(a.x==b.x)return (xl!=xr||a.x!=xl)&&xl>=a.x;
	int l=1,r=top2-1,mid,aim=0;
	while(l<=r)
	{
		mid=l+r>>1;
		if(calc(t[st2[mid]],t[st2[mid+1]],a,b)<0)aim=mid,l=mid+1;
		else r=mid-1;
	}
	return calc(a,t[st2[aim+1]],a,b)>=0;
}

int main()
{
	freopen("lo.in","r",stdin);
	freopen("lo.out","w",stdout);
	scanf("%d%d",&n,&m);
	xl=yl=1000000000;
	xr=yr=-1000000000;
	for(i=1;i<=n;++i)
	{
		scanf("%d%d",&t[i].x,&t[i].y);
		if(t[i].x<xl)xl=t[i].x;
		if(t[i].x>xr)xr=t[i].x;
		if(t[i].y<yl)yl=t[i].y;
		if(t[i].y>yr)yr=t[i].y;
	}
	for(i=1;i<=m;++i)scanf("%d%d",&q[i].x,&q[i].y);
	sort(t+1,t+n+1,cmp);
	sort(q+1,q+m+1,cmp);
	
	k=0;
	for(i=1;i<=n;++i)
	{
		if(i==1||t[i].x!=a.x||t[i].y!=a.y)++k,t[k]=t[i];
		a=t[i];
	}
	n=k;
	
	k=0;
	for(i=1;i<=m;++i)
	{
		if(i==1||q[i].x!=a.x||q[i].y!=a.y)++k,q[k]=q[i];
		a=q[i];
	}
	m=k;
	
	st1[top1=1]=1;
	for(i=2;i<=n;++i)
	{
		for(;top1>1&&calc(t[st1[top1-1]],t[st1[top1]],t[st1[top1-1]],t[i])<=0;--top1);
		st1[++top1]=i;
	}
	
	st2[top2=1]=1;
	for(i=2;i<=n;++i)
	{
		for(;top2>1&&calc(t[st2[top2-1]],t[st2[top2]],t[st2[top2-1]],t[i])>=0;--top2);
		st2[++top2]=i;
	}
	
	ans=10000;
	if(xl==xr)
	{
		flag1=flag2=false;
		for(i=1;i<=m;++i)
		if(q[i].x==xl)
		{
			if(q[i].y<=yl)flag1=true;
			if(q[i].y>=yr)flag2=true;
		}
		if(flag1&&flag2)ans=2;
		
		if(yl==yr)
		{
			for(i=1;i<=m;++i)
			if(q[i].x==xl&&q[i].y==yl)
			ans=1;
		}
	}
	
	for(i=1;i<m;++i)
	for(j=1;i+j<=m;++j)
	{
		l=j;r=i+j;
		if(check1(q[l],q[r]))f[l][r]=2;else f[l][r]=10000000;
		if(check2(q[l],q[r]))g[l][r]=2;else g[l][r]=10000000;
		for(k=l+1;k<r;++k)
		{
			if(f[l][k]+f[k][r]-1<f[l][r])f[l][r]=f[l][k]+f[k][r]-1;
			if(g[l][k]+g[k][r]-1<g[l][r])g[l][r]=g[l][k]+g[k][r]-1;
		}
		if(f[l][r]+g[l][r]-2<ans&&q[l].x<=xl&&q[r].x>=xr)ans=f[l][r]+g[l][r]-2;
	}
	
	if(ans>m)printf("-1\n");
	else printf("%d\n",ans);
}
