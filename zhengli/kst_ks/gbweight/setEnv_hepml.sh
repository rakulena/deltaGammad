
lcg="LCG_96bpython3"
rel="x86_64-centos7-gcc8-opt"

source /cvmfs/sft.cern.ch/lcg/releases/${lcg}/numpy/1.16.4/${rel}/numpy-env.sh
source /cvmfs/sft.cern.ch/lcg/releases/${lcg}/theano/1.0.4/${rel}/theano-env.sh
source /cvmfs/sft.cern.ch/lcg/releases/${lcg}/scikitlearn/0.21.2/${rel}/scikitlearn-env.sh
source /cvmfs/sft.cern.ch/lcg/releases/${lcg}/root_numpy/4.8.0/${rel}/root_numpy-env.sh
source /cvmfs/sft.cern.ch/lcg/releases/${lcg}/pip/19.1.1/${rel}/pip-env.sh
source /cvmfs/sft.cern.ch/lcg/releases/${lcg}/ROOT/6.18.04/${rel}/ROOT-env.sh

# pip install --install-option="--prefix=/home/lhcb/softwares" hep_ml
PYTHONPATH="$HOME/pubsoft/lib/python3.6/site-packages:$PYTHONPATH"
#PYTHONPATH="$HOME/.local/lib/python3.8/site-packages:$PYTHONPATH"
#echo $PYTHONPATH

export PYTHONPATH=$(echo $PYTHONPATH | awk -v RS=: -v ORS=: '!($0 in a) {a[$0]; print}' |sed 'N;s/\n//g')
:<<!
!
