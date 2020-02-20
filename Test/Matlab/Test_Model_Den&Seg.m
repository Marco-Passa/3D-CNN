%% Script to test the denoising and segmentation model
%% --------------------------------------------------------
%% Copyright (c) 2020, Marco Passa
%% --------------------------------------------------------

close all; clear all; clc;

%% add matcaffe path
addpath(genpath('../3D-Caffe/matlab/'));

%% set model path 
addpath('./util');
model_folder = '../DNN/'
model   = [model_folder, 'deployD04.prototxt'];
weights = [model_folder, 'snapshot/HVSMR_D04_002_iter_100000.caffemodel'];

%% set save path
root_folder = '/mnt/tempo/Cases/Case1/FLAIR/Cropped/';

%% prediction
caffe.reset_all;     %% net_.reset(new Net<float>(model_file, TEST));
caffe.set_mode_cpu();     %% Caffe::set_mode(Caffe::GPU);NON VA CON GPU;
caffe.set_device(0);
net = caffe.Net(model, weights, 'test');     %% net_.reset(new Net<float>(model_file, TEST));
                                             %% net_->CopyTrainedLayersFrom(trained_file);

vol_path = [root_folder, 'FLAIR_11287_2016-05-20_corrected.nii'];
data = load_untouch_nii(vol_path);
%%img = pre_process_isotropic(data,[],0)

   
res = net.forward({data.img});    %% net_->Forward();

%% save result
save_nii(make_nii(res{1,1}), '../BrainData/Test001.nii');

caffe.reset_all;
