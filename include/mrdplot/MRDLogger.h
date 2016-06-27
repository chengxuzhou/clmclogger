#pragma once

#include <vector>
#include <list>
#include <map>

class MRDLogger
{

protected:
  enum LoggerDataType {
    LOOGER_DATA_TYPE_UNDEF = 0,
    LOGGER_DATA_TYPE_BOOL,
    LOGGER_DATA_TYPE_CHAR,
    LOGGER_DATA_TYPE_INT,
    LOGGER_DATA_TYPE_FLOAT,
    LOGGER_DATA_TYPE_DOUBLE,
    LOGGER_DATA_TYPE_LONG,
    LOGGER_DATA_TYPE_UCHAR,
    LOGGER_DATA_TYPE_UINT,
    LOGGER_DATA_TYPE_ULONG,
    LOGGER_DATA_TYPE_SIZE
  };

  class DataChannel {
  public:
    std::string name;
    std::string unit;
    LoggerDataType type;
    size_t channel;
    const void *ptr;
    std::vector<float> data;

    DataChannel()
    {
      type = LOOGER_DATA_TYPE_UNDEF;
      ptr = NULL;
      channel = 0;
    }
  };

  std::string _name;
  float _freq;
  
  size_t _ptEnd;
  size_t _ptStart;

  std::map<const std::string, DataChannel> _channels;
  std::list<const DataChannel *> _outputOrder;
  
  void _reset();

public:
  MRDLogger();
  virtual ~MRDLogger();
  void saveData();
  
  bool readFromFile(const std::string &name);
  bool writeToFile(const std::string &name);
  
  bool addChannel(const std::string &name, const std::string &unit, const bool *ptr) 
    { return _addChannel(name, unit, ptr, LOGGER_DATA_TYPE_BOOL); } 
  bool addChannel(const std::string &name, const std::string &unit, const char *ptr)
    { return _addChannel(name, unit, ptr, LOGGER_DATA_TYPE_CHAR); } 
  bool addChannel(const std::string &name, const std::string &unit, const int *ptr)
    { return _addChannel(name, unit, ptr, LOGGER_DATA_TYPE_INT); } 
  bool addChannel(const std::string &name, const std::string &unit, const float *ptr)
    { return _addChannel(name, unit, ptr, LOGGER_DATA_TYPE_FLOAT); } 
  bool addChannel(const std::string &name, const std::string &unit, const double *ptr)
    { return _addChannel(name, unit, ptr, LOGGER_DATA_TYPE_DOUBLE); } 
  bool addChannel(const std::string &name, const std::string &unit, const long *ptr)
    { return _addChannel(name, unit, ptr, LOGGER_DATA_TYPE_LONG); } 
  bool addChannel(const std::string &name, const std::string &unit, const unsigned char *ptr)
    { return _addChannel(name, unit, ptr, LOGGER_DATA_TYPE_UCHAR); } 
  bool addChannel(const std::string &name, const std::string &unit, const unsigned int *ptr)
    { return _addChannel(name, unit, ptr, LOGGER_DATA_TYPE_UINT); } 
  bool addChannel(const std::string &name, const std::string &unit, const unsigned long *ptr)
    { return _addChannel(name, unit, ptr, LOGGER_DATA_TYPE_ULONG); } 

  bool hasMoreData() const { return size() != 0; }
  void popData();

  size_t size() const;
  size_t maxSize() const;

private:
  bool _addChannel(const std::string &name, const std::string &unit, const void *ptr, LoggerDataType type);
};
