//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   InnerGMRES.cc
 * \author robertsj
 * \date   Apr 4, 2012
 * \brief  InnerGMRES class definition.
 * \note   Copyright (C) 2012 Jeremy Roberts.
 */
//---------------------------------------------------------------------------//

// Detran
#include "InnerGMRES.hh"
//
//#include "CMR.hh"

namespace detran
{

// Constructor
template <class D>
InnerGMRES<D>::InnerGMRES(SP_input          input,
                          SP_state          state,
                          SP_mesh           mesh,
                          SP_material       material,
                          SP_quadrature     quadrature,
                          SP_boundary       boundary,
                          SP_externalsource q_e,
                          SP_fissionsource  q_f)
  :  InnerIteration<D>::InnerIteration(input,
                                       state,
                                       mesh,
                                       material,
                                       quadrature,
                                       boundary,
                                       q_e,
                                       q_f)
  , d_moments_size(0)
  , d_boundary_size(0)
{

  // Error from PETSc calls.
  PetscErrorCode ierr;

  // Determine the sizes of the moments.
  d_moments_size = mesh->number_cells();

  // Determine the sizes of any reflected boundary fluxes.
  for (int side = 0; side < 2*D::dimension; side++)
  {
    if (boundary->is_reflective(side))
    {
      // We only need to store only half of the unknowns.
      d_boundary_size += boundary->boundary_flux_size(side)/2;
    }
  }

  // Total number of unknowns in the within-group solve.
  int number_unknowns = d_moments_size + d_boundary_size;

  ierr = MatCreateShell(PETSC_COMM_WORLD,
                        number_unknowns,
                        number_unknowns,
                        number_unknowns,
                        number_unknowns,
                        this,
                        &d_operator);
  Insist(!ierr, "Error creating MR shell matrix.");

  // Create the corresponding vectors.
  ierr = VecCreateSeq(PETSC_COMM_WORLD,
                      number_unknowns,
                      &d_X);
  ierr = VecCreateSeq(PETSC_COMM_WORLD,
                      number_unknowns,
                      &d_B);

  VecSet(d_X, 0.0);
  VecSet(d_B, 0.0);

  // Set the operator.
  ierr = set_operation();
  Insist(!ierr, "Error setting matrix-vector operation.");

  // Create the KSP object.
  ierr = KSPCreate(PETSC_COMM_WORLD, &d_solver);
  Insist(!ierr, "Error creating KSP object.");

  // Set the operator.
  KSPSetOperators(d_solver, d_operator, d_operator, SAME_NONZERO_PATTERN);

  // Set tolerances.
  ierr = KSPSetTolerances(d_solver,
                          d_tolerance,
                          PETSC_DEFAULT,
                          PETSC_DEFAULT,
                          PETSC_DEFAULT);

  // Allow for command line flags.
  ierr = KSPSetFromOptions(d_solver);

}

template <class D>
PetscErrorCode InnerGMRES<D>::set_operation()
{
  return MatShellSetOperation(d_operator,
                              MATOP_MULT,
                              (void(*)(void)) apply_WGTO_3D);
}
template <>
PetscErrorCode InnerGMRES<_2D>::set_operation()
{
  return MatShellSetOperation(d_operator,
                              MATOP_MULT,
                              (void(*)(void)) apply_WGTO_2D);
}
template <>
PetscErrorCode InnerGMRES<_1D>::set_operation()
{
  return MatShellSetOperation(d_operator,
                              MATOP_MULT,
                              (void(*)(void)) apply_WGTO_1D);
}

} // end namespace detran

//---------------------------------------------------------------------------//
//              end of InnerGMRES.cc
//---------------------------------------------------------------------------//
