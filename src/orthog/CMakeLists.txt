#------------------------------------------------------------------------------#
# src/orthog/CMakeLists.txt
#------------------------------------------------------------------------------#

set(LIB_NAME "orthog")

#-----------------------------------------------------------------------------#
# SOURCE
#-----------------------------------------------------------------------------#

set(SRC
  OrthogonalBasis.cc
  ContinuousOrthogonalBasis.cc
  CLP.cc
  DLP.cc
  DCT.cc
  DCP.cc
  Jacobi01.cc
  ChebyshevU.cc
  DDF.cc
  TransformedBasis.cc
  UserBasis.cc
)

#-----------------------------------------------------------------------------#
# LINKED LIBRARIES
#-----------------------------------------------------------------------------#

set(LINKED_LIBS
    callow                      
)

#-----------------------------------------------------------------------------#
# LIBRARY
#-----------------------------------------------------------------------------#

setup_detran_library(${LIB_NAME} "${SRC}" "${LINKED_LIBS}")
