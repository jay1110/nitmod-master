"""Original ELF item tags independently verify Lua's divergent weapon IDs."""
from pathlib import Path
import struct,re,hashlib,json
root=Path(__file__).resolve().parents[1]
b=(root/'original_nitmod_shared_objects_32bit/qagame.mp.i386.so').read_bytes()
assert hashlib.sha256(b).hexdigest()=='84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49'
ph=struct.unpack_from('<I',b,28)[0];size,count=struct.unpack_from('<HH',b,42)
segments=[struct.unpack_from('<8I',b,ph+i*size) for i in range(count)]
def offset(a):
    return next(o+a-v for t,o,v,_,length,_,_,_ in segments if t==1 and v<=a<v+length)
items={}
for i in range(1,73):
    row=struct.unpack_from('<14I',b,offset(0x2a59a0)+56*i)
    if not row[0] or row[9]!=1: continue
    a=offset(row[0]);name=b[a:b.index(b'\0',a)].decode()
    items.setdefault(name,[]).append(row[10])
expected={
 'weapon_fg42':'WP_FG42', 'weapon_fg42scope':'WP_FG42SCOPE',
 'weapon_medic_adrenaline':'WP_MEDIC_ADRENALINE', 'weapon_medic_syringe':'WP_MEDIC_SYRINGE',
 'weapon_poison_syringe':'WP_POISON_SYRINGE', 'weapon_bomb':'WP_BOMB',
 'weapon_tripmine':'WP_TRIPMINE', 'weapon_poisonbomb':'WP_POISON_BOMB',
 'weapon_mobile_mg42':'WP_MOBILE_MG42', 'weapon_mobile_mg42_set':'WP_MOBILE_MG42_SET',
 'weapon_kar43':'WP_K43', 'weapon_kar43_scope':'WP_K43_SCOPE',
 'weapon_mortar':'WP_MORTAR', 'weapon_mortar_set':'WP_MORTAR_SET',
 'weapon_binoculars':'WP_BINOCULARS', 'weapon_class_special':'WP_PLIERS',
 'weapon_satchel':'WP_SATCHEL', 'weapon_satchelDetonator':'WP_SATCHEL_DET',
 'weapon_smokebomb':'WP_SMOKE_BOMB'}
header=(root/'src_2.60/game/nitmod_weapon_ids.h').read_text()
table=re.findall(r'WP_\w+|VERYBIGEXPLOSION',header.split('= {',1)[1].split('};',1)[0])
assert len(table)==52 and len(set(table))==52
for name,native in expected.items():
    assert len(items[name])==1 and table[items[name][0]]==native,(name,items[name],native)
assert {table[i] for i in items['weapon_landmine']}=={'WP_LANDMINE','WP_POISON_MINE'}
print(json.dumps({'sha256':hashlib.sha256(b).hexdigest(),'original_item_table':'0x2a59a0','independent_weapon_tags':len(expected)+2},indent=2))
print('Original weapon item tags -> shared snapshot/Lua mapping: PASS')
