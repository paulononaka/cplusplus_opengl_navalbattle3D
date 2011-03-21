/*
 * Classe mina.
 * representa a bomba lançada pelo submarino no mapa.
 */

#ifndef _MINA_CPP
#define	_MINA_CPP

extern void imprimeVariavel(const char* nome, double valor, int id);
extern GLint idMina;
extern int opmenu[5];

class Mina {
public:
    int cod;
    double x, y, z;

    Mina(int parcod, double parx, double pary, double parz) {
        x = parx;
        y = pary;
        z = parz;
        cod = parcod;
    }

    // lista para o desenho da mina
    void criaListas() {
        idMina = glGenLists(1);
        glNewList(idMina, GL_COMPILE);
            glColor3f(0.3, 0, 0);
            glutWireSphere(5,25,25);
        glEndList();
    }

    // metodo para desenhar a mina
    void desenha(){
            glPushMatrix();
                glTranslatef(x, y, z);
//            imprimeVariavel("Mina x",x,10);
//            imprimeVariavel("Mina y",y,11);
//            imprimeVariavel("Mina z",z,12);
                glCallList(idMina);
            glPopMatrix();
        }

};

#endif	/* _MINA_CPP */
