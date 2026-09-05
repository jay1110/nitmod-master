# Active mover speed scale

Original `g_moverScale` registration at 0x2a91d0 uses default 1.0 and flags 0.
The recovered four consumers are now connected to the ordinary live qagame
cvar cache:

- G_ScriptAction_FollowSpline multiplies the parsed speed before duration.
- G_ScriptAction_GotoMarker assigns scaled entity speed for ET_MOVER only.
  Its acceleration/deceleration override retains the unscaled script speed,
  as the original does; non-mover goto paths are unchanged.
- Reached_Train and Reached_Train_rotating multiply explicit corner speed,
  but do not multiply the fallback train speed. The existing minimum speed
  of 1 remains. Rotating-corner explicit duration retains precedence.
  The native rotating path now also stores gDuration before SetMoverState,
  preventing that routine from replacing the newly calculated duration with
  stale state. The full integration test exposed this pre-existing mismatch.

Evidence: sorted nitmod_script.c (followspline and gotomarker),
nitmod_unknown.c (Reached_Train and Reached_Train_rotating), original cvar
inventory. No private offsets were introduced. This is not a global multiplier
for all doors or all movers. No new client command is sent: existing position
and angle trajectories supply cgame with the resulting movement.

Full-qagame tests run both real train handlers through a link-entity syscall
fixture: four scales, explicit/fallback speed and fixed-duration combinations.
They verify duration, trajectory velocity, clock, next corner, sound and link.
The actual followspline parser is exercised against a typed spline fixture.
Live map, collision/passenger and browser testing remain outstanding; the
gotomarker change has build coverage but no new runtime fixture in this batch.
No UI feature, assets or original binaries were changed. Extreme/nonfinite
administrator-supplied scaling remains subject to existing mover arithmetic.
