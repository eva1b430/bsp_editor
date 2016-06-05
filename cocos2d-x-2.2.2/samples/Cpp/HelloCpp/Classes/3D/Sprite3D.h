#ifndef __SPRITE3D_H__
#define __SPRITE3D_H__

#include "cocos2d.h"
#include "Math3D.h"

using namespace std;
using namespace cocos2d;
class Sprite3D : public cocos2d::CCSprite
{
public:
	Sprite3D();
	virtual ~Sprite3D();

	void fillVertexList(std::vector<Vertex3D>& vertexList);
	void fillIndexList(std::vector<int>& indexList);

    virtual bool init();
	virtual bool init(std::vector<Vertex3D>& vertexList, std::vector<int>& indexList);

	virtual void onEnter();
	virtual void onExit();
	static Sprite3D *create();
	static Sprite3D *create(std::vector<Vertex3D>& vertexList, std::vector<int>& indexList);

	// 绘制
	virtual void draw(void);

	// 设置位置
	void setPosition3D(float x, float y, float z);
	Vector3D getPosition3D();
	// 设置缩放（等比缩放）
	void setScale3D(float fScale);
	// 设置角度
	void setRotX3D(float fDegree);
	void setRotY3D(float fDegree);
	void setRotZ3D(float fDegree);
	void setRotAxis3D(kmVec3 axis, float fDegree);

	// 旋转动作
	void runRotation(kmVec3 axis, float fDegreeOffset);
	void runRotationFoever(kmVec3 axis);
	void updateRotation(float dt);
	void updateRotationFoever(float dt);

	// 移动动作
	void runMove3D(Vector3D vecDirection);
	void updateMove3D(float dt);

	void set2DEnable(bool bEnable)
	{
		m_bIs2D = bEnable;
	}

private:
	CCGLProgram*	m_glProgram;

	GLuint			m_uVao;
	GLuint			m_uVbo;
	GLuint			m_uVboIndex;

	CCSprite*		m_pTexture;

	// 平移
	kmMat4		m_moveMatrix;
	// 旋转
	kmMat4		m_rotMatrix;
	// 缩放
	kmMat4		m_scaleMatrix;

	float		m_rotationOffset;
	float		m_rotationOffsetMax;
	kmVec3		m_rotationAxis;

	Vector3D	m_vecDirection;

	std::vector<Vertex3D>	m_vertexList;
	std::vector<int>		m_indexList;

	// 是否为正交投影
	bool		m_bIs2D;
};

#endif // __SPRITE3D_H__
