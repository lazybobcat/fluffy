add_executable(sandbox sandbox.cpp layers/sandbox2d_state.hpp layers/imgui_state.hpp)
target_link_libraries(sandbox ${FLUFFY_INTERNAL_LIBS} ${FLUFFY_EXTERNAL_LIBS})