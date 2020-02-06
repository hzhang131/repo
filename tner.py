# Regex notes:
# ? -- exactly zero or one occurences of prev char
# \d -- any digit
# {n} -- n occurences
# . -- any arbitrary char
# \s -- whitespace
import re
import datetime
from datetime import date

MONTHS = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December',
          'Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec']
DAYS = ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday']
PART = ['morning', 'noon', 'afternoon', 'evening']
TIME = ['am', 'a.m.', 'pm', 'p.m.', 'A.M.', 'P.M.', 'AM', 'PM']
HOLIDAYS = ["New Year's Day", 'Martin Luther King, Jr. Day', 'George Washington’s Birthday', 'Memorial Day', 'Independence Day', 'Labor Day', 'Columbus Day', 'Veterans Day', 'Thanksgiving Day', 'Christmas Day']

def sanity_check(lst):
    pass
    return


def tner(filename):
    lst = []
    f = open(filename, "r")
    s_ = f.read()
    s = s_

    # extract holidays.
    for i in HOLIDAYS:
        for j in re.findall(re.escape(i), s, re.IGNORECASE):
            lst.append(j)
            s = s.replace(j, "")

    # try to capture the following variants.
    # 10/10/2018
    # 04/01/1999
    for i in re.findall(r'(?:(?:Monday|Tuesday|Wednesday|Thursday|Friday|Saturday|Sunday|Mon|Tue|Wed|Thu|Fri|Sat|Sun)[,][\s])?(?:[1][0-2]|[0]?[1-9])[/\-/\.(\.\s)\s](?:(?:[0]?[1-9]|[1]\d|[2]\d|[3][01])[/\-/.\s])?(?:[1]\d{3}|[2][0][0]\d|[2][0][1]\d|[2][0][2][0])', s, re.IGNORECASE):
        lst.append(i) 
        s = s.replace(i, "")


    # try to capture the following variants.
    # Wedenesday, Oct. 11th
    # Tuesday, Oct. 2018
    # October 20th
    # Tuesday, March 15
    # January 5th, 2015
    # Aug 23rd, 2000
    # Thursday, Nov. 28th, 1948
    for i in re.findall(r'(?:(?:Monday|Tuesday|Wednesday|Thursday|Friday|Saturday|Sunday|Mon|Tue|Wed|Thu|Fri|Sat|Sun)[,][\s])?(?:January|Jan|February|Feb|March|Mar|April|Apr|May|June|Jun|July|Jul|August|Aug|September|Sep|October|Oct|November|Nov|December|Dec)(?:[\s]|[\.][\s])(?:(?:[2]\d|[1]\d|[3][01]|[0]?[1-9])(?:st|th|nd|rd)?(?:[,][\s])?)?(?:[1]\d{3}|[2][0][0]\d|[2][0][1]\d|[2][0][2][0])', s, re.IGNORECASE):
        lst.append(i)
        s = s.replace(i, "")

    for i in re.findall(r'(?:(?:Monday|Tuesday|Wednesday|Thursday|Friday|Saturday|Sunday|Mon|Tue|Wed|Thu|Fri|Sat|Sun)[,][\s])?(?:January|Jan|February|Feb|March|Mar|April|Apr|May|June|Jun|July|Jul|August|Aug|September|Sep|October|Oct|November|Nov|December|Dec)(?:[\s]|[\.][\s])(?:(?:[2]\d|[1]\d|[3][01]|[0]?[1-9])(?:st|th|nd|rd)?(?:[,][\s])?)', s, re.IGNORECASE):
        lst.append(i)
        s = s.replace(i, "")

    #try to capture the following variants.
    # the third of March.
    # the 21st of april.
    for i in re.findall(r'the[\s](?:first|second|third|fourth|fifth|sixth|seventh|eighth|nineth|tenth|eleventh|twelfth|thirteenth|fourteenth|fifteenth|sixteenth|seventeenth|eighteenth|nineteenth|twentieth|twenty-first|twenty-second|twenty-third|twenty-fourth|twenty-fifth|twenty-sixth|twenty-seventh|twenty-eighth|twenty_nineth|thirtieth|thirty-first|(?:(?:[2]\d|[1]\d|[3][01]|[0]?[1-9])(?:st|th|nd|rd)))[\s]of[\s](?:January|Jan|February|Feb|March|Mar|April|Apr|May|June|Jun|July|Jul|August|Aug|September|Sep|October|Oct|November|Nov|December|Dec)', s, re.IGNORECASE):
        lst.append(i)
        s = s.replace(i, "")

    for i in re.findall(r'(?:January|Jan|February|Feb|March|Mar|April|Apr|May|June|Jun|July|Jul|August|Aug|September|Sep|October|Oct|November|Nov|December|Dec)[\s]of[\s](?:[1]\d{3}|[2][0][0]\d|[2][0][1]\d|[2][0][2][0])', s, re.IGNORECASE):
        lst.append(i)
        s = s.replace(i, "")

    # try to capture the following variants.
    # monday the 23rd.
    for i in re.findall(r'(?:Monday|Tuesday|Wednesday|Thursday|Friday|Saturday|Sunday)[\s]the[\s](?:first|second|third|fourth|fifth|sixth|seventh|eighth|nineth|tenth|eleventh|twelfth|thirteenth|fourteenth|fifteenth|sixteenth|seventeenth|eighteenth|nineteenth|twentieth|twenty-first|twenty-second|twenty-third|twenty-fourth|twenty-fifth|twenty-sixth|twenty-seventh|twenty-eighth|twenty_nineth|thirtieth|thirty-first|(?:(?:[2]\d|[1]\d|[3][01]|[0]?[1-9])(?:st|th|nd|rd)))', s, re.IGNORECASE):
        lst.append(i)
        s = s.replace(i, "")

    # try to capture the following variants.
    # 10/31
    # Monday, 10/31
    for i in re.findall(r'(?:(?:Monday|Tuesday|Wednesday|Thursday|Friday|Saturday|Sunday|Mon|Tue|Wed|Thu|Fri|Sat|Sun)[,][\s])?(?:[1][0-2]|[0]?[1-9])[/\-/\.(\.\s)\s](?:[1]\d|[2]\d|[3][01]|[0]?[1-9])', s, re.IGNORECASE):
        lst.append(i) 
        s = s.replace(i, "")

    # try to capture the following variants.
    # Monday, 2pm
    # Monday afternoon
    for i in re.findall(r'(?:(?:Monday|Tuesday|Wednesday|Thursday|Friday|Saturday|Sunday|Mon|Tue|Wed|Thu|Fri|Sat|Sun)(?:[\s]|[,][\s]))(?:(?:[1]\d|[2][0-4]|[0]?\d)(?:am|pm|a.m.|p.m.|am.|pm.)|(?:evening|morning|afternoon|noon|midnight))', s, re.IGNORECASE):
        lst.append(i)
        s = s.replace(i, "")
        
    # try to capture the following variants.
    # Monday thru Friday.

    for i in DAYS: 
        for j in re.findall(re.escape(i), s, re.IGNORECASE):
            lst.append(i)
            s = s.replace(i, "") 

    # try to capture the following variants.
    # MONTHS.

    for i in MONTHS:
        for j in re.findall(re.escape(i), s, re.IGNORECASE):
            lst.append(i)
            s = s.replace(i, "") 
    # try to capture the following variants.
    # (in) 1963
    for i in re.findall(r'[\s](?:[1]\d{3}|[2][0][0]\d|[2][0][1]\d|[2][0][2][0])', s, re.IGNORECASE):
        lst.append(i)
        s = s.replace(i, "")

    sanity_check(lst)

    new_f = open("output.txt", "w+")
    output_str = ""
    for i in lst:
        output_str += i 
        output_str += "\n"
    new_f.write(output_str)
    print("output saved to output.txt")
    return

tner("input.txt")