#include			"Comet.hh"

// CTOR - DTOR

Comet::Comet(void)
  : AEntity(AEntity::ENEMY),
    speed_(1)
{
  boundX_ = 20;
  boundY_ = 20;
  posX_ = 800;
  posY_ = 30 + rand() % (600 - 60);
}

Comet::~Comet() {}

// PUBLIC METHODS

void				Comet::draw(void)
{
  al_draw_filled_circle(posX_, posY_, 20, al_map_rgb(255, 0, 0));

  // Bounding Box
  al_draw_rectangle(posX_ - boundX_, posY_ - boundY_, posX_ + boundX_, posY_ + boundY_, al_map_rgb(0, 255, 0), 1);
}


void				Comet::update(void)
{
  posX_ -= speed_;
  if (posX_ < 0)
    {
      Context::getInstance().removeEntity(*this);
      delete this;
    }
}
