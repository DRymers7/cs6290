git status
git add .
git commit -m "original state for compconf4
git commit -m "original state for compconf4"
git checkout -b "original-state-for-compconf4"
git switch project-1
clear
git status
clear
cd ~/sesc/apps/Splash2/raytrace/
make
~/sesc/sesc.opt -f HyA -c ~/sesc/confs/cmp4-noc.conf -ort.out -ert.err raytrace.mipseb -m128 Input/reduced.env
cd ~/
ls
~/sesc/sesc.opt -f HyA -c ~/sesc/confs/cmp4-noc.conf -ort.out -ert.err raytrace.mipseb -m128 Input/reduced.env
cd ~/sesc/apps/Splash2/raytrace
~/sesc/sesc.opt -f HyA -c ~/sesc/confs/cmp4-noc.conf -ort.out -ert.err raytrace.mipseb -m128 Input/reduced.env
cd ~/sesc
make
clear
git status
cd ..
git add .
git status
git commit -m "compiled sesc"
git status
clear
cd ~/sesc/apps/Splash2/raytrace
ls
clear
~/sesc/sesc.opt -f HyA -c ~/sesc/confs/cmp4-noc.conf -ort.out -ert.err raytrace.mipseb -m128 Input/reduced.env
~/sesc/scripts/report.pl sesc_raytrace.mipseb.HyA 
clear
~/sesc/sesc.opt -f OrA -c ~/sesc/confs/cmp4-noc.conf -ort.out -ert.err raytrace.mipseb -m128 Input/reduced.env
git status
git status
git add .
git commit -m "ORA config done"
git status
git push
