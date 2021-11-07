cmake_minimum_required(VERSION 3.14)
project(Property2)

set(CMAKE_CXX_STANDARD 17)

#Property lib files

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
         )

#TODO проверить являемся ли вложенным проектом и если да, то только тогда добавлять в родительский каталог
#Объявим для родителя чтобы он мог напрямую вызывать наши исходники
set(PROPERTY_HDR ${PROPERTY_HDR} PARENT_SCOPE)

foreach(F ${PROPERTY_SRC})
    set(FULL_PROPERTY_SRC ${FULL_PROPERTY_SRC} Property/${F})
endforeach()
set(FULL_PROPERTY_SRC ${FULL_PROPERTY_SRC} PARENT_SCOPE)

add_library(Property STATIC ${PROPERTY_SRC})

option(BUILD_PROPERTY_TEST "Set ON to build property test" ON)

if(${BUILD_PROPERTY_TEST})
    message("Build test enabled")
    #if(NOT EXISTS ${CMAKE_SOURCE_DIR}/pugixml)
        #Если pugixml нет, то клонируем
    #    exec_program("git" "" ARGS "clone --depth=1 https://github.com/zeux/pugixml ${CMAKE_BINARY_DIR}/pugixml")
    #endif()
    #if(NOT EXISTS ${CMAKE_SOURCE_DIR}/sigslot)
        #Если sigslot нет, то клонируем
    #    exec_program("git" "" ARGS "clone --depth=1 https://github.com/palacaze/sigslot ${CMAKE_BINARY_DIR}/sigslot")
    #endif()
    #if(NOT EXISTS ${CMAKE_SOURCE_DIR}/googletest)
    #    #Если каталога тестирования нет, то сами клонируем его
     #   exec_program("git" "" ARGS "clone --depth=1 https://github.com/google/googletest ${CMAKE_BINARY_DIR}/googletest")
    #endif()
    include(FetchContent)
    if(MSVC)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    FetchContent_Declare(pugixml
        GIT_REPOSITORY https://github.com/zeux/pugixml.git
        SOURCE_DIR pugixml
        )

    FetchContent_Declare(sigslot
        GIT_REPOSITORY https://github.com/palacaze/sigslot.git
        SOURCE_DIR sigslot
        )

    FetchContent_Declare(googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            SOURCE_DIR googletest
            )
    FetchContent_MakeAvailable(pugixml sigslot googletest)

    add_executable(PropertyTest
            ${PROPERTY_SRC}
            pugixml/src/pugixml.cpp
            tests/PropertyTest.cpp
            tests/TestCasePropertyClass.cpp
            tests/VariableTest.cpp
            tests/PropertyEditorTest.cpp
            )
    target_include_directories(PropertyTest
                PUBLIC ${CMAKE_SOURCE_DIR}
                PUBLIC ${CMAKE_BINARY_DIR}/pugixml/src
                PUBLIC ${CMAKE_BINARY_DIR}/sigslot/include
                PUBLIC ${CMAKE_BINARY_DIR}/googletest/googletest/include
            )
    target_link_libraries(PropertyTest PUBLIC gtest gtest_main gmock)
    enable_testing()
    add_test(NAME PropertyTest COMMAND PropertyTest)
endif()

#Property library
#Dependences:
#   pugixml:
#       submodule: https://github.com/zeux/pugixml.git to dir: puxixml
#       include dir: pugixml/src
#   sigslot:
#       submodule: https://github.com/palacaze/sigslot.git to dir: sigslot
#       include dir: sigslot/include
#   if BUILD_PROPERTY_TEST googletest:
#       submodule: https://github.com/google/googletes to dir: googletest
#       include dir: googletest/googletest/include
