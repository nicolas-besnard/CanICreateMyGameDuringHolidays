#ifndef					FONTMANAGER_HH_
# define				FONTMANAGER_HH_

# include				<map>
# include				<set>
# include				<string>

# include		    		<allegro5/allegro.h>
# include				<allegro5/allegro_font.h>
# include				<allegro5/allegro_ttf.h>

# include				"Singleton.hpp"
# include				"File.hpp"
# include				"Exception.hh"

# include				<iostream>

class					FontManager : public Singleton<FontManager>
{
  friend class				Singleton<FontManager>;
  typedef int						FontSize;
  typedef std::pair<std::string, FontSize>		FontParamPair;
  typedef std::map<FontParamPair, ALLEGRO_FONT *>	FontMap;
  typedef std::pair<FontParamPair, ALLEGRO_FONT *>	FontPair;
  typedef FontMap::iterator				FontMapIT;
  typedef FontMap::const_iterator			FontMapConstIT;

  typedef std::set<std::string>				PathSet;
  typedef PathSet::iterator				PathSetIT;
  typedef PathSet::const_iterator			PathSetConstIT;

public:
  FontManager();
  ~FontManager();

  void					addSearchPath(const std::string &path);
  ALLEGRO_FONT				*get(const std::string &font, FontSize size);
  void					deleteLoaded();
  void					initAddon();

protected:

private:
  FontManager 			&operator=(const FontManager &other);
  FontManager(const FontManager &other);

  ALLEGRO_FONT				*load_(const std::string &font, FontSize size);

  FontMap				fontCollection_;
  PathSet				paths_;
  bool					addonAreInit_;
};

#endif				/* !FONTMANAGER_HH_ */
