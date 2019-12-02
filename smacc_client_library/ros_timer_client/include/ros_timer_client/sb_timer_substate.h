#pragma once

#include <smacc/smacc.h>
#include <ros_timer_client/timer_client.h>

namespace ros_timer_client
{
class SbTimer : public smacc::SmaccSubStateBehavior
{
public:
  virtual void onEntry() override;
  virtual void onExit() override;

private:
  SmaccTimerClient *timerClient_;
};
} // namespace ros_timer_client
