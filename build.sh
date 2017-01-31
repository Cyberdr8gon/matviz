#!/bin/bash
# sanity check the build directories exist
mkdir -p ~/workspace/matrixVisualizer/build/debug
mkdir -p ~/workspace/matrixVisualizer/build/release
# check if there were command line arguments
if [ -z "$1" ]
then
  # no arguments, execute default behavior, build debug
  pushd ~/workspace/matrixVisualizer/build/debug
  cmake ../.. -DCMAKE_BUILD_TYPE=Debug
  make
  popd
else
  # parse arguments
  if [ "$1" == "a" ]
  # if all build
  then
  echo "building debug and release"

  pushd ~/workspace/matrixVisualizer/build/debug
  cmake ../.. -DCMAKE_BUILD_TYPE=Debug
  make
  popd

  pushd ~/workspace/matrixVisualizer/build/release
  cmake ../.. -DCMAKE_BUILD_TYPE=Release
  make
  popd

  elif [ "$1" == "r" ] 
  # build release only
  then
  echo "building release"

  pushd ~/workspace/matrixVisualizer/build/release
  cmake ../.. -DCMAKE_BUILD_TYPE=Release
  make
  popd

  else
  echo "unknown command\n building debug and release"
  pushd ~/workspace/matrixVisualizer/build/debug
  cmake ../.. -DCMAKE_BUILD_TYPE=Debug
  make
  popd
  fi
fi
