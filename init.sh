#!/bin/bash
file=$1
if [ -f $file ]
then
    rm -i $file
fi

echo "#include \"common.h\"" >> $file
echo "" >>$file
echo "int main() {" >> $file
echo "" >>$file
echo -e "\tSolution s;" >> $file
echo -e "\treturn 0;" >> $file
echo "}" >> $file
ls -lrt --color=auto
#vi $file
