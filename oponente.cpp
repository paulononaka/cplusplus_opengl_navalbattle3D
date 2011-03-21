/*
 * File:   oponente.cpp
 *
 * Classe oponente. Herda funcionalidade da classe veiculo.  Contem especializacoes
 * que são responsáveis por funcinalidades de movimento randomico, colisao com
 * outros veiculos e tiro automatico
 * 
 */

#ifndef _OPONENTE_CPP
#define	_OPONENTE_CPP

#include "veiculo.cpp"
#include "pthread.h"

// Classe que retorna se houve colisao com alguma embarcação presente no mar
extern int colisaoNavios(int id, double xCol, double zCol, double raioCol );
class Oponente: public Veiculo {
public:
    int distancia;      //Distancia dos limites do mar
    int mudar;          //Atributo que define a direcao randomica a ser tomada pelo oponente
    double limite_tela; //Define qual sera o limite da tela a percorrer
    int flagDirecao;    //Flag utilizado para alternar a direcao em colisoes
    double h;
    Oponente() {
        srand(time(0));
        x = rand() % ((TAM-10)*2)+1 - TAM;
        z = rand() % ((TAM-10)*2)+1 - TAM;
        limite_tela = LIMITE_MAR-100;
        flagDirecao =1;
    }

    int consultaColisao(){

        if(qtdOrigem % 2 != 0){
            int comp = qtdOrigem/2;

            for(int i = 0;i <= comp ;i++){

      //          printf("i: %d  calcraio: %f \n ", i, calcRaio(xCol,zCol,calculaOrigemX(i*diametro),calculaOrigemZ(i*diametro) ) );
                if (colisaoNavios(cod,calculaOrigemX(x,i*diametro),calculaOrigemZ(z,i*diametro),raio) != 0){
                    return 1;
                }else if (colisaoNavios(cod,calculaOrigemX(x,-i*diametro),calculaOrigemZ(z,-i*diametro),raio) != 0){
                    return 1;
                }

            }
        }else{
            int comp = qtdOrigem/2;
            //double r = raio;
            int ind = 1;
            for(int i = 1;i <= comp;i= i++){
                if(colisaoNavios(cod,calculaOrigemX(x,ind*raio),calculaOrigemZ(z,ind*raio),raio) != 0){
                    return 1;
                } else if  (colisaoNavios(cod,calculaOrigemX(x,-ind*raio),calculaOrigemZ(z,-ind*raio),raio) != 0){
                    return 1;
                }
                 ind = ind+2;
            }
        }
        return 0;

    }

    // Classe que define o movimento randomico dos oponentes, utilizando variacões
    // na direcao de navagação dos mesmos.
    void movimenta(){
        if(distancia >=  DISTANCIA_MAXIMA){
            srand(time(0));
            mudar = rand() % 3; // escolhe aleatoriamente uma nova direcao
            distancia = 0; // reinicia a distancia percorrida na direcao atual
        }
        switch(mudar){
            case 0:
                direcao -= 1*flagDirecao;
                break;
            case 2:
                direcao += 1*flagDirecao;
                break;
            default:
                break;
        }
    }

    //Metodo que responsàvel pela animacao padrão dos oponentes
    // nao permitindo ultrapassar os limites definidos no mar
    void anima(){
        distancia++;
        movimenta();
        Veiculo::calculaXZ();
        if(x >= limite_tela || z >= limite_tela || x <= -limite_tela || z <= -limite_tela){
            velocidade = -velocidade;
        }
        if(x >= limite_tela) {
           x = limite_tela;
        } else if(x <= -limite_tela) {
            x = -limite_tela;
        }
        if(z >= limite_tela) {
            z = limite_tela;
        } else if(z <= -limite_tela) {
            z = -limite_tela;
        }
        if (consultaColisao() == 1){
            velocidade = -velocidade;
            flagDirecao*=-1;
        }
    }

    // Metodo responsável pelo calculo do angulo em que o inimigo esta presente
    // utilizando a sua posicao e do navios posicões do navio como referencia
    double angInimigo(double xa, double za, double xb, double zb, double h) {
        if (zb - za < 0) {
            return -1 * (180 + acos((xb-xa)/h)*180/PI);
        }
        return (180 + acos((xb-xa)/h)*180/PI);
    }

    // Calcula a forca atirar nos inimigos atraves de lancamento obliquo
    double forcaInimigo(double raio){
        return sqrt(raio * GRAVIDADE);
    }

private:

};

#endif	/* _OPONENTE_CPP */
