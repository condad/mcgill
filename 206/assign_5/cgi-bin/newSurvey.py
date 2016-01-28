#!/usr/bin/env python

import cgi, formgen

def new():
	form = cgi.FieldStorage()
	if form.has_key("surveyname") and form["surveyname"].value != "":
		open("../results.ssv","w").close()
		file = open("../survey.ssv","w")
		file.write(form["surveyname"].value + "\n")
		file.close()
new()
formgen.top()
formgen.middle()
formgen.bottom()
