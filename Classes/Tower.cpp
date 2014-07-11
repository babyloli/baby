#include "Tower.h"


Tower::Tower()
{
	this->range = 3;
	this->type = 0;
	this->level = 1;
	target = NULL;
	tower = NULL;
}
Tower::Tower(int type)
{
	this->type = type;
	this->level = 1;
	this->range = 3;
	target = NULL;
	tower = NULL;
}
Tower::~Tower(void)
{
}

bool Tower::init()
{
	switch (type)
	{
	case TOWER_TYPE_0:
		tower = Sprite::create("tower0.png");
		break;
	default:
		break;
	}
	if(!tower)
		return false;
	this->addChild(tower);
	
	return true;
}

Tower* Tower::create(int type)
{
	Tower* temp = new Tower(type);
	if( temp && temp->init()) {
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
	/*for (auto enemy : gamelayer->getEnemies()){
		double currdistance = ccpDistance(this->getPosition(),enemy->getPosition());
		if( currdistance < maxdistance){
			closetarge = enemy;
			maxdistance = currdistance;
		}
	}
	*/
	if(maxdistance < this->range )
	{
		return closetarge;
	}
	else
		return NULL;
}

void Tower::generateBullet()
{
	target = getCloseTarget();
	if(!target)
		return ;
	Bullet* t_bullet = Bullet::create(type,level,level+3);

	if(!t_bullet)
		return;

	t_bullet->setPosition(tower->getPosition());
	/////////
	this->addChild(t_bullet);
	//发射子弹
	shotBullet(t_bullet,target);
	//把子弹放入vector中
	bullets.pushBack(t_bullet);
}

void Tower::shotBullet(Bullet* bullet, Enemy* target)
{
	if(!bullet || !target)
		return;
	bullet->setBulletVelocity(target->getPosition());
}









///////////////////////////////////////////////////////////
int Tower::getType()
{
	return type;
}
void Tower::setType(int type)
{
	this->type = type;
}
int Tower::getlevel()
{
	return level;
}
void Tower::upgrade()
{
	level++;
}
int Tower::getRange()
{
	return range;
}
void Tower::setRange(int r)
{
	this->range = r;
}