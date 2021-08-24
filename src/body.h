#define grav 9.80665

// Classe que define os Corpos
class Body
{
	 public:
	 Vetor q; // vetor de coord generalizada
	 Matriz u; // pontos auxiliares (cada linha)
	 Matriz A , Ad; // rotacao e derivada 
	 unsigned int l1; // identificador
	 double m,J; // inercias
	 double (*f0)(double),(*f1)(double),(*f2)(double); //forcas ext.
	 
	 //Construtor
	 Body(int label,int np,double mm,double JJ,
	 double (*)(double),double (*)(double),double (*)(double));
	 Body(const Body& bd);
	 
	 // vetores auxiliares
	 inline Vetor R()  {return q[slice(0,2,1)];}
	 inline Vetor r(int p) { return R() + A*u[p] ; }
	 
	 // atualizacoes
	 void A_utd();
	 void q_utd(Vetor& Q) { Q[slice(l1,3,1)]=q; }
	 void q_utdi(const Vetor& qg) { q=Vetor(3); q_inc(qg); }
	 void q_inc(const Vetor& dq) {q += dq[slice(l1,3,1)] ; A_utd();} 	 	 
	 void Minv_utd(Matriz &M) 
	 {M[l1][l1]=M[l1+1][l1+1]=1/m; M[l1+2][l1+2]=1/J;}
	 void Qe_utd(Vetor& Qe,double t);
	};

Body::Body(int label,int np,double mm,double JJ,
double (*pf0)(double),double (*pf1)(double),double (*pf2)(double))
{		
	l1 = 3*label;
	q = Vetor(3);
	A = Matriz(Vetor(2),2);
	Ad = Matriz(Vetor(2),2);
	A_utd();
	u=Matriz(Vetor(2),np);
	m=mm; J=JJ;
	f0=pf0; f1=pf1; f2=pf2;
	}

Body::Body(const Body& bd)
{		
	l1 = bd.l1;
	q = bd.q;
	u= bd.u;
	A = Matriz(Vetor(2),2);
	Ad = Matriz(Vetor(2),2);
	A_utd();
	m=bd.m; J=bd.J;
	f0=bd.f0; f1=bd.f1; f2=bd.f2;
	}
	
void Body::A_utd()
{
	A[0][0]=A[1][1]=Ad[1][0]=cos(q[2]);
	Ad[0][1]=-A[0][0];
	A[1][0]=sin(q[2]);
	A[0][1]=Ad[0][0]=Ad[1][1]=-A[1][0];
	}
	 
void Body::Qe_utd(Vetor& Qe,double t)
{
		Qe[l1]=f0(t);
		Qe[l1+1]=f1(t)-m*grav;
		Qe[l1+2]=f2(t);
	}
