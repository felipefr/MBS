#include <iostream>
#include "mbs.h" // classe multicorpo

#define PI 3.1415
#define K 3.29
#define Theta0 PI/4
#define omegaMax 50.0


// Definicoes das funcoes nas forcas e nos movimentos prescritos
double g(double t) { return  Theta0 + omegaMax*t - (omegaMax/K)*(1-exp(-K*t));  } 
double gt(double t) { return omegaMax*(1-exp(-K*t)); }
double gtt(double t) { return omegaMax*K*exp(-K*t); }
double nula(double t) {return 0;}
double torque(double t) { return 100; }

using namespace std;

int main ()
{	
	// criacao do multicorpo
	//~ MBS mb(4,12); //K
	MBS mb(4,11); // D
	
	// ================= CORPOS ====================
	//adiciona um corpo (chao)
	mb.b.push_back(Body(0,1,1.0,1.0,nula,nula,nula));
	mb.b.back().u[0][0]=0.0; mb.b.back().u[0][1]=0.0; // ponto O
	
	//adciona um corpo (manivela)
	//~ mb.b.push_back(Body(1,2,0.25,200e-6,nula,nula,nula)); // K
	mb.b.push_back(Body(1,2,1.0,1.0,nula,nula,torque)); // D
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
	//~ mb.ct.push_back(PrescribedMotion(11,mb.b[1],2,g,gt,gtt)); // K 
    
    // Estimativas inicial q0 e qt0
	Vetor q0(12);
	Vetor qt0(12); 
	q0[3]=3.5356e-02; 
	q0[4]=3.5355e-02;
	q0[5]=7.8538e-01;
	q0[6]=1.3686e-01;
	q0[7]=3.5355e-02;
	q0[8]=-4.9087e-01;
	q0[9]=2.0300e-01;
	
	double Tmax=1.0; // tempo de simulacao
	int N=500; // subdivisoes 
	double dt=Tmax/double(N); // passo de tempo

	//inicia simulacoes
	//~ mb.simulKin(Tmax,dt,q0); //K
	mb.simulDyn(Tmax,dt,q0,qt0); // D

    return 0;
}

