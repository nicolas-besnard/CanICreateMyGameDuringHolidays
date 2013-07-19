#include			"Image.hh"

// CTOR - DTOR

Image::Image(ALLEGRO_BITMAP *bmp, const std::string &name)
  : AResource(name),
    bmp_(bmp)
{}

Image::~Image()
{
  if (bmp_)
    al_destroy_bitmap(bmp_);
}
