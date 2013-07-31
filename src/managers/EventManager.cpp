#include				"EventManager.hh"

// CTOR - DTOR

EventManager::EventManager(void)
  : isRunning_(false),
    canDraw_(false),
    eventQueue_(NULL),
    timer_(NULL)
{}

EventManager::~EventManager()
{
  if (eventQueue_)
    al_destroy_event_queue(eventQueue_);
  if (timer_)
    al_destroy_timer(timer_);
}

// PRIVATE METHODS

// void				Context::notifyNewEvent_(ALLEGRO_EVENT &event) const
// {
//   ObserverVectorConstIT		actualObserver = eventListener_.begin();

//   for (; actualObserver != eventListener_.end(); actualObserver++)
//     {
//       (*actualObserver)->notify(event);
//     }
// }


// PUBLIC METHODS

void					EventManager::init(void)
{
  if (!(this->timer_ = al_create_timer(1.0 / 300)))
    throw ContextException(__FILE__, __LINE__, "Can't create timer.");
  if (!(eventQueue_ = al_create_event_queue()))
    throw ContextException(__FILE__, __LINE__, "Can't create event queue.");
  al_register_event_source(eventQueue_, al_get_keyboard_event_source());
  al_register_event_source(eventQueue_, al_get_mouse_event_source());
  al_register_event_source(eventQueue_, al_get_display_event_source(al_get_current_display()));
  al_register_event_source(eventQueue_, al_get_timer_event_source(timer_));
  al_start_timer(timer_);
  isRunning_ = true;
}

void					EventManager::loop(void)
{
  static double fps = 0;
  static double frames_done = 0;
  static double old_time = al_get_time();

  while (isRunning_)
    {
      ALLEGRO_EVENT			event;

      al_wait_for_event(eventQueue_, &event);
      SystemManager::getInstance().update(event);
      canDraw_ = false;
      if (event.type == ALLEGRO_EVENT_KEY_DOWN)
	{
	  if ((event.keyboard.keycode == ALLEGRO_KEY_ESCAPE))
	    {
	      isRunning_ = false;
	    }
	}
      if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	isRunning_ = false;
      if (event.type == ALLEGRO_EVENT_TIMER)
	{
	  canDraw_ = true;
	}
      if (canDraw_ && al_is_event_queue_empty(eventQueue_))
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
	  ShipSystem			s;
	  s.draw();
	  al_flip_display();
	  al_clear_to_color(al_map_rgb(0, 0, 0));
	}
    }
}

// void				Context::addEventListener(AObserver &observer)
// {
//   ObserverVectorIT			it = find(eventListener_.begin(), eventListener_.end(), &observer);
//   if (it != eventListener_.end())
//     return ;
//   eventListener_.push_back(&observer);
// }
