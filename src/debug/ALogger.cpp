#include			"ALogger.hh"

ALogger				*ALogger::currentLogger_ = NULL;

ALogger::~ALogger()
{}

// OPERATOR

template <typename T>
ALogger				&ALogger::operator<<(const T &toLog)
{
  std::ostringstream		stream;

  stream << toLog;
  write_(stream.str());

  return *currentLogger_;
}

template <>
ALogger				&ALogger::operator<<(const std::string &toLog)
{
  std::ostringstream		stream;

  stream << toLog;
  write_(stream.str());

  return *currentLogger_;
}

// PROTECTED METHODS

std::string			ALogger::getCurrentDate_(void) const
{
  char				cTime[24];
  time_t			currentTime = time(NULL);

  strftime(cTime, sizeof(cTime), "%d/%m/%Y", localtime(&currentTime));
  return cTime;
}

std::string			ALogger::getCurrentTime_(void) const
{
  char				cTime[24];
  time_t			currentTime = time(NULL);

  strftime(cTime, sizeof(cTime), "%H:%M:%S", localtime(&currentTime));
  return cTime;
}


// PUBLIC METHODS

void				ALogger::setLogger(ALogger *logger)
{
  if (currentLogger_)
    delete currentLogger_;
  currentLogger_ = logger;
}

void				ALogger::log(const char *format, ...)
{
  char				buffer[512];
  va_list			params;

  assert(currentLogger_ != NULL);

  va_start(params, format);
  vsprintf(buffer, format, params);
  va_end(params);
  currentLogger_->write_(buffer);
}

ALogger				&ALogger::getLogger(void)
{
  return *currentLogger_;
}
