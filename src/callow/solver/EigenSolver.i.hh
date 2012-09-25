//----------------------------------*-C++-*----------------------------------//
/**
 *  @file   EigenSolver.i.hh
 *  @author robertsj
 *  @date   Sep 25, 2012
 *  @brief  EigenSolver.i class definition.
 */
//---------------------------------------------------------------------------//

#ifndef callow_EIGENSOLVER_I_HH_
#define callow_EIGENSOLVER_I_HH_

#include "LinearSolverCreator.hh"

namespace callow
{

//---------------------------------------------------------------------------//
template <class T>
EigenSolver<T>::EigenSolver(const double    tol,
                            const int       maxit,
                            std::string     name)
  : d_tolerance(tol)
  , d_maximum_iterations(maxit)
  , d_name(name)
  , d_residual_norm(maxit + 1, 0)
  , d_number_iterations(0)
  , d_monitor_level(1)
{
  Require(d_tolerance >= 0.0);
  Require(d_maximum_iterations > 0);
}

//---------------------------------------------------------------------------//
template <class T>
inline void EigenSolver<T>::set_operators(SP_matrix    A,
                                          SP_matrix    B,
                                          std::string  type)
{
  Insist(A, "The operator A cannot be null");
  d_A = A;
  Ensure(d_A->number_rows() == d_A->number_columns());
  if (B)
  {
    d_B = B;
    Ensure(d_B->number_rows() == d_B->number_columns());
    Ensure(d_B->number_rows() == d_A->number_columns());
    // Create linear solver.  Defaults can be changed by
    // extracting the solver and resetting.  The same goes
    // for the preconditioner, which is null by default.
    d_solver = LinearSolverCreator<PetscScalar>::
               Create(type, d_tolerance, d_tolerance);
    d_solver->set_operators(d_B);
    d_A->print_matlab("A.out");
    d_B->print_matlab("B.out");
  }
}

//---------------------------------------------------------------------------//
template <class T>
inline int EigenSolver<T>::solve(Vector<T> &x, Vector<T> &x0)
{
  Require(x.size() == d_A->number_rows());
  if (x0.size())
    Require(x0.size() == d_A->number_rows());
  d_status = MAXIT;
  solve_impl(x, x0);
  if (d_status ==  MAXIT)
  {
    printf("*** %s did not converge within the maximum number of iterations\n",
           d_name.c_str());
  }
  return d_status;
}

//---------------------------------------------------------------------------//
template <class T>
inline bool EigenSolver<T>::monitor(int it, T l, T r)
{
  // record the iteration and residual norm
  d_number_iterations = it;
  d_residual_norm[it] = r;
  // echo the residual
  if (d_monitor_level > 1)
    printf("iteration: %5i  eigenvalue: %12.8e    residual: %12.8e \n", it, l, r);
  // send a signal
  if (r < d_tolerance)
  {
    if (d_monitor_level > 0)
    {
      printf("*** %s converged in %5i iterations with a residual of %12.8e \n",
             d_name.c_str(), it, r);
    }
    d_status = SUCCESS;
    return true;
  }
  return false;
}



} // end namespace callow

#endif /* callow_EIGENSOLVER_I_HH_ */
