README - libdetran
------------------

Detran is a set of simple utilities for deterministic neutral particle 
transport, mostly with a focus on easy algorithm development for reactor 
physics and other transport applications.  Several aspects of the design 
are directly inspired by ORNL code Denovo, especially with respect to 
object-orientation.  

Current features:
  - Multigroup diffusion, discrete ordinates, and method of 
    characteristics
  - Various built-in fixed source and eigenvalue solvers that can be extended
    via use of PETSc and SLEPc
  - Initial support for time-dependent transport with time varying sources
    and materials as well as support for arbitrary state-dependent materials
    for modeling feedback
  - Executable input via HDF5 or a somewhat limited text-based input
  - Full access via a SWIG-generated Python front end
  - Output to Silo for visualization in Visit or Paraview


# INSTALLATION

### Create environment
# $ conda create -n py2 python=2
# $ conda activate py2
# $ conda install numpy pandas 
# $ conda install -c conda-forge matplotlib petsc


### Get code
```
>>> mkdir -p  DETRAN_DIR/install
>>> cd DETRAN_DIR
>>> git clone https://github.com/baklanovp/libdetran.git 
>>> git clone https://github.com/baklanovp/detran-examples.git
``` 

### Make program and install
# cd DETRAN_DIR/src
# $ ../tools/config_detran


