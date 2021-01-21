cmake_minimum_required(VERSION 3.19)
project(clazy-inspection-checker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "/usr/local")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

add_executable(${PROJECT_NAME} main.cpp test/level2/string-allocations.cpp test/level0/empty-qstringliteral.cpp test/level0/connect-by-name.cpp test/level0/connect-non-signal.cpp test/level0/connect-not-normalized.cpp test/level0/container-anti-pattern.cpp test/level0/lambda-in-connect.cpp test/level0/qgetenv.cpp test/level0/qenums.cpp test/level1/auto-unexpected-qstringbuilder.cpp)
if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
