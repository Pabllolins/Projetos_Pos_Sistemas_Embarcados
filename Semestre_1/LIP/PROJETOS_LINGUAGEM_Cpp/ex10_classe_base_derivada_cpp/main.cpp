#include <iostream>
#include <stdlib.h>
using namespace std; 

class Uart {
	/* 
		Por padrão, as variáveis e funções são privadas nas classes. 
		Somente a classe e as funções da classe derivada podem acessar os membros privados
	*/
	private: 
	   /* ... */ 
	
	/* 
		somente a classe Uart e as funções da classe filha (a que herdou esta classe pai) 
		é quem podem acessar os membros protected; 
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
			é chamado o construtor de classe da classe base 'Uart';
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

