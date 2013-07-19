#include			"Context.hh"

// CTOR - DTOR

Context::Context() {}

Context::~Context()
{
  al_destroy_display(al_get_current_display());
  if (eventQueue_)
    al_destroy_event_queue(eventQueue_);
  if (timer_)
    al_destroy_timer(timer_);
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
  if (!(this->eventQueue_ = al_create_event_queue()))
    throw ContextException(__FILE__, __LINE__, "Can't create event queue.");
  if (!(this->timer_ = al_create_timer(1.0 / 60)))
    throw ContextException(__FILE__, __LINE__, "Can't create timer.");
  if (!al_install_joystick())
    throw ContextException(__FILE__, __LINE__, "Can't install joystick.");
  al_register_event_source(this->eventQueue_, al_get_keyboard_event_source());
  al_register_event_source(this->eventQueue_, al_get_mouse_event_source());
  al_register_event_source(this->eventQueue_, al_get_display_event_source(al_get_current_display()));
  al_register_event_source(this->eventQueue_, al_get_timer_event_source(this->timer_));
  al_start_timer(this->timer_);
}

void				Context::loop()
{
  bool				canDraw;

  isRunning_ = true;
  while (isRunning_)
    {
      ALLEGRO_EVENT		ev;
      canDraw = false;

      al_wait_for_event(eventQueue_, &ev);
      if (ev.type == ALLEGRO_EVENT_TIMER)
	{
	  canDraw = true;
	  //logic
	}
      else if (ev.type == ALLEGRO_EVENT_KEY_CHAR)
	{
	  if ((ev.keyboard.keycode = ALLEGRO_KEY_ESCAPE))
	    {
	      isRunning_ = false;
	    }
	}
      if (canDraw && al_is_event_queue_empty(eventQueue_))
	{
	  al_clear_to_color(al_map_rgb(0, 0, 0));
	  al_draw_rectangle(10, 10, 20, 20, al_map_rgb(255, 0, 0), 10);
	  al_flip_display();
	}
      if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	isRunning_ = false;
    }
}
