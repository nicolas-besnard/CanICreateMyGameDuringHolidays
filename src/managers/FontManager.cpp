#include			"FontManager.hh"
#include			<iostream>
// CTOR - DTOR

FontManager::FontManager()
  : addonAreInit_(false)
{}

FontManager::~FontManager()
{}

// PUBLIC METHODS

void				FontManager::addSearchPath(const std::string &path)
{
  if (path.empty() || (*path.rbegin() == '\\' || (*path.rbegin() == '/')))
    paths_.insert(path);
  else
    paths_.insert(path + "\\");
}

ALLEGRO_FONT			*FontManager::get(const std::string &font, FontSize size)
{
  if (!addonAreInit_)
    initAddon();

  // Check if font already load
  FontMapConstIT		actualFont;

  for (actualFont = fontCollection_.begin(); actualFont != fontCollection_.end(); ++actualFont)
    {
      if ((*actualFont).first.first == font && (*actualFont).first.second == size)
	return (*actualFont).second;
    }
  // The font isn't already loaded : load it
  return load_(font, size);
}

void				FontManager::deleteLoaded(void)
{
  FontMapConstIT		actualFont;

  for (actualFont = fontCollection_.begin(); actualFont != fontCollection_.end(); ++actualFont)
    {
      al_destroy_font((*actualFont).second);
    }
}

void				FontManager::initAddon(void)
{
  al_init_font_addon();
  if (!al_init_ttf_addon())
    throw Exception("Failed to init Fonts addon");
  addonAreInit_ = true;
}
// PRIVATE METHODS

ALLEGRO_FONT			*FontManager::load_(const std::string &font, FontSize size)
{
  PathSetConstIT		actualPath;
  std::string			lastPath;

  for (actualPath = paths_.begin(); actualPath != paths_.end(); ++actualPath)
    {
      lastPath = *actualPath;
      File			f(lastPath + font);

      if (f.exists())
	{
	  ALLEGRO_FONT		*tmp = al_load_font(f.getFullName().c_str(), 24, 0);
	  FontParamPair		fontParam(font, size);
	  fontCollection_.insert(FontPair(fontParam, tmp));
	  return tmp;
	}
    }
  throw LoadingFailed(lastPath + font, "Not found font.");
}
