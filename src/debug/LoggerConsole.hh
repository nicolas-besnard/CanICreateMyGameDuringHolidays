#ifndef				LOGGERCONSOLE_HH_
# define			LOGGERCONSOLE_HH_

# include			<iostream>

# include			"ALogger.hh"

class				LoggerConsole : public ALogger
{
private:
  virtual void			write_(const std::string & message)
  {
    std::clog << message << std::endl;
  }
};

#endif				/* !LOGGERCONSOLE_HH_ */
