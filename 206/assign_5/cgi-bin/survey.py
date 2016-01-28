#! /usr/bin/env python

import formgen

def survey():
	data = open("../survey.ssv", "r")
	index = 0
	for line in data.readlines():
		if index == 0:
			print "<p><u>%s</u></p>" % line.rstrip()
			print """
				<div>
				<div class="survey">
				<form action="results.py">
			"""
		else:
			print "<p>%s</p>" % (line.rstrip())
			print """
				<input type="radio" name="q%d" value="1">Agree Strongly
				<input type="radio" name="q%d" value="2">Agree
				<input type="radio" name="q%d" value="3">Disagree
				<input type="radio" name="q%d" value="4">Disagree Strongly
			""" % (index,index,index,index)
		index += 1
	data.close()
	print """
		<br><br><input type="submit" value="DONE"><a href="results.html"><div>
		<a href="http://www.cs.mcgill.ca/~csulli7/welcome.html">Home</a></div>
		</form>	
		</div>
		</div>
	"""

formgen.top()
survey()
formgen.bottom()
