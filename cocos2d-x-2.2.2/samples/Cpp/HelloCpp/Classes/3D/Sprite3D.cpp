#include "Sprite3D.h"
#include "AppMacros.h"
#include "ccMacros.h"

using namespace cocos2d;

#define TEX_COORD_MAX   1
// 扩展顶点格式
Vertex3D data[] =
{
	// Front
	Vertex3D(1, -1, 1, 1, 0, 0, 1, TEX_COORD_MAX, 0),
	Vertex3D(1, 1, 1, 0, 1, 0, 1, TEX_COORD_MAX, TEX_COORD_MAX),
	Vertex3D(-1, 1, 1, 0, 0, 1, 1, 0, TEX_COORD_MAX),
	Vertex3D(-1, -1, 1, 0, 0, 0, 1, 0, 0),
	// Back
	Vertex3D(1, 1, -1, 1, 0, 0, 1, TEX_COORD_MAX, TEX_COORD_MAX),
	Vertex3D(-1, -1, -1, 0, 1, 0, 1, 0, 0),
	Vertex3D(1, -1, -1, 0, 0, 1, 1, TEX_COORD_MAX, 0),
	Vertex3D(-1, 1, -1, 0, 0, 0, 1, 0, TEX_COORD_MAX),
	// Left
	Vertex3D(-1, -1, 1, 1, 0, 0, 1, TEX_COORD_MAX, 0),
	Vertex3D(-1, 1, 1, 0, 1, 0, 1, TEX_COORD_MAX, TEX_COORD_MAX),
	Vertex3D(-1, 1, -1, 0, 0, 1, 1, 0, TEX_COORD_MAX),
	Vertex3D(-1, -1, -1, 0, 0, 0, 1, 0, 0),
	// Right
	Vertex3D(1, -1, -1, 1, 0, 0, 1, TEX_COORD_MAX, 0),
	Vertex3D(1, 1, -1, 0, 1, 0, 1, TEX_COORD_MAX, TEX_COORD_MAX),
	Vertex3D(1, 1, 1, 0, 0, 1, 1, 0, TEX_COORD_MAX),
	Vertex3D(1, -1, 1, 0, 0, 0, 1, 0, 0),
	// Top
	Vertex3D(1, 1, 1, 1, 0, 0, 1, TEX_COORD_MAX, 0),
	Vertex3D(1, 1, -1, 0, 1, 0, 1, TEX_COORD_MAX, TEX_COORD_MAX),
	Vertex3D(-1, 1, -1, 0, 0, 1, 1, 0, TEX_COORD_MAX),
	Vertex3D(-1, 1, 1, 0, 0, 0, 1, 0, 0),
	// Bottom
	Vertex3D(1, -1, -1, 1, 0, 0, 1, TEX_COORD_MAX, 0),
	Vertex3D(1, -1, 1, 0, 1, 0, 1, TEX_COORD_MAX, TEX_COORD_MAX),
	Vertex3D(-1, -1, 1, 0, 0, 1, 1, 0, TEX_COORD_MAX),
	Vertex3D(-1, -1, -1, 0, 0, 0, 1, 0, 0)
};

int indexList[] = {
	// Front
	0, 1, 2,
	2, 3, 0,
	// Back
	4, 5, 6,
	5, 7, 4,
	// Left
	8, 9, 10,
	10, 11, 8,
	// Right
	12, 13, 14,
	14, 15, 12,
	// Top
	16, 17, 18,
	18, 19, 16,
	// Bottom
	20, 21, 22,
	22, 23, 20
};

Sprite3D::Sprite3D()
	: m_glProgram(NULL)
	, m_uVao(0)
	, m_uVbo(0)
	, m_uVboIndex(0)
	, m_pTexture(NULL)
	, m_rotationOffset(0.0f)
	, m_rotationOffsetMax(0.0f)
	, m_vecDirection(Vector3D())
	, m_bIs2D(false)
{
	kmMat4Identity(&m_moveMatrix);
	kmMat4Identity(&m_rotMatrix);
	kmMat4Identity(&m_scaleMatrix);

	kmVec3Fill(&m_rotationAxis, 0.0f, 0.0f, 1.0f);

	for (int i = 0; i < 24; i++)
	{
		m_vertexList.push_back(data[i]);
	}

	for (int i = 0; i < 36; i++)
	{
		m_indexList.push_back(indexList[i]);
	}
}

Sprite3D::~Sprite3D()
{
	delete m_glProgram;
	m_glProgram = NULL;
}

bool Sprite3D::init(std::vector<Vertex3D>& vertexList, std::vector<int>& indexList)
{
	fillVertexList(vertexList);
	fillIndexList(indexList);

	return init();
}

bool Sprite3D::init()
{
    if ( !CCSprite::init() )
    {
        return false;
    }

	m_glProgram = new CCGLProgram();
	m_glProgram->initWithVertexShaderFilename("Tiny3DShader/myVertextShader.vert", "Tiny3DShader/myFragmentShader.frag");
	m_glProgram->link();
	m_glProgram->updateUniforms();

	//创建和绑定vao
	glGenVertexArrays(1, &m_uVao);
	glBindVertexArray(m_uVao);

	glGenBuffers(1, &m_uVbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_uVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex3D) * m_vertexList.size(), &m_vertexList[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_uVboIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uVboIndex);
	int nSize = sizeof(indexList);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_indexList.size(), &m_indexList[0], GL_STATIC_DRAW);
	
	GLuint positionLocation = glGetAttribLocation(m_glProgram->getProgram(), "a_position");
	GLuint colorLocation = glGetAttribLocation(m_glProgram->getProgram(), "a_color");
	GLuint textureLocation = glGetAttribLocation(m_glProgram->getProgram(), "a_coord");
	GLuint textureUniform = glGetUniformLocation(m_glProgram->getProgram(), "CC_Texture0");

	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(colorLocation);
	glEnableVertexAttribArray(textureLocation);

	glVertexAttribPointer(positionLocation,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex3D),
		(GLvoid* )offsetof(Vertex3D, Position));

	glVertexAttribPointer(colorLocation,
		4,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex3D),
		(GLvoid* )offsetof(Vertex3D, Color));

	glVertexAttribPointer(textureLocation,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex3D),
		(GLvoid* )offsetof(Vertex3D, TexCoord));

	// for safty
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// 纹理
	m_pTexture = CCSprite::create("Texture/can.png");
	m_pTexture->retain();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    return true;
}

void Sprite3D::onEnter()
{
	CCSprite::onEnter();
}

void Sprite3D::onExit()
{
	unschedule(schedule_selector(Sprite3D::updateRotation));
	unschedule(schedule_selector(Sprite3D::updateRotationFoever));
	unschedule(schedule_selector(Sprite3D::updateMove3D));

	CCSprite::onExit();
}

Sprite3D* Sprite3D::create(std::vector<Vertex3D>& vertexList, std::vector<int>& indexList)
{
	Sprite3D *pRet = new Sprite3D();
	if (pRet && pRet->init(vertexList, indexList))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

Sprite3D* Sprite3D::create( void )
{
	Sprite3D *pRet = new Sprite3D();
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

// 注意：使用VBO和VAO步骤：
// glGen×××
// glBind×××
// 投影矩阵 × 视图矩阵 × 模型矩阵 × 3D位置
// OpenGL 使用右手规则进行旋转
// MVP = Projection * View * Model
// 参考在shader
// gl_Position = MVP * vec4(a_position.xyz, 1);
// 所以，构造的矩阵应该是 P（观察）* V（相机）* [  T（平移） * R（旋转） * S（缩放） ]（模型） 
void Sprite3D::draw( void )
{
	// 开启线框模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (m_bIs2D)
	{
		// 关闭深度测试
		//glDisable(GL_DEPTH_TEST);

		// 绘制部分
		m_glProgram->use();
		m_glProgram->setUniformsForBuiltins();

		// 参考在shader
		// gl_Position = Modelview * vec4(a_position.xyz, 1);
		//////////////////////////////////////////////////////////////////////////
		// 定义model
		// 缩放
		/*
		【kmMat4 scaleMatrix;kmMat4Identity(&scaleMatrix);
		//kmMat4Scaling(&scaleMatrix, 0.1f, 0.1f, 0.1f);
		// 旋转
		kmMat4 rotMatrix;kmMat4Identity(&rotMatrix);
		static float rotation = 0;
		kmVec3 axis;
		kmVec3Fill(&axis, 1.0f, 1.0f, 1.0f);
		kmMat4RotationAxisAngle(&rotMatrix, &axis, CC_DEGREES_TO_RADIANS(rotation));
		rotation += 1.0f;
		if (rotation > 360.0f)
		{
		rotation = 0.0f;
		}
		// 平移
		kmMat4 moveMatrix;kmMat4Identity(&moveMatrix);
		kmMat4Translation(&moveMatrix, 0.0f, 0.0f, 1.0f);】
		*/

		kmMat4 modelMatrix;kmMat4Identity(&modelMatrix);
		kmMat4Multiply(&modelMatrix, &modelMatrix, &m_moveMatrix);
		kmMat4Multiply(&modelMatrix, &modelMatrix, &m_rotMatrix);
		kmMat4Multiply(&modelMatrix, &modelMatrix, &m_scaleMatrix);

		//////////////////////////////////////////////////////////////////////////
		// 定义view
		kmMat4 viewMatrix;kmMat4Identity(&viewMatrix);
		kmVec3 eye, center, up;
		// 第一组eyex, eyey,eyez 相机在世界坐标的位置
		// 第二组centerx,centery,centerz 相机镜头对准的物体在世界坐标的位置
		// 第三组upx,upy,upz 相机向上的方向在世界坐标中的方向
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		//kmVec3Fill(&eye, 0.0f, 0.0f, 20.0f);
		//kmVec3Fill(&center, 0.0f, 0.0f, 0.0f);
		//kmVec3Fill(&up, 0.0f, 1.0f, 0.0f);
		float zeye = CCDirector::sharedDirector()->getZEye();
		kmVec3Fill( &eye, size.width/2, size.height/2, zeye );
		kmVec3Fill( &center, size.width/2, size.height/2, 0.0f );
		kmVec3Fill( &up, 0.0f, 1.0f, 0.0f);
		kmMat4LookAt(&viewMatrix, &eye, &center, &up);

		//////////////////////////////////////////////////////////////////////////
		// 构造MVP
		// MV矩阵
		kmMat4 matrixMV;kmMat4Identity(&matrixMV);
		kmMat4Multiply(&matrixMV, &viewMatrix, &modelMatrix);

		// MVP矩阵
		kmMat4 matrixMVP;kmMat4Identity(&matrixMVP);
		kmMat4 matrixP;kmMat4Identity(&matrixP);
		kmMat4OrthographicProjection(&matrixP, 0, size.width, 0, size.height, -1024, 1024 );
		//kmGLGetMatrix(KM_GL_PROJECTION, &matrixP);
		kmMat4Multiply(&matrixMVP, &matrixP, &matrixMV);

		//////////////////////////////////////////////////////////////////////////
		GLuint mvpUniform = glGetUniformLocation(m_glProgram->getProgram(), "MVP");
		m_glProgram->setUniformLocationWithMatrix4fv(mvpUniform, matrixMVP.mat, 1);

		glBindVertexArray(m_uVao);
		// uniform
		//GLuint uColorLocation = glGetUniformLocation(m_glProgram->getProgram(), "u_color");
		//float uColor[] = {1.0, 1.0, 0.6, 1.0};
		//glUniform4fv(uColorLocation, 1, uColor);
		ccGLBindTexture2D(m_pTexture->getTexture()->getName());

		// 36 = 12 * 3（12个三角形，每个三角形需要3个顶点）
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// 必须这么做，否则2D元素不显示，因为openGL变化是一个“马尔科夫变化”
		//kmGLPushMatrix();
		//kmGLLoadIdentity();
		//kmGLPopMatrix();

		// 开启深度测试
		//glEnable(GL_DEPTH_TEST);
	}
	else
	{
		// 开启深度测试
		glEnable(GL_DEPTH_TEST);

		// 绘制部分
		m_glProgram->use();
		m_glProgram->setUniformsForBuiltins();

		// 参考在shader
		// gl_Position = Modelview * vec4(a_position.xyz, 1);
		//////////////////////////////////////////////////////////////////////////
		// 定义model
		// 缩放
		/*
		【kmMat4 scaleMatrix;kmMat4Identity(&scaleMatrix);
		//kmMat4Scaling(&scaleMatrix, 0.1f, 0.1f, 0.1f);
		// 旋转
		kmMat4 rotMatrix;kmMat4Identity(&rotMatrix);
		static float rotation = 0;
		kmVec3 axis;
		kmVec3Fill(&axis, 1.0f, 1.0f, 1.0f);
		kmMat4RotationAxisAngle(&rotMatrix, &axis, CC_DEGREES_TO_RADIANS(rotation));
		rotation += 1.0f;
		if (rotation > 360.0f)
		{
		rotation = 0.0f;
		}
		// 平移
		kmMat4 moveMatrix;kmMat4Identity(&moveMatrix);
		kmMat4Translation(&moveMatrix, 0.0f, 0.0f, 1.0f);】
		*/

		kmMat4 modelMatrix;kmMat4Identity(&modelMatrix);
		kmMat4Multiply(&modelMatrix, &modelMatrix, &m_moveMatrix);
		kmMat4Multiply(&modelMatrix, &modelMatrix, &m_rotMatrix);
		kmMat4Multiply(&modelMatrix, &modelMatrix, &m_scaleMatrix);

		//////////////////////////////////////////////////////////////////////////
		// 定义view
		kmMat4 viewMatrix;kmMat4Identity(&viewMatrix);
		kmVec3 eye, center, up;
		// 第一组eyex, eyey,eyez 相机在世界坐标的位置
		// 第二组centerx,centery,centerz 相机镜头对准的物体在世界坐标的位置
		// 第三组upx,upy,upz 相机向上的方向在世界坐标中的方向
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		//kmVec3Fill(&eye, 0.0f, 0.0f, 20.0f);
		//kmVec3Fill(&center, 0.0f, 0.0f, 0.0f);
		//kmVec3Fill(&up, 0.0f, 1.0f, 0.0f);
		float zeye = CCDirector::sharedDirector()->getZEye();
		kmVec3Fill( &eye, size.width/2, size.height/2, zeye );
		kmVec3Fill( &center, size.width/2, size.height/2, 0.0f );
		kmVec3Fill( &up, 0.0f, 1.0f, 0.0f);
		kmMat4LookAt(&viewMatrix, &eye, &center, &up);

		//////////////////////////////////////////////////////////////////////////
		// 构造MVP
		// MV矩阵
		kmMat4 matrixMV;kmMat4Identity(&matrixMV);
		kmMat4Multiply(&matrixMV, &viewMatrix, &modelMatrix);

		// MVP矩阵
		kmMat4 matrixMVP;kmMat4Identity(&matrixMVP);
		kmMat4 matrixP;kmMat4Identity(&matrixP);
		kmGLGetMatrix(KM_GL_PROJECTION, &matrixP);
		kmMat4Multiply(&matrixMVP, &matrixP, &matrixMV);

		//////////////////////////////////////////////////////////////////////////
		GLuint mvpUniform = glGetUniformLocation(m_glProgram->getProgram(), "MVP");
		m_glProgram->setUniformLocationWithMatrix4fv(mvpUniform, matrixMVP.mat, 1);

		glBindVertexArray(m_uVao);
		// uniform
		//GLuint uColorLocation = glGetUniformLocation(m_glProgram->getProgram(), "u_color");
		//float uColor[] = {1.0, 1.0, 0.6, 1.0};
		//glUniform4fv(uColorLocation, 1, uColor);
		ccGLBindTexture2D(m_pTexture->getTexture()->getName());

		// 36 = 12 * 3（12个三角形，每个三角形需要3个顶点）
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// 必须这么做，否则2D元素不显示，因为openGL变化是一个“马尔科夫变化”
		//kmGLPushMatrix();
		//kmGLLoadIdentity();
		//kmGLPopMatrix();

		// 关闭深度测试
		glDisable(GL_DEPTH_TEST);
	}
}

void Sprite3D::setPosition3D( float x, float y, float z )
{
	kmMat4Translation(&m_moveMatrix, x, y, z);
}

Vector3D Sprite3D::getPosition3D()
{
	return Vector3D(m_moveMatrix.mat[12], m_moveMatrix.mat[13], m_moveMatrix.mat[14]);
}

void Sprite3D::setScale3D( float fScale )
{
	kmMat4Scaling(&m_scaleMatrix, fScale, fScale, fScale);
}

void Sprite3D::setRotX3D( float fDegree )
{
	kmVec3 axis;
	kmVec3Fill(&axis, 1.0f, 0.0f, 0.0f);
	kmMat4RotationAxisAngle(&m_rotMatrix, &axis, CC_DEGREES_TO_RADIANS(fDegree));
}

void Sprite3D::setRotY3D( float fDegree )
{
	kmVec3 axis;
	kmVec3Fill(&axis, 0.0f, 1.0f, 0.0f);
	kmMat4RotationAxisAngle(&m_rotMatrix, &axis, CC_DEGREES_TO_RADIANS(fDegree));
}

void Sprite3D::setRotZ3D( float fDegree )
{
	kmVec3 axis;
	kmVec3Fill(&axis, 0.0f, 0.0f, 1.0f);
	kmMat4RotationAxisAngle(&m_rotMatrix, &axis, CC_DEGREES_TO_RADIANS(fDegree));
}

void Sprite3D::setRotAxis3D( kmVec3 axis, float fDegree )
{
	kmMat4RotationAxisAngle(&m_rotMatrix, &axis, CC_DEGREES_TO_RADIANS(fDegree));
}

void Sprite3D::runRotation( kmVec3 axis, float fDegreeOffset )
{
	unschedule(schedule_selector(Sprite3D::updateRotation));
	m_rotationAxis = axis;
	m_rotationOffsetMax = fDegreeOffset;
	schedule(schedule_selector(Sprite3D::updateRotation));
}

void Sprite3D::runRotationFoever( kmVec3 axis )
{
	m_rotationAxis = axis;
	schedule(schedule_selector(Sprite3D::updateRotationFoever));
}

void Sprite3D::updateRotation( float dt )
{
	m_rotationOffset += 1.0f;
	if (m_rotationOffset > m_rotationOffsetMax)
	{
		unschedule(schedule_selector(Sprite3D::updateRotationFoever));
	}
	else
	{
		setRotAxis3D(m_rotationAxis, m_rotationOffset);
	}
	
}

void Sprite3D::updateRotationFoever( float dt )
{
	m_rotationOffset += 1.0f;
	setRotAxis3D(m_rotationAxis, m_rotationOffset);
}

void Sprite3D::fillVertexList( std::vector<Vertex3D>& vertexList )
{
	m_vertexList.clear();
	m_vertexList = vertexList;
}

void Sprite3D::fillIndexList( std::vector<int>& indexList )
{
	m_indexList.clear();
	m_indexList = indexList;
}

void Sprite3D::runMove3D(Vector3D vecDirection)
{
	unschedule(schedule_selector(Sprite3D::updateMove3D));
	m_vecDirection = vecDirection;
	schedule(schedule_selector(Sprite3D::updateMove3D));
}

void Sprite3D::updateMove3D(float dt)
{
	Vector3D posNow = getPosition3D();
	setPosition3D(m_vecDirection.m_fVec[0] / 100.0f,
		m_vecDirection.m_fVec[1] / 100.0f,
		m_vecDirection.m_fVec[2] / 100.0f);
}
