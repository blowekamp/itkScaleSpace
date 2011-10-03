itk_module_test()

set(ITKScaleSpaceTests
itkMultiScaleLaplacianBlobDetectorImageFilterTest.cxx
itkRecursiveGaussianInPlacePerformanceTest.cxx
)

CreateTestDriver(ITKScaleSpace  "${ITKScaleSpace-Test_LIBRARIES}" "${ITKScaleSpaceTests}")

itk_add_test( NAME itkLaplacianBlobDetectorTest
  COMMAND ITKScaleSpaceTestDriver itkMultiScaleLaplacianBlobDetectorImageFilterTest )
itk_add_test( NAME itkRecursiveGaussianInPlacePerformanceTest
  COMMAND ITKScaleSpaceTestDriver itkRecursiveGaussianInPlacePerformanceTest )