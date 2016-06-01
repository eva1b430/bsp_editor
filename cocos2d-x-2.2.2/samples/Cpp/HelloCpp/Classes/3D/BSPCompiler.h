#ifndef __BSPCOMPILER_H__
#define __BSPCOMPILER_H__

#include "cocos2d.h"
#include "Math3D.h"
#include "BSPStructure.h"
#include "Sprite3D.h"

using namespace std;
using namespace cocos2d;
class BSPCompiler
{
public:
	BSPCompiler();
	virtual ~BSPCompiler();

	void addToCCNode(CCNode* pNode);

	// 读取数据，生成Polygon-List
	void InitPolygons();
	POLYGON *addPolygon(POLYGON* Parent, Vertex3D* Vertices, int NumberOfVerts);

	Vertex3D getRootPosition3D();

private:
	POLYGON*		m_polygonList;
	Sprite3D*		m_pRenderNode;
};

#endif // __BSPCOMPILER_H__
