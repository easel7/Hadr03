#!/bin/bash
exe=/Users/xiongzheng/software/Hadr03/build/Hadr03
Tag=Proton


${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_12000GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_16000GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_20000GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_25000GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_32000GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_49000GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_50000GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_63000GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_80000GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_10000GeV.mac

# ${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_24000GeV.mac
# ${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_25001GeV.mac
# ${exe} /Users/xiongzheng/software/Hadr03/Macro2/Proton_26000GeV.mac



git add -A
git commit -m "Auto update $(date '+%F %T')" || true
git push