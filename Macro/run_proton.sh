#!/bin/bash
exe=/Users/xiongzheng/software/Hadr03/build/Hadr03
Tag=Proton

# ${exe} /Users/xiongzheng/software/Hadr03/Macro/Proton_10GeV.mac
# ${exe} /Users/xiongzheng/software/Hadr03/Macro/Proton_20GeV.mac
# ${exe} /Users/xiongzheng/software/Hadr03/Macro/Proton_30GeV.mac
# ${exe} /Users/xiongzheng/software/Hadr03/Macro/Proton_40GeV.mac
# ${exe} /Users/xiongzheng/software/Hadr03/Macro/Proton_50GeV.mac
# ${exe} /Users/xiongzheng/software/Hadr03/Macro/Proton_60GeV.mac
# ${exe} /Users/xiongzheng/software/Hadr03/Macro/Proton_70GeV.mac
# ${exe} /Users/xiongzheng/software/Hadr03/Macro/Proton_80GeV.mac
# ${exe} /Users/xiongzheng/software/Hadr03/Macro/Proton_90GeV.mac
# ${exe} /Users/xiongzheng/software/Hadr03/Macro/Proton_100GeV.mac

${exe} /Users/xiongzheng/software/Hadr03/Macro/Deuteron_1TeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro/Deuteron_10GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro/Deuteron_10TGeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro/Deuteron_100GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro/Proton_1TeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro/Proton_10TGeV.mac

git add -A
git commit -m "Auto update $(date '+%F %T')" || true
git push