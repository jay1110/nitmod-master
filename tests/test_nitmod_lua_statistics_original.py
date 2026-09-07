"""Compare every original damage-to-statistics row against production mappings."""
from pathlib import Path
import struct,re,hashlib,json
root=Path(__file__).resolve().parents[1]
b=(root/'original_nitmod_shared_objects_32bit/qagame.mp.i386.so').read_bytes()
assert hashlib.sha256(b).hexdigest()=='84a7e7958952f804d65fbe6db6b4758ea0cf6b596b26a514a68de0ba3bd9ef49'
ph=struct.unpack_from('<I',b,28)[0];size,count=struct.unpack_from('<HH',b,42)
segments=[struct.unpack_from('<8I',b,ph+i*size) for i in range(count)]
def offset(a): return next(o+a-v for t,o,v,_,length,_,_,_ in segments if t==1 and v<=a<v+length)
original={}
for i in range(69):
    cause,stat=struct.unpack_from('<2I',b,offset(0x23c040)+8*i);original.setdefault(cause,stat)
enum=(root/'src_2.60/game/bg_public.h').read_text().split('typedef enum extWeaponStats_s',1)[1].split('} extWeaponStats_t',1)[0]
enum=re.sub(r'//[^\n]*','',enum)
indices={name:i for i,name in enumerate(re.findall(r'\bWS_\w+',enum))}
rows=dict(re.findall(r'\{\s*(MOD_\w+)\s*,\s*(WS_\w+)\s*\}',(root/'src_2.60/game/g_match.c').read_text()))
causes=re.findall(r'case (MOD_\w+): return (\d+);',(root/'src_2.60/game/nitmod_lua_mod.h').read_text())
for native,wire in causes:
    stat=indices[rows.get(native,'WS_MAX')]
    converted=26 if stat in (indices['WS_SMOKE'],indices['WS_MAX']) else stat if stat<15 else stat-1
    assert converted==original.get(int(wire),26),(native,wire,converted,original.get(int(wire),26))
print(json.dumps({'sha256':hashlib.sha256(b).hexdigest(),'aWeapMOD':'0x23c040','verified_causes':len(causes)},indent=2))
print('Original damage -> native statistics -> Lua index: PASS')
