#ifndef __BSPSTRUCTURE_H__
#define __BSPSTRUCTURE_H__
#include "cocos2d.h"
#include "Math3D.h"

// ����һ�������棬һ��ǽ��
struct POLYGON 
{
	Vertex3D VertexList[10];		// ����
	Vector3D Normal;				// ��ķ�����
	int NumberOfVertices;			// ������
	int NumberOfIndices;			// ������
	int Indices[30];				// ����
	POLYGON * Next;					// ָ��
};


#endif // __BSPSTRUCTURE_H__
