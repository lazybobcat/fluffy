#include <bandit/bandit.h>
#include <fluffy/pch.hpp>

using namespace bandit;

int main(int argc, char* argv[])
{
    Fluffy::Logger::init(true);

    auto ret = bandit::run(argc, argv);

    Fluffy::Logger::clear();

    return ret;
}