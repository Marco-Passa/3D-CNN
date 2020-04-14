3D-CNN
Denosing, segmentation and classification of brain MRI with deep learnig technique
The roject contains:

-Pre procesess: data augmentation and cropping

-Train: CNN for denosing, segmentation, classification and transfer learning for classification using denoising data

-Test: API to test the models

Installation

Follow the instruction of 3D-Caffe to install Caffe library. Rememebr to use git checkout 3D-Caffe to switch the correct branch and use make matcaffe to build Matlab interface.

Install Matlab toolbox NIfTI_tools in order to read nii data format in Matlab.

Prepare the hdf5 data to train the model.
