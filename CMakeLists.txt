cmake_minimum_required(VERSION 3.14)
project(Property2)

set(CMAKE_CXX_STANDARD 14)

#Property lib files

set(PROPERTY_HDR
        Types.h
        Algorithms.h
        EnumInfo.h
        Variable.h
        Serialization.h
        )

set(PROPERTY_SRC
        EnumInfo.cpp
        Variable.cpp
        Serialization.cpp
        )

#TODO проверить являемся ли вложенным проектом и если да, то только тогда добавлять в родительский каталог
#Объявим для родителя чтобы он мог напрямую вызывать наши исходники
set(PROPERTY_HDR ${PROPERTY_HDR} PARENT_SCOPE)

foreach(F ${PROPERTY_SRC})
    set(FULL_PROPERTY_SRC ${FULL_PROPERTY_SRC} Property/${F})
endforeach()
set(FULL_PROPERTY_SRC ${FULL_PROPERTY_SRC} PARENT_SCOPE)

add_library(Property STATIC ${PROPERTY_SRC})

option(BUILD_PROPERTY_TEST "Set ON to build property test" OFF)

if(${BUILD_PROPERTY_TEST})
    add_executable(PropertyTest tests/PropertyTest.cpp)
    enable_testing()
    add_test(NAME PropertyTest COMMAND PropertyTest)
endif()

#Property library
#Dependences:
#   pugixml:
#       submodule: https://github.com/zeux/pugixml.git to puxixml
#       include dir: pugixml/src

message("Property library is added")
message("Dependences:")