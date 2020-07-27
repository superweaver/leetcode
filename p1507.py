class Solution:
    def reformatDate(self, date: str) -> str:
       lessThan10 = len(date) == 12
       #print(len(date))
       offset = 0 if lessThan10 else 1
       d = int(date[0:1+offset])
       mm = {}
       for i, v in enumerate(["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"]):
           mm[v] = i+1
       #print(date[4+offset:7+offset])
       m = mm[date[4+offset:7+offset]]
       y = int(date[-4:])
       return "{}-{:02}-{:02}".format(y, m, d)

date = "20th Oct 2052"
s = Solution()
print(s.reformatDate(date))
date = "6th Jun 1933"
print(s.reformatDate(date))
date = "26th May 1960"
print(s.reformatDate(date))


       
# 
class Solution:
    def reformatDate(self, date: str) -> str:
        # create a dict
        # handle 01 here
        Month = {"Jan":"01", "Feb":"02", "Mar":"03", "Apr":"04", "May":"05", "Jun":"06", "Jul":"07", "Aug":"08", "Sep":"09", "Oct":"10", "Nov":"11", "Dec":"12"}
        date_ = date.split(" ")
        # date_[2] is year
        # date_[1] is month
        # date_[0] is day
        # 1st or 12nd
        # len date_[0] == 3 or 4
        return '-'.join([date_[2], Month[date_[1]], date_[0][:-2] if len(date_[0][:-2]) == 2 else '0' + date_[0][:-2]])


