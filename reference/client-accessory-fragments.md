# General accessory fragments

CG_LoseACC in sorted/cgame_client.c selects character accModels/accSkins
by accessory index and obtains its origin from either head or body refEntity.
The typed port generalizes the existing CG_LoseHat implementation; the active
hat wrapper calls it with ACC_HAT, tag_mouth and head=true, matching original
event/effect calls. Body fragments use roll velocity 50 and effectFlags bit 2;
head fragments retain 400. The original body effect bit is retained without
claiming an additional native effect consumer. Existing gravity, fade, bounce
and fire inheritance remain in the fragment implementation.

Full-cgame tests spawn each accessory from both tag parents and inspect the
actual local-entity list, registered model/skin selection, transformed origin,
roll, fragment type and body bit. Invalid accessory input cannot allocate.
Null/invalid client/character checks fail closed instead of dereferencing.

No new server events or arbitrary accessory-detachment triggers are added;
existing hat events now use the generalized implementation. Random-number
sequence and extreme-time behavior are not proven bit-identical to original.
Browser fragment rendering remains unverified. Pak assets are untouched.
