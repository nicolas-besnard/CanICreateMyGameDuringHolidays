#ifndef				COMET_HH_
# define			COMET_HH_

# include			"Context.hh"
# include			"AEntity.hpp"

class				Comet : public AEntity
{
public:
  Comet(void);
  virtual ~Comet();

  virtual void			draw();
  virtual void			update();

protected:

private:
  Comet 			&operator=(const Comet &other);
  Comet(const Comet &other);

  float				speed_;
};

#endif				/* !COMET_HH_ */
