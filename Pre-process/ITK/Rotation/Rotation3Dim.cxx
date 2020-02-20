% Rotate the MRI
% --------------------------------------------------------
% Copyright (c) 2020, Marco Passa
% --------------------------------------------------------
/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
//  Software Guide : BeginCommandLineArgs
//    INPUTS:  {BrainProtonDensitySlice.png}
//    OUTPUTS: {ResampleImageFilterOutput10.png}
//    ARGUMENTS:    -15
//  Software Guide : EndCommandLineArgs
//  Software Guide : BeginLatex
//
//  The following example illustrates how to rotate an image around its
//  center.  In this particular case an \doxygen{AffineTransform} is used to
//  map the input space into the output space.
//
//  \index{itk::AffineTransform!resampling}
//
//  Software Guide : EndLatex
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkResampleImageFilter.h"
#include "itkEuler3DTransform.h"
#include "itkScaleTransform.h"
#include "itkCompositeTransform.h"
#include "itkCompositeTransformIOHelper.h"

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <string>
#include <random>
#include <array>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

//  Software Guide : BeginLatex
//
//  The header of the affine transform is included below.
//
//  Software Guide : EndLatex
// Software Guide : BeginCodeSnippet
#include "itkAffineTransform.h"
// Software Guide : EndCodeSnippet


int main (){
  typedef std::chrono::high_resolution_clock myclock;
  myclock::time_point beginning = myclock::now();

  char Text[20000];
  char FileName[200][40];
  char FileNameInput[200];
  char FileNameOutput[200];
  char Input[200];
  char Output[200];
  int i = 0;
  int k = 0;
  int j = 0;
  int n = 0;
  int x = 0;
  unsigned seed;
  
  fstream myfile;
  myfile.open("listClassification.txt");

  while(i < 20000){
    myfile >> Text[i];
    i++;
  }

  cout << Text << endl;

  i = 0;

  while(i < 20000){
    if(Text[i] == '.'){
      cout << FileName[n] << endl;
      n++;
      k = 0;
      i = i + 4;
    }
    FileName[n][k] = Text[i];
    i++;
    k++;
  }
  
  while(j < 162){
   
   myclock::duration d = myclock::now() - beginning;
   if(x == 0){
   seed = d.count();
   x++;}
   else if (x==1){x = 0;} 
  strcpy (FileNameInput, "/mnt/tempo/Cases/Case3/ML_classification/HC_Neg/Crop/");
  strcat (FileNameInput, FileName[j]);
  strcat (FileNameInput, ".nii");
  cout << FileNameInput << endl;

  strcpy (FileNameOutput, "/mnt/tempo/Cases/Case3/ML_classification/HC_Neg/Crop/Rotated/");
  strcat (FileNameOutput, FileName[j]);
  strcat (FileNameOutput, "_Rotated3");
  strcat (FileNameOutput, ".nii");
  cout << FileNameOutput << endl;

  memcpy(Input, FileNameInput, 200);
  memcpy(Output, FileNameOutput, 200);

  const     unsigned int   Dimension = 3;
  typedef   double  InputPixelType;
  typedef   double  OutputPixelType;
  typedef itk::Image< InputPixelType,  Dimension >   InputImageType;
  typedef itk::Image< OutputPixelType, Dimension >   OutputImageType;
  typedef itk::ImageFileReader< InputImageType  >  ReaderType;
  typedef itk::ImageFileWriter< OutputImageType >  WriterType;
  ReaderType::Pointer reader = ReaderType::New();
  WriterType::Pointer writer = WriterType::New();

  reader->SetFileName( Input );
  writer->SetFileName( Output );
  //const double angleInDegrees = atof( argv[3] );
typedef itk::ResampleImageFilter<
                  InputImageType, OutputImageType >  FilterType;
  FilterType::Pointer filter = FilterType::New();
  //  Software Guide : BeginLatex
  //
  //  The transform type is instantiated using the coordinate representation
  //  type and the space dimension. Then a transform object is constructed
  //  with the New() method and passed to a \doxygen{SmartPointer}.
  //
  //  \index{itk::AffineTransform!instantiation}
  //  \index{itk::AffineTransform!New()}
  //  \index{itk::AffineTransform!Pointer}
  //
  //  Software Guide : EndLatex
  // Software Guide : BeginCodeSnippet
  using TransformType = itk::Euler3DTransform< double >;
  TransformType::Pointer transform = TransformType::New();
  // Random angles
  default_random_engine generator(seed);
  
  cout << generator << endl;

  normal_distribution<double> dist_x(0.0,0.1);
  normal_distribution<double> dist_yz(0.0,0.05);
  //
  TransformType::ParametersType parameters( 6 );
  parameters[0] = dist_x(generator);  // rotation
  parameters[1] = dist_yz(generator); // rotation
  parameters[2] = dist_yz(generator); // rotation

  cout << parameters[0] << endl;
  cout << parameters[1] << endl;

  parameters[3] = 0.0; // translation
  parameters[4] = 0.0; // translation
  parameters[5] = 0.0; // translation
  transform->SetParameters( parameters );
  TransformType::FixedParametersType fixedParameters( 3 );
  fixedParameters[0] = -11.64; // center of rotation
  fixedParameters[1] =  -4.15; // center of rotation
  fixedParameters[2] =  -6.01; // center of rotation
  transform->SetFixedParameters( fixedParameters );

  // Software Guide : EndCodeSnippet
  typedef itk::LinearInterpolateImageFunction<
                       InputImageType, double >  InterpolatorType;
  InterpolatorType::Pointer interpolator = InterpolatorType::New();
  filter->SetInterpolator( interpolator );
  filter->SetDefaultPixelValue( 100 );
  //  Software Guide : BeginLatex
  //
  //  The parameters of the output image are taken from the input image.
  //
  //  Software Guide : EndLatex
  // Software Guide : BeginCodeSnippet
  reader->Update();
  const InputImageType * inputImage = reader->GetOutput();
  const InputImageType::SpacingType & spacing = inputImage->GetSpacing();
  const InputImageType::PointType   & origin  = inputImage->GetOrigin();
  InputImageType::SizeType size =
      inputImage->GetLargestPossibleRegion().GetSize();
  filter->SetOutputOrigin( origin );
  filter->SetOutputSpacing( spacing );
  filter->SetOutputDirection( inputImage->GetDirection() );
  filter->SetSize( size );
  // Software Guide : EndCodeSnippet
  filter->SetInput( reader->GetOutput() );
  writer->SetInput( filter->GetOutput() );
  //  Software Guide : BeginLatex
  //
  //  Rotations are performed around the origin of physical coordinates---not
  //  the image origin nor the image center. Hence, the process of
  //  positioning the output image frame as it is shown in Figure
  //  \ref{fig:ResampleImageFilterOutput10} requires three steps.  First, the
  //  image origin must be moved to the origin of the coordinate system, this
  //  is done by applying a translation equal to the negative values of the
  //  image origin.
  //
  // \begin{figure}
  // \center
  // \includegraphics[width=0.44\textwidth]{BrainProtonDensitySliceBorder20}
  // \includegraphics[width=0.44\textwidth]{ResampleImageFilterOutput10}
  // \itkcaption[Effect of the Resample filter rotating an image]{Effect of the
  // resample filter rotating an image.}
  // \label{fig:ResampleImageFilterOutput10}
  // \end{figure}
  //
  //
  //  \index{itk::AffineTransform!Translate()}
  //
  //  Software Guide : EndLatex
  // Software Guide : BeginCodeSnippet

  filter->SetTransform( transform );


  // Software Guide : EndCodeSnippet
  //  Software Guide : BeginLatex
  //
  //  The third and final step requires translating the image origin back to
  //  its previous location. This is be done by applying a translation equal
  //  to the origin values.
  //
  //  \index{itk::AffineTransform!Translate()}
  //
  //  Software Guide : EndLatex
  // Software Guide : BeginCodeSnippet
  /*TransformType::OutputVectorType translation2;
  translation2[0] =   imageCenterX;
  translation2[1] =   imageCenterY;
  transform->Translate( translation2, false );
  filter->SetTransform( transform );*/
  // Software Guide : EndCodeSnippet
  //  Software Guide : BeginLatex
  //
  //  The output of the resampling filter is connected to a writer and the
  //  execution of the pipeline is triggered by a writer update.
  //
  //  Software Guide : EndLatex
  // Software Guide : BeginCodeSnippet
  try
    {
    writer->Update();
    }
  catch( itk::ExceptionObject & excep )
    {
    std::cerr << "Exception caught !" << std::endl;
    std::cerr << excep << std::endl;
    }
  j++;}
  // Software Guide : EndCodeSnippet
  return EXIT_SUCCESS;
}

