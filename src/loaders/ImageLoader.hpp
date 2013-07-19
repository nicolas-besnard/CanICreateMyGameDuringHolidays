#ifndef					IMAGELOADER_HPP_
# define				IMAGELOADER_HPP_

# include				<allegro5/allegro.h>
# include				<allegro5/allegro_opengl.h>

# include				"ALoader.hpp"
# include				"Exception.hh"
# include				"Image.hh"

class					ImageLoader : public ALoader<Image>
{
 public:
  virtual				~ImageLoader()
  {}

  virtual Image				*load(const File &file)
  {
    ALLEGRO_BITMAP			*bmp = al_load_bitmap(file.getFullName().c_str());

    if (!bmp)
      throw LoadingFailed(file.getFullName(), "ImageLoader failed to load image.");
    return new Image(bmp, file.getFileName());
  }

  virtual void				save(const Image *, const std::string &name)
  {
    throw LoadingFailed(name, "ImageLoader doesn't support SAVE.");
  }
};

#endif				/* !IMAGELOADER_H_ */
