#include <fluffy/file/path.hpp>

using namespace Fluffy;

Path Path::getWorkingDirectory()
{
    return Path(std::filesystem::current_path());
}

std::ostream& Fluffy::operator<<(std::ostream& os, const Path& p)
{
    return (os << p.toString());
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Path::Path(const char* name)
{
    changePath(name);
}

Path::Path(const String& name)
{
    changePath(name);
}

Path::Path(const std::filesystem::path& path)
  : mPath(path)
{
}

Path& Path::operator=(const String& other)
{
    changePath(other);

    return *this;
}

Path Path::operator/(const char* other) const
{
    return operator/(Path(other));
}

Path Path::operator/(const Path& other) const
{
    return Path(mPath / other.mPath);
}

Path Path::operator/(const String& other) const
{
    return operator/(Path(other));
}

bool Path::operator==(const char* other) const
{
    return operator==(Path(other));
}

bool Path::operator==(const Path& other) const
{
    return mPath == other.mPath;
}

bool Path::operator!=(const Path& other) const
{
    return mPath != other.mPath;
}

String Path::toString() const
{
    return mPath.string();
}

bool Path::exists() const
{
    return std::filesystem::exists(mPath);
}

bool Path::isDirectory() const
{
    return std::filesystem::is_directory(mPath);
}

bool Path::isFile() const
{
    return std::filesystem::is_regular_file(mPath);
}

bool Path::isAbsolute() const
{
    return mPath.is_absolute();
}

bool Path::isEmpty() const
{
    return std::filesystem::is_empty(mPath);
}

void Path::clear()
{
    mPath.clear();
}

Path Path::getParent() const
{
    return Path(mPath.parent_path());
}

Path Path::getFilename() const
{
    return Path(mPath.filename());
}

Path Path::getFileStem() const
{
    return Path(mPath.stem());
}

Path Path::getFileExtension() const
{
    return Path(mPath.extension());
}

void Path::changePath(const String& name)
{
    mPath = name;
    normalize();
}

void Path::normalize()
{
    mPath.make_preferred();
}
