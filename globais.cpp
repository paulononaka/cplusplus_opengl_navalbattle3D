#ifndef _GLOBAIS_CPP
#define	_GLOBAIS_CPP

/**
 * Define todas as variaveis globais
 */

#include "constantes.cpp"
#include "ceumar.cpp"
#include "canhao.cpp"
#include "navio.cpp"
#include "cruzador.cpp"
#include "destroier.cpp"
#include "submarino.cpp"
#include "portaAviao.cpp"

Submarino gsubmarino;   // Objeto submarino
PortaAviao gportaaviao; // Objeto porta aviao
Destroier gdestroier;   // Objeto destroier
Cruzador gcruzador;     // Objeto cruzado
Navio gnavio;           // Objeto navio
Ceumar gceumar;         // Objeto para o ceu e o mar

double gdesliza_tela_horizontal = 0;    // soma ao gluOrtho no eixo X quando aperta H e K
double gdesliza_tela_vertical = 0;      // soma ao gluOrtho no eixo Y quando aperta U e J
int gPressionandoTeclaTiro = 0;         // booleana para saber se esta apertando a tecla T
int visao = 1;                          // para alternar entre visao pespectiva e ortografica
int opmenu[5] = {0,0,0,0,0};            // vetor para armazenar opcoes do menu

GLint idMina;                           // lista de mina
GLint idCanhao;                         // lista do canhao

#endif /* _GLOBAIS_CPP */
