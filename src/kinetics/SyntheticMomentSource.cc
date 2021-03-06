//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   SyntheticMomentSource.cc
 *  @brief  SyntheticMomentSource
 *  @author Jeremy Roberts
 *  @date   Nov 15, 2012
 */
//---------------------------------------------------------------------------//

#include "SyntheticMomentSource.hh"

namespace detran
{

//---------------------------------------------------------------------------//
SyntheticMomentSource::SyntheticMomentSource(const size_t number_groups,
                                             SP_mesh mesh,
                                             SP_material material)
  : Base(number_groups, mesh, SP_quadrature(0), material)
  , d_source(d_number_groups, vec_dbl(d_mesh->number_cells(), 0.0))
{
  /* ... */
}

} // end namespace detran

//---------------------------------------------------------------------------//
//              end of file SyntheticMomentSource.cc
//---------------------------------------------------------------------------//
