#!/usr/bin/env python3

#
# This plugin requires HatSploit: https://hatsploit.netlify.app
# Current source: https://github.com/EntySec/HatSploit
#

from hatsploit.lib.plugin import Plugin


class HatSploitPlugin(Plugin):
    def __init__(self):
        super().__init__()

        self.backend = ['test.so', '/tmp/test.so']

        self.scope = {
            2: {
                'test': 1
            }
        }

        self.details = {
            'Name': "Test Pwny Plugin",
            'Plugin': "test",
            'Authors': [
                'Ivan Nikolsky (enty8080) - plugin developer'
            ],
            'Description': ""
        }

        self.commands = {
            'test': {
                'test': {
                    'Description': "test",
                    'Usage': "test",
                    'MinArgs': 0
                }
            }
        }

    def test(self, argc, argv):
        self.print_empty(self.session.send_command(
            'test', output=True, scope=self.scope))

    def load(self):
        pass