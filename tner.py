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

def tner(filename):
    lst = []
    f = open(filename, "r")
    s_ = f.read()
    s = s_

    # extract holidays.
    for i in HOLIDAYS:
        for j in re.findall(re.escape(i), s):
            lst.append(j)
            s.replace(j, "")

    # try to capture the following variants.
    # Wednesday, 02/05/2020
    # Wednesday, 02/2020
    # 02/2020
    for i in re.findall(r'(?:(?:Monday|Tuesday|Wednesday|Thursday|Friday|Saturday|Sunday)[,][\s])?(?:[1][0-2]|[0]?[1-9]|January|February|March|April|May|June|July|August|September|October|November|December|Jan|Feb|Mar|Apr|May|Jun|Jul|Aug|Sep|Oct|Nov|Dec)[/-/.(/.\s)\s](?:(?:[0]?[1-9]|[1]\d|[2]\d|[3][01])[/-/.\s])?(?:[1]\d{3}|[2][0][0]\d|[2][0][1]\d|[2][0][2][0])', s, re.IGNORECASE):
        lst.append(i) 
        s.replace(i, "")

    # for i in re.findall(r'([0]\d|[1][0-2])\/([0-2]\d|[3][0-1])\/([2][01]|[1][6-9])\d{2}', s):
    #     print(i)
    #     lst.append(i)
    
    print(lst)    

tner("input.txt")