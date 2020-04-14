#export LD_LIBRARY_PATH=/usr/local/cuda/lib64
LOGDIR=./training_log
CAFFE=../3D-Caffe/build/tools/caffe
SOLVER=./solver.prototxt
SNAPSHOT=./snapshot/HVSMR_TR01_001_iter_20000.solverstate
mkdir snapshot
mkdir $LOGDIR

GLOG_log_dir=$LOGDIR $CAFFE train -solver $SOLVER -gpu 0
