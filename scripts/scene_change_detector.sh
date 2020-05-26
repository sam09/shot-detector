#!/bin/bash
my_fpath=$(readlink -f "$0")
my_dpath=$(dirname "$my_fpath")

#echo "my directory: $my_dpath"
input=$1
output=$2
dur=$(mediainfo --inform="General;%Duration%" "$input")

$my_dpath/scene_detect $input $output $dur $use_cuda
