#include <iostream>
#include <stdlib.h>
using namespace std; 

class Uart {
	/* 
		Por padr�o, as vari�veis e fun��es s�o privadas nas classes. 
		Somente a classe e as fun��es da classe derivada podem acessar os membros privados
	*/
	private: 
	   /* ... */ 
	
	/* 
		somente a classe Uart e as fun��es da classe filha (a que herdou esta classe pai) 
		� quem podem acessar os membros protected; 
	*/   
	protected: 
		/* ... */
	
	public:
		/* construtor da classe base Uart*/
		Uart(void) {
			cout << "Classe base" << endl; 
		}
			 
};
class Serial: public Uart {
	
	public:			
		/* 
			Construtor; 
			Antes de inicializar o construtor da classe derivada 'Serial, 
			� chamado o construtor de classe da classe base 'Uart';
		 */
		Serial (): Uart () { 
			cout << "Classe derivada" << endl; 
		}
		
};

int main(int argc, char** argv) {
	
	/* Cria o objeto 'serial' */
	Serial serial;

	return 0;
}

