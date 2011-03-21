#ifndef _UTIL_CPP
#define	_UTIL_CPP

/**
 * Funcoes globais
 */

#include "constantes.cpp"
#include "globais.cpp"

/**
 * Verifica se o tiro colidiu com algum veiculo
 *
 * @param cod   Identificador de quem esta' usando a funcao
 * @param x     X do tiro
 * @param z     Z do tiro
 */
int colisaoTiro(int cod, double x, double z){
    int acertou = colisaoNavios(cod, x, z, RAIOTIRO);
    switch (acertou){
        case CODNAVIO:
            gnavio.sangue--;
            break;
        case CODSUBMARINO:
            gsubmarino.sangue--;
            break;
        case CODCRUZADOR:
            gcruzador.sangue--;
            break;
        case CODPORTAAVIAO:
            gportaaviao.sangue--;
            break;
        case CODDESTROIER:
            gdestroier.sangue--;
            break;
    }

    int comp;
    int inicia;
    int inc;
    double dist;
    if (cod != CODNAVIO) {
        if (gnavio.qtdOrigem % 2 != 0) {
            comp = gnavio.qtdOrigem / 2;
            inicia = 0;
            inc = 1;
            dist = gnavio.diametro;
        } else {
            comp = gnavio.qtdOrigem;
            inicia = 1;
            inc = 2;
            dist = gnavio.raio;
        }
        for (int i = inicia; i <= comp; i+=inc) {
            if (calcRaio(x, z, gnavio.calculaOrigemX(x, -i * dist), gnavio.calculaOrigemZ(z, -i * dist)) <= gnavio.raio + RAIOTIRO) {
                return 1;
            }
        }
    }
    return 0;
}

/**
 * Calcula hipotenusa para saber a distancia entre dois pontos
 *
 * @param xa     X do ponto A
 * @param za     Z do ponto A
 * @param xb     X do ponto B
 * @param zb     Z do ponto B
 */
double calcRaio(double xa, double za, double xb, double zb){
    double ptx = xb - xa;
    double ptz = zb - za;
    if (ptx < 0){
        ptx *= -1;
    }
    if (ptz < 0){
        ptz *= -1;
    }
    double c = sqrt(pow(ptx,2) + pow(ptz,2));
    return c;
}

/**
 * Escreve um texto na tela
 *
 * @param texto     String que vai escrever
 * @param posX      X do texo
 * @param posY      Y do texo
 * @param posZ      Z do texo
 */
void escreve(const char* texto, int posX, int posY, int posZ) {
    glPushMatrix();
        glColor3i(1, 1, 1);
        glRasterPos3f(posX, posY, posZ);
        while (*texto)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *texto++);
    glPopMatrix();
}

/**
 * Escreve um texto maior na tela
 *
 * @param texto     String que vai escrever
 * @param posX      X do texo
 * @param posY      Y do texo
 * @param posZ      Z do texo
 */
void escreveMaior(const char* texto, int posX, int posY, int posZ) {
    glPushMatrix();
        glColor3i(1, 1, 1);
        glRasterPos3f(posX, posY, posZ);
        while (*texto)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *texto++);
    glPopMatrix();
}

/**
 * Escreve uma variavel e seu valor na tela
 *
 * @param nome      String nome da variavel
 * @param valor     Double valor da variavel
 * @param id        Posicao na tela (de 1 a 5 +-)
 */
void imprimeVariavel(const char* nome, double valor, int id) {
    char num [10000];
    int desloca = (ESCR/10);
    sprintf(num, "%f", valor);
    escreve(nome, 0, ESCR - desloca*id + desloca, 0);
    escreve(num, 0/*desloca*/, ESCR - desloca*id, 0);
}

/**
 * Desenha os eixos X, Y, Z na tela
 */
void cartesiano() {
    if (opmenu[3] == 1) {
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
        glVertex3i(-LIMITE_MAR, 0, 0);
        glVertex3i(LIMITE_MAR, 0, 0);
        glEnd();

        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        glVertex3i(0, -LIMITE_MAR, 0);
        glVertex3i(0, LIMITE_MAR, 0);
        glEnd();

        glColor3f(0, 0, 1);
        glBegin(GL_LINES);
        glVertex3i(0, 0, -LIMITE_MAR);
        glVertex3i(0, 0, LIMITE_MAR);
        glEnd();

        glPushMatrix();
            glTranslatef(-50, 0, 0);
            escreve("X", ESCR, 0, 0);
            escreve("Y", 0, ESCR, 0);
            escreve("Z", 0, 0, ESCR);
        glPopMatrix();
    }
}

/**
 * Verifica se um veiculo colidiu com o outro
 *
 * @param id        Identificador de quem esta' usando a funcao
 * @param xCol      X de um raio do veiculo a verificar
 * @param zCol      Z de um raio do veiculo a verificar
 * @param raioCol   Tamanho desse raio do veiculo a vefificar
 */
int colisaoNavios(int id, double xCol, double zCol,  double raioCol ){
    if (id != CODNAVIO ){
         if (gnavio.calculaColisao(xCol,zCol,raioCol) == 1){
             return CODNAVIO;
         }
    }
    if (id != CODCRUZADOR ){
        if ((gcruzador.sangue > 0) && (gcruzador.calculaColisao(xCol,zCol,raioCol) == 1)){
            return CODCRUZADOR;
        }
     }
    if (id != CODSUBMARINO ){
        if ((gsubmarino.sangue > 0) && (gsubmarino.calculaColisao(xCol,zCol,raioCol) == 1)){
            return CODSUBMARINO;
        }
    }
    if (id != CODPORTAAVIAO ){
        if ((gportaaviao.sangue > 0) && (gportaaviao.calculaColisao(xCol,zCol,raioCol) == 1)){
            return CODPORTAAVIAO;
        }
    }
    if (id != CODDESTROIER ){
        if ((gdestroier.sangue > 0) && (gdestroier.calculaColisao(xCol,zCol,raioCol) == 1)){
            return CODDESTROIER;
        }
    }
    return 0;
}


#endif /* _UTIL_CPP */