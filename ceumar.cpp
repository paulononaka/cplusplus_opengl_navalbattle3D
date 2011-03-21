/* 
 * ceumar.cpp
 * 
 * Classe responsavel pela modelagem do céu (fundo)
 * e do mar
 * 
 */

#ifndef _CEUMAR_H
#define	_CEUMAR_H

#include <GL/gl.h>


class Ceumar {
public:
    GLint idMar;
    Ceumar(){
    }

    void desenha() {
        // ceu
        glClearColor(0.7, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // mar
        glCallList(idMar);
    }

    void criaListas() {
        idMar = glGenLists(1);
        glNewList(idMar, GL_COMPILE);
            glColor3f(0, 0, 0.5);
            glBegin(GL_QUADS);
                glVertex3i(-LIMITE_MAR*3, 0, -LIMITE_MAR*3);
                glVertex3i(-LIMITE_MAR*3, 0, LIMITE_MAR*3);
                glVertex3i(LIMITE_MAR*3, 0, LIMITE_MAR*3);
                glVertex3i(LIMITE_MAR*3, 0, -LIMITE_MAR*3);
            glEnd();
            glColor3f(0, 0, 0);
            glBegin(GL_LINES);
                glVertex3i(-LIMITE_MAR, 10, -LIMITE_MAR);
                glVertex3i(-LIMITE_MAR, 10, LIMITE_MAR);
            glEnd();
            glBegin(GL_LINES);
                glVertex3i(-LIMITE_MAR, 10, LIMITE_MAR);
                glVertex3i(LIMITE_MAR, 10, LIMITE_MAR);
            glEnd();
            glBegin(GL_LINES);
                glVertex3i(LIMITE_MAR, 10, LIMITE_MAR);
                glVertex3i(LIMITE_MAR, 10, -LIMITE_MAR);
            glEnd();
            glBegin(GL_LINES);
                glVertex3i(LIMITE_MAR, 10, -LIMITE_MAR);
                glVertex3i(-LIMITE_MAR, 10, -LIMITE_MAR);
            glEnd();
        glEndList();
    }
private:
};

#endif	/* _CEUMAR_H */
