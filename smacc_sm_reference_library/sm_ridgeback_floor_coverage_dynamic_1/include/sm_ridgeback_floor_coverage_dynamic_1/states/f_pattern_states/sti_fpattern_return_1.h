namespace sm_ridgeback_floor_coverage_dynamic_1
{
  namespace f_pattern_states
  {
    // STATE DECLARATION
    template <typename SS>
    struct StiFPatternReturn1 : smacc::SmaccState<StiFPatternReturn1<SS>, SS>
    {
      typedef SmaccState<StiFPatternReturn1<SS>, SS> TSti;
      using TSti::context_type;
      using TSti::SmaccState;

      // TRANSITION TABLE
      typedef mpl::list<

          Transition<EvCbSuccess<CbUndoPathBackwards, OrNavigation>, StiFPatternRotate1<SS>>

          >
          reactions;

      // STATE FUNCTIONS
      static void staticConfigure()
      {
        TSti::template configure_orthogonal<OrNavigation, CbUndoPathBackwards>();
        TSti::template configure_orthogonal<OrLED, CbLEDOn>();
      }

      void runtimeConfigure()
      {
      }
    };
  } // namespace f_pattern_states
} // namespace sm_ridgeback_floor_coverage_dynamic_1