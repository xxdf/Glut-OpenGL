#include "windows.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"
#include "stdio.h"
void putpixel(double x, double y);
void DDA(double x1, double y1, double x2, double y2);
void DesenhaPlano(void);
void Desenha(void);
void polyline(void);

// Função pintar o pixel!!
void putpixel(double x, double y){
	// Especifica que a cor corrente é vermelha
	// RGB
	glColor3f(1.0f, 0.0f, 0.0f);	// cor ponto
	glBegin(GL_POINTS);

	//define os pontos
	// round(y);
	glVertex2f(x, y);
	glEnd();
};
// Função DDA
void DDA(double x1, double y1, double x2, double y2){
	double x, y;
	double m;
	m = (y2 - y1)/(x2 - x1);
	for (x = x1; x < x2; x++){
		y = y1 + m*(x - x1);
		putpixel(x, y);
	};
};
void polyline(){
	glColor3f(1.0f, 0.0f, 0.0f);	// Cor ponto
	glBegin(GL_LINE_STRIP);
	//glVertex2f(10, 10);
	glVertex2f(0, 10);
	glVertex2f(10, 20);
	glVertex2f(15, 20);
	glVertex2f(20, 40);
	glEnd();
};
void DesenhaPlano(void){
	glColor3f(1, 1, 0);		// Cor da linha
	glLineWidth(3.0);		// Espessura da linha
	glBegin(GL_LINES);
	glVertex3f(-500, 0, 0);
	glVertex3f(500, 0, 0);
	glVertex3f(0, -500, 0);
	glVertex3f(0, 500, 0);
	glEnd();
};
// Função callback chamada para fazer o desenho
void Desenha(void){
	// Limpa a janela de visualização com a cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT);

	DesenhaPlano();			// Desenha plano cartesiano

	DDA(0, 0, 5, 5);		// Algoritmo DDA(0.0, 0.0, 5.0, 5.0)

	glFlush();
};
// Programa Principal
int main(void){
	/* code */
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);				// tamanho da janela
	glutInitWindowPosition(100, 100);			// localização que a janela abrirá
	glutCreateWindow("Computação Gráfica");		// Nome da Janela
	glClearColor(0.0, 0.0, 0.0, 0.0);			// Cor Fundo da tela - Preto
	glPointSize(5.0);							// seta o tamanho do ponto
	gluOrtho2D(-50.0, 50.0, -50.0, 50.0);		// é usada para determinar que...
	glutDisplayFunc(Desenha);					// Chama a função principal
	glutMainLoop();

	polyline();
	//return 0;
};
