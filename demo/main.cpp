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

int				main(void)
{
  ALogger::setLogger(new LoggerConsole);
  Context			&context = Context::getInstance();

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
  FontManager::getInstance().addSearchPath("./assets/fonts/");
  try
    {
      context.init(800, 600);
      FontManager::getInstance().initAddon();
      FontManager::getInstance().get("comics.ttf", 24);
      context.loop();
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
