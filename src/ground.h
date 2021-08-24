// Classe de fixacao, herda a classe de Restricoes
class Ground: public Constraint
{
	public:
	Vetor c; // posicao relativa do corpo fixo ao SC global
	// construtor
	Ground(int label,Body &bd, double c1, double c2, double c3);
	// atualizacoes
	void C_upd(Vetor& C) { C[slice(l1,3,1)]=b1->q-c; }
	void Cq_upd(Matriz& Cq) 
	{Cq[l1][l1]=1.0; Cq[l1+1][l1+1]=1.0; Cq[l1+2][l1+2]=1.0;}
	};

Ground::Ground(int label,Body &bd, 
double c1, double c2, double c3): Constraint(label,bd)
{		
	c=Vetor(3);
	c[0]=c1; c[1]=c2; c[2]=c3;
	}
