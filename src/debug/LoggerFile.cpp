#include			"LoggerFile.hh"

// CTOR - DTOR

LoggerFile::LoggerFile(const std::string &filename)
  : file_(filename.c_str())
{
  if (file_.fail()) // FIX ME - add exception
    {
      std::cout << "CAN'T OPEN FILE" << std::endl;
      exit(0);
    }
  file_ << "===========================================" << std::endl;
  file_ << "  Event log - " << this->getCurrentDate_() << std::endl;
  file_ << "===========================================" << std::endl;
}

LoggerFile::~LoggerFile()
{
  file_ << std::endl;
  file_ << "========================================" << std::endl;
  file_ << "  Closed at " << this->getCurrentTime_() << std::endl;
  file_ << "=========================================" << std::endl;
  file_.close();
}

void				LoggerFile::write_(const std::string &message)
{
  assert(file_.is_open());
  file_ << message << std::endl;
}

