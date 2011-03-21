/*
 * Classe Veiculo
 * 
 * Classe da qual todos os barcos herdam
 * incluido o navio do jogador.
 * 
 */

#ifndef _VEICULO_CPP
#define	_VEICULO_CPP

#define DISTANCIA_MAXIMA 30

#include <GL/gl.h>
#include <pthread.h>
#include <stdlib.h>

extern void imprimeVariavel(const char* nome, double valor, int id);
extern void escreveMaior(const char* texto, int posX, int posY, int posZ);
extern double calcRaio(double xa, double za, double xb, double zb);
extern int gPressionandoTeclaTiro;
extern int opmenu[5];

class Veiculo {
public:
    int cod;
    GLint id;
    double sangue; // life do jogador
    double velocidade;
    double direcao;
    double x, y, z;
    double raio,diametro;
    int qtdOrigem;
    double  o1, o2, o3, o4, o5;
    
    Veiculo() {
        sangue = 0;
        velocidade = 0;
        direcao = 0;
        x = 0;
        y = 0;
        z = 0;
    }

    // metodos para calcular a origem do veiculo
    double calculaOrigemX(double xOr, double dist){
        return xOr + dist * cos(direcao*PI/180);
    }

    double calculaOrigemZ(double zOr, double dist){
        return zOr + dist * (-1* sin(direcao*PI/180));
    }

    // metodos para desenhar os raios do veiculo
    void desenhaRaios(){
        if (opmenu[1] == 1) {
            int comp;
            int inicia;
            int inc;
            double dist;
            if (qtdOrigem % 2 != 0) {
                comp = qtdOrigem / 2;
                inicia = 0;
                inc = 1;
                dist = diametro;
            } else {
                comp = qtdOrigem;
                inicia = 1;
                inc = 2;
                dist = raio;
            }
            for (int i = inicia; i <= comp; i+=inc) {
                glPushMatrix();
                    glColor3f(1, 0, 0);
                    glTranslatef(calculaOrigemX(x,i * dist), y+50, calculaOrigemZ(z,i * dist));
                    glutSolidSphere(raio,10,10);
                glPopMatrix();
                glPushMatrix();
                    glColor3f(1, 0, 0);
                    glTranslatef(calculaOrigemX(x,-i * dist), y+50, calculaOrigemZ(z,-i * dist));
                    glutSolidSphere(raio,10,10);
                glPopMatrix();
            }
        }
    }

    // metodo que verifica se um veiculo colidiu com outro veiculo
    // verifica se o raio do navio irá invadir a area onde está o raio de outro navio
    int calculaColisao(double xCol,double zCol, double raioCol){


        if(qtdOrigem % 2 != 0){
            int comp = qtdOrigem/2;
            
            
            for(int i = 0;i <= comp ;i++){
                if (calcRaio(xCol,zCol,calculaOrigemX(x,i*diametro),calculaOrigemZ(z,i*diametro))  <= raio + raioCol){
                    return 1;
                } else if (calcRaio(xCol,zCol,calculaOrigemX(x,-i*diametro),calculaOrigemZ(z,-i*diametro))  <= raio + raioCol){
                    return 1;
                }
            }
        }else{
            int comp = qtdOrigem/2;
            
            int ind = 1;
            for(int i = 1;i <= comp;i= i++){
                 if (calcRaio(xCol,zCol,calculaOrigemX(x,ind*raio),calculaOrigemZ(z,ind*raio))  <= raio + raioCol){
                    return 1;
                } else if (calcRaio(xCol,zCol,calculaOrigemX(x,-ind*raio),calculaOrigemZ(z,-ind*raio))  <= raioCol){
                    return 1;
                }
                 ind = ind+2;
            }
        }
        return 0;
    }

    void calculaXZ(){
        x += velocidade * cos(direcao*PI/180);
        z += -1 * velocidade * sin(direcao*PI/180);
    }
};

#endif	/* _VEICULO_CPP */
