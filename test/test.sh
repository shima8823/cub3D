#!/bin/bash

RED="\033[31m"
GREEN="\033[32m"
WHITE="\033[37m"

SHELL_DIR="`dirname $0`"
CUBFILE_DIR="assets/cubfiles/invalid"
CUBEXEC_DIR="."

# もしshellが"test/"で呼ばれているならば
if [ "." == "$SHELL_DIR" ]; then
	CUBFILE_DIR="../assets/cubfiles/invalid"
	CUBEXEC_DIR=".."
fi

function test_file_parse()
{
	$CUBEXEC_DIR/cub3D $1 &> /dev/null
	if [ $? -eq "1" ]; then
		printf "$GREEN[$1]\n"
	else
		printf "$RED[$1]\n"
	fi
}

for file in $(ls $CUBFILE_DIR/*); do
	test_file_parse $file
done