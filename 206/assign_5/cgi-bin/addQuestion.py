#!/usr/bin/env python

import cgi, formgen

def add():
	form = cgi.FieldStorage()
	if form.has_key("question") and form["question"].value != "":
		file = open("../survey.ssv","a")
		file.write(form["question"].value + "\n")
		file.close()
add()
formgen.top()
formgen.middle()
formgen.bottom()
