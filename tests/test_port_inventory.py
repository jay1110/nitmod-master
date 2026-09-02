#!/usr/bin/env python3
"""Verify that the committed Ghidra-function inventory is reproducible."""
from __future__ import annotations

import pathlib
import subprocess
import sys
import tempfile


def main() -> None:
    if len(sys.argv) != 2:
        raise SystemExit("usage: test_port_inventory.py <repository-root>")
    root = pathlib.Path(sys.argv[1]).resolve()
    committed = root / "reference" / "port_inventory.csv"
    generator = root / "tools" / "build_port_inventory.py"

    with tempfile.TemporaryDirectory() as temporary:
        generated = pathlib.Path(temporary) / "port_inventory.csv"
        subprocess.run(
            [sys.executable, str(generator), "--source", str(root / "src_nitmod_decompiled"),
             "--output", str(generated)],
            cwd=root, check=True, stdout=subprocess.DEVNULL,
        )
        if committed.read_bytes() != generated.read_bytes():
            raise AssertionError(
                "reference/port_inventory.csv is stale; run tools/build_port_inventory.py"
            )


if __name__ == "__main__":
    main()
