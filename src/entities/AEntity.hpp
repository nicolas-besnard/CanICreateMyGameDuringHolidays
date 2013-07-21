#ifndef				AENTITY_HH_
# define			AENTITY_HH_

# include			<allegro5/allegro.h>
# include			<allegro5/allegro_primitives.h>

class				AEntity
{
public:
  enum	Type
  {
    PLAYER,
    BULLET,
    ENEMY
  };

  virtual ~AEntity() {}

  virtual void			draw() = 0;
  virtual void			update() = 0;

  int				getPosX() const { return posX_; }
  int				getPosY() const { return posY_; }
  int				getType() const { return type_; }
  int				getBoundX() const { return boundX_; }
  int				getBoundY() const { return boundY_; }

protected:
  AEntity(int type)
    : type_(type),
      posX_(20),
      posY_(20),
      boundX_(6),
      boundY_(7)
  {}

  int				type_;
  int				posX_;
  int				posY_;
  int				boundX_;
  int				boundY_;

private:
  AEntity 			&operator=(const AEntity &other);
  AEntity(const AEntity &other);
};

#endif				/* !AENTITY_HH_ */
