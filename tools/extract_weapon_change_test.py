"""Generate test-only verbatim Pmove function bodies; never edit product sources."""
import pathlib
import re
import sys

NAMES = ('PM_AddEvent', 'PM_AltSwitchFromForWeapon', 'PM_AltSwitchToForWeapon',
         'PM_RaiseAnimForWeapon', 'PM_DropAnimForWeapon', 'PM_StartWeaponAnim',
         'PM_IdleAnimForWeapon', 'PM_ReloadAnimForWeapon', 'PM_ContinueWeaponAnim',
         'PM_BeginWeaponReload', 'PM_FinishWeaponRaise',
         'PM_ReloadClip', 'PM_FinishWeaponReload', 'PM_BeginWeaponChange', 'PM_FinishWeaponChange', 'PM_CheckForReload',
         'PM_ProcessWeaponTransitions', 'PM_WeaponFiringClip', 'PM_WeaponUseAmmo', 'PM_WeaponAmmoAvailable')


def extract(source, name):
    matches = list(re.finditer(r'^(?:static\s+)?(?:void|int)\s+' + name +
                              r'\s*\([^)]*\)\s*\{', source, re.M))
    if len(matches) != 1:
        raise ValueError('expected exactly one definition: ' + name)
    match = matches[0]
    # Ignore braces inside comments, strings and character literals.
    tokens = re.finditer(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[{}]',
                         source[match.end() - 1:], re.S)
    depth = 0
    for token in tokens:
        if token.group() == '{':
            depth += 1
        elif token.group() == '}':
            depth -= 1
            if not depth:
                return source[match.start():match.end() - 1 + token.end()]
    raise ValueError('unterminated function: ' + name)


if __name__ == '__main__':
    source = pathlib.Path(sys.argv[1]).read_text()
    bodies = '\n\n'.join(extract(source, name) for name in NAMES)
    pathlib.Path(sys.argv[2]).write_text('/* Generated verbatim from bg_pmove.c. */\n' + bodies + '\n')
