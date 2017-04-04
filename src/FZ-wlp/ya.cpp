#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
using namespace std;
#define ll long long
#define P 1000000007
int n,m,i,j,ans,a[3005],b[3005],c[3005],f[10000005],I[10000005];
int main()
{
	freopen("ya.in","r",stdin);
	freopen("ya.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(I[1]=1,i=2;i<=n;i++)I[i]=(ll)(P-P/i)*I[P%i]%P;
	for(i=2,f[0]=f[1]=1;i<=n;i++)f[i]=(ll)(f[i-1]+f[i-2])*I[i]%P;
	for(I[0]=i=1;i<=m;i++)I[i]=(ll)I[i-1]*I[i]%P;
	if(m<<1<=n)ans=(ll)f[n-(m<<1)]*I[m]%P;
	for(i=1;i<=m;i++)
	{
		scanf("%d",a+i);
		for(j=c[b[i]=a[i]]=i;j&&b[j]<b[j-1];j--)b[j]^=b[j-1]^=b[j]^=b[j-1];
		for(j=1;j<=i;j++)if(b[c[b[j]]]!=a[j])break;
		if(j>i&&m<<1<=n+i)ans=(ans+(ll)f[n+i-(m<<1)]*I[m-i])%P;
	}
	for(i=1;i+m<=n;i++)ans=(ll)ans*i%P;
	cout<<ans<<endl;
	return 0;
}

