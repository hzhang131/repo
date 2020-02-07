import re
import sys

MONTHS = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December',
          'Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec']
DAYS = ['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday']
PART = ['morning', 'noon', 'afternoon', 'evening']
TIME = ['am', 'a.m.', 'pm', 'p.m.', 'A.M.', 'P.M.', 'AM', 'PM']
HOLIDAYS = ["New Year's Day", 'Martin Luther King, Jr. Day', 'George Washington’s Birthday', 'Memorial Day', 'Independence Day', 'Labor Day', 'Columbus Day', 'Veterans Day', 'Thanksgiving Day', 'Christmas Day']


def LEAP_YEAR(yr):
    """
    Examines whether a year is a leap year.
    """
    return yr % 4 == 0

def sanity_check(lst):

    """
    Removes illegal date and time cases.
    """

    # removes 02/30, 2/30, 2-30, 2.30
    for i in lst:
        for j in re.findall(r'(?:0?2[/\-\.]30|0?[2469][/\-\.]31|11[/\-\.]31)', i, re.IGNORECASE):
            lst.remove(i)
            print('\033[91m'+"ILLEGAL D&T ENTRY REMOVED (ILLEGAL DATE):"+'\033[0m', '\033[94m'+i+'\033[0m')

    # removes February 31
    for i in lst:
        for j in re.findall(r'((?:February[(,\s)\s(\.\s)]30|Feb[(,\s)\s(\.\s)]30|(?:February|Feb|April|Apr|June|Jun|September|Sep|November|Nov)[(,\s)\s(\.\s)]31)(?:th|st))', i, re.IGNORECASE):
            lst.remove(i)
            print('\033[91m'+"ILLEGAL D&T ENTRY REMOVED (ILLEGAL DATE):"+'\033[0m', '\033[94m'+i+'\033[0m')
    
    for i in lst:
        for j in re.findall(r'the[\s](?:(?:thirtieth|30th) of February|(?:thirty-first|31st of (?:February|Feb|April|Apr|June|Jun|September|Sep|November|Nov)))', i, re.IGNORECASE):
            lst.remove(i)
            print('\033[91m'+"ILLEGAL D&T ENTRY REMOVED (ILLEGAL DATE):"+'\033[0m', '\033[94m'+i+'\033[0m')

    # removes February 19nd, March 2st, the 31st of February
    for i in lst:
        for j in re.findall(r'(?:[023]?1nd|[023]?1rd|[023]?1th|[02]?2st|[02]?2rd|[02]?2th|[02]?3st|[02]?3nd|[02]?3th|[0-3]?[4-9]st|[0-3]?[4-9]nd|[0-3]?[4-9]rd)', i, re.IGNORECASE):
            lst.remove(i)
            print(i)
            print('\033[91m'+"ILLEGAL D&T ENTRY REMOVED (ILLEGAL ORDINAL NUMERAL):"+'\033[0m', '\033[94m'+i+'\033[0m')

    # removes illegal non-leap year February 29ths.
    # such as 02/29/2019
    # the 29th of 2019.
    # February. 29th, 2019
    for i_ in range(0, 100):
        if LEAP_YEAR(i_):
            continue
        else:
            for i in lst:
                for j in re.findall(r'(?:February|Feb)(?:(\.\s)|\s)(29(th)?),\s\d{2}'+re.escape(str(i_)), i, re.IGNORECASE):
                    lst.remove(i)
                    print('\033[91m'+"ILLEGAL D&T ENTRY REMOVED (NOT LEAP YEAR):"+'\033[0m', '\033[94m'+i+'\033[0m')
                for j in re.findall(r'0?2/29/\d{2}'+re.escape(str(i_)), i, re.IGNORECASE):
                    lst.remove(i)
                    print('\033[91m'+"ILLEGAL D&T ENTRY REMOVED (NOT LEAP YEAR):"+'\033[0m', '\033[94m'+i+'\033[0m')
                for j in re.findall(r'the[\s](?:twenty-ninth|29th)[\s]of[\s]February,[\s]\d{2}'+re.escape(str(i_)), i, re.IGNORECASE):
                    lst.remove(i)
                    print('\033[91m'+"ILLEGAL D&T ENTRY REMOVED (NOT LEAP YEAR):"+'\033[0m', '\033[94m'+i+'\033[0m')
    return


def tner(filename):
    """
    identify all possible date and times in an article. 
    """
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
    for i in re.findall(r'(?:(?:Monday|Tuesday|Wednesday|Thursday|Friday|Saturday|Sunday|Mon|Tue|Wed|Thu|Fri|Sat|Sun)[,][\s])?(?:[1][0-2]|[0]?[1-9])[/\-/\.(\.\s)\s](?:(?:[0]?[1-9]|[1]\d|[2]\d|[3][01])[/\-/.\s])?[12]\d{3}', s, re.IGNORECASE):
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
    
    for i in re.findall(r'(?:(?:Monday|Tuesday|Wednesday|Thursday|Friday|Saturday|Sunday|Mon|Tue|Wed|Thu|Fri|Sat|Sun)[,][\s])?(?:January|Jan|February|Feb|March|Mar|April|Apr|May|June|Jun|July|Jul|August|Aug|September|Sep|October|Oct|November|Nov|December|Dec)(?:[\s]|[\.][\s])(?:(?:[2]\d|[1]\d|[3][01]|[0]?[1-9])(?:st|th|nd|rd)?(?:[,][\s])?)?[12]\d{3}', s, re.IGNORECASE):
        lst.append(i)
        s = s.replace(i, "")

    for i in re.findall(r'(?:(?:Monday|Tuesday|Wednesday|Thursday|Friday|Saturday|Sunday|Mon|Tue|Wed|Thu|Fri|Sat|Sun)[,][\s])?(?:January|Jan|February|Feb|March|Mar|April|Apr|May|June|Jun|July|Jul|August|Aug|September|Sep|October|Oct|November|Nov|December|Dec)(?:[\s]|[\.][\s])(?:(?:[2]\d|[1]\d|[3][01]|[0]?[1-9])(?:st|th|nd|rd)?(?:[,][\s])?)', s, re.IGNORECASE):
        lst.append(i)
        s = s.replace(i, "")

    #try to capture the following variants.
    # the third of March.
    # the 21st of april.
    # the 29th of February, 2019
    

    for i in re.findall(r'the[\s](?:first|second|third|fourth|fifth|sixth|seventh|eighth|nineth|tenth|eleventh|twelfth|thirteenth|fourteenth|fifteenth|sixteenth|seventeenth|eighteenth|nineteenth|twentieth|twenty-first|twenty-second|twenty-third|twenty-fourth|twenty-fifth|twenty-sixth|twenty-seventh|twenty-eighth|twenty_nineth|thirtieth|thirty-first|(?:(?:[2]\d|[1]\d|[3][01]|[0]?[1-9])(?:st|th|nd|rd)))[\s]of[\s](?:January|Jan|February|Feb|March|Mar|April|Apr|May|June|Jun|July|Jul|August|Aug|September|Sep|October|Oct|November|Nov|December|Dec)[,][\s][12]\d{3}', s, re.IGNORECASE):
        lst.append(i)
        s = s.replace(i, "")

    for i in re.findall(r'the[\s](?:first|second|third|fourth|fifth|sixth|seventh|eighth|nineth|tenth|eleventh|twelfth|thirteenth|fourteenth|fifteenth|sixteenth|seventeenth|eighteenth|nineteenth|twentieth|twenty-first|twenty-second|twenty-third|twenty-fourth|twenty-fifth|twenty-sixth|twenty-seventh|twenty-eighth|twenty_nineth|thirtieth|thirty-first|(?:(?:[2]\d|[1]\d|[3][01]|[0]?[1-9])(?:st|th|nd|rd)))[\s]of[\s](?:January|Jan|February|Feb|March|Mar|April|Apr|May|June|Jun|July|Jul|August|Aug|September|Sep|October|Oct|November|Nov|December|Dec)', s, re.IGNORECASE):
        lst.append(i)
        s = s.replace(i, "")

    for i in re.findall(r'(?:January|Jan|February|Feb|March|Mar|April|Apr|May|June|Jun|July|Jul|August|Aug|September|Sep|October|Oct|November|Nov|December|Dec)[\s]of[\s][12]\d{3}', s, re.IGNORECASE):
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
    # 1963
    for i in re.findall(r'[12]\d{3}', s, re.IGNORECASE):
        lst.append(i)
        s = s.replace(i, "")

    sanity_check(lst)

    new_f = open("output.txt", "w+")
    output_str = ""
    for i in lst:
        output_str += i 
        output_str += "\n"
    new_f.write(output_str)
    print('\033[92m'+"OUTPUT SAVED TO output.txt"+'\033[0m')
    return

tner(sys.argv[1])