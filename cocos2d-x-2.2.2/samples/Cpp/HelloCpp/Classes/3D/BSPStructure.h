#ifndef __BSPSTRUCTURE_H__
#define __BSPSTRUCTURE_H__
#include "cocos2d.h"
#include "Math3D.h"

// 定义一个几何面，一个墙面
struct POLYGON 
{
	Vertex3D VertexList[10];		// 顶点
	Vector3D Normal;				// 面的法向量
	int NumberOfVertices;			// 顶点数
	int NumberOfIndices;			// 索引量
	int Indices[30];				// 索引
	POLYGON * Next;					// 指针
};


#endif // __BSPSTRUCTURE_H__
