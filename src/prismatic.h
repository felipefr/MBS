// Classe de junta Prismatica , herda a classe de Restricoes
class Prismatic: public Constraint
{
	 public:
	 int p1,p2,o; // identificador de pontos
	 double c; // angulo relativo
	 Vetor h; // vetor normal ao movimento no SC local
	 Body *b2; // ponteiro ao corpo 2
	 //construtor
	 Prismatic(int label,Body &bd1,Body &bd2,
				double cc,int pp1,int pp2,int oo);
	 // vetores auxiliares
	 inline Vetor hg() { return b1->A*h; } // h no SC global
	 inline Vetor rij() { return b1->r(p1)-b2->r(p2); }
	 
	 // atualizacoes
	 void C_upd(Vetor& C);
	 void Cq_upd(Matriz& Cq);
	 void Qtt_upd(Vetor& Qtt,const Vetor& w);
	};
				
Prismatic::Prismatic(int label,Body &bd1,Body &bd2,
double cc,int pp1,int pp2,int oo): Constraint(label,bd1)
{		
	b2=&bd2;
	p1=pp1;
	p2=pp2;
	o=oo;
	cc=c;
	h=Vetor(2);
	h=b1->u[p1]-b1->u[o];
	}

void Prismatic::C_upd(Vetor& C) 
{ 
	C[l1]=b1->q[2] - b2->q[2] - c; 
	C[l1+1]= dot(hg(),rij());
	 }

void Prismatic::Cq_upd(Matriz& Cq)
{
	 Cq[l1][b1->l1]=0; Cq[l1][b1->l1+1]=0; Cq[l1][b1->l1+2]=1;
	 Cq[l1][b2->l1]=0; Cq[l1][b2->l1+1]=0; Cq[l1][b2->l1+2]=-1;
	 Cq[l1+1][slice(b1->l1,2,1)]=hg();
	 Cq[l1+1][slice(b2->l1,2,1)]=-hg();
	 Cq[l1+1][b1->l1+2] = dot(b1->Ad*h,rij()) + dot(hg(),b1->Ad*b1->u[p1]);
	 Cq[l1+1][b2->l1+2] = -dot(hg(),b2->Ad*b2->u[p2]);
	}

void Prismatic::Qtt_upd(Vetor& Qtt,const Vetor& w)
{
	double w1=w[b1->l1+2];
	double w2=w[b2->l1+2];
	Vetor vR21=w[slice(b2->l1,2,1)] -  w[slice(b1->l1,2,1)];
	
	Qtt[l1]=0.0;
	
	Qtt[l1+1]=2*w1*dot(b1->Ad*h,vR21+w2*b2->Ad*b2->u[p2])
			 + w1*w1*( dot( hg(),rij()) - dot(h,b1->u[p1]) ) 
			 - w2*w2*dot( hg(),b2->A*b2->u[p2]); 
	 }
