#include <iostream>
#include "mbs.h" // classe multicorpo

#define PI 3.1415
#define K 3
#define Theta0 PI/6
#define omegaMax 60.0

// Definicoes das funcoes nas forcas e nos movimentos prescritos
double g(double t) { return  Theta0 + omegaMax*t - (omegaMax/K)*(1-exp(-K*t));  } 
double gt(double t) { return omegaMax*(1-exp(-K*t)); }
double gtt(double t) { return omegaMax*K*exp(-K*t); }
double nula(double t) {return 0;}

using namespace std;

int main ()
{	
	// criacao do multicorpo
	MBS mb(4,12); //K
	
	// ================= CORPOS ====================
	//adiciona um corpo (chao)
	mb.b.push_back(Body(0,1,1.0,1.0,nula,nula,nula));
	mb.b.back().u[0][0]=0.0; mb.b.back().u[0][1]=0.0; // ponto O
	
	//adciona um corpo (manivela)
	mb.b.push_back(Body(1,2,0.25,200e-6,nula,nula,nula)); // K
	mb.b.back().u[0][0]=-0.05; mb.b.back().u[0][1]=0.0; // ponto O
 	mb.b.back().u[1][0]=0.05; mb.b.back().u[1][1]=0.0; // ponto A
	
	//adiciona um corpo (biela)
	mb.b.push_back(Body(2,2,0.35,650e-6,nula,nula,nula));
	mb.b.back().u[0][0]=-0.075; mb.b.back().u[0][1]=0.0; // ponto A
	mb.b.back().u[1][0]=0.075; mb.b.back().u[1][1]=0.0; // ponto B 
	
	//adiciona um corpo (cursor)
	mb.b.push_back(Body(3,2,0.55,150e-6,nula,nula,nula)); 
	mb.b.back().u[0][0]=0.0; mb.b.back().u[0][1]=0.0; // ponto B
	mb.b.back().u[1][0]=0.0; mb.b.back().u[1][1]=1.0; // ponto Q (norm)

	// ================= RESTRICOES ====================
	mb.cg.push_back(Ground(0,mb.b[0],0.0,0.0,0.0)); // fixacao
	
	mb.cr.push_back(Revolute(3,mb.b[0],mb.b[1],0,0)); // rotula em O
	mb.cr.push_back(Revolute(5,mb.b[1],mb.b[2],1,0)); // rotula em A
	mb.cr.push_back(Revolute(7,mb.b[2],mb.b[3],1,0)); // rotula em B
	
	// Primatica cursor-camisa
	mb.cp.push_back(Prismatic(9,mb.b[3],mb.b[0],0.0,0,0,1)); 
	
	// Movimento prescrito da manivela 
	mb.ct.push_back(PrescribedMotion(11,mb.b[1],2,g,gt,gtt)); // K 
    
    // Estimativas inicial q0 e qt0
	Vetor q0(12);
	Vetor qt0(12); 
	
	double Tmax=1.4; // tempo de simulacao
	int N=1000; // subdivisoes 
	double dt=Tmax/double(N); // passo de tempo

	//inicia simulacoes
 	mb.simulKin(Tmax,dt,q0); //K
	
    return 0;
}

