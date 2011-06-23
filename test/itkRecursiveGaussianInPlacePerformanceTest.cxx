
#include "itkRecursiveGaussianImageFilter.h"

#include "itkGaussianImageSource.h"

#include "itkTimeProbe.h"

int itkRecursiveGaussianInPlacePerformanceTest( int argc, char *argv[] )
{
  typedef float PixelType;
  const unsigned int Dimension = 4;
  typedef itk::Image< PixelType, Dimension > ImageType;


  const unsigned int imageSize = 256;

  ImageType::SizeType size;
  size.Fill( imageSize );


  typedef itk::GaussianImageSource<ImageType> GaussianSourceType;
  GaussianSourceType::Pointer gaussianSource = GaussianSourceType::New();
  gaussianSource->SetSize( size );
  gaussianSource->SetMean( itk::FixedArray< double, Dimension>( imageSize/2 ) );
  gaussianSource->SetSigma( itk::FixedArray< double, Dimension>( imageSize/6 ) );
  gaussianSource->SetNormalized( false );
  gaussianSource->SetScale( 1.0 );

  for (unsigned int d = 0; d < Dimension; ++d )
    {
    itk::TimeProbe t1;
    itk::TimeProbe t2;
    {
    gaussianSource->Update();

    typedef itk::RecursiveGaussianImageFilter< ImageType, ImageType> GaussianFilterType;
    GaussianFilterType::Pointer filter = GaussianFilterType::New();
    filter->SetInput( gaussianSource->GetOutput() );
    filter->SetOrder( GaussianFilterType::ZeroOrder );
    filter->SetSigma( 5.0 ); // this filter run-time performance in
    filter->SetDirection( d );
    // independed of scale
    filter->InPlaceOn();

    t1.Start();
    filter->Update();
    t1.Stop();

    std::cout << "InPlace: " << t1.GetTotal() << t1.GetUnit() << std::endl;
    }

    {
    gaussianSource->Update();

    typedef itk::RecursiveGaussianImageFilter< ImageType, ImageType> GaussianFilterType;
    GaussianFilterType::Pointer filter = GaussianFilterType::New();
    filter->SetInput( gaussianSource->GetOutput() );
    filter->SetOrder( GaussianFilterType::ZeroOrder );
    filter->SetDirection( d );
    filter->SetSigma( 5.0 ); // this filter run-time performance in
    // independed of scale
//  filter->InPlaceOn();

    t2.Start();
    filter->Update();
    t2.Stop();

    std::cout << "Copy: " << t2.GetTotal() << t2.GetUnit() << std::endl;
    }

    std::cout << "Speed Up with InPlace: " << t2.GetTotal()/ (double) t1.GetTotal() << std::endl;
    }

  return EXIT_FAILURE;
}
