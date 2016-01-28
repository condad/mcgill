#!/usr/bin/env python

def top():
	print "Content-type: text/html\n\n"	
	print """
		<!DOCTYPE html>
		<html>
		<head>
		<title>Create Survey</title>
		<link rel="stylesheet" href="http://www.cs.mcgill.ca/~csulli7/style.css">
		</head>
		<body>
		<div class="header">
		<h1>Create Survey</h1>
		</div>
		<div class="menu">
		<ul>
        	<li><a href="http://www.cs.mcgill.ca/~csulli7/index.html">Home</a></li>
		<li><a href="http://www.cs.mcgill.ca/~csulli7/login.html">Login/New User</a></li>
		<li><a href="http://www.cs.mcgill.ca/~csulli7/createsurvey.html">Create Survey</a></li>
    		</ul>
		<form action="http://www.cs.mcgill.ca/~csulli7/cgi-bin/survey.py">
		<input type="submit" value="TAKE SURVEY">
		</form>
		</div>
		<div class="page">
	"""

def middle():
	print """
		<span>To create a survey enter the title</span>
                <span> of your survey into the title box.</span>
                <span> Then enter the first question into the</span>
                <span> question box and hit ADD. This will create</span>
                <span> a new survey starting with the initial question.</span>
                <span> After this you may add more questions to the survey</span>
                <span> by hitting the add button. When the survey is</span>
                <span> complete, press DONE.</span>
                <div>
                <div class="survey">
                <form action="http://www.cs.mcgill.ca/~csulli7/cgi-bin/newSurvey.py" method="GET">
                <span>Enter the survey name:</span>
                <input type="textarea" name="surveyname">
                <input type="submit" value="NEW">
                </form>
	"""
	data = open("../survey.ssv", "r")
	index = 0
	for line in data.readlines():
		if index == 0:
			print "<div>Survey Name: %s</div>" % line.rstrip()
		else:
			print "<div>Question %d: %s</div>" % (index,line.rstrip())
		index += 1
	data.close()
	print """
		<form action="http://www.cs.mcgill.ca/~csulli7/cgi-bin/addQuestion.py" method="GET">
                <span>Enter a question name:</span>
                <input type="textarea" name="question">
                <input type="submit" value="ADD">
                </form><br>
                <form action="http://www.cs.mcgill.ca/~csulli7/cgi-bin/endSurvey.py" method="GET">
                <input type="submit" value="DONE">
                </form>
                </div>
                </div>
	"""

def bottom():
	print """
		</div>
		</body>
		</html>
	"""
