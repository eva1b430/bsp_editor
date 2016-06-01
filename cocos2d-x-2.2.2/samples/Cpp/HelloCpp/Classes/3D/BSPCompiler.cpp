#include "BSPCompiler.h"
#include "AppMacros.h"
#include "ccMacros.h"

using namespace cocos2d;

// MAP
BYTE BSPMAP[] ={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,
	1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,
	1,0,0,3,0,0,0,1,0,0,0,0,0,0,0,0,2,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,1,
	1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

BSPCompiler::BSPCompiler()
	: m_polygonList(NULL)
	, m_pRenderNode(NULL)
{

}

BSPCompiler::~BSPCompiler()
{

}

void BSPCompiler::addToCCNode(CCNode* pNode)
{
	InitPolygons();

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (pNode)
	{
		// 设置一下
		std::vector<Vertex3D>	vertexList;
		std::vector<int>		indexList;
		POLYGON* pNext = m_polygonList;
		while(pNext)
		{
			vertexList.clear();
			indexList.clear();

			// 拿出8个顶点
			for (int i = 0; i < pNext->NumberOfVertices; i++)
			{
				vertexList.push_back(pNext->VertexList[i]);
			}
			
			for (int i = 0; i < pNext->NumberOfIndices; i++)
			{
				indexList.push_back(pNext->Indices[i]);
			}

			m_pRenderNode = Sprite3D::create(vertexList, indexList);
			pNode->addChild(m_pRenderNode);
			m_pRenderNode->setRotX3D(90.0f);
			m_pRenderNode->setPosition3D(size.width / 2, size.height / 2, 0.0f);
			m_pRenderNode->setScale3D(10.0f);

			pNext = pNext->Next;
		}
		
		
	}
}

void BSPCompiler::InitPolygons()
{
	Vertex3D	VERTLIST[4][4];
	POLYGON*	child = NULL;
	int			direction[4];

	m_polygonList = NULL;

	// 遍历数组20 * 40
	for( int y = 0; y < 40; ++y )
	{
		for( int x = 0; x < 20; ++x )
		{
			ZeroMemory(direction, sizeof(int) * 4);

			int offset = (y * 20) + x;

			if( BSPMAP[offset] != 0 ) 
			{
				if( BSPMAP[offset] == 2 ) 
				{   
					VERTLIST[0][0] = Vertex3D(x-10.5f, 3.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,0.0f);
					VERTLIST[0][1] = Vertex3D(x- 9.5f,3.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,0.0f);
					VERTLIST[0][2] = Vertex3D(x- 9.5f,0.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,1.0f);
					VERTLIST[0][3] = Vertex3D(x-10.5f,0.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,1.0f);
					direction[0]   = 1;

					if( x > 0 ) 
					{
						if( BSPMAP[offset-1] == 0) 
						{
							VERTLIST[1][0] = Vertex3D(x-10.5f,3.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,0.0f);
							VERTLIST[1][1] = Vertex3D(x-10.5f,3.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,0.0f);
							VERTLIST[1][2] = Vertex3D(x-10.5f,0.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,1.0f);
							VERTLIST[1][3] = Vertex3D(x-10.5f,0.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,1.0f);
							direction[1]   = 1;
						}
					}

					if( y > 0 ) 
					{
						if( BSPMAP[offset-20] == 0 ) 
						{
							VERTLIST[2][0] = Vertex3D(x- 9.5f,3.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,0.0f);
							VERTLIST[2][1] = Vertex3D(x-10.5f,3.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,0.0f);
							VERTLIST[2][2] = Vertex3D(x-10.5f,0.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,1.0f);
							VERTLIST[2][3] = Vertex3D(x- 9.5f,0.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,1.0f);
							direction[2]   = 1;
						}
					}
				}

				if( BSPMAP[offset] == 3 )
				{   
					VERTLIST[0][0] = Vertex3D(x-10.5f,3.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,0.0f);
					VERTLIST[0][1] = Vertex3D(x- 9.5f,3.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,0.0f);
					VERTLIST[0][2] = Vertex3D(x- 9.5f,0.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,1.0f);
					VERTLIST[0][3] = Vertex3D(x-10.5f,0.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,1.0f);
					direction[0]   = 1;

					if(x < 19)
					{
						if( BSPMAP[offset+1] == 0)
						{
							VERTLIST[1][0] = Vertex3D(x-9.5f,3.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,0.0f);
							VERTLIST[1][1] = Vertex3D(x-9.5f,3.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,0.0f);
							VERTLIST[1][2] = Vertex3D(x-9.5f,0.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,1.0f);
							VERTLIST[1][3] = Vertex3D(x-9.5f,0.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,1.0f);
							direction[1]   = 1;
						}
					}

					if( y > 0 )
					{
						if( BSPMAP[offset-20] == 0 )
						{
							VERTLIST[2][0] = Vertex3D(x- 9.5f,3.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,0.0f);
							VERTLIST[2][1] = Vertex3D(x-10.5f,3.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,0.0f);
							VERTLIST[2][2] = Vertex3D(x-10.5f,0.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,1.0f);
							VERTLIST[2][3] = Vertex3D(x- 9.5f,0.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,1.0f);
							direction[2]   = 1;
						}
					}
				}               

				if( BSPMAP[offset] == 1 )
				{
					if( x > 0 )
					{
						if( BSPMAP[offset-1] == 0 )
						{
							VERTLIST[0][0] = Vertex3D(x-10.5f,3.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,0.0f);
							VERTLIST[0][1] = Vertex3D(x-10.5f,3.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,0.0f);
							VERTLIST[0][2] = Vertex3D(x-10.5f,0.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,1.0f);
							VERTLIST[0][3] = Vertex3D(x-10.5f,0.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,1.0f);
							direction[0]   = 1;
						}
					}

					if (x < 19) 
					{
						if( BSPMAP[offset+1] == 0) 
						{
							VERTLIST[1][0] = Vertex3D(x-9.5f,3.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,0.0f);
							VERTLIST[1][1] = Vertex3D(x-9.5f,3.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,0.0f);
							VERTLIST[1][2] = Vertex3D(x-9.5f,0.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,1.0f);
							VERTLIST[1][3] = Vertex3D(x-9.5f,0.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,1.0f);
							direction[1]   = 1;
						}
					}

					if( y > 0 ) 
					{
						if( BSPMAP[offset-20] == 0 ) 
						{
							VERTLIST[2][0] = Vertex3D(x- 9.5f,3.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,0.0f);
							VERTLIST[2][1] = Vertex3D(x-10.5f,3.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,0.0f);
							VERTLIST[2][2] = Vertex3D(x-10.5f,0.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,1.0f);
							VERTLIST[2][3] = Vertex3D(x- 9.5f,0.0f,(20.0f-y)+0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,1.0f);
							direction[2]   = 1;
						}
					}

					if( y < 39 )
					{   
						if( BSPMAP[offset+20] == 0)
						{
							VERTLIST[3][0] = Vertex3D(x-10.5f,3.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,0.0f);
							VERTLIST[3][1] = Vertex3D(x- 9.5f,3.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,0.0f);
							VERTLIST[3][2] = Vertex3D(x- 9.5f,0.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 1.0f,1.0f);
							VERTLIST[3][3] = Vertex3D(x-10.5f,0.0f,(20.0f-y)-0.5f, 1.0f,1.0f,1.0f,1.0f, 0.0f,1.0f);
							direction[3]   = 1;
						}
					}

				}

				// 1， 2， 3 的情况都考虑完了
				for( int a = 0; a < 4; ++a )
				{
					if( direction[a] != 0 )
					{
						if( m_polygonList == NULL )
						{
							m_polygonList = addPolygon(NULL,&VERTLIST[a][0],4);
							child = m_polygonList;
						}
						else
						{
							child = addPolygon(child,&VERTLIST[a][0],4);
						}
					}
				}
			}
			else/*( BSPMAP[offset] == 0 ) */
			{
				// 什么也不做
			}

		}// for
	}// for
}

POLYGON * BSPCompiler::addPolygon( POLYGON* Parent, Vertex3D* Vertices, int NumberOfVerts )
{
	POLYGON* Child = new POLYGON;
	int v0;
	int v1;
	int v2;
	int  i = 0;

	Child->NumberOfVertices = NumberOfVerts;
	Child->NumberOfIndices  = (NumberOfVerts - 2) * 3;
	Child->Next              = NULL;

	// Copy Vertices
	for( i = 0; i < NumberOfVerts; ++i )
	{
		Child->VertexList[i] = Vertices[i];
	}

	// Calculate indices
	for( i = 0; i < Child->NumberOfIndices / 3; ++i )
	{
		if( i == 0 )
		{
			v0 = 0;
			v1 = 1;
			v2 = 2;
		}
		else
		{
			v1 = v2;
			++v2;
		}

		Child->Indices[ i * 3     ] = v0;
		Child->Indices[(i * 3) + 1] = v1;
		Child->Indices[(i * 3) + 2] = v2;
	} // Next Tri

	// Generate polygon normal
	Vector3D* vec0 = (Vector3D*) &Child->VertexList[0];
	Vector3D* vec1 = (Vector3D*) &Child->VertexList[1];
	Vector3D* vec2 = (Vector3D*) &Child->VertexList[Child->NumberOfVertices-1];// the last vert

	Vector3D edge1 = (*vec1)-(*vec0);
	Vector3D edge2 = (*vec2)-(*vec0);

	// 计算叉积（叉积数学概念是垂直于这两个向量的向量，同时按照右手原则）
	//Vector3D pOut;
	kmVec3 pOut;
	kmVec3 kmvec1;
	kmVec3 kmvec2;
	kmVec3Fill(&kmvec1, edge1.m_fVec[0], edge1.m_fVec[1], edge1.m_fVec[2]);
	kmVec3Fill(&kmvec2, edge2.m_fVec[0], edge2.m_fVec[1], edge2.m_fVec[2]);
	kmVec3Cross(&pOut, &kmvec1, &kmvec2);
	kmVec3 pOutN;
	kmVec3Normalize(&pOutN, &pOut);
	Child->Normal = Vector3D(pOutN.x, pOutN.y, pOutN.z);
	//D3DXVec3Cross(&Child->Normal,&edge1,&edge2);
	//D3DXVec3Normalize(&Child->Normal,&Child->Normal);

	if( Parent != NULL )
	{
		Parent->Next=Child;
	}

	return Child;
}

Vertex3D BSPCompiler::getRootPosition3D()
{
	if (m_polygonList)
	{
		return m_polygonList->VertexList[0];
	}
	
	return Vertex3D();
}
