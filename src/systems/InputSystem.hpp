#ifndef					INPUTSYSTEM_HPP_
# define				INPUTSYSTEM_HPP_

# include				<map>

# include				"System.hpp"

class					InputSystem : public System
{
  typedef std::map<int, bool>		ActiveKeyMap;
  typedef ActiveKeyMap::iterator	ActiveKeyMapIT;

  typedef std::pair<int, bool>		ActiveKeyPair;

public:
  InputSystem(void)
    : System()
  {}

  virtual ~InputSystem()
  {}

  virtual void				update(const ALLEGRO_EVENT &event)
  {
    if (!isKeyEvent_(event))
      return ;

    ActiveKeyMapIT			find = keys_.find(event.keyboard.keycode);

    if (find != keys_.end())
      {
	if (isKeyDownEvent_(event))
	  find->second = true;
	else if (isKeyUpEvent_(event))
	  find->second = false;
      }
  }

  virtual void				init(void)
  {
    for (int i = ALLEGRO_KEY_A; i <= ALLEGRO_KEY_COMMAND; ++i)
      {
	keys_.insert(ActiveKeyPair(i, false));
      }
  }

  bool					isKeyDown(int key)
  {
    ActiveKeyMapIT			find = keys_.find(key);

    if (find != keys_.end())
      return find->second;
    return false;
  }

protected:

private:
  InputSystem			&operator=(const InputSystem &other);
  InputSystem(const InputSystem &other);

  bool					isKeyEvent_(const ALLEGRO_EVENT &event)
  {
    return isKeyDownEvent_(event) || isKeyUpEvent_(event);
  }

  bool					isKeyDownEvent_(const ALLEGRO_EVENT &event)
  {
    return event.type == ALLEGRO_EVENT_KEY_DOWN;
  }

  bool					isKeyUpEvent_(const ALLEGRO_EVENT &event)
  {
    return event.type == ALLEGRO_EVENT_KEY_UP;
  }

  ActiveKeyMap				keys_;
};

#endif					/* !INPUTMOVEMENTSYSTEM_HPP_ */
