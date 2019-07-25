#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <random>
#include <algorithm>
#include <math.h>

#include "ceres/ceres.h"

#include "third_party/eigenmvn/eigenmvn.h"

using Eigen::Vector2d;
using Eigen::Vector3d;
using Eigen::VectorXd;
using Eigen::Matrix3d;
using Eigen::MatrixXd;
using Eigen::Quaterniond;

struct Pose
{
    Vector3d pos;
    Quaterniond quat;
};

struct PoseSolution
{
    Pose pose;
    ceres::Solver::Summary summary;
};

struct Twist
{
    Vector3d vel;
    Vector3d ang_vel;
};

class Utilities
{
    public:
        static Matrix3d Euler2DCM_312(const Vector3d& eulVec);
        static Vector3d DCM2Euler_312(const MatrixXd& DCM);
        static MatrixXd FeaPointsTargetToChaser(const Pose& state, const Vector3d& rCamVec, const MatrixXd& rFeaMat);
        static Vector2d CameraProjection(const Vector3d& point3DVec, const double& f);
        static VectorXd SimulateMeasurements(const MatrixXd& rMat, const double& focal_length);
        static VectorXd AddGaussianNoiseToVector(const VectorXd& vec, const double& std);
        static Pose ConjugatePose(const Pose& state);
        static double PositionScore(const Vector3d& pos, const Vector3d& posHat);
        static double AttitudeScore(const Quaterniond& quat, const Quaterniond& quatHat);
        static double StdVectorMean(const std::vector<double>& vec);
        static double StdVectorVar(const std::vector<double>& vec);

        static constexpr double DEG2RAD = M_PI/180.0;
        static constexpr double RAD2DEG = 180.0/M_PI;
};

#endif // UTILITIES_H_