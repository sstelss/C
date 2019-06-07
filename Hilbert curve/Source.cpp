#include <windows.h>
#include <glut.h>   //����������� ���������� glut.h
#include <stdio.h>
#include <iostream>

using namespace std;

int p = 1; //������� ������
//long double lx = 100, ly = 100;
double h = 100;
long double X = 0, Y = 0;
int i;

void GU(int i);
void GR(int i);
void GD(int i);
void GL(int i);

void DrawPart(double lx, double ly){
	glBegin(GL_LINE_STRIP);
	glVertex2d(X, Y);
	glVertex2d(X + lx, Y + ly);
	glEnd();
	X = X + lx;
	Y = Y + ly;
}



void GU(int i) {
	if (i > 0) {
		GR(i - 1);
		glColor3d(0, 100, 0);
		DrawPart(0, h);
		glColor3d(0, 0, 0);
		GU(i - 1);
		glColor3d(100, 0, 0);
		DrawPart(h, 0);
		glColor3d(0, 0, 0);
		GU(i - 1);
		glColor3d(0, 0, 100);
		DrawPart(0, -h);
		glColor3d(0, 0, 0);
		GL(i - 1);
	}
}

void GR(int i) {
	if (i > 0) {
		GU(i - 1);
		glColor3d(100, 0, 0);
		DrawPart(h, 0);
		glColor3d(0, 0, 0);
		GR(i - 1);
		glColor3d(0, 100, 0);
		DrawPart(0, h);
		glColor3d(0, 0, 0);
		GR(i - 1);
		glColor3d(100.0, 100.0, 0);
		DrawPart(-h, 0);
		glColor3d(0, 0, 0);
		GD(i - 1);
	}
}

void GD(int i) {
	if (i > 0) {
		GL(i - 1);
		glColor3d(0, 0, 100);
		DrawPart(0, -h);
		glColor3d(0, 0, 0);
		GD(i - 1);
		glColor3d(100.0, 100.0, 0);
		DrawPart(-h, 0);
		glColor3d(0, 0, 0);
		GD(i - 1);
		glColor3d(0, 100, 0);
		DrawPart(0, h);
		glColor3d(0, 0, 0);
		GR(i - 1);
	}
}

void GL(int i) {
	if (i > 0) {
		GD(i - 1);
		glColor3d(100.0, 100.0, 0);
		DrawPart(-h, 0);
		glColor3d(0, 0, 0);
		GL(i - 1);
		glColor3d(0, 0, 100);
		DrawPart(0, -h);
		glColor3d(0, 0, 0);
		GL(i - 1);
		glColor3d(100, 0, 0);
		DrawPart(h, 0);
		glColor3d(0, 0, 0);
		GU(i - 1);
	}
}

void Draw(){
	// ������� ������ ����� � �������
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0); //�������� ����� ����
	//a(p);
	X = 0;
	Y = 0;
	cout << "In draw x = " << X << "    Y = " << Y << endl;
	glColor3f(100.0, 0.0, 0.0);
	/*glPointSize(10);
	glBegin(GL_POINTS);
	glVertex2d(X, Y);
	glEnd();*/
	GU(p);
	//glFlush();
	
	glutSwapBuffers();
}

void KeyBoard(unsigned char key, int x, int y) {
	printf("This key have code %d\n", key);
	if (key == 27) {
		exit(0);
	}
	if (key == '+') {
		p++;
		//lx /= 2;
		//ly /= 2;
		h /= 2;
		Draw();
		cout << "h = " << h <<"  X ="<<X<<"  Y ="<<Y<<endl;
	}

	if (key == '-') {
		if (p != 1) {
			p--;
			/*lx *= 2;
			ly *= 2;*/
			h *= 2;
			Draw();
		}
	}
}

void Initialize(){
	//������� ������� (���������) ����
	glClearColor(1.0,1.0, 1.0, 1.0);
	//���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 200.0, -1.0, 200.0, -1.0, 1.0);
}


void Reshape(int width, int height)
{	
	int lenght;
	cout << "������� ��������!" << endl;
	if (width > height) {
		lenght = height;
	}
	else {
		lenght = width;
	}
	//��������� ����� ������
	glViewport(0, 0, lenght, lenght);

	//����� ������� ��������
	glMatrixMode(GL_PROJECTION);
	//��������� �������
	glLoadIdentity();
	//��������� ��������� ��������������� ������� ���������
	glOrtho(-1., 200., -1., 200., -1., 1.);
	
	Draw();
	//����� ������� �������
	glMatrixMode(GL_MODELVIEW);
	
}


//����� � ������� ����
int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);		//��������� ������ ����
	glutInitWindowPosition(100, 100);	//������� ����
	glutCreateWindow("Gilbert's Curve");		//��� ����
	Initialize();						//����� ������� Initialize
	glutDisplayFunc(Draw);				//����� ������� ���������
	glutKeyboardFunc(KeyBoard);
	glutReshapeFunc(Reshape);
	glutMainLoop();

	return 0;
}