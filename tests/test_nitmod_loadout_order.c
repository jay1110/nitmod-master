/* Original G_SetClientWeapons publishes the secondary latch to the policy
 * callback before asking whether the primary is disabled (ELF 0x56220).
 * Reuse the existing transaction matrix but observe this intermediate state. */
#define main previous_loadout_matrix
#define G_NITMOD_CheckWeaponAndNotify previous_policy_double
#include "test_nitmod_loadout.c"
#undef G_NITMOD_CheckWeaponAndNotify
#undef main
static int original_order_mismatches;
nitmodWeaponPolicyResult_t G_NITMOD_CheckWeaponAndNotify(
    gentity_t *entity, int weapon, int pickup, int silent ) {
    if(entity->client->sess.latchPlayerWeapon2 != WP_LUGER)
        original_order_mismatches++;
    return previous_policy_double(entity, weapon, pickup, silent);
}
int main(void) {
    int status=previous_loadout_matrix();
    if(status) return status;
    if(original_order_mismatches) {
        fprintf(stderr,"Original-order mismatch: %d policy calls observed the old secondary latch; expected WP_LUGER before policy.\n",original_order_mismatches);
        return 1;
    }
    puts("Original secondary-before-policy ordering passed");
    return 0;
}
