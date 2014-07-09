#include "Enemy.h"
#include <math.h>
USING_NS_CC;

Enemy::Enemy(){
}

Enemy::~Enemy(){
}

bool Enemy::init(){
	auto enemy = Sprite::create("s1.png");
	this->addChild(enemy);
	auto hpBar = Sprite::create("hpbar.png");
	auto MaxhpBar = Sprite::create("Maxhpbar.png");
	MaxhpBar->setScale(0.06);
	this->addChild(MaxhpBar);
	auto protimer=ProgressTimer::create(hpBar);
	protimer->setType(ProgressTimer::Type::BAR);
    protimer->setMidpoint(ccp(0, 0.5));
    protimer->setBarChangeRate(ccp(1, 0));
	protimer->setPercentage(30);
	protimer->setScale(0.06);
	this->addChild(protimer);
	protimer->setPosition(0,25);
	MaxhpBar->setPosition(0,25);
	pointCount=0;
	return true;
}

bool Enemy::SetObjectGroup(TMXObjectGroup* obj){
	this->objects=obj;
	return true;
}

void Enemy::InitWayPoints(float offx){
	Node* WayPoint = NULL;
	int count = 0;
	ValueMap point;
	point=objects->getObject(std::to_string(count));
	do{
		float x=point.at("x").asFloat();
		float y=point.at("y").asFloat();
		WayPoint=Node::create();
		WayPoint->setPosition(Vec2(x-offx,y));
		this->pointsVector.pushBack(WayPoint);
		count++;
		point=objects->getObject(std::to_string(count));
	} while(point.begin()!=point.end());
	WayPoint=NULL;
}

Node* Enemy::currPoint(){
 
	return this->pointsVector.at(pointCount);
}

Node* Enemy::nextPoint(){
	int maxcount=this->pointsVector.size();
	pointCount++;
	if(pointCount<maxcount){
		return this->pointsVector.at(pointCount);
	}
	else{
	    return this->pointsVector.at(pointCount-1);
	}
	return NULL;
}

void Enemy::runbyWay(){
	int maxcount=this->pointsVector.size();
	Vector<FiniteTimeAction*> Actions;
	auto wayPoint=currPoint();
	setPosition(wayPoint->getPosition());
	while(pointCount<maxcount){
		auto wayPoint=currPoint();
	    auto goalpoint=nextPoint();
		float distance=sqrtf(pow((wayPoint->getPositionX()-goalpoint->getPositionX()),2)+pow((wayPoint->getPositionY()-goalpoint->getPositionY()),2));
		Actions.pushBack(MoveTo::create(distance/OriSpeed,goalpoint->getPosition()));
	}
	run=Sequence::create(Actions);
	runAction(run);
}

bool Enemy::changeSpeed(int rspeed){
	this->getScheduler()->setTimeScale(100);
	return true;
}

int Enemy::getType(){
	return this->type;
}
bool Enemy::setType(int type){
	this->type=type;
	return true;
}
int Enemy::getMaxHp(){
	return this->MaxHp;
}
bool Enemy::setMaxHp(int hp){
	this->MaxHp=hp;
	return true;
}
int Enemy::getHp(){
	return this->Hp;
	
}

bool Enemy::setHp(int hp){
	this->Hp=hp;
	return true;
}
int Enemy::getOriSpeed(){
	return this->OriSpeed;
}
bool Enemy::setOriSpeed(int ospeed){
	this->OriSpeed=ospeed;
	return true;
}
int Enemy::getSpeed(){
	return this->OriSpeed;
}
bool Enemy::setSpeed(int rspeed){
	this->rSpeed=rspeed;
	return true;
}

