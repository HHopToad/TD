//
//  PlayLayer.cpp
//  thiefTD
//
//  Created by cocos2d-x on 14-4-11.
//
//
#define MAP_WIDTH (16)
#define MAP_HEIGHT (9)

#include "PlayLayer.h"
#include "GameManager.h"
#include "SuccessfulScene.h"
#include "FailedScene.h"
#include "LevelScene.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
using namespace CocosDenshion;

PlayLayer::PlayLayer()
	:isTouchEnable(false)
	,spriteSheet(NULL)
	,map(NULL)
	,objects(NULL)
	,pointsVector(NULL)
	,chooseTowerpanel(NULL)
	,towerMatrix(NULL)
	,groupCounter(0)
	,money(0)
	,playHpBar(NULL)
	,playHpPercentage(100)
	,moneyLabel(NULL)
	,groupLabel(NULL)
	,groupTotalLabel(NULL)
	,isSuccessful(false)
{
}

PlayLayer::~PlayLayer()
{
	if (towerMatrix) {
		free(towerMatrix);
	}
	pointsVector.clear();
}

Scene *PlayLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = PlayLayer::create();
	scene->addChild(layer);
	return scene;
}

bool PlayLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	enemyCounter=0;
	Size winSize = Director::getInstance()->getWinSize();
	instance = GameManager::getInstance();

	auto gameBg = Sprite::create(instance->getCurBgName());
	gameBg->setPosition (Point(winSize.width / 2 ,winSize.height / 2));
	addChild(gameBg, -20);

	map = TMXTiledMap::create(instance->getCurMapName());

	//add by  
	bgLayer = map->getLayer("env");
	bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
	bgLayer->setPosition(Point(winSize.width / 2 ,winSize.height / 2));


	bgLayer = map->getLayer("bg");
	bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
	bgLayer->setPosition(Point(winSize.width / 2 ,winSize.height / 2));
	objects = map->getObjectGroup("obj");
	this->addChild(map, -10);

	initToolLayer();

	offX = ( map->getContentSize().width - winSize.width )/ 2;
	initPointsVector(offX);
	schedule(schedule_selector(PlayLayer::logic), 2.0f);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(PlayLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//add by  
	isDrawed=false;
	draw = DrawNode::create();
	draw->retain();
	currTower=NULL;
	chooseUpgradepanel=NULL;


	scheduleUpdate();

	int arraySize = sizeof(TowerBase *) * MAP_WIDTH * MAP_HEIGHT;
	towerMatrix = (TowerBase **)malloc(arraySize);
	memset((void*)towerMatrix, 0, arraySize);

	for (int row = 0; row < MAP_HEIGHT; row++) {
		for (int col = 0; col < MAP_WIDTH; col++) {
			towerMatrix[row * MAP_WIDTH + col] = NULL;
		}
	}
	return true;
}

void PlayLayer::initPointsVector(float offX)
{
	Node *runOfPoint = NULL;
	int count = 0;
	ValueMap point;

	//by  
	char countBuf1[16] = "";
	sprintf(countBuf1, "%d", count);
	auto moneyText = countBuf1;
	//point = objects->getObject(std::to_string(count));
	point = objects->getObject(moneyText);
	while (point.begin()!= point.end())
	{
		float x = point.at("x").asFloat();
		float y = point.at("y").asFloat();
		runOfPoint = Node::create();
		runOfPoint->setPosition(Point(x - offX, y ));
		this->pointsVector.pushBack(runOfPoint);
		count++;

		//by  
		char countBuf2[16] = "";
		sprintf(countBuf2, "%d", count);
		auto moneyText = countBuf2;
		//point = objects->getObject( std::to_string(count));
		point = objects->getObject( moneyText);
	}
	runOfPoint = NULL;
}

void PlayLayer::initToolLayer()
{
	auto size = Director::getInstance()->getWinSize();
	//add by  
	auto zoom = size.height / 864;
	toolLayer = Layer::create();
	addChild(toolLayer);

	spritetool = Sprite::createWithSpriteFrameName("status.png");
	//auto spritetool = Sprite::create("status.png");

	//add by  
	auto statussize=spritetool->getContentSize();
	//auto patchsize=(size.width - statussize.width)/2;

	spritetool->setAnchorPoint(Point(0.5f, 1));
	spritetool->setPosition (Point(size.width / 2, size.height));
	toolLayer->addChild(spritetool);

	//������� 54������370������ 484������ 684������ 790������1060,add by  
	money = instance->getMoney();
	moneyLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
	// moneyLabel->setPosition(Point(spritetool->getContentSize().width / 8, spritetool->getContentSize().height / 2));
	//���ڸ�ͼƬ���������Ź�������Ҫ��Ӧ�������ش���
	moneyLabel->setPosition(Point( 54* zoom, spritetool->getContentSize().height / 2));
	moneyLabel->setAnchorPoint(Point(0, 0.5f));
	//modify by  
	char countBuf3[16] = "";
	sprintf(countBuf3, "%d", money);
	auto moneyText = countBuf3;
	//
	//auto moneyText = std::to_string(money);
	moneyLabel->setString(moneyText);
	spritetool->addChild(moneyLabel);


	//�����ķ���
	//int groupTotal = instance->getGroupNum();	
	int temp =1;
	char countBuf5[16] = "";
	sprintf(countBuf5, "%d",temp);
	groupcurrLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
	auto groupInfoText2 = countBuf5;
	groupcurrLabel->setPosition(Point(370 * zoom , spritetool->getContentSize().height / 2 ));
	groupcurrLabel->setAnchorPoint(Point(0.0f , 0.5f));
	groupcurrLabel->setString(groupInfoText2);
	spritetool->addChild(groupcurrLabel);
	//�ܹ�����
	int groupTotal = instance->getGroupNum();
	groupLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
	groupLabel->setPosition(Point(484 * zoom , spritetool->getContentSize().height / 2 ));
	groupLabel->setAnchorPoint(Point(0.0f , 0.5f));
	char countBuf4[16] = "";
	sprintf(countBuf4, "%d", groupTotal);
	auto groupInfoText = countBuf4;
	groupLabel->setString(groupInfoText);
	spritetool->addChild(groupLabel);








	//by  
	//��ǰ���Ĺ���
	char countBuf6[16] = "";
	sprintf(countBuf6, "%d", temp);
	auto groupTotalText3 = countBuf6;	
	numcurrLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
	numcurrLabel->setPosition(Point( 684 * zoom , spritetool->getContentSize().height / 2 ));
	numcurrLabel->setAnchorPoint(Point(0.0f , 0.5f));
	numcurrLabel->setString(groupTotalText3);
	spritetool->addChild(numcurrLabel);

	//��ǰ���Ĺ��� ����
	char countBuf7[16] = "";
	auto en= instance->getEnemyNum();	
	sprintf(countBuf7, "%d", en);
	auto groupTotalText4 = countBuf7;	
	numLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
	numLabel->setPosition(Point( 790 * zoom , spritetool->getContentSize().height / 2 ));
	numLabel->setAnchorPoint(Point(0.0f , 0.5f));
	numLabel->setString(groupTotalText4);
	spritetool->addChild(numLabel);

	//��ǰ����ֵ�� ����
	char countBuf8[16] = "";
	sprintf(countBuf8, "100");
	auto groupTotalText5 = countBuf8;	
	hpLabel = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");
	hpLabel->setPosition(Point( 1060 * zoom , spritetool->getContentSize().height / 2 ));
	hpLabel->setAnchorPoint(Point(0.0f , 0.5f));
	hpLabel->setString(groupTotalText5);
	spritetool->addChild(hpLabel);




	// back
	//add by  
	Sprite *backItem1 = CCSprite::createWithSpriteFrameName("btn_back.png");
	Sprite *backItem2 = CCSprite::createWithSpriteFrameName("btn_back_press.png");
	MenuItemSprite *pPauseItem = MenuItemSprite::create(backItem1, backItem2, CC_CALLBACK_1(PlayLayer::menuBackCallback, this));
	pPauseItem->setPosition(Point(spritetool->getContentSize().width + backItem1->getContentSize().width / 2, spritetool->getContentSize().height / 2));

	pPauseItem->setAnchorPoint(Point(0, 0.5f));
	Menu* pMenu = Menu::create(pPauseItem, NULL);
	pMenu->setPosition(Point::ZERO);
	spritetool->addChild(pMenu);
}

void PlayLayer::menuBackCallback(Ref* pSender)
{
	int effect= UserDefault::getInstance()->getIntegerForKey("effect");
	if ( 1 == effect )
	{
		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);

	}
	//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str(), false);
	instance->clear();
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, LevelScene::create()));
}

GroupEnemy* PlayLayer::currentGroup()
{
	GroupEnemy* groupEnemy;
	if(!instance->groupVector.empty() )
	{
		groupEnemy = (GroupEnemy*)instance->groupVector.at(groupCounter);
	}
	else{
		groupEnemy =NULL;
	}
	return groupEnemy;
}

GroupEnemy* PlayLayer::nextGroup()
{
	if(instance->groupVector.empty())
	{
		return NULL;
	}

	if (groupCounter < instance->getGroupNum() - 1)
	{
		groupCounter++;
	}
	else{
		isSuccessful = true;
	}
	GroupEnemy* groupEnemy = (GroupEnemy*)instance->groupVector.at(groupCounter);
	return groupEnemy;

}

void PlayLayer::addEnemy()
{
	GameManager *instance = GameManager::getInstance();

	GroupEnemy* groupEnemy = this->currentGroup();
	if(groupEnemy == NULL)
	{
		return;
	}
	auto restEnemyNum = groupEnemy->getEnemyTotal();
	if( restEnemyNum <= 0){
		groupEnemy->setIsFinishedAddGroup(true);
		//add by  
		return;
	}

	restEnemyNum--;
	groupEnemy->setEnemyTotal(restEnemyNum);

	//add by  ,��̬�޸Ĺָ���
	int temp = instance->getEnemyNum();
	temp= temp-restEnemyNum;
	char countBuf8[16] = "";
	sprintf(countBuf8, "%d", temp);
	auto moneyText = countBuf8;
	//auto moneyText = std::to_string(money);
	numcurrLabel->setString(moneyText);


	EnemyBase* enemy = NULL;

	//add by   ȥ������ ����
	if(groupEnemy->getType1Total() > 0){
		//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
		enemy = Thief::createThief(pointsVector, groupEnemy->getType1Hp());
		groupEnemy->setType1Total(groupEnemy->getType1Total() - 1);
	}
	else if(groupEnemy->getType2Total() > 0){
		// SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
		enemy = Pirate::createPirate(pointsVector, groupEnemy->getType2Hp());
		groupEnemy->setType2Total(groupEnemy->getType2Total() - 1);
	}
	else if(groupEnemy->getType3Total() > 0){
		enemy = Bandit::createBandit(pointsVector, groupEnemy->getType3Hp());
		//SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str(), false);
		groupEnemy->setType3Total(groupEnemy->getType3Total() - 1);
	}

	this->addChild(enemy, 10);
	instance->enemyVector.pushBack(enemy);
}

void PlayLayer::logic(float dt)
{
	GroupEnemy* groupEnemy = this->currentGroup();

	if(groupEnemy == NULL)
	{
		return;
	}
	if(groupEnemy->getIsFinishedAddGroup() ==true  && instance->enemyVector.size() == 0 && groupCounter < instance->getGroupNum())
	{
		groupEnemy = this->nextGroup();
		int groupTotal = instance->getGroupNum();


		//by   ��ǰ����
		char countBuf5[16] = "";
		sprintf(countBuf5, "%d", groupCounter+1);
		auto groupInfoText = countBuf5;
		groupcurrLabel->setString(groupInfoText);


		////by  ��ǰ���ĵ�ǰ����
		char countBuf6[16] = "";		
		int temp=groupEnemy->getEnemyTotal();
		instance->setEnemyNum(temp);
		sprintf(countBuf6, "%d", temp);
		groupInfoText = countBuf6;
		numLabel->setString(groupInfoText);

		//by  ��ǰ���Ĺ�������
		char countBuf7[16] = "";
		temp=1;
		sprintf(countBuf7, "%d", temp);
		groupInfoText = countBuf7;
		numcurrLabel->setString(groupInfoText);

	}
	this->addEnemy();
}

bool PlayLayer::onTouchBegan(Touch *touch, Event *event)
{

	//add by 
	//ȥ��draw �е�Ȧ
	draw->clear();
	this->removeChild(draw);
	isDrawed = false;
	//********************************ȥ���������
	this->removeChild(chooseUpgradepanel);
	chooseUpgradepanel=NULL;
	//

	this->removeChild(chooseTowerpanel);
	chooseTowerpanel = NULL;
	auto location = touch->getLocation();


	checkAndAddTowerPanle(location);
	return true;
}

void PlayLayer::addTowerChoosePanel(Point point)
{
	chooseTowerpanel = TowerPanleLayer::create();
	chooseTowerpanel->setPosition(point);
	this->addChild(chooseTowerpanel);
}
void PlayLayer::addTowerUpgradePanel(Point point)
{
	chooseUpgradepanel = TowerUpgradePanleLayer::create();
	chooseUpgradepanel->setPosition(point);
	this->addChild(chooseUpgradepanel);
}
Point PlayLayer::convertTotileCoord(Point position)
{
	int x = (position.x + offX)/ map->getContentSize().width * map->getMapSize().width;
	int y =map->getMapSize().height- position.y / map->getContentSize().height * map->getMapSize().height;
	return Point(x, y);
}
Point PlayLayer::convertToMatrixCoord(Point position)
{
	int x = (position.x + offX)/ map->getContentSize().width * map->getMapSize().width;
	int y = position.y / map->getContentSize().height * map->getMapSize().height;
	return Point(x, y);
}

void PlayLayer::checkAndAddTowerPanle(Point position)
{
	Point towerCoord = convertTotileCoord(position);
	Point matrixCoord = convertToMatrixCoord(position);

	int gid = bgLayer->getTileGIDAt(towerCoord);
	auto tileTemp = map->getPropertiesForGID(gid).asValueMap();
	int MatrixIndex = static_cast<int>( matrixCoord.y * MAP_WIDTH + matrixCoord.x );

	int TouchVaule;
	if (tileTemp.empty())
	{
		TouchVaule = 0;
	}else
	{
		TouchVaule = tileTemp.at("canTouch").asInt();
	}
	auto tileWidth = map->getContentSize().width / map->getMapSize().width;
	auto tileHeight = map->getContentSize().height / map->getMapSize().height;
	towerPos = Point((towerCoord.x * tileWidth) + tileWidth/2 -offX, map->getContentSize().height - (towerCoord.y * tileHeight) - tileHeight/2);

	if (1 == TouchVaule && towerMatrix[MatrixIndex]==NULL)
	{
		addTowerChoosePanel(towerPos);
	}
	else
	{
		//add by  to draw the scope
		if ( 1 == TouchVaule && towerMatrix[MatrixIndex]!=NULL )
		{

			Point towerCoord = convertTotileCoord(position);
			Point matrixCoord = convertToMatrixCoord(position);

			auto tower= towerMatrix[MatrixIndex];
			//���õ�ǰѡ������level�ȼ������ڴ��ݸ�upgradepanel
			int ll=tower->getLevel();
			instance->setLev(ll);
			auto tp=tower->getTowerType();
			instance->setTp(tp);
			//auto s=tower->getContentSize();
			//��������Χ
			int r=tower->getScope();	

			if( isDrawed == false)
			{
				this->addChild(draw, 10);
				//draw->drawDot(position, r, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
				towerPos = Point((towerCoord.x * tileWidth) + tileWidth/2 -offX, map->getContentSize().height - (towerCoord.y * tileHeight) - tileHeight/2);
				draw->drawDot(towerPos, r, Color4F(0.2,0.3,0.6, 0.3));
				isDrawed = true;

				//add upgrade panel				
				currTower =tower;
				//add to use different pic by tp
				addTowerUpgradePanel(towerPos);
				return;
			}
			else 
			{
				return;
			}


		}
		//*********************************************

		SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
		//auto tips = Sprite::createWithSpriteFrameName("no.png");
		//add by 
		//auto tips = Sprite::create("nopark.png");
		auto tips = Sprite::createWithSpriteFrameName("nopark.png");
		tips->setPosition(towerPos);
		this->addChild(tips);
		tips->runAction(Sequence::create(DelayTime::create(0.8f),
			CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
			NULL));
	}
}

void PlayLayer::addTower()
{
	if(chooseTowerpanel)
	{
		auto type = chooseTowerpanel->getChooseTowerType();
		if(type == TowerType::ANOTHER)
		{
			return;
		}
		Point matrixCoord = convertToMatrixCoord(towerPos);
		int MatrixIndex = static_cast<int>( matrixCoord.y * MAP_WIDTH + matrixCoord.x );
		bool noMoneyTips = false;
		TowerBase* tower = NULL;
		if( type == TowerType::ARROW_TOWER )
		{
			if( money >= 120 )
			{
				tower = ArrowTower::create();
				money -= 120;
			}
			else
				noMoneyTips = true;
		}
		else if( type == TowerType::ATTACK_TOWER )
		{
			if( money >= 150 )
			{
				tower = AttackTower::create();
				money -= 150;
			}
			else
				noMoneyTips = true;
		}
		else if( type == TowerType::MULTIDIR_TOWER )
		{
			if( money >= 400 )
			{
				tower = MultiDirTower::create();
				money -= 400;
			}else
				noMoneyTips = true;
		}
		if(tower != NULL)
		{
			tower->setPosition(towerPos);
			tower->runAction(Sequence::create(FadeIn::create(1.0f),NULL));
			this->addChild(tower);
			towerMatrix[MatrixIndex] =  tower;
			//add by  ����towerλ��
			tower->setTowerPos(towerPos);
		}
		type =  TowerType::ANOTHER;
		chooseTowerpanel->setChooseTowerType(type);
		this->removeChild(chooseTowerpanel);
		chooseTowerpanel = NULL;

		//add by 
		instance->setMoney(money);


		//by 
		char countBuf8[16] = "";
		sprintf(countBuf8, "%d", money);
		auto moneyText = countBuf8;
		//auto moneyText = std::to_string(money);
		moneyLabel->setString(moneyText);



		if( noMoneyTips == true )
		{
			SimpleAudioEngine::getInstance()->playEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str(), false);
			//auto tips = Sprite::createWithSpriteFrameName("nomoney_mark.png");
			//add by 
			auto tips = Sprite::createWithSpriteFrameName("tip.png");
			tips->setPosition(towerPos);
			this->addChild(tips);
			tips->runAction(Sequence::create(DelayTime::create(0.5f),
				CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tips)),
				NULL));
		}
	}
}

void PlayLayer::upgradeTower(int tt,int lv)
{
	Point matrixCoord = convertToMatrixCoord(towerPos);
	int MatrixIndex = static_cast<int>( matrixCoord.y * MAP_WIDTH + matrixCoord.x );
	TowerBase* tower;
	// ���Ƴ��͵ȼ���,�Ƴ�ǰ�߻�ý����Ϣ
	tower = towerMatrix[MatrixIndex];
	int m= tower->getTowerValue();
	
	if ( tt == 0 )//��ʾ��һ����
	{


		if( money < m )
			return;
		money=money-m;
		tower->removeFromParent();
		towerMatrix[MatrixIndex]=NULL;
		instance->setMoney(money);
		char countBuf8[16] = "";
		sprintf(countBuf8, "%d", money);
		auto moneyText = countBuf8;
		moneyLabel->setString(moneyText);

		//���������������
		if( lv == 0 )
		{
			tower = ArrowTower1::create();	
			tower->setLevel(1);		
		}
		else if ( lv == 1)
		{
			tower = ArrowTower2::create();	
			tower->setLevel(2);	
		}
		else 
		{
			tower = ArrowTower3::create();	
			tower->setLevel(3);	
		}

		if(tower != NULL)
		{
			tower->setTowerPos(towerPos);
			//tower->runAction(Sequence::create(FadeIn::create(1.0f),NULL));
			this->addChild(tower);
			towerMatrix[MatrixIndex] =  tower;
			tower->setPosition(towerPos);
		}
		auto type =  TowerUpgrade::OTHER;
		chooseUpgradepanel->setChooseTowerUpgrade(type);
		//�쳣������岢����ΪNULL��������Χ
		chooseUpgradepanel->removeFromParent();
		draw->clear();
		chooseUpgradepanel=NULL;
		return;




	}
	else if (tt == 1)//��ʾ�ڶ�����
	{

		//int m= currTower->getTowerValue();
		if( money < m )
			return;
		money=money-m;
		tower->removeFromParent();
		towerMatrix[MatrixIndex]=NULL;
		//currTower = NULL;
		instance->setMoney(money);
		char countBuf8[16] = "";
		sprintf(countBuf8, "%d", money);
		auto moneyText = countBuf8;
		//auto moneyText = std::to_string(money);
		moneyLabel->setString(moneyText);
		//���������������
		if( lv == 0 )
		{
			tower = AttackTower1::create();	
			tower->setLevel(1);		
		}
		else if ( lv == 1)
		{
			tower = AttackTower2::create();	
			tower->setLevel(2);	
		}
		else 
		{
			tower = AttackTower3::create();	
			tower->setLevel(3);	
		}

		if(tower != NULL)
		{
			tower->setTowerPos(towerPos);
			//tower->runAction(Sequence::create(FadeIn::create(1.0f),NULL));
			this->addChild(tower);
			towerMatrix[MatrixIndex] =  tower;
			tower->setPosition(towerPos);

		}


		auto type =  TowerUpgrade::OTHER;
		chooseUpgradepanel->setChooseTowerUpgrade(type);
		//�쳣������岢����ΪNULL��������Χ
		chooseUpgradepanel->removeFromParent();
		draw->clear();
		chooseUpgradepanel=NULL;

		return;
	}
	else //��ʾ��������
	{

		//int m= currTower->getTowerValue();
		if( money < m )
			return;
		money=money-m;
		tower->removeFromParent();
		towerMatrix[MatrixIndex]=NULL;
		//currTower = NULL;

		instance->setMoney(money);
		char countBuf8[16] = "";
		sprintf(countBuf8, "%d", money);
		auto moneyText = countBuf8;
		//auto moneyText = std::to_string(money);
		moneyLabel->setString(moneyText);
		//���������������
		if( lv == 0 )
		{
			tower = MultiDirTower1::create();	
			tower->setLevel(1);		
		}
		else if ( lv == 1)
		{
			tower = MultiDirTower2::create();	
			tower->setLevel(2);	
		}
		else 
		{
			tower = MultiDirTower3::create();	
			tower->setLevel(3);	
		}

		if(tower != NULL)
		{
			tower->setTowerPos(towerPos);
			//tower->runAction(Sequence::create(FadeIn::create(1.0f),NULL));
			this->addChild(tower);
			towerMatrix[MatrixIndex] =  tower;
			tower->setPosition(towerPos);

		}


		auto type =  TowerUpgrade::OTHER;
		chooseUpgradepanel->setChooseTowerUpgrade(type);
		//�쳣������岢����ΪNULL��������Χ
		chooseUpgradepanel->removeFromParent();
		draw->clear();
		chooseUpgradepanel=NULL;

		return;
	}

}

void PlayLayer::sellorupgradeTower()
{
	if(chooseUpgradepanel)
	{
		auto type = chooseUpgradepanel->getChooseTowerUpgrade();
		if( type == OTHER )
		{
			return;
		}
		Point matrixCoord = convertToMatrixCoord(towerPos);
		int MatrixIndex = static_cast<int>( matrixCoord.y * MAP_WIDTH + matrixCoord.x );
		bool noMoneyTips = false;
		TowerBase* tower = NULL;
		if( type == TowerUpgrade::UPGRADE_ONE )
		{

			//������Χ���������������ٶȿ��Զ�Ӧ����
			//��Ҫ�л�����ͼƬ

			int le = currTower->getLevel();
			int tt = currTower->getTowerType();
			//le ��ǰ���ȼ���tt��ǰ������
			if( le == 0 )
			{
				//��ȡ������,��������������
				upgradeTower(tt,le);
			}
			else if(le == 1)
			{
				upgradeTower(tt,le);
			}
			else if( le == 2)
			{
				upgradeTower(tt,le);
			}
			else if ( le == 3)
			{
				;
			}

			return;
		}
		else if( type == TowerUpgrade::SELL )//������
		{
			int m= currTower->getTowerValue();
			money=m/2+money;
			towerMatrix[MatrixIndex]=NULL;
			currTower->removeFromParent();
			currTower = NULL;
			instance->setMoney(money);
			char countBuf8[16] = "";
			sprintf(countBuf8, "%d", money);
			auto moneyText = countBuf8;
			//auto moneyText = std::to_string(money);
			moneyLabel->setString(moneyText);
			chooseUpgradepanel->removeFromParent();
			draw->clear();
			chooseUpgradepanel=NULL;
			return;
		} else
		{
			chooseUpgradepanel->removeFromParent();
			draw->clear();
			chooseUpgradepanel=NULL;
			return;

		}
	}
}

void PlayLayer::CollisionDetection()
{
	auto bulletVector = instance->bulletVector;
	auto enemyVector = instance->enemyVector;

	if(bulletVector.empty() || enemyVector.empty() ){
		return;
	}
	Vector<EnemyBase*> enemyNeedToDelete;
	Vector<Sprite*> bulletNeedToDelete;
	for (int i = 0; i < bulletVector.size(); i++)
	{
		auto bullet = bulletVector.at(i);
		//if(bullet->getParent() == NULL )
		//{
		//	return;
		//}
		//�ӵ��ĸ��ڵ���������Ҫͨ������������λ�ã��������������ӵ��ò������ڵ㡣 modified by 
		/*	auto  bulletRect = Rect(bullet->getPositionX() +bullet->getParent()->getPositionX() - bullet->getContentSize().width / 2,
		bullet->getPositionY() +bullet->getParent()->getPositionY() - bullet->getContentSize().height / 2,
		bullet->getContentSize().width,
		bullet->getContentSize().height );
		*/
		auto  bulletRect = Rect(bullet->getPositionX() ,bullet->getPositionY(),
			bullet->getContentSize().width,
			bullet->getContentSize().height );

		for (int j = 0; j < enemyVector.size(); j++)
		{
			auto enemy = enemyVector.at(j);
			//auto enemyRect = enemy->sprite->getBoundingBox();
			auto enemyRect = Rect(enemy->sprite->getPositionX() - enemy->sprite->getContentSize().width / 4,
				enemy->sprite->getPositionY()  - enemy->sprite->getContentSize().height / 4,
				enemy->sprite->getContentSize().width / 2,
				enemy->sprite->getContentSize().height / 2 );
			if (bulletRect.intersectsRect(enemyRect))
			{
				auto currHp = enemy->getCurrHp();

				//modified by  �޸ĸ������Ĺ���������Ѫ
				auto heat = bullet->getTag();
				auto attack= heat/10;//ȡʮλ��
				heat=heat%10;//ȡ��λ��


				if( attack == 1 )//����һ��������,���м���
				{
					enemy->scheduler1->setTimeScale(0.5);
					enemy->sprite->setColor(Color3B::BLUE);
					enemy->setSlow(true);
					//scheduleOnce(SEL_SCHEDULE(&PlayLayer::recoverSpeed ,this,enemy),2.0f);
				}
				else if (attack == 2)//���ڶ���������,���и��ʱ���,2,5,10��
				{ 
					int i = CCRANDOM_0_1()* 100;
					if (  i >= 25 && i < 50 )
					{
						heat = heat * 2;
						//modify by 
						auto label = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");	
						char countBuf3[16] = "";
						sprintf(countBuf3, "X 2");
						auto moneyText = countBuf3;
						//auto moneyText = std::to_string(money);
						label->setString(moneyText);
						auto p = bullet->getPosition();
						label->setPosition(p);
						enemy->addChild(label);

						CCFiniteTimeAction* actiondone= CallFuncN::create(this,callfuncN_selector(PlayLayer::removelabel));

						CCFiniteTimeAction* action = ScaleBy::create(1, 0.1,0.1,0.1);


						label->runAction(Sequence::create(action,actiondone,NULL));
						//two shot

					}
					else if(  i >= 5 && i < 25 )
					{
						heat = heat * 3;
						//three shot						
						//modify by 
						auto label = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");	
						char countBuf3[16] = "";
						sprintf(countBuf3, "X 3");
						auto moneyText = countBuf3;
						//auto moneyText = std::to_string(money);
						label->setString(moneyText);
						auto p = bullet->getPosition();
						label->setPosition(p);
						enemy->addChild(label);

						CCFiniteTimeAction* actiondone= CallFuncN::create(this,callfuncN_selector(PlayLayer::removelabel));

						CCFiniteTimeAction* action = ScaleBy::create(1, 0.1,0.1,0.1);


						label->runAction(Sequence::create(action,actiondone,NULL));

					}
					else if( i > 1 && i < 5 ) 
					{
						//five shot
						heat = heat * 5;						
						//modify by 
						auto label = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");	
						char countBuf3[16] = "";
						sprintf(countBuf3, "X 5");
						auto moneyText = countBuf3;
						//auto moneyText = std::to_string(money);
						label->setString(moneyText);
						auto p = bullet->getPosition();
						label->setPosition(p);
						enemy->addChild(label);

						CCFiniteTimeAction* actiondone= CallFuncN::create(this,callfuncN_selector(PlayLayer::removelabel));

						CCFiniteTimeAction* action = ScaleBy::create(1, 0.1,0.1,0.1);


						label->runAction(Sequence::create(action,actiondone,NULL));
					}
					else if(  i == 1)
					{

						heat = heat * 10;	
						//modify by 
						auto label = Label::createWithBMFont("fonts/bitmapFontChinese.fnt", " ");	
						char countBuf3[16] = "";
						sprintf(countBuf3, "X 10");
						auto moneyText = countBuf3;
						//auto moneyText = std::to_string(money);
						label->setString(moneyText);
						auto p = bullet->getPosition();
						label->setPosition(p);
						enemy->addChild(label);

						CCFiniteTimeAction* actiondone= CallFuncN::create(this,callfuncN_selector(PlayLayer::removelabel));

						CCFiniteTimeAction* action = ScaleBy::create(1, 0.1,0.1,0.1);


						label->runAction(Sequence::create(action,actiondone,NULL));
					}		//ten shot
					else
					{
						;//do nothing,���˺������κδ���
					}


				}
				else //��������������,���м��٣���ʱ�����κδ���
				{
					;

				}



				currHp = currHp - heat;
				//currHp--;
				enemy->setCurrHp( currHp );

				auto currHpPercentage = enemy->getHpPercentage();
				//auto offHp = 100 / enemy->getMaxHp();
				//currHpPercentage -= offHp;
				/*if(currHpPercentage < 0){
				currHpPercentage = 0;
				}*/
				if( currHp < 0 ) 
				{
					currHpPercentage = 0;
				}
				currHpPercentage = currHp*100 /enemy->getMaxHp();



				enemy->setHpPercentage(currHpPercentage);
				enemy->getHpBar()->setPercentage(currHpPercentage);

				if(currHp <= 0)
				{
					enemyNeedToDelete.pushBack(enemy);
					auto valueMoney = enemy->getVaule();
					money += valueMoney;

					//by 
					char countBuf9[16] = "";
					sprintf(countBuf9, "%d", money);
					auto moneyText = countBuf9;
					// auto moneyText = std::to_string(money);
					moneyLabel->setString(moneyText);
				}
				bulletNeedToDelete.pushBack( bullet);
				break;
			}
		}
		for (EnemyBase* enemyTemp : enemyNeedToDelete)
		{
			enemyTemp->enemyExpload();
			instance->enemyVector.eraseObject(enemyTemp);
		}
		enemyNeedToDelete.clear();
	}

	for (Sprite* bulletTemp : bulletNeedToDelete)
	{
		instance->bulletVector.eraseObject(bulletTemp);
		bulletTemp->removeFromParent();
	}
	bulletNeedToDelete.clear();
}

//���ûָ������ٶȵĺ���
void PlayLayer::recoverSpeed(EnemyBase* enemy)
{

	if(enemy == NULL )
		return;
	else
	{
		enemy->sprite->setColor(ccc3(0,0,0));
		enemy->scheduler1->setTimeScale(1);
	}
}


void PlayLayer::enemyIntoHouse()
{
	auto enemyVector = instance->enemyVector;
	int playHp;
	for (int i = 0; i < enemyVector.size(); i++)
	{
		auto enemy = enemyVector.at(i);
		if( enemy->getEnemySuccessful())
		{
			instance->enemyVector.eraseObject(enemy);
			enemy->removeFromParent();
			playHp = getPlayHpPercentage() - 10;
			if(playHp > 0){
				setPlayHpPercentage(playHp);


				//add by ,��̬�޸�����
				char countBuf8[16] = "";
				sprintf(countBuf8, "%d", playHp);
				auto moneyText = countBuf8;
				hpLabel->setString(moneyText);

				//��ͼ�λ�һ��ȥ��
				//                playHpBar->setPercentage(playHp);
			}
			else{
				instance->clear();
				Director::getInstance()->replaceScene(TransitionFade::create(0.1f, FailedScene::create()));
			}
		}
	}
}

void PlayLayer::update(float dt)
{
	addTower();
	//add by  
	sellorupgradeTower();

	CollisionDetection();
	enemyIntoHouse();


	//debug for  
	//instance->clear();
	//  // Director::getInstance()->replaceScene(TransitionFade::create(0.1f, SuccessfulScene::create()));
	//Director::getInstance()->replaceScene(TransitionFade::create(0.1f, FailedScene::create()));
	//---------------

	if(isSuccessful)
	{
		isSuccessful = false;
		auto star = 0;
		auto playHp = this->getPlayHpPercentage();

		if( playHp > 0 && playHp <= 30){ star = 1;}
		else if(playHp > 30 && playHp <= 60 ){ star = 2;}
		else if(playHp > 60 && playHp <= 100 ){ star = 3;}

		if( star > UserDefault::getInstance()->getIntegerForKey(instance->getCurrLevelFile().c_str()))
		{
			UserDefault::getInstance()->setIntegerForKey(instance->getCurrLevelFile().c_str(), star);
			auto levelNum = UserDefault::getInstance()->getIntegerForKey("levelNum") + 1;
			UserDefault::getInstance()->setIntegerForKey("levelNum", levelNum);
		}

		auto nextlevel = instance->getNextLevelFile();
		UserDefault::getInstance()->setStringForKey("nextLevelFile", nextlevel);

		instance->clear();
		Director::getInstance()->replaceScene(TransitionFade::create(0.1f, SuccessfulScene::create()));
	}
}


void PlayLayer::removelabel(Node* sender)
{
	Sprite* sprite = (Sprite*) sender;
	sprite->removeFromParent();
}