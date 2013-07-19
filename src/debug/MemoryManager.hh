#ifndef				MEMORYMANAGER_HH_
# define			MEMORYMANAGER_HH_

# include			<map>
# include			<stack>
# include			<iomanip>

# include			<iostream> // DEBUG

# include			<cstdlib>

# include			"File.hpp"

struct				MemBlock
  {
    std::size_t			size;
    File			file;
    unsigned int		line;
    bool			isArray;
  };

class				MemoryManager
{
  typedef std::map<void *, MemBlock>	MemBlockMap;
  typedef MemBlockMap::iterator		MemBlockMapIT;
public:
  static MemoryManager		&getInstance(void);
  void				*allocate(std::size_t size, const File &file, int line, bool isArray = false);
  void				free(void* ptr, bool isArray = false);
  void				nextDelete(const File& file, int line);

protected:

private:
  MemoryManager(void);
  ~MemoryManager();
  MemoryManager			&operator=(const MemoryManager &other);
  MemoryManager(const MemoryManager &other);

  void				reportLeaks_(void);

  MemBlockMap			memBlock_;
  std::ofstream			file_;
  std::stack<MemBlock>		nextDelete_;
};

#endif				/* !MEMORYMANAGER_HH_ */
