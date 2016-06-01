#ifndef __MATH3D_H__
#define __MATH3D_H__
#include "cocos2d.h"
// 3D格式
struct Vertex3D
{
	float Position[3];
	float Color[4];
	float TexCoord[2];

	Vertex3D()
	{
		// 位置
		Position[0] = 0.0f;
		Position[1] = 0.0f;
		Position[2] = 0.0f;

		// color
		Color[0] = 0.0f;
		Color[1] = 0.0f;
		Color[2] = 0.0f;
		Color[3] = 0.0f;

		// 纹理
		TexCoord[0] = 0.0f;
		TexCoord[1] = 0.0f;
	}

	Vertex3D(float x, float y, float z,
			float r, float g, float b, float alpha,
			float tu, float tv)
	{
		// 位置
		Position[0] = x;
		Position[1] = y;
		Position[2] = z;

		// color
		Color[0] = r;
		Color[1] = g;
		Color[2] = b;
		Color[3] = alpha;

		// 纹理
		TexCoord[0] = tu;
		TexCoord[1] = tv;
	}
};

// 上述定义不利于整合
struct Vector3D
{
	float m_fVec[3];
	Vector3D()
	{
		m_fVec[0] = 0.0f;
		m_fVec[1] = 0.0f;
		m_fVec[2] = 0.0f;
	}

	Vector3D(float* fVec)
	{
		memcpy(m_fVec, fVec, sizeof(float[3]));
	}

	Vector3D(float x, float y, float z)
	{
		m_fVec[0] = x;
		m_fVec[1] = y;
		m_fVec[2] = z;
	}

	Vector3D operator-(const Vector3D& right) const
	{
		return Vector3D(this->m_fVec[0] - right.m_fVec[0], 
			this->m_fVec[1] - right.m_fVec[1], 
			this->m_fVec[2] - right.m_fVec[2]);
	}
};

struct Vector2D
{
	float m_fVec[2];
	Vector2D(float * fVec)
	{
		memcpy(m_fVec, fVec, sizeof(float[2]));
	}
};

#endif // __MATH3D_H__
