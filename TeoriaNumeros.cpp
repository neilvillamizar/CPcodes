typedef long long ll;
typedef pair<ll, ll> pll;
void fillSieve(int p[]) {
	for (ll i=4; i<MAXN; i+=2) p[i]=2;
	for (ll i=3; i*i<MAXN; i+=2) if (!p[i])
		for (ll j=i*i; j<MAXN; j+=2*i) p[j]=i;
}
int fact (int n, int f[], int p[]) {
	int F=0;
	while (p[n]) {
		f[F++]=p[n];
		n/=p[n];
	}
	f[F++]=n;
	return F;
}

// Teroma chino del resto
pll egcd (ll a, ll b) {
	if (b==0) return mp(1, 0);
	pll RES=egcd(b, a%b);
	return mp(RES.second, RES.first-RES.second*(a/b));
}
ll inv (ll n, ll m) {
	pll EDGC = egcd(n, m);
	return ((EDGC.first%m)+m)%m;
}
ll tcr(int k, ll a[], ll n[]) {
	ll i, temp, MOD=1, RES;
	for (i=0; i<k; i++) MOD*=n[i];
	RES=0;
	for (i=0; i<k; i++) {
		temp=MOD/n[i];
		temp*=inv(temp, n[i]);
		RES+=(temp*a[i])%MOD;
	}
	return RES%MOD;
}

int D=0;
void div(int cur, int s, int e, int f[], int d[]) {
	if (cur==0) return;
	if(s==e) d[D++] = cur;
	else {
		int m;
		for(m=s+1; m<e && f[m]==f[s]; m++);
		for (int i=s; i<=m; i++) {
			div(cur, m, e, f, d);
			cur*=f[s];
		}
	}
}


// Factorizacion de Calovetor en 2
ll gcd(ll a, ll b){return a?gcd(b %a, a):b;}
ll mulmod (ll a, ll b, ll c) { //returns (a*b)%c, and minimize overfloor
	ll x = 0, y = a%c;
	while (b > 0){
		if (b % 2 == 1) x = (x+y) % c;
		y = (y*2) % c;
		b /= 2;
	}
	return x % c;
}
ll expmod (ll b, ll e, ll m){//O(log b)
	if(!e) return 1;
	ll q= expmod(b,e/2,m); q=mulmod(q,q,m);
	return e%2? mulmod(b,q,m) : q;
}
bool es_primo_prob (ll n, int a) {
	if (n == a) return true;
	ll s = 0,d = n-1;
	while (d % 2 == 0) s++,d/=2;
	ll x = expmod(a,d,n);
	if ((x == 1) || (x+1 == n)) return true;
	forn (i, s-1){
		x = mulmod(x, x, n);
		if (x == 1) return false;
		if (x+1 == n) return true;
	}
	return false;
}		
bool rabin (ll n){ 
	if (n == 1)	return false;
	const int ar[] = {2,3,5,7,11,13,17,19,23};
	FOR(i, 0, 9) if(!es_primo_prob(n,ar[j]))
			return false;
	return true;
}
ll rho(ll n){
    if( (n & 1) == 0 ) return 2;
    ll x = 2 , y = 2 , d = 1;
    ll c = rand() % n + 1;
    while( d == 1 ){
        x = (mulmod( x , x , n ) + c)%n;
        y = (mulmod( y , y , n ) + c)%n;
        y = (mulmod( y , y , n ) + c)%n;
        if( x - y >= 0 ) d = gcd( x - y , n );
        else d = gcd( y - x , n );
    }
    return d==n? rho(n):d;
}
map<ll,ll> prim; 
void factRho (ll n){ //O (lg n)^3. un solo numero
	if (n == 1) return;
	if (rabin(n)){
		prim[n]++;
		return;
	}
	ll factor = rho(n);
	factRho(factor);
	factRho(n/factor);
}
