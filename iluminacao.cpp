#ifndef _ILUMINACAO_CPP
#define	_ILUMINACAO_CPP

/**
 * Efeito de iluminacao Gouraud
 *
 * @author Nonaka
 */
void iluminacao(void)
{
  GLfloat luzAmbiente[4]={0.2,0.2,1.0,1.0};         // qual cor reflete
  GLfloat luzDifusa[4]={1.0, 1.0, 1.0, 1.0};	    // "cor"
  GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};     // "brilho"
  GLfloat posicaoLuz[4]={200.0, 200.0, 200.0, 1.0};

  // Capacidade de brilho do material
  GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
  GLint especMaterial = 60;

  // Especifica que a cor de fundo da janela será preta
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  // Habilita o modelo de colorização de Gouraud
  glShadeModel(GL_SMOOTH);

  // Define a refletância do material
  glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
  // Define a concentração do brilho
  glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

  // Define os parâmetros da luz de número 0
  glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
  glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
  glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

  // Habilita a definição da cor do material a partir da cor corrente
  glEnable(GL_COLOR_MATERIAL);
  //Habilita o uso de iluminação
  glEnable(GL_LIGHTING);
  // Habilita a luz de número 0
  glEnable(GL_LIGHT0);
  // Habilita o depth-buffering
  glEnable(GL_DEPTH_TEST);
}

#endif