from subprocess import Popen, PIPE
from PIL import Image
import io
import os

p = Popen(["/home/sdsoc/PycharmProjects/sb_work_space/TestShareMemory/SubProcessPIPE/a.out"], shell=True, stdout=PIPE, stdin=PIPE)
im = Image.open("image.jpg");
if im == None:
	print("Open Image Error")
	exit(1)

buf = io.BytesIO()
im.save(buf, format='JPEG')
jpeg = buf.getvalue()
p.stdin.write(bytes(str(len(jpeg)) + '\n', 'UTF-8'))
p.stdin.flush()
result = p.stdout.readline()
print(int(result))
p.stdin.write(jpeg)
p.stdin.flush()

# result = p.stdout.readline()
# print(int(result))
# p.stdin.flush()

# value = str(ii) + '\n'
# value = bytes(value, 'UTF-8')  # Needed in Python 3.
# p.stdin.write(value)
# p.stdin.flush()
# result = p.stdout.readline().strip()
# print(int(result))