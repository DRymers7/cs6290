git status
git stash
git status
git switch master
git branch
git branch -a
git fetch
git status
git push
git status
git switch master
clear
ls
git status
git branch
git status
git add .
git status
git commit -m "gitignore update"
git push
git checkout -b "project-2"
git status
clear
cd sesc/
make
git status
git add . && git commit -m "initial build"
clear
cd ~/sesc/apps/Splash2/fmm
make
clear
~/sesc/sesc.opt -f Default -c ~/sesc/confs/cmp4-noc.conf -iInput/input.256 -ofmm.out -efmm.err fmm.mipseb -p 1
clear
~/sesc/sesc.opt -f SmallL1 -c ~/sesc/confs/cmp4-noc.conf -iInput/input.256 -ofmm.out -efmm.err fmm.mipseb -p 1
~/sesc/scripts/report.pl sesc_fmm.mipseb.SmallL1
~/sesc/scripts/report.pl sesc_fmm.mipseb.Default
clear
~/sesc/sesc.opt -f DMapL1 -c ~/sesc/confs/cmp4-noc.conf -iInput/input.256 -ofmm.out -efmm.err fmm.mipseb -p 1
~/sesc/scripts/report.pl sesc_fmm.mipseb.DMapL1
~/sesc/scripts/report.pl sesc_fmm.mipseb.Default
clear
~/sesc/sesc.opt -f SlowL1 -c ~/sesc/confs/cmp4-noc.conf -iInput/input.256 -ofmm.out -efmm.err fmm.mipseb -p 1
~/sesc/sesc.opt -f SlowerL1 -c ~/sesc/confs/cmp4-noc.conf -iInput/input.256 -ofmm.out -efmm.err fmm.mipseb -p 1
~/sesc/scripts/report.pl sesc_fmm.mipseb.SlowL1
~/sesc/scripts/report.pl sesc_fmm.mipseb.SlowerL1
~/sesc/scripts/report.pl sesc_fmm.mipseb.Default
git status
git add .
git commit -m "done with part 1"
git statuas
git status
cd ../..
cd ..
git status
git add .
git status
git add .
git status
git commit -m "done with part one reverted state of cmp4"
git push
git push --set-upstream origin project-2
cd sesc/
ls
make
cd sesc/
ls
cd scripts/
ls
report.pl /home/cs6290/sesc/apps/Splash2/lu/sesc_lu.mipseb.n256.rpt
sh report.pl /home/cs6290/sesc/apps/Splash2/lu/sesc_lu.mipseb.n256.rpt
cd sesc/
make
~/sesc/sesc.opt -f Baseline_LRU -c ~/sesc/confs/cmp4-noc.conf -iInput/input.256 -ofmm.out -efmm.err fmm.mipseb -p 1
~/sesc/sesc.opt -f BaselineLRU -c ~/sesc/confs/cmp4-noc.conf -iInput/input.256 -ofmm.out -efmm.err fmm.mipseb -p 1
cd ~/sesc/apps/Splash2/fmm
~/sesc/sesc.opt -f BaselineLRU -c ~/sesc/confs/cmp4-noc.conf -iInput/input.256 -ofmm.out -efmm.err fmm.mipseb -p 1
~/sesc/scripts/report.pl sesc_fmm.mipseb.BaselineLRU
~/sesc/sesc.opt -f InitImplLRU -c ~/sesc/confs/cmp4-noc.conf -iInput/input.256 -ofmm.out -efmm.err fmm.mipseb -p 1
~/sesc/scripts/report.pl sesc_fmm.mipseb.BaselineLRU
~/sesc/scripts/report.pl sesc_fmm.mipseb.InitImplLRU
cd sesc/
make
clear
make
git status
clear
make
git status
git add .
git commit -m "initial implementation of NXLRU"
clear
cd sesc/
cd apps/
ls
cd Splash2/
ls
cd lu/
ls
make
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_fmm.mipseb.n256.rpt
ls
pwd
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
make
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
make
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
git status
clear
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
clear
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
git status
git add .
git commit -m "added comments"
git status
git add .
git commit -m "working impl"
git status
git add . && git commit -m "cleaned up. moving to pt 3"
git push
cd sesc/
make
cd sesc/
cd apps/
cd Splash2/
ls
cd lu/
ls
clear
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
clear
cd sesc/
clear
cd sesc/
kls
ks
ls
cd apps/
ls
cd Splash2/
ls
cd lu/
ls
clear
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
~/sesc/scripts/report.pl sesc_lu.mipseb.n256.rpt
cd ..
ls
cd fmm
ls
clear
~/sesc/scripts/report.pl sesc_fmm.mipseb.BaselineLRU
clear
~/sesc/sesc.opt -f L1NXLRU -c ~/sesc/confs/cmp4-noc.conf -iInput/input.256 -ofmm.out -efmm.err fmm.mipseb -p 1
~/sesc/scripts/report.pl sesc_fmm.mipseb.L1NXLRU 
~/sesc/sesc.opt -f L1LRU_base2 -c ~/sesc/confs/cmp4-noc.conf -iInput/input.256 -ofmm.out -efmm.err fmm.mipseb -p 1
~/sesc/scripts/report.pl sesc_fmm.mipseb.L1LRU_base2 
~/sesc/scripts/report.pl sesc_fmm.mipseb.L1NXLRU 
cd sesc/
clear
git status
make
git status
git restore src/libsuc/CacheCore.cpp
make
git status
git restore sesc/src/libsuc/CacheCore.h
git status
git add .
git commit -m "done with part 2 and moving to part 3"
git push
git status
git add .
git commit -m "working initial implementation"
git status
git add .
git commit -m "results matching for 32kb 4w assc LRU lu 256"
git status
git push
git status
git add . && git commit -m "beginning cleanup and final tests"
gi tpush
git push
cd sesc/
ls
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
cd sesc/
cd apps/
ls
cd SPlasq
cd Splash2/q
cd Splash2/
ls
cd lu/
ls
clear
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
clear
~/sesc/sesc.opt -fn256.rpt -c ~/sesc/confs/cmp4-noc.conf -olu.out -elu.err lu.mipseb -n256 -p1
