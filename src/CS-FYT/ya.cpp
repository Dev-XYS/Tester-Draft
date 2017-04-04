#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10000005
#define M 3005
using namespace std;
typedef long long ll;
const int mod = 1e9+7;
inline int read(){
	int sum = 0, t = 1; char ch = getchar();
	while(ch < '0' || ch > '9'){ if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9'){ sum = sum * 10 + ch - '0'; ch = getchar(); }
	return sum * t;
}

ll quick_mod(ll x, ll y){
	ll res = 1; x %= mod;
	for(; y ; y >>= 1, (x *= x) %= mod)
		if(y & 1) (res *= x) %= mod;
	return res;
}

int n, m;
int b[M], p[M], a[M];
ll fac[N], ifac[N], f[N];
bool fuck[M];

void pre(){
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	ifac[n] = quick_mod(fac[n], mod - 2);
	for(int i = n; i ; i--) ifac[i - 1] = ifac[i] * i % mod;
	f[0] = 1; f[1] = 1; f[2] = 2;
	for(int i = 3; i <= n; i++)
		f[i] = (f[i - 1] + f[i - 2] * (i - 1) % mod) % mod;
}

ll C(int x, int y){ return x < y ? 0 : fac[x] * ifac[y] % mod * ifac[x - y] % mod; }

int main(){
	freopen("ya.in", "r", stdin);
	freopen("ya.out", "w", stdout);
	n = read(), m = read();
	pre();
	for(int i = 1; i <= m; i++) p[b[i] = read()] = i;
	ll ans = 0;
	for(int i = max(0, 2 * m - n); i <= m; i++){
		memset(fuck, 0, sizeof(fuck));
		for(int j = i + 1; j <= m; j++) fuck[b[j]] = true;
		int t = 1;
		for(int j = 1; j <= m; j++) if(!fuck[j])
			a[j] = b[t++];
		bool flag = true;
		for(int j = 1; j <= m && flag; j++) if(!fuck[j])
			flag &= (!fuck[a[j]] && a[a[j]] == j);
		if(flag) (ans += C(n - m, m - i) * f[n - 2 * m + i] % mod) %= mod;
	}
	printf("%lld\n", ans);
}

