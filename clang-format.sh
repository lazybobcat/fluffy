#!/bin/sh

# core
clang-format --dry-run -style=file -i fluffy/core/include/fluffy/*/*.hpp
clang-format --dry-run -style=file -i fluffy/core/include/fluffy/*/*.inl
clang-format --dry-run -style=file -i fluffy/core/fluffy/*/*.cpp

# utils
clang-format --dry-run -style=file -i fluffy/utils/include/fluffy/*/*.hpp
clang-format --dry-run -style=file -i fluffy/utils/include/fluffy/*/*.inl
clang-format --dry-run -style=file -i fluffy/utils/fluffy/*/*.cpp

# platform
#clang-format --dry-run -style=file -i fluffy/platform/*/*/*.hpp
#clang-format --dry-run -style=file -i fluffy/platform/*/*/*.inl
#clang-format --dry-run -style=file -i fluffy/platform/*/*/*.cpp

