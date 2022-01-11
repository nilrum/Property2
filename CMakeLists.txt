cmake_minimum_required(VERSION 3.14)
project(Property)

set(CMAKE_CXX_STANDARD 17)

include(C:/CMakeProjects/Fetch.cmake)

#Определяем зависимости проекта
MakeAvailable(Base github.com/nilrum/Base .)
#Загрузка зависимостей без add_subdirectory
#Набор каталогов для указания target_include..
Populate(pugixml github.com/zeux/pugixml src)
Populate(sigslot github.com/palacaze/sigslot include)

#Набор h и cpp файлов библиотеки
set(PROPERTY_SRC
        PropertyClass.cpp
        Serialization.cpp
        PropertyEditor.cpp
        GlobalCustom.cpp
        Progress.cpp
        History.cpp
        )

#Объявление библиотеки
if(NOT TARGET Property)
    add_library(Property STATIC ${PROPERTY_SRC} ${pugixml_INCL}/pugixml.cpp)
    target_include_directories(Property PUBLIC ${FETCH_DIR} ${Property_DEPS_INCL})
    target_link_libraries(Property PUBLIC Base)
endif()

if(${BUILD_TEST})
    message("Build property test enabled")
    #Загрузка googletest и вызов add_subdirectory
    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    if(NOT TARGET gtest)
        MakeAvailable(googletest github.com/google/googletest googletest/include)
    endif()
    #Объявим цель тестирования
    add_executable(PropertyTest
            tests/PropertyTest.cpp
            tests/TestCasePropertyClass.cpp
            tests/PropertyEditorTest.cpp
            )

    target_link_libraries(PropertyTest Property gtest gtest_main gmock)
    enable_testing()
    add_test(NAME PropertyTest COMMAND PropertyTest)
endif()