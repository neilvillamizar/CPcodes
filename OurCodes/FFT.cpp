//MAXN tiene que ser potencia de 2!!!

const double dos_pi=4.0*acos(0.0);
struct cpx{
	double real, i;
	cpx(double _real, double _i):real(_real), i(_i){real=_real; i=_i;}
	cpx(double _real=0):real(_real){i=0;}
	cpx operator +(cpx z){return cpx(real+z.real, i+z.i);}
	cpx operator -(cpx z){return cpx(real-z.real, i-z.i);}
	cpx operator *(cpx z){return cpx(real*z.real-i*z.i, real*z.i+i*z.real);}
};
void FFT(cpx *y, int n, int rev) {
	for (int i=1, j, k, t; i<n; ++i) {
		for (j=0, k=n>>1, t=i; k; k>>=1, t>>=1) {
			j = j<<1 | t & 1;
		}
		if (i<j) swap(y[i], y[j]);
	}
	for (int s=2, ds=1; s<=n; ds=s, s<<=1) {
		cpx wn(cos(rev*dos_pi/s), sin(rev*dos_pi/s));
		for (int k=0; k<n; k+=s) {
			cpx w(1, 0), t;
			for (int i=k; i<k+ds; ++i, w=w*wn) {
				y[i+ds] = y[i] - (t=w*y[i+ds]);
				y[i] = y[i] + t;
			}
		}
	}	
}
// Multiplicar polinomios p, q y guardar resultado en r
void multiply(cpx *p, cpx *q, cpx *r){
	FFT(p, MAXN, 1);
	FFT(q, MAXN, 1);
	FOR(i, 0, MAXN) r[i] = p[i]*q[i];
	FFT(r, MAXN, -1);
	FOR(i, 0, MAXN) r[i].real /= MAXN;
}