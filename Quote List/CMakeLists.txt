# CMakeList.txt: проект CMake для Checkhold; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

cmake_minimum_required(VERSION 3.8)

# Добавьте источник в исполняемый файл этого проекта.
file(GLOB_RECURSE SOURCES
	"${CMAKE_SOURCE_DIR}/source/*.cpp"
)

set(RESOURCE_FILE "${CMAKE_SOURCE_DIR}/Resources/resources.rc")

add_executable(QuoteList 
"Quote List.cpp" 
${RESOURCE_FILE}
${SOURCES}
)

include_directories(${CMAKE_SOURCE_DIR}/include/)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
