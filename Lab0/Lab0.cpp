#include <GL/glut.h>
#include <GL/gl.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
using namespace std;

int window;
int oldx = 0;
int oldy = 0;
static int nowcount =0, j = 0;
static int xstart = 0, ystart = 0;
static float a, b, c;
static char nowplay;
vector <pair<int, int>> dreturnplace;
vector <float> drecord;
vector <pair<int, int>> lreturnplace;
vector<float> lrecord;
vector <pair<int, int>> preturnplace;
vector<float> precord;
vector <pair<int, int>> oreturnplace;
vector<float> orecord;
void display();
void mouseMove(int x, int y);
void Bresenham(float xs, float ys, float xe, float ye);
void ManyGlVertex2f(float absX, float absY, float x, float y);
void keyboardFunc(unsigned char key, int x, int y);
void Bresenham_O(float xs, float ys, float xe, float ye);
void delayTime(int time);
void Return();


void mouse(int bin, int state, int x, int y) {
    if(bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
         if (nowplay == 'd') {
             //dreturnplace.push_back(make_pair(x, y));
             
             a = (rand() % 255);
             b = (rand() % 255);
             c = (rand() % 255);
             a = a / 255;
             b = b / 255;
             c = c / 255;
            cout << "a: " << a << " b: " << b << " c: " << c << endl;
             glColor3f(a, b, c);
             mouseMove(x,y);
         }
         else if (nowplay == 'l') {
             if (nowcount == 0) {
                 oldx = x;
                 oldy = y;
                 nowcount = 1;
                 
             }
             else if (nowcount == 1) {
                 lreturnplace.push_back(make_pair(oldx, oldy));
                 lreturnplace.push_back(make_pair(x, y));
                 a = (rand() % 255);
                 b = (rand() % 255);
                 c = (rand() % 255);
                 a = a / 255;
                 b = b / 255;
                 c = c / 255;
                 cout << "a: " << a << " b: " << b << " c: " << c << endl;
                 glColor3f(a, b, c);
                 lrecord.push_back(a);
                 lrecord.push_back(b);
                 lrecord.push_back(c);
                 Bresenham(oldx, oldy, x, y);
             }
         }
         else if (nowplay == 'p') {
             cout << "now p" << endl;
             if (nowcount == 0) {
                 xstart = x;
                 ystart = y;
                 oldx = x;
                 oldy = y;
                 nowcount = 1;
                 a = (rand() % 255);
                 b = (rand() % 255);
                 c = (rand() % 255);
                 a = a / 255;
                 b = b / 255;
                 c = c / 255;
                 cout << "a: " << a << " b: " << b << " c: " << c << endl;
                 glColor3f(a, b, c);
                 precord.push_back(a);
                 precord.push_back(b);
                 precord.push_back(c);
             }
             else {
                 preturnplace.push_back(make_pair(oldx, oldy));
                 preturnplace.push_back(make_pair(x, y));
                 precord.push_back(a);
                 precord.push_back(b);
                 precord.push_back(c);
                 Bresenham(oldx, oldy, x, y);
                 nowcount = 1;
                 oldx = x;
                 oldy = y;
             }
         }
         else if (nowplay == 'o') {
             cout << "now o" << endl;
             if (nowcount == 0) {
                 oldx = x;
                 oldy = y;
                 nowcount = 1;
                 
             }
             else {
                oreturnplace.push_back(make_pair(oldx, oldy));
                oreturnplace.push_back(make_pair(x, y));
                a = (rand() % 255);
                b = (rand() % 255);
                c = (rand() % 255);
                a = a / 255;
                b = b / 255;
                c = c / 255;
                cout << "a: " << a << " b: " << b << " c: " << c << endl;
                glColor3f(a, b, c);
                orecord.push_back(a);
                orecord.push_back(b);
                orecord.push_back(c);
                Bresenham_O(oldx, oldy, x, y);
             }
         }
    }  
    if(bin == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        if (nowplay == 'p') {
            preturnplace.push_back(make_pair(oldx, oldy));
            preturnplace.push_back(make_pair(xstart, ystart));
            precord.push_back(a);
            precord.push_back(b);
            precord.push_back(c);
            Bresenham(oldx, oldy, xstart, ystart);
            xstart = 0;
            ystart = 0;
            nowcount = 0;
        }
    }
}
int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    system("pause");
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    gluOrtho2D(0, 800, 0, 800);
    window = glutCreateWindow("Your First GLUT  Window!");
    glutDisplayFunc(display);
    //glutSwapBuffers();
    delayTime(1);
    glutKeyboardFunc(keyboardFunc);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);
    gluOrtho2D(0, 800, 0, 800);
    glutMainLoop();
}
void display() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glFlush();
}
void delayTime(int time) {
    glutTimerFunc(time, delayTime, 0);
    glutPostRedisplay();
}
void mouseMove(int x, int y) {
    if (nowplay == 'd') {
        drecord.push_back(a);
        drecord.push_back(b);
        drecord.push_back(c);
        dreturnplace.push_back(make_pair(x, y));
        glBegin(GL_POINTS);
        glVertex2i(x, 800 - y);
        glEnd();
        nowcount = 0;
    }
    else if (nowplay == 'r') {
        glBegin(GL_POINTS);
        glVertex2i(x, 800 - y);
        glEnd();
    }
    else {
        cout << "Can't draw" << endl;
    }
}
void Bresenham(float xs, float ys, float xe, float ye) {

    if (xe < xs) {
        swap(xe, xs);
        swap(ye, ys);
    }
    float absY = ye- ys;
    float absX = xe - xs;
    if ((fabsf(absY) > fabsf(absX)) && absX > 0 && absY > 0) {//斜率大於1
        float  m = ys;
        ys = xs;
        xs = m;
        float n = ye;
        ye = xe;
        xe = n;
    }
    else if (absY < 0 && absX>0 && (fabsf(absY) <= fabs(absX))) {//斜率-1到0
        ys = -ys;
        ye = -ye;
    }
    else if (absY < 0 && absX>0 && (fabsf(absY) > fabs(absX))) {//斜率小於-1
        float  m = ys;
        ys = xs;
        xs = -m;
        float n = ye;
        ye = xe;
        xe = -n;
    }
    else {
    }
    float dx = xe - xs;
    float dy = ye - ys;
    float m = (double)dy / (double)dx;
    float e = m - 0.5;
    float x, y;
    x = xs;
    y = ys;
    for (int i = 0; i < fabsf(dx); i++) {
        ManyGlVertex2f(absX, absY, x, y); //呼叫ManyGlVertex2f()函式
        if (e >= 0) {
            y = y + 1; e = e - 1;
        }
        x = x + 1; e = e + m;
    }
    //畫直線
    if (xs == xe) {
        float maxY = max(ys, ye);
        float minY = min(ys, ye);
        glBegin(GL_POINTS);
        for (float i = minY; i <= maxY; i++) {
            glVertex2f(xs, i);  
        }
         glEnd();
    }
    nowcount = 0;
}
void ManyGlVertex2f(float absX, float absY, float x, float y) {
    glBegin(GL_POINTS);
    //glColor3f(float(rand() % 255), float(rand() % 255), float(rand() % 255));
    if ((fabsf(absY) > fabsf(absX)) && absX > 0 && absY > 0) {//斜率大於1 ok
        glVertex2f(y, 800-x);        
    }
    else if (absY < 0 && absX>0 && (fabsf(absY) <= fabs(absX))) {//斜率-1到 OK
        glVertex2f(x,    800+ y);
    }
    else if (absY < 0 && absX>0 && (fabsf(absY) > fabs(absX))) {//斜率小於-1
        glVertex2f(y,  800+ x);        
    }
    else {//斜率0到1
        glVertex2f(x,800-y);
    }
    glEnd();
}
void keyboardFunc(unsigned char key, int x, int y) {
    if (key == 'd' ) {  //點
        nowplay= key;
        nowcount = 2;
    }
    else if (key == 'l') { //線
        nowplay = key;
        nowcount = 0;
    }   
    else if (key == 'p') { //多邊形
        nowplay = key;
        nowcount = 0;
    }
    else if (key == 'o') { //圓
        nowplay = key;
        nowcount = 0;
    }
    else if (key == 'c') { //清除
        nowplay = key;
        cout << "Clear" << endl;
        nowcount == 0;
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();   
    }
    else if(key== 'r') { //回復
        nowplay = key;
        Return();
    }
    else if (key == 'q') { //關閉
        nowplay = key;
        exit(0);
    }
}
void Bresenham_O(float xs, float ys, float xe, float ye) {
    float R = sqrt(pow((xe - xs), 2) + pow((ye - ys), 2)); //算半徑
    float x, y, d;
    x = 0;
    y = R;
    d = 3 - 2 * R;
    glBegin(GL_POINTS);
    while (x < y) {
        glVertex2f(xs + x, 800 - (ys + y));       
        glVertex2f(xs - x, 800 - (ys + y));       
        glVertex2f(xs + x, 800 - (ys - y));
        glVertex2f(xs - x, 800 - (ys - y));        
        glVertex2f(xs + y, 800 - (ys + x));        
        glVertex2f(xs - y, 800 - (ys + x));       
        glVertex2f(xs + y, 800 - (ys - x));      
        glVertex2f(xs - y, 800 - (ys - x)); 

        if (d < 0) {
            d = d + 4 * x + 6;
        }
        else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    if (x == y) {
        glVertex2f(xs + x, 800 - (ys + y));
        glVertex2f(xs - x, 800 - (ys + y));
        glVertex2f(xs + x, 800 - (ys - y));
        glVertex2f(xs - x, 800 - (ys - y));
        glVertex2f(xs + y, 800 - (ys + x));
        glVertex2f(xs - y, 800 - (ys + x));
        glVertex2f(xs + y, 800 - (ys - x));
        glVertex2f(xs - y, 800 - (ys - x));
    }

    nowcount = 0;
    glEnd();
    //glFlush();
}
void Return() {
    if (lreturnplace.size() != NULL) {
        j = 0;
        cout << "YES l" << endl;
        for (int i = 0; i < lreturnplace.size(); i+=2) {
            
            glColor3f(lrecord[j], lrecord[j + 1], lrecord[j + 2]);
            Bresenham(lreturnplace[i].first, lreturnplace[i].second, lreturnplace[i+1].first, lreturnplace[i+1].second);
            j+=3;
        }
        j = 0;
    }
    else {
        cout << "NO l" << endl;
    }
    if (dreturnplace.size() != NULL) {
        j = 0;
        cout << "YES d" << endl;
        for (int i = 0; i < dreturnplace.size(); i++) {
            //cout << "1: " << dreturnplace[i].first << "2: " << dreturnplace[i].second;
            glColor3f(drecord[j], drecord[j+1], drecord[j+2]);
            mouseMove(dreturnplace[i].first, dreturnplace[i].second);
            j += 3;
        }
        j = 0;
    }else cout << "NO d" << endl;
    if (preturnplace.size() != NULL) {
        j = 0;
        cout << "YES p" << endl;
        for (int i = 0; i < preturnplace.size(); i+=2) {
            glColor3f(precord[j], precord[j + 1], precord[j + 2]);
            Bresenham(preturnplace[i].first, preturnplace[i].second, preturnplace[i + 1].first, preturnplace[i + 1].second);
            j += 3;
        }
        j = 0;
    }else cout << "NO p" << endl;
    if (oreturnplace.size() != NULL) {
        j = 0;
        cout << "YES o" << endl;
        for (int i = 0; i < oreturnplace.size(); i+=2) {
            glColor3f(orecord[j], orecord[j + 1], orecord[j + 2]);
            Bresenham_O(oreturnplace[i].first, oreturnplace[i].second, oreturnplace[i + 1].first, oreturnplace[i + 1].second);
            j += 3;
        }
        j = 0;
    }else cout << "NO o" << endl;
    dreturnplace.clear();
    drecord.clear();
    lreturnplace.clear();
    lrecord.clear();
    preturnplace.clear();
    precord.clear();
    oreturnplace.clear();
    orecord.clear();
}




