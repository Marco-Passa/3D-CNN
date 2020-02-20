%% Script to test the classification model
%% --------------------------------------------------------
%% Copyright (c) 2020, Marco Passa
%% --------------------------------------------------------

close all; clear all; clc;

for n = 1:1

N = (n*2000);
N = num2str(N);

for i = 1:14

%% add matcaffe path
addpath(genpath('../../../3D-Caffe/matlab/'));

%% set model path 
addpath('./util');
model_folder = '../DNN/';
model   = [model_folder, 'deploy.prototxt'];
weights = [model_folder, 'snapshot/HVSMR_iter_', N, '.caffemodel'];

%% set save path
root_folder = '/mnt/tempo/Cases/Case3/ML_classification/Ad_Bio/Crop/';

%% prediction
caffe.reset_all;     %% net_.reset(new Net<float>(model_file, TEST));
caffe.set_mode_cpu();     %% Caffe::set_mode(Caffe::GPU);NON VA CON GPU;
caffe.set_device(0);
net = caffe.Net(model, weights, 'test');     %% net_.reset(new Net<float>(model_file, TEST));
                                             %% net_->CopyTrainedLayersFrom(trained_file);

lista = load('testlist_Ad_Bio.txt');

nome_file = lista(i);

nome = num2str(nome_file);

vol_path = [root_folder, nome , '.nii'];
data = load_untouch_nii(vol_path);
   
res(i) = net.forward({data.img});    %% net_->Forward();

caffe.reset_all;

end

Result{n} = 0;

for i = 1:14

a = res{i};

Result{n} = Result{n} + a(2);

end

end

for n = 1:1

Result{n} = (Result{n})/14

end

R = cell2mat(Result);

plot(R)
