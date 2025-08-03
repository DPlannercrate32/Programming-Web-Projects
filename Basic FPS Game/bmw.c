
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#define WALKFILE   "walk1.txt"
#define MAPFILE    "map.txt"

#define DEGRAD        57.295779513
#define K           1024

#define CT_FLOOR       0
#define CT_EAST        1
#define CT_NORTH       2
#define CT_WEST        3
#define CT_SOUTH       4
#define CT_WALL        9

#define TOOS(X)     ((X) < NEAR)
#define TOOB(X)     ((X) > (CELLSIZE-NEAR))

#define NEAR           1.0
#define CELLSIZE       5.0
#define MSIZ          21
#define WSIZ         105.0
#define FUDGE          0.2

#define WALLHGT        4.0
#define MAXFUDGE      25
#define NBOB          2 

#define EXPTICKS      15

#define MAXTICKS      60
#define NSLIDES        8
#define FPS            1 

typedef
  unsigned char
uchar;

typedef struct viewer {
  GLfloat x,y,z;
  GLfloat theta, phi;
  GLfloat vx,vy,vz;
} VIEWER;

typedef struct bullet {
  int flag;
  int counter;
  VIEWER dir;
} BULLET;

typedef struct monstertype {
  int fall,nomore;
  GLfloat lowerleglen, upperleglen, bodylen, headrad;
  GLfloat x,y,z,fx,fy,fz,mx,mz;
  GLfloat heading, falling;
  GLfloat leftleg,rightleg;
  GLfloat leftankle,rightankle;
  int nslides, fps;
} MONSTER;


typedef struct walkdata {
  GLfloat leftleg[NSLIDES];
  GLfloat rightleg[NSLIDES];
  GLfloat leftankle[NSLIDES];
  GLfloat rightankle[NSLIDES];
  GLfloat height[NSLIDES];
  GLfloat ds[NSLIDES];
  int fps;
} WALK;

uchar map[MSIZ][MSIZ];

int automode,score,kills,missed;
float health;   
GLuint walltex, ceilingtex;

GLfloat pos0[] = {  1.0,  3.0,  4.0,  1.0};
GLfloat pos1[] = { -1.0,  3.0,  4.0,  1.0};
GLfloat amb[] =  {  0.5,  0.5,  0.5,  1.0};
GLfloat dif[] =  {  0.5,  0.5,  0.5,  1.0};
GLfloat spe[] =  {  0.9,  0.9,  0.9,  1.0};

GLfloat matamb[] = {0.30,  0.30,  0.30,  1.0};
GLfloat matdif[] = {0.50,  0.50,  0.50,  1.0};
GLfloat matspe[] = {0.10,  0.10,  0.10,  1.0};

GLfloat monamb[] = {0.60,  0.10,  0.10,  1.0};
GLfloat mondif[] = {0.10,  0.10,  0.10,  1.0};
GLfloat monspe[] = {0.10,  0.10,  0.80,  1.0};

GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
GLfloat red[] = {1.0, 0.4, 0.4, 1.0};

GLfloat objamb1[] = {0.00,  0.00,  0.00,  1.0};
GLfloat objdif1[] = {0.00,  0.00,  0.00,  1.0};
GLfloat objspe1[] = {0.00,  0.00,  0.00,  1.0};

GLfloat objamby[] = {0.50,  0.50,  0.00,  1.0};
GLfloat objdify[] = {0.50,  0.50,  0.00,  1.0};
GLfloat objspey[] = {0.50,  0.50,  0.00,  1.0};

GLfloat objambo[] = {0.50,  0.10,  0.00,  1.0};
GLfloat objdifo[] = {0.50,  0.10,  0.00,  1.0};
GLfloat objspeo[] = {0.50,  0.10,  0.00,  1.0};

GLfloat objambg[] = {0.00,  0.20,  0.00,  1.0};
GLfloat objdifg[] = {0.00,  0.20,  0.00,  1.0};
GLfloat objspeg[] = {0.00,  0.20,  0.00,  1.0};

GLfloat objambb[] = {0.00,  0.00,  0.20,  1.0};
GLfloat objdifb[] = {0.00,  0.00,  0.20,  1.0};
GLfloat objspeb[] = {0.00,  0.00,  0.20,  1.0};

GLfloat objambw[] = {1.00,  1.00,  1.00,  1.0};
GLfloat objdifw[] = {1.00,  1.00,  1.00,  1.0};
GLfloat objspew[] = {1.00,  1.00,  1.00,  1.0};

GLfloat objambr[] = {0.20,  0.00,  0.00,  1.0};
GLfloat objdifr[] = {0.20,  0.00,  0.00,  1.0};
GLfloat objsper[] = {0.20,  0.00,  0.00,  1.0};

GLfloat objamb[] = {0.60,  0.10,  0.10,  1.0};
GLfloat objdif[] = {0.10,  0.10,  0.10,  1.0};
GLfloat objspe[] = {0.10,  0.10,  0.80,  1.0};

GLUquadric *body;
MONSTER bob[NBOB];
WALK walk1;
BULLET ping;

double pov;
VIEWER moi;

void display();
void display2();
void animate();
void animate_bullets();
void reshape(int w, int h);
void arrows(int c, int x, int y);
void keyboard(unsigned char c, int x, int y);
//Colors
void blue();
void red1();
//Colors
void init();
void update_viewer();

void building();
void bullets();
void monster(MONSTER *p);
void hitbob(VIEWER *p);
void radar();
void bazooka();
void position();
void bobposition(int i);
void drawString(char *s); 
void exitmenu(int selection);
int numbobs = NBOB;
int get_cell_type(GLfloat x, GLfloat z);
float px, pz;
GLuint mainwin, subwin;
int menu;
int main(int argc, char *argv[])
{
  //GLuint mainwin, subwin;
  pov = (argc == 1) ? 60.0 : atof(argv[1]);
  glutInit(&argc, argv);
  glutInitWindowSize(800,600);
  glutInitWindowPosition(400,100);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  mainwin = glutCreateWindow("BoiLeRPLaTe");
  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutSpecialFunc(arrows);
  glutReshapeFunc(reshape);
  glutIdleFunc(animate);
  
  init();

  subwin = glutCreateSubWindow(mainwin, 0,450, 800,150);
  //display2();
  glutDisplayFunc(display2);
  menu = glutCreateMenu(exitmenu);
  glutAddMenuEntry("Exit", 0);
  glutAddMenuEntry("hard mode", 1);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutSetMenu(menu);

  glutMainLoop();
}
void start_monster(MONSTER *p)
{
  p->fps = lrand48() % FPS;
  p->nslides = 0;
}
void keyboard(unsigned char c, int x, int y)
{
  int i;
  MONSTER *p;
  switch(c){
    case 27:  /* escape key */
      //kill(getpid(),9);
      //exit(0);
      glutLeaveMainLoop();
    case 'w':
      automode = 1 - automode;
      if(automode){
        for(i=0;i<NBOB;i++)
          start_monster(bob+i);
      }
      break;
    case ' ':
      ping.flag = 1;
      ping.counter = 0;
      ping.dir = moi;
      ping.dir.y /= 2.0;
      break;

  }
  update_viewer();
  glutPostRedisplay();
}
void move_viewer(int dir)
{
  GLfloat tx,tz;
  int k;

  if(dir > 0){
    tx = moi.x + moi.vx;
    tz = moi.z + moi.vz;
    if(get_cell_type(tx,tz) == CT_FLOOR){
      moi.x += moi.vx;
      moi.z += moi.vz;
      //px += 0.002;
      position();
    } else {
      k = 0;
      do {
        if(++k == MAXFUDGE){
          fprintf(stderr,"maxfudge in move_viewer\n");
          break;
        }
        tx = moi.x + ((drand48() - 0.5)/10.0);
        tz = moi.z + ((drand48() - 0.5)/10.0);
      } while(get_cell_type(tx,tz) != CT_FLOOR);
      moi.theta += (drand48() - 0.5);
      moi.x = tx;
      moi.z = tz;
    }
  } else {
    tx = moi.x - moi.vx;
    tz = moi.z - moi.vz;
    if(get_cell_type(tx,tz) == CT_FLOOR){
      moi.x -= moi.vx;
      moi.z -= moi.vz;
      position();
    } else {
      do {
        k = 0;
        if(++k == MAXFUDGE){
          fprintf(stderr,"maxfudge in move_viewer\n");
          break;
        }
        tx = moi.x + ((drand48() - 0.5)/10.0);
        tz = moi.z + ((drand48() - 0.5)/10.0);
      } while(get_cell_type(tx,tz) != CT_FLOOR);
      moi.theta += (drand48() - 0.5);
      moi.x = tx;
      moi.z = tz;
    }
  }
  pos1[0] = moi.x;
  pos1[1] = moi.y;
  pos1[2] = moi.z;
  glLightfv(GL_LIGHT0, GL_POSITION, pos1);
}
void arrows(int c, int x, int y)
{
  switch(c){
    case GLUT_KEY_LEFT:
      moi.theta -= 0.1;
      break;
    case GLUT_KEY_UP:
      move_viewer( 1);
      break;
    case GLUT_KEY_DOWN:
      move_viewer(-1);
      break;
    case GLUT_KEY_RIGHT:
      moi.theta += 0.1;
      break;
    case GLUT_KEY_PAGE_UP:
      moi.y += 0.1;
      break;
    case GLUT_KEY_PAGE_DOWN:
      moi.y -= 0.1;
      break;
  }
  update_viewer();
  glutPostRedisplay();
}
void reshape(int w, int h)
{
  glViewport(0,0,w,h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(pov, (GLdouble)w/(GLdouble)h, 0.001, 90.0);
  glMatrixMode(GL_MODELVIEW);
}
void init_monster(MONSTER *p)
{
  memset(p,0,sizeof(MONSTER));
  p->fx = 1.0;
  p->fy = 0.0;
  p->fz = 0.0;
  p->falling = -90.0; 
  p->lowerleglen = 0.5;
  p->upperleglen = 0.5;
  p->bodylen = 0.5 + drand48() * 1.0;
  p->headrad = 0.1 + drand48() * 0.4;
  p->heading = 360.0 * drand48(); 
  p->y = 1.0;
  do {
    p->x = drand48() * WSIZ;
    p->z = drand48() * WSIZ;
  } while(get_cell_type(p->x,p->z) != CT_FLOOR);
}
void read_map(uchar map[MSIZ][MSIZ])
{
  FILE *fd;
  int i,j,k;

  fd = fopen(MAPFILE,"r");
  if(!fd){
    fprintf(stderr,"Map file '%s' missing?\n", MAPFILE);
    exit(0);
  }
  for(i=0;i<MSIZ;i++)
    for(j=0;j<MSIZ;j++){
      fscanf(fd,"%1d", &k);
      map[j][MSIZ-1-i] = k;
    }
  fclose(fd);
}
void read_walk(WALK *w)
{
  FILE *fd;
  int i;

  fd = fopen(WALKFILE,"r");
  if(!fd){
    fprintf(stderr,"Walk file '%s' missing?\n", WALKFILE);
    exit(0);
  }
  for(i=0;i<NSLIDES;i++)
    fscanf(fd,"%f %f %f %f %f %f\n",
      &w->leftleg[i],
      &w->rightleg[i],
      &w->leftankle[i],
      &w->rightankle[i],
      &w->height[i],
      &w->ds[i]);
  fclose(fd);
  w->fps = FPS;
}
void init()
{
  int i,j;
  MONSTER *p;

  srand48(getpid());
  moi.x =  7.5;
  moi.y =  1.0;
  moi.z =  7.5;
  moi.theta = M_PI/4.0;
  moi.phi = 0.0;
  px = -0.20; 
  pz = 0.0;
  pos1[0] = moi.x;
  pos1[1] = moi.y;
  pos1[2] = moi.z;
  glLightfv(GL_LIGHT0, GL_POSITION, pos1);

  automode = 1;
  score = 0;
  kills = 0;
  missed = 0;
  health = 100.00;  

  update_viewer();

  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHT0);

  glLightfv(GL_LIGHT0, GL_POSITION, pos1);
  glLightfv(GL_LIGHT0, GL_AMBIENT,  amb);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  dif);
  glLightfv(GL_LIGHT0, GL_SPECULAR, spe);

  body = gluNewQuadric();
  gluQuadricDrawStyle(body, GLU_FILL);

  read_walk(&walk1);
  read_map(map);
  walltex = readppm("wall.ppm");
  ceilingtex = readppm("ceiling.ppm");

  for(i=0;i<NBOB;i++)
    init_monster(bob+i);
  memset(&ping, 0, sizeof(BULLET));
  printf("done with init\n");
}
int get_cell_type(GLfloat x, GLfloat z)
{
  int ix,iz;

  ix = (int)(x / CELLSIZE);
  iz = (int)(z / CELLSIZE);
  return map[ix][iz];
}
unsigned int near_wall(GLfloat x, GLfloat z)
{
  unsigned int flags;
  int ix,iz;
  GLfloat rx,rz;

  ix = (int)(x / CELLSIZE);
  iz = (int)(z / CELLSIZE);
  rx = fmod(x,CELLSIZE);
  rz = fmod(z,CELLSIZE);
  flags = 0;
  if((map[ix+1][iz] != CT_FLOOR) && (rx > CELLSIZE - NEAR)){
    flags |= 1;
  } else if((map[ix-1][iz] != CT_FLOOR) && (rx < NEAR)){
    flags |= 4;
  }
  if((map[ix][iz+1] != CT_FLOOR) && (rz > CELLSIZE - NEAR)){
    flags |= 2;
  } else if((map[ix][iz-1] != CT_FLOOR) && (rz < NEAR)){
    flags |= 8;
  }
  if(map[ix-1][iz-1] && TOOS(rx) && TOOS(rz)){ flags |= 12; }
  if(map[ix-1][iz+1] && TOOS(rx) && TOOB(rz)){ flags |=  6; }
  if(map[ix+1][iz-1] && TOOB(rx) && TOOS(rz)){ flags |=  9; }
  if(map[ix+1][iz+1] && TOOB(rx) && TOOB(rz)){ flags |=  3; }

  return flags;
}
void animate()
{
  MONSTER *p;
  GLfloat tx,tz;
  int i,j,k;
  unsigned int f;

  animate_bullets();

  for(i=0;i<NBOB;i++){
     if(!automode){
       glutPostRedisplay();
       return;
     }
  }
  /*for(i=0;i<NBOB;i++){
     if(p->fall == 0);{
       glutPostRedisplay();
       return;
     } 
  } */ 
  for(i=0;i<NBOB;i++){
    p = bob + i;
    p->fps++;
    if(p->fps == walk1.fps && !bob[i].fall){
      if(get_cell_type(p->x,p->z) != CT_FLOOR)
        fprintf(stderr,"Bob %d is weird.\n", i);
      tx = p->x + walk1.ds[p->nslides] * cos(p->heading/DEGRAD);
      tz = p->z + walk1.ds[p->nslides] * sin(p->heading/DEGRAD);
      f = near_wall(p->x,p->z);     
      switch(f){
        case  0: break;
        case  1: p->heading = 180.0; break;
        case  2: p->heading = 270.0; break;
        case  3: p->heading = 225.0; break;
        case  4: p->heading =   0.0; break;
        case  5:
        case  6: p->heading = 315.0; break;
        case  7:
        case  8: p->heading =  90.0; break;
        case  9: p->heading = 135.0; break;
        case 10:
        case 11:
        case 12: p->heading =  45.0; break;
        case 13:
        case 14:
        case 15: break;
      }
      if(f)
        p->heading += 90.0*(drand48() - 0.5);
      p->x += walk1.ds[p->nslides] * cos(p->heading/DEGRAD);
      p->z += walk1.ds[p->nslides] * sin(p->heading/DEGRAD);
      p->leftleg = walk1.leftleg[p->nslides];
      p->rightleg = walk1.rightleg[p->nslides];
      p->leftankle = walk1.leftankle[p->nslides];
      p->rightankle = walk1.rightankle[p->nslides];
      p->y = walk1.height[p->nslides];
      p->fps = 0;
      p->nslides++;
      if(p->nslides == NSLIDES){
        automode = 1;
        p->fps = 0;
        p->nslides = 0;
      }
    }
  }
  update_viewer();
  glutSetWindow(mainwin);
  glutPostRedisplay();
  glutSetWindow(subwin);
  glutPostRedisplay();
}
void update_viewer()
{
  MONSTER *p;
  int i; 
  int deg;
  deg = fabs((int)(moi.theta * DEGRAD) % 360);  
  double dif = 0;
  dif = fabs(bob->x - moi.x); 
  moi.vx = cos(moi.theta);
  moi.vz = sin(moi.theta);
  for(i = 0; i<NBOB; i++){
    //bobposition(bob, i);
    printf("MX  %.3lf\n", bob[i].mx); 
    if(fabs(bob[i].x - moi.x) >0 && fabs(bob[i].x - moi.x) <3.7&&fabs(bob[i].z - moi.z) >0 && fabs(bob[i].z - moi.z) <3.7){ 
       	    bob[i].heading = deg - 180;
            printf("Bob%d, has %.3lf degrees\n",i, bob[i].heading);
            //automode = 0; 
      } 
 
  }  

  for(i=0;i<NBOB;i++){
      if(fabs(bob[i].x - moi.x) >0 && fabs(bob[i].x - moi.x) <2.7&&fabs(bob[i].z - moi.z) >0 && fabs(bob[i].z - moi.z) <0.7&& bob[i].nomore == 0){
           health -= 0.7;
      }else{
            health -= 0.0; 

         }

   }  
  if(kills == NBOB){
     printf("Winner");
     //kill(getpid(),9);
      //exit(0);
      glutLeaveMainLoop();
  } 
  if(health <= 0){
     printf("Winner");
     //kill(getpid(),9);
      //exit(0);
     glutLeaveMainLoop();
  }

  printf("x%.3lf, z%.3lf\n", moi.x, moi.z);
  printf("dif%.3lf\n", dif);
  printf("Bobfps%d\n", bob->fps);
  printf("walkfps%d\n", walk1.fps);
  printf("flag%d\n", automode);  
  printf("vxdegree%.3lf\n", moi.vx);
  printf("vzdegree%.3lf\n", moi.vz);
  //printf("bobdegree%.3lf\n",bob->heading);
  printf("my degree %d\n", deg);

}
void display()
{
  int i,j,k,u,v,deg;
  char label[1000];
  
  deg = fabs((int)(moi.theta * DEGRAD) % 360 );

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  gluLookAt(moi.x, moi.y, moi.z,
            moi.x + moi.vx, moi.y + moi.vy, moi.z + moi.vz,
            0.0, 1.0, 0.0);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  matamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  matdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matspe);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 150.0);

  glBegin(GL_QUADS);
    glNormal3f(  0.0,-1.0,  0.0);   /* Ceiling */
    glVertex3f(  0.0, 0.0,  0.0);
    glVertex3f( WSIZ, 0.0,  0.0);
    glVertex3f( WSIZ, 0.0, WSIZ);
    glVertex3f(  0.0, 0.0, WSIZ);
  glEnd();
  glPushMatrix();
  glTranslatef(moi.x, moi.y, moi.z);
  glRotatef((-(moi.theta)*57.2957795),0.0, 1.0, 0.0);

  glTranslatef(0.7, 0.30, 0.3);
  glPushMatrix();
  glTranslatef(0.0, px, pz);
  blue();
  glutSolidSphere(0.0125, 12, 12);
  glPopMatrix();
  glPushMatrix();
  for(i=0; i<NBOB;i++){
    bobposition(i);
    red1();
    glPushMatrix(); 
    glTranslatef(0.0, bob[i].mx, bob[i].mz);
    if(bob[i].nomore>0)
       glTranslatef(7.0, 0.0, 0.0);

    glutSolidSphere(0.0060, 12, 12);
    glPopMatrix();
  }
  bazooka();
  glPopMatrix();
  radar();
  glPopMatrix(); 
  building();
  for(i=0;i<NBOB;i++){ 
   glPushMatrix(); 
   monster(bob + i);
   glPopMatrix();
  }
  bullets();

  glutSwapBuffers();
}
void rand_unit_vector(GLfloat v[])
{
  int i;

  for(i=0;i<3;i++)
    v[i] = drand48() - 0.5;
}
void explode()
{
  int i;
  GLfloat v[3];

  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 1.0);
  glLineWidth(4.0);

  glBegin(GL_LINES);
    for(i=0;i<10;i++){
      rand_unit_vector(v);
      glVertex3f(ping.dir.x, ping.dir.y, ping.dir.z);
      glVertex3f(ping.dir.x+v[0], ping.dir.y+v[1], ping.dir.z+v[2]);
    }
  glEnd();
}
void move_bullet()
{
  VIEWER *p;
  int i;
  p = &(ping.dir);
  p->x += p->vx/2.0;
  p->y += p->vy/2.0;
  p->z += p->vz/2.0;
  hitbob(p);
  if(get_cell_type(p->x,p->z) != CT_FLOOR){
    ping.flag = 2;
    ping.counter = 0;
    missed+=1; 
    if(score>0)
      score-=25; 
    //glutSetWindow(mainwin);
    //glutSetWindow(subwin);
 
    return;
  }
  for(i = 0; i<NBOB; i++){
     if(bob[i].fall){
        ping.flag = 2;
        ping.counter = 0;
       
     }

    //if(ping.flag == 2 && bob[i].nomore == 0)
      //       missed+=1;
  }
}

void animate_bullets()
{
  switch(ping.flag){
    case 0: return;
    case 1: move_bullet(); break;
    case 2: if(++ping.counter == EXPTICKS) ping.flag = 0; break;
  }
}
void bullets()
{
  if(ping.flag == 0)
    return;
  if(ping.flag == 2){
    explode();
    return;
   }
  
  /*red[0] = drand48();
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,red);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,red);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 1.0); 
  glLineWidth(4.0); */ 

  /*glBegin(GL_LINES);
    glVertex3f(ping.dir.x, ping.dir.y, ping.dir.z);
    glVertex3f(ping.dir.x+ping.dir.vx/4.0,
               ping.dir.y+ping.dir.vy/4.0,
               ping.dir.z+ping.dir.vz/4.0);
  glEnd(); */ 
  //glTranslatef(ping.dir.x, ping.dir.y, ping.dir.z);
  //glPushMatrix();
  glTranslatef(ping.dir.x, ping.dir.y, ping.dir.z);
 /* glRotatef(-90.0, 1.0, 0.0, 0.0);
  glColor3f(0.5, 0.5, 0.5);
  glTranslatef(0.0, 7.0, 0.125);
  glScalef(0.01, 0.01, 0.01);
  gluCylinder(body, 3.7, 5.0, 2.2, 48, 6);
  glTranslatef(0.0, 0.00, 2.2);
  glColor3f(0.6, 0.0, 0.0);
  gluCylinder(body, 5.0, 3.65, 1.0, 48, 6);
  glScalef(1.27, 1.27, 1.0);*/ 

  //glutSolidSphere(3.0, 12, 12);
  glutSolidSphere(0.2, 12, 12);

  /*glColor3f(0.0, 0.0, 0.0);
  glTranslatef(0.35, 0.00, 3.0);
  glRotatef(90.0, 0.0, 1.0, 0.0);
  glScalef(0.3527, 0.3527, 1.0);
  glutSolidSphere(0.25, 12, 12);
  glTranslatef(0.00, 0.00, -0.7);
  glutSolidSphere(0.25, 12, 12);
  glScalef(1.0, 2.8527, 0.2527);
  glTranslatef(0.00, -0.35, 1.25);
  glutSolidSphere(0.25, 12, 12);
  glTranslatef(0.00, 0.7, 0.0);
  glutSolidSphere(0.25, 12, 12);
  glPopMatrix();  
  */
}
void monster(MONSTER *p)
{
  int i;
  glPushMatrix();

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  monamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  mondif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, monspe);
  glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS,10.0);

  glLineWidth(1.0);

  glTranslatef(p->x, 0.0, p->z);
  glRotatef(-p->heading, 0.0, 1.0, 0.0);
  //glRotatef(-90.0, 1.0, 0.0, 0.0);
  glRotatef(p->falling, p->fx, p->fy, p->fz);


/* torso and head*/
 glPushMatrix();

  glTranslatef(0.0, 0.0,0.5 + bob->y);
  glutSolidSphere(0.5, 12, 12);

  glTranslatef(0.45, 0.0, 0.1);
  glScalef(0.5, 1.3, 0.75);
  glutSolidSphere(0.30, 12, 12);
  glScalef(0.5, 1.0, 1.19);
  glTranslatef(0.00, 0.0, -0.17);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objamb1);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdif1);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspe1);

  glutSolidSphere(0.30, 12, 12);
  glTranslatef(0.63, 0.0, 0.17);
  glScalef(0.1, 0.133, 0.65);
  glutSolidSphere(0.30, 12, 12);

  glTranslatef(-3.73, 0.7, -0.17);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objamby);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdify);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspey);
  glutSolidSphere(0.30, 12, 12);

  glPushMatrix();
  glPushMatrix();
  glTranslatef(-0.05, -0.7, -0.455);
  glutSolidSphere(0.084, 12, 12);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objamb1);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdif1);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspe1);
  glTranslatef(0.0, -0.05, 0.05);
  glutSolidSphere(0.084, 12, 12);
  glTranslatef(0.0, 0.10, 0.0);
  glutSolidSphere(0.084, 12, 12);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objamby);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdify);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspey);
  glPopMatrix();
  glTranslatef(-0.05, -1.4, 0.0);
  glutSolidSphere(0.30, 12, 12);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objamb1);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdif1);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspe1);
  glTranslatef(0.3, 0.1, -0.28);
  glutSolidSphere(0.15, 12, 12);
  glPopMatrix();

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objamb1);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdif1);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspe1);

  glTranslatef(0.3, -0.1, -0.28);
  glutSolidSphere(0.15, 12, 12);

  //gluCylinder(body, 0.2, 0.3, 1.0, 12, 12);
  glPopMatrix();

/* legs */

  glPushMatrix();
  glPushMatrix();
  glTranslatef(0.0, 0.1, 1.0);
  if(p->nslides == 1){
    glTranslatef(0.55, 0.0, 0.5);
    glRotatef(7, 0.0, 1.0, 0.0);
  }

  if(p->nslides == 2){
    glTranslatef(0.30, 0.0, 0.19);
    glRotatef(-10, 0.0, 1.0, 0.0);
  }

  if(p->nslides == 5){
    glTranslatef(0.2, 0.0, 0.0);
    glRotatef(40, 0.0, 1.0, 0.0);
  }

  if(p->nslides == 6){
    glTranslatef(0.16, 0.0, 0.0);
    glRotatef(45, 0.0, 1.0, 0.0);
  }

  if(p->nslides == 7){
    glTranslatef(0.34, 0.0, -0.4);
    glRotatef(77, 0.0, 1.0, 0.0);
  }

  if(p->nslides == 0){
    glTranslatef(0.87, 0.0, -0.05);
    glRotatef(60, 0.0, 1.0, 0.0);
  }
   //ColorsRed
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspe);
   //ColorsRed
  glTranslatef(0.0, 0.3,-1.0);
  gluCylinder(body, 0.05, 0.05, 0.45, 12, 12);
  glPopMatrix();
  glRotatef(-180, 0.0, 1.0, 0.0);
  glTranslatef(0.0, 0.4, -1.0);
  glRotatef(p->rightleg, 0.0, 1.0, 0.0);
  //Green
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objambg);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdifg);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspeg);
  //Green
  glutSolidSphere(0.17, 12, 12);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspe);

  gluCylinder(body, 0.05, 0.05, 0.50, 12, 12);
  glTranslatef(0.0, 0.0, 0.5);
  //orange
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objambo);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdifo);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspeo);
  //orange
  glutSolidSphere(0.10, 12, 12);

  glPopMatrix();

  glPushMatrix();
  glPushMatrix();
  glTranslatef(0.0, -0.1, 1.0);

  if(p->nslides == 6){
    glTranslatef(0.30, 0.0, 0.19);
    glRotatef(-10, 0.0, 1.0, 0.0);
  }

  if(p->nslides == 5){
    glTranslatef(0.55, 0.0, 0.5);
    glRotatef(7, 0.0, 1.0, 0.0);

  }

  if(p->nslides == 4){
    glTranslatef(0.87, 0.0, -0.05);
    glRotatef(60, 0.0, 1.0, 0.0);
  }

  if(p->nslides == 3){
    glTranslatef(0.34, 0.0, -0.4);
    glRotatef(77, 0.0, 1.0, 0.0);
  }

  if(p->nslides == 2){
    glTranslatef(0.16, 0.0, 0.0);
    glRotatef(45, 0.0, 1.0, 0.0);
  }

  if(p->nslides == 1){
    glTranslatef(0.34, 0.0, -0.4);
    glRotatef(77, 0.0, 1.0, 0.0);
  }
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspe);

  glTranslatef(0.0, -0.3,-1.0);
  gluCylinder(body, 0.05, 0.05, 0.45, 12, 12);
  glPopMatrix();
  glRotatef(-180, 0.0, 1.0, 0.0);
  glTranslatef(0.0, -0.4, -1.0);
  glRotatef(p->leftleg, 0.0, 1.0, 0.0);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objambg);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdifg);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspeg);
  glutSolidSphere(0.17, 12, 12);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objamb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdif);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspe);
  gluCylinder(body, 0.05, 0.05, 0.50, 12, 12);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objambo);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdifo);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspeo);

  glTranslatef(0.0, 0.0, 0.5);
  glutSolidSphere(0.10, 12, 12);
  glPopMatrix();

  glPopMatrix();
}

void hitbob(VIEWER *p)
{
   //p = &(ping.dir);

   int i;
   for(i=0;i<NBOB;i++){
      printf("bob %d falling is %.3lf\n", i, bob[i].falling);
      printf("bob %d fall = %d\n", i, bob[i].fall);
      if(fabs(bob[i].x - p->x) >0 && fabs(bob[i].x - p->x) <1.7&&fabs(bob[i].z - p->z) >0 && fabs(bob[i].z - p->z) <0.70){
        bob[i].fall += 1;
        bob[i].fx = 1.0;
        bob[i].fy = 1.0;
        bob[i].fz = 0.0;
        bob[i].falling = 0;
        bob[i].nomore+=1;
        if(bob[i].nomore == 1){
           score+=100; 
           kills+=1; 
           numbobs-=1;
        }
        //glutSetWindow(subwin);
        if(bob[i].fall>0){
             while(bob[i].falling>90)
               bob[i].falling  -= 9;

           }
      }else{
            bob[i].fall = 0;
         }

   }

}
void radar()
{
 glPushMatrix(); 
 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objambw);
 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdifw);
 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspew);

 glRotatef(-90, 0.0, 0.0, 1.0);
 glBegin(GL_QUADS);
 glVertex3f(  0.0, 0.0,  0.0);
 glVertex3f( 0.20, 0.0,  0.0);
 glVertex3f( 0.20, 0.0, 0.20);
 glVertex3f(  0.0, 0.0, 0.20);
 glEnd(); 
 glPopMatrix();

}
void bazooka()
{
 glPushMatrix(); 
 glRotatef(90,0.0, 1.0, 0.0);
 glTranslatef(0.32, -0.80, 0.3);
 glRotatef(-20,1.0, 0.0, 0.0);
 
 gluCylinder(body, 0.30, 0.05, 1.0, 12, 12);
 glPopMatrix(); 
}
void blue()
{
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objambb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdifb);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objspeb);
}

void red1()
{
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,  objambr);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,  objdifr);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objsper);
}

void drawString(char *s)
{
  int i;
  for(i=0; i<strlen(s); i++)
     glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
}
void display2()
{
  int i,j,k,u,v, menu;
  char label[1000];
  /* Clear subwindow */
  glClearColor (0.25, 0.25, 0.25, 1.0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();


  glColor3f(1.0, 1.0, 1.0);
  sprintf(label, "Score: %d", score);
  glRasterPos2f(-0.90F, 0.50F);
  drawString(label);

  sprintf(label, "kills: %d", kills);
  glRasterPos2f(-0.90F, 0.10F);
  drawString(label);

  sprintf(label, "missed: %d", missed);
  glRasterPos2f(-0.90F, -0.30F);
  drawString(label);

  sprintf(label, "Health: %.3lf", health);
  glRasterPos2f(-0.90F, -0.70F);
  drawString(label);

  sprintf(label, "Space button = Shoot");
  glRasterPos2f(-0.60F, 0.10F);
  drawString(label);

  sprintf(label, "Directional Arrow Keys = Movement");
  glRasterPos2f(-0.60F, 0.50F);
  drawString(label);

  sprintf(label, "Defeat All Bobs to WIN!");
  glRasterPos2f(0.20F, 0.50F);
  drawString(label);

  sprintf(label, "And have a Good Chrismas Break!");
  glRasterPos2f(0.20F, 0.20F);
  drawString(label);

  sprintf(label, "Bobs Left: %d\n", numbobs);
  glRasterPos2f(0.20F, -0.10F);
  drawString(label);

  sprintf(label, "Try to Score 2500 Points");
  glRasterPos2f(0.20F, -0.50F);
  drawString(label);

  sprintf(label, "Move Arrow Cursor to Game Screen to Play If You cant move");
  glRasterPos2f(-0.30F, -0.90F);
  drawString(label);

  glutSwapBuffers ();
}
void exitmenu(int selection)
{
  if(selection == 0)
     glutLeaveMainLoop(); 
  if(selection == 1)
     health = 28;
}

void position()
{
 if(moi.x > 5.8 && moi.x < 15.0)
    px = -0.18; 
 else
    px = -0.20;
 if(moi.x > 15.0 && moi.x < 25.0)
    px = -0.16;

 if(moi.x > 25.0 && moi.x < 35.0)
    px = -0.14;
 
 if(moi.x > 35.0 && moi.x < 45.0)
    px = -0.12;
 
 if(moi.x > 45.0 && moi.x < 55.0)
    px = -0.10;
 
 if(moi.x > 55.0 && moi.x < 65.0)
    px = -0.08;
 
 if(moi.x > 65.0 && moi.x < 75.0)
    px = -0.06;

 if(moi.x > 75.0 && moi.x < 85.0)
    px = -0.04;

 if(moi.x > 85.0 && moi.x < 95.0)
    px = -0.02;

 if(moi.x > 95.0 && moi.x < 100.0)
    px = -0.00;

 //pz
 
 if(moi.z > 5.8 && moi.z < 15.0)
    pz = 0.02;
 else
    pz = 0.0;
 if(moi.z > 15.0 && moi.z < 25.0)
    pz = 0.04;

 if(moi.z > 25.0 && moi.z < 35.0)
    pz = 0.06;

 if(moi.z > 35.0 && moi.z < 45.0)
    pz = 0.08;

 if(moi.z > 45.0 && moi.z < 55.0)
    pz = 0.10;

 if(moi.z > 55.0 && moi.z < 65.0)
    pz = 0.12;

 if(moi.z > 65.0 && moi.z < 75.0)
    pz = 0.14;

 if(moi.z > 75.0 && moi.z < 85.0)
    pz = 0.16;

 if(moi.z > 85.0 && moi.z < 95.0)
    pz = 0.18;

 if(moi.z > 95.0 && moi.z < 100.0)
    pz = 0.20;

}
void bobposition(int i)
{
 if(bob[i].x > 5.8 && bob[i].x < 15.0)
    bob[i].mx = -0.18;
 else
    bob[i].mx = -0.20;
 if(bob[i].x > 15.0 && bob[i].x < 25.0)
    bob[i].mx = -0.16;

 if(bob[i].x > 25.0 && bob[i].x < 35.0)
    bob[i].mx = -0.14;

 if(bob[i].x > 35.0 && bob[i].x < 45.0)
    bob[i].mx = -0.12;

 if(bob[i].x > 45.0 && bob[i].x < 55.0)
    bob[i].mx = -0.10;

 if(bob[i].x > 55.0 && bob[i].x < 65.0)
    bob[i].mx = -0.08;

 if(bob[i].x > 65.0 && bob[i].x < 75.0)
    bob[i].mx = -0.06;

 if(bob[i].x > 75.0 && bob[i].x < 85.0)
    bob[i].mx = -0.04;

 if(bob[i].x > 85.0 && bob[i].x < 95.0)
    bob[i].mx = -0.02;

 if(bob[i].x > 95.0 && bob[i].x < 100.0)
    bob[i].mx = -0.00;

  //mz
 if(bob[i].z > 5.8 && bob[i].z < 15.0)
    bob[i].mz = 0.02;
 else
    bob[i].mz = 0.00;
 if(bob[i].z > 15.0 && bob[i].z < 25.0)
    bob[i].mz = 0.04;

 if(bob[i].z > 25.0 && bob[i].z < 35.0)
    bob[i].mz = 0.06;

 if(bob[i].z > 35.0 && bob[i].z < 45.0)
    bob[i].mz = 0.08;

 if(bob[i].z > 45.0 && bob[i].z < 55.0)
    bob[i].mz = 0.10;

 if(bob[i].z > 55.0 && bob[i].z < 65.0)
    bob[i].mz = 0.12;

 if(bob[i].z > 65.0 && bob[i].z < 75.0)
    bob[i].mz = 0.14;

 if(bob[i].z > 75.0 && bob[i].z < 85.0)
    bob[i].mz = 0.16;

 if(bob[i].z > 85.0 && bob[i].z < 95.0)
    bob[i].mz = 0.18;

 if(bob[i].z > 95.0 && bob[i].z < 100.0)
    bob[i].mz = 0.20;

}
void building()
{
  int i,j;
  GLfloat fx,fz;

  glBindTexture(GL_TEXTURE_2D, walltex);
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  for(i=0;i<MSIZ;i++){
    fx = CELLSIZE * i;
    for(j=0;j<MSIZ;j++){
      if(map[i][j] == CT_WALL){
        fz = CELLSIZE * j;
        glBegin(GL_QUADS);
          glNormal3f( 0.0, 0.0,-1.0);
          glTexCoord2f(0.0, 0.0);
          glVertex3f(fx, 0.0, fz);
          glTexCoord2f(0.0, 1.0);
          glVertex3f(fx, WALLHGT, fz);
          glTexCoord2f(1.0, 1.0);
          glVertex3f(fx+CELLSIZE, WALLHGT, fz);
          glTexCoord2f(1.0, 0.0);
          glVertex3f(fx+CELLSIZE, 0.0, fz);
        glEnd();
        glBegin(GL_QUADS);
          glNormal3f( 1.0, 0.0, 0.0);
          glTexCoord2f(0.0, 0.0);
          glVertex3f(fx+CELLSIZE, 0.0, fz);
          glTexCoord2f(0.0, 1.0);
          glVertex3f(fx+CELLSIZE, WALLHGT, fz);
          glTexCoord2f(1.0, 1.0);
          glVertex3f(fx+CELLSIZE, WALLHGT, fz+CELLSIZE);
          glTexCoord2f(1.0, 0.0);
          glVertex3f(fx+CELLSIZE, 0.0, fz+CELLSIZE);
        glEnd();
        glBegin(GL_QUADS);
          glNormal3f( 0.0, 0.0, 1.0);
          glTexCoord2f(0.0, 0.0);
          glVertex3f(fx+CELLSIZE, 0.0, fz+CELLSIZE);
          glTexCoord2f(0.0, 1.0);
          glVertex3f(fx+CELLSIZE, WALLHGT, fz+CELLSIZE);
          glTexCoord2f(1.0, 1.0);
          glVertex3f(fx, WALLHGT, fz+CELLSIZE);
          glTexCoord2f(1.0, 0.0);
          glVertex3f(fx, 0.0, fz+CELLSIZE);
        glEnd();
        glBegin(GL_QUADS);
          glNormal3f(-1.0, 0.0, 0.0);
          glTexCoord2f(0.0, 0.0);
          glVertex3f(fx, 0.0, fz+CELLSIZE);
          glTexCoord2f(0.0, 1.0);
          glVertex3f(fx, WALLHGT, fz+CELLSIZE);
          glTexCoord2f(1.0, 1.0);
          glVertex3f(fx, WALLHGT, fz);
          glTexCoord2f(1.0, 0.0);
          glVertex3f(fx, 0.0, fz);
        glEnd();
      }
    }
  }
  glBindTexture(GL_TEXTURE_2D, ceilingtex);
  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
  for(i=0;i<MSIZ;i++){
    fx = CELLSIZE * i;
    for(j=0;j<MSIZ;j++){
      if(map[i][j] == CT_FLOOR){
        fz = CELLSIZE * j;
        glBegin(GL_QUADS);
          glNormal3f( 0.0,-1.0, 0.0);
          glTexCoord2f(0.0, 0.0); glVertex3f(fx, WALLHGT, fz);
          glTexCoord2f(4.0, 0.0); glVertex3f(fx+CELLSIZE, WALLHGT, fz);
          glTexCoord2f(4.0, 4.0); glVertex3f(fx+CELLSIZE, WALLHGT, fz+CELLSIZE);
          glTexCoord2f(0.0, 4.0); glVertex3f(fx, WALLHGT, fz+CELLSIZE);
        glEnd();
      }
    }
  }

}


 
