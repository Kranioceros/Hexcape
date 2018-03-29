#!/bin/sh

BUILD_DIR=$1

cp assets -r ${BUILD_DIR}
cp fonts -r ${BUILD_DIR}
cp openal32.dll ${BUILD_DIR}
cp README ${BUILD_DIR}
cp sounds -r ${BUILD_DIR}
cp *.exe ${BUILD_DIR}
cp *.bin ${BUILD_DIR}

rm ${BUILD_DIR}/assets/*.xcf
rm ${BUILD_DIR}/assets/*.ase
rm ${BUILD_DIR}/assets/*.jpg
rm ${BUILD_DIR}/assets/escotillas/*
rmdir ${BUILD_DIR}/assets/escotillas
