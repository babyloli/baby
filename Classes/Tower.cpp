#include "Tower.h"
#include "GameScene.h"
#include "ResourceManager.h"

Tower::Tower()
{
}

bool Tower::initWithType(int id)
{
	HCSVFile* towerData = ResourceManager::getInstance()->towerData;
	m_target = NULL;
	m_level = 1;
	m_id = id;
	m_name = towerData->getData(id, 1);
	m_type = std::atoi(towerData->getData(id, 2));
	m_speed = std::atof(towerData->getData(id, 3));
	m_attack = std::atoi(towerData->getData(id, 4));
	m_deltaAttack = std::atoi(towerData->getData(id, 5));
	m_range = std::atoi(towerData->getData(id, 6));
	m_deltaRange = std::atoi(towerData->getData(id, 7));
	m_price = std::atoi(towerData->getData(id, 8));
	m_deltaPrice = std::atoi(towerData->getData(id, 9));
	m_moneyReturnRate = std::atof(towerData->getData(id, 10));
	m_bulletName = towerData->getData(id, 11);
	m_bulletSpeed = std::atoi(towerData->getData(id, 12));
	m_rotateEnable = std::atoi(towerData->getData(id, 13)) ? true : false;
	m_bulletRotateEnable = std::atoi(towerData->getData(id, 14)) ? true : false;
	m_bulletCollide = std::atoi(towerData->getData(id, 15)) ? true : false;
	m_elapsedTime = 0.0f;
	//根据名字，从Plist读图片。
	m_sprite = Sprite::createWithSpriteFrameName(m_name);
	this->addChild(m_sprite);
	if (m_sprite){
		this->setContentSize(m_sprite->getContentSize());
	}
	m_circle = DrawNode::create();
	m_circle->drawDot(Vec2::ZERO, m_range, Color4F(0.2f, 0.2f, 0.2f, 0.8f));
	this->addChild(m_circle);
	m_circle->setVisible(false);
	return true;
}

Tower* Tower::create(int id)
{
	Tower* temp = new Tower();
	if( temp && temp->initWithType(id)) {
		temp->autorelease();
		return temp;
	}
	else
	{
		delete temp;
		temp = NULL;
		return NULL;
	}
}

Enemy* Tower::getCloseTarget()
{
	Enemy* closetarge = NULL;
	double maxdistance = MAX_RANGE;

	Game* gamelayer = dynamic_cast<Game*>(this->getParent());
	for (auto enemy : gamelayer->getEnemies()){
//		double currdistance = ccpDistance(this->getPosition(),enemy->getPosition());
		double currdistance = this->getPosition().distance(enemy->getPosition());
		if( currdistance < maxdistance){
			closetarge = enemy;
			maxdistance = currdistance;
		}
	}
	
	if(maxdistance < this->m_range )
	{
		return closetarge;
	}
	else
		return NULL;
}

void Tower::generateBullet(float dt)
{
	m_elapsedTime += dt;
	if (m_elapsedTime > m_speed){
		m_elapsedTime -= m_speed;
		m_target = getCloseTarget();
		if(!m_target)
			return ;

		Bullet* t_bullet = Bullet::create(m_bulletName, m_type, m_level, m_attack, m_bulletSpeed, m_bulletRotateEnable, m_bulletCollide);
		if(!t_bullet)
			return;
		t_bullet->setPosition(this->getPosition());

		Game* gamelayer = static_cast<Game*>(this->getParent());
		gamelayer->addBullet(t_bullet); //把子弹放入vector中
		gamelayer->addChild(t_bullet); 
		shotBullet(t_bullet, m_target);	//发射子弹
	}
}

void Tower::shotBullet(Bullet* bullet, Enemy* target)
{
	if(!bullet || !target)
		return;
	Vec2 direction = target->getPosition() - this->getPosition();
	direction.normalize();
	float angle = acos(Vec2::dot(direction, Vec2(0.0f, -1.0f))) * 57.325f;
	if (direction.x > 0)
		angle = -angle;
	if (m_rotateEnable)
		this->setRotation(angle);
	if (!m_bulletRotateEnable)
		bullet->setRotation(angle);
	bullet->setBulletVelocity(direction * bullet->getSpeed());
}

//-------------------------get/sets------------------------
int Tower::getId()
{
	return m_id;
}
void Tower::setId(int id)
{
	this->m_id = id;
}
int Tower::getlevel()
{
	return m_level;
}
void Tower::upgrade()
{
	m_level++;
	if (m_level == 2)
		m_sprite->setScale(1.1f);
	else if (m_level == 3)
		m_sprite->setScale(1.2f);
	m_circle->setVisible(false);
	m_attack += m_deltaAttack;
	m_range += m_deltaRange;
	m_price += m_deltaPrice;
	m_circle->drawDot(Vec2::ZERO, m_range, Color4F(0.2f, 0.2f, 0.2f, 0.8f));
}
int Tower::getRange()
{
	return m_range;
}
void Tower::setRange(int r)
{
	this->m_range = r;
}
void Tower::showRange(bool b){
	m_circle->setVisible(b);
}
int Tower::getUpgradePrice(){
	return m_price + m_deltaPrice;
}
int Tower::getMoneyWhenDeleted(){
	float ret = m_price * m_moneyReturnRate;
	return (int)ret;
}