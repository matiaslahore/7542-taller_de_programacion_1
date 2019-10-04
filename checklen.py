import os
len = os.stat("out").st_size

if(len == 1093):
    print("TEST SUCCESS")
else:
    print("TEST FAIL")