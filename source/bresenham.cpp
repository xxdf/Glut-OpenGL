#include "windows.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"
#include "stdio.h"
void putpixel(double x, double y);
void breseham(double x0, double y0, double x1, double y1);
void DDA(double x1, double y1, double x2, double y2);
void DesenhaPlano(void);
void Desenha(void);

// FUNCAO BRESEHAM
void breseham(double x0, double y0, double x1, double y1){
	double Dx, Dy, p, p2, xy2, x, y, xf, yf, CF0, CFf;
	bool fy=false, fx=false, fn=false, continua=true;
	Dx = x1 - x0; Dy = y1 - y0;
	// Coeficiente Angular para saber se é > 45º
	CF0 = x0 - y0; CFf = x1 - y1;
	// X0=X1 and Y0=Y1 PONTOS
	if (x0 == x1 && y0 == y1){
		putpixel(x0, y1);
		continua=false;
	}
	// Reta no eixo Y
	if (x0 == x1 && continua){
		for (y=y0; y<=y1; y++){
			putpixel(x0, y);
		}
		continua=false;
	}
	// Reta no eixo X
	if (y0 == y1 && continua){
		for (x=x0; x<=x1; x++){
			putpixel(x, y0);
		}
		continua=false;
	}
	if (continua){
		if (y0 > y1){			// Eixo Y negativo
			fy = true;
			printf("\ny0 > y1");
			y = y1;
			x = x1;
			yf = y0;
			//--
			Dx = x - x0;
			Dy = yf - y;
		}
		if (x0 > x1){			// Eixo X negativo
			fx = true;
			printf("\nx0 > x1");
			x = x1;
			y = y1;
			xf = x0;
			//--
			Dx = xf - x;
			Dy = y - y0;
		}
		if(x1 > x0 && y1 > y0){	// TUDO POSITIVO
			fn = true;
			x = x0;
			y = y0;
			yf = y1;
			xf = x1;
			//--
			Dx = xf - x;
			Dy = yf - y;
			//p = -(2 * Dy + Dx);	//d
			p = 2 * Dy - Dx;
			//p2 = 2 * Dx;		// ACIMA DE 45º
			//p2 = 2 * Dy;		// ABAIXO DE 45º
			//xy2 = 2 * (Dy + Dx);//dT
			xy2 = 2 * (Dy - Dx);
		}
		if ((CFf - CF0) > 0){		// ABAIXO DE 45 GRAUS
			printf("\nABAIXO DE 45 GRAUS");
			p2 = 2 * Dy;
			if(fn){
				printf("\nINICIAL: x=%.2f, y=%.2f\n", x, y);
				putpixel(x, y);
				while(x < xf){
					x++;
					if (p < 0)
						p = p + p2;
					else{
						y++;
						p = p + xy2;
					}
					printf("\n\tx=%.2f y=%.2f", x, y);
					putpixel(x, y);
				}
			}
			if (fy){
				printf("\nINICIAL: x=%.2f, y=%.2f\n", x, y);
				putpixel(x, y);
				while(y < yf){
					y = y + 1;
					if (p > 0)
						p = p - p2;
					else{
						x = x - 1;
						p = p + xy2;
					}
					printf("\n\tx=%.2f y=%.2f", x, y);
					putpixel(x, y);
				}
			}
			if(fx){
				printf("\nINICIAL: x=%.2f, y=%.2f\n", x, y);
				putpixel(x, y);
				while(x < xf){
					x = x + 1;
					if (p < 0)
						p = p + p2;
					else{
						y = y - 1;
						p = p + xy2;
					}
					printf("\n\tx=%.2f y=%.2f", x, y);
					putpixel(x, y);
				}
			}
			printf("\nFINAL: x=%.2f, y=%.2f\n", xf, yf);
			putpixel(xf, yf);
		}
		if((CFf - CF0) < 0){		// ACIMA DE 45 GRAUS
			printf("\nACIMA DE 45 GRAUS");
			p2 = 2 * Dx;
			if (fn){
				p2 = 2 * Dx;
				printf("\nINICIAL: x=%.2f, y=%.2f\n", x, y);
				putpixel(x, y);
				while(y<yf){
					y++;
					if(p>0)
						p = p - p2;
					else{
						x++;
						p = p + xy2;
					}
					printf("\n\tx=%.2f y=%.2f", x, y);
					putpixel(x, y);
				}
				xf = x;
			}
			if (fy){
				printf("\nINICIAL: x=%.2f, y=%.2f\n", x, y);
				putpixel(x, y);
				while(y < yf){
					y = y + 1;
					if (p > 0)
						p = p - p2;
					else{
						x = x - 1;
						p = p + xy2;
					}
					printf("\n\tx=%.2f y=%.2f", x, y);
					putpixel(x, y);
				}
				xf = x;
			}
			if(fx){
				printf("\nINICIAL: x=%.2f, y=%.2f\n", x, y);
				putpixel(x, y);
				while(x < xf){
					x = x + 1;
					if (p < 0)
						p = p + p2;
					else{
						y = y - 1;
						p = p + xy2;
					}
					printf("\n\tx=%.2f y=%.2f", x, y);
					putpixel(x, y);
				}
				yf = y;
			}
			printf("\nFINAL: x=%.2f, y=%.2f\n", xf, yf);
			putpixel(xf, yf);
		}
		if ((CFf - CF0) == 0){		// EXATOS 45 GRAUS
			x = x0; xf = x1;
			y = y0; yf = y1;
			printf("\nEXATOS 45 GRAUS");
			printf("\nINICIAL: x=%.2f, y=%.2f\n", x, y);
			putpixel(x, y);
			while(x < xf)
				if (printf("\n\tx=%.2f y=%.2f", x, y))
					putpixel(x++, y++);
			printf("\nFINAL: x=%.2f, y=%.2f\n", xf, yf);
			putpixel(xf, yf);
		}
	}
}
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
// Função que desenha o plano
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
	/* ABAIXO DE 45º */
	breseham(-5, 9, 30, 17);
	/* ACIMA DE 45º */
	breseham(5, -6, 20, 40);
	/* EXATOS 45 º */
	breseham(-20, -20, 30, 30);
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
	//return 0;
};
