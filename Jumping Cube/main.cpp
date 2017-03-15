//  This is COMP 410 - 510 Assigment 1
//  Author: Ahmet Can Turgut - 40616
//  Bouncing Ball - Cube
//  Spring 2017 - Koc Unviversity - CE
//  Skeleton code from spinning cube from Angel's Book...
//  Sphere and Cube code taken from angels book and edited according to needs...
//  This code works in ios 10.8 and Below otherwise some methods depracated...

#include <iostream>
#include "Angel.h" // Go to this web page "https://www.cs.unm.edu/~angel/BOOK/INTERACTIVE_COMPUTER_GRAPHICS/SIXTH_EDITION/CODE/include/Angel.h"

// Initilizing Variables ---------------------------------------------------------------------------------------------------------------------------------

typedef vec4  color4;
typedef vec4  point4;

bool isCube = true; // Is cube selected or NOT..

// Movement Related Vectors Defined

vec3 location(0.0,0.8,0.0);
vec3 velocity(0.0,0.0000001,0.0);
vec3 accelaration(0.0,0.00000001,0.0);
vec4 myWhite(1.0, 0.0, 0.0, 0.0);
vec4 myColor = myWhite;

// Menu Related Inits..

static int window;
static int menu_id;
static int submenu_id;
static int submenu_id2;
static int submenu_id3;
static int valueMenu = 0;

// ..

int colorSelector = 0;

// View related inits..

enum { Xaxis   = 0,
       Yaxis   = 1,
       Zaxis   = 2,
       NumAxes = 3 };

int Axis = Xaxis;
int Zmeter = Zaxis;

GLfloat Theta[NumAxes] = { 0.0, -20, 20};
GLfloat aspect;
GLuint  ModelView, Projection;
GLuint  program;

// Color method initilized...

void colorChanger(std::string);

// Cube -----------------------------------------------------------------------
// Cube Variables

const int NumVerticesCube = 36;

point4 pointsCube[NumVerticesCube];
color4 colorsCube[NumVerticesCube];

int IndexCube = 0;
double sizeCube = 1.0;

point4 vertices[8] = { // Create Cube Vertex "8"

    point4(-0.1, -0.1,  0.1, sizeCube),
    point4(-0.1,  0.1,  0.1, sizeCube),
    point4( 0.1,  0.1,  0.1, sizeCube),
    point4( 0.1, -0.1,  0.1, sizeCube),
    point4(-0.1, -0.1, -0.1, sizeCube),
    point4(-0.1,  0.1, -0.1, sizeCube),
    point4( 0.1,  0.1, -0.1, sizeCube),
    point4( 0.1, -0.1, -0.1, sizeCube)
};


//----------------------------------------------------------------------------
// Only one type of color setted. In spinning cube 8 diffrent color was setted.
// Unncessary codes were deleted above this part... Check spining cube example !.

void quad(int a, int b, int c, int d){ // Locate and Colirized Each Vertex

    colorsCube[IndexCube] = myColor;
    pointsCube[IndexCube] = vertices[a];
    IndexCube++;
    colorsCube[IndexCube] = myColor;
    pointsCube[IndexCube] = vertices[b];
    IndexCube++;
    colorsCube[IndexCube] = myColor;
    pointsCube[IndexCube] = vertices[c];
    IndexCube++;
    colorsCube[IndexCube] = myColor;
    pointsCube[IndexCube] = vertices[a];
    IndexCube++;
    colorsCube[IndexCube] = myColor;
    pointsCube[IndexCube] = vertices[c];
    IndexCube++;
    colorsCube[IndexCube] = myColor;
    pointsCube[IndexCube] = vertices[d];
    IndexCube++;
}

//----------------------------------------------------------------------------

void drawCube(){ // Combine Vertex

    quad(1, 0, 3, 2);
    quad(2, 3, 7, 6);
    quad(3, 0, 4, 7);
    quad(6, 5, 1, 2);
    quad(4, 5, 6, 7);
    quad(5, 4, 0, 1);

}

// SPHARE ------------------------------------------------------------------------------------------

// Sphere Variables

const int NumTriangles        = 1024;
const int NumVerticesSphare   = 3 * NumTriangles;

point4 pointsSp[NumVerticesSphare];
vec3   normalsSp[NumVerticesSphare];
color4 colorSp[NumVerticesSphare];

int IndexSphere = 0;

// Creating Triangle and Color Assign ----------

// I slightly understand this code, it is hard to understand
// But triangle class recursivly called and 1024*3 verticies were createde


void triangle( const point4& a, const point4& b, const point4& c ){

    vec3  normal = normalize(cross(b - a, c - b));

    normalsSp[IndexSphere] = normal;
    colorSp[IndexSphere] = myColor; // Added code for color
    pointsSp[IndexSphere] = a;
    IndexSphere++;

    normalsSp[IndexSphere] = normal;
    colorSp[IndexSphere] = myColor; // Added Code for color
    pointsSp[IndexSphere] = b;
    IndexSphere++;

    normalsSp[IndexSphere] = normal;
    colorSp[IndexSphere] = myColor; // Added Code For Color
    pointsSp[IndexSphere] = c;
    IndexSphere++;
}

// Sphare Related Codes ----------------------------------------------------------------------------

double sizeSP = 10.0;

point4 unit( const point4& p ){

    float len = p.x*p.x + p.y*p.y + p.z*p.z;
    point4 t;

    if ( len > DivideByZeroTolerance ) {
        t = p / sqrt(len);
        t.w = sizeSP; // Optimum value was assigned
    }

    return t;
}

void divide_triangle( const point4& a, const point4& b, const point4& c, int count ){

    if ( count > 0 ) {

        point4 v1 = unit( a + b );
        point4 v2 = unit( a + c );
        point4 v3 = unit( b + c );
        divide_triangle(  a, v1, v2, count - 1 );
        divide_triangle(  c, v2, v3, count - 1 );
        divide_triangle(  b, v3, v1, count - 1 );
        divide_triangle( v1, v3, v2, count - 1 );

    }else{
        triangle( a, b, c );
    }
}

void drawSphare(int count){

    point4 v[4] = {

        vec4( 0.0, 0.0, 1.0, 100.0 ), // w index were changed other wise werd triangles occured best option selected "100.0"
        vec4( 0.0, 0.942809, -0.333333, 100.0 ),
        vec4( -0.816497, -0.471405, -0.333333, 100.0 ),
        vec4( 0.816497, -0.471405, -0.333333, 100.0 )
    };

    divide_triangle( v[0], v[1], v[2], count );
    divide_triangle( v[3], v[2], v[1], count );
    divide_triangle( v[0], v[3], v[1], count );
    divide_triangle( v[0], v[2], v[3], count );
}

// INIT CODE -----------------------------------------------------------------------------------------

// Starts with Cube
// Shader connection

void init(){ // From Angels Book and Class Code, Shader Related Stuffs Handled...

    drawCube();

    GLuint vao;
    glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArrayAPPLE(vao);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointsCube) + sizeof(colorsCube), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pointsCube), pointsCube);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(pointsCube), sizeof(colorsCube), colorsCube);

    program = InitShader("vshader.glsl", "fshader.glsl");

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(pointsCube)));

    ModelView = glGetUniformLocation(program, "ModelView");
    Projection = glGetUniformLocation(program, "Projection");

    glUseProgram(program);

    mat4 projection;
    projection = Ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0); // BG Color White Init...
}

// BUFFER RECALL for CUBE and SPHERE -------------------------------------------------------------------------------------

void resetObjectCube(){
    // Angels Book... And Class Example Combined...

    isCube = true; // Cube Related Stuffs Start
    IndexCube = 0; // Vertex Index RESET
    drawCube();    // ReDraw Cube

    GLuint vao;
    glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArrayAPPLE(vao);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointsCube) + sizeof(colorsCube), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pointsCube), pointsCube);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(pointsCube), sizeof(colorsCube), colorsCube);

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(pointsCube)));

}

void resetObjectSphare(){
    // Angels Book... And Class Example Combined...
    
    isCube = false;  // Cube Related Stuffs Stop
    IndexSphere = 0; // Vertex Index RESET
    drawSphare(4);   // ReDraw Sphere

    GLuint vao;
    glGenVertexArraysAPPLE(1, &vao);
    glBindVertexArrayAPPLE(vao);
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointsSp) + sizeof(colorSp), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pointsSp), pointsSp);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(pointsSp), sizeof(colorSp), colorSp);

    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(pointsSp)));

}

// DISPLAY ACTIONS ----------------------------------------------------------------------------

void display(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mat4  model_view = (Scale(1.0, 1.0, 1.0) * Translate(location) *
                        RotateX(Theta[Xaxis]) *
                        RotateY(Theta[Yaxis]) *
                        RotateZ(Theta[Zaxis])); // Shader Connection Location Handeled In Here !

    glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view);

    if(isCube){
        glDrawArrays(GL_TRIANGLES, 0, NumVerticesCube); // Shader Connection Shape Cube Handeled In Here !

    }else{
        glDrawArrays(GL_TRIANGLES, 0, NumVerticesSphare); // Shader Connection Shape Sphare Handeled In Here !
    }

    glutSwapBuffers();

}

// TIMER ACTIONS ----------------------------------------------------------------------------

static void Timer(int n) { // Gravity Related Codes...

    if(location.y <= -0.8 ){ // Border Bottom
        velocity = vec3 (0.0,-velocity.y + 0.00000001,0.0);
    }

    if(location.y >= 0.8 ){ // Border Top
        velocity = vec3 (0.0, -velocity.y,0.0);
    }
    if(location.y <-0.8){ // Bottom Stop
        location.y = -0.8;
    }

    velocity.operator+=(accelaration); // Gravity Handled

    accelaration.y = 0.001;

    location.operator-=(velocity); // Velocity Handled

    glutTimerFunc(1, Timer, 0);
    glutPostRedisplay();
}

void idle(void) {
    glutPostRedisplay(); // Useless...
}

void colorChanger(std::string k);

// KEYBOARD ACTIONS ----------------------------------------------------------------------------

void keyboard(unsigned char key, int x, int y) { // Keyboard Related Operations PRESS H During to Exevution

    if (key == 'Q' | key == 'q') {
        exit(0);
    }

    if (key == 'w' |key =='W') {

        if(velocity.y > 0){
            velocity = vec3 (0.0,velocity.y + 0.01,0.0);

        }else if(velocity.y < 0){
            velocity = vec3 (0.0,velocity.y - 0.01,0.0);
        }
    }

    if (key == 'H' |key =='h') {

        printf("Instruction \n");
        printf("Left Click Open Menu \n");
        printf("w faster \n");
        printf("s slower  \n");
        printf("o init position  \n");
        printf("q exit from program \n");
        printf("a - d rotate (EXTRA EVENT) \n");
        printf("m - n fill and line mode \n");
        printf("z - x change shape \n");
    }

    if (key == 'S'|key=='s') {

        if(velocity.y > 0){
            velocity = vec3 (0.0,velocity.y - 0.01,0.0);

        }else if (velocity.y < 0){
            velocity = vec3 (0.0,velocity.y + 0.01,0.0);
        }
    }

    if (key == 'O'|key=='o') {
        location = vec3(0.0,0.8, 0.0);
        velocity = vec3(0.0,0.01, 0.0);
    }

    if (key == 'A'|key=='a') {
        Theta[Axis] += 4.0;
    }

    if (key == 'D'|key=='d') {
        Theta[Axis] -= 4.0;
    }
    
    if (key == '3') {
        Theta[Zmeter] += 4.0;
    }

    if (key == '1') {
        Theta[Zmeter] -= 4.0;
    }

    if (key == 'M'|key=='m') {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (key == 'N'|key=='n') {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    if (key == 'z'|key=='Z') {
        resetObjectCube();
        glutPostRedisplay();
    }
    
    if (key == 'x'|key=='X') {
        resetObjectSphare();
        glutPostRedisplay();
    }
    
    if (key == 'b'|key=='B') {
        if(isCube){
            sizeCube = sizeCube + 0.1;
            for (int i = 0; i< 8; i++) {
                vertices[i].w = sizeCube;
            }
            resetObjectCube();
        }else{
            sizeSP = sizeSP + 0.1;
            resetObjectSphare();
        }
    }
    
    if (key == 'v'|key=='V') {
        if(isCube){
            sizeCube = sizeCube - 0.1;
            for (int i = 0; i< 8; i++) {
                vertices[i].w = sizeCube;
            }
            resetObjectCube();
        }else{
            sizeSP = sizeSP - 0.1;
            resetObjectSphare();
        }
    }
    
    if (key == 'r'|key=='R') {
        
        if(colorSelector == 0){
            colorChanger("blue");
            colorSelector++;
        
        }else if(colorSelector == 1){
            colorChanger("red");
            colorSelector++;
        
        }else if(colorSelector == 2){
            colorChanger("green");
            colorSelector++;
        
        }else if(colorSelector == 3){
            colorChanger("yellow");
            colorSelector++;
    
        }else if(colorSelector == 4){
            colorChanger("black");
            colorSelector = 0;
        }
        
        glutPostRedisplay();
    }
}

// MENU MENU ACTIONS ----------------------------------------------------------------------------

void menu(int num){ // Menu Options Handled

    if(num == 0){
        glutDestroyWindow(window);
        exit(0);

    }else if(num == 5){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Line Drawing "Keyboard M"

    }else if(num == 6){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Fill Drawing "Keyboard N"

    }else if(num == 3){
        colorChanger("blue"); // BLUE

    }else if(num == 4){
        colorChanger("red"); // RED

    }else if(num == 7){
        colorChanger("green");

    }else if(num == 8){
        colorChanger("yellow");
        
    }else if(num == 9){
        colorChanger("white");
        glClearColor(0.0, 0.0, 0.0, 1.0); // Also Back Groudn Change

    }else if(num == 10){
        colorChanger("black");
        glClearColor(1.0, 1.0, 1.0, 1.0); // Also Back Groudn Change

    }else if(num == 11){  // CUBE DRAW
        resetObjectCube();
        glutPostRedisplay();

    }else if(num == 2){  // SPHARE DRAW
        resetObjectSphare();
        glutPostRedisplay();

    }else{
        valueMenu = num;
    }

    glutPostRedisplay(); // Re Call Display Method.
}

void colorChanger(std::string k){ // Color Conditions...

    if(k == "blue"){

        vec4 myBlue(0.0, 0.0, 1.0, 1.0);
        myColor = myBlue;

        if(isCube){
            resetObjectCube();
        }else{
            resetObjectSphare();
        }

    }else if(k == "red"){

        vec4 myRed(1.0, 0.0, 0.0, 1.0);
        myColor = myRed;

        if(isCube){
            resetObjectCube();
        }else{
            resetObjectSphare();
        }

    }else if(k == "yellow"){

        vec4 myYellow(1.0, 1.0, 0.0, 1.0);
        myColor = myYellow;

        if(isCube){
            resetObjectCube();
        }else{
            resetObjectSphare();
        }

    }else if(k == "green"){

        vec4 myGreen(0.0, 1.0, 0.0, 1.0);
        myColor = myGreen;

        if(isCube){
            resetObjectCube();
        }else{
            resetObjectSphare();
        }


    }else if(k == "white"){

        vec4 myWhite2(1.0, 1.0, 1.0, 1.0);
        myColor = myWhite2;

        if(isCube){
            resetObjectCube();
        }else{
            resetObjectSphare();
        }

    }else if(k == "black"){

        vec4 myBlack(0.0, 0.0, 0.0, 1.0);
        myColor = myBlack;

        if(isCube){
            resetObjectCube();
        }else{
            resetObjectSphare();
        }
    }
}

void createMenu(void){ // Creating Menu, Class Slides were used...

    submenu_id3 = glutCreateMenu(menu);
    glutAddMenuEntry("wireframe", 5);
    glutAddMenuEntry("solid", 6);
    submenu_id2 = glutCreateMenu(menu);
    glutAddMenuEntry("Blue", 3);
    glutAddMenuEntry("Red", 4);
    glutAddMenuEntry("Green",7);
    glutAddMenuEntry("Yellow",8);
    glutAddMenuEntry("White", 9);
    glutAddMenuEntry("Black", 10);
    submenu_id = glutCreateMenu(menu);
    glutAddMenuEntry("Sphere", 2);
    glutAddMenuEntry("Square", 11);
    menu_id = glutCreateMenu(menu);
    glutAddSubMenu("Object type", submenu_id);
    glutAddSubMenu("Drawing mode", submenu_id3);
    glutAddSubMenu("Color", submenu_id2);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


// RESHAPE ----------------------------------------------------------------------------

void reshape( int width, int height ){ // Taken from angels sphere example Appendix emxaple 7.

    glViewport( 0, 0, width, height );
    GLfloat left = -1.0, right = 1.0;
    GLfloat top = 1.0, bottom = -1.0;
    GLfloat zNear = -40.0, zFar = 40.0;
    GLfloat aspect = GLfloat(width)/height;

    if (aspect > 1.0) {
        
        left *= aspect;
        right *= aspect;
        
    }else{
        top /= aspect;
        bottom /= aspect;
    }

    mat4 projection = Ortho(left, right, bottom, top, zNear, zFar );
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
}

// MAIN ----------------------------------------------------------------------------

int main(int argc, char **argv){ // Taken From Class Exapmle

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize( 512, 512 );
    glutCreateWindow("Bouncing Ball - Ass 1 - 0040616");
    init();
    createMenu();
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutReshapeFunc( reshape );
    glutKeyboardFunc(keyboard);
    
    Timer(1);
    glutMainLoop();
    return 0;
}
