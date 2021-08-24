#include <cmath>
#include <vector>
#include <fstream>
#include "matriz.h"
#include "body.h"
#include "constraint.h"
#include "revolute.h"
#include "prismatic.h"
#include "ground.h"
#include "motion.h"


// Classe que define o sistema multicorpo
class MBS
{
	 public:
	 // n-> num coord, nb-> num corpos, nc-> num restricoes 
	 int n,nb,nc;
	 //var. auxiliares:
	 int itmax,k;
	 double err,tol,t;
	 //listas de corpos e restricoes
	 vector<Body> b;
	 vector<Revolute> cr;
	 vector<Prismatic> cp;
	 vector<Ground> cg;
	 vector<PrescribedMotion> ct;
	 
	 //Vetores e Matrizes globais
	 Vetor C,Qt,Qtt,q,qt,qtt;
	 Matriz Cq,Minv;
	 Vetor Qe,Lm,Qc;
	 Matriz Hll,Hqq,Hql; //Matrizes auxiliares
	 
	 
	 //arquivos de saida
	 ofstream q_out,qt_out,qtt_out;
	 ofstream Qe_out,Lm_out,Qc_out;
	 
	 MBS(int nnb,int nnc); // Construtor
	 void defineInit(); // inicia as matrizes fixas
	 // Atualizacoes de vetores/matrizes
	 void q_utd(); // local para o global 
	 void q_utdi(); // global para o local
	 void q_inc(Vetor& dq); // incrementa q
	 void C_utd(); 
	 void Cq_utd(); 
	 void Qt_utd(); 
	 void Qtt_utd();
	 void Qe_utd();
	 
	 // cinematica
	 void calculKin(); 
	 void simulKin(double tf,double dt,Vetor &q0);

	 // dinamica
	 void calculDyn();
	 void simulDyn(double tf,double dt,Vetor &q0,Vetor &qt0);
	 
	 // Arquivos
	 void closeFiles();
	 void q_write();
	 void Q_write();

	};

// ======== Implementacao das funcoes ===================
MBS::MBS(int nnb,int nnc)
{		
		nb=nnb;
		n=3*nb;
		nc=nnc;
		
		C=Vetor(nc);
		Cq=Matriz(Vetor(n),nc); // nc x n 
		Qtt=Vetor(nc);
		Qt=Vetor(nc);
		q=Vetor(n);
		qt=Vetor(n);
		qtt=Vetor(n);
		Qe=Vetor(n);
		Lm=Vetor(nc);
		Qc=Vetor(n);
		Minv=Matriz(Vetor(n),n);
		
		Hll=Matriz(Vetor(nc),nc);
		Hqq=Matriz(Vetor(n),n);
		Hql=Matriz(Vetor(nc),n); // n x nc
	
	// parametros numericos
	tol=0.001;
	itmax=10;
	
	q_out.open ("q_out.txt"); 	
	qt_out.open ("qt_out.txt"); 
	qtt_out.open ("qtt_out.txt"); 
	Qe_out.open ("Qe_out.txt"); 	
	Lm_out.open ("Lm_out.txt"); 
	Qc_out.open ("Qc_out.txt"); 
	
	q_out.setf(ios::scientific,ios::floatfield); q_out.precision(4);
	qt_out.setf(ios::scientific,ios::floatfield); qt_out.precision(4);
	qtt_out.setf(ios::scientific,ios::floatfield); qtt_out.precision(4);
	Qe_out.setf(ios::scientific,ios::floatfield); Qe_out.precision(4);
	Lm_out.setf(ios::scientific,ios::floatfield); Lm_out.precision(4);
	Qc_out.setf(ios::scientific,ios::floatfield); Qc_out.precision(4);
	
	}

void MBS::defineInit()
{
	register unsigned int i;
	for(i=0;i<cg.size();i++)
	{
		cg[i].C_upd(C);
		cg[i].Cq_upd(Cq);
		cg[i].Qt_upd(Qt);
		cg[i].Qtt_upd(Qtt);
		}
	
	for(i=0;i<b.size();i++) b[i].Minv_utd(Minv);
	}

void MBS::q_utd()
{
	register unsigned int i=0;
	for(i=0;i<b.size();i++) b[i].q_utd(q);		
	}

void MBS::q_utdi()
{
	register unsigned int i;
	for(i=0;i<b.size();i++) b[i].q_utdi(q);
	}
	
void MBS::q_inc(Vetor& dq)
{
	register unsigned int i=0;
	for(i=0;i<b.size();i++) b[i].q_inc(dq);
	}

void MBS::C_utd()
{
	register unsigned int i=0;
	for(i=0;i<cr.size();i++) cr[i].C_upd(C);
	for(i=0;i<cp.size();i++) cp[i].C_upd(C);
	for(i=0;i<ct.size();i++) ct[i].C_upd(C,t); 
	}

void MBS::Cq_utd()
{
	register unsigned int i=0;
	for(i=0;i<cr.size();i++) cr[i].Cq_upd(Cq);
	for(i=0;i<cp.size();i++) cp[i].Cq_upd(Cq);
	for(i=0;i<ct.size();i++) ct[i].Cq_upd(Cq);
	for(i=0;i<cg.size();i++) cg[i].Cq_upd(Cq);
	}

void MBS::Qt_utd()
{
	register unsigned int i=0;
	for(i=0;i<ct.size();i++) ct[i].Qt_upd(Qt,t);
	}
	
void MBS::Qtt_utd()
{
	register unsigned int i=0;
	for(i=0;i<cr.size();i++) cr[i].Qtt_upd(Qtt,qt);
	for(i=0;i<cp.size();i++) cp[i].Qtt_upd(Qtt,qt);
	for(i=0;i<ct.size();i++) ct[i].Qtt_upd(Qtt,t);
	}
	
void MBS::Qe_utd()
{
	register unsigned int i;
	for(i=0;i<b.size();i++) b[i].Qe_utd(Qe,t);
	}

void MBS::calculKin()
{	
	k=0;
	err=10;
	//comeca Newton-Raphson
	while(err>tol && k<itmax)
	{	
		C_utd(); Cq_utd();
		
		solve(Cq,-C,q);
		
		q_inc(q);

		err=q.max();
		k++;
		}
	
	//atualiza as matrizes e calcula qt, depois qtt
	C_utd(); Cq_utd(); Qt_utd();
	
	solve(Cq,Qt,qt);
	
	Qtt_utd();
	
	solve(Cq,Qtt,qtt);
	
	q_utd(); //atualiza q para chute em outro passo
	}


void MBS::simulKin(double tf,double dt,Vetor &q0)
{
	q_inc(q0);
	defineInit();
	
	for(t=0;t<tf;t+=dt)
	{
		calculKin();
		
		q_write();
			
		}
		
	cerr << "simulacao Cinematica terminada com sucesso" << endl;
	closeFiles();	
	system("python plotKin.py"); // script python de plot 
	}
	
void MBS::calculDyn()
{
	Cq_utd();
	Qe_utd();
	Qtt_utd();
	inv( Cq*Minv*T(Cq) , Hll);
	Hqq=Minv + Minv*T(Cq)*Hll*Cq*Minv;	
	Hql=(-1)*Minv*T(Cq)*Hll;
	
	qtt=Hqq*Qe + Hql*Qtt;
	Lm=T(Hql)*Qe + Hll*Qtt;
	Qc=(-1)*T(Cq)*Lm;
	}

void MBS::simulDyn(double tf,double dt,Vetor &q0,Vetor &qt0)
{
		q=q0;
		q_utdi();
		qt=qt0;
		defineInit();
			
		for(t=0;t<tf;t+=dt)
		{
			
			calculDyn();
			qt+= dt*qtt;
			q+= dt*qt;
			q_utdi();
			
			q_write();
			Q_write();
			
			}
	
	cerr << "simulacao Dinamica terminada com sucesso" << endl;
	closeFiles();	
	
	// scripts python de plot
	system("python plotDyn.py"); 
	system("python plotKin.py"); 	
	}

void MBS::closeFiles()
{
q_out.close(); qt_out.close(); qtt_out.close();	
Qe_out.close(); Lm_out.close(); Qc_out.close();
	}

void MBS::q_write()
{
	register unsigned int i;
		
	q_out << t ; qt_out << t ; qtt_out << t ;
			
	for (i = 0; i<n; i++)  
	{
		q_out << " " << q[i] ; qt_out << " " << qt[i] ; 
		qtt_out << " " << qtt[i] ;
		}
	
	q_out << "\n" ; qt_out << "\n" ; qtt_out << "\n" ;
	}


void MBS::Q_write()
{
	register unsigned int i;
		
	Qe_out << t ; Lm_out << t ; Qc_out << t ;
			
	for (i = 0; i<n; i++)  
	{
		Qe_out << " " << Qe[i] ; Qc_out << " " << Qc[i] ; 
		}
	
	for (i = 0; i<nc; i++)  
	{
		Lm_out << " " << Lm[i] ;  
		}
	
	Qe_out << "\n" ; Lm_out << "\n" ; Qc_out << "\n" ;
	}
