
#ifndef CONFIG_H_
#define CONFIG_H_

//C++
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <ctime>



namespace params {

typedef double fptype;

const std::string s0 (__FILE__);
const std::size_t p0 = s0.find("include");
const std::string s1 (s0.substr(0,p0));
const std::string s2 ("conf/config.yaml");  //! 配置文件
const std::string s3 = s1 + s2;
const std::string conf (s3);

const std::string out0 (__FILE__);
const std::size_t iout0 = out0.find("include");
const std::string out1 (out0.substr(0,iout0));
const std::string out2 ("output/");
const std::string out3 = out1 + out2;
const std::string outpath (out3);


//!  ========================  通用底层函数  ==================================
template<typename T> inline static T GetVal(std::string path, std::string paramname)
{
    cv::FileStorage fSettings(path, cv::FileStorage::READ);

    if(!fSettings.isOpened())
    {
       std::cerr << "Failed to open config file at: " << path << std::endl;
       exit(-1);
    }

    const double val = fSettings[paramname];
    return (T)val;
}


 inline static std::string GetStr(std::string path, std::string paramname)
{
    cv::FileStorage fSettings(path, cv::FileStorage::READ);

    if(!fSettings.isOpened())
    {
       std::cerr << "Failed to open config file at: " << path << std::endl;
       exit(-1);
    }

    const std::string val = fSettings[paramname];
    return val;
}

//! ========================= 以下全为专用函数  =============================

inline std::string GetTimeAsString()
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );

    std::string year,mon,day,hour,min,sec,stringtime;

    std::stringstream* ss;
    ss = new std::stringstream;
    *ss << now->tm_year + 1900;
    year = ss->str();

    ss = new std::stringstream;
    *ss << now->tm_mon + 1;
    mon = ss->str();
    if(mon.size() == 1)
    {
        ss = new std::stringstream;
        *ss << 0 << mon;
        mon = ss->str();
    }

    ss = new std::stringstream;
    *ss << now->tm_mday;
    day = ss->str();
    if(day.size() == 1)
    {
        ss = new std::stringstream;
        *ss << 0 << day;
        day = ss->str();
    }

    ss = new std::stringstream;
    *ss << now->tm_hour;
    hour = ss->str();
    if(hour.size() == 1)
    {
        ss = new std::stringstream;
        *ss << 0 << hour;
        hour = ss->str();
    }

    ss = new std::stringstream;
    *ss << now->tm_min;
    min = ss->str();
    if(min.size() == 1)
    {
        ss = new std::stringstream;
        *ss << 0 << min;
        min = ss->str();
    }

    ss = new std::stringstream;
    *ss << now->tm_sec;
    sec = ss->str();
    if(sec.size() == 1)
    {
        ss = new std::stringstream;
        *ss << 0 << sec;
        sec = ss->str();
    }

    ss = new std::stringstream;
    *ss << year << mon << day << "_" << hour << min << sec << "_";

    stringtime = ss->str();

    delete ss;

    return stringtime;
}


//! 下面使用到了ROS msg 话题消息（找到ROS包进行修改）， 使用的方式是 仿函数
//TODO 记得回来补充使用案例
#if 1

struct ColorRGBA
{

    ColorRGBA()
            : r(0.0)
            , g(0.0)
            , b(0.0)
            , a(0.0)  {
    }

    typedef float _r_type;
    _r_type r;

    typedef float _g_type;
    _g_type g;

    typedef float _b_type;
    _b_type b;

    typedef float _a_type;
    _a_type a;

}; // struct ColorRGBA_



inline ColorRGBA MakeColorMsg(float fR,float fG, float fB)
{
    ColorRGBA msg;
    msg.r = fR;
    msg.g = fG;
    msg.b = fB;
    msg.a = 1.0;
    return msg;
}

struct VisColorRGB
{
public:
    VisColorRGB(float fR,float fG, float fB)
        : mfR(fR),mfG(fG),mfB(fB),
          mu8R((u_int8_t)(fR*255)),mu8G((u_int8_t)(fG*255)),mu8B((u_int8_t)(fB*255)),mColMsg(MakeColorMsg(fR,fG,fB))
        {
            //...
        }

    const float mfR,mfG,mfB;
    const u_int8_t mu8R,mu8G,mu8B;
    const ColorRGBA mColMsg;
};

#endif   //end of 仿函数案例




namespace sys {
    const int mbStrictLock = 1;
    const std::string msTime = GetTimeAsString();
}

namespace stats {
    const bool mbWriteKFsToFile = GetVal<bool>(conf,"Stats.WriteKFsToFile");
    const std::string  msOutputDir = outpath;
}

namespace timings {
    const int miLockSleep = GetVal<int>(conf,"Timing.LockSleep");

    namespace client {
        const int miRosRate = GetVal<int>(conf,"Timing.Client.RosRate");
        const int miViewerRate = GetVal<int>(conf,"Timing.Client.ViewerRate");
        const int miMappingRate = GetVal<int>(conf,"Timing.Client.MappingRate");
        const int miCommRate = GetVal<int>(conf,"Timing.Client.CommRate");
    }

    namespace server {
        const int miRosRate = GetVal<int>(conf,"Timing.Server.RosRate");
        const int miViewerRate = GetVal<int>(conf,"Timing.Server.ViewerRate");
        const int miMappingRate = GetVal<int>(conf,"Timing.Server.MappingRate");
        const int miCommRate = GetVal<int>(conf,"Timing.Server.CommRate");
        const int miPlaceRecRateRate = GetVal<int>(conf,"Timing.Server.PlaceRecRate");

        //TODO  skylor加入
        const int miWriteToDBRate = GetVal<int>(conf,"Timing.Server.WriteToDBRate");
    }
}

namespace extractor {
    const int miNumFeatures = GetVal<int>(conf,"ORBextractor.nFeatures");
    const fptype mfScaleFactor = GetVal<fptype>(conf,"ORBextractor.scaleFactor");
    const int miNumLevels = GetVal<int>(conf,"ORBextractor.nLevels");
    const int miIniThFAST = GetVal<int>(conf,"ORBextractor.iniThFAST");
    const int miNumThFAST = GetVal<int>(conf,"ORBextractor.minThFAST");
}

namespace tracking {
    const int miInitKFs = GetVal<int>(conf,"Tracking.iInitKFs");
    //KF Creation Params
    const int miMinFrames = GetVal<int>(conf,"Tracking.MinFrames");
    const int miMaxFrames = GetVal<int>(conf,"Tracking.MaxFrames");
    const int miMatchesInliersThres = GetVal<int>(conf,"Tracking.nMatchesInliersThres");
    const fptype mfThRefRatio = GetVal<fptype>(conf,"Tracking.thRefRatio");
    //Tracking Functions Inlier Thresholds
    const int miTrackWithRefKfInlierThresSearch = GetVal<int>(conf,"Tracking.TrackWithRefKfInlierThresSearch");
    const int miTrackWithRefKfInlierThresOpt = GetVal<int>(conf,"Tracking.TrackWithRefKfInlierThresOpt");
    const int miTrackWithMotionModelInlierThresSearch = GetVal<int>(conf,"Tracking.TrackWithMotionModelInlierThresSearch");
    const int miTrackWithMotionModelInlierThresOpt = GetVal<int>(conf,"Tracking.TrackWithMotionModelInlierThresOpt");
    const int miTrackLocalMapInlierThres = GetVal<int>(conf,"Tracking.TrackLocalMapInlierThres");
}

namespace mapping {
    const fptype mfRedundancyThres = GetVal<fptype>(conf,"Mapping.RedThres");
    const int miLocalMapSize = GetVal<int>(conf,"Mapping.LocalMapSize");
    const int miLocalMapBuffer = GetVal<int>(conf,"Mapping.LocalMapBuffer");
    const int miNumRecentKFs = GetVal<int>(conf,"Mapping.RecentKFWindow");
}

namespace comm {

    namespace client {
        const fptype mfPubFreq = GetVal<fptype>(conf,"Comm.Client.PubFreq");
        const fptype mfPubPeriodicTime = 1/mfPubFreq;

        const int miKfItBound = GetVal<int>(conf,"Comm.Client.KfItBound");
        const int miMpItBound = GetVal<int>(conf,"Comm.Client.MpItBound");
        const int miPubMapBufferSize = GetVal<int>(conf,"Comm.Client.PubMapBuffer");
        const int miSubMapBufferSize = GetVal<int>(conf,"Comm.Client.SubMapBuffer");
        const int miKfPubMax = GetVal<int>(conf,"Comm.Client.PubMaxKFs");
        const int miMpPubMax = GetVal<int>(conf,"Comm.Client.PubMaxMPs");
    }

    namespace server {
        const fptype mfPubFreq = GetVal<fptype>(conf,"Comm.Server.PubFreq");
        const fptype mfPubPeriodicTime = 1/mfPubFreq;

        const int miKfLimitToClient = GetVal<int>(conf,"Comm.Server.KfsToClient");  //发送回客户端的关键帧限制值 K (也是数量上限限制),//max == -1 means there is no upper limit

        const int miKfItBound = GetVal<int>(conf,"Comm.Server.KfItBound");
        const int miMpItBound = GetVal<int>(conf,"Comm.Server.MpItBound");
        const int miPubMapBufferSize = GetVal<int>(conf,"Comm.Server.PubMapBuffer");  //发布话题名
        const int miSubMapBufferSize = GetVal<int>(conf,"Comm.Server.SubMapBuffer");  //订阅话题名
    }

}

namespace placerec {
    const int miNewLoopThres = GetVal<int>(conf,"Placerec.NewLoopThres");
    const int miStartMapMatchingAfterKf = GetVal<int>(conf,"Placerec.StartMapMatchingAfterKf");
    const int miCovisibilityConsistencyTh = GetVal<int>(conf,"Placerec.CovisibilityConsistencyTh");
}

namespace opt {
    //Loop Closure
    const int mSolverIterations = GetVal<int>(conf,"Opt.SolverIterations");
    const int mMatchesThres = GetVal<int>(conf,"Opt.MatchesThres"); //matches that need to be found by SearchByBoW()
    const int mInliersThres = GetVal<int>(conf,"Opt.InliersThres"); //inliers after pose optimization
    const int mTotalMatchesThres = GetVal<int>(conf,"Opt.TotalMatchesThres"); //total matches SearchByProjection
    //RANSAC params
    const fptype mProbability = GetVal<fptype>(conf,"Opt.Probability");
    const int mMinInliers = GetVal<int>(conf,"Opt.MinInliers");
    const int mMaxIterations = GetVal<int>(conf,"Opt.MaxIterations");
    //Map Merger
    const int mGBAIterations = GetVal<int>(conf,"Opt.GBAIterations");
    const int miEssGraphMinFeats = GetVal<int>(conf,"Opt.EssGraphMinFeats");
}

namespace vis {
    const bool mbActive = GetVal<bool>(conf,"Viewer.Active");  //控制着闭环检测的可视化显示

    const bool mbShowCovGraph = GetVal<bool>(conf,"Viewer.ShowCovGraph");
    const bool mbShowMPs = GetVal<bool>(conf,"Viewer.ShowMapPoints");
    const bool mbShowTraj = GetVal<bool>(conf,"Viewer.ShowTraj");
    const bool mbShowKFs = GetVal<bool>(conf,"Viewer.ShowKFs");
    const int miCovGraphMinFeats = GetVal<int>(conf,"Viewer.CovGraphMinFeats");

    const fptype mfScaleFactor = GetVal<fptype>(conf,"Viewer.ScaleFactor");
    const fptype mfTrajMarkerSize = GetVal<fptype>(conf,"Viewer.TrajMarkerSize");
    const fptype mfCovGraphMarkerSize = GetVal<fptype>(conf,"Viewer.CovGraphMarkerSize");
    const fptype mfLoopMarkerSize = GetVal<fptype>(conf,"Viewer.LoopMarkerSize");
    const fptype mfMarkerSphereDiameter = GetVal<fptype>(conf,"Viewer.MarkerSphereDiameter");
    const fptype mfCamSize = GetVal<fptype>(conf,"Viewer.CamSize");
    const fptype mfCamLineSize = GetVal<fptype>(conf,"Viewer.CamLineSize");
}



#if 1
namespace colors {
    const VisColorRGB mc0 = VisColorRGB(GetVal<float>(conf,"Viewer.ColorR0"),GetVal<float>(conf,"Viewer.ColorG0"),GetVal<float>(conf,"Viewer.ColorB0"));
    const VisColorRGB mc1 = VisColorRGB(GetVal<float>(conf,"Viewer.ColorR1"),GetVal<float>(conf,"Viewer.ColorG1"),GetVal<float>(conf,"Viewer.ColorB1"));
    const VisColorRGB mc2 = VisColorRGB(GetVal<float>(conf,"Viewer.ColorR2"),GetVal<float>(conf,"Viewer.ColorG2"),GetVal<float>(conf,"Viewer.ColorB2"));
    const VisColorRGB mc3 = VisColorRGB(GetVal<float>(conf,"Viewer.ColorR3"),GetVal<float>(conf,"Viewer.ColorG3"),GetVal<float>(conf,"Viewer.ColorB3"));
    const VisColorRGB mcCovGraph = VisColorRGB(GetVal<float>(conf,"Viewer.ColorRcov"),GetVal<float>(conf,"Viewer.ColorGcov"),GetVal<float>(conf,"Viewer.ColorBcov"));
}
#endif


//! skylor : topo  08-13
namespace Topo {
    const int miLockSleep = GetVal<int>(conf,"Timing.LockSleep");

    namespace client {
        const std::string PythonScript = GetStr(conf,"Topo.Client.PythonScript");
        const std::string NetModel = GetStr(conf,"Topo.Client.NetModel");
        const size_t Categories = GetVal<size_t>(conf,"Topo.Client.Categories");
    }

    namespace server {
        const std::string PythonScript = GetStr(conf,"Topo.Server.PythonScript");
        const std::string NetModel = GetStr(conf,"Topo.Server.NetModel");
        const size_t Categories = GetVal<size_t>(conf,"Topo.Server.Categories");
    }
}


void ShowParams();

} //end ns

#endif
