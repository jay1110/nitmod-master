#ifndef CG_NITMOD_EVENTS_H
#define CG_NITMOD_EVENTS_H

/* Internal dispatch marker, never a network event ID. */
#define NITMOD_FIRE_THROWKNIFE (-3)
qboolean CG_NitmodExtendedEvent(centity_t *cent, int wireEvent);
void CG_NitmodFireSupportChat(const entityState_t *es, qboolean airstrike);
extern vmCvar_t cg_obituary, cg_tkSounds, cg_goatSound;
int CG_NitmodDeathCause(int wireCause);
int CG_NitmodObituaryWeapon(int cause);
qboolean CG_NitmodFormatObituary(int cause, const char *target, const char *attacker,
    qboolean self, qboolean teamkill, char *out, int size);
void CG_NitmodObituary(const entityState_t *es);
typedef struct {
    const char *first, *second;
    qhandle_t shader;
    int scale;
    vec3_t color;
} nitmodObituaryPlan_t;
qboolean CG_NitmodPlanGraphicObituary(const entityState_t *es, int mode,
    qhandle_t fallback, nitmodObituaryPlan_t *plan);
void CG_NitmodSpecialObituary(int cause, char **message, char **suffix);
void CG_NitmodObituaryPrint(const char *text, qhandle_t shader, const entityState_t *event);
qboolean CG_NitmodAddGraphicObituary(const char *first, const char *second, qhandle_t shader, int scale, const vec3_t color);
void CG_NitmodObituarySounds(const entityState_t *es);
void CG_NitmodObituaryReset(void);

#endif
