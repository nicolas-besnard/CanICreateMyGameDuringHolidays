#ifndef				LOGGERFILE_HH_
# define			LOGGERFILE_HH_

# include			<fstream>
# include			<iostream>

# include			<cstdlib> // FIX ME - add exception

# include			"ALogger.hh"

class				LoggerFile : public ALogger
{
public:
  LoggerFile(const std::string &filename = "output.log");
  virtual ~LoggerFile();

protected:

private:
  LoggerFile 			&operator=(const LoggerFile &other);
  LoggerFile(const LoggerFile &other);
  virtual void			write_(const std::string &message);
  std::ofstream			file_;
};

#endif				/* !LOGGERFILE_HH_ */
