#ifndef CGAME_MATH_H
#define CGAME_MATH_H

/* Vector, angle and geometry helpers */

#include "nitmod_types.h"
#include "nitmod_globals.h"

void SnapVectorTowards(float *param_1,float *param_2);
uint8_t ClampChar(int param_1);
int ClampShort(int param_1);
int DirToByte(float *param_1);
void ByteToDir(uint param_1,uint32_t *param_2);
uint32_t ColorBytes3(float param_1,float param_2,float param_3);
uint32_t ColorBytes4(float param_1,float param_2,float param_3,float param_4);
void NormalizeColor(float *param_1,float *param_2);
uint32_t PlaneFromPoints(float *param_1,float *param_2,float *param_3,float *param_4);
void vectoangles(float *param_1,float *param_2);
void AnglesToAxis(float *param_1,float *param_2);
void AxisClear(uint32_t *param_1);
void AxisCopy(uint32_t *param_1,uint32_t *param_2);
void ProjectPointOnPlane(float *param_1,float *param_2,float *param_3);
void MakeNormalVectors(float *param_1,float *param_2,float *param_3);
void VectorRotate(float *param_1,float *param_2,float *param_3);
long double LerpAngle(float param_1,float param_2,float param_3);
void LerpPosition(float *param_1,float *param_2,float param_3,float *param_4);
void AngleSubtract(float param_1,float param_2);
void AnglesSubtract(float *param_1,float *param_2,float *param_3);
long double AngleMod(float param_1);
long double AngleNormalize2Pi(float param_1);
long double AngleNormalize360(float param_1);
uint AngleNormalizeInt(uint param_1);
long double AngleNormalize180(float param_1);
long double AngleDelta(float param_1,float param_2);
void SetPlaneSignbits(float *param_1);
long double RadiusFromBounds(float *param_1,float *param_2);
void ClearBounds(uint32_t *param_1,uint32_t *param_2);
void AddPointToBounds(float *param_1,float *param_2,float *param_3);
bool PointInBounds(float *param_1,float *param_2,float *param_3);
bool VectorCompare(float *param_1,float *param_2);
void VectorNormalize(float *param_1);
void VectorNormalizeFast(float *param_1);
long double VectorNormalize2(float *param_1,float *param_2);
void _VectorMA(float *param_1,float param_2,float *param_3,float *param_4);
long double _DotProduct(float *param_1,float *param_2);
void _VectorSubtract(float *param_1,float *param_2,float *param_3);
void _VectorAdd(float *param_1,float *param_2,float *param_3);
void _VectorCopy(uint32_t *param_1,uint32_t *param_2);
void _VectorScale(float *param_1,float param_2,float *param_3);
void CrossProduct(float *param_1,float *param_2,float *param_3);
long double VectorLength(float *param_1);
long double VectorLengthSquared(float *param_1);
long double Distance(float *param_1,float *param_2);
long double DistanceSquared(float *param_1,float *param_2);
void VectorInverse(float *param_1);
void Vector4Scale(float *param_1,float param_2,float *param_3);
void MatrixMultiply(float *param_1,float *param_2,float *param_3);
void AngleVectors(float *param_1,float *param_2,float *param_3,float *param_4);
void PerpendicularVector(float *param_1,float *param_2);
void RotatePointAroundVector(float *param_1,float *param_2,float *param_3,float param_4);
void RotateAroundDirection(float *param_1,float param_2);
void GetPerpendicularViewVector(float *param_1,float *param_2,float *param_3,float *param_4);
void ProjectPointOntoVector(float *param_1,float *param_2,float *param_3,float *param_4);
void ProjectPointOntoVectorBounded(float *param_1,float *param_2,float *param_3,float *param_4);
long double DistanceFromLineSquared(float *param_1,float *param_2,float *param_3);
long double DistanceFromVectorSquared(float *param_1,float *param_2,float *param_3);
long double vectoyaw(float *param_1);
void AxisToAngles(int param_1,float *param_2);
long double VectorDistance(float *param_1,float *param_2);
long double VectorDistanceSquared(float *param_1,float *param_2);
void LerpColor(float *param_1,float *param_2,float *param_3,float param_4);

#endif

