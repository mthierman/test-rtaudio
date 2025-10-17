set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(RTAUDIO_API_ASIO ON CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(rtaudio GIT_REPOSITORY "https://github.com/thestk/rtaudio.git" GIT_TAG "6.0.1")

FetchContent_MakeAvailable(rtaudio)

add_executable(${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

target_sources(${PROJECT_NAME} PRIVATE main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE rtaudio)
