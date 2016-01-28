#!/usr/bin/env python

import cgi, formgen

def end():
	print """
		<p>Thanks for making a survey!!</p>
        	<div><a href="http://www.cs.mcgill.ca/~csulli7/welcome.html">Return Home</a></div>
        	<div><a href="http://www.cs.mcgill.ca/~csulli7/createsurvey.html">Create a New Survey</a></div>
        	<div><form action="http://www.cs.mcgill.ca/~csulli7/cgi-bin/survey.py"><br>
		<input type="submit" value="Take Survey">
		</form></div>
	"""

formgen.top()
end()
formgen.bottom()	
