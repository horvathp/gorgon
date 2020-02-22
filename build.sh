#!/bin/bash
mkdir -p atlgnd_dir
mkdir -p smogpgnd_dir

mkdir -p atlgnd_dir/download
mkdir -p atlgnd_dir/packets
mkdir -p atlgnd_dir/partial
mkdir -p atlgnd_dir/spectrum
mkdir -p atlgnd_dir/json

mkdir -p smogpgnd_dir/download
mkdir -p smogpgnd_dir/packets
mkdir -p smogpgnd_dir/partial
mkdir -p smogpgnd_dir/spectrum
mkdir -p smogpgnd_dir/json

cp build/smogpgnd smogpgnd_dir/
cp build/atlgnd atlgnd_dir/

