/* O presente trabalho realiza o cálculo da área sob a curva de uma função inserida pelo usuário utilizando o método dos trapézios da integração numérica, que consiste em tomar sucessivos trapézios sob a curva da função, calcular a área de cada um e ao final somar todas as áreas. 

Autores: Angel Gabriel Arieta, Marcos Vinícius Pivetta e Vinícius Franceschi

Comandos Linux para rodar:
sudo apt-get install libmatheval-dev (instalar biblioteca)
gcc metodoTrapezio.c -o exe -lmatheval (compilar)
./exe (executar)

*/

// bibliotecas utilizadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <matheval.h> // para permitir a inserção das funções pelo usuário
#include <assert.h>

#define BUFF_SIZE 50 // tamanho do buffer para guardar função inserida pelo usuário

double xa, xb; // valores de x que vão sendo atualizados como as bases do trapézio (xa é o valor da função à esquerda e xb o valor da direita)
double A = 0; // responsável por acumular a área que está sendo calculada 
int n; // número de trapézios que serão utilizados para a aproximação da área
char buffer[BUFF_SIZE]; // declaração do buffer
void *f; // função f após o tratamento

void imprime_cabecalho() {
	printf("\n============================================================\n");
	printf("====================MÉTODO DOS TRAPÉZIOS====================\n");
	printf("============================================================\n");
}

// recebe os parâmetros necessários para efetuar a integral
void coleta() {
	int length;
	printf("\n----------------------Digite a função----------------------|\n");
	fgets(buffer,BUFF_SIZE,stdin); // coloca função no buffer (representação textual)
	__fpurge(stdin); // limpa o buffer
	length = strlen(buffer);
	if(length > 0 && buffer[length-1] == '\n') {
		buffer[length-1] = '\0'; // insere o terminador de string no buffer
	}
	// passa a representar a função matematicamente
	f = evaluator_create(buffer); 
	if(f != NULL) {
		assert (f); 
	}
	printf("============================================================\n");
	printf("-----------------Digite o limite inferior------------------|\n");
	scanf("%lf",&xa);
	printf("-----------------Digite o limite superior------------------|\n");
	scanf("%lf",&xb);
	printf("-------------Digite a quantidade de trapézios--------------|\n");
	scanf("%d",&n);	
	printf("============================================================\n");		
}


int calcula() {
	int i; 
	double h = (xb - xa)/n; // h é a altura do trapézio ou largura do subintervalo (em x), sendo o (limite superior - limite inferior) / número de trapézios
	for(i=0; i<n; i++) {
		xb = xa + h; // xb é atualizado com o valor de xa + h a cada incremento
		A += (xb - xa) * (evaluator_evaluate_x(f, xa) + evaluator_evaluate_x(f, xb)) / 2; // área é calculada tomando ==> (h * (base menor + base maior)) / 2; 
		xa = xb; // xa é atualizado com o valor de xb após calcular a área 
	}
	printf("\nÁREA SOB A FUNÇÃO: %lf \n",A);
}

void main() {
	system("clear");
	imprime_cabecalho();
	int confirma = 1;
	// coleta e calcula até o usuário sair
	while (confirma != 0) {		
		coleta();
		calcula();
		printf("\nDeseja fazer outra área? (1 para sim e 0 para não) \n");
		scanf("%d",&confirma);
		__fpurge(stdin);
		system("clear");
		imprime_cabecalho();
		xa = 0; xb = 0; A = 0;
	}
	printf("Obrigado por utilizar nosso algoritmo de integração pelo método do trapézio! \n");
}
