//
//  PlayLayer.h
//  thiefTD
//
//  Created by cocos2d-x on 14-4-11.
//
//

#ifndef __thiefTD__PlayLayer__
#define __thiefTD__PlayLayer__

#include <iostream>
#include "cocos2d.h"
#include "Thief.h"
#include "ArrowTower.h"
#include "AttackTower.h"
#include "MultiDirTower.h"

#include "ArrowTower1.h"
#include "AttackTower1.h"
#include "MultiDirTower1.h"
#include "ArrowTower2.h"
#include "AttackTower2.h"
#include "MultiDirTower2.h"
#include "ArrowTower3.h"
#include "AttackTower3.h"
#include "MultiDirTower3.h"

#include "TowerPanleLayer.h"
#include "TowerBase.h"
//add upgrade header file
#include "TowerUpgradePanleLayer.h"
#include "GameManager.h"
#include "CCDrawingPrimitives.h"


//// 引入相关的头文件
//#include "Cocos2dx/Common/CCUMSocialSDK.h"
//#include "Cocos2dx/ShareButton/UMShareButton.h"
//
//// 使用友盟命令空间
//USING_NS_UM_SOCIAL;
USING_NS_CC;
class PlayLayer : public Layer
{
public:
    PlayLayer();
    ~PlayLayer();
    
    virtual bool init() override;
    static Scene* createScene();
    CREATE_FUNC(PlayLayer);
    
    virtual void update(float dt) override;
    virtual bool onTouchBegan(Touch *touch, Event *event) override;
    
    GroupEnemy* currentGroup();
	GroupEnemy* nextGroup();
	void addGroupEnemy();
	void logic(float dt);
	void initLabelText();

	DrawNode* draw;
	bool isDrawed;
	//******************
private:
    SpriteBatchNode *spriteSheet;
    TMXTiledMap* map;
	TMXLayer* bgLayer;
    TMXObjectGroup* objects;
    Vector<Node*> pointsVector;
    
	GameManager* instance;
    float offX;
    
	int groupCounter;

	int enemyCounter;

	int money;
    
    Label* moneyLabel;
	Label* groupLabel;
	Label* groupTotalLabel;
	Layer* toolLayer;

	//
	Label* groupcurrLabel;
	Label* numcurrLabel;
	Label* numLabel;
	Label* hpLabel;

	void initToolLayer();
	CC_SYNTHESIZE(float, playHpPercentage, PlayHpPercentage);
	CC_SYNTHESIZE_READONLY(ProgressTimer*, playHpBar, PlayHpBar);
	bool isSuccessful;
    
    bool isTouchEnable;
    TowerPanleLayer* chooseTowerpanel;
	
    void addTowerChoosePanel(Point position);
	void addTowerUpgradePanel(Point position);


    Point convertTotileCoord(Point position);
	Point convertToMatrixCoord(Point position);
	void checkAndAddTowerPanle(Point position);
	void CollisionDetection();
    void enemyIntoHouse();
    void menuBackCallback(Ref* pSender);
    
	Point towerPos;
	TowerBase* currTower;
    void initPointsVector(float offX);
    void addEnemy();
    void addTower();

	//sellorupgradeTower();
	void sellorupgradeTower();
	TowerUpgradePanleLayer* chooseUpgradepanel;
	void removelabel(Node* sender)	;
	//恢复减速的怪物速度
	void recoverSpeed(EnemyBase* enemy);
	Sprite* spritetool;

    TowerBase **towerMatrix;

	void upgradeTower(int tt,int lv);
};

#endif /* defined(__thiefTD__PlayLayer__) */
