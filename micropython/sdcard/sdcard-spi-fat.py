'''
VCC 	VCC 	3V
GND 	GND
CS  	GP9 	Pin12
MOSI 	GP11	Pin15 SPI1-TX
CLK		GP10	Pin14 SCK
MISO	GP8		Pin11 SPI1-RX

sdcard format fat
'''
import uos, sdcard, machine

# start 1MHz
cs = machine.Pin(15, machine.Pin.OUT)

spi = machine.SPI(
    1,
    baudrate=1000000,
    polarity=0,
    phase=0,
    bits=8,
    firstbit=machine.SPI.MSB,
    sck=machine.Pin(10),
    mosi=machine.Pin(11),
    miso=machine.Pin(12),
)

#Init sdcard
sd = sdcard.SDCard(spi,cs)

#Mount filesystem
vfs = uos.VfsFat(sd)
uos.mount(vfs,"/sd")

# Create file and write something to it
with open("/sd/test01.txt","w") as file:
    file.write("Hello world !\r\n")
    file.write("This is a test\r\n")

# Read justed created
with open("/sd/test01.txt","r") as file:
    data = file.read()
    print(data)
