#include <valarray>
#include <ctime>
#include <algorithm>
#include <cassert>

using namespace std;

//Definicao da estrutura do Vetor
typedef valarray<double> Vetor;
//Definicao da estrutura da Matriz
typedef valarray< valarray <double> > Matriz;

unsigned int nn,mm,l,c; // Var. auxiliares


void print(const Vetor& v) // escreve vetor
{ 
	register unsigned int i;
	cout << "[ " ;
	
    for (i = 0; i<v.size(); i++)  cout << v[i] << " " ;
  
	cout << "] \n" ;

	}

void print(const Matriz& m) // escreve matriz
{
	cout << endl;
    register unsigned int i;
    for (i = 0; i<m.size(); i++) print(m[i]);

	}

Vetor getrow(const Matriz& M,int i) //extrai linha da matriz
{
	return M[i];
}

Vetor getcol(const Matriz& M,int j) //extrai coluna da matriz
{
	Vetor vt(M.size());
	register unsigned int i;
	for(i=0;i<M.size();i++) vt[i]=M[i][j];
	
	return vt;
}
	
Matriz Mrand(int n,int m) // Matriz Randomica
{
	srand(time(NULL));
	Matriz M(Vetor(m),n);
	
	register unsigned int i;
	register unsigned int j;
	for(i=0;i<M.size();i++) 
		for(j=0;j<M[0].size();j++) 
			M[i][j]=rand()%10;
	
	return M;
}

double dot(const Vetor& v,const Vetor& w) // prod. Interno
{
	return (v*w).sum();
	}

Matriz T(const Matriz& M) // Matriz Transposta
{
	mm=M[0].size();
	Matriz At( Vetor(M.size()) , mm);
	register unsigned int i;
	
	for(i=0;i<mm;i++) At[i]=getcol(M,i);
	
	return At;	
}

Vetor operator*(const double c,const Vetor& v) // c*Vec(v)
{	
	nn=v.size();
	Vetor vt(nn);
	register unsigned int i;
	for(i = 0; i<nn ; i++) vt[i]=c*v[i];
	
	return vt;
	}

Matriz operator*(const double c,const Matriz& M) // c*Mat(M)
{	
	nn=M.size();
	Matriz At(M[0],M.size());
	register unsigned int i;
	for(i = 0; i<nn; i++) At[i]=c*M[i];
	
	return At;
	}

Vetor operator*(const Matriz& M,const Vetor& v) // Mat(M)*Vec(v)
{	
	if(v.size()!=M.size()) assert("erro de dimensao matriz-vetor");
	
	nn=v.size();
	Vetor vt(nn);
	
	register unsigned int i;
	for(i = 0; i<nn; i++) vt[i]=dot(M[i],v);
	
	return vt;
	}

Matriz operator*(const Matriz& M,const Matriz& MM) //Mat(M)*Mec(MM)
{	
	if(M[0].size()!=MM.size()) assert("erro de dimensao matrizes");
	
	l=M.size();
	c=MM[0].size();
	
	Matriz At(Vetor(c),l); // c , l
	
	register unsigned int i;
	register unsigned int j;
	for(i = 0; i<l; i++) 
		for(j = 0; j<c; j++)
			At[i][j]=dot(M[i],getcol(MM,j));
			
	return At;
	}
	
void solve(const Matriz &A,const Vetor& b,Vetor& x) // elim. Gauss
{	
	Matriz At=Matriz(A);
	x=Vetor(b);
	int n = x.size();
	register int i,j,k,p=0;
	double m;
	double max;
	int imax;
		
	for(i=0;i<n-1;i++)
	{
	// ordenacao (pivoteamento)
		max=abs(At[i][i]);
		imax=i;
		for(p=i+1;p<n;p++) 
			if(abs(At[p][i])>max) {imax=p; max=abs(At[p][i]);}
		
		if(imax!=i)
		{
			for(p=i;p<n;p++) swap(At[i][p],At[imax][p]);
			swap(x[i],x[imax]);
			}		
		
		//eliminacao propriamente dita
		for(j=i+1;j<n;j++)
		{	
			m=-At[j][i]/At[i][i];
			for(k=i+1;k<n;k++) At[j][k]+= m*At[i][k]; 
			x[j]+=m*x[i];
			}
		}

		//retrosubstituicao
	for(i=n-1;i>-1;i--)
	{
		m=0;
		for(j=i+1;j<n;j++) m+= x[j]*At[i][j];
		x[i]=(x[i]-m)/At[i][i];
	}
	
	
}

void inv(const Matriz& A,Matriz& Ainv) // calcula inversa
{
	Matriz At=Matriz(A);
	nn=Ainv.size();
	Vetor vt(nn);
	register unsigned int i,j;
	
	for(i=0; i<nn ; i++)
	{
		vt[i]=1; // vetor elementar
		solve(At,vt,vt);
		At=A;
		for(j=0; j<nn ; j++) {Ainv[j][i]=vt[j]; vt[j]=0;}
	}
	
}
