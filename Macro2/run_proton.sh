#!/bin/bash
exe=/Users/xiongzheng/software/Hadr03/build/Hadr03
Tag=Proton

${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_10GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_12GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_16GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_20GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_25GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_40GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_50GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_63GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_80GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_100GeV.mac

git add -A
git commit -m "Auto update $(date '+%F %T')" || true
git push