#!/bin/bash
exe=/Users/xiongzheng/software/Hadr03/build/Hadr03
Tag=Proton

${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_10GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_12GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_16GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_20GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_25GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_32GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_49GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_50GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_63GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_80GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_100GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_120GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_160GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_200GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_250GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_320GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_490GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_500GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_630GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_800GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_1000GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_1200GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_1600GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_2000GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_2500GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_3200GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_4900GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_5000GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_6300GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_8000GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_10000GeV.mac

git add -A
git commit -m "Auto update $(date '+%F %T')" || true
git push