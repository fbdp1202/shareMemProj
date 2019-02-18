import sysv_ipc
import time
memory = sysv_ipc.SharedMemory(123457)
while 1:
	data = str(input("Indata: "))+'\0'
	print(data)
	bdata=data.encode("utf-8")
	print(len(bdata))
	memory_value = memory.write(bdata)
