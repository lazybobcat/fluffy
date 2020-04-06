#!/bin/sh

# core
clang-format -style=file -i src/core/include/fluffy/*/*.hpp
clang-format -style=file -i src/core/include/fluffy/*/*/*.hpp
clang-format -style=file -i src/core/include/fluffy/*/*.inl
clang-format -style=file -i src/core/src/*/*.cpp

# ecs
clang-format -style=file -i src/ecs/include/fluffy/*/*.hpp
clang-format -style=file -i src/ecs/include/fluffy/*/*.inl
clang-format -style=file -i src/ecs/src/*.cpp

# utils
clang-format -style=file -i src/utils/include/fluffy/*/*.hpp
clang-format -style=file -i src/utils/include/fluffy/*/*.inl
clang-format -style=file -i src/utils/src/*/*.cpp

# scripting
