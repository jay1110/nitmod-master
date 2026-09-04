# Animated explosion and trail dispatch

Reference: sorted/cgame_particles.c, CG_ParticleExplosion and
CG_ParticleExplosionTrail (lines 482 and 552). The recovered constructors
share the same typed particle fields, allocation order, animation lookup,
duration/roll handling, size interpolation, light type and initial motion.
Their difference is the entry guard: cg_wolfparticles for explosions,
cg_trailparticles for trails. Disabled calls consume neither pool entries
nor random values and do not inspect the animation string.

The production implementation shares the ET 2.60 constructor internally and
exposes both original entrypoints. All active CG_RocketTrail branches now
call the trail constructor: missile smoke, flame barrels, flying parts,
ramjets, fire columns and smoky fire columns. Their existing typed trajectory,
fluid and timing behavior was already present, not newly reconstructed here.
Ordinary impact/explosion callers continue to use CG_ParticleExplosion.
No packet identifiers, assets, server commands or shared structures change.

Full-cgame fixture tests exercise both constructors over four values of each
independent option (negative, zero, one, two), pool allocation and disabled
null inputs. Negative duration verifies no random roll is consumed. The
active rocket dispatcher is exercised for six types, both explosion-option
states and air/slime contents; trail creation must remain independent of
cg_wolfparticles, and slime must create no animated particles.

Native Debug build and all 97 CTest tests passed. Rendering, shader frame
appearance, RNG parity across platforms and original-server replay remain
unverified. This closes the explosion-trail dispatch gap from
client-particle-options.md, not the entire particle or cgame port.
