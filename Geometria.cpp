
struct Point{
	double x, y;
	Point(double _x=0, double _y=0){x=_x; y=_y;}
	double operator *(Point p){return x*p.y-y*p.x;}
	double operator ^(Point p){return x*p.x+y*p.y;}
	Point operator  +(Point p){return Point(x+p.x, y+p.y);}
	Point operator  -(Point p){return Point(x-p.x, y-p.y);}
	Point operator  *(double a){return Point(x*a, y*a);}
	Point operator  /(double a){return Point(x/a, y/a);}
};
double norma(Point p){return sqrt(p^p);}
double dist2(Point p, Point q){return (p-q)^(p-q);}
Point RA90(Point p){return Point(-p.y, p.x);}
Point RH90(Point p){return Point(p.y, -p.x);}
Point Rotar(Point p, double t){return Point(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t));}
Point proyeccionSegmento(Point a, Point b, Point c){
	double r=dist2(a, b);
	if(abs(r)<EPS) return a;
	r=((c-a)^(b-a))/r;
	if(r<0) return a;
	if(r>1) return b;
	return a+(b-a)*r;
}
double distPointSegmento(Point a, Point b, Point c){
	return norma(c-proyeccionSegmento(a, b, c));
}
bool paralelas(Point a, Point b, Point c, Point d){
	return abs((b-a)*(d-c))<EPS;
}
bool colineales(Point a, Point b, Point c, Point d){
	return paralelas(a, b, c, d) &&
	       abs((a-b)*(a-c))<EPS && abs((c-d)*(c-a))<EPS;
}
bool interSegmentos(Point a, Point b, Point c, Point d){
		if(colineales(a, b, c, d)){
			if( dist2(a, c)<EPS || dist2(a, d)<EPS ||
			    dist2(b, c)<EPS || dist2(b, d)<EPS) return true;
			if(((c-a)^(c-b))>0 && ((d-a)^(d-b))>0 && ((c-b)^(d-b))>0) return false;
			return true;
		}
		return ((d-a)*(b-a))*((c-a)*(b-a))<=0 &&
		       ((a-c)*(d-c))*((b-c)*(d-c))<=0;
}
double distSegmentos(Point a, Point b, Point c, Point d){
	if(interSegmentos(a, b, c, d)) return 0;
	double D=distPointSegmento(a, b, c);
	D=min(D, distPointSegmento(a, b, d));
	D=min(D, distPointSegmento(c, d, a));
	D=min(D, distPointSegmento(c, d, b));
	return D;	
}
Point interseccionLineas(Point a, Point b, Point c, Point d){
	b=b-a; d=c-d; c=c-a;
	return a+b*(c*d)/(b*d);
}
Point proyeccionLineas(Point a, Point b, Point c){
	b=b-a; c=c-a;
	return a+ b*(c^b)/(b^b);
}

//---------------------------------------------------------------------//
//Coordenadas enteras

struct Punto{
	ll x, y; int index;
	Punto (ll _x=0, ll _y=0, int _index=0){x=_x; y=_y; index=_index;}
	bool operator==(Punto p)const{return x==p.x && y==p.y;}
	bool operator<(const Punto p)const{return y<p.y || (y==p.y && x<p.x);}
	bool operator <=(const Punto p)const{return y<p.y || (y==p.y && x<=p.x);}
	Punto operator+(Punto p)const{return Punto(x+p.x, y+p.y);}
	Punto operator-(Punto p)const{return Punto(x-p.x, y-p.y);}
};
ll operator *(Punto p1, Punto p2){return p1.x*p2.y-p2.x*p1.y;}
ll operator ^(Punto p1, Punto p2){return p1.x*p2.x+p1.y*p2.y;}
double norma(Punto p){return sqrt(p.x*p.x+p.y*p.y);}
ll norma2(Punto p){return p.x*p.x+p.y*p.y;}
vector<Punto> convex_hull(vector<Punto> P){
	int n=P.size(), k=0;
	sort(P.begin(), P.end());
	vector<Punto>H(2*n);
	for(int i=0; i<n; i++){
		while (k>=2 && (P[i]-H[k-1])*(H[k-2]-H[k-1])<0) --k;
		H[k++]=P[i];
	}
	for(int i=n-2, t=k+1; i>=0; i--){
		while (k>=t && (P[i]-H[k-1])*(H[k-2]-H[k-1])<0) --k;
		H[k++]=P[i];
	}
	H.resize(k);
	return H;
}
Punto Pmin;
bool comp (Punto p1, Punto p2){
	if(p2==Pmin) return false;
	if(p1==Pmin) return true;
	ll pr=(p1-Pmin)*(p2-Pmin);
	return pr>0 || (pr==0 && norma2(p1-Pmin)<norma2(p2-Pmin));
}
vector<Punto> convex_hull2(vector<Punto> P){
	int n=P.size()+1, k=0;
	sort(P.begin(), P.end(), comp);
	P.pb(Pmin);
	vector<Punto>H(n);
	for(int i=0; i<n; i++){
		while (k>=2 && (P[i]-H[k-1])*(H[k-2]-H[k-1])<=0) k--;
		H[k++]=P[i];
	}
	H.resize(k);
	return H;
}

bool intersectan(Punto p1, Punto p2, Punto p3, Punto p4) {
	if ( (p2-p1)*(p3-p1)==0 && (p2-p1)*(p4-p1)==0){
		if( p1==p3 || p1==p4 || p2==p3 || p2==p4) return true;
		if(((p3-p1)^(p3-p2))>0 && ((p4-p1)^(p4-p2))>0 && ((p3-p2)^(p4-p2))>0) return false;
		return true;
	}
	return ((p2-p1)*(p3-p1))*((p2-p1)*(p4-p1))<=0 &&
	       ((p4-p3)*(p1-p3))*((p4-p3)*(p2-p3))<=0;
}

double ang(double a, double b, double c){
	double x;
	x = (a*a + b*b - c*c) / (2 * a * b);
	x = max(min(x, 1.0), -1.0);
	return acos(x);
}
pair<Point, Point> interCir(Point O1, double r1, Point O2, double r2){
	if(r2 < EPS) while(true);
	double d = norma(O2 - O1);
	Point v = (O2 - O1)/d;
	double a = ang(r1, d, r2);
	Point X = rotar(v, a), Y = rotar(v, -a);
	X = X*r1 + O1;
	Y = Y*r1 + O1;
	return {X, Y};
}


//checks if v is inside of P, using ray casting
//works with convex and concave.
//excludes boundaries, handle it separately using segment.inside()
bool inPolygon(pto v, vector<pto>& P) {
	bool c = false;
	forn(i, sz(P)){
		int j=(i+1)%sz(P);
		if((P[j].y>v.y) != (P[i].y > v.y) &&
	(v.x < (P[i].x - P[j].x) * (v.y-P[j].y) / (P[i].y - P[j].y) + P[j].x))
			c = !c;
	}
	return c;
}



