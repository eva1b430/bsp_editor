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

	// ����
	virtual void draw(void);

	// ����λ��
	void setPosition3D(float x, float y, float z);
	Vector3D getPosition3D();
	// �������ţ��ȱ����ţ�
	void setScale3D(float fScale);
	// ���ýǶ�
	void setRotX3D(float fDegree);
	void setRotY3D(float fDegree);
	void setRotZ3D(float fDegree);
	void setRotAxis3D(kmVec3 axis, float fDegree);

	// ��ת����
	void runRotation(kmVec3 axis, float fDegreeOffset);
	void runRotationFoever(kmVec3 axis);
	void updateRotation(float dt);
	void updateRotationFoever(float dt);

	// �ƶ�����
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

	// ƽ��
	kmMat4		m_moveMatrix;
	// ��ת
	kmMat4		m_rotMatrix;
	// ����
	kmMat4		m_scaleMatrix;

	float		m_rotationOffset;
	float		m_rotationOffsetMax;
	kmVec3		m_rotationAxis;

	Vector3D	m_vecDirection;

	std::vector<Vertex3D>	m_vertexList;
	std::vector<int>		m_indexList;

	// �Ƿ�Ϊ����ͶӰ
	bool		m_bIs2D;
};

#endif // __SPRITE3D_H__
