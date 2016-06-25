// Includes

// Structures

class CMesh
{
public:
	char headerID[5];
	char meshName[64];	// object name
	int numFrames;		// number of meshFrames
	int numTextures;		// number of textures
	int numVertex;		// number of vertices
	int numFaces;		// number of faces
	int faceStart;		// byte location of faces
	int textureStart;	// byte location of textures
	int texCoordStart;	// byte location of texture coords
	int vertexStart;	// byte location of vertices
	int meshSize;		// total byte size of mesh
	float *vertex;
	float *texCoords;
	int *faces;
	char textures[68];	// texture names, only used for file info
//	CTexture texData;

	CMesh()
	{
		faces = NULL;
		texCoords = NULL;
		vertex = NULL;
	}
};

class CMd3Model
{
public:
	char headerID[4];	// header value (always "IDP3")
	char fileName[64];	// filename, can be left blank
	int numFrames;		// number of frames
	int numTags;		// number of tags
	int numMeshes;		// number of meshes/objects
	int numTextures;	// max number of textures
	int frameStart;		// byte location of frame data
	int tagStart;		// byte location of tag data
	int meshStart;		// byte location of mesh data
	int fileSize;		// size of file
	CMesh *meshes;		// Meshes

	CMd3Model()
	{
		meshes = NULL;
	}
	~CMd3Model();
};

// Function Headers

BOOL LoadMd3( CArchive &input, CMd3Model *m );
void DrawMd3Wire( CMd3Model *m );
