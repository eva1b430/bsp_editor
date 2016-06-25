#include "stdafx.h"
#include "Model.h"

// A bunch of functions used to read
// and draw MD3 models.

BOOL LoadMd3( CArchive &input, CMd3Model *m )
{
	BYTE *buffer;
	int curLocation;
	int meshStart;

	// read the ID
	input.Read( &m->headerID, sizeof(char)*4 );
	m->headerID[4] = 0;
	if ( strcmp( m->headerID, "IDP3" ) != 0 )
		return FALSE;	// not an md3 file

	// throw away a version number
	// we'll overwrite it later
	input.Read( &m->numTags, sizeof(int) );

	// read the other header stuff
	input.Read( &m->fileName, sizeof(char)*68 );		// may be blank
	input.Read( &m->numFrames, sizeof(int) );
	input.Read( &m->numTags, sizeof(int) );
	input.Read( &m->numMeshes, sizeof(int) );
	input.Read( &m->numTextures, sizeof(int) );
	input.Read( &m->frameStart, sizeof(int) );
	input.Read( &m->tagStart, sizeof(int) );
	input.Read( &m->meshStart, sizeof(int) );
	input.Read( &m->fileSize, sizeof(int) );

	// to start we'll only read the first frame of the
	// each mesh - only text coords, verts, and faces

	// read the rest of the file
	buffer = new BYTE[m->fileSize - 108];
	input.Read( buffer, m->fileSize-108 );

	meshStart = curLocation = m->meshStart - 108;
	if ( m->meshes != NULL )
		delete m->meshes;
	m->meshes = new CMesh[m->numMeshes];
	for ( int i = 0; i < m->numMeshes; i++ )
	{
		strncpy( m->meshes[i].headerID, (char *)(&buffer[curLocation]), 4 );
		m->meshes[i].headerID[4] = 0;
		curLocation += 4;
		if ( strcmp( m->meshes[i].headerID, "IDP3" ) == 0 )
		{
			strncpy( m->meshes[i].meshName, (char *)(&buffer[curLocation]), 68 );
			curLocation += 68;
		}
		m->meshes[i].numFrames = *(int*)(&buffer[curLocation]);
		curLocation += sizeof(int);
		m->meshes[i].numTextures = *(int*)(&buffer[curLocation]);
		curLocation += sizeof(int);
		m->meshes[i].numVertex = *(int*)(&buffer[curLocation]);
		curLocation += sizeof(int);
		m->meshes[i].numFaces = *(int*)(&buffer[curLocation]);
		curLocation += sizeof(int);
		m->meshes[i].faceStart = *(int*)(&buffer[curLocation]);
		curLocation += sizeof(int);
		m->meshes[i].textureStart = *(int*)(&buffer[curLocation]);
		curLocation += sizeof(int);
		m->meshes[i].texCoordStart = *(int*)(&buffer[curLocation]);
		curLocation += sizeof(int);
		m->meshes[i].vertexStart = *(int*)(&buffer[curLocation]);
		curLocation += sizeof(int);
		m->meshes[i].meshSize = *(int*)(&buffer[curLocation]);
		curLocation += sizeof(int);


		// get the vert info
		curLocation = meshStart + m->meshes[i].vertexStart;
		if ( m->meshes[i].vertex != NULL )
			delete m->meshes[i].vertex;
		m->meshes[i].vertex = new float[m->meshes[i].numVertex * 3];
		for ( int j = 0; j < m->meshes[i].numVertex * 3; j+=3 )
		{
			m->meshes[i].vertex[j] = (float)(*(short*)(&buffer[curLocation])) / 64.0f;
			curLocation += sizeof(short);
			m->meshes[i].vertex[j+1] = (float)(*(short*)(&buffer[curLocation])) / 64.0f;
			curLocation += sizeof(short);
			m->meshes[i].vertex[j+2] = (float)(*(short*)(&buffer[curLocation])) / 64.0f;
			curLocation += sizeof(short);

			// skip the vertex normals, to be added later
			curLocation += sizeof(GLubyte) * 2;
		}

		// get the texture coords
		curLocation = meshStart + m->meshes[i].texCoordStart;
		if ( m->meshes[i].texCoords != NULL )
			delete m->meshes[i].texCoords;
		m->meshes[i].texCoords = new float[m->meshes[i].numVertex * 2];
		for ( int j = 0; j < m->meshes[i].numVertex * 2; j+=2 )
		{
			m->meshes[i].texCoords[j] = *(float*)(&buffer[curLocation]);
			curLocation += sizeof(float);
			m->meshes[i].texCoords[j+1] = 1.0f - *(float*)(&buffer[curLocation]);
			curLocation += sizeof(float);
		}

		// get the faces
		curLocation = meshStart + m->meshes[i].faceStart;
		if ( m->meshes[i].faces != NULL )
			delete m->meshes[i].faces;
		m->meshes[i].faces = new int[m->meshes[i].numFaces * 3];
		for ( int j = 0; j < m->meshes[i].numFaces * 3; j+=3 )
		{
			m->meshes[i].faces[j] = *(int*)(&buffer[curLocation]);
			curLocation += sizeof(int);
			m->meshes[i].faces[j+1] = *(int*)(&buffer[curLocation]);
			curLocation += sizeof(int);
			m->meshes[i].faces[j+2] = *(int*)(&buffer[curLocation]);
			curLocation += sizeof(int);
		}

		// get the texture names
		curLocation = meshStart + m->meshes[i].textureStart;
		strcpy( m->meshes[i].textures, (char*)(&buffer[curLocation]) );

		meshStart = curLocation = meshStart + m->meshes[i].meshSize;
	}

	delete buffer;
	return TRUE;
}

void DrawMeshWire( CMesh *m )
{
	glDisable( GL_TEXTURE_2D );
	glColor3f( 1.0f, 1.0f, 1.0f );

	glBegin( GL_LINES );
	for ( int i = 0; i < m->numFaces * 3; i+=3 )
		{
			glVertex3f( m->vertex[m->faces[i]*3], m->vertex[m->faces[i]*3+1],
				m->vertex[m->faces[i]*3+2] );
			glVertex3f( m->vertex[m->faces[i+1]*3], m->vertex[m->faces[i+1]*3+1],
				m->vertex[m->faces[i+1]*3+2] );
			glVertex3f( m->vertex[m->faces[i+1]*3], m->vertex[m->faces[i+1]*3+1],
				m->vertex[m->faces[i+1]*3+2] );
			glVertex3f( m->vertex[m->faces[i+2]*3], m->vertex[m->faces[i+2]*3+1],
				m->vertex[m->faces[i+2]*3+2] );
			glVertex3f( m->vertex[m->faces[i+2]*3], m->vertex[m->faces[i+2]*3+1],
				m->vertex[m->faces[i+2]*3+2] );
			glVertex3f( m->vertex[m->faces[i]*3], m->vertex[m->faces[i]*3+1],
				m->vertex[m->faces[i]*3+2] );
		}
	glEnd();
	glEnable( GL_TEXTURE_2D );
}

void DrawMd3Wire( CMd3Model *m )
{
	for ( int i = 0; i < m->numMeshes; i++ )
			DrawMeshWire( &m->meshes[i] );
}

CMd3Model::~CMd3Model()
{
	if ( meshes != NULL )
	{
		if ( meshes->vertex != NULL )
			delete meshes->vertex;
		if ( meshes->texCoords != NULL )
			delete meshes->texCoords;
		if ( meshes->faces != NULL )
			delete meshes->faces;
		delete meshes;
	}
}