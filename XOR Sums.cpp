#include <iostream>
using namespace std;
const int MAXN = 3e5 + 10, MOD = 998244353, g = 3;
int wu1[MAXN], wu2[MAXN];
int rev[MAXN];
int fac[MAXN], ifac[MAXN], pw2[MAXN];
int n, m, d, half;
int fpw(int x, int t){
	if(!t) return 1;
	int o = fpw(x, t >> 1);
	o = 1ll * o * o % MOD;
	if(t & 1) o = 1ll * o * x % MOD;
	return o;
}
void getrev(int L){
	d = 1;
	while(d < L)
		d <<= 1;
	half = (d >> 1);
	for(int i = 1; i < d; ++ i)
		rev[i] = ((rev[i >> 1] >> 1) | (i & 1 ? half : 0));
}
void ntt_core(int *a, int *wu){
	for(int i = 0 ; i < d ; ++ i)
		if(rev[i] > i)
			swap(a[i] , a[rev[i]]);
	for(int i = 1 ; i < d ; i <<= 1)
		for(int j = 0 ; j < d ; j += (i << 1))
			for(int k = 0; k < i ; k ++){
				int a1 = a[j + k], a2 = 1ll * a[j + k + i] * wu[i + k] % MOD;
				a[j + k] = (a1 + a2) % MOD;
				a[j + k + i] = (a1 + MOD - a2) % MOD;
			}}
void intt(int *a, int *wu){
	ntt_core(a, wu);
	int c = fpw(d , MOD - 2);
	for(int i = 0 ; i < d ; ++ i)
		a[i] = 1ll * a[i] * c % MOD;
}
void ntt(int *a, int *wu){ntt_core(a, wu);}
void init(){
	getrev(n + 1);
	int c = fpw(g , (MOD - 1) / d);
	wu1[half] = 1;
	for(int i = half + 1 ; i < d ; ++ i)
		wu1[i] = 1ll * wu1[i - 1] * c % MOD;
	for(int i = half - 1 ; i ; -- i)
		wu1[i] = wu1[i << 1];
	c = fpw(c, MOD - 2);
	wu2[half] = 1;
	for(int i = half + 1 ; i < d ; ++ i)
		wu2[i] = 1ll * wu2[i - 1] * c % MOD;
	for(int i = half - 1 ; i ; -- i)
		wu2[i] = wu2[i << 1];
	fac[0] = 1;
	for(int i = 1 ; i <= n ; ++ i)
		fac[i] = 1ll * fac[i - 1] * i % MOD;
	ifac[0] = ifac[1] = 1;
	for(int i = 2 ; i <= n ; ++ i)
		ifac[i] = MOD - 1ll * (MOD / i) * ifac[MOD % i] % MOD;
	for(int i = 2 ; i <= n ; ++ i)
		ifac[i] = 1ll * ifac[i - 1] * ifac[i] % MOD;
	pw2[0] = 1;
	for(int i = 1 ; i <= 30 ; ++ i)
		pw2[i] = 1ll * pw2[i - 1] * 2 % MOD;}
int C(int x , int y){
	if(x < y || y < 0) return 0;
	return 1ll * fac[x] * ifac[y] % MOD * ifac[x - y] % MOD;
}
int v[MAXN];
int a[MAXN] , b[MAXN], c[MAXN];
int ans[MAXN];
int main(){
	scanf("%d", &n);
//	n = 200000;
	init();
	for(int i = 1 ; i <= n ; ++ i)
		scanf("%d", &v[i]);
	for(int i = 0 ; i < 30 ; ++ i){
		int tot = 0;
		for(int j = 1 ; j <= n ; ++ j)
			tot += ((v[j] >> i) & 1);
		for(int j = 0 ; j < d ; ++ j)
			a[j] = (j & 1 ? C(tot , j) : 0);
		for(int j = 0 ; j < d ; ++ j)
			b[j] = C(n - tot, j);
		ntt(a, wu1); ntt(b, wu1);
		for(int j = 0 ; j < d ; ++ j)
			c[j] = 1ll * a[j] * b[j] % MOD;
		intt(c, wu2);
		for(int j = 0 ; j <= n ; ++ j)
			ans[j] = (ans[j] + 1ll * pw2[i] * c[j]) % MOD;
	}
	for(int j = 1 ; j <= n ; ++ j)
		ans[j] = (ans[j] + ans[j - 1]) % MOD;
	int Q;
	scanf("%d", &Q);
	for(int i = 1 ; i <= Q; ++ i){
//		int x = i;
		int x;
		scanf("%d", &x);
		printf("%d\n", ans[x]);
	}
//	printf("finish\n");
	return 0;
}
