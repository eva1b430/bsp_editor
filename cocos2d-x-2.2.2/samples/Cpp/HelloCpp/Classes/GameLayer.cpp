#include "GameLayer.h"
#include "AppMacros.h"
#include "Sprite3D.h"
#include "BSPCompiler.h"
USING_NS_CC;

GameLayer::GameLayer()
// 	: m_pBSP(NULL)
// 	, m_pVehicle(NULL)
{

}

GameLayer::~GameLayer()
{
// 	if (m_pBSP)
// 	{
// 		delete m_pBSP;
// 		m_pBSP = NULL;
// 	}
	
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 225)) )
    {
        return false;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	// ÄÚ´æÐ¹Â¶
 	m_pBSP = new BSPCompiler;
 	m_pBSP->addToCCNode(this);
 
	m_pVehicle = Sprite3D::create();
	Vertex3D pos3D = m_pBSP->getRootPosition3D();
	addChild(m_pVehicle);
	m_pVehicle->setPosition3D(pos3D.Position[0], pos3D.Position[1], pos3D.Position[2]);
	m_pVehicle->setScale3D(10.0f);
	m_pVehicle->setRotX3D(90.0f);
	m_pVehicle->setPosition3D(winSize.width / 2, winSize.height / 2, 0.0f);

	kmVec3 axis;
	kmVec3Fill(&axis, 1.0f, 1.0f, 1.0f);
	m_pVehicle->runRotationFoever(axis);
	
    return true;
}

void GameLayer::onEnter()
{
	CCLayerColor::onEnter();

	// Ìí¼Ó
	scheduleUpdate();
}

void GameLayer::onExit()
{
	// Ìí¼Ó
	unscheduleUpdate();

	CCLayerColor::onExit();
}

void GameLayer::update(float delta)
{

}

bool GameLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void GameLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void GameLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
 	if (!m_pVehicle)
 	{
 		return ;
 	}
 
 	//CCPoint pos = CCDirector::sharedDirector()->convertToGL(pTouch->getLocation());
 
 	CCPoint pos = pTouch->getLocation();
 	m_pVehicle->setPosition3D(pos.x, pos.y, 2.0f);
}