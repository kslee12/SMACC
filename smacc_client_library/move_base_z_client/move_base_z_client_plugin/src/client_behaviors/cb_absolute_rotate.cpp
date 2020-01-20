
#include <move_base_z_client_plugin/client_behaviors/cb_absolute_rotate.h>

namespace move_base_z_client
{
CbAbsoluteRotate::CbAbsoluteRotate()
{
}

CbAbsoluteRotate::CbAbsoluteRotate(float absoluteGoalAngleDegree)
{
    this->absoluteGoalAngleDegree = absoluteGoalAngleDegree;
}

void CbAbsoluteRotate::onEntry() 
{
    double goal_angle;

    if (!this->absoluteGoalAngleDegree)
    {
        this->currentState->param("goal_angle", goal_angle, 45.0);
    }
    else
    {
        goal_angle = *this->absoluteGoalAngleDegree;
    }

    this->requiresClient(moveBaseClient_);

    auto plannerSwitcher = moveBaseClient_->getComponent<PlannerSwitcher>();
    //this should work better with a coroutine and await
    //this->plannerSwitcher_->setForwardPlanner();
    plannerSwitcher->setDefaultPlanners();

    ros::Rate rate(10.0);
    geometry_msgs::Pose currentPoseMsg;
    while (ros::ok())
    {
        tf::StampedTransform currentPose;
        try
        {
            listener.lookupTransform("/odom", "/base_link",
                                     ros::Time(0), currentPose);

            tf::poseTFToMsg(currentPose, currentPoseMsg);
            break;
        }
        catch (tf::TransformException ex)
        {
            ROS_INFO("[CbAbsoluteRotate] Waiting transform: %s", ex.what());
            ros::Duration(1.0).sleep();
        }
    }

    ClMoveBaseZ::Goal goal;
    goal.target_pose.header.frame_id = "/odom";
    goal.target_pose.header.stamp = ros::Time::now();

    auto currentAngle = tf::getYaw(currentPoseMsg.orientation);
    auto targetAngle = goal_angle * M_PI / 180.0;
    goal.target_pose.pose.position = currentPoseMsg.position;
    goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(targetAngle);

    ROS_INFO_STREAM("current pose: " << currentPoseMsg);
    ROS_INFO_STREAM("goal pose: " << goal.target_pose.pose);
    moveBaseClient_->sendGoal(goal);
}
} // namespace move_base_z_client
