/*
 * cruzador.cpp
 * 
 * Barco cruzador
 * 
 */

#ifndef _CRUZADOR_CPP
#define	_CRUZADOR_CPP

#include <GL/gl.h>
#include "oponente.cpp"
#include "veiculo.cpp"
#include "navio.cpp"
#include "util.cpp"

#define TAM_CRUZADOR 160
#define TAM_CRUZADOR1 220
#define QTDE_RAIO_CRUZADOR 4
#define LARGURA_CRUZADOR (TAM_CRUZADOR/QTDE_RAIO_CRUZADOR)
#define LARGURA_CRUZADOR1 (TAM_CRUZADOR1/QTDE_RAIO_CRUZADOR)
#define CANHAO_CRUZADOR 40

extern Navio gnavio;

class Cruzador: public Oponente { // herda de oponente caracteristicas semelhantes a outros oponentes
public:
    Canhao canhao; // objeto canhao
    Cruzador(): canhao(CODCRUZADOR, CANHAO_CRUZADOR){
        inicializa();
    }
    void inicializa() {
        sangue = 1;
        velocidade = 2; // velocidade
        cod = CODCRUZADOR;
        diametro = LARGURA_CRUZADOR1;
        raio = LARGURA_CRUZADOR1/2;
        qtdOrigem = QTDE_RAIO_CRUZADOR;
        x = TAM/2;
        z = TAM/2;
    }

    GLint id;
    GLint idFundo;
    GLint idConves;
    GLint idLados;
    GLint idPontas;
    GLint idCabines;
    GLint idBaseCanhao;
    GLint idColetores;


    // modelagem hierarquica
    void criaListas() {
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
            glColor3f(1,1,1);
            glCallList(idFundo);
            glCallList(idConves);
            glColor3f(1,0.5,0);
            glCallList(idLados);
            glCallList(idPontas);
            glColor3f(1,0.5,0);
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
                glVertex3i(-TAM_CRUZADOR/2,LARGURA_CRUZADOR/2,0);
                glVertex3i(TAM_CRUZADOR/2,LARGURA_CRUZADOR/2,0);
                glVertex3i(TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2,0);
                glVertex3i(-TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2,0);
            glEnd();
            glPopMatrix();

            //triangulo fundo
            glPushMatrix();
            glRotatef(90,1,0,0);
            glBegin(GL_TRIANGLES);
                glVertex3i(-TAM_CRUZADOR/2,LARGURA_CRUZADOR/2,0);
                glVertex3i(-TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2,0);
                glVertex3i(-TAM_CRUZADOR/2-30,0,0);
            glEnd();
            glPopMatrix();

            //triangulo fundo
            glPushMatrix();
            glRotatef(90,1,0,0);
            glBegin(GL_TRIANGLES);
                glVertex3i(TAM_CRUZADOR/2,LARGURA_CRUZADOR/2,0);
                glVertex3i(TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2,0);
                glVertex3i(TAM_CRUZADOR/2+30,0,0);
            glEnd();
            glPopMatrix();

        glEndList();

        glNewList(idConves, GL_COMPILE);
            // conves
            glPushMatrix();
            glRotatef(90,1,0,0);
            glTranslatef(0,0,-LARGURA_CRUZADOR);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_CRUZADOR/2,LARGURA_CRUZADOR/2,0);
                glVertex3i(TAM_CRUZADOR/2,LARGURA_CRUZADOR/2,0);
                glVertex3i(TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2,0);
                glVertex3i(-TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2,0);
            glEnd();
            glPopMatrix();

            //triangulo conves
            glPushMatrix();
            glRotatef(90,1,0,0);
            glTranslatef(0,0,-LARGURA_CRUZADOR);
            glBegin(GL_TRIANGLES);
                glVertex3i(-TAM_CRUZADOR/2,LARGURA_CRUZADOR/2,0);
                glVertex3i(-TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2,0);
                glVertex3i(-TAM_CRUZADOR/2-30,0,0);
            glEnd();
            glPopMatrix();

            //triangulo conves
            glPushMatrix();
            glRotatef(90,1,0,0);
            glTranslatef(0,0,-LARGURA_CRUZADOR);
            glBegin(GL_TRIANGLES);
                glVertex3i(TAM_CRUZADOR/2,LARGURA_CRUZADOR/2,0);
                glVertex3i(TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2,0);
                glVertex3i(TAM_CRUZADOR/2+30,0,0);
            glEnd();
            glPopMatrix();
        glEndList();

        glNewList(idLados, GL_COMPILE);
            // lado 1
            glPushMatrix();
            glTranslatef(0,LARGURA_CRUZADOR/2,LARGURA_CRUZADOR/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_CRUZADOR/2,LARGURA_CRUZADOR/2+5,0);
                glVertex3i(TAM_CRUZADOR/2,LARGURA_CRUZADOR/2+5,0);
                glVertex3i(TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2-5,0);
                glVertex3i(-TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2-5,0);
            glEnd();
            glPopMatrix();

            // lado 2
            glPushMatrix();
            glTranslatef(0,LARGURA_CRUZADOR/2,-LARGURA_CRUZADOR/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_CRUZADOR/2,LARGURA_CRUZADOR/2+5,0);
                glVertex3i(TAM_CRUZADOR/2,LARGURA_CRUZADOR/2+5,0);
                glVertex3i(TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2-5,0);
                glVertex3i(-TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2-5,0);
            glEnd();
            glPopMatrix();
        glEndList();

        glNewList(idPontas, GL_COMPILE);
            // frente
            glPushMatrix();
            glTranslatef(0,LARGURA_CRUZADOR/2,-LARGURA_CRUZADOR/2);
            glBegin(GL_QUADS);
                glVertex3i(TAM_CRUZADOR/2,LARGURA_CRUZADOR/2+5,0);
                glVertex3i(TAM_CRUZADOR/2+30,LARGURA_CRUZADOR/2+5,20);
                glVertex3i(TAM_CRUZADOR/2+30,-LARGURA_CRUZADOR/2-5,20);
                glVertex3i(TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2-5,0);
            glEnd();
            glPopMatrix();

            // frente
            glPushMatrix();
            glTranslatef(0,LARGURA_CRUZADOR/2,LARGURA_CRUZADOR/2);
            glBegin(GL_QUADS);
                glVertex3i(TAM_CRUZADOR/2,LARGURA_CRUZADOR/2+5,0);
                glVertex3i(TAM_CRUZADOR/2+30,LARGURA_CRUZADOR/2+5,-20);
                glVertex3i(TAM_CRUZADOR/2+30,-LARGURA_CRUZADOR/2-5,-20);
                glVertex3i(TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2-5,0);
            glEnd();
            glPopMatrix();

            // frente
            glPushMatrix();
            glTranslatef(0,LARGURA_CRUZADOR/2,-LARGURA_CRUZADOR/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_CRUZADOR/2,LARGURA_CRUZADOR/2+5,0);
                glVertex3i(-TAM_CRUZADOR/2-30,LARGURA_CRUZADOR/2+5,20);
                glVertex3i(-TAM_CRUZADOR/2-30,-LARGURA_CRUZADOR/2-5,20);
                glVertex3i(-TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2-5,0);
            glEnd();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,LARGURA_CRUZADOR/2,LARGURA_CRUZADOR/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_CRUZADOR/2,LARGURA_CRUZADOR/2+5,0);
                glVertex3i(-TAM_CRUZADOR/2-30,LARGURA_CRUZADOR/2+5,-20);
                glVertex3i(-TAM_CRUZADOR/2-30,-LARGURA_CRUZADOR/2-5,-20);
                glVertex3i(-TAM_CRUZADOR/2,-LARGURA_CRUZADOR/2-5,0);
            glEnd();
            glPopMatrix();
        glEndList();


        glNewList(idCabines, GL_COMPILE);

            glPushMatrix();
            glTranslatef(-40,45,0);
            glutSolidCube(25);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(40,45,0);
            glutSolidCube(25);
            glPopMatrix();

        glEndList();

        glNewList(idBaseCanhao, GL_COMPILE);
            glPushMatrix();
            glTranslatef(TAM_CRUZADOR/2-80,40,0);
            glutSolidSphere(LARGURA_CRUZADOR-30,20,20);
            glPopMatrix();
        glEndList();

        glNewList(idColetores, GL_COMPILE);
            glPushMatrix();
            glRotatef(90,90,0,0);
            glTranslatef(40,0,-70);
            gluCylinder(gluNewQuadric(), 2, 2, 30, 10, 10);
            glPopMatrix();

            glPushMatrix();
            glRotatef(90,90,0,0);
            glTranslatef(-40,0,-70);
            gluCylinder(gluNewQuadric(), 2, 2, 30, 10, 10);
            glPopMatrix();

        glEndList();

    }


    // metodo que desenha o objeto
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

    // metodo para a animacao do objeto
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

#endif	/* _CRUZADOR_CPP */
