cmake_minimum_required(VERSION 3.14)
project(Property)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_SOURCE_DIR}/Libs/Fetch.cmake)

#Определяем зависимости проекта

#Загрузка зависимостей без add_subdirectory
#Набор каталогов для указания target_include..
set(PROPERTY_INCL_DEPS ${CMAKE_SOURCE_DIR})

Populate(pugixml PUGIXML src github.com/zeux/pugixml PROPERTY_INCL_DEPS)
Populate(sigslot SIGSLOT include github.com/palacaze/sigslot PROPERTY_INCL_DEPS)

#Набор h и cpp файлов библиотеки
set(PROPERTY_HDR
        Types.h
        Algorithms.h
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
add_library(Property STATIC ${PROPERTY_SRC} ${PUGIXML_INCL}/pugixml.cpp)
target_include_directories(Property PUBLIC ${PROPERTY_INCL_DEPS})

if(${BUILD_TEST})
    message("Build property test enabled")
    #Загрузка googletest и вызов add_subdirectory
    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    MakeAvailable(googletest GOOGLETEST googletest/include github.com/google/googletest PROPERTY_INCL_DEPS)

    #Объявим цель тестирования
    add_executable(PropertyTest
            tests/PropertyTest.cpp
            tests/TestCasePropertyClass.cpp
            tests/VariableTest.cpp
            tests/PropertyEditorTest.cpp
            )

    target_include_directories(PropertyTest
                PUBLIC ${FETCH_DIR}
                PUBLIC ${PROPERTY_INCL_DEPS}
            )
    target_link_libraries(PropertyTest PUBLIC Property gtest gtest_main gmock)
    enable_testing()
    add_test(NAME PropertyTest COMMAND PropertyTest)
endif()

if(NOT DEFINED ROOT_PROJECT)
    #Объявим каталоги включения для родительского проекта
    set(PROPERTY_INCL_DEPS ${PROPERTY_INCL_DEPS} PARENT_SCOPE)
    #Объявим для родителя наши исходники

    foreach(F ${PROPERTY_SRC})
        set(FULL_PROPERTY_SRC ${FULL_PROPERTY_SRC} ${FETCH_DIR}/Property/${F})
    endforeach()
    set(FULL_PROPERTY_SRC ${FULL_PROPERTY_SRC} ${PUGIXML_DIR}/src/pugixml.cpp PARENT_SCOPE)
endif()