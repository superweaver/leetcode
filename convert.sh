#!/bin/bash
# note: The first two method in this shell can only handle one line of input, change [ to { and [ to }
# method 3 is correct
# 1) use $@ to get all input parameters of shell, redirect it to temp and use sed
# how to use it : ./convert.sh "[1,2,3]"
#echo "$@" > temp && sed "s/\[/\{/g; s/\]/\}/g" temp
# echo "$@" | sed "s/\[/\{/g; s/\]/\}/g"
# 2) use xclip utility
# copy content into clipboard, then run convert.sh
# echo $(xclip -o) | sed "s/\[/\{/g; s/\]/\}/g"

# !!! this works
# 3) this can handle multiple lines and it uses content from system clipboard instead of termianl clipboard
echo $(xclip -selection clipboard -o) | sed "s/\[/\{/g; s/\]/\}/g"
