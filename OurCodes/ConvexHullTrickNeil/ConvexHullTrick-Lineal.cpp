
/* Complejidad O(n)

	precondicion: recursion de la forma dpi=min(j)(dpj+mj*xi),  pendientes y abscisas ordenadas.

*/

//recta: m pendiente, b interseccion con eje y.
struct line
{
	ll m,b;
};

vector<line> v;
int ptr=1;

//retorna la coordenada x de la interseccion de dos rectas.
double inters(line l1, line l2){
	return 1.0*(l2.b-l1.b)/(l1.m-l2.m);
}

//inserta una recta en el Hull.
//Se deben agregar las rectas en orden decreciente (Upper Hull) o creciente (Lower Hull) de m.
void add(line l){
	int n = v.size();

	while(n>=2 && inters(v[n-2],v[n-1]) >= inters(v[n-1,l])){
		v.pop_back();
		n--;
	}

	v.pb(l);
}

//devuelve Y maximo (o minimo) para alguna recta Y = m*x+b, para un x dado.
// las querys se deben realizar en orden creciente de x. (codigo para orden decreciente es analogo).
ll query(ll x){
	int n = v.size();

	ptr = min(ptr,n-2);

	while(ptr<=n-2	&& inters(v[ptr],v[ptr+1])<x) ptr++;

	return v[ptr].m*x + v[ptr].b;
}