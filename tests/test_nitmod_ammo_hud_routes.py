"""Source wiring regression; not a rendered HUD/runtime parity test."""
from pathlib import Path

root = Path(__file__).resolve().parents[1]
text = (root / 'src_2.60/cgame/cg_draw.c').read_text()
body = text.split('static int CG_PlayerAmmoValue(', 1)[1].split('#define HEAD_TURNTIME', 1)[0]
knife = body.split('case WP_KNIFE:', 1)[1].split('case WP_AMMO:', 1)[0]
assert 'NITMOD_ClientSkillUnlocked(ps->clientNum, SK_LIGHT_WEAPONS, 5)' in knife
assert 'skipammo = qtrue;' in knife
hidden = body.split('case WP_AMMO:', 1)[1].split('case WP_LANDMINE:', 1)[0]
assert 'case WP_BOMB:' in hidden and 'case WP_POISON_BOMB:' in hidden
clip = body.split('case WP_LANDMINE:', 1)[1].split('default:', 1)[0]
assert 'case WP_POISON_MINE:' in clip and 'case WP_POISON_SYRINGE:' in clip
assert 'if( weap == WP_LANDMINE || weap == WP_POISON_MINE )' in body
assert '*ammo = ps->ammoclip[BG_FindClipForWeapon(weap)];' in body
print('Nitmod ammo HUD routing checks passed')
