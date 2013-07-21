#include			"Player.hh"

// CTOR - DTOR

Player::Player(void)
  :
    AObserver(),
    AEntity(AEntity::PLAYER),
    speed_(1),
    bulletCount_(5)
{
  boundX_ = 6;
  boundY_ = 7;
  keys_[Player::UP] = false;
  keys_[Player::DOWN] = false;
  keys_[Player::LEFT] = false;
  keys_[Player::RIGHT] = false;
  keys_[Player::SPACE] = false;
}

Player::~Player() {}

// PUBLIC METHODS

void				Player::draw(void)
{
  al_draw_filled_rectangle(posX_, posY_ - 9, posX_ + 10, posY_ - 7, al_map_rgb(255, 0, 0));
  al_draw_filled_rectangle(posX_, posY_ + 9, posX_ + 10, posY_ + 7, al_map_rgb(255, 0, 0));
  al_draw_filled_triangle(posX_ - 12, posY_ - 17, posX_ + 12, posY_, posX_ - 12, posY_ + 17, al_map_rgb(0, 255, 0));
  al_draw_filled_rectangle(posX_ - 12, posY_ - 2, posX_ + 15, posY_ + 2, al_map_rgb(0, 0, 255));

  // Bounding Box
  al_draw_rectangle(posX_ - boundX_ - 9, posY_ - boundY_ - 9, posX_ + boundX_ + 10, posY_ + boundY_ + 10, al_map_rgb(255, 0, 0), 1);
}


void				Player::update(void)
{
  if (keys_[Player::UP])
    move_(Player::UP);
  if (keys_[Player::DOWN])
    move_(Player::DOWN);
  if (keys_[Player::LEFT])
    move_(Player::LEFT);
  if (keys_[Player::RIGHT])
    move_(Player::RIGHT);
  if (keys_[Player::SPACE])
    fireBullet_();
}

void				Player::notify(ALLEGRO_EVENT &ev)
{
  if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
      switch (ev.keyboard.keycode)
	{
	case ALLEGRO_KEY_UP:
	  keys_[Player::UP] = true;
	  break;

	case ALLEGRO_KEY_DOWN:
	  keys_[Player::DOWN] = true;
	  break;

	case ALLEGRO_KEY_LEFT:
	  keys_[Player::LEFT] = true;
	  break;

	case ALLEGRO_KEY_RIGHT:
	  keys_[Player::RIGHT] = true;
	  break;

	case ALLEGRO_KEY_SPACE:
	  keys_[Player::SPACE] = true;
	  break;
	}
    }

    if (ev.type == ALLEGRO_EVENT_KEY_UP)
    {
      switch (ev.keyboard.keycode)
	{
	case ALLEGRO_KEY_UP:
	  keys_[Player::UP] = false;
	  break;

	case ALLEGRO_KEY_DOWN:
	  keys_[Player::DOWN] = false;
	  break;

	case ALLEGRO_KEY_LEFT:
	  keys_[Player::LEFT] = false;
	  break;

	case ALLEGRO_KEY_RIGHT:
	  keys_[Player::RIGHT] = false;
	  break;
	}
    }
}

void				Player::reload(void)
{
  ++bulletCount_;
}

// PRIVATE METHODS

void				Player::move_(Player::Movement direction)
{
  switch (direction)
    {
    case Player::UP:
      posY_ -= speed_;
      if (posY_ < 0)
	posY_ = 0;
      break;

    case Player::DOWN:
      posY_ += speed_;
      if (posY_ > 600)
	posY_ = 600;
      break;

    case Player::LEFT:
      posX_ -= speed_;
      if (posX_ < 0)
	posX_ = 0;
      break;

    case Player::RIGHT:
      posX_ += speed_;
      if (posX_ > 800)
	posX_ = 800;
      break;

    default:
      break;
    }
}

void				Player::fireBullet_(void)
{
  if (bulletCount_ > 0)
    {
      Bullet			*bullet = new Bullet(*this);

      Context::getInstance().addEntity(*bullet);
      --bulletCount_;
    }
  keys_[Player::SPACE] = false;
}
