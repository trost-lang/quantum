# -*- coding: utf-8 -*-

import unittest
from subprocess import check_output


def run(json):
    return check_output(["./trost", "-j", "jsons/%s" % json]).strip()


class Quantum_Test(unittest.TestCase):

    def test_print(self):
        self.assertEqual("नमस्ते, Hello, Привет, 您好, ہیلو", run("print.json"))

    def test_iadd(self):
        self.assertEqual("42", run("iadd.json"))

    def test_fadd(self):
        self.assertEqual("44.21", run("fadd.json"))

    def test_mixed_add(self):
        self.assertEqual("43.34", run("mixed_add.json"))

    def test_scat(self):
        self.assertEqual("Hello, World!", run("scat.json"))

    def test_function(self):
        self.assertEqual("17", run("function.json"))

    def test_bool(self):
        self.assertEqual("true", run("bool.json"))

    def test_if_else(self):
        self.assertEqual("lesser", run("if_else.json"))

if __name__ == '__main__':
    unittest.main()
