from pathlib import Path
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
from audit_engine_syscall_numbers import parse_enum, compare, compare_exports


class EnumAudit(unittest.TestCase):
    def test_values_and_comments(self):
        source = "typedef enum { A, /* , FAKE */ B = 0x10, C, D = BASE, E = C, } T;"
        self.assertEqual(parse_enum(source, "T", {"BASE": 700}),
                         {"A": 0, "B": 16, "C": 17, "D": 700, "E": 17})

    def test_reject_unsupported(self):
        for body in ("A = UNKNOWN", "A = 1 + 2", "#if X\n A\n#endif", "A, A", "A = 012"):
            with self.subTest(body=body), self.assertRaises(ValueError):
                parse_enum("typedef enum {" + body + "} T;", "T")

    def test_missing_or_duplicate(self):
        for source in ("", "typedef enum { A } T; typedef enum { B } T;"):
            with self.assertRaises(ValueError):
                parse_enum(source, "T")

    def test_classifications(self):
        rows = compare({"A": 0, "B": 2, "C": 3}, {"A": 0, "B": 5, "OTHER": 3})
        self.assertEqual([row["status"] for row in rows],
                         ["same-number", "different-number", "missing-engine-name"])
        self.assertIsNone(rows[2]["engine_number"])

    def test_export_collisions_and_extensions(self):
        report = compare_exports({"A": 0, "OLD": 1}, {"A": 0, "NEW": 1, "EXT": 8})
        self.assertEqual(report["counts"], {"same-number": 1, "different-number": 0,
                                          "missing-engine-name": 1, "missing-mod-name": 2})
        rows = {row["name"]: row for row in report["entries"]}
        self.assertEqual(rows["OLD"]["engine_names_at_mod_number"], ["NEW"])
        self.assertEqual(rows["NEW"]["mod_names_at_engine_number"], ["OLD"])
        self.assertEqual(rows["EXT"]["mod_names_at_engine_number"], [])

    def test_commented_bot_exports_keep_explicit_message_number(self):
        source = "typedef enum { SNAP = 10, // OLD_BOT,\n MESSAGE = 14, EXTRA } T;"
        self.assertEqual(parse_enum(source, "T"), {"SNAP": 10, "MESSAGE": 14, "EXTRA": 15})


if __name__ == "__main__":
    unittest.main()
