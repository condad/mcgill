#!/usr/bin/env python

import cgi, formgen

def results():
	form = cgi.FieldStorage()
	file = open("../results.ssv","a")
	index = 1
	while form.has_key("q%d" % index):
		file.write(form["q%d" % index].value +" ")
		index += 1
	file.write("\n")
	file.close()

def calc():
	file = open("../results.ssv")
	option = []
	start = 1
	for line in file.readlines():
		data = line.split()
		for num in range(len(data)):
			if start:
				option.append([])
			option[num].append(int(data[num]))
		start = 0
	file.close()
	
	names = open("../survey.ssv")
	index = -1
	for line in names.readlines():
		if index < 0:
			print "<p><u>%s</u></p>" % line.rstrip()		
		else:
			sa = option[index].count(1)
			a = option[index].count(2)
			d = option[index].count(3)
			sd = option[index].count(4)
			average = (sa + 2*a + 3*d + 4*sd)/(sa + a + d + sd)
			print "<div>%s:</div>" % line.rstrip()
			print """
				<div>Strongly Agreed: %d Agreed:
				 %d Disagreed: %d Strongly Disagreed:
				 %d Average: %d</div>
			""" % (sa, a, d, sd, average)
		index += 1
	names.close()

results()
formgen.top()
calc()
formgen.bottom()		
