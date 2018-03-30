#!/bin/sh

INSTALL_DIR=$1/Hexcape
mkdir ${INSTALL_DIR}

cp assets -r ${INSTALL_DIR}
cp fonts -r ${INSTALL_DIR}
cp openal32.dll ${INSTALL_DIR}
cp README ${INSTALL_DIR}
cp LICENSE ${INSTALL_DIR}
cp sounds -r ${INSTALL_DIR}
cp *.exe ${INSTALL_DIR}
cp *.bin ${INSTALL_DIR}
cp *.sh ${INSTALL_DIR}

rm ${INSTALL_DIR}/assets/*.xcf
rm ${INSTALL_DIR}/assets/*.ase
rm ${INSTALL_DIR}/assets/*.jpg
rm ${INSTALL_DIR}/assets/escotillas/*
rmdir ${INSTALL_DIR}/assets/escotillas
rm ${INSTALL_DIR}/install.sh
