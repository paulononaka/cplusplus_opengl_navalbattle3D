/**
 * Funcoes principais do programa
 */

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "util.cpp"
#include "constantes.cpp"
#include "teclado.cpp"
#include "iluminacao.cpp"
#include "globais.cpp"
#include "iluminacao.cpp"

int pressionando_botao_mouse = 0;   // para saber se esta' apertando o botao do mouse
int x_ant, y_ant = 0;               // armazena a posicao do mouse antes de arrastar
double camera_inclinacao = 0;       // angulo de inclinacao da camera
double camera_orientacao = 0;       // angulo de orientacao da camera
double zoom = 2;                    // zoom para camera
GLfloat fAspect;                    // aspecto para visao pespectiva

/**
 * Cria a lista de cada objeto
 */
void criaListas() {
    gceumar.criaListas();
    gnavio.criaListas();
    gsubmarino.criaListas();
    gcruzador.criaListas();
    gportaaviao.criaListas();
    gdestroier.criaListas();
    // cria a lista para a mina apenas uma unica vez
    Mina m1(0,0,0,0);
    m1.criaListas();
}

/**
 * Prepara a vizualizacao orverview (ortografica) ou do canhao (pespectiva)
 */
void preparaVisualizacao(){
    if(visao == 1){
        // orverview
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-TAM*zoom+gdesliza_tela_horizontal, TAM*zoom+gdesliza_tela_horizontal, (-TAM)*zoom+gdesliza_tela_vertical, TAM*zoom+gdesliza_tela_vertical, -TAM*zoom, TAM*zoom);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(cos(camera_orientacao*PI/180), cos(camera_inclinacao*PI/180), sin(camera_orientacao*PI/180), 0, 0, 0, 0, 1, 0);
    } else {
        // canhao
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(70,fAspect,0.4,5000);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(-60*cos(gnavio.canhao.orientacao*PI/180)+gnavio.x, 100, -60*sin(gnavio.canhao.orientacao*PI/180)+gnavio.z, 10000*cos(gnavio.canhao.orientacao*PI/180), 0.1, 10000*sin(gnavio.canhao.orientacao*PI/180), 0, 1, 0);
    }
}

/**
 * Redenriza cada objeto
 */
void desenha() {
    preparaVisualizacao();
    gceumar.desenha();
    cartesiano();
    if (gnavio.sangue > 0) {
        gnavio.desenha();
    } else {
        if(visao == 1){
            // orverview
            escreveMaior("GAME OVER!!!", 0, 150, 0);
        } else {
            // pespectiva
            escreveMaior("GAME OVER!!!", 150*cos(gnavio.canhao.orientacao*PI/180)+gnavio.x, 150, 150*sin(gnavio.canhao.orientacao*PI/180)+gnavio.z);
        }
    }
    if (gsubmarino.sangue > 0) {
        gsubmarino.desenha();
    }
    if (gcruzador.sangue > 0) {
        gcruzador.desenha();
    }
    if (gportaaviao.sangue > 0) {
        gportaaviao.desenha();
    }
    if (gdestroier.sangue > 0) {
        gdestroier.desenha();
    }
    if ((gsubmarino.sangue <= 0) && (gcruzador.sangue <= 0) &&
        (gportaaviao.sangue <= 0) && (gdestroier.sangue <= 0)) {
        if(visao == 1){
            // orverview
            escreveMaior("YOU WIN!!!", 0, 150, 0);
        } else {
            // pespectiva
            escreveMaior("YOU WIN!!!", 150*cos(gnavio.canhao.orientacao*PI/180)+gnavio.x, 150, 150*sin(gnavio.canhao.orientacao*PI/180)+gnavio.z);
        }        
    }
    glutSwapBuffers();
}

/**
 * Atualiza as variaveis de cada objeto
 */
void anima(int par) {
    if (gnavio.sangue > 0) {
        gnavio.anima();
    }
    if (gsubmarino.sangue > 0) {
        gsubmarino.anima();
    }
    if (gcruzador.sangue > 0) {
        gcruzador.anima();
    }
    if (gportaaviao.sangue > 0) {
        gportaaviao.anima();
    }
    if (gdestroier.sangue > 0) {
        gdestroier.anima();
    }
    glutPostRedisplay();
    glutTimerFunc(DELTA, anima, 0);
}

/**
 * Move a camera com o mouse
 */
void mouseMove(int x,int y) {
    if (pressionando_botao_mouse == 1) {
        if ((x - x_ant) > 0) {
            // movendo para direita
            camera_orientacao += 2;
        } else if ((x - x_ant) < 0) {
            // movendo para esquerda
            camera_orientacao -= 2;
        }
        if ((y - y_ant) > 0) {
            // limite de inclinacao para cima
            if (camera_inclinacao <= 0) {
                camera_inclinacao += 2;
            }
        } else if ((y - y_ant) < 0) {
            // limite de inclinacao para baixo
            if (camera_inclinacao >= -180) {
                camera_inclinacao -= 2;
            }
        }
        x_ant = x;
        y_ant = y;
    }
}

/**
 * Zoom da camera com scroll e flag para saber se esta precionando botao do mouse
 */
void mouse(int botao, int estado, int x, int y){
    switch (botao){
        case 3:
            if (estado == GLUT_UP) {
                zoom -=0.1;
            }
            break;
        case 4:
            if (estado == GLUT_DOWN) {
                zoom +=0.1;
            }
            break;
        case GLUT_LEFT_BUTTON:
            if (estado == GLUT_DOWN) {
                if (pressionando_botao_mouse == 0) {
                    pressionando_botao_mouse = 1;
                }
            } else if (estado == GLUT_UP) {
                pressionando_botao_mouse = 0;
            }
            break;
    }
}

/**
 * Opcoes do menu de contexto
 */
void menu(int value) {
    // Habilita ou desabilita opcao que escolheu
    if (opmenu[value] == 0) {
        opmenu[value] = 1;
    } else {
        opmenu[value] = 0;
    }
    // Reset
    switch(value) {
    case 0:
        gcruzador.inicializa();
        gcruzador.canhao.inicializa();
        gnavio.inicializa();
        gnavio.canhao.inicializa();
        gportaaviao.inicializa();
        gportaaviao.canhao.inicializa();
        gsubmarino.inicializa();
        gdestroier.inicializa();
        gdestroier.canhao.inicializa();
    break;
    }
}

/**
 * Cria menu de contexto
 */
void criamenu() {
    int mainmenu;
    mainmenu = glutCreateMenu(menu);
    glutAddMenuEntry("Reiniciar", 0);
    glutAddMenuEntry("Exibir raios", 1);
    glutAddMenuEntry("Exibir minas", 2);
    glutAddMenuEntry("Exibir eixos", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

/**
 * Inicializa parametros para visualizacao pespectiva
 */
void parametrosVisualizacao()
{
  int w = 1000, h = 600;
  glViewport(0, 0, w, h);
  fAspect = (GLfloat)w/(GLfloat)h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(50,fAspect,0.4,500);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(-200,80,0, 0,0,0, 0,1,0);
}

/**
 * Funcao principal do programa
 */
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 600);
    glutCreateWindow("Batalha Naval");
    criaListas();
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);
    glutKeyboardFunc(teclado);
    glutKeyboardUpFunc(tecladoSolta);
    glutSpecialFunc(teclasEspeciais);
    glutDisplayFunc(desenha);
    glutTimerFunc(DELTA, anima, 0);
    criamenu();
    iluminacao();
    parametrosVisualizacao();
    glutMainLoop();
}
