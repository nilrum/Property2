cmake_minimum_required(VERSION 3.14)
project(Property)

set(CMAKE_CXX_STANDARD 17)

#Property lib files

#Определяем зависимости проекта
include(FetchContent)

if(NOT DEFINED ${FETCH_DIR})
    set(FETCH_DIR ${CMAKE_SOURCE_DIR}/Libs)
endif()

set(PUGIXML_DIR ${FETCH_DIR}/pugixml)
FetchContent_Declare(pugixml
        GIT_REPOSITORY https://github.com/zeux/pugixml.git
        SOURCE_DIR ${PUGIXML_DIR}
        )

set(SIGSLOT_DIR ${FETCH_DIR}/sigslot)
FetchContent_Declare(sigslot
        GIT_REPOSITORY https://github.com/palacaze/sigslot.git
        SOURCE_DIR ${SIGSLOT_DIR}
        )

#FetchContent_MakeAvailable(pugixml sigslot)
FetchContent_Populate(pugixml)
FetchContent_Populate(sigslot)

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

#TODO проверить являемся ли вложенным проектом и если да, то только тогда добавлять в родительский каталог
#Объявим для родителя чтобы он мог напрямую вызывать наши исходники

#foreach(F ${PROPERTY_SRC})
#    set(FULL_PROPERTY_SRC ${FULL_PROPERTY_SRC} Property/${F})
#endforeach()
#set(FULL_PROPERTY_SRC ${FULL_PROPERTY_SRC} PARENT_SCOPE)

add_library(Property STATIC ${PROPERTY_SRC})

option(BUILD_TEST "Set ON to build property test" ON)


if(${BUILD_TEST})
    message("Build property test enabled")

    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    set(GOOGLETEST_DIR ${FETCH_DIR}/googletest)
    FetchContent_Declare(googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            SOURCE_DIR ${GOOGLETEST_DIR}
            )
    FetchContent_MakeAvailable(googletest)

    add_executable(PropertyTest
            ${PROPERTY_SRC}
            tests/PropertyTest.cpp
            tests/TestCasePropertyClass.cpp
            tests/VariableTest.cpp
            tests/PropertyEditorTest.cpp
            )
    target_include_directories(PropertyTest
                PUBLIC ${CMAKE_SOURCE_DIR}
                PUBLIC ${FETCH_DIR}
                PUBLIC ${PUGIXML_DIR}/src
                PUBLIC ${SIGSLOT_DIR}/include
                PUBLIC ${GOOGLETEST_DIR}/googletest/include
            )
    target_link_libraries(PropertyTest PUBLIC gtest gtest_main gmock)
    enable_testing()
    add_test(NAME PropertyTest COMMAND PropertyTest)
endif()