#include			<iostream>

#include			"Context.hh"
#include			"ALogger.hh"
#include			"LoggerConsole.hh"
#include			"FontManager.hh"
#include			"EventManager.hh"
#include			"OptionManager.hpp"

#include			"EntityManager.hh"

#include			"components/PositionComponent.hpp"
#include			"components/ShipComponent.hpp"
#include			"components/InputMovementComponent.hpp"
#include			"components/BoundingBoxComponent.hpp"
#include			"components/AggroCircleComponent.hpp"
#include			"components/TagComponent.hpp"
#include			"components/SpeedComponent.hpp"
#include			"components/OrientationComponent.hpp"
#include			"components/SpriteComponent.hpp"

#include			"systems/ShipSystem.hpp"
#include			"systems/InputSystem.hpp"
#include			"systems/InputMovementSystem.hpp"
#include			"systems/BoundingBoxSystem.hpp"
#include			"systems/AggroCircleSystem.hpp"
#include			"systems/MovementSystem.hpp"
#include			"systems/CreateEnemySystem.hpp"
#include			"systems/SpriteSystem.hpp"
#include			"systems/ImageSystem.hpp"
#include			"systems/MouseSystem.hpp"

#include			"managers/SystemManager.hpp"

#include			"EntityFactory.hpp"

int				main(void)
{
  srand(time(NULL));
  ALogger::setLogger(new LoggerConsole);

  Context			&context = Context::getInstance();

  EntityManager::getInstance().createMouseEntity();

  Entity			&entity = EntityManager::getInstance().getNewEntity();

  BoundingBox			&bb = EntityManager::getInstance().addComponent<BoundingBox>(entity);
  bb.sizeX = 24;
  bb.sizeY = 24;

  InputMovement			&m = EntityManager::getInstance().addComponent<InputMovement>(entity);
  m.keyUp = ALLEGRO_KEY_Z;
  m.keyDown = ALLEGRO_KEY_S;
  m.keyLeft = ALLEGRO_KEY_Q;
  m.keyRight = ALLEGRO_KEY_D;
  m.keyShoot = ALLEGRO_KEY_SPACE;
  m.keyMissile = ALLEGRO_KEY_A;

  Position			&p = EntityManager::getInstance().addComponent<Position>(entity);
  p.x = 210;
  p.y = 660;

  Tag				&t = EntityManager::getInstance().addComponent<Tag>(entity);
  t.name = "Player";

  Orientation			&o = EntityManager::getInstance().addComponent<Orientation>(entity);
  o.radian = -M_PI / 2;

  Speed				&speed = EntityManager::getInstance().addComponent<Speed>(entity);
  speed.value = 110;

  Sprite			&sprite = EntityManager::getInstance().addComponent<Sprite>(entity);
  sprite.isInit = false;
  sprite.url = "./assets/images/ship.png";
  sprite.columnNumber = 1;
  sprite.partWidth = 24;
  sprite.partHeight = 24;
  sprite.from = 0;
  sprite.stepNumber = 0;
  sprite.currentStep = 0;
  sprite.speed = 1;
  sprite.timeCounter = -1;

  SystemManager::getInstance().addSystem<InputSystem>();
  SystemManager::getInstance().addSystem<InputMovementSystem>();
  SystemManager::getInstance().addSystem<BoundingBoxSystem>();
  SystemManager::getInstance().addSystem<AggroCircleSystem>();
  SystemManager::getInstance().addSystem<MovementSystem>();
  SystemManager::getInstance().addSystem<SpriteSystem>(10, true);
  SystemManager::getInstance().addSystem<MouseSystem>();
  SystemManager::getInstance().addSystem<ImageSystem>(10, true);

  try
    {
      context.init(480, 720);
      EventManager::getInstance().init();
      EventManager::getInstance().loop();
    }
  catch (ContextException &e)
    {
      ALogger::log(e.what());
    }
  catch (LoadingFailed &e)
    {
      ALogger::log(e.what());
      exit(0);
    }
  return (0);
}
