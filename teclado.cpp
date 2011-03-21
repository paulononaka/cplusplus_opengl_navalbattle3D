#ifndef _TECLADO_CPP
#define	_TECLADO_CPP

#include "globais.cpp"
#include <sys/time.h>


/**
 * Captura de teclas especiais tipo as setas
 *
 * @param tecla       tecla
 * @param a         pos X do mouse
 * @param b         pos Y do mouse
 * @author          ?
 */

bool pressionado = false;
struct timeval tvi;
struct timeval tvf;
double tempoPressionado = 0;


void teclado(unsigned char tecla, int a, int b) {
    switch(tecla) {
        case 'w': case 'W':
            gnavio.canhao.inclinacao+=3;
        break;
        case 's': case 'S':
            gnavio.canhao.inclinacao-=3;
        break;
        case 'a': case 'A':
            gnavio.canhao.orientacao-=3;
        break;
        case 'd': case 'D':
            gnavio.canhao.orientacao+=3;
        break;
        case 't': case 'T':
            glutIgnoreKeyRepeat(true);
            gPressionandoTeclaTiro = true;
        break;
        case 'h': case 'H':
            gdesliza_tela_horizontal = gdesliza_tela_horizontal + 2;
        break;
        case 'k': case 'K':
            gdesliza_tela_horizontal = gdesliza_tela_horizontal - 2;
        break;
        case 'u': case 'U':
            gdesliza_tela_vertical = gdesliza_tela_vertical + 2;
        break;
        case 'j': case 'J':
            gdesliza_tela_vertical = gdesliza_tela_vertical - 2;
        break;
        case 'v': case 'V':
                visao *= -1;
        break;
    }
    switch(tecla) {
        case 'w': case 's': case 'a': case 'd':
        case 'W': case 'S': case 'A': case 'D':
            if (gnavio.canhao.atirou == 0) {
                gnavio.canhao.posicaoInicialTiro(gnavio.x, gnavio.z);
            }
    }
    glutPostRedisplay();
}

void tecladoSolta(unsigned char key, int a, int b) {
  switch(key) {
    case 't': case 'T':
        glutIgnoreKeyRepeat(false);
        gnavio.canhao.calculaVelocidadeTiro();
        gnavio.canhao.forca = 0;
        gPressionandoTeclaTiro = false;
    break;
  }
}

/**
 * Captura de teclas especiais tipo as setas
 *
 * @param key       tecla
 * @param a         pos X do mouse
 * @param b         pos Y do mouse
 * @author          ?
 */
void teclasEspeciais(int tecla, int a, int b) {
      int move;
      double xaux;
      double zaux;
     switch(tecla) {
        case GLUT_KEY_UP:
            if (gnavio.velocidade < 0)
                gnavio.velocidade *= -1;

            move = 0;
            xaux = gnavio.x + gnavio.velocidade * cos(gnavio.direcao*PI/180);
            zaux = gnavio.z + -1 * gnavio.velocidade * sin(gnavio.direcao*PI/180);


            if(gnavio.qtdOrigem % 2 != 0){
                int comp = gnavio.qtdOrigem/2;

                for(int i = 0;i <= comp ;i++){

                    if (colisaoNavios(gnavio.cod,gnavio.calculaOrigemX(xaux,i*gnavio.diametro),gnavio.calculaOrigemZ(zaux,i*gnavio.diametro),gnavio.raio) != 0){
                        //printf("colisao do navio\n");
                        move = 1;
                    }else if (colisaoNavios(gnavio.cod,gnavio.calculaOrigemX(xaux,-i*gnavio.diametro),gnavio.calculaOrigemZ(zaux,-i*gnavio.diametro),gnavio.raio) != 0){
                        //printf("colisao do navio\n");
                        move = 1;
                    }

                }
            }else{
                int comp = gnavio.qtdOrigem/2;
                int ind = 1;
                for(int i = 1;i <= comp;i= i++){
                    if(colisaoNavios(gnavio.cod,gnavio.calculaOrigemX(xaux,ind*gnavio.raio),gnavio.calculaOrigemZ(zaux,ind*gnavio.raio),gnavio.raio) != 0){
                        //printf("colisao do navio\n");
                        move = 1;
                    } else if  (colisaoNavios(gnavio.cod,gnavio.calculaOrigemX(xaux,-ind*gnavio.raio),gnavio.calculaOrigemZ(zaux,-ind*gnavio.raio),gnavio.raio) != 0){
                        //printf("colisao do navio\n");
                        move = 1;
                    }
                    ind = ind+2;
                }

            }

            if(move == 0){
                gnavio.calculaXZ();
                if (gnavio.colisaoMina()){
                    gnavio.sangue--;
                }

            }
        break;
        case GLUT_KEY_DOWN:
            if (gnavio.velocidade > 0)
                gnavio.velocidade *= -1;

            move = 0;
            xaux = gnavio.x + gnavio.velocidade * cos(gnavio.direcao*PI/180);
            zaux = gnavio.z + -1 * gnavio.velocidade * sin(gnavio.direcao*PI/180);


            if(gnavio.qtdOrigem % 2 != 0){
                int comp = gnavio.qtdOrigem/2;

                for(int i = 0;i <= comp ;i++){

                    if (colisaoNavios(gnavio.cod,gnavio.calculaOrigemX(xaux,i*gnavio.diametro),gnavio.calculaOrigemZ(zaux,i*gnavio.diametro),gnavio.raio) != 0){
                        move = 1;
                        //printf("colisao do navio\n");
                    }else if (colisaoNavios(gnavio.cod,gnavio.calculaOrigemX(xaux,-i*gnavio.diametro),gnavio.calculaOrigemZ(zaux,-i*gnavio.diametro),gnavio.raio) != 0){
                        //printf("colisao do navio\n");
                        move = 1;
                    }

                }
            }else{
                int comp = gnavio.qtdOrigem/2;
                int ind = 1;
                for(int i = 1;i <= comp;i= i++){
                    if(colisaoNavios(gnavio.cod,gnavio.calculaOrigemX(xaux,ind*gnavio.raio),gnavio.calculaOrigemZ(zaux,ind*gnavio.raio),gnavio.raio) != 0){
                        //printf("colisao do navio\n");
                        move = 1;
                    } else if  (colisaoNavios(gnavio.cod,gnavio.calculaOrigemX(xaux,-ind*gnavio.raio),gnavio.calculaOrigemZ(zaux,-ind*gnavio.raio),gnavio.raio) != 0){
                       // printf("colisao do navio\n");
                        move = 1;
                    }
                    ind = ind+2;
                }
            }
            if(move == 0){
                gnavio.calculaXZ();
                if (gnavio.colisaoMina()){
                    gnavio.sangue--;
                }


            }
        break;
        case GLUT_KEY_LEFT:
            gnavio.direcao+=3;
        break;
        case GLUT_KEY_RIGHT:
            gnavio.direcao-=3;
        break;
     }
     switch(tecla) {
        case GLUT_KEY_UP: case GLUT_KEY_DOWN:
        case GLUT_KEY_LEFT: case GLUT_KEY_RIGHT:
            gnavio.canhao.posicaoInicialTiro(gnavio.x, gnavio.z);
     }
     glutPostRedisplay();
}

#endif /* _TECLADO_CPP */
