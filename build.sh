#!/bin/bash

make
env -C cli/ cargo build --release
mv cli/target/release/basspatch .