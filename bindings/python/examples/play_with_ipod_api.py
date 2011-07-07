#!/usr/bin/python

import gpod
import sys

db = gpod.Database(sys.argv[1])

print db

for track in db[4:20]:
    print track
    print track['title']

for pl in db.Playlists:
    print pl
    for track in pl:
        print " ", track
