import time
import sys

mensaje = "hola flor como estas"

sys.stdout.write("===========================================>             ")
sys.stdout.flush()

for char in mensaje:
    sys.stdout.write(char)
    sys.stdout.flush()
    time.sleep(0.2)
    sys.stdout.write("\b")
    sys.stdout.flush()
    sys.stdout.write("_")
    sys.stdout.flush()
    time.sleep(0.2)
    sys.stdout.write("\b")
    sys.stdout.flush()

print ""