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
```
>>> conda create -n py2 python=2
>>> conda activate py2
>>> conda install numpy pandas 
>>> conda install -c conda-forge matplotlib petsc
```


### Install Petsc
- https://damask3.mpie.de/installation/damask-source/spectral-solver/petsc/

```
 ./configure --with-cc=gcc --with-cxx=g++ --with-fc=gfortran \
    --download-mpich --download-fftw --download-hdf5 --download-fblaslapack \
    --download-chaco --download-hypre --download-metis \
    --download-ml --download-mumps --download-parmetis --download-scalapack \
    --download-suitesparse --download-superlu --download-superlu_dist \
    --download-triangle --download-zlib --with-cxx-dialect=C++11 \
    --with-c2html=0 --with-debugging=0 --with-ssl=0 --with-x=0 \
    COPTFLAGS="-O3 -xHost -no-prec-div" CXXOPTFLAGS="-O3 -xHost -no-prec-div" \
     FOPTFLAGS="-O3 -xHost -no-prec-div" \
     PETSC_DIR=$(pwd)```
```


### Install Slepc
- https://slepc.upv.es/documentation/
```
>>> wget https://slepc.upv.es/download/distrib/slepc-3.14.1.tar.gz
>>> tar zxvf  slepc-3.14.1.tar.gz
>>> cd slepc-3.14.1
>>> export PETSC_DIR=${HOME}/bin/petsc
>>> export PETSC_ARCH=arch-linux-c-opt
>>> ./configure
>>> make
```


### Install Silo (to plot)
- https://wci.llnl.gov/simulation/computer-codes/silo
```
>>> wget https://wci.llnl.gov/sites/wci/files/2021-01/silo-4.10.2.tgz
>>> tar zxvf  silo-4.10.2.tgz
>>> cd silo-4.10.2
>>> ./configure  --prefix=/home/bakl/bin/silo-4.10.2/bin
>>> make
>>> make install
```

### Get code
```
>>> mkdir -p  DETRAN_DIR/install
>>> cd DETRAN_DIR
>>> git clone https://github.com/baklanovp/libdetran.git 
>>> git clone https://github.com/baklanovp/detran-examples.git
``` 


### Make program and install
```
>>> cd DETRAN_DIR/src
>>> ../tools/config_detran
```

