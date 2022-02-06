#!/bin/bash

make
LD_PRELOAD=./basspatch.so $1