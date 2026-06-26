#!/bin/bash
exe=/Users/xiongzheng/software/Hadr03/build/Hadr03
Tag=Proton

<<<<<<< Updated upstream
# ${exe} /Users/xiongzheng/software/Hadr03/Macro/${Tag}_10GeV.mac
# ${exe} /Users/xiongzheng/software/Hadr03/Macro/${Tag}_100GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro/${Tag}_1TeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro/${Tag}_10TeV.mac

Tag=Deuteron
${exe} /Users/xiongzheng/software/Hadr03/Macro/${Tag}_10GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro/${Tag}_100GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro/${Tag}_1TeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro/${Tag}_10TeV.mac
=======
${exe} /Users/xiongzheng/software/Hadr03/Macro/${Tag}_20GeV.mac
${exe} /Users/xiongzheng/software/Hadr03/Macro/${Tag}_50GeV.mac
# ${exe} /Users/xiongzheng/software/Hadr03/Macro/${Tag}_1TeV.mac
# ${exe} /Users/xiongzheng/software/Hadr03/Macro/${Tag}_10TeV.mac
>>>>>>> Stashed changes

git add -A
git commit -m "Auto update $(date '+%F %T')" || true
git push