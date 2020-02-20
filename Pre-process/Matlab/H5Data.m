% Generate the hdf5 file and a file list used to train the network
% --------------------------------------------------------
% Copyright (c) 2020, Marco Passa
% --------------------------------------------------------

data_folder = '/mnt/tempo/Cases/Case3/ML_classification/HC_Neg/Crop/Rotated/';
h5_save_folder = '../HDF5_Classification';
h5_save_list = '../trainClassification_HC_Neg1.list';

addpath('./util');
fid = fopen(h5_save_list, 'w');

list = dir(data_folder);

list = struct2cell(list);

i=3;

while i < 10000
   
   A = char(list{1,i});
   B = strrep(A,'nii','h5');

   img_path = [data_folder, '/', A];

   img_nii = load_untouch_nii(img_path);
 
   h5_path    = [h5_save_folder, '/', B];
   if exist(h5_path,'file')
      delete(h5_path);
   end

   [d1, d2, d3, d4, d5] = size(img_nii.img);
   data_dims = [d1, d2, d3, d4, d5];
   output = 0;

   h5create(h5_path,'/DATA',data_dims,'Datatype','int16','Deflate',0,'ChunkSize',data_dims);
   h5create(h5_path,'/LABEL',[1],'Datatype','int16','Deflate',0,'ChunkSize',[1]);
   h5write(h5_path,'/DATA', int16(img_nii.img));
   h5write(h5_path,'/LABEL', int16(output));
   fprintf(fid,'%s\n', h5_path);
   
   i = i + 1

end
