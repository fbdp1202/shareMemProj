import sysv_ipc

memory = sysv_ipc.SharedMemory(123456)

memory_value = memory.read().decode("utf-8")

i = memory_value.find('\0')

if i != -1 :
	memory_value = memory_value[:i]

print(memory_value)