#ifndef				PLAYER_HH_
# define			PLAYER_HH_

# include			"AEntity.hpp"
# include			"AObserver.hh"
# include			"Context.hh"
# include			"Bullet.hh"

class				Player :  public AObserver, public AEntity
{
  enum	Movement
    {
      UP,
      DOWN,
      LEFT,
      RIGHT,
      SPACE
    };

public:
  Player(void);
  virtual ~Player();

  virtual void			draw();
  virtual void			update();
  virtual void			notify(ALLEGRO_EVENT &event);
  void				reload();

  Player(const Player &other);

protected:

private:
  Player 			&operator=(const Player &other);


  void				move_(Player::Movement direction);
  void				fireBullet_();

  float				speed_;
  bool				keys_[5];
  int				bulletCount_;
};

#endif				/* !PLAYER_HH_ */
