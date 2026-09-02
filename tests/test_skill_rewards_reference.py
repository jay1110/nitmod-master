"""Compare every production reward string against the hash-pinned ELF."""
import importlib.util
import pathlib
import subprocess
import sys

sys.dont_write_bytecode = True
root = pathlib.Path(sys.argv[1]).resolve()
spec = importlib.util.spec_from_file_location('rewards', root / 'tools/extract_skill_rewards.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
expected = [value for row in module.extract(root) for value in row]
result = subprocess.run([sys.argv[2]], check=True, capture_output=True, text=True)
assert result.stdout.splitlines() == expected, 'reconstructed reward table differs from original ELF'
