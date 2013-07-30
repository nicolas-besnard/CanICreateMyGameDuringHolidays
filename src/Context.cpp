#include			"Context.hh"

// CTOR - DTOR

Context::Context()
{
  OptionManager::getInstance().add<bool>("isRunning", false);
  OptionManager::getInstance().add<bool>("canDraw", false);

  isRunning_ = OptionManager::getInstance().get<bool>("isRunning");
  canDraw_= OptionManager::getInstance().get<bool>("canDraw");
}

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
  if (!(this->timer_ = al_create_timer(1.0 / 300)))
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
  static double fps = 0;
  static double frames_done = 0;
  static double old_time = al_get_time();

  isRunning_->set(true);
  while (isRunning_->get())
    {
      ALLEGRO_EVENT		ev;
      canDraw_->set(false);

      al_wait_for_event(eventQueue_, &ev);
      notifyNewEvent_(ev);
      if (canDraw_->get() && al_is_event_queue_empty(eventQueue_))
	{
	  // FPS COUNT
	  double time = al_get_time();
	  if(time - old_time >= 1.0)
	    {
	      fps = frames_done / (time - old_time);
	      frames_done = 0;
	      old_time = time;
	      std::cout << "FPS : " << fps << " || TIME : " << old_time << std::endl;
	    }
	  frames_done++;


	  al_flip_display();
	  al_clear_to_color(al_map_rgb(0, 0, 0));

	}
    }
}


void				Context::addEventListener(AObserver &observer)
{
  ObserverVectorIT			it = find(eventListener_.begin(), eventListener_.end(), &observer);
  if (it != eventListener_.end())
    return ;
  eventListener_.push_back(&observer);
}

// PRIVATE METHODS

void				Context::notifyNewEvent_(ALLEGRO_EVENT &event) const
{
  ObserverVectorConstIT		actualObserver = eventListener_.begin();

  for (; actualObserver != eventListener_.end(); actualObserver++)
    {
      (*actualObserver)->notify(event);
    }
}
