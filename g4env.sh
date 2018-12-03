#!/bin/bash

# load geant4 environment variables
source /usr/local/root/bin/thisroot.sh
source /home/ueno/local/geant4/share/Geant4-10.3.3/geant4make/geant4make.sh
source /home/ueno/local/geant4/bin/geant4.sh
export LD_LIBRARY_PATH=/usr/local/gcc-4.9.1/lib64:$LD_LIBRARY_PATH
