#include			"MemoryManager.hh"

// CTOR - DTOR

MemoryManager::MemoryManager(void)
  : file_("Leaks.log")
{}

MemoryManager::~MemoryManager()
{
  if (!this->memBlock_.empty())
    reportLeaks_();
}

// PRIVATE METHODS

void				MemoryManager::reportLeaks_(void)
{
  std::size_t			totalSize = 0;

  file_ << std::endl
	<< "=====================================" << std::endl
	<< " LEAKS REPORT " << std::endl
    	<< "=====================================" << std::endl;

  for (MemBlockMapIT actualMemBlock = memBlock_.begin(); actualMemBlock != memBlock_.end(); ++actualMemBlock)
    {
      totalSize += actualMemBlock->second.size;

      file_ << "-> 0x" << actualMemBlock->first
	    << " | "   << std::setw(7) << std::setfill(' ')
	    << static_cast<int>(actualMemBlock->second.size) << " octets"
	    << " | "   << actualMemBlock->second.file.getFileName()
	    << " (" << actualMemBlock->second.line << ")" << std::endl;
      // free(actualMemBlock->first);
    }

  file_ << std::endl << std::endl << "-- "
	<< static_cast<int>(this->memBlock_.size()) << " blocs non-libéré(s), "
	<< static_cast<int>(totalSize) << " octets --"
	<< std::endl;
}

// PUBLIC METHODS

MemoryManager			&MemoryManager::getInstance(void)
{
  static MemoryManager		that;

  return that;
}

void				*MemoryManager::allocate(std::size_t size, const File &file, int line, bool isArray)
{
  // Allocation de la mémoire
  void				*ptr = malloc(size);

  // Ajout du bloc à la liste des blocs alloués
  MemBlock			 memBlock;

  memBlock.size  = size;
  memBlock.file  = file;
  memBlock.line  = line;
  memBlock.isArray = isArray;
  this->memBlock_[ptr] = memBlock;

  // Loggization
  file_ << "++ Allocation    | 0x" << ptr
	<< " | " << std::setw(7) << std::setfill(' ')
	<< static_cast<int>(memBlock.size) << " octets"
	<< " | " << memBlock.file.getFileName()
	<< "(" << memBlock.line << ")" << std::endl;

  return ptr;
}

void				MemoryManager::free(void *ptr, bool isArray)
{
  if (this->memBlock_.size() > 0)
    {
      // std::cout << memBlock_.size() << std::endl;
      // MemBlockMapIT		it = this->memBlock_.find(ptr);
      MemBlockMapIT			it = this->memBlock_.end();
      if (it == this->memBlock_.end())
	{
	  free(ptr);
	  return ;
	}

      if (it->second.isArray != isArray)
	{
	  std::cout << "ERROR" << std::endl;
	  exit(0); // FIX ME - add exception
	  // throw CBadDelete(Ptr, It->second.File.Filename(), It->second.Line, !Array);
	}

      file_ << "-- Désallocation | 0x" << ptr
	    << " | " << std::setw(7) << std::setfill(' ')
	    << static_cast<int>(it->second.size) << " octets"
	    << " | " << this->nextDelete_.top().file.getFileName()
	    << " (" << this->nextDelete_.top().line << ")" << std::endl;
      this->memBlock_.erase(it);
      this->nextDelete_.pop();
      free(ptr);
    }
}

void				MemoryManager::nextDelete(const File& file, int line)
{
  MemBlock			deleteBlock;

  deleteBlock.file = file;
  deleteBlock.line = line;

  this->nextDelete_.push(deleteBlock);
}
