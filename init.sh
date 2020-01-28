#!/bin/bash
if [ -f $1 ]
then
    rm -i $1
fi
echo "#include \"common.h\"" >> $1
echo "" >>$1
echo "int main() {" >> $1
echo "" >>$1
echo -e "\tSolution s;" >> $1
echo -e "\treturn 0;" >> $1
echo "}" >> $1
ls -lrt
#vi $1
