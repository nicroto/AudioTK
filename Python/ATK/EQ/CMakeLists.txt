
FILE(GLOB_RECURSE
  PYTHON_MODULE_EQ_SRC
  *.cpp
)

FILE(GLOB_RECURSE
  PYTHON_MODULE_EQ_HEADERS
  *.h
)

SET(PYTHON_MODULE_EQ_DEFINITIONS)
SET(PYTHON_MODULE_EQ_INCLUDE)
SET(PYTHON_MODULE_EQ_LIBRARIES ATKCore ATKEQ ATKUtility)

SET(PYTHON_MODULE_EQ_NAME PythonEQ)
SET(PYTHON_MODULE_EQ_FOLDER EQ)

ATK_add_python_module(PYTHON_MODULE_EQ)
