#include "square.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/glut.h>
#endif

#include <IL/ilut.h>

// Load Bitmaps And Convert To Textures
unsigned int load_texture(char *filename)
{
	return ilutGLLoadImage((ILstring)filename);
	
}

Square::Square( int width )
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(2.0, 4.0, 0.0);
	glVertex3f(8.0, 4.0, 0.0);
	glVertex3f(8.0, 6.0, 0.0);
	glVertex3f(2.0, 6.0, 0.0);
	glEnd();
	glFlush();
}

void Square::ToggleTexturing()
{
}

void Square::Render() 
{
}

void Square::WindowWidth( int w, int h )
{
}

void Square::Click( int x, int y )
{
}

void Square::Drag( int x, int y )
{
}