#!/bin/sh

# core
clang-format --dry-run -style=file fluffy/core/include/fluffy/*/*.hpp
clang-format --dry-run -style=file fluffy/core/include/fluffy/*/*.inl
clang-format --dry-run -style=file fluffy/core/fluffy/*/*.cpp

# utils
clang-format --dry-run -style=file fluffy/utils/include/fluffy/*/*.hpp
clang-format --dry-run -style=file fluffy/utils/include/fluffy/*/*.inl
clang-format --dry-run -style=file fluffy/utils/fluffy/*/*.cpp

# platform
#clang-format --dry-run -style=file fluffy/platform/*/*/*.hpp
#clang-format --dry-run -style=file fluffy/platform/*/*/*.inl
#clang-format --dry-run -style=file fluffy/platform/*/*/*.cpp

