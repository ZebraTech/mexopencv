/**
 * @file bilateralFilter.cpp
 * @brief mex interface for cv::bilateralFilter
 * @ingroup imgproc
 * @author Kota Yamaguchi
 * @date 2011
 */
#include "mexopencv.hpp"
#include "opencv2/imgproc.hpp"
using namespace std;
using namespace cv;

/**
 * Main entry called from Matlab
 * @param nlhs number of left-hand-side arguments
 * @param plhs pointers to mxArrays in the left-hand-side
 * @param nrhs number of right-hand-side arguments
 * @param prhs pointers to mxArrays in the right-hand-side
 */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // Check the number of arguments
    nargchk(nrhs>=1 && (nrhs%2)==1 && nlhs<=1);

    // Argument vector
    vector<MxArray> rhs(prhs, prhs+nrhs);

    // Option processing
    int d = 7;
    double sigmaColor = 50.0;
    double sigmaSpace = 50.0;
    int borderType = cv::BORDER_DEFAULT;
    for (int i=1; i<nrhs; i+=2) {
        string key(rhs[i].toString());
        if (key == "Diameter")
            d = rhs[i+1].toInt();
        else if (key == "SigmaColor")
            sigmaColor = rhs[i+1].toDouble();
        else if (key == "SigmaSpace")
            sigmaSpace = rhs[i+1].toDouble();
        else if (key == "BorderType")
            borderType = BorderType[rhs[i+1].toString()];
        else
            mexErrMsgIdAndTxt("mexopencv:error",
                "Unrecognized option %s", key.c_str());
    }

    // Process
    Mat src(rhs[0].toMat(rhs[0].isUint8() ? CV_8U : CV_32F)), dst;
    bilateralFilter(src, dst, d, sigmaColor, sigmaSpace, borderType);
    plhs[0] = MxArray(dst);
}
