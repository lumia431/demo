from datetime import *
import datetime,time

a = datetime.date(2003,12,2)
now = datetime.datetime.now()
# dates support calendar arithmetic
birthday = datetime.date(1964, 7, 31)
#age = now - birthday
#print(age.days)

today = datetime.date.today()
yesterday = today - datetime.timedelta(days=1)
last_month = today.month - 1 if today.month - 1 else 12
time_stamp = time.time()
datetime.datetime.fromtimestamp(time_stamp)
int(time.mktime(today.timetuple()))
today_str = today.strftime("%Y-%m-%d")
today + datetime.timedelta(hours=8)

now += timedelta(hours=10)
print(now)
