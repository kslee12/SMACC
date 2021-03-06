#include <smacc/smacc.h>

namespace sm_ridgeback_floor_coverage_dynamic_1 {
namespace SS2 {
namespace sm_ridgeback_floor_coverage_dynamic_1 {
namespace radial_motion_states {

//FORWARD DECLARATION OF INNER STATES
class StiRadialRotate;
class StiRadialReturn;
class StiRadialEndPoint;
class StiRadialLoopStart;
} // namespace radial_motion_states
} // namespace sm_ridgeback_floor_coverage_dynamic_1
using namespace sm_ridgeback_floor_coverage_dynamic_1::radial_motion_states;

// STATE DECLARATION
struct SsRadialPattern2 : smacc::SmaccState<SsRadialPattern2, MsDanceBotRunMode, StiRadialLoopStart>
{
public:
    using SmaccState::SmaccState;

// TRANSITION TABLE
    typedef mpl::list<
    
    Transition<EvLoopEnd<StiRadialLoopStart>, StNavigateToWaypointsX, ENDLOOP> //,

    >reactions;

// STATE FUNCTIONS
    static void staticConfigure()
    {
        //configure_orthogonal<OrObstaclePerception, CbLidarSensor>();
    }

    void runtimeConfigure()
    {
    }

    int iteration_count = 0;
    static constexpr int total_iterations() { return 32; }
    static constexpr float ray_angle_increment_degree() { return 360.0 / total_iterations(); }
    static constexpr float ray_length_meters() { return 5; }
};

// FORWARD DECLARATION FOR THE SUPERSTATE
using SS = SsRadialPattern2;
#include <sm_ridgeback_floor_coverage_dynamic_1/states/radial_motion_states/sti_radial_end_point.h>
#include <sm_ridgeback_floor_coverage_dynamic_1/states/radial_motion_states/sti_radial_return.h>
#include <sm_ridgeback_floor_coverage_dynamic_1/states/radial_motion_states/sti_radial_rotate.h>
#include <sm_ridgeback_floor_coverage_dynamic_1/states/radial_motion_states/sti_radial_loop_start.h>
} // namespace SS2
} // namespace sm_ridgeback_floor_coverage_dynamic_1