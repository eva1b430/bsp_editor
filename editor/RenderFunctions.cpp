#include "stdafx.h"
#include "RenderFunctions.h"

// A simple function for drawing a
// cube with colored faces. Used
// during development for testing.
void DrawCube( CViewerDoc* doc )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glBegin( GL_TRIANGLE_STRIP );
		glColor3f( 1.0f, 0.0f, 0.0f );
		glVertex3f( -1.0f, -1.0f, 0.0f );
		glVertex3f( 1.0f, -1.0f, 0.0f );
		glVertex3f( -1.0f, 1.0f, 0.0f );
		glVertex3f( 1.0f, 1.0f, 0.0f );
	glEnd();

	glBegin( GL_TRIANGLE_STRIP );
		glColor3f( 1.0f, 0.0f, 0.0f );
		glVertex3f( -1.0f, -1.0f, -2.0f );
		glVertex3f( 1.0f, -1.0f, -2.0f );
		glVertex3f( -1.0f, 1.0f, -2.0f );
		glVertex3f( 1.0f, 1.0f, -2.0f );
	glEnd();

	glBegin( GL_TRIANGLE_STRIP );
		glColor3f( 0.0f, 1.0f, 0.0f );
		glVertex3f( -1.0f, -1.0f, 0.0f );
		glVertex3f( -1.0f, -1.0f, -2.0f );
		glVertex3f( -1.0f, 1.0f, 0.0f );
		glVertex3f( -1.0f, 1.0f, -2.0f );
	glEnd();

	glBegin( GL_TRIANGLE_STRIP );
		glColor3f( 0.0f, 1.0f, 0.0f );
		glVertex3f( 1.0f, -1.0f, 0.0f );
		glVertex3f( 1.0f, -1.0f, -2.0f );
		glVertex3f( 1.0f, 1.0f, 0.0f );
		glVertex3f( 1.0f, 1.0f, -2.0f );
	glEnd();

	glBegin( GL_TRIANGLE_STRIP );
		glColor3f( 0.0f, 0.0f, 1.0f );
		glVertex3f( -1.0f, 1.0f, 0.0f );
		glVertex3f( 1.0f, 1.0f, 0.0f );
		glVertex3f( -1.0f, 1.0f, -2.0f );
		glVertex3f( 1.0f, 1.0f, -2.0f );
	glEnd();

	glBegin( GL_TRIANGLE_STRIP );
		glColor3f( 0.0f, 0.0f, 1.0f );
		glVertex3f( -1.0f, -1.0f, 0.0f );
		glVertex3f( 1.0f, -1.0f, 0.0f );
		glVertex3f( -1.0f, -1.0f, -2.0f );
		glVertex3f( 1.0f, -1.0f, -2.0f );
	glEnd();
}

void DrawDocWire( CViewerDoc* doc )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	if ( doc->m_currentModel != NULL )
		DrawMd3Wire( doc->m_currentModel );
}