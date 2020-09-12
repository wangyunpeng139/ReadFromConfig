/*
 * @Description: 
 * @Version: 1.0
 * @Autor: skylor
 * @Date: 2020-09-12 09:57:22
 * @LastEditors: skylor
 * @LastEditTime: 2020-09-12 10:32:30
 */
#include <config/config.h>

using namespace std;

namespace params {

void ShowParams()
{
    cout << "++++++++++ System ++++++++++" << endl;
    cout << "miLockSleep: " << params::sys::mbStrictLock << endl;
    cout << endl;
    std::cout << "++++++++++ Stats ++++++++++" << std::endl;
    std::cout << "mbWriteKFsToFile: " << (int)params::stats::mbWriteKFsToFile << std::endl;
    std::cout << "msOutputDir: " << params::stats::msOutputDir << std::endl;
    std::cout << std::endl;
    cout << "++++++++++ Timings ++++++++++" << endl;
    cout << "miLockSleep: " << params::timings::miLockSleep << endl;
    cout << "----- Client -----" << endl;
    cout << "miRosRate: " << params::timings::client::miRosRate << endl;
    cout << "miViewerRate: " << params::timings::client::miViewerRate << endl;
    cout << "miMappingRate: " << params::timings::client::miMappingRate << endl;
    cout << "miCommRate: " << params::timings::client::miCommRate << endl;
    cout << endl;

    //Tracking Functions Inlier Thresholds
    cout << "----- Server -----" << endl;
    cout << "++++++++++ Colors ++++++++++" << endl;
    cout << "R0: " << params::colors::mc0.mfR << endl;
    cout << "G0: " << params::colors::mc0.mfG << endl;
    cout << "B0: " << params::colors::mc0.mfB << endl;
    cout << "R1: " << params::colors::mc1.mfR << endl;
    cout << "G1: " << params::colors::mc1.mfG << endl;
    cout << endl;
    //语义分割脚本
    cout << "++++++++++ Python脚本配置信息 ++++++++++" << endl;
    cout << "PythonScript : " << params::Topo::client::PythonScript << endl;
    cout << "NetModel: " << params::Topo::client::NetModel << endl;
    cout << "Categories: " << params::Topo::client::Categories  << endl;
    cout << endl;

}

} //end ns
