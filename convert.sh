#!/bin/bash
# 1) use $@ to get all input parameters of shell, redirect it to temp and use sed
# how to use it : ./convert.sh "[1,2,3]"
#echo "$@" > temp && sed "s/\[/\{/g; s/\]/\}/g" temp
# echo "$@" | sed "s/\[/\{/g; s/\]/\}/g"
# 2) use xclip utility
# copy content into clipboard, then run convert.sh
echo $(xclip -o) | sed "s/\[/\{/g; s/\]/\}/g" | xclip -o
