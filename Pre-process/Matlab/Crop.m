% Crop the MRI
% --------------------------------------------------------
% Copyright (c) 2020, Marco Passa
% --------------------------------------------------------

list = dir('/mnt/tempo/Cases/Case3/ML_classification/Pib_NEG');

list = struct2cell(list);

for i = 19:200

          read_path = ['/mnt/tempo/Cases/Case3/ML_classification//Pib_NEG/',list{1,i}];

          list2 = dir(read_path);

          list2 = struct2cell(list2);

          read_path = [read_path,'/',list2{1,3}];

          list2 = dir(read_path);

          list2 = struct2cell(list2);

          list3 = char(list2{1,3});

          list3 = strsplit(list3,'_');

          list3 = regexprep(list3{1,1},'-','X');

          read_path = [read_path,'/',list2{1,3},'/MP-LAS_',list3,'.nii']

          a = load_untouch_nii(read_path);

	    for x = 1:160

		      for y = 32:223

				for z = 32:223

					  A(x,y-31,z-31) = a.img(x,y,z);
				end

		      end

	    end

	  save_path = ['/mnt/tempo/Cases/Case3/ML_classification/Pib_NEG/Crop/',list{1,i},'.nii'];

          save_nii(make_nii(int16(A)), save_path);
            
          i

end
