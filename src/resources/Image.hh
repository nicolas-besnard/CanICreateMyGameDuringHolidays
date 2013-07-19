#ifndef				IMAGE_HH_
# define			IMAGE_HH_

# include			<allegro5/allegro.h>
# include			<string>

# include			"AResource.hh"
# include			"SmartPointer.hpp"
# include			"SmartPointerPolicies.hpp"

class				Image : public AResource
{
public:
  Image(ALLEGRO_BITMAP *bmp, const std::string &name);
  virtual ~Image();

  const ALLEGRO_BITMAP		&getBitmap() const { return *bmp_; }

private:
  Image 			&operator=(const Image &other);
  Image(const Image &other);

  ALLEGRO_BITMAP		*bmp_;
};

typedef	SmartPointer<Image, InternalRef>	ImagePointer;

#endif				/* !IMAGE_H_ */
