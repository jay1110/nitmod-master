#!/usr/bin/env python3
"""Ensure supplied forensic reference modules remain byte-identical."""
from __future__ import annotations

import hashlib
import pathlib
import re
import sys


def main() -> None:
    if len(sys.argv) != 2:
        raise SystemExit("usage: test_reference_artifacts.py <repository-root>")
    root = pathlib.Path(sys.argv[1])
    manifest = root / "reference" / "original_nitmod_i386.sha256"
    modules = root / "original_nitmod_shared_objects_32bit"
    entries = []
    for line in manifest.read_text(encoding="utf-8").splitlines():
        match = re.fullmatch(r"([0-9a-f]{64})\s+(.+)", line, re.IGNORECASE)
        if match:
            entries.append((match.group(1).lower(), match.group(2)))
    if len(entries) != 3:
        raise AssertionError("reference manifest must describe exactly three modules")
    for expected, name in entries:
        path = modules / name
        if not path.is_file():
            raise AssertionError(f"missing reference module: {name}")
        actual = hashlib.sha256(path.read_bytes()).hexdigest()
        if actual != expected:
            raise AssertionError(f"checksum mismatch: {name}")


if __name__ == "__main__":
    main()
