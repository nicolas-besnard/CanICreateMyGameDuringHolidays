#include			"Bullet.hh"

// CTOR - DTOR

Bullet::Bullet(Player &owner)
  : AEntity(AEntity::BULLET),
    speed_(1),
    owner_(owner)
{
  boundX_ = 5;
  boundY_ = 5;
  posX_ = owner.getPosX();
  posY_ = owner.getPosY();
}

Bullet::~Bullet()
{
  owner_.reload();
}

// PUBLIC METHODS

void				Bullet::draw(void)
{
  al_draw_filled_circle(posX_, posY_, boundX_, al_map_rgb(255, 255, 255));

  // Bounding Box
  al_draw_rectangle(posX_ - boundX_, posY_ - boundY_, posX_ + boundX_, posY_ + boundY_, al_map_rgb(255, 0, 0), 1);
}

void				Bullet::update(void)
{
  posX_ += speed_;

  if (posX_ > 800)
    {
      Context::getInstance().removeEntity(*this);
      delete this;
    }

  // COLLISION
  Context::EntityVector		entities = Context::getInstance().getEntities();
  Context::EntityVectorConstIT	actualEntity = entities.begin();
  Context::EntityVectorConstIT	lastEntity = entities.end();

  for (; actualEntity != lastEntity; ++actualEntity)
  {
    if ((*actualEntity)->getType() == AEntity::ENEMY)
      {
	if ( (abs(posX_ - (*actualEntity)->getPosX()) * 2 < (boundX_ + (*actualEntity)->getBoundX())) &&
	     (abs(posY_ - (*actualEntity)->getPosY()) * 2 < (boundY_ + (*actualEntity)->getBoundY()))
	     )
	  {
	    Context::getInstance().removeEntity(*this);
	    Context::getInstance().removeEntity(*(*actualEntity));
	    delete this;
	    delete (*actualEntity);
	  }
      }
  }
}
