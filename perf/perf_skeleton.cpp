#include "opencv_ptest/include/opencv2/ts/ts.hpp"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "skeleton_filter.hpp"

using namespace std;
using namespace perf;
using namespace cv;
using std::tr1::make_tuple;
using std::tr1::get;

//
// Test(s) for the ConvertColor_BGR2GRAY_BT709 function
//

#define IMAGES testing::Values( std::string("./bin/testdata/sla.png"),\
				std::string("./bin/testdata/page.png"),\
				std::string("./bin/testdata/schedule.png") )

typedef perf::TestBaseWithParam<std::string> ImageName;

PERF_TEST_P(ImageName, ConvertColor_BGR2GRAY_BT709, IMAGES)
{
    Mat input = cv::imread(GetParam());
    Mat dst(input.size(), CV_8UC1);
    declare.in(input, WARMUP_RNG).out(dst).iterations(100);
    TEST_CYCLE()
    {
        ConvertColor_BGR2GRAY_BT709(input, dst);
    }
    SANITY_CHECK(dst, 1 + 1e-6);
}

//
// Test(s) for the ImageResize function
//

#define MAT_SIZES  ::perf::szVGA, ::perf::sz720p, ::perf::sz1080p

typedef perf::TestBaseWithParam<Size> Size_Only;

PERF_TEST_P(Size_Only, ImageResize, testing::Values(MAT_SIZES))
{
    Size sz = GetParam();
    Size sz_to(sz.width / 2, sz.height / 2);

    cv::Mat src(sz, CV_8UC1), dst(Size(sz_to), CV_8UC1);
    declare.in(src, WARMUP_RNG).out(dst);

    TEST_CYCLE()
    {
        ImageResize(src, dst, sz_to);
    }

    SANITY_CHECK(dst, 1 + 1e-6);
}

//
// Test(s) for the skeletonize function
//

 #define IMAGES testing::Values( std::string("./bin/testdata/sla.png"),\
                                 std::string("./bin/testdata/page.png"),\
                                 std::string("./bin/testdata/schedule.png") )

 typedef perf::TestBaseWithParam<std::string> ImageName;
 
 // Without saving
 PERF_TEST_P(ImageName, skeletonize, IMAGES)
 {
     Mat input = cv::imread(GetParam());
	Mat dst(input.size(), CV_8UC1);
    declare.in(input, WARMUP_RNG).out(dst).iterations(100).time(30);
    TEST_CYCLE()
    {
        skeletonize(input, dst, false);
    }
    SANITY_CHECK(dst, 1 + 1e-6);
}
