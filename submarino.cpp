/*
 * Classe submarino
 * Um dos barcos.
 * permanece a maior parte do tempo submerso e deposita minas
 * nao possui um canhao
 */

#ifndef _SUBMARINO_H
#define	_SUBMARINO_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <list>
#include "constantes.cpp"
#include "oponente.cpp"
#include "veiculo.cpp"
#include "mina.cpp"

#define MAX_TEMPO_MINA 100  // Intervalo de tempo para o submarino colocar minas
#define SUB_DISTANCIA_MAXIMA 30 // distancia maxima que o sub pode percorrer em uma direcao.
#define SUB_TEMPO_ABAIXO 100// tempo para ficar abaixo dagua sem oxigenio.
#define SUB_TEMPO_ACIMA 30 // tempo para ficar acima dagua pegando oxigenio.

#define SUB_EMBAIXO 0 // embaixo da agua.
#define SUB_SUBINDO 1 // subindo.
#define SUB_DESCENDO 2 // descendo.
#define SUB_EMCIMA 3 // em cima da agua.

#define TAM_SUB 40 // comprimento
#define TAM_SUB1 80
#define QTDE_RAIO_SUBMARINO 2 // numero de raios
#define LARGURA_SUB (TAM_SUB/QTDE_RAIO_SUBMARINO) // largura
#define LARGURA_SUB1 (TAM_SUB1/QTDE_RAIO_SUBMARINO)
#define RAIOMINA 5

extern void imprimeVariavel(const char* nome, double valor, int id);

class Submarino: public Oponente { // herda de oponente
public:
    int tempo; // guarda o tempo que o submarino permanece submerso e na superficie
    int estado;
    int tempoMina;
    std::list <Mina*> listaMinas; // lista de minas que o submarino deposita
    std::list <Mina*>::const_iterator itMina;
    Mina m;

    GLint idConves;
    GLint idPonte;
    GLint idChamine;
    GLint idFundo;
    GLint idCasco;

    GLint idCorpo;
    GLint idFrente;
    GLint idTraseira;
    GLint idCabine;
    GLint idColetores;

    Submarino():m(0,0,0,0) {
        inicializa();
    }

    void inicializa() {
        sangue = 1;
        velocidade = 3; // velocidade do sub.
        direcao = 0;
        estado = SUB_EMBAIXO;
        tempo = 0;
        //variacao = 1;
        distancia = SUB_DISTANCIA_MAXIMA + 1;
        y = -100;
        cod = CODSUBMARINO;
        diametro = LARGURA_SUB1;
        raio = LARGURA_SUB1/2;
        qtdOrigem = QTDE_RAIO_SUBMARINO;
        tempoMina = 0;
        x = TAM/2; // posicao no mapa
        z = -TAM/2;
        listaMinas.clear(); // inicializa com 0 minas depositadas
    }

    // modelagem hierarquica
    void criaListas(){
        id = glGenLists(1);
        idConves = glGenLists(1);
        idPonte = glGenLists(1);
        idChamine = glGenLists(1);
        idFundo = glGenLists(1);
        idCasco = glGenLists(1);

        idCorpo = glGenLists(1);
        idFrente = glGenLists(1);
        idTraseira = glGenLists(1);
        idCabine = glGenLists(1);
        idColetores = glGenLists(1);

        glNewList(id,GL_COMPILE);           //  Submarino
            glPushMatrix();
            glTranslatef(TAM_SUB/2,0,0);
            glCallList(idCorpo);
            glCallList(idFrente);
            glCallList(idTraseira);
            glCallList(idCabine);
            glCallList(idColetores);
            glPopMatrix();
        glEndList();                          // fim sub

        // ----------------------------------------------------------------------------------------------

        glNewList(idCorpo, GL_COMPILE);
            glPushMatrix();
            glColor3f(0.1,0.3,0.1);
            glRotatef(-90,0,1,0);
            gluCylinder(gluNewQuadric(), LARGURA_SUB, LARGURA_SUB, TAM_SUB, 10, 10);
            glPopMatrix();
        glEndList();

        glNewList(idFrente, GL_COMPILE);
            glPushMatrix();
            glColor3f(0.1,0.3,0.1);
            glTranslatef(0,0,0);
            glutSolidSphere(LARGURA_SUB,10,10);
            glPopMatrix();
        glEndList();

        glNewList(idTraseira, GL_COMPILE);
            glPushMatrix();
            glColor3f(0.1,0.3,0.1);
            glTranslatef(-40,0,0);
            glutSolidSphere(LARGURA_SUB,10,10);
            glPopMatrix();
        glEndList();

        glNewList(idCabine, GL_COMPILE);
            glPushMatrix();
            glColor3f(0.1,0.3,0.1);
            glTranslatef(-20,15,0);
            glutSolidCube(LARGURA_SUB);
            glPopMatrix();
        glEndList();

        glNewList(idColetores, GL_COMPILE);
            glPushMatrix();
            glColor3f(1,1,1);
            glRotatef(90,90,0,0);
            glTranslatef(-23,0,-30);
            gluCylinder(gluNewQuadric(), 2, 2, 10, 10, 10);
            glTranslatef(7,0,-10);
            gluCylinder(gluNewQuadric(), 2, 2, 30, 10, 10);
            glPopMatrix();
        glEndList();
    }

    void desenha(){
        glPushMatrix();
            glTranslatef(x, y, z);
            glRotatef(direcao,0,1,0);
//            imprimeVariavel("Submarino x",x,5);
//            imprimeVariavel("Submarino y",y,6);
//            imprimeVariavel("Submarino z",z,7);
            glCallList(id);
        glPopMatrix();
        if (opmenu[2]) {
            for (itMina = listaMinas.begin(); itMina != listaMinas.end(); itMina++) {
                    m = **itMina;
                    m.desenha();
            }
        }
        desenhaRaios();
    }

    void anima(){
        if(tempoMina <= MAX_TEMPO_MINA){
            tempoMina++;
        }else{
            if(estado == 0){ // submerso
                //Mina m(0, gsubmarino.x, /*gsubmarino.y*/ 0, gsubmarino.z);
                listaMinas.push_front(new Mina(0, x, /*gsubmarino.y*/ 0, z));
            }
            tempoMina = 0;
        }
        Oponente::anima();
        
        /*
        * Este switch verifica em qual estado esta o movimento do submarino
        * A cada intervalo de tempo o submarino pode subir a superfice e
        * descer de volta ao fundo do mar. existe um tempo para que ele
        * permaneça em cada uma dessas regioes.
        */        
        switch(estado){
            case SUB_EMBAIXO:
                if(tempo <= SUB_TEMPO_ABAIXO){
                    tempo += 1;
                }else{
                    tempo = 0;
                    estado = SUB_SUBINDO;
                }
                break;
            case SUB_EMCIMA:
                if(tempo <= SUB_TEMPO_ACIMA){
                    tempo += 1;
                }else{
                    tempo = 0;
                    estado = SUB_DESCENDO;
                }
                break;
            case SUB_SUBINDO:
                if(y <= 20){ // posicao quando esta na superficie
                    y++;
                }else{
                    estado = SUB_EMCIMA;
                }
                break;
            case SUB_DESCENDO:
                if(y >= -100){ // posicao no fundo do mar
                    y--;
                }else{
                    estado = SUB_EMBAIXO;
                }
                break;
            default:
                break;
        }
    }

};

#endif
