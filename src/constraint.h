// Classe de interface (abstrata) de Restricoes
class Constraint
{
	public:
	int l1; // identificador 
	Body *b1; // ponteiro ao corpo 1
	//Construtor
	Constraint(int label, Body& bd);
    // funcoes virtuais de atualizacoes
    virtual void C_upd(Vetor& C) {}
    virtual void C_upd(Vetor& C,const Vetor& w) {}
    virtual void C_upd(Vetor& C,const double& t) {}
    virtual void Cq_upd(Matriz& Cq) {}
	virtual void Qt_upd(Vetor& Qt) {}
	virtual void Qt_upd(Vetor& Qt,const double& t) {}
	virtual void Qtt_upd(Vetor& Qtt) {}
	virtual void Qtt_upd(Vetor& Qtt,const Vetor& w) {}
	virtual void Qtt_upd(Vetor& Qtt,const double& t) {}
	
	};
	
 Constraint::Constraint(int label, Body& bd)
 {
	 l1=label;
	 b1=&bd;
	}
