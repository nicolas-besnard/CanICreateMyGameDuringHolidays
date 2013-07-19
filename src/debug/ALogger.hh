#ifndef				ALOGGER_HH_
# define			ALOGGER_HH_

# include			<string>
# include			<sstream>

# include			<cstdarg>
# include			<cassert>
# include			<cstdio>
# include			<ctime>

class ALogger
{
public :
  virtual ~ALogger();
  static void			setLogger(ALogger *Logger);
  static ALogger		&getLogger(void);
  static void			log(const char *format, ...);

  template <class T>
  ALogger			&operator<<(const T &toLog);

  ALogger			&operator<<(const std::string &toLog);

protected:
  std::string			getCurrentDate_(void) const;
  std::string			getCurrentTime_(void) const;

private :
  virtual void			write_(const std::string &message) = 0;
  static ALogger		*currentLogger_;
};

#endif				/* !ALOGGER_HH_ */
