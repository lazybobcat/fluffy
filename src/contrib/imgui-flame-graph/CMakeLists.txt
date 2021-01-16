set(SOURCE_FILES imgui_widget_flamegraph.h imgui_widget_flamegraph.cpp)

add_library(imgui-flame-graph STATIC ${SOURCE_FILES})
target_link_libraries(imgui)
target_include_directories(imgui-flame-graph PUBLIC ".")