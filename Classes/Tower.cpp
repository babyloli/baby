#include "Tower.h"
#include "GameScene.h"
#include "ResourceManager.h"

Tower::Tower()
{
}

bool Tower::initWithType(int type)
{
	m_target = NULL;
	this->m_type = type;
	this->m_level = 1;

	switch (m_type)
	{
	case TOWER_TYPE_0:
		m_sprite = Sprite::createWithTexture(ResourceManager::getInstance()->tower0);
		this->addChild(m_sprite);
		this->m_range = 300;
		break;
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
	double maxdistance = 9999;

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

void Tower::generateBullet()
{
	m_target = getCloseTarget();
	if(!m_target)
		return ;
	Bullet* t_bullet = Bullet::create(m_type, m_level);

	if(!t_bullet)
		return;

	t_bullet->setPosition(this->getPosition());
	/////////
	this->addChild(t_bullet);
	//发射子弹
	shotBullet(t_bullet,m_target);
	//把子弹放入vector中
	m_bullets.pushBack(t_bullet);
}

void Tower::shotBullet(Bullet* bullet, Enemy* target)
{
	if(!bullet || !target)
		return;
	bullet->setBulletVelocity(target->getPosition() - this->getPosition());
}









///////////////////////////////////////////////////////////
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