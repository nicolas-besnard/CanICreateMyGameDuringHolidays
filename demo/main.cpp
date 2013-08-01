#include			<iostream>
#include			"Context.hh"
#include			"ALogger.hh"
#include			"LoggerConsole.hh"
#include			"SmartPointer.hpp"
#include			"ResourceManager.hpp"
#include			"MediaManager.hpp"
#include			"ImageLoader.hpp"
#include			"Image.hh"
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

#include			"systems/ShipSystem.hpp"
#include			"systems/InputSystem.hpp"
#include			"systems/InputMovementSystem.hpp"
#include			"systems/BoundingBoxSystem.hpp"
#include			"systems/AggroCircleSystem.hpp"
#include			"systems/MovementSystem.hpp"
#include			"systems/CreateEnemySystem.hpp"

#include			"managers/SystemManager.hpp"

#include			"EntityFactory.hpp"

int				main(void)
{
  // srand(time(NULL));
  // ALogger::setLogger(new LoggerConsole);
  // Context&context = Context::getInstance();

  // MediaManager::getInstance().registerLoader(new ImageLoader, ".jpg,.png");
  // MediaManager::getInstance().addSearchPath("./assets/images/");

  // try
  //   {
  //     ImagePointer tmp = ResourceManager::getInstance().get<Image>("github.png");
  //   }
  // catch (LoadingFailed &e)
  //   {
  //     ALogger::log(e.what());
  //     exit (0);
  //   }
  Context&context = Context::getInstance();
  // FontManager::getInstance().addSearchPath("./assets/fonts/");

  Entity&entity = EntityManager::getInstance().getNewEntity();
  Ship				&s = EntityManager::getInstance().addComponent<Ship>(entity);
  s.size = 50;

  BoundingBox			&bb = EntityManager::getInstance().addComponent<BoundingBox>(entity);
  bb.sizeX = s.size;
  bb.sizeY = s.size;

  InputMovement			&m = EntityManager::getInstance().addComponent<InputMovement>(entity);
  m.keyUp = ALLEGRO_KEY_Z;
  m.keyDown = ALLEGRO_KEY_S;
  m.keyLeft = ALLEGRO_KEY_Q;
  m.keyRight = ALLEGRO_KEY_D;
  m.keyShoot = ALLEGRO_KEY_SPACE;
  m.keyMissile = ALLEGRO_KEY_A;

  Position			&p = EntityManager::getInstance().addComponent<Position>(entity);
  p.x = 50;
  p.y = 50;

  Tag				&t = EntityManager::getInstance().addComponent<Tag>(entity);
  t.name = "Player";

  SystemManager::getInstance().addSystem<ShipSystem>(10, true);
  SystemManager::getInstance().addSystem<InputSystem>();
  SystemManager::getInstance().addSystem<InputMovementSystem>();
  SystemManager::getInstance().addSystem<BoundingBoxSystem>(1, true);
  SystemManager::getInstance().addSystem<AggroCircleSystem>(1, true);
  SystemManager::getInstance().addSystem<MovementSystem>();
  SystemManager::getInstance().addSystem<CreateEnemySystem>();

  try
    {
      context.init(800, 600);
      EventManager::getInstance().init();
      // FontManager::getInstance().initAddon();
      // FontManager::getInstance().get("comics.ttf", 24);
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
