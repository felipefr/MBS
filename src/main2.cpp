#include <iostream>
#include "mbs.h" // classe multicorpo


// Definicoes das funcoes nas forcas e nos movimentos prescritos
double nula(double t) {return 0;}
double torque(double t) { return (t<2.5? 100 : 0); }

using namespace std;

int main ()
{	
	// criacao do multicorpo
	MBS mb(4,11); // D
	
	// ================= CORPOS ====================
	//adiciona um corpo (chao)
	mb.b.push_back(Body(0,1,1,1,nula,nula,nula));
	mb.b.back().u[0][0]=0.0; mb.b.back().u[0][1]=0.0; // ponto O
	
	//adciona um corpo (manivela)
	mb.b.push_back(Body(1,2,1,1,nula,nula,torque)); // D
	mb.b.back().u[0][0]=-0.05; mb.b.back().u[0][1]=0.0; // ponto O
 	mb.b.back().u[1][0]=0.05; mb.b.back().u[1][1]=0.0; // ponto A
	
	//adiciona um corpo (biela)
	mb.b.push_back(Body(2,2,1,1,nula,nula,nula));
	mb.b.back().u[0][0]=-0.075; mb.b.back().u[0][1]=0.0; // ponto A
	mb.b.back().u[1][0]=0.075; mb.b.back().u[1][1]=0.0; // ponto B 
	
	//adiciona um corpo (cursor)
	mb.b.push_back(Body(3,2,1,1,nula,nula,nula)); 
	mb.b.back().u[0][0]=0.0; mb.b.back().u[0][1]=0.0; // ponto B
	mb.b.back().u[1][0]=0.0; mb.b.back().u[1][1]=1.0; // ponto Q (norm)

	// ================= RESTRICOES ====================
	mb.cg.push_back(Ground(0,mb.b[0],0.0,0.0,0.0)); // fixacao
	
	mb.cr.push_back(Revolute(3,mb.b[0],mb.b[1],0,0)); // rotula em O
	mb.cr.push_back(Revolute(5,mb.b[1],mb.b[2],1,0)); // rotula em A
	mb.cr.push_back(Revolute(7,mb.b[2],mb.b[3],1,0)); // rotula em B
	
	// Primatica cursor-camisa
	mb.cp.push_back(Prismatic(9,mb.b[3],mb.b[0],0.0,0,0,1)); 
	
    // Estimativas inicial q0 e qt0
	Vetor q0(12);
	Vetor qt0(12); 
	q0[3]=4.3302e-02; 
	q0[4]=2.4999e-02;
	q0[5]=5.2358e-01;
	q0[6]=1.5731e-01;
	q0[7]=2.4999e-02;
	q0[8]=-3.3983e-01;
	q0[9]=2.2803e-01;
	
	double Tmax=4.0; // tempo de simulacao
	int N=500; // subdivisoes 
	double dt=Tmax/double(N); // passo de tempo

	//inicia simulacoes
	mb.simulDyn(Tmax,dt,q0,qt0); // D

    return 0;
}

