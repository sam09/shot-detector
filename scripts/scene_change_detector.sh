#!/bin/bash
my_fpath=$(readlink -f "$0")
my_dpath=$(dirname "$my_fpath")

print_help_and_exit() {
	echo "Usage instructions";
	echo "scene_change_detector.sh <input_video> <output_file> [--use_cuda]";
	exit 1;
}

input=$1
output=$2
if [[ -z "$input" ]]; then
	echo "No input file found"
	print_help_and_exit
elif [[ -z "$output" ]]; then
	echo "No output file found"
	print_help_and_exit
elif [[ -z "$3" ]]; then
	use_cuda=0
elif [[ "$3" = "--use-cuda" ]]; then
	use_cuda=1
else
	echo "$3 Invalid option"
	print_help_and_exit
fi

dur=$(mediainfo --inform="General;%Duration%" "$input")

$my_dpath/scene_detect $input $output $dur $use_cuda
