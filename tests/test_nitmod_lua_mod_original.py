"""Check the Lua cause translation against the immutable original ELF table."""
from pathlib import Path
import struct, re, hashlib, json
root=Path(__file__).resolve().parents[1]
binary=root/'original_nitmod_shared_objects_32bit/qagame.mp.i386.so'
b=binary.read_bytes(); ph=struct.unpack_from('<I',b,28)[0]; size,count=struct.unpack_from('<HH',b,42)
segments=[struct.unpack_from('<8I',b,ph+i*size) for i in range(count)]
def offset(a):
    return next(o+a-v for t,o,v,_,length,_,_,_ in segments if t==1 and v<=a<v+length)
names=[]
for i in range(70):
    pointer=struct.unpack_from('<I',b,offset(0x2a7bc0)+4*i)[0]
    start=offset(pointer);names.append(b[start:b.index(b'\0',start)].decode())
aliases={'MOD_FG42SCOPE':'MOD_FG42_SCOPE','MOD_POISON_GAS':'MOD_POISONGAS','MOD_POISON_GAS_MINE':'MOD_POISONGASMINE'}
header=(root/'src_2.60/game/nitmod_lua_mod.h').read_text()
mapped=re.findall(r'case (MOD_\w+): return (\d+);',header)
for native,original in mapped:
    assert names[int(original)]==aliases.get(native,native),(native,original)
assert len(mapped)==len({int(i) for _,i in mapped})
assert len(mapped)==69, 'every original damage cause must be mapped'
print(json.dumps({'sha256':hashlib.sha256(b).hexdigest(),'table':'0x2a7bc0','mapped':len(mapped),'original_only':sorted(set(names[:-1])-{aliases.get(n,n) for n,_ in mapped})},indent=2))
print('Original ELF -> native/Lua cause map: PASS')
