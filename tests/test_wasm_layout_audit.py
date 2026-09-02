from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from run_wasm_layout_audit import parse, compare


class LayoutAudit(unittest.TestCase):
    def test_rows(self):
        self.assertEqual(parse("void *.size=4\nT.size=16\nT.field=4,8\n"),
                         {"void *.size": [4], "T.size": [16], "T.field": [4, 8]})

    def test_invalid(self):
        for text in ("", "void *.size=8", "void *.size=4\nnoise", "void *.size=4\nvoid *.size=4"):
            with self.subTest(text=text), self.assertRaises(ValueError):
                parse(text)

    def test_differences(self):
        self.assertEqual(compare({"x": [0, 4]}, {"x": [0, 4]}), [])
        self.assertEqual(compare({"x": [0, 4]}, {"x": [4, 4]}),
                         [{"field": "x", "mod": [0, 4], "engine": [4, 4]}])
        with self.assertRaises(ValueError):
            compare({"x": [4]}, {"y": [4]})

    def test_snapshot_capacity_difference(self):
        mod = parse("void *.size=4\nsnapshot_t.entities=1500,147456\nMAX_ENTITIES_IN_SNAPSHOT=512\n")
        engine = parse("void *.size=4\nsnapshot_t.entities=1500,294912\nMAX_ENTITIES_IN_SNAPSHOT=1024\n")
        self.assertEqual([row["field"] for row in compare(mod, engine)],
                         ["snapshot_t.entities", "MAX_ENTITIES_IN_SNAPSHOT"])


if __name__ == "__main__":
    unittest.main()
