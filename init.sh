#!/bin/bash
file=$1
if [[ -f $file ]]; then
    echo "no init, delete original file and run shell again to init"
    rm -i $file
    exit
else
	echo "#include \"common.h\"" >> $file
	echo "" >>$file
	echo "int main() {" >> $file
	echo "" >>$file
	echo -e "\tSolution s;" >> $file
	echo "" >>$file
	echo -e "\treturn 0;" >> $file
	echo "}" >> $file
	ls -lrt --color=auto $file
	vim $file
fi


