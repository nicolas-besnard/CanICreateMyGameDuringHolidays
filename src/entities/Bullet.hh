#ifndef				BULLET_HH_
# define			BULLET_HH_

# include			"AEntity.hpp"
# include			"Player.hh"
# include			"Context.hh"

class Player;

class				Bullet : public AEntity
{
public:
  Bullet(Player &owner);
  virtual ~Bullet();

  virtual void			draw();
  virtual void			update();

  Bullet(const Bullet &other);
protected:

private:
  Bullet 			&operator=(const Bullet &other);


  int				posX_;
  int				posY_;
  int				speed_;
  Player			&owner_;
};

#endif				/* !BULLET_HH_ */
