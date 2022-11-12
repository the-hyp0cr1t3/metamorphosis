include(UseBreathe)

set(DOCS_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/html)

add_breathe_doc(
  TARGET_NAME docs
  SOURCE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}
  HTML_DIR
    ${DOCS_OUTPUT_DIR}
  DOXY_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
  CONF_FILE
    ${CMAKE_CURRENT_SOURCE_DIR}/conf.py.in
  COMMENT
    "HTML documentation")

add_custom_command(
  TARGET docs
  POST_BUILD
  COMMAND
    ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/images/storyboard.mp4
    ${DOCS_OUTPUT_DIR}/_images/storyboard.mp4)


install(DIRECTORY ${DOCS_OUTPUT_DIR}
        DESTINATION ${CMAKE_INSTALL_DOCDIR} COMPONENT Bresenham_docs)