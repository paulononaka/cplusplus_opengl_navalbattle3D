/*
 * Classe canhao
 * todos os barcos que possuem canhão
 * tem um objeto deste tipo entre seus atributos.
 * Desta forma, as funcoes do canhao puderam ser 
 * implementadas independentemente do restante do barco
 */

#ifndef _CANHAO_CPP
#define	_CANHAO_CPP

#define	TAM_CANHAO (50) // tamanho do canhao
#define	LARG_CANHAO (TAM_CANHAO/10) // largura do canhao
#define LARG_TIRO LARG_CANHAO
#define RAIOTIRO 3

#include "globais.cpp"
#include "util.cpp"
#include "pthread.h"

extern void imprimeVariavel(const char* nome, double valor, int id);
extern int colisaoTiro(int cod, double x, double z); // metodo para verificar colisoes entre tiros e barcos
extern GLint idCanhao;

class Canhao {
public:
    double orientacao;
    double inclinacao;
    int timer; // guardara o tempo desde o ultimo disparo
    int max_timer; // tempo maximo entre disparos
    int cod_veiculo; // codigo do veiculo ao qual pertence

    GLint gbalacanhao; // variavel pra associar à lista da bala de canhao.
    double forca; //Variavel da forca do tiro
    double vx; //Velocidade do eixo x no calculo da direcao do tiro
    double vy; //Velocidade do eixo y no calculo da direcao do tiro
    double vz; //Velocidade do eixo z no calculo da direcao do tiro
    double x;
    double y;
    double z;
    int atirou; //variaver de controle para tiro
    double alt_canhao;
    
    // construtor
    Canhao(int pcod_veiculo, double alt_veiculo){
        alt_canhao = alt_veiculo;
        cod_veiculo = pcod_veiculo;
        inicializa();
    }
    void inicializa(){
        orientacao = 0;
        inclinacao = 45;
        forca = 0; //Variavel da forca do tiro
        vx = 0; //Velocidade do eixo x no calculo da direcao do tiro
        vy = 0; //Velocidade do eixo y no calculo da direcao do tiro
        vz = 0; //Velocidade do eixo z no calculo da direcao do tiro
        atirou = 0; //variaver de controle para tiro
        posicaoInicialTiro(0, 0);
        srand(time(0));
        timer = rand() % 100;
        max_timer = 50;
    }
    
    // define a posicao inicial do tiro
    void posicaoInicialTiro(double x_navio, double z_navio) {
        if (atirou == 0) {
            x = x_navio + TAM_CANHAO * cos(orientacao*PI/180) * cos(inclinacao*PI/180);
            y = alt_canhao + TAM_CANHAO * sin(inclinacao*PI/180);
            z = z_navio + TAM_CANHAO * sin(orientacao* PI/180) * cos(inclinacao* PI/180);
        }
    }

    // metodo responsavel por calcular a velocidade do tiro para que acerte o navio
    void calculaVelocidadeTiro() {
        if (atirou == 0) {
            if(timer < max_timer){
                timer++;
            }
            if ((cod_veiculo == CODNAVIO) || (timer >= max_timer)) {
                atirou = 1;
                timer = 0;
                vx = forca * cos(orientacao* PI/180) * cos(inclinacao* PI/180);
                vy = forca * sin(inclinacao* PI/180);
                vz = forca * sin(orientacao* PI/180) * cos(inclinacao* PI/180);
            }
        }
    }
    
    // modelagem hierarquica
    void criaListas() {
        idCanhao = glGenLists(1);
        glNewList(idCanhao, GL_COMPILE);
        glRotatef(90,0,1,0);
            GLUquadricObj *cilindro1 = gluNewQuadric();
            glColor3f(0, 1, 0);
            gluQuadricDrawStyle(cilindro1, GLU_LINE);
            gluCylinder(cilindro1, LARG_CANHAO, LARG_CANHAO, TAM_CANHAO, LARG_CANHAO*3, LARG_CANHAO*3);
        glEndList();

        gbalacanhao = glGenLists(1);
        glNewList(gbalacanhao, GL_COMPILE);
            glColor3f(1, 0, 0);
            glutWireSphere(LARG_TIRO,LARG_TIRO*3,LARG_TIRO*3);
        glEndList();
    }

    // metodo que desenha o canhao
    void desenhaCanhao() {
        glPushMatrix();
            glTranslatef(0, alt_canhao, 0); // encaixa canhao no navio
            glRotatef(orientacao, 0, -1, 0); // orientação - rotacionando em relacao ao eixo Y
            glRotatef(inclinacao, 0, 0, 1); // inclinação - rotacionando em relacao ao eixo -X
            glCallList(idCanhao);
        glPopMatrix();
    }

    // metodo que desenha o tiro
    void desenhaTiro() {
        glPushMatrix();
            glTranslatef(x, y, z);
            glCallList(gbalacanhao);
        glPopMatrix();

    }
    
    
    // metodo responsavel por fazer a animação do tiro percorrendo sua trajetoria
    void animaTiro(double x_navio, double z_navio) {
        if (atirou == 1){
            vy = vy - GRAVIDADE;
            x += vx;
            y += vy;
            z += vz;
            if(y < (alt_canhao + TAM_CANHAO * sin(inclinacao*PI/180))){
                colisaoTiro(cod_veiculo, x, z);
            }
            if(y < -LARG_TIRO){
                atirou = 0;
                posicaoInicialTiro(x_navio, z_navio);
            }
        }
    }
private:
};

#endif	/* _CANHAO_CPP */
