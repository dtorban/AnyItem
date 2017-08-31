project (AnyItem)

# -------------------------------- Project -------------------------------------

include_directories(src)

# Core engine files

set (${PROJECT_NAME}_cpp
  main.cpp
  AnyItem.cpp
  impl/BlankItem.cpp
  impl/DictionaryItemImpl.cpp
  impl/ArrayItemImpl.cpp
)
set (${PROJECT_NAME}_h
)

# Library configuration

set (${PROJECT_NAME}_source_files
  ${${PROJECT_NAME}_cpp}
)
set (${PROJECT_NAME}_header_files
${${PROJECT_NAME}_h}
)

source_group("Source Files" FILES ${${PROJECT_NAME}_cpp})
source_group("Header Files" FILES ${${PROJECT_NAME}_h})

add_library (${PROJECT_NAME} ${${PROJECT_NAME}_source_files} ${${PROJECT_NAME}_header_files})
add_executable (${PROJECT_NAME}b ${${PROJECT_NAME}_source_files} ${${PROJECT_NAME}_header_files})

install(DIRECTORY ${PROJECT_SOURCE_DIR}/  DESTINATION "include/AnyItem" FILES_MATCHING PATTERN "*.h")

install( TARGETS ${PROJECT_NAME}
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib
         RUNTIME DESTINATION bin)



