#!/bin/bash
# this likely must be set for your system
PROJECT_ROOT_DIR=~/workspace/matrixVisualizer
# sanity check the build directories exist
PROJECT_BIN_DIR=$PROJECT_ROOT_DIR/bin
PROJECT_RELEASE_BUILD_DIR=$PROJECT_ROOT_DIR/build/release
PROJECT_DEBUG_BUILD_DIR=$PROJECT_ROOT_DIR/build/debug
mkdir -p $PROJECT_BIN_DIR
mkdir -p $PROJECT_DEBUG_BUILD_DIR
mkdir -p $PROJECT_RELEASE_BUILD_DIR
# check if there were command line arguments
if [ -z "$1" ]
then
  # no arguments, execute default behavior, build debug
  echo "build debug"
  pushd $PROJECT_DEBUG_BUILD_DIR
  cmake $PROJECT_ROOT_DIR -DCMAKE_BUILD_TYPE=Debug
  make
  popd
else
  # parse arguments
  if [ "$1" == "a" ]
  # if all build
  then
  echo "building debug and release"

  pushd $PROJECT_DEBUG_BUILD_DIR
  cmake $PROJECT_ROOT_DIR -DCMAKE_BUILD_TYPE=Debug
  make
  popd

  pushd $PROJECT_RELEASE_BUILD_DIR
  cmake $PROJECT_ROOT_DIR -DCMAKE_BUILD_TYPE=Release
  make
  popd

  elif [ "$1" == "r" ] 
  # build release only
  then
  echo "building release"

  pushd $PROJECT_RELEASE_BUILD_DIR
  cmake $PROJECT_ROOT_DIR -DCMAKE_BUILD_TYPE=Release
  make
  popd

  else
  # handle unknown command
  echo "unknown command\n building debug"

  pushd $PROJECT_DEBUG_BUILD_DIR
  cmake $PROJECT_ROOT_DIR -DCMAKE_BUILD_TYPE=Debug
  make
  popd
  fi
fi
