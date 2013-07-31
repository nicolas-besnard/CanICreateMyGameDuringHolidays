#include			"Context.hh"

// CTOR - DTOR

Context::Context()
{

}

Context::~Context()
{
  al_destroy_display(al_get_current_display());
  al_uninstall_keyboard();
  al_uninstall_mouse();
}

// PUBLIC METHODS

void				Context::init(int width, int height)
{
  if (!al_init())
    throw ContextException(__FILE__, __LINE__, "Can't init Allegro.");
  if (!al_init_image_addon())
    throw ContextException(__FILE__, __LINE__, "Can't init Allegro's image addon.");
  if (!al_init_primitives_addon())
    throw ContextException(__FILE__, __LINE__, "Can't init primtivies addon.");
  al_set_new_bitmap_flags(ALLEGRO_MIPMAP | ALLEGRO_MIN_LINEAR);
  if (!al_create_display(width, height))
    throw ContextException(__FILE__, __LINE__, "Can't create display.");
  if (!al_install_keyboard())
    throw ContextException(__FILE__, __LINE__, "Can't install keyboard.");
  if (!al_install_mouse())
    throw ContextException(__FILE__, __LINE__, "Can't install mouse.");
  if (!al_install_joystick())
    throw ContextException(__FILE__, __LINE__, "Can't install joystick.");
}

