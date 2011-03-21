/*
 * destroier.cpp
 *  
 *  Classe Destroier. herda funcionalidades da classe
 *  oponente e possui atributos proprios que diferem o
 *  destroier dos outros oponentes.
 */

#ifndef _DESTROIER_CPP
#define	_DESTROIER_CPP

// includes
#include <GL/gl.h>
#include "oponente.cpp"
#include "veiculo.cpp"
#include "navio.cpp"
#include "util.cpp"

// constantes
#define	TAM_DESTROIER 120 // comprimento da parte central
#define	TAM_DESTROIER1 180 // comprimento com pontas do desenho
#define RAIOS_DESTROIER 3 // quantidade de raios
#define	LARGURA_DESTROIER1 (TAM_DESTROIER1/RAIOS_DESTROIER) // largura
#define	LARGURA_DESTROIER (TAM_DESTROIER/RAIOS_DESTROIER)
#define TAM_PONTA 30
#define CANHAO_DESTROIER 55 // posicionamento do canhao

extern Navio gnavio; // precisa obter o objeto navio para poder mirá-lo

class Destroier: public Oponente {
public:
    Canhao canhao; // objeto canhao para o destroier
    Destroier(): canhao(CODDESTROIER, CANHAO_DESTROIER){
        inicializa();
    }
    
    // metodo que inicializa os atributos do destroier
    void inicializa() {
        sangue = 1; // 100% de pontos de vida no inicio
        velocidade = 5; // velocidade do barco
        cod = CODDESTROIER; // codigo para ser inserido na lista de navios
        diametro = LARGURA_DESTROIER1;
        raio = LARGURA_DESTROIER1/2;
        qtdOrigem = RAIOS_DESTROIER;
        x = -TAM/2; // posicoes iniciais do barco na tela
        z = TAM/2;
    }

    // identificadores de listas
    GLint id;

    GLint idFundo;
    GLint idConves;
    GLint idLados;
    GLint idPontas;
    GLint idCabines;
    GLint idBaseCanhao;
    GLint idColetores;


    void criaListas(){
        
        // modelagem hierarquica
        canhao.criaListas();

        id = glGenLists(1);

        idFundo = glGenLists(1);
        idConves = glGenLists(1);
        idLados = glGenLists(1);
        idPontas = glGenLists(1);
        idCabines = glGenLists(1);
        idBaseCanhao = glGenLists(1);
        idColetores = glGenLists(1);

        glNewList(id,GL_COMPILE); 
            glPushMatrix();
            glColor3f(1,1,0);
            glCallList(idFundo);
            glCallList(idConves);
            glColor3f(0.2,0,0);
            glCallList(idLados);
            glCallList(idPontas);
            glColor3f(0.2,0,0);
            glCallList(idCabines);
            glColor3f(0.15,0.15,0.15);
            glCallList(idBaseCanhao);
            glColor3f(0.2,0,0);
            glCallList(idColetores);
            glPopMatrix();
        glEndList();    

        // ----------------------------------------------------------------------------------------------

        glNewList(idFundo, GL_COMPILE);
            glPushMatrix();
            glRotatef(90,1,0,0);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_DESTROIER/2,LARGURA_DESTROIER/2,0);
                glVertex3i(TAM_DESTROIER/2,LARGURA_DESTROIER/2,0);
                glVertex3i(TAM_DESTROIER/2,-LARGURA_DESTROIER/2,0);
                glVertex3i(-TAM_DESTROIER/2,-LARGURA_DESTROIER/2,0);
            glEnd();
            glPopMatrix();

            //triangulo fundo
            glPushMatrix();
            glRotatef(90,1,0,0);
            glBegin(GL_TRIANGLES);
                glVertex3i(-TAM_DESTROIER/2,LARGURA_DESTROIER/2,0);
                glVertex3i(-TAM_DESTROIER/2,-LARGURA_DESTROIER/2,0);
                glVertex3i(-TAM_DESTROIER/2-30,0,0);
            glEnd();
            glPopMatrix();

            //triangulo fundo
            glPushMatrix();
            glRotatef(90,1,0,0);
            glBegin(GL_TRIANGLES);
                glVertex3i(TAM_DESTROIER/2,LARGURA_DESTROIER/2,0);
                glVertex3i(TAM_DESTROIER/2,-LARGURA_DESTROIER/2,0);
                glVertex3i(TAM_DESTROIER/2+30,0,0);
            glEnd();
            glPopMatrix();

        glEndList();

        glNewList(idConves, GL_COMPILE);
            // conves
            glPushMatrix();
            glRotatef(90,1,0,0);
            glTranslatef(0,0,-LARGURA_DESTROIER);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_DESTROIER/2,LARGURA_DESTROIER/2,0);
                glVertex3i(TAM_DESTROIER/2,LARGURA_DESTROIER/2,0);
                glVertex3i(TAM_DESTROIER/2,-LARGURA_DESTROIER/2,0);
                glVertex3i(-TAM_DESTROIER/2,-LARGURA_DESTROIER/2,0);
            glEnd();
            glPopMatrix();

            //triangulo conves
            glPushMatrix();
            glRotatef(90,1,0,0);
            glTranslatef(0,0,-LARGURA_DESTROIER);
            glBegin(GL_TRIANGLES);
                glVertex3i(-TAM_DESTROIER/2,LARGURA_DESTROIER/2,0);
                glVertex3i(-TAM_DESTROIER/2,-LARGURA_DESTROIER/2,0);
                glVertex3i(-TAM_DESTROIER/2-30,0,0);
            glEnd();
            glPopMatrix();

            //triangulo conves
            glPushMatrix();
            glRotatef(90,1,0,0);
            glTranslatef(0,0,-LARGURA_DESTROIER);
            glBegin(GL_TRIANGLES);
                glVertex3i(TAM_DESTROIER/2,LARGURA_DESTROIER/2,0);
                glVertex3i(TAM_DESTROIER/2,-LARGURA_DESTROIER/2,0);
                glVertex3i(TAM_DESTROIER/2+30,0,0);
            glEnd();
            glPopMatrix();
        glEndList();

        glNewList(idLados, GL_COMPILE);
            // lado 1
            glPushMatrix();
            glTranslatef(0,LARGURA_DESTROIER/2,LARGURA_DESTROIER/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_DESTROIER/2,LARGURA_DESTROIER/2+5,0);
                glVertex3i(TAM_DESTROIER/2,LARGURA_DESTROIER/2+5,0);
                glVertex3i(TAM_DESTROIER/2,-LARGURA_DESTROIER/2-5,0);
                glVertex3i(-TAM_DESTROIER/2,-LARGURA_DESTROIER/2-5,0);
            glEnd();
            glPopMatrix();

            // lado 2
            glPushMatrix();
            glTranslatef(0,LARGURA_DESTROIER/2,-LARGURA_DESTROIER/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_DESTROIER/2,LARGURA_DESTROIER/2+5,0);
                glVertex3i(TAM_DESTROIER/2,LARGURA_DESTROIER/2+5,0);
                glVertex3i(TAM_DESTROIER/2,-LARGURA_DESTROIER/2-5,0);
                glVertex3i(-TAM_DESTROIER/2,-LARGURA_DESTROIER/2-5,0);
            glEnd();
            glPopMatrix();
        glEndList();

        glNewList(idPontas, GL_COMPILE);
            // frente
            glPushMatrix();
            glTranslatef(0,LARGURA_DESTROIER/2,-LARGURA_DESTROIER/2);
            glBegin(GL_QUADS);
                glVertex3i(TAM_DESTROIER/2,LARGURA_DESTROIER/2+5,0);
                glVertex3i(TAM_DESTROIER/2+30,LARGURA_DESTROIER/2+5,20);
                glVertex3i(TAM_DESTROIER/2+30,-LARGURA_DESTROIER/2-5,20);
                glVertex3i(TAM_DESTROIER/2,-LARGURA_DESTROIER/2-5,0);
            glEnd();
            glPopMatrix();

            // frente
            glPushMatrix();
            glTranslatef(0,LARGURA_DESTROIER/2,LARGURA_DESTROIER/2);
            glBegin(GL_QUADS);
                glVertex3i(TAM_DESTROIER/2,LARGURA_DESTROIER/2+5,0);
                glVertex3i(TAM_DESTROIER/2+30,LARGURA_DESTROIER/2+5,-20);
                glVertex3i(TAM_DESTROIER/2+30,-LARGURA_DESTROIER/2-5,-20);
                glVertex3i(TAM_DESTROIER/2,-LARGURA_DESTROIER/2-5,0);
            glEnd();
            glPopMatrix();

            // frente
            glPushMatrix();
            glTranslatef(0,LARGURA_DESTROIER/2,-LARGURA_DESTROIER/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_DESTROIER/2,LARGURA_DESTROIER/2+5,0);
                glVertex3i(-TAM_DESTROIER/2-30,LARGURA_DESTROIER/2+5,20);
                glVertex3i(-TAM_DESTROIER/2-30,-LARGURA_DESTROIER/2-5,20);
                glVertex3i(-TAM_DESTROIER/2,-LARGURA_DESTROIER/2-5,0);
            glEnd();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,LARGURA_DESTROIER/2,LARGURA_DESTROIER/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_DESTROIER/2,LARGURA_DESTROIER/2+5,0);
                glVertex3i(-TAM_DESTROIER/2-30,LARGURA_DESTROIER/2+5,-20);
                glVertex3i(-TAM_DESTROIER/2-30,-LARGURA_DESTROIER/2-5,-20);
                glVertex3i(-TAM_DESTROIER/2,-LARGURA_DESTROIER/2-5,0);
            glEnd();
            glPopMatrix();
        glEndList();


        glNewList(idCabines, GL_COMPILE);
            glPushMatrix();
            glTranslatef(0,45,0);
            glutSolidCube(25);
            glPopMatrix();
        glEndList();

        glNewList(idBaseCanhao, GL_COMPILE);
            glPushMatrix();
            glTranslatef(TAM_DESTROIER/2-60,55,0);
            glutSolidSphere(LARGURA_DESTROIER-30,20,20);
            glPopMatrix();
        glEndList();

        glNewList(idColetores, GL_COMPILE);
            glPushMatrix();
            glRotatef(90,90,0,0);
            glTranslatef(40,0,-60);
            gluCylinder(gluNewQuadric(), 2, 2, 30, 10, 10);
            glPopMatrix();

            glPushMatrix();
            glRotatef(90,90,0,0);
            glTranslatef(-40,0,-60);
            gluCylinder(gluNewQuadric(), 2, 2, 30, 10, 10);
            glPopMatrix();

        glEndList();


    }

    // metodo que desenha o destroier e seu canhão
    void desenha(){
        glPushMatrix();
            glTranslatef(x, y, z);
            canhao.desenhaCanhao();
            glRotatef(direcao,0,1,0);
            glCallList(id);
        glPopMatrix();
        if (gnavio.sangue > 0) {
            canhao.desenhaTiro();
        }
        desenhaRaios();
    }

    // metodo responsavel pela animação do barco.
    void anima(){
        canhao.posicaoInicialTiro(x, z);
        canhao.calculaVelocidadeTiro();
        h = calcRaio(gnavio.x, gnavio.z, x, z);
        canhao.orientacao = angInimigo(gnavio.x, gnavio.z, x, z, h);
        canhao.forca = forcaInimigo(h);
        canhao.animaTiro(x, z);
        Oponente::anima();
    }

private:

};

#endif	/* _DESTROIER_CPP */

