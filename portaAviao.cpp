/*
 * portaaviao.cpp
 *  
 *  Classe PortaAviao. herda funcionalidades da classe
 *  oponente e possui atributos proprios que diferem o
 *  portaaviao dos outros oponentes.
 */

#ifndef _PORTAAVIAO_CPP
#define	_PORTAAVIAO_CPP

#include <GL/gl.h>
#include "oponente.cpp"
#include "veiculo.cpp"
#include "navio.cpp"
#include "util.cpp"

#define TAM_PA 200 // comprimento
#define TAM_PA1 260 // comprmento com as pontas
#define QTDE_RAIOS_PA 5 // numero de raios
#define LARGURA_PA (TAM_PA/QTDE_RAIOS_PA) // largura
#define LARGURA_PA1 (TAM_PA1/QTDE_RAIOS_PA)
#define CANHAO_PORTAAVIAO 60 // posicao do canhao

extern Navio gnavio; // acessa objeto navio para poder mirá-lo

class PortaAviao: public Oponente {
public:
    Canhao canhao; // objeto canhao.
    PortaAviao(): canhao(CODPORTAAVIAO, CANHAO_PORTAAVIAO){
        inicializa();
    }
    void inicializa() {
        sangue = 1;
        velocidade = 0.5; // o mais lento de todos
        cod = CODPORTAAVIAO;
        diametro = LARGURA_PA1;
        raio = LARGURA_PA1/2;
        qtdOrigem = QTDE_RAIOS_PA;
        x = -TAM/2;
        z = -TAM/2;
    }

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
            glColor3f(0.5,0.5,0);
            glCallList(idFundo);
            glCallList(idConves);
            glColor3f(0.05,0.05,0.05);
            glCallList(idLados);
            glCallList(idPontas);
            glColor3f(0.05,0.05,0.05);
            glCallList(idCabines);
            glColor3f(0.15,0.15,0.15);
            glCallList(idBaseCanhao);
            glColor3f(1,1,1);
            glCallList(idColetores);
            glPopMatrix();
        glEndList();     

        // ----------------------------------------------------------------------------------------------

        glNewList(idFundo, GL_COMPILE);
            glPushMatrix();
            glRotatef(90,1,0,0);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_PA/2,LARGURA_PA/2,0);
                glVertex3i(TAM_PA/2,LARGURA_PA/2,0);
                glVertex3i(TAM_PA/2,-LARGURA_PA/2,0);
                glVertex3i(-TAM_PA/2,-LARGURA_PA/2,0);
            glEnd();
            glPopMatrix();

            //triangulo fundo
            glPushMatrix();
            glRotatef(90,1,0,0);
            glBegin(GL_TRIANGLES);
                glVertex3i(-TAM_PA/2,LARGURA_PA/2,0);
                glVertex3i(-TAM_PA/2,-LARGURA_PA/2,0);
                glVertex3i(-TAM_PA/2-30,0,0);
            glEnd();
            glPopMatrix();

            //triangulo fundo
            glPushMatrix();
            glRotatef(90,1,0,0);
            glBegin(GL_TRIANGLES);
                glVertex3i(TAM_PA/2,LARGURA_PA/2,0);
                glVertex3i(TAM_PA/2,-LARGURA_PA/2,0);
                glVertex3i(TAM_PA/2+30,0,0);
            glEnd();
            glPopMatrix();

        glEndList();

        glNewList(idConves, GL_COMPILE);
            // conves
            glPushMatrix();
            glRotatef(90,1,0,0);
            glTranslatef(0,0,-LARGURA_PA);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_PA/2,LARGURA_PA/2,0);
                glVertex3i(TAM_PA/2,LARGURA_PA/2,0);
                glVertex3i(TAM_PA/2,-LARGURA_PA/2,0);
                glVertex3i(-TAM_PA/2,-LARGURA_PA/2,0);
            glEnd();
            glPopMatrix();

            //triangulo conves
            glPushMatrix();
            glRotatef(90,1,0,0);
            glTranslatef(0,0,-LARGURA_PA);
            glBegin(GL_TRIANGLES);
                glVertex3i(-TAM_PA/2,LARGURA_PA/2,0);
                glVertex3i(-TAM_PA/2,-LARGURA_PA/2,0);
                glVertex3i(-TAM_PA/2-30,0,0);
            glEnd();
            glPopMatrix();

            //triangulo conves
            glPushMatrix();
            glRotatef(90,1,0,0);
            glTranslatef(0,0,-LARGURA_PA);
            glBegin(GL_TRIANGLES);
                glVertex3i(TAM_PA/2,LARGURA_PA/2,0);
                glVertex3i(TAM_PA/2,-LARGURA_PA/2,0);
                glVertex3i(TAM_PA/2+30,0,0);
            glEnd();
            glPopMatrix();
        glEndList();

        glNewList(idLados, GL_COMPILE);
            // lado 1
            glPushMatrix();
            glTranslatef(0,LARGURA_PA/2,LARGURA_PA/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_PA/2,LARGURA_PA/2+5,0);
                glVertex3i(TAM_PA/2,LARGURA_PA/2+5,0);
                glVertex3i(TAM_PA/2,-LARGURA_PA/2-5,0);
                glVertex3i(-TAM_PA/2,-LARGURA_PA/2-5,0);
            glEnd();
            glPopMatrix();

            // lado 2
            glPushMatrix();
            glTranslatef(0,LARGURA_PA/2,-LARGURA_PA/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_PA/2,LARGURA_PA/2+5,0);
                glVertex3i(TAM_PA/2,LARGURA_PA/2+5,0);
                glVertex3i(TAM_PA/2,-LARGURA_PA/2-5,0);
                glVertex3i(-TAM_PA/2,-LARGURA_PA/2-5,0);
            glEnd();
            glPopMatrix();
        glEndList();

        glNewList(idPontas, GL_COMPILE);
            // frente
            glPushMatrix();
            glTranslatef(0,LARGURA_PA/2,-LARGURA_PA/2);
            glBegin(GL_QUADS);
                glVertex3i(TAM_PA/2,LARGURA_PA/2+5,0);
                glVertex3i(TAM_PA/2+30,LARGURA_PA/2+5,20);
                glVertex3i(TAM_PA/2+30,-LARGURA_PA/2-5,20);
                glVertex3i(TAM_PA/2,-LARGURA_PA/2-5,0);
            glEnd();
            glPopMatrix();

            // frente
            glPushMatrix();
            glTranslatef(0,LARGURA_PA/2,LARGURA_PA/2);
            glBegin(GL_QUADS);
                glVertex3i(TAM_PA/2,LARGURA_PA/2+5,0);
                glVertex3i(TAM_PA/2+30,LARGURA_PA/2+5,-20);
                glVertex3i(TAM_PA/2+30,-LARGURA_PA/2-5,-20);
                glVertex3i(TAM_PA/2,-LARGURA_PA/2-5,0);
            glEnd();
            glPopMatrix();

            // frente
            glPushMatrix();
            glTranslatef(0,LARGURA_PA/2,-LARGURA_PA/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_PA/2,LARGURA_PA/2+5,0);
                glVertex3i(-TAM_PA/2-30,LARGURA_PA/2+5,20);
                glVertex3i(-TAM_PA/2-30,-LARGURA_PA/2-5,20);
                glVertex3i(-TAM_PA/2,-LARGURA_PA/2-5,0);
            glEnd();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,LARGURA_PA/2,LARGURA_PA/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_PA/2,LARGURA_PA/2+5,0);
                glVertex3i(-TAM_PA/2-30,LARGURA_PA/2+5,-20);
                glVertex3i(-TAM_PA/2-30,-LARGURA_PA/2-5,-20);
                glVertex3i(-TAM_PA/2,-LARGURA_PA/2-5,0);
            glEnd();
            glPopMatrix();
        glEndList();


        glNewList(idCabines, GL_COMPILE);

            glPushMatrix();
            glRotatef(-90,0,1,0);
            glTranslatef(0,45,-TAM_PA/2+15);
            gluCylinder(gluNewQuadric(), LARGURA_PA-26, LARGURA_PA-26, TAM_PA-40, 10, 10);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(TAM_PA-120,45,0);
            glutSolidSphere(LARGURA_PA-26,20,20);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(TAM_PA-270,45,0);
            glutSolidSphere(LARGURA_PA-26,20,20);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-55,60,0);
            glutSolidCube(15);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-30,60,0);
            glutSolidCube(15);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(30,60,0);
            glutSolidCube(15);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(55,60,0);
            glutSolidCube(15);
            glPopMatrix();

        glEndList();

        glNewList(idBaseCanhao, GL_COMPILE);
            glPushMatrix();
            glTranslatef(TAM_PA-200,60,0);
            glutSolidSphere(LARGURA_PA-30,20,20);
            glPopMatrix();
        glEndList();

        glNewList(idColetores, GL_COMPILE);
            glPushMatrix();
            glRotatef(90,90,0,0);
            glTranslatef(30,0,-85);
            gluCylinder(gluNewQuadric(), 2, 2, 30, 10, 10);
            glPopMatrix();

            glPushMatrix();
            glRotatef(90,90,0,0);
            glTranslatef(55,0,-85);
            gluCylinder(gluNewQuadric(), 2, 2, 30, 10, 10);
            glPopMatrix();

            glPushMatrix();
            glRotatef(90,90,0,0);
            glTranslatef(-30,0,-85);
            gluCylinder(gluNewQuadric(), 2, 2, 30, 10, 10);
            glPopMatrix();

            glPushMatrix();
            glRotatef(90,90,0,0);
            glTranslatef(-55,0,-85);
            gluCylinder(gluNewQuadric(), 2, 2, 30, 10, 10);
            glPopMatrix();
        glEndList();


    }

    // metodo responsavel por chamar as listas de desenho
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
    
    // metodo responsavel por animar o portaaviao
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
