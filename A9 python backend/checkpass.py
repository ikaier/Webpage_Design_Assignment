#!/usr/bin/python
import cgi, cgitb, csv, sys

form=cgi.FieldStorage()
username=form.getvalue("var1")
password=form.getvalue("var2")

print("ContentType:text/html\n\n")
with open('users.csv') as file:
    reader = csv.reader(file)
    for row in reader:
        if row[0]==username and row[1]==password:
            print("Your Password Matches")
            sys.exit()
    print("Wrong username or password")



