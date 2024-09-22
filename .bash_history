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
cd sesc/
ls
clear
git status
make
clear
git status
git add . && git commit -m "reverting to orig state"
make clean
make
clear
git status
make
clear
make
git status
git add . && git commit -m "trying new implementation"
clear
make
clear
make
mkw
clearw
clear
make
clear
make
clear
make
clear
make
clear
make
clear
make clean
make
clear
make
clear
make
clear
make
clear
make
clear
make
clear
make
clear
make
clear
make
clear
make
clear
make
clear
git status
git add .
git commit -m "working on python script to count new run"
git push
git status
git add . && git commit -m "getting rid of large file"
git push
git status
git checkout -b "project-1-rev"
git status
git push
git push --set-upstream origin project-1-rev
pip install git-filter-repo
sudo apt install pip
clear
git filter-branch --force --index-filter \'git rm --cached --ignore-unmatch sesc~/sesc/apps/Splash2/lu/branch_log.txt' \--prune-empty --tag-name-filter cat -- --all
git filter-branch --force --index-filter
clear
ls
git status
git prune
git rm --cached --ignore-unmatch path/to/largefile
git rm --cached --ignore-unmatch ~/sesc/apps/Splash2/lu/branch_log.txt
--prune-empty --tag-name-filter cat -- --all
git --prune-empty --tag-name-filter cat -- --all
clear
ls
git push
git push --set-upstream origin project-1-rev
ls
ls -a
cd ..
ls -a
rm -rf .git/refs/original
git reflog expire --expire=now --all
git gc --prune=now --aggressive
git push origin --force --all
ls -a
rm -rf .git
git status
git init
git status
git remote add origin git@github.com:DRymers7/cs6290.git
git checkout -b "project-1-rev"
git status
git add .
git commit -m "init"
git push
git push --set-upstream origin project-1-rev
cd sesc/
ls
cd apps/
ls
cd Splash2/
ls
cd lu/
ls
clear
amke
make
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
clear
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
clear
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
ls
clear
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
cleawr
clear
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
clear
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
clear
ls
cd sesc/
ls
cd scripts/
ls
clear
ls
cd ..
cd apps/
ls
cd scripts/
ls
clear
ls
python count_statics.py 
clear
python count_statics.py 
python --version
cvlear
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
cd sesc/
make
clear
make
cd ..
python -m venv venv
cd sesc/
clear
cd ..
git status
git add .
git status
git commit -m "working benchmark counts and accuracy"
clear
git status
git add .
git commit -m "code cleanup before we test other things"
git status
git add .
git commit -m "prepping to run nt sim
git commit -m "prepping to run nt sim"
git push
cd sesc/apps/
ls
cd scripts/
ls
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clerw
clear
clerw
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
git status
cd sesc/apps/
cd spla
cd Splash2/
ls
cd lu/
ls
make
clear
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
cd sesc/
cd apps/
cd Splash2/
ls
cd lu/
ls
clear
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt 
clear
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
clear
ls
cat branch_log.txt | grep "Ohter"
cat branch_log.txt | grep "Other"
cat branch_log.txt | grep Other
clear
grep -v
grep --help
clear
cd sesc/
cd apps/
cd scripts/
ls
clear
python count_statics.py 
~/sesc/scripts/report.pl sesc_lu.mipseb.256.rpt
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
xlw
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
git status
git diff sesc/src/libcore/BPred.cpp
clear
git status
git restore sesc/src/libcore/BPred.cpp
git status
git restore sesc/src/libcore/BPred.h
git status
cd sesc/
clear
make
git status
cd ..
git status
git add . && git commit -m "working on getting hybrid accuracy, then I am done"
git push
clear
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
clear
make
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
clear
make
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
clear
make
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
clear
make
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
clear
clear
ls
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
clear
python count_statics.py 
cd sesc/
cd apps/
ls
cd Splash2/
ls
cd raytrace/
ls
~/sesc/sesc.opt -f NTH -c ~/sesc/confs/cmp4-noc.conf -ort.out -ert.err raytrace.mipseb -m128 Input/reduced.env
