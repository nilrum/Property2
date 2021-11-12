cmake_minimum_required(VERSION 3.14)
project(Property)

set(CMAKE_CXX_STANDARD 17)

include(C:/CMakeProjects/Fetch.cmake)

#Определяем зависимости проекта

#Загрузка зависимостей без add_subdirectory
#Набор каталогов для указания target_include..
Populate(Base github.com/nilrum/Base .)
Populate(pugixml github.com/zeux/pugixml src)
Populate(sigslot github.com/palacaze/sigslot include)

#Набор h и cpp файлов библиотеки
set(PROPERTY_HDR
        Result.h
        EnumInfo.h
        Variable.h
        FileFunctions.h
        PropertyClass.h
        Serialization.h
        Serialization.hpp
        PropertyEditor.h
        GlobalCustom.h
        )

set(PROPERTY_SRC
        EnumInfo.cpp
        Result.cpp
        Variable.cpp
        FileFunctions.cpp
        PropertyClass.cpp
        Serialization.cpp
        PropertyEditor.cpp
        GlobalCustom.cpp
        )

#Объявление библиотеки
if(NOT TARGET Property)
    add_library(Property STATIC ${PROPERTY_SRC} ${pugixml_INCL}/pugixml.cpp)
    target_include_directories(Property PUBLIC ${FETCH_DIR} ${Property_DEPS_INCL})
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
            tests/VariableTest.cpp
            tests/PropertyEditorTest.cpp
            )
    
    target_link_libraries(PropertyTest Property gtest gtest_main gmock)
    enable_testing()
    add_test(NAME PropertyTest COMMAND PropertyTest)
endif()