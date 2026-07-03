#!/bin/bash
Name=(10   12   16   20   25   32   49   50   63   80  \
      100  120  160  200  250  320  490  500  630  800 \
      1000 1200 1600 2000 2500 3200 4900 5000 6300 8000 \
      10000)

for ((i=0;i<${#Name[@]};i++))
do

    Energy=$(awk -v i="$i" 'BEGIN {printf "%.2f", 10^(1+0.1*i)}')
    sed \
        -e "s/ENERGY/${Energy}/g" \
        -e "s/NAME/${Name[$i]}/g" \
        /Users/xiongzheng/software/Hadr03/Macro2/Proton_template.mac \
        > /Users/xiongzheng/software/Hadr03/Macro2/He4_${Name[$i]}GeV.mac
done