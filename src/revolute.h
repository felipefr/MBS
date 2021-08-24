// Classe de junta Rotula , herda a classe de Restricoes
class Revolute: public Constraint
{
	 public:
	 int p1,p2; // identificador de pontos
	 Body *b2; // ponteiro ao corpo 2
	 // construtor
	 Revolute(int label,Body &bd1,Body &bd2,int pp1,int pp2);
	 // Atualizacoes
	 void C_upd(Vetor& C) { C[slice(l1,2,1)]=b1->r(p1) - b2->r(p2); }
	 void Cq_upd(Matriz& Cq);
	 void Qtt_upd(Vetor& Qtt,const Vetor& w);
	};
				
Revolute::Revolute(int label,Body &bd1,Body &bd2,int pp1,int pp2):
 Constraint(label,bd1)
{		
	b2=&bd2;
	p1=pp1;
	p2=pp2;
	}
	
void Revolute::Cq_upd(Matriz& Cq)
{
	 Cq[l1][b1->l1]=1; Cq[l1+1][b1->l1+1]=1;
	 Cq[l1][b2->l1]=-1; Cq[l1+1][b2->l1+1]=-1;
	 
	 Vetor temp=b1->Ad*b1->u[p1];
	 Cq[l1][b1->l1+2]=temp[0]; Cq[l1+1][b1->l1+2]=temp[1];
	 
	 temp=b2->Ad*b2->u[p2];
	 Cq[l1][b2->l1+2]=-temp[0]; Cq[l1+1][b2->l1+2]=-temp[1];
	 }

void Revolute::Qtt_upd(Vetor& Qtt,const Vetor& w)
{
	double w1=w[b1->l1+2];
	double w2=w[b2->l1+2];
	Qtt[slice(l1,2,1)]=(w1*w1)*(b1->A*b1->u[p1]) - (w2*w2)*(b2->A*b2->u[p2]);
	 }
