#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"


using namespace std;
using namespace cocos2d;
class BSPCompiler;
class Sprite3D;
class GameLayer : public cocos2d::CCLayerColor
{
public:
	GameLayer();
	virtual ~GameLayer();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	virtual void onEnter();
	virtual void onExit();
	// 重载刷新函数
	virtual void update(float delta);

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    //static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameLayer);

	// 添加触摸事件
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

private:
	BSPCompiler*	m_pBSP;
	Sprite3D*		m_pVehicle;
};

#endif // __GAME_LAYER_H__
