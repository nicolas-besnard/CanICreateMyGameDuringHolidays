#include			"EventManager.hh"

// CTOR - DTOR

EventManager::EventManager(void)
  : AObserver()
{}

EventManager::~EventManager() {}

// PUBLIC METHODS

void				EventManager::notify(ALLEGRO_EVENT &ev)
{
  if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
    {
      if ((ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE))
	{
	  OptionManager::getInstance().get<bool>("isRunning")->set(false);
	}
    }
  if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    OptionManager::getInstance().get<bool>("isRunning")->set(false);
  if (ev.type == ALLEGRO_EVENT_TIMER)
    {
      SystemManager::getInstance().update(ev);
      OptionManager::getInstance().get<bool>("canDraw")->set(true);
    }
}
