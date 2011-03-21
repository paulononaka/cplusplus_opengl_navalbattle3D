#ifndef _CONSTANTES_CPP
#define	_CONSTANTES_CPP

/**
 * Define todas as contantes globais
 */

#define PI 3.14159265   // Valor de PI
#define DELTA 100       // Tempo para glutTimerFunc
#define LIMITE_MAR 1000 // Limite dos barcos no mar da origem até esse valor em X e Z
#define TAM 500         // Tamanho maximo para o glOrtho
#define ESCR (LIMITE_MAR - LIMITE_MAR/100) // posicao para escrever as coordenadas
#define GRAVIDADE 9.80665   // Valor da gravidade
#define CODNAVIO 1      // Codigo para identificar que quem chama o metodo e' o navio
#define CODSUBMARINO 2  // Codigo para identificar que quem chama o metodo e' o submarino
#define CODCRUZADOR 3   // Codigo para identificar que quem chama o metodo e' o cruzador
#define CODPORTAAVIAO 4 // Codigo para identificar que quem chama o metodo e' o porta avioes
#define CODDESTROIER 5  // Codigo para identificar que quem chama o metodo e' o destroier

#endif /* _CONSTANTES_CPP */