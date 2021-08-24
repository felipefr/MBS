// Classe de junta Movimento Prescrito , herda a classe de Restricoes
class PrescribedMotion: public Constraint
{
	public:
	//funcoes de posicao, velocidade, aceleracao prescrita
	double (*f)(double),(*ft)(double),(*ftt)(double); 
	int i; // coord. controlada
	//Construtor
	PrescribedMotion(int label,Body &bd1,int ii,
	double (*)(double),double (*)(double),double (*)(double));
	// Atualizacoes
	void C_upd(Vetor& C,const double& t) { C[l1]=b1->q[i] - f(t); } 
	void Cq_upd(Matriz& Cq) { Cq[l1][b1->l1+i]=1; }
	void Qt_upd(Vetor& Qt,const double& t) {  Qt[l1]=ft(t);}
	void Qtt_upd(Vetor& Qtt,const double& t) {  Qtt[l1]=ftt(t);}
	};

PrescribedMotion::PrescribedMotion(int label,Body &bd1,int ii,
double (*pf)(double),double (*pft)(double),double (*pftt)(double))
:Constraint(label,bd1)
{	
	i=ii;	
	f=pf;
	ft=pft;
	ftt=pftt;
	}
