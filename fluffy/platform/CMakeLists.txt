set(FLUFFY_PLATFORM_LIBS "")

if (FLUFFY_USE_OPENGL OR FLUFFY_USE_OPENGL_ES2 OR FLUFFY_USE_OPENGL_ES3)
    add_subdirectory(opengl)
    set(FLUFFY_PLATFORM_LIBS ${FLUFFY_PLATFORM_LIBS} "fluffy-opengl")
    target_include_directories(fluffy-opengl PUBLIC "opengl/src")
endif()

set(FLUFFY_INTERNAL_LIBS ${FLUFFY_INTERNAL_LIBS} ${FLUFFY_PLATFORM_LIBS} PARENT_SCOPE)