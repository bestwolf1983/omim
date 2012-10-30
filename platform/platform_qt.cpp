#include "platform.hpp"
#include "constants.hpp"
#include "regexp.hpp"

#include "../coding/file_reader.hpp"

#include "../std/target_os.hpp"
#include "../std/algorithm.hpp"

#include <QtCore/QDir>
#include <QtCore/QFileInfo>


////////////////////////////////////////////////////////////////////////////////////////
ModelReader * Platform::GetReader(string const & file) const
{
  return new FileReader(ReadPathForFile(file),
                        READER_CHUNK_LOG_SIZE, READER_CHUNK_LOG_COUNT);
}

bool Platform::GetFileSizeByName(string const & fileName, uint64_t & size) const
{
  try
  {
    return GetFileSizeByFullPath(ReadPathForFile(fileName), size);
  }
  catch (RootException const &)
  {
    return false;
  }
}

void Platform::GetFilesByRegExp(string const & directory, string const & regexp, FilesList & outFiles)
{
  regexp::RegExpT exp;
  regexp::Create(regexp, exp);

  QDir dir(QString::fromUtf8(directory.c_str()));
  int const count = dir.count();

  for (int i = 0; i < count; ++i)
  {
    string const name = dir[i].toUtf8().data();
    if (regexp::IsExist(name, exp))
      outFiles.push_back(name);
  }
}

string Platform::DeviceName() const
{
  return OMIM_OS_NAME;
}

int Platform::PreCachingDepth() const
{
  return 3;
}

int Platform::ScaleEtalonSize() const
{
  return 512 + 256;
}

int Platform::VideoMemoryLimit() const
{
  return 20 * 1024 * 1024;
}

bool Platform::DoSupportRotation() const
{
  return IsPro();
}

///////////////////////////////////////////////////////////////////////////////
extern Platform & GetPlatform()
{
  class PlatformQt : public Platform
  {
  public:
    PlatformQt()
    {
      m_isPro = true;
    }
  };

  static PlatformQt platform;
  return platform;
}
