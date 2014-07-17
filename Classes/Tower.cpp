#include "Tower.h"
#include "GameScene.h"
#include "ResourceManager.h"

Tower::Tower()
{
}

bool Tower::initWithType(int type)
{
	m_target = NULL;
	m_type = type;
	m_level = 1;
	m_elapsedTime = 0.0f;
	switch (m_type)
	{
	case TOWER_TYPE_0:
		m_sprite = Sprite::createWithTexture(ResourceManager::getInstance()->tower0);
		this->addChild(m_sprite);
		m_range = 200;
		m_speed = 1;
		break;
	case TOWER_TYPE_1:
		m_sprite = Sprite::createWithTexture(ResourceManager::getInstance()->tower1);
		this->addChild(m_sprite);
		m_range = 200;
		m_speed = 1;
		break;
	}
	if (m_sprite){
		this->setContentSize(m_sprite->getContentSize());
	}
	return true;
}

Tower* Tower::create(int type)
{
	Tower* temp = new Tower();
	if( temp && temp->initWithType(type)) {
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
		Bullet* t_bullet = Bullet::create(m_type, m_level);

		if(!t_bullet)
			return;

		t_bullet->setPosition(this->getPosition());
		Game* gamelayer = dynamic_cast<Game*>(this->getParent());
		gamelayer->addBullet(t_bullet);
		//把子弹放入vector中
		gamelayer->addChild(t_bullet);
		//发射子弹
		shotBullet(t_bullet,m_target);
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
	this->setRotation(angle);
	bullet->setRotation(angle);
	bullet->setBulletVelocity(direction * bullet->getSpeed());
}

//-------------------------get/sets------------------------
int Tower::getType()
{
	return m_type;
}
void Tower::setType(int type)
{
	this->m_type = type;
}
int Tower::getlevel()
{
	return m_level;
}
void Tower::upgrade()
{
	m_level++;
}
int Tower::getRange()
{
	return m_range;
}
void Tower::setRange(int r)
{
	this->m_range = r;
}
int Tower::getPrice(int type, int level){
	switch (type)
	{
	case TOWER_TYPE_0:
		switch (level)
		{
		case 1:
			return 100;
		case 2:
			return 200;
		case 3:
			return 300;
		default:
			return 9999;
		}
	default:
		return 9999;
	}
}