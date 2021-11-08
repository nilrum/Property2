cmake_minimum_required(VERSION 3.14)
project(Property)

set(CMAKE_CXX_STANDARD 17)

#Property lib files

#Определяем зависимости проекта
if(NOT DEFINED FETCH_DIR)
    #Если FETCH_DIR не объявлен, то считаем что это корневой проект
    set(FETCH_DIR ${CMAKE_SOURCE_DIR}/Libs)
    set(ROOT_PROJECT TRUE)
endif()

#Каталоги для загрузки зависимостей
set(PUGIXML_DIR ${FETCH_DIR}/pugixml)
set(SIGSLOT_DIR ${FETCH_DIR}/sigslot)

#Набор каталогов для указания target_include..
set(PROPERTY_INCL_DEPS
        ${PUGIXML_DIR}/src
        ${SIGSLOT_DIR}/include)

#Загрузка зависимостей без add_subdirectory
include(FetchContent)

FetchContent_Declare(pugixml
        GIT_REPOSITORY https://github.com/zeux/pugixml.git
        SOURCE_DIR ${PUGIXML_DIR}
        )

FetchContent_Declare(sigslot
        GIT_REPOSITORY https://github.com/palacaze/sigslot.git
        SOURCE_DIR ${SIGSLOT_DIR}
        )

FetchContent_Populate(pugixml)
FetchContent_Populate(sigslot)

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
        )

set(PROPERTY_SRC
        EnumInfo.cpp
        Result.cpp
        Variable.cpp
        FileFunctions.cpp
        PropertyClass.cpp
        Serialization.cpp
        PropertyEditor.cpp
        ${PUGIXML_DIR}/src/pugixml.cpp
        )

#Объявление библиотеки
add_library(Property STATIC ${PROPERTY_SRC})
target_include_directories(Property PUBLIC ${PROPERTY_INCL_DEPS})

#Если не указано что либо другого, то тесты включены по умолчанию
if(NOT DEFINED BUILD_TEST)
    set(BUILD_TEST ON)
endif()

if(${BUILD_TEST})
    message("Build property test enabled")
    #Загрузка googletest и вызов add_subdirectory
    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    set(GOOGLETEST_DIR ${FETCH_DIR}/googletest)
    FetchContent_Declare(googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            SOURCE_DIR ${GOOGLETEST_DIR}
            )
    FetchContent_MakeAvailable(googletest)

    #Обновим каталоги зависимостей
    set(PROPERTY_INCL_DEPS ${PROPERTY_INCL_DEPS} ${GOOGLETEST_DIR}/googletest/include)

    #Объявим цель тестирования
    add_executable(PropertyTest
            ${PROPERTY_SRC}
            tests/PropertyTest.cpp
            tests/TestCasePropertyClass.cpp
            tests/VariableTest.cpp
            tests/PropertyEditorTest.cpp
            )

    target_include_directories(PropertyTest
                PUBLIC ${FETCH_DIR}
                PUBLIC ${PROPERTY_INCL_DEPS}
            )
    target_link_libraries(PropertyTest PUBLIC gtest gtest_main gmock)
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
    set(FULL_PROPERTY_SRC ${FULL_PROPERTY_SRC} PARENT_SCOPE)
endif()