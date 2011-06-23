itk_module_test()

set(ITK-ScaleSpaceTests
itkMultiScaleLaplacianBlobDetectorImageFilterTest.cxx
itkRecursiveGaussianInPlacePerformanceTest.cxx
)

CreateTestDriver(ITK-ScaleSpace  "${ITK-ScaleSpace-Test_LIBRARIES}" "${ITK-ScaleSpaceTests}")

itk_add_test( NAME itkLaplacianBlobDetectorTest )
itk_add_test( NAME itkRecursiveGaussianInPlacePerformanceTest )