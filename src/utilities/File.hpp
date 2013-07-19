#ifndef				FILE_H_
#define				FILE_H_

# include			<string>
# include			<fstream>

class				File
{
public :
  File(const std::string &name = "unknown")
    : filePath_(name)
  {}

  File(const char *name)
    : filePath_(name)
  {}

  bool				exists() const
  {
    std::ifstream		file(this->filePath_.c_str());

    return file.is_open();
  }

  const std::string		&getFullName() const
  {
    return this->filePath_;
  }

  const std::string		getFileName() const
  {
    std::string::size_type	pos;

    pos = this->filePath_.find_last_of("\\/");

    if (pos != std::string::npos)
      return this->filePath_.substr(pos + 1, std::string::npos);
    else
      return this->filePath_;
  }

  std::string			getShortFileName() const
  {
    return this->getFileName().substr(0, this->getFileName().find_last_of("."));
  }

  std::string			getExtension() const
  {
    std::string::size_type	pos;

    pos = this->filePath_.find_last_of(".");
    if (pos != std::string::npos)
      return this->filePath_.substr(pos + 1, std::string::npos);
    else
      return "";
  }

private :
  std::string			filePath_;
};

#endif				/* !FILE_H_ */
