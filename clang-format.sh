#!/bin/sh

# core
clang-format -style=file fluffy/core/include/fluffy/*/*.hpp
clang-format -style=file fluffy/core/include/fluffy/*/*.inl
clang-format -style=file fluffy/core/fluffy/*/*.cpp

# utils
clang-format -style=file fluffy/utils/include/fluffy/*/*.hpp
clang-format -style=file fluffy/utils/include/fluffy/*/*.inl
clang-format -style=file fluffy/utils/fluffy/*/*.cpp

# platform
#clang-format -style=file fluffy/platform/*/*/*.hpp
#clang-format -style=file fluffy/platform/*/*/*.inl
#clang-format -style=file fluffy/platform/*/*/*.cpp

