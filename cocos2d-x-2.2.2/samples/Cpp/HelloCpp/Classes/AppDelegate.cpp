/****************************************************************************
Copyright (c) 2010-2013 cocos2d-x.org
Copyright (c) Microsoft Open Technologies, Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "AppDelegate.h"

#include <vector>
#include <string>

#include "GameLayer.h"
#include "Sprite3D.h"
#include "AppMacros.h"


USING_NS_CC;
using namespace std;

AppDelegate::AppDelegate()
	: m_pLayer3D(NULL)
{

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	CCDirector* pDirector = CCDirector::sharedDirector();
	CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	pDirector->setOpenGLView(pEGLView);
	pDirector->setDisplayStats(true);
	pDirector->setAnimationInterval(1.0 / 60);

	//pEGLView->setDesignResolutionSize(800, 600, kResolutionShowAll);

    // create a scene. it's an autorelease object
	cocos2d::CCScene* pGameScene = cocos2d::CCScene::create();
	m_pLayer3D = GameLayer::create();
	pGameScene->addChild(m_pLayer3D);

	Sprite3D* pCube = Sprite3D::create();
	m_pLayer3D->addChild(pCube);
	pCube->set2DEnable(true);
	pCube->setScale3D(20.0f);
	pCube->setPosition3D(400.f, 200.0f, 0.0f);

	//Sprite3D* pSprite3D = Sprite3D::create();
	//pLayer->addChild(pSprite3D);
	//pSprite3D->setPosition3D(3.0f, 3.0f, 0.0f);
	//kmVec3 axis;
	//kmVec3Fill(&axis, 1.0f, 0.0f, 0.0f);
	//pSprite3D->runRotation(axis, 180.0f);

	//Sprite3D* pSprite3D2 = Sprite3D::create();
	//pLayer->addChild(pSprite3D2);
	//pSprite3D2->setPosition3D(-3.0f, 3.0f, 0.0f);
	//kmVec3Fill(&axis, 0.0f, 0.0f, 1.0f);
	//pSprite3D2->runRotationFoever(axis);

	//Sprite3D* pSprite3D3 = Sprite3D::create();
	//pLayer->addChild(pSprite3D3);
	//pSprite3D3->setPosition3D(0.0f, 0.0f, 0.0f);
	//pSprite3D3->setRotX3D(30);
	//kmVec3Fill(&axis, 1.0f, 1.0f, 1.0f);
	//pSprite3D3->runRotationFoever(axis);

	//CCSprite* pSprite = CCSprite::create("Texture/coin.png");
	//pLayer->addChild(pSprite);
	//pSprite->setPosition(ccp(400.0f, 300.0f));
	//pSprite->setScale(0.6f);

    // run
    pDirector->runWithScene(pGameScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
