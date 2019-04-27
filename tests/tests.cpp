//
// Fluffy
// @author Lo-X
// @website http://www.loicboutter.fr
// @copyright 2016 All rights reserved
// File created by loic on 20/05/17.
//

#include <bandit/bandit.h>
#include <fluffy/utils/logger.hpp>

using namespace bandit;

int main(int argc, char* argv[])
{
    // Logger in file only mode so that it does not pollute unit tests output
    Fluffy::Logger::getInstance(Fluffy::Logger::LogOutput::File);

    auto ret = bandit::run(argc, argv);

    Fluffy::Logger::deleteInstance();

    return ret;
}