#ifndef _NAVIO_CPP
#define	_NAVIO_CPP

#include <GL/gl.h>
#include <list>
#include "constantes.cpp"
#include "globais.cpp"
#include "mina.cpp"
#include "submarino.cpp"

#define TAM_BARCO 120       // Comprimento do barco sem as pontas
#define TAM_BARCO1 170      // Comprimento do barco com as pontas
#define QTDE_RAIO_NAVIO 3   // Quantidade de raios
#define LARGURA (TAM_BARCO/QTDE_RAIO_NAVIO)     // Largura do barco
#define LARGURA1 (TAM_BARCO1/QTDE_RAIO_NAVIO)   // Limite do raios
#define NIVELCONVES 20      // Tamanho e largura do conves

extern Submarino gsubmarino;
extern void escreve(const char* texto, int posX, int posY, int posZ);

/**
 * Classe para o navio do jogador
 */
class Navio: public Veiculo {

public:
    Canhao canhao;

    /**
     * Id das listas referentes ao navio
     */
    GLint idFundo;
    GLint idConves;
    GLint idLados;
    GLint idPontas;
    GLint idCabines;
    GLint idCabinesSuperior;
    GLint idBaseCanhao;
    GLint idColetores;
    GLint idFumaca;

    /**
     * Construtor
     */
    Navio():canhao(CODNAVIO, NIVELCONVES+40){
        inicializa();
    }

    /**
     * Inicializa as variaveis
     */
    void inicializa(){
        sangue = 20;
        velocidade =  10;
        diametro = LARGURA1;
        raio = LARGURA1/2;
        qtdOrigem = QTDE_RAIO_NAVIO;
        cod = CODNAVIO;
        x = y = z = 0;
    }

    /**
     * Verifica se colidiu com uma mina e retira a mesma da lista caso colidir
     */
    int colisaoMina() {
        std::list <Mina*>::const_iterator itMina;
        int comp;
        int inicia;
        int inc;
        double dist;
        if (qtdOrigem % 2 != 0) {
            // se qtde de raios for impar
            comp = qtdOrigem / 2;
            inicia = 0;
            inc = 1;
            dist = diametro;
        } else {
            // se qtde de raios for par
            comp = qtdOrigem;
            inicia = 1;
            inc = 2;
            dist = raio;
        }
        // percorre os raios
        for (int i = inicia; i <= comp; i+=inc) {
            // percorre a lista de minas
            for (itMina = gsubmarino.listaMinas.begin(); itMina != gsubmarino.listaMinas.end(); itMina++) {
                Mina m = **itMina;
                // verifica os raios da direita
                if (calcRaio(m.x, m.z, calculaOrigemX(x,i * dist), calculaOrigemZ(z,i * dist)) <= raio + RAIOMINA) {
                    gsubmarino.listaMinas.remove(*itMina);
                    return 1;
                // verifica os raios da esquerda
                } else if (calcRaio(m.x, m.z, calculaOrigemX(x,-i * dist), calculaOrigemZ(z,-i * dist)) <= raio + RAIOMINA) {
                    gsubmarino.listaMinas.remove(*itMina);
                    return 1;
                }
            }
        }
        return 0;
    }

    /**
     * Renderiza componentes do navio
     */
    void desenha(){
        glPushMatrix();
            glTranslatef(x, y, z);
            canhao.desenhaCanhao();
            glRotatef(direcao,0,1,0);
            imprimeVariavel("Sangue",sangue,8.5);
            glCallList(id);
        glPopMatrix();
        canhao.desenhaTiro();
        desenhaRaios();
    }

    /**
     * Atualizacao das variaveis do navio
     */
    void anima(){
        canhao.animaTiro(x, z);
        if (gPressionandoTeclaTiro) {
            canhao.forca+=6;
        }
    }

    /**
     * Cria a lista referente ao navio
     */
    void criaListas(){

        canhao.criaListas();

        id = glGenLists(1);
        idFundo = glGenLists(1);
        idConves = glGenLists(1);
        idLados = glGenLists(1);
        idPontas = glGenLists(1);
        idCabines = glGenLists(1);
        idCabinesSuperior = glGenLists(1);
        idBaseCanhao = glGenLists(1);
        idColetores = glGenLists(1);

        glNewList(id,GL_COMPILE);
            glPushMatrix();
            glColor3f(0,0.3,0);
            glCallList(idFundo);
            glCallList(idConves);
            glColor3f(1,1,1);
            glCallList(idLados);
            glCallList(idPontas);
            glColor3f(1,1,1);
            glCallList(idCabines);
            glColor3f(0,0.3,0);
            glCallList(idCabinesSuperior);
            glColor3f(0.15,0.15,0.15);
            glCallList(idBaseCanhao);
            glColor3f(1,1,1);
            glCallList(idColetores);
            glPopMatrix();
        glEndList();

        glNewList(idFundo, GL_COMPILE);
            glPushMatrix();
            glRotatef(90,1,0,0);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_BARCO/2,LARGURA/2,0);
                glVertex3i(TAM_BARCO/2,LARGURA/2,0);
                glVertex3i(TAM_BARCO/2,-LARGURA/2,0);
                glVertex3i(-TAM_BARCO/2,-LARGURA/2,0);
            glEnd();
            glPopMatrix();

            //triangulo fundo
            glPushMatrix();
            glRotatef(90,1,0,0);
            glBegin(GL_TRIANGLES);
                glVertex3i(-TAM_BARCO/2,LARGURA/2,0);
                glVertex3i(-TAM_BARCO/2,-LARGURA/2,0);
                glVertex3i(-TAM_BARCO/2-30,0,0);
            glEnd();
            glPopMatrix();

            //triangulo fundo
            glPushMatrix();
            glRotatef(90,1,0,0);
            glBegin(GL_TRIANGLES);
                glVertex3i(TAM_BARCO/2,LARGURA/2,0);
                glVertex3i(TAM_BARCO/2,-LARGURA/2,0);
                glVertex3i(TAM_BARCO/2+30,0,0);
            glEnd();
            glPopMatrix();

        glEndList();

        glNewList(idConves, GL_COMPILE);
            // conves
            glPushMatrix();
            glRotatef(90,1,0,0);
            glTranslatef(0,0,-LARGURA);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_BARCO/2,LARGURA/2,0);
                glVertex3i(TAM_BARCO/2,LARGURA/2,0);
                glVertex3i(TAM_BARCO/2,-LARGURA/2,0);
                glVertex3i(-TAM_BARCO/2,-LARGURA/2,0);
            glEnd();
            glPopMatrix();

            //triangulo conves
            glPushMatrix();
            glRotatef(90,1,0,0);
            glTranslatef(0,0,-LARGURA);
            glBegin(GL_TRIANGLES);
                glVertex3i(-TAM_BARCO/2,LARGURA/2,0);
                glVertex3i(-TAM_BARCO/2,-LARGURA/2,0);
                glVertex3i(-TAM_BARCO/2-30,0,0);
            glEnd();
            glPopMatrix();

            //triangulo conves
            glPushMatrix();
            glRotatef(90,1,0,0);
            glTranslatef(0,0,-LARGURA);
            glBegin(GL_TRIANGLES);
                glVertex3i(TAM_BARCO/2,LARGURA/2,0);
                glVertex3i(TAM_BARCO/2,-LARGURA/2,0);
                glVertex3i(TAM_BARCO/2+30,0,0);
            glEnd();
            glPopMatrix();
        glEndList();

        glNewList(idLados, GL_COMPILE);
            // lado 1
            glPushMatrix();
            glTranslatef(0,LARGURA/2,LARGURA/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_BARCO/2,LARGURA/2+5,0);
                glVertex3i(TAM_BARCO/2,LARGURA/2+5,0);
                glVertex3i(TAM_BARCO/2,-LARGURA/2-5,0);
                glVertex3i(-TAM_BARCO/2,-LARGURA/2-5,0);
            glEnd();
            glPopMatrix();

            // lado 2
            glPushMatrix();
            glTranslatef(0,LARGURA/2,-LARGURA/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_BARCO/2,LARGURA/2+5,0);
                glVertex3i(TAM_BARCO/2,LARGURA/2+5,0);
                glVertex3i(TAM_BARCO/2,-LARGURA/2-5,0);
                glVertex3i(-TAM_BARCO/2,-LARGURA/2-5,0);
            glEnd();
            glPopMatrix();
        glEndList();

        glNewList(idPontas, GL_COMPILE);
            // frente
            glPushMatrix();
            glTranslatef(0,LARGURA/2,-LARGURA/2);
            glBegin(GL_QUADS);
                glVertex3i(TAM_BARCO/2,LARGURA/2+5,0);
                glVertex3i(TAM_BARCO/2+30,LARGURA/2+5,20);
                glVertex3i(TAM_BARCO/2+30,-LARGURA/2-5,20);
                glVertex3i(TAM_BARCO/2,-LARGURA/2-5,0);
            glEnd();
            glPopMatrix();

            // frente
            glPushMatrix();
            glTranslatef(0,LARGURA/2,LARGURA/2);
            glBegin(GL_QUADS);
                glVertex3i(TAM_BARCO/2,LARGURA/2+5,0);
                glVertex3i(TAM_BARCO/2+30,LARGURA/2+5,-20);
                glVertex3i(TAM_BARCO/2+30,-LARGURA/2-5,-20);
                glVertex3i(TAM_BARCO/2,-LARGURA/2-5,0);
            glEnd();
            glPopMatrix();

            // frente
            glPushMatrix();
            glTranslatef(0,LARGURA/2,-LARGURA/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_BARCO/2,LARGURA/2+5,0);
                glVertex3i(-TAM_BARCO/2-30,LARGURA/2+5,20);
                glVertex3i(-TAM_BARCO/2-30,-LARGURA/2-5,20);
                glVertex3i(-TAM_BARCO/2,-LARGURA/2-5,0);
            glEnd();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0,LARGURA/2,LARGURA/2);
            glBegin(GL_QUADS);
                glVertex3i(-TAM_BARCO/2,LARGURA/2+5,0);
                glVertex3i(-TAM_BARCO/2-30,LARGURA/2+5,-20);
                glVertex3i(-TAM_BARCO/2-30,-LARGURA/2-5,-20);
                glVertex3i(-TAM_BARCO/2,-LARGURA/2-5,0);
            glEnd();
            glPopMatrix();
        glEndList();


        glNewList(idCabines, GL_COMPILE);
            glPushMatrix();
            glTranslatef(0,45,0);
            glutSolidCube(25);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-25,45,0);
            glutSolidCube(25);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-50,45,0);
            glutSolidCube(25);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(25,45,0);
            glutSolidCube(25);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(50,45,0);
            glutSolidCube(25);
            glPopMatrix();
        glEndList();

        glNewList(idCabinesSuperior, GL_COMPILE);
            glPushMatrix();
            glTranslatef(45,60,0);
            glutSolidCube(15);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-45,60,0);
            glutSolidCube(15);
            glPopMatrix();
        glEndList();

        glNewList(idBaseCanhao, GL_COMPILE);
            glPushMatrix();
            glTranslatef(TAM_BARCO/2-60,55,0);
            glutSolidSphere(LARGURA-30,20,20);
            glPopMatrix();
        glEndList();

        glNewList(idColetores, GL_COMPILE);
            glPushMatrix();
            glRotatef(90,90,0,0);
            glTranslatef(45,0,-80);
            gluCylinder(gluNewQuadric(), 2, 2, 30, 10, 10);
            glPopMatrix();

            glPushMatrix();
            glRotatef(90,90,0,0);
            glTranslatef(-45,0,-80);
            gluCylinder(gluNewQuadric(), 2, 2, 30, 10, 10);
            glPopMatrix();
        glEndList();
    }

};

#endif	/* _NAVIO_CPP */
