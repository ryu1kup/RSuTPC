#!/bin/bash

MCDIR=$(pwd)/..
source ${MCDIR}/g4env.sh
${MCDIR}/bin/RSuTPC_G4p10 \
  -s WuTPC \
  -i ${MCDIR}/data/cry_WuTPC_mu.root \
  -p ${MCDIR}/macros/preinit.mac \
  -o ${MCDIR}/output/WuTPC_G4p10.root
