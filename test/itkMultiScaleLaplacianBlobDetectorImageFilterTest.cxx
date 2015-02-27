#include "itkMultiScaleLaplacianBlobDetectorImageFilter.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkGaussianImageSource.h"
#include "itkImageFileWriter.h"

namespace
{

template <unsigned int IDimension>
bool MaximaGaussianBlobTest( const double sigma )
{
  const unsigned int imageSize = 64;

  typedef itk::Image< float, IDimension > ImageType;

  typename ImageType::SizeType size;
  size.Fill( imageSize );

  typename ImageType::SpacingType spacing;
  spacing.Fill( 1.0 );



  typedef itk::GaussianImageSource<ImageType> GaussianSourceType;
  typename GaussianSourceType::Pointer gaussianSource = GaussianSourceType::New();
  gaussianSource->SetSize( size );
  gaussianSource->SetSpacing( spacing );
  gaussianSource->SetMean( itk::FixedArray< double, IDimension>( imageSize/2 ) );
  gaussianSource->SetSigma( itk::FixedArray< double, IDimension>( sigma ) );
  gaussianSource->SetNormalized( false );
  gaussianSource->SetScale( -1.0 ); // dark blob

  typedef itk::MultiScaleLaplacianBlobDetectorImageFilter< ImageType > BlobFilterType;
  typename BlobFilterType::Pointer blobFilter = BlobFilterType::New();
  blobFilter->SetStartT( vcl_pow(sigma, 2.0/4.0) );
  blobFilter->SetEndT( vcl_pow(sigma, 2.0*4.0) );
  blobFilter->SetStepsPerOctave( 10 );
  blobFilter->SetNumberOfBlobs( 5 );
  blobFilter->SetInput( gaussianSource->GetOutput() );
  blobFilter->Update();

  typedef typename BlobFilterType::BlobsListType BlobsListType;
  BlobsListType blobs =  blobFilter->GetBlobs();
  std::cout << "Detecting blog with sigma " << sigma << std::endl;


  if ( !blobs.empty() )
//    for( typename BlobsListType::const_iterator i = blobs.begin(); i != blobs.end(); ++i)
    {
    typename BlobsListType::const_iterator i = blobs.begin();
    std::cout <<  "Value: " << (*i)->GetScaleSpaceValue() << " sigma of Laplacian detector " << (*i)->GetScaleSpaceSigma() << " sigma of detected Gaussian " << (*i)->GetSigma() << std::endl;
    }
  std::cout << std::endl;


  spacing.Fill( 2.0 );

  gaussianSource->SetSpacing( spacing );

  blobFilter->Update();


  blobs =  blobFilter->GetBlobs();

  std::cout << "Detecting blog with sigma " << sigma << " and pixel spacing " << 2.0 << std::endl;

  if ( !blobs.empty() )
//    for( typename BlobsListType::const_iterator i = blobs.begin(); i != blobs.end(); ++i)
    {
    typename BlobsListType::const_iterator i = blobs.begin();
    std::cout <<  "Value: " << (*i)->GetScaleSpaceValue() << " sigma of Laplacian detector " << (*i)->GetScaleSpaceSigma() << " sigma of detected Gaussian " << (*i)->GetSigma() << std::endl;
    }

  std::cout << std::endl;

  return true;
}

}


int itkMultiScaleLaplacianBlobDetectorImageFilterTest( int , char *[] )
{

  MaximaGaussianBlobTest<2>( 3 );
  MaximaGaussianBlobTest<2>( 5 );
  MaximaGaussianBlobTest<2>( 10 );

  MaximaGaussianBlobTest<3>( 3 );
  MaximaGaussianBlobTest<3>( 5 );
  MaximaGaussianBlobTest<3>( 10 );


  return 0;
}
