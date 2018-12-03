#!/bin/bash

MCDIR=$(pwd)/..
source ${MCDIR}/g4env.sh
${MCDIR}/bin/RSuTPC_G4p10 \
  -s RSuTPC \
  -i ${MCDIR}/data/cry_RSuTPC_mu.root \
  -p ${MCDIR}/macros/preinit.mac \
  -o ${MCDIR}/output/RSuTPC_G4p10.root
