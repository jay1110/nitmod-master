#ifndef CG_NITMOD_CORONAS_H
#define CG_NITMOD_CORONAS_H
#define NITMOD_MAX_MAP_CORONAS 1024
typedef struct {
    float scale;
    vec3_t origin, color;
} nitmodMapCorona_t;
void CG_NitmodResetCoronas(void);
void CG_NitmodSpawnCorona(void);
void CG_NitmodDrawCoronas(void);
int CG_NitmodCoronaCount(void);
const nitmodMapCorona_t *CG_NitmodCorona(int index);
#endif
